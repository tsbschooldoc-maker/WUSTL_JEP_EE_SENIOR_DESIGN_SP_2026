/*
   Copyright (c) 2014-2023 by Plexim GmbH
   All rights reserved.

   A free license is granted to anyone to use this software for any legal
   non safety-critical purpose, including commercial applications, provided
   that:
   1) IT IS NOT USED TO DIRECTLY OR INDIRECTLY COMPETE WITH PLEXIM, and
   2) THIS COPYRIGHT NOTICE IS PRESERVED in its entirety.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
 */

#ifndef PLX_EPWM_TYPE4_H_
#define PLX_EPWM_TYPE4_H_

#include "sysctl.h"
#include "inc/hw_memmap.h"
#include "math.h"

#ifndef TARGET_29h85x
typedef struct PLX_PWM_REG_PARAMS {
  uint16_t TBPRD;
  uint16_t TBPRDHR;
  union TBPHS_REG TBPHS;
  union TBCTL_REG TBCTL;
  union CMPCTL_REG CMPCTL;
  union AQCTLA_REG AQCTLA;
  union DBCTL_REG DBCTL;
  union DBFED_REG DBFED;
  union DBRED_REG DBRED;
  union TZCTL_REG TZCTL;
  union ETSEL_REG ETSEL;
  union TZSEL_REG TZSEL;
  union ETSOCPS_REG ETSOCPS;
  union HRCNFG_REG HRCNFG;
  union HRCNFG2_REG HRCNFG2;
  union HRPCTL_REG HRPCTL;
} PLX_PWM_RegParams_t;
#endif

typedef enum PLX_PWM_OUTPUT_MODE {
  PLX_PWM_OUTPUT_MODE_DUAL = 0,
  PLX_PWM_OUTPUT_MODE_SINGLE,
  PLX_PWM_OUTPUT_MODE_DISABLED
} PLX_PWM_OutputMode_t;

typedef struct PLX_PWM_PARAMS {
  PLX_PWM_RegParams_t reg;
  PLX_PWM_OutputMode_t outMode;
  bool highResDutyEnabled;
  bool highResPeriodEnabled;
  bool highResDeadTimeEnabled;
} PLX_PWM_Params_t;

typedef struct PLX_PWM_OBJ {
  uint16_t *cmprProbe;
  volatile struct EPWM_REGS *pwm;
  uint16_t nomTBPRD;
  uint16_t sequence;
  bool highResDutyEnabled;
  bool highResPeriodEnabled;
  bool highResDeadTimeEnabled;
} PLX_PWM_Obj_t;

typedef struct PLX_HRPWM_SOBJ {
  volatile uint16_t status; // MEP Status
} PLX_HRPWM_SObj_t;

typedef PLX_PWM_Obj_t *PLX_PWM_Handle_t;

extern void PLX_PWM_getRegisterBase(PLX_PWM_Unit_t aPwmChannel,
                                    volatile struct EPWM_REGS **aReg);

#pragma CODE_SECTION(PLX_PWM_getFullDutyCompare, "ramfuncs")
static inline uint32_t PLX_PWM_getFullDutyCompare(PLX_PWM_Handle_t aHandle) {
  PLX_PWM_Obj_t *obj = (PLX_PWM_Obj_t *)aHandle;
  if (obj->pwm->TBCTL.bit.CTRMODE == TB_COUNT_UPDOWN) {
    // up-down
    return obj->pwm->TBPRD;
  } else {
    // sawtooth
    return (uint32_t)obj->pwm->TBPRD + 1;
  }
}

#pragma CODE_SECTION(PLX_PWM_getHighResPeriod, "ramfuncs")
static inline uint32_t PLX_PWM_getHighResPeriod(PLX_PWM_Handle_t aHandle) {
  PLX_PWM_Obj_t *obj = (PLX_PWM_Obj_t *)aHandle;
  return (uint32_t)obj->pwm->TBPRDHR >> 8;
}

static inline uint32_t PLX_PWM_getCounter(PLX_PWM_Handle_t aHandle) {
  PLX_PWM_Obj_t *obj = (PLX_PWM_Obj_t *)aHandle;
  return obj->pwm->TBCTR;
}

static inline bool PLX_PWM_getCountDirection(PLX_PWM_Handle_t aHandle) {
  PLX_PWM_Obj_t *obj = (PLX_PWM_Obj_t *)aHandle;
  return obj->pwm->TBSTS.bit.CTRDIR;
}

static inline void PLX_PWM_enableOut(PLX_PWM_Handle_t aHandle) {
  PLX_PWM_Obj_t *obj = (PLX_PWM_Obj_t *)aHandle;
  EALLOW;
  obj->pwm->TZCLR.bit.OST = 1;
  obj->pwm->TZCLR.bit.OST = 1; // defensive silicon advisory workaround
  EDIS;
}

static inline bool PLX_PWM_pwmOutputIsEnabled(PLX_PWM_Handle_t aHandle) {
  PLX_PWM_Obj_t *obj = (PLX_PWM_Obj_t *)aHandle;
  return (obj->pwm->TZFLG.bit.OST == 0);
}

static inline void PLX_PWM_disableOut(PLX_PWM_Handle_t aHandle) {
  PLX_PWM_Obj_t *obj = (PLX_PWM_Obj_t *)aHandle;
  EALLOW;
  obj->pwm->TZFRC.bit.OST = 1;
  obj->pwm->TZFRC.bit.OST = 1; // defensive silicon advisory workaround
  EDIS;
}

static inline void PLX_PWM_setTZSafe(PLX_PWM_Handle_t aHandle, uint16_t aSafe) {
  PLX_PWM_Obj_t *obj = (PLX_PWM_Obj_t *)aHandle;
  obj->pwm->TZCTL.bit.TZA = aSafe;
  obj->pwm->TZCTL.bit.TZB = aSafe;
}

#pragma CODE_SECTION(PLX_PWM_setDeadTimeCounts, "ramfuncs")
static inline void PLX_PWM_setDeadTimeCounts(PLX_PWM_Handle_t aHandle,
                                      float aRisingEdgeDelayCounts,
                                      float aFallingEdgeDelayCounts) {
  PLX_PWM_Obj_t *obj = (PLX_PWM_Obj_t *)aHandle;

  if (obj->highResDeadTimeEnabled) {
    const float maxDeadTime = 8192.0f;

    float clampedRising = fminf(maxDeadTime, aRisingEdgeDelayCounts);
    float clampedFalling = fminf(maxDeadTime, aFallingEdgeDelayCounts);

    // Convert to fixed-point with 7 fractional bits
    // * 128 (7 fractional bits) * 2 (half cycle clocking mode)
    uint32_t risingFixedPoint = (uint32_t)((clampedRising * 256.0f) + 0.5f);
    uint32_t fallingFixedPoint = (uint32_t)((clampedFalling * 256.0f) + 0.5f);

    // Clamp fixed-point values to maximum representable in registers
    // Max: (16383 << 7) | 127 = 2,097,151
    const uint32_t maxFixedPoint = 0x1FFFFF;  // 21 bits = 2,097,151
    if (risingFixedPoint > maxFixedPoint) {
      risingFixedPoint = maxFixedPoint;
    }
    if (fallingFixedPoint > maxFixedPoint) {
      fallingFixedPoint = maxFixedPoint;
    }

    obj->pwm->DBRED.bit.DBRED = risingFixedPoint >> 7;
    obj->pwm->DBREDHR.bit.DBREDHR = risingFixedPoint & 0x7F;
    obj->pwm->DBFED.bit.DBFED = fallingFixedPoint >> 7;
    obj->pwm->DBFEDHR.bit.DBFEDHR = fallingFixedPoint & 0x7F;
  } else {
    const float maxDeadTime = 16383.0f;

    float clampedRising = fminf(maxDeadTime, aRisingEdgeDelayCounts);
    float clampedFalling = fminf(maxDeadTime, aFallingEdgeDelayCounts);

    obj->pwm->DBFED.bit.DBFED = (uint16_t)(clampedFalling + 0.5f);
    obj->pwm->DBRED.bit.DBRED = (uint16_t)(clampedRising + 0.5f);
  }
}

#pragma CODE_SECTION(PLX_PWM_setDeadTimeCountsRising, "ramfuncs")
static inline void PLX_PWM_setDeadTimeCountsRising(PLX_PWM_Handle_t aHandle,
                                            float aRisingEdgeDelayCounts) {
  PLX_PWM_Obj_t *obj = (PLX_PWM_Obj_t *)aHandle;

  if (obj->highResDeadTimeEnabled) {
      const float maxDeadTime = 8192.0f;

      float clampedRising = fminf(maxDeadTime, aRisingEdgeDelayCounts);

      // Convert to fixed-point with 7 fractional bits
      // * 128 (7 fractional bits) * 2 (half cycle clocking mode)
      uint32_t risingFixedPoint = (uint32_t)((clampedRising * 256.0f) + 0.5f);

      // Clamp fixed-point values to maximum representable in registers
      // Max: (16383 << 7) | 127 = 2,097,151
      const uint32_t maxFixedPoint = 0x1FFFFF;  // 21 bits = 2,097,151
      if (risingFixedPoint > maxFixedPoint) {
        risingFixedPoint = maxFixedPoint;
      }

      obj->pwm->DBRED.bit.DBRED = risingFixedPoint >> 7;
      obj->pwm->DBREDHR.bit.DBREDHR = risingFixedPoint & 0x7F;
  } else {
    const float maxDeadTime = 16383.0f;

    float clampedRising = fminf(maxDeadTime, aRisingEdgeDelayCounts);

    obj->pwm->DBRED.bit.DBRED = (uint16_t)(clampedRising + 0.5f);
  }
}

#pragma CODE_SECTION(PLX_PWM_setDeadTimeCountsFalling, "ramfuncs")
static inline void PLX_PWM_setDeadTimeCountsFalling(PLX_PWM_Handle_t aHandle,
                                             float aFallingEdgeDelayCounts) {
  PLX_PWM_Obj_t *obj = (PLX_PWM_Obj_t *)aHandle;

  if (obj->highResDeadTimeEnabled) {
    const float maxDeadTime = 8192.0f;

    float clampedFalling = fminf(maxDeadTime, aFallingEdgeDelayCounts);

    // Convert to fixed-point with 7 fractional bits
    // * 128 (7 fractional bits) * 2 (half cycle clocking mode)
    uint32_t fallingFixedPoint = (uint32_t)((clampedFalling * 256.0f) + 0.5f);

    // Clamp fixed-point values to maximum representable in registers
    // Max: (16383 << 7) | 127 = 2,097,151
    const uint32_t maxFixedPoint = 0x1FFFFF;  // 21 bits = 2,097,151
    if (fallingFixedPoint > maxFixedPoint) {
      fallingFixedPoint = maxFixedPoint;
    }

    obj->pwm->DBFED.bit.DBFED = fallingFixedPoint >> 7;
    obj->pwm->DBFEDHR.bit.DBFEDHR = fallingFixedPoint & 0x7F;
  } else {
    const float maxDeadTime = 16383.0f;

    float clampedFalling = fminf(maxDeadTime, aFallingEdgeDelayCounts);

    obj->pwm->DBFED.bit.DBFED = (uint16_t)(aFallingEdgeDelayCounts + 0.5f);
  }
}

static inline void PLX_PWM_setOutToPassive(PLX_PWM_Handle_t aHandle) {
  PLX_PWM_Obj_t *obj = (PLX_PWM_Obj_t *)aHandle;

  // force 'EPWMxA in' and 'EPWMxB in'
  if (obj->pwm->DBCTL.bit.POLSEL == 1) {
    // DB_ACTV_LOC
    obj->pwm->AQCSFRC.bit.CSFA = 2;  // force high
    obj->pwm->AQCSFRC.bit.CSFB = 2;  // force high
  } else {
    // DB_ACTV_HIC
    obj->pwm->AQCSFRC.bit.CSFA = 1;  // force low
    obj->pwm->AQCSFRC.bit.CSFB = 1;  // force low
  }
  // bypass dead-band submodule
  obj->pwm->DBCTL.bit.OUT_MODE = 0x0;
}

static inline void PLX_PWM_setOutToOperational(PLX_PWM_Handle_t aHandle) {
  PLX_PWM_Obj_t *obj = (PLX_PWM_Obj_t *)aHandle;
  obj->pwm->DBCTL.bit.OUT_MODE = 0x3;  // enable dead-band submodule
  // disable forcing of 'EPWMxA in' and 'EPWMxB in'
  obj->pwm->AQCSFRC.bit.CSFA = 0;
  obj->pwm->AQCSFRC.bit.CSFB = 0;
}

static inline void PLX_PWM_prepareSetOutToXTransition(PLX_PWM_Handle_t aHandle) {
  PLX_PWM_Obj_t *obj = (PLX_PWM_Obj_t *)aHandle;

  // Configure shadowing to allow synchronized disabling of leg
  // through force and deadband control.
  if (obj->pwm->TBCTL.bit.CTRMODE == TB_COUNT_UP) {  // Sawtooth carrier
    obj->pwm->AQSFRC.bit.RLDCSF = 1;                 // load at period
    obj->pwm->DBCTL2.bit.LOADDBCTLMODE = 0;          // load at zero
  } else {                                           // Symmetrical carrier
    // Check polarity and sequence (odd=negative, even=positive)
    // with xor operation
    if ((obj->pwm->DBCTL.bit.POLSEL == 2) != ((obj->sequence & 0x01) == 0)) {
      // positive polarity & positive sequence
      // OR negative polarity & negative sequence
      obj->pwm->AQSFRC.bit.RLDCSF = 1;         // load at period
      obj->pwm->DBCTL2.bit.LOADDBCTLMODE = 1;  // load at period
    } else {
      // positive polarity & negative sequence
      // OR negative polarity & positive sequence
      obj->pwm->AQSFRC.bit.RLDCSF = 0;         // load at zero
      obj->pwm->DBCTL2.bit.LOADDBCTLMODE = 0;  // load at zero
    }
  }
}

static inline void PLX_PWM_setSequenceAq(PLX_PWM_Handle_t aHandle,
                                  uint32_t aSequenceAq) {
  PLX_PWM_Obj_t *obj = (PLX_PWM_Obj_t *)aHandle;

  // this function allows setting the AQ actions directly from a sequence mask -
  // note that AQCTLA/A2 and AQCTLB/B2 are configured identically, with the
  // exception of the CMP events - for those, we assign the CAs to AQCTLA and
  // the CBs to AQCTLB
  obj->pwm->AQCTLA.all = aSequenceAq & 0xFF;           // [CAD CAU PRD ZRO]
  obj->pwm->AQCTLA2.all = (aSequenceAq >> 16) & 0xFF;  // [T2D T2U T1D T1U]

  obj->pwm->AQCTLB.all = (aSequenceAq & 0x0F)
                         | (aSequenceAq & 0xF00);  // [CBD CBU X X PRD ZRO]
  obj->pwm->AQCTLB2.all = obj->pwm->AQCTLA2.all;   // [T2D T2U T1D T1U]

  obj->sequence = 1;  // ensures that the duty cycle is not inverted
}

static inline void PLX_PWM_setSequence(PLX_PWM_Handle_t aHandle, uint16_t aSequence) {
  PLX_PWM_Obj_t *obj = (PLX_PWM_Obj_t *)aHandle;

  obj->sequence = aSequence & 1;
  uint16_t zeroTransition, firstCompareTransition;

  if (obj->sequence == 0) {
    // negative sequence
    zeroTransition = 1;          // clear
    firstCompareTransition = 2;  // set
  } else {
    // positive sequence
    zeroTransition = 2;          // set
    firstCompareTransition = 1;  // clear
  }

  // configure channel A compare events
  obj->pwm->AQCTLA.bit.CAU = firstCompareTransition;
  obj->pwm->AQCTLA.bit.CAD = zeroTransition;  // only relevant for
                                              // symmetrical carrier

  // configure channel A zero and period events
  obj->pwm->AQCTLA.bit.ZRO = zeroTransition;
  if (obj->pwm->TBCTL.bit.CTRMODE != TB_COUNT_UP) {
    // only force period for symmetrical carrier
    obj->pwm->AQCTLA.bit.PRD = firstCompareTransition;
  } else {
    // HR period in upcount mode requires unique sequence (set on PRD)
    if (obj->pwm->HRPCTL.bit.HRPE == 1) {
        obj->pwm->AQCTLA.bit.PRD = zeroTransition;
        obj->pwm->AQCTLA.bit.ZRO = 0;
    } else {
        obj->pwm->AQCTLA.bit.PRD = 0;
    }
  }

  // channel B has equivalent actions as channel A
  obj->pwm->AQCTLB.bit.CBU = obj->pwm->AQCTLA.bit.CAU;
  obj->pwm->AQCTLB.bit.CBD = obj->pwm->AQCTLA.bit.CAD;
  obj->pwm->AQCTLB.bit.ZRO = obj->pwm->AQCTLA.bit.ZRO;
  obj->pwm->AQCTLB.bit.PRD = obj->pwm->AQCTLA.bit.PRD;
}

#pragma CODE_SECTION(PLX_PWM_calcCompareValue, "ramfuncs")
static inline uint16_t PLX_PWM_calcCompareValue(PLX_PWM_Handle_t aHandle,
                                         float aDuty) {
  PLX_PWM_Obj_t *obj = (PLX_PWM_Obj_t *)aHandle;
  float duty = aDuty;

  if (duty > 1.0) {
    duty = 1.0;
  } else if (duty < 0.0) {
    duty = 0.0;
  }

  if (obj->sequence == 0) {
    duty = 1.0 - duty;
  }

  float cmpF = duty * (float)PLX_PWM_getFullDutyCompare(aHandle);
  uint16_t cmpI = (uint16_t)(cmpF + 0.5f);

  if (cmpI > 65535) {
    cmpI = 65535;
  }

  // HR period in upcount mode requires shifted compare value for different AQ
  if ((obj->pwm->HRPCTL.bit.HRPE == 1) && (obj->pwm->TBCTL.bit.CTRMODE == TB_COUNT_UP)) {
      // But if a user commands 0 duty, set cmpF to 0 so shutoff is relatively immediate instead of always on
      if (cmpI == 0) {
        return 0;
      } else {
        return cmpI - 1; // subtract 1 for sequence
      }
  }

  return cmpI;
}

#pragma CODE_SECTION(PLX_PWM_calcHighResCompareValue, "ramfuncs")
static inline uint32_t PLX_PWM_calcHighResCompareValue(PLX_PWM_Handle_t aHandle,
                                           float aDuty) {
  PLX_PWM_Obj_t *obj = (PLX_PWM_Obj_t *)aHandle;
  float duty = aDuty;

  if (duty > 1.0) {
      duty = 1.0;
  } else if (duty < 0.0) {
     duty = 0.0;
  }

  if (obj->sequence == 0) {
      duty = 1.0 - duty;
  }

  // Get the base period
  uint32_t TBPRD = PLX_PWM_getFullDutyCompare(aHandle);
  uint32_t TBPRD_effective_Q15;

  // Add on HR component if high resolution period is used
  if (obj->highResPeriodEnabled) {
      uint32_t TBPRDHR = PLX_PWM_getHighResPeriod(aHandle);

      uint32_t TBPRD_base_Q15 = TBPRD * 32768;

      uint32_t TBPRDHR_Q15_addition = TBPRDHR * 128;

      TBPRD_effective_Q15 = TBPRD_base_Q15 + TBPRDHR_Q15_addition;
  } else {
      TBPRD_effective_Q15 = TBPRD * 32768;
  }

  // Get fullCompare in Q15 with fixed point math
  uint32_t fullCompare = (uint32_t)(duty * TBPRD_effective_Q15);

  // Adjust for up/down count mode, which uses an additive/subtractive approach to HR
  if (obj->pwm->TBCTL.bit.CTRMODE == TB_COUNT_UPDOWN) {
      fullCompare += 16383;
  }

  // Extract low-res and high-res components
  uint16_t dutyLowRes = fullCompare >> 15;
  uint16_t highResTicks = (fullCompare & 0x7FFF) >> 7;

  // Special case for HRPE in up-count mode
  if (obj->highResPeriodEnabled && obj->pwm->TBCTL.bit.CTRMODE == TB_COUNT_UP) {
      // 0 duty is unachievable so get as close as possible
      if (dutyLowRes == 0) {
          highResTicks = 0;
      // ... but otherwise we need to adjust due to the different sequence
      } else {
          dutyLowRes -= 1;
      }
  }

  // HighResTick value of 0 with triangle carrier doesn't behave properly (change to 1)
  if (highResTicks == 0 && obj->pwm->TBCTL.bit.CTRMODE == TB_COUNT_UPDOWN) {
      highResTicks = 1;
  }

  // Combine and return the final value
  return ((uint32_t)dutyLowRes) << 16 | ((uint32_t)highResTicks << 8);
}

static inline void PLX_PWM_setPwmDutyCSmallerThanFull(PLX_PWM_Handle_t aHandle,
                                               float aDuty) {
  PLX_PWM_Obj_t *obj = (PLX_PWM_Obj_t *)aHandle;
  uint16_t cmp = PLX_PWM_calcCompareValue(aHandle, aDuty);
  if (cmp >= PLX_PWM_getFullDutyCompare(aHandle)) {
    cmp = PLX_PWM_getFullDutyCompare(aHandle) - 1;
  }
  obj->pwm->CMPC = cmp;
}

static inline void PLX_PWM_setPwmDutyCGreaterThanZero(PLX_PWM_Handle_t aHandle,
                                               float aDuty) {
  PLX_PWM_Obj_t *obj = (PLX_PWM_Obj_t *)aHandle;
  uint16_t cmp = PLX_PWM_calcCompareValue(aHandle, aDuty);
  if (cmp < 1) {
    cmp = 1;
  }
  obj->pwm->CMPC = cmp;
}

#pragma CODE_SECTION(PLX_PWM_setPwmDutyA, "ramfuncs")
static inline void PLX_PWM_setPwmDutyA(PLX_PWM_Handle_t aHandle, float aDuty) {
  PLX_PWM_Obj_t *obj = (PLX_PWM_Obj_t *)aHandle;
  if (obj->highResDutyEnabled) {
    obj->pwm->CMPA.all = PLX_PWM_calcHighResCompareValue(aHandle, aDuty);
  } else {
    obj->pwm->CMPA.bit.CMPA = PLX_PWM_calcCompareValue(aHandle, aDuty);
    // If high resolution period is enabled (in symmetrical mode)
    // HR compare component must be set to 128 for "0"
    if ((obj->highResPeriodEnabled) && (obj->pwm->TBCTL.bit.CTRMODE == TB_COUNT_UPDOWN)) {
      obj->pwm->CMPA.bit.CMPAHR = (uint16_t)(128 << 8);
    }
  }
}

#pragma CODE_SECTION(PLX_PWM_setPwmDutyB, "ramfuncs")
static inline void PLX_PWM_setPwmDutyB(PLX_PWM_Handle_t aHandle, float aDuty) {
  PLX_PWM_Obj_t *obj = (PLX_PWM_Obj_t *)aHandle;
  if (obj->highResDutyEnabled) {
    obj->pwm->CMPB.all = PLX_PWM_calcHighResCompareValue(aHandle, aDuty);
  } else {
    obj->pwm->CMPB.bit.CMPB = PLX_PWM_calcCompareValue(aHandle, aDuty);
    // If high resolution period is enabled (in symmetrical mode)
    // HR compare component must be set to 128 for "0"
    if ((obj->highResPeriodEnabled) && (obj->pwm->TBCTL.bit.CTRMODE == TB_COUNT_UPDOWN)) {
      obj->pwm->CMPB.bit.CMPBHR = (uint16_t)(128 << 8);
    }
  }
}

#pragma CODE_SECTION(PLX_PWM_setPwmDuty, "ramfuncs")
static inline void PLX_PWM_setPwmDuty(PLX_PWM_Handle_t aHandle, float aDuty) {
  PLX_PWM_Obj_t *obj = (PLX_PWM_Obj_t *)aHandle;

  if (obj->highResDutyEnabled) {
    uint32_t compareVal = PLX_PWM_calcHighResCompareValue(aHandle, aDuty);
    obj->pwm->CMPA.all = compareVal;
    obj->pwm->CMPB.all = compareVal;
  } else {
    obj->pwm->CMPA.bit.CMPA = PLX_PWM_calcCompareValue(aHandle, aDuty);
    // If high resolution period is enabled (in symmetrical mode)
    // HR compare component must be set to 128 for "0"
    if ((obj->highResPeriodEnabled) && (obj->pwm->TBCTL.bit.CTRMODE == TB_COUNT_UPDOWN)) {
      obj->pwm->CMPA.bit.CMPAHR = (uint16_t)(128 << 8);
    }
  }
}

static inline void PLX_PWM_enableOutputSwap(PLX_PWM_Handle_t aHandle, bool aEnableSwap) {
  PLX_PWM_Obj_t *obj = (PLX_PWM_Obj_t *)aHandle;
  if(aEnableSwap){
    obj->pwm->DBCTL.bit.OUTSWAP = 3;
  } else {
    obj->pwm->DBCTL.bit.OUTSWAP = 0;
  }
}

static inline void PLX_PWM_enableAllClocks() {
#ifdef EPWM1_BASE
  SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1);
#endif
#ifdef EPWM2_BASE
  SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM2);
#endif
#ifdef EPWM3_BASE
  SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM3);
#endif
#ifdef EPWM4_BASE
  SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM4);
#endif
#ifdef EPWM5_BASE
  SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM5);
#endif
#ifdef EPWM6_BASE
  SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM6);
#endif
#ifdef EPWM7_BASE
  SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM7);
#endif
#ifdef EPWM8_BASE
  SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM8);
#endif
#ifdef EPWM9_BASE
  SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM9);
#endif
#ifdef EPWM10_BASE
  SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM10);
#endif
#ifdef EPWM11_BASE
  SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM11);
#endif
#ifdef EPWM12_BASE
  SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM12);
#endif
#ifdef EPWM13_BASE
  SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM13);
#endif
#ifdef EPWM14_BASE
  SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM14);
#endif
#ifdef EPWM15_BASE
  SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM15);
#endif
#ifdef EPWM16_BASE
  SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM16);
#endif
#ifdef EPWM17_BASE
  SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM17);
#endif
#ifdef EPWM18_BASE
  SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM18);
#endif
#if defined(TARGET_28p65x) || defined(TARGET_29h85x)
  SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_HRCAL0);
  SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_HRCAL1);
  SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_HRCAL2);
#elif defined(TARGET_28p55x) || defined(TARGET_28003x) || defined(TARGET_2838x)
  SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_HRCAL);
#elif defined(TARGET_28004x) || defined(TARGET_2837x)
  SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_HRPWM);
#else
  PLX_ASSERT(0);
#endif
}

static inline void PLX_PWM_disableAllClocks() {
#ifdef EPWM1_BASE
  SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_EPWM1);
#endif
#ifdef EPWM2_BASE
  SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_EPWM2);
#endif
#ifdef EPWM3_BASE
  SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_EPWM3);
#endif
#ifdef EPWM4_BASE
  SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_EPWM4);
#endif
#ifdef EPWM5_BASE
  SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_EPWM5);
#endif
#ifdef EPWM6_BASE
  SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_EPWM6);
#endif
#ifdef EPWM7_BASE
  SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_EPWM7);
#endif
#ifdef EPWM8_BASE
  SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_EPWM8);
#endif
#ifdef EPWM9_BASE
  SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_EPWM9);
#endif
#ifdef EPWM10_BASE
  SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_EPWM10);
#endif
#ifdef EPWM11_BASE
  SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_EPWM11);
#endif
#ifdef EPWM12_BASE
  SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_EPWM12);
#endif
#ifdef EPWM13_BASE
  SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_EPWM13);
#endif
#ifdef EPWM14_BASE
  SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_EPWM14);
#endif
#ifdef EPWM15_BASE
  SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_EPWM15);
#endif
#ifdef EPWM16_BASE
  SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_EPWM16);
#endif
#ifdef EPWM17_BASE
  SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_EPWM17);
#endif
#ifdef EPWM18_BASE
  SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_EPWM18);
#endif
#if defined(TARGET_28p65x) || defined(TARGET_29h85x)
  SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_HRCAL0);
  SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_HRCAL1);
  SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_HRCAL2);
#elif defined(TARGET_28p55x) || defined(TARGET_28003x) || defined(TARGET_2838x)
  SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_HRCAL);
#elif defined(TARGET_28004x) || defined(TARGET_2837x)
  SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_HRPWM);
#else
  PLX_ASSERT(0);
#endif
}

#endif /* PLX_EPWM_TYPE4_H_ */
