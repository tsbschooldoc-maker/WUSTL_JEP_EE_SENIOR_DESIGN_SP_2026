/*
   Copyright (c) 2023 by Plexim GmbH
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

#include "inc/hw_memmap.h"
#include "plx_ain.h"

#pragma diag_suppress 112  // PLX_ASSERT(0) in switch statements

/* Note:
 * No power-up delay implemented.
 * Assuming system-level delay will allow ADC to settle
 */

uint32_t PLX_AIN_SysClkHz;

void PLX_AIN_sinit(uint32_t aSysClkHz) {
  PLX_AIN_SysClkHz = aSysClkHz;
}

PLX_AIN_Handle_t PLX_AIN_init(void *aMemory, const size_t aNumBytes) {
  PLX_AIN_Handle_t handle;

  if (aNumBytes < sizeof(PLX_AIN_Obj_t)) {
    return ((PLX_AIN_Handle_t)NULL);
  }
  // set handle
  handle = (PLX_AIN_Handle_t)aMemory;

  return handle;
}

void PLX_AIN_configure(PLX_AIN_Handle_t aHandle, PLX_AIN_Unit_t aUnit,
                       const PLX_AIN_AdcParams_t *aParams) {
  PLX_AIN_Obj_t *obj = (PLX_AIN_Obj_t *)aHandle;

  // we are only supporting 12 bit/single ended
  obj->voltsPerAdcBit = aParams->vref / 4096.0f;
  #pragma diag_suppress 552
  uint32_t base;
  #pragma diag_default 552

  EALLOW;
  switch (aUnit) {
    default:
      PLX_ASSERT(0);
      break;

#ifdef ADCA_BASE
    case PLX_AIN_ADC_A:
      base = ADCA_BASE;
      obj->adc = &AdcaRegs;
      obj->results = (uint16_t *)&AdcaResultRegs;
      SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCA);
      break;
#endif
#ifdef ADCB_BASE
    case PLX_AIN_ADC_B:
      base = ADCB_BASE;
      obj->adc = &AdcbRegs;
      obj->results = (uint16_t *)&AdcbResultRegs;
      SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCB);
      break;
#endif
#ifdef ADCC_BASE
		case PLX_AIN_ADC_C:
      base = ADCC_BASE;
			obj->adc = &AdccRegs;
			obj->results = (uint16_t *)&AdccResultRegs;
			SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCC);
			break;
#endif
#ifdef ADCD_BASE
    case PLX_AIN_ADC_D:
      base = ADCD_BASE;
      obj->adc = &AdcdRegs;
      obj->results = (uint16_t *)&AdcdResultRegs;
      SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCD);
      break;
#endif
#ifdef ADCE_BASE
    case PLX_AIN_ADC_E:
      base = ADCE_BASE;
      obj->adc = &AdceRegs;
      obj->results = (uint16_t *)&AdceResultRegs;
      SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCE);
      break;
#endif
  }

#ifdef TARGET_29h85x
  // the F29H85x ADC can also operate in other modes
  ADC_setMode(base, ADC_RESOLUTION_12BIT, ADC_MODE_SINGLE_ENDED);
#endif
  EDIS;

#ifndef TARGET_29h85x
  obj->socCtrl = (union ADCSOC0CTL_REG *)&obj->adc->ADCSOC0CTL;
#else
  obj->socCtrl = (union ADC_ADCSOC0CTL_REG *)&obj->adc->ADCSOC0CTL;
#endif

  EALLOW;
  obj->adc->ADCCTL1.bit.ADCPWDNZ = 1;  // power up the ADC
  obj->adc->ADCCTL1.bit.INTPULSEPOS = aParams->ADCCTL1.bit.INTPULSEPOS;
  obj->adc->ADCCTL2.bit.PRESCALE = aParams->ADCCTL2.bit.PRESCALE;
  obj->adc->ADCSOCPRICTL.bit.SOCPRIORITY =
      aParams->ADCSOCPRICTL.bit.SOCPRIORITY;
  obj->adc->ADCINTSEL1N2.bit.INT1SEL = aParams->ADCINTSEL1N2.bit.INT1SEL;
  EDIS;
  PLX_AIN_resetChannelSetup(aHandle);
}

void PLX_AIN_setDefaultChannelParams(PLX_AIN_ChannelParams_t *aParams) {
  aParams->ADCSOCxCTL.bit.TRIGSEL = 1;  // trigger on CpuTimer0
  aParams->ADCSOCxCTL.bit.ACQPS = 14;   // safe default, overwritten later
                                        // based on user configuration
  aParams->scale = 1.0;
  aParams->offset = 0.0;
}

void PLX_AIN_resetChannelSetup(PLX_AIN_Handle_t aHandle) {
  PLX_AIN_Obj_t *obj = (PLX_AIN_Obj_t *)aHandle;

  EALLOW;
  for (int i = 0; i < PLX_AIN_NUM_CHANNELS; i++) {
    obj->socCtrl[i].bit.TRIGSEL = 0;
  }
  EDIS;
}

void PLX_AIN_setupChannel(PLX_AIN_Handle_t aHandle, uint16_t aChannel,
                          uint16_t aSource,
                          const PLX_AIN_ChannelParams_t *aParams) {
  PLX_AIN_Obj_t *obj = (PLX_AIN_Obj_t *)aHandle;

  PLX_ASSERT(aChannel < PLX_AIN_NUM_CHANNELS);

  EALLOW;
  obj->socCtrl[aChannel].bit.CHSEL = aSource;
  obj->socCtrl[aChannel].bit.TRIGSEL = aParams->ADCSOCxCTL.bit.TRIGSEL;
  obj->socCtrl[aChannel].bit.ACQPS = aParams->ADCSOCxCTL.bit.ACQPS;
  EDIS;
  obj->scale[aChannel] = aParams->scale * obj->voltsPerAdcBit;
  obj->offset[aChannel] = aParams->offset;
}
