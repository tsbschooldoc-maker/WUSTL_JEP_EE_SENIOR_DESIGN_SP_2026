/*
   Copyright (c) 2014-2016 by Plexim GmbH
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

#ifndef PLX_AIN_IMPL_H_
#define PLX_AIN_IMPL_H_

#include "f28004x_adc.h"

#define PLX_AIN_NUM_CHANNELS 16

typedef enum PLX_AIN_UNIT {
  PLX_AIN_ADC_A = 0,
  PLX_AIN_ADC_B,
  PLX_AIN_ADC_C,
  PLX_AIN_ADC_D
} PLX_AIN_Unit_t;

#include "ain_type5.h"

inline void PLX_AIN_setDefaultAdcParams(PLX_AIN_AdcParams_t *aParams,
                                        float aVref,
                                        bool sigmodeDifferential) {
  aParams->ADCCTL1.bit.INTPULSEPOS = 1;  // set pulse positions to late
  // max allowable ADC clock is 50 MHz (min 5 MHz)
  if (PLX_AIN_SysClkHz <= 50000000L) {
    aParams->ADCCTL2.bit.PRESCALE = 0;  // set ADCCLK divider to /1.0
  } else if (PLX_AIN_SysClkHz <= 75000000L) {
    aParams->ADCCTL2.bit.PRESCALE = 1;  // set ADCCLK divider to /1.5
  } else if (PLX_AIN_SysClkHz <= 100000000L) {
    aParams->ADCCTL2.bit.PRESCALE = 2;  // set ADCCLK divider to /2.0
  } else if (PLX_AIN_SysClkHz <= 125000000L) {
    aParams->ADCCTL2.bit.PRESCALE = 3;  // set ADCCLK divider to /2.5
  } else if (PLX_AIN_SysClkHz <= 150000000L) {
    aParams->ADCCTL2.bit.PRESCALE = 4;  // set ADCCLK divider to /3.0
  } else if (PLX_AIN_SysClkHz <= 175000000L) {
    aParams->ADCCTL2.bit.PRESCALE = 5;  // set ADCCLK divider to /3.5
  } else {
    aParams->ADCCTL2.bit.PRESCALE = 6;  // set ADCCLK divider to /4.0
  }
  aParams->ADCSOCPRICTL.bit.SOCPRIORITY = 0;  // round-robin
                                              // no high priority channels
  aParams->ADCINTSEL1N2.bit.INT1SEL = 0;

  aParams->vref = aVref;
}

#endif /* PLX_AIN_IMPL_H_ */
