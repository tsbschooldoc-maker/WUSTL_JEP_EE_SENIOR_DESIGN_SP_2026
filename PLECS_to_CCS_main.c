#include "includes.h"
#include "PLECS_to_CCS.h"  
#include "plx_dispatcher.h"
// The union that chops a 32-bit float into four 8-bit bytes
typedef union {
    float f_val;
    Uint32 u32_val;
} FloatPacker;

// An array to hold the 6 values you want to send to the ESP32
FloatPacker telemetry_buffer[8];
Uint16 i2c_tx_index = 0; 

#ifndef _FLASH
#endif

extern   float ext_V_EV;
extern   float ext_I_EV;
extern   float ext_V_PV;
extern   float ext_I_PV;
extern   float ext_V_Bat;
extern   float ext_I_Bat;

void init_I2C_Hardware(void)
{
    EALLOW;
    // TURN ON THE PERIPHERAL CLOCK FIRST!
    CpuSysRegs.PCLKCR9.bit.I2C_A = 1;
    
    GpioCtrlRegs.GPBPUD.bit.GPIO35 = 0;    
    GpioCtrlRegs.GPBQSEL1.bit.GPIO35 = 3;  
    GpioCtrlRegs.GPBGMUX1.bit.GPIO35 = 0;  
    GpioCtrlRegs.GPBMUX1.bit.GPIO35 = 3;   

    GpioCtrlRegs.GPBPUD.bit.GPIO37 = 0;    
    GpioCtrlRegs.GPBQSEL1.bit.GPIO37 = 3;  
    GpioCtrlRegs.GPBGMUX1.bit.GPIO37 = 0;  
    GpioCtrlRegs.GPBMUX1.bit.GPIO37 = 3;   
    EDIS;

    I2caRegs.I2CMDR.bit.IRS = 0;           

    I2caRegs.I2COAR.all = 0x08; // ESP32 will ping 0x08           

    // --- CRITICAL CLOCK FIX ---
    I2caRegs.I2CPSC.all = 9;       
    I2caRegs.I2CCLKL = 10;         
    I2caRegs.I2CCLKH = 5;          
    // --------------------------

    I2caRegs.I2CFFTX.all = 0x0000;
    I2caRegs.I2CFFRX.all = 0x0000;

    I2caRegs.I2CMDR.all = 0x0020;

    I2caRegs.I2CMDR.bit.FREE = 1;
}

extern void MemCopy(Uint16 *SourceAddr, Uint16 *SourceEndAddr, Uint16 *DestAddr);
extern Uint16 RamfuncsLoadStart, RamfuncsLoadEnd, RamfuncsRunStart;
void PLECS_to_CCS_initialize();

#define TSP_VER 0x0202
#ifdef TSP_VER
#if (TSP_VER != THIS_TSP_VER)
#error TSP Version mismatch.
#endif
#endif

/// Function to determine the current operating mode
float determine_system_mode(void)
{
    float i_threshold = 0.1f;
    float v_threshold = 1.0f;

    bool pv_active = (ext_V_PV > v_threshold) || (ext_I_PV > i_threshold);
    bool ev_charging = (ext_I_EV > i_threshold);

    // --- NEW: EMA Filter for Battery Current ---
    // This variable must be static so it remembers its value between cycles
    static float smoothed_I_Bat = 0.0f;

    // Alpha of 0.05 heavily smooths the data. 
    // It takes 5% of the new noisy reading and 95% of the old stable reading.
    smoothed_I_Bat = (0.05f * ext_I_Bat) + (0.95f * smoothed_I_Bat);
    // -----------------------------------------

    if (pv_active && !ev_charging) 
    {
        return 0.0f; 
    } 
    else if (!pv_active && ev_charging) 
    {
        return 1.0f; 
    } 
    // FIXED: Use the smoothed current, and remove the dead zone gap
    else if (pv_active && ev_charging && (smoothed_I_Bat >= 0.0f)) 
    {
        return 2.0f; 
    } 
    else if (pv_active && ev_charging && (smoothed_I_Bat < 0.0f)) 
    {
        return 3.0f; 
    }

    return -1.0f; 
}
// Function to determine the charging speed status
// Returns 1.0f for Fast Charge, 0.0f for Non-Fast Charge, -1.0f for Not Charging

float determine_charging_speed(void)
{
    // Fast charging: 1.8A or greater
    if (ext_I_EV >= 1.8f) 
    {
        return 1.0f; 
    }
    // Regular charging: Anything above "zero" (0.1A to account for sensor noise)
    else if (ext_I_EV > 0.1f) 
    {
        return 0.0f; 
    }
    // Standby: Effectively zero current
    else 
    {
        return -1.0f; 
    }
}

void update_telemetry_data(void)
{
    telemetry_buffer[0].f_val = ext_V_PV;
    telemetry_buffer[1].f_val = ext_I_PV;
    telemetry_buffer[2].f_val = ext_V_Bat;
    telemetry_buffer[3].f_val = ext_I_Bat;
    telemetry_buffer[4].f_val = ext_V_EV;
    telemetry_buffer[5].f_val = ext_I_EV;
    telemetry_buffer[6].f_val = determine_system_mode();
    telemetry_buffer[7].f_val = determine_charging_speed();
}

void respond_to_ESP32(void)
{
    // 1. Transaction Complete (Stop Condition)
    if (I2caRegs.I2CSTR.bit.SCD == 1)
    {
        I2caRegs.I2CSTR.bit.SCD = 1; // Clear the flag first
        i2c_tx_index = 0;            // Reset the byte counter
        
        
        I2caRegs.I2CMDR.bit.IRS = 0; 
        I2caRegs.I2CMDR.bit.IRS = 1; 
    }

 
   // 2. Feed the Pipeline
    if (I2caRegs.I2CSTR.bit.XRDY == 1)
    {
        // Simply send the 32 bytes of float data (8 floats * 4 bytes)
        if (i2c_tx_index < 32)
        {
            Uint16 float_index = i2c_tx_index / 4;
            Uint16 byte_index = i2c_tx_index % 4;

            Uint16 byte_to_send = (telemetry_buffer[float_index].u32_val >> (byte_index * 8)) & 0xFF;
            I2caRegs.I2CDXR.all = byte_to_send;
            i2c_tx_index++;
        }
        // Notice there is NO 'else' block here anymore!
    }
}


void main(void)
{
#ifdef _FLASH
    MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);
#endif

    // disable all interrupts
    DINT;
    IER = 0x0000;
    IFR = 0x0000;

    
    PLECS_to_CCS_initialize();

    // enable interrupts
    EINT;   // global
    ERTM;   // real-time

// Initialize custom hardware
    init_I2C_Hardware();

    // go!
    DISPR_start(); // will not return

    PLX_ASSERT(0); // should never get here
}

