/*
 * Hardware configuration file for: TI28004x
 * Generated with                 : PLECS 4.9.8
 * Generated on                   : Fri Apr 10 19:05:09 2026
 */

/* HAL Includes */
#include "PLECS_to_CCS.h"
#include "plx_hal.h"
#include "plx_dispatcher.h"
#include "pil.h"
#include "pin_map.h"
#include "gpio.h"
#include "xbar.h"
#include "asysctl.h"
#include "sysctl.h"
#include "plx_dio.h"
#include "plx_ain.h"
#include "plx_pwm.h"
#include "math.h"
#include "epwm.h"
#include "hrpwm.h"


/* HAL Declarations */
void DevInit(uint32_t aDeviceClkConf);
void InitFlashHz(uint32_t clkHz);
void F28x_usDelay(long LoopCount);

// Clock configuration
#define PLX_DEVICE_SETCLOCK_CFG       (SYSCTL_OSCSRC_OSC2 | SYSCTL_IMULT(20) |  \
                                       SYSCTL_FMULT_0 | SYSCTL_SYSDIV(1) |  \
                                       SYSCTL_ODIV(2) | \
                                       SYSCTL_PLL_ENABLE)

#define SYSCLK_HZ 100000000L
#define LSPCLK_HZ (100000000L / 4l)

#define PLX_DELAY_US(A)  F28x_usDelay(((((long double) A * \
                                         1000.0L) / \
                                        (long double)10.000000L) - \
                                       9.0L) / 5.0L)
PIL_Obj_t PilObj;
PIL_Handle_t PilHandle = 0;
extern PLX_PWM_Handle_t EpwmHandles[];
// PWM Enable Functions
void PLXHAL_PWM_setToPassive(uint16_t aChannel)
{
   PLX_PWM_setOutToPassive(EpwmHandles[aChannel]);
}

void PLXHAL_PWM_setToOperational(uint16_t aChannel)
{
   PLX_PWM_setOutToOperational(EpwmHandles[aChannel]);
}

void PLXHAL_PWM_prepareSetOutToXTransition(uint16_t aHandle)
{
   PLX_PWM_prepareSetOutToXTransition(EpwmHandles[aHandle]);
}

// PWM Set Duty Cycle Function
        #pragma CODE_SECTION(PLXHAL_PWM_setDuty, "ramfuncs")
void PLXHAL_PWM_setDuty(uint16_t aHandle, float aDuty)
{
   PLX_PWM_setPwmDuty(EpwmHandles[aHandle], aDuty);
}

// PWM Set Dead Time Functions
        #pragma CODE_SECTION(PLXHAL_PWM_setRisingDelay, "ramfuncs")
void PLXHAL_PWM_setRisingDelay(uint16_t aChannel, float delay)
{
   PLX_PWM_setDeadTimeCountsRising(EpwmHandles[aChannel],
                                   delay * 1.000000e+08f);
}

        #pragma CODE_SECTION(PLXHAL_PWM_setFallingDelay, "ramfuncs")
void PLXHAL_PWM_setFallingDelay(uint16_t aChannel, float delay)
{
   PLX_PWM_setDeadTimeCountsFalling(EpwmHandles[aChannel],
                                    delay * 1.000000e+08f);
}

// PWM Set Sequence Functions
void PLXHAL_PWM_setSequence(uint16_t aChannel, uint16_t aSequence)
{
   PLX_PWM_setSequence(EpwmHandles[aChannel], aSequence);
}

void PLXHAL_PWM_setSequenceAq(uint16_t aChannel, uint32_t aSequenceAq)
{
   PLX_PWM_setSequenceAq(EpwmHandles[aChannel], aSequenceAq);
}

void PLXHAL_PWM_enableOutputSwap(uint16_t aChannel, bool aEnableSwap)
{
   PLX_PWM_enableOutputSwap(EpwmHandles[aChannel], aEnableSwap);
}
// Function for updating MEP using SFO
void PLXHAL_PWM_updateMEP()
{
   PLX_PWM_updateMEP();
}
    #pragma CODE_SECTION(PLXHAL_PWM_setDutyAB, "ramfuncs")
void PLXHAL_PWM_setDutyAB(uint16_t aHandle, float aDutyA, float aDutyB)
{
   PLX_PWM_setPwmDutyA(EpwmHandles[aHandle], aDutyA);
   PLX_PWM_setPwmDutyB(EpwmHandles[aHandle], aDutyB);
}

void PLXHAL_PWM_setOverflowSocDelay(uint16_t aHandle, float aPhase)
{
   PLX_PWM_setPwmDutyCGreaterThanZero(EpwmHandles[aHandle], 1.0f - aPhase);
}

void PLXHAL_PWM_setUnderflowSocDelay(uint16_t aHandle, float aPhase)
{
   PLX_PWM_setPwmDutyCSmallerThanFull(EpwmHandles[aHandle], aPhase);
}
PLX_PWM_Handle_t EpwmHandles[3];
PLX_PWM_Obj_t EpwmObj[3];
void PLXHAL_PWM_enableAllOutputs()
{
   PLX_PWM_enableOut(EpwmHandles[0]);
   PLX_PWM_enableOut(EpwmHandles[2]);
   PLX_PWM_enableOut(EpwmHandles[1]);
}
PLX_AIN_Handle_t AdcHandles[2];
PLX_AIN_Obj_t AdcObj[2];

float PLXHAL_ADC_getIn(uint16_t aHandle, uint16_t aChannel)
{
   return PLX_AIN_getInF(AdcHandles[aHandle], aChannel);
}
void PIL_setErrorMessage(PIL_Handle_t aPilHandle, const char* aMessage);
extern const char * PLECS_to_CCS_errorStatus;
extern PIL_Handle_t PilHandle;
DISPR_TaskObj_t TaskObj[1];
extern void PLECS_to_CCS_step();
extern void PLECS_to_CCS_enableTasksInterrupt();
extern void PLECS_to_CCS_syncTimers();
static void Tasks(bool aInit, void * const aParam)
{
   if(PLECS_to_CCS_errorStatus)
   {
      PIL_setErrorMessage(PilHandle, PLECS_to_CCS_errorStatus);
      return;
   }
   if(aInit)
   {
      PLECS_to_CCS_enableTasksInterrupt();
   }
   else
   {
      PLECS_to_CCS_step();
   }
}
interrupt void PLECS_to_CCS_baseTaskInterrupt(void)
{
   AdccRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;                  // clear ADCINT1 flag reinitialize for next SOC
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;  // acknowledge interrupt to PIE (All ADCS in group 1)
   IER |= M_INT1;

   DISPR_dispatch();
}


/* Interrupt Enable Code */
void PLECS_to_CCS_enableTasksInterrupt(void)
{
   IER |= M_INT1;

}

/* Timer Synchronization Code */
void PLECS_to_CCS_syncTimers(void)
{
   CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;        // start all the timers synced

}

/* Background task */
void PLECS_to_CCS_background(void)
{

}

/* HAL Initialization Code */
static bool HalInitialized = false;
void PLECS_to_CCS_initHal()
{

   if(HalInitialized == true)
   {
      return;
   }
   HalInitialized = true;

   // Pre init code
   SysCtl_disableWatchdog();
   {
      uint32_t sysPllConfig = PLX_DEVICE_SETCLOCK_CFG;
      DevInit(sysPllConfig);
      SysCtl_setLowSpeedClock(SYSCTL_LSPCLK_PRESCALE_4);
   }

   InitFlashHz(SYSCLK_HZ);

   // set cpu timers to same clock as ePWM
   CpuTimer0Regs.TPR.all = 0;
   CpuTimer1Regs.TPR.all = 0;
   CpuTimer2Regs.TPR.all = 0;
   EALLOW;
   CpuSysRegs.PCLKCR0.bit.CPUTIMER0 = 1;
   CpuSysRegs.PCLKCR0.bit.CPUTIMER1 = 1;
   CpuSysRegs.PCLKCR0.bit.CPUTIMER2 = 1;
   CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;  // stop all the TB clocks
   EDIS;
   {
      // early system configuration
      PLX_DIO_sinit();
   }
   // setup analog voltage references
   {
      SetVREF(ADC_ADCA, ADC_INTERNAL, ADC_VREF3P3);
      SetVREF(ADC_ADCC, ADC_INTERNAL, ADC_VREF3P3);
      SetVREF(ADC_ADCB, ADC_INTERNAL, ADC_VREF3P3);
   }
   PLX_PWM_sinit();
   for (int i = 0; i < 3; i++)
   {
      EpwmHandles[i] = PLX_PWM_init(&EpwmObj[i], sizeof(EpwmObj[i]));
   }
   // configure PWM1 at 50000.0 Hz in triangle mode
   // soc='p'
   {
      PLX_PWM_Params_t params;
      PLX_PWM_setDefaultParams(&params);
      params.outMode = PLX_PWM_OUTPUT_MODE_DUAL;
      params.reg.TBPRD = 1000;
      params.reg.TBCTL.bit.CTRMODE = 2;
      params.reg.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;
      // active state is high
      params.reg.DBCTL.bit.POLSEL = 2; // DB_ACTV_HIC
      // enable deadtime insertion
      params.reg.DBCTL.bit.OUT_MODE = 3; // DB_FULL_ENABLE
      params.reg.DBCTL.bit.IN_MODE = 0; // DBA_ALL
      // TZ settings
      params.reg.TZSEL.bit.CBC1 = 0;
      params.reg.TZSEL.bit.OSHT1 = 0;
      params.reg.TZSEL.bit.CBC2 = 0;
      params.reg.TZSEL.bit.OSHT2 = 0;
      params.reg.TZSEL.bit.CBC3 = 0;
      params.reg.TZSEL.bit.OSHT3 = 0;
      PLX_PWM_configure(EpwmHandles[0], 1, &params);
      // configure deadtime to 3.000000e-07/3.000000e-07 seconds (rising/falling)
      PLX_PWM_setDeadTimeCounts(EpwmHandles[0], 30.000000, 30.000000);
      // PWM sequence starting with active state
      PLX_PWM_setSequence(EpwmHandles[0], 1);
      EPwm1Regs.ETSEL.bit.SOCASEL = 2;
      EPwm1Regs.ETPS.bit.SOCPSSEL = 1;
      EPwm1Regs.ETSOCPS.bit.SOCAPRD2 = 1;
      EPwm1Regs.ETSEL.bit.SOCAEN = 1;
   }
   // configure PWM2 at 50000.0 Hz in triangle mode
   //
   {
      PLX_PWM_Params_t params;
      PLX_PWM_setDefaultParams(&params);
      params.outMode = PLX_PWM_OUTPUT_MODE_DUAL;
      params.reg.TBPRD = 1000;
      params.reg.TBCTL.bit.CTRMODE = 2;
      params.reg.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;
      // active state is high
      params.reg.DBCTL.bit.POLSEL = 2; // DB_ACTV_HIC
      // enable deadtime insertion
      params.reg.DBCTL.bit.OUT_MODE = 3; // DB_FULL_ENABLE
      params.reg.DBCTL.bit.IN_MODE = 0; // DBA_ALL
      // TZ settings
      params.reg.TZSEL.bit.CBC1 = 0;
      params.reg.TZSEL.bit.OSHT1 = 0;
      params.reg.TZSEL.bit.CBC2 = 0;
      params.reg.TZSEL.bit.OSHT2 = 0;
      params.reg.TZSEL.bit.CBC3 = 0;
      params.reg.TZSEL.bit.OSHT3 = 0;
      PLX_PWM_configure(EpwmHandles[2], 2, &params);
      // configure deadtime to 3.000000e-07/3.000000e-07 seconds (rising/falling)
      PLX_PWM_setDeadTimeCounts(EpwmHandles[2], 30.000000, 30.000000);
      // PWM sequence starting with active state
      PLX_PWM_setSequence(EpwmHandles[2], 1);

   }
   // configure PWM4 at 50000.0 Hz in triangle mode
   //
   {
      PLX_PWM_Params_t params;
      PLX_PWM_setDefaultParams(&params);
      params.outMode = PLX_PWM_OUTPUT_MODE_DUAL;
      params.reg.TBPRD = 1000;
      params.reg.TBCTL.bit.CTRMODE = 2;
      params.reg.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;
      // active state is high
      params.reg.DBCTL.bit.POLSEL = 2; // DB_ACTV_HIC
      // enable deadtime insertion
      params.reg.DBCTL.bit.OUT_MODE = 3; // DB_FULL_ENABLE
      params.reg.DBCTL.bit.IN_MODE = 0; // DBA_ALL
      // TZ settings
      params.reg.TZSEL.bit.CBC1 = 0;
      params.reg.TZSEL.bit.OSHT1 = 0;
      params.reg.TZSEL.bit.CBC2 = 0;
      params.reg.TZSEL.bit.OSHT2 = 0;
      params.reg.TZSEL.bit.CBC3 = 0;
      params.reg.TZSEL.bit.OSHT3 = 0;
      PLX_PWM_configure(EpwmHandles[1], 4, &params);
      // configure deadtime to 3.000000e-07/3.000000e-07 seconds (rising/falling)
      PLX_PWM_setDeadTimeCounts(EpwmHandles[1], 30.000000, 30.000000);
      // PWM sequence starting with active state
      PLX_PWM_setSequence(EpwmHandles[1], 1);

   }
   {
      PLX_AIN_sinit(100000000);

      for (int i = 0; i < 2; i++)
      {
         AdcHandles[i] = PLX_AIN_init(&AdcObj[i], sizeof(AdcObj[i]));
      }
   }
   // configure ADC B
   {
      PLX_AIN_AdcParams_t params;
      PLX_AIN_setDefaultAdcParams(&params, 3.300000, 0);
      PLX_AIN_configure(AdcHandles[1], (PLX_AIN_Unit_t)1, &params);
   }
   // configure SOC0 of ADC-B to measure ADCIN0
   {
      PLX_AIN_ChannelParams_t params;
      PLX_AIN_setDefaultChannelParams(&params);
      params.scale =  1.000000000e+00f;
      params.offset = 0.000000000e+00f;
      // set SOC trigger to PWM1
      params.ADCSOCxCTL.bit.TRIGSEL = 5;
      params.ADCSOCxCTL.bit.ACQPS = 50;
      PLX_AIN_setupChannel(AdcHandles[1], 0, 0, &params);
   }
   // configure SOC1 of ADC-B to measure ADCIN1
   {
      PLX_AIN_ChannelParams_t params;
      PLX_AIN_setDefaultChannelParams(&params);
      params.scale =  1.000000000e+00f;
      params.offset = 0.000000000e+00f;
      // set SOC trigger to PWM1
      params.ADCSOCxCTL.bit.TRIGSEL = 5;
      params.ADCSOCxCTL.bit.ACQPS = 50;
      PLX_AIN_setupChannel(AdcHandles[1], 1, 1, &params);
   }
   // configure SOC2 of ADC-B to measure ADCIN2
   {
      PLX_AIN_ChannelParams_t params;
      PLX_AIN_setDefaultChannelParams(&params);
      params.scale =  1.000000000e+00f;
      params.offset = 0.000000000e+00f;
      // set SOC trigger to PWM1
      params.ADCSOCxCTL.bit.TRIGSEL = 5;
      params.ADCSOCxCTL.bit.ACQPS = 50;
      PLX_AIN_setupChannel(AdcHandles[1], 2, 2, &params);
   }
   // configure ADC C
   {
      PLX_AIN_AdcParams_t params;
      PLX_AIN_setDefaultAdcParams(&params, 3.300000, 0);
      PLX_AIN_configure(AdcHandles[0], (PLX_AIN_Unit_t)2, &params);
   }
   // configure SOC0 of ADC-C to measure ADCIN1
   {
      PLX_AIN_ChannelParams_t params;
      PLX_AIN_setDefaultChannelParams(&params);
      params.scale =  1.000000000e+00f;
      params.offset = 0.000000000e+00f;
      // set SOC trigger to PWM1
      params.ADCSOCxCTL.bit.TRIGSEL = 5;
      params.ADCSOCxCTL.bit.ACQPS = 50;
      PLX_AIN_setupChannel(AdcHandles[0], 0, 1, &params);
   }
   // configure SOC1 of ADC-C to measure ADCIN3
   {
      PLX_AIN_ChannelParams_t params;
      PLX_AIN_setDefaultChannelParams(&params);
      params.scale =  1.000000000e+00f;
      params.offset = 0.000000000e+00f;
      // set SOC trigger to PWM1
      params.ADCSOCxCTL.bit.TRIGSEL = 5;
      params.ADCSOCxCTL.bit.ACQPS = 50;
      PLX_AIN_setupChannel(AdcHandles[0], 1, 3, &params);
   }
   // configure SOC2 of ADC-C to measure ADCIN5
   {
      PLX_AIN_ChannelParams_t params;
      PLX_AIN_setDefaultChannelParams(&params);
      params.scale =  1.000000000e+00f;
      params.offset = 0.000000000e+00f;
      // set SOC trigger to PWM1
      params.ADCSOCxCTL.bit.TRIGSEL = 5;
      params.ADCSOCxCTL.bit.ACQPS = 50;
      PLX_AIN_setupChannel(AdcHandles[0], 2, 5, &params);
   }
   DISPR_sinit();
   DISPR_configure((uint32_t)(2000), PilHandle, &TaskObj[0],
                   sizeof(TaskObj)/sizeof(DISPR_TaskObj_t));
   DISPR_registerIdleTask(&PLECS_to_CCS_background);
   DISPR_registerSyncCallback(&PLECS_to_CCS_syncTimers);
   DISPR_setPowerupDelay(50);
   {
      static int taskId = 0;
      // Task 0 at 5.000000e+04 Hz
      DISPR_registerTask(0, &Tasks, 2000L, (void *)&taskId);
   }
   EALLOW;
   AdccRegs.ADCINTSEL1N2.bit.INT1CONT = 0;  // disable ADCINT1 Continuous mode
   AdccRegs.ADCINTSEL1N2.bit.INT1SEL = 2;  // setup EOC2 to trigger ADCINT1
   AdccRegs.ADCINTSEL1N2.bit.INT1E = 1;  // enable ADCINT1
   AdccRegs.ADCCTL1.bit.INTPULSEPOS = 1;  // ADCINT1 trips after AdcResults latch
   EDIS;
   EALLOW;
   *(PINT *)((uint32_t)(&PieVectTable.ADCA1_INT) + ((uint32_t)2)*
             sizeof(PINT *)) = &PLECS_to_CCS_baseTaskInterrupt;
   PieCtrlRegs.PIEIER1.all |= 4;
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
   EDIS;


   // Post init code (for modules that depend on other modules)
   {
      // late system configuration
      GPIO_setPinConfig(GPIO_0_EPWM1_A);
      GPIO_setPinConfig(GPIO_1_EPWM1_B);
      GPIO_setPinConfig(GPIO_6_EPWM4_A);
      GPIO_setPinConfig(GPIO_7_EPWM4_B);
      GPIO_setPinConfig(GPIO_2_EPWM2_A);
      GPIO_setPinConfig(GPIO_3_EPWM2_B);
   }


   // If applicable, boot secondary core(s)

}
