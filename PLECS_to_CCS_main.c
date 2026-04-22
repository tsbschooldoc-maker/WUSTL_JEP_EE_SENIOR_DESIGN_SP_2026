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


// We only need to send 6 floats now (24 bytes) instead of 8
void update_telemetry_data(void)
{
    telemetry_buffer[0].f_val = ext_V_PV;
    telemetry_buffer[1].f_val = ext_I_PV;
    telemetry_buffer[2].f_val = ext_V_Bat;
    telemetry_buffer[3].f_val = ext_I_Bat;
    telemetry_buffer[4].f_val = ext_V_EV;
    telemetry_buffer[5].f_val = ext_I_EV;
    // We removed the two determine() functions!
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
        // Send the 24 bytes of float data (6 floats * 4 bytes)
        if (i2c_tx_index < 24)
        {
            Uint16 float_index = i2c_tx_index / 4;
            Uint16 byte_index = i2c_tx_index % 4;

            Uint16 byte_to_send = (telemetry_buffer[float_index].u32_val >> (byte_index * 8)) & 0xFF;
            I2caRegs.I2CDXR.all = byte_to_send;
            i2c_tx_index++;
        }
        else 
        {
            // CRITICAL FIX: Send a dummy byte so the hardware releases the clock line!
            I2caRegs.I2CDXR.all = 0xFF;
        }
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

