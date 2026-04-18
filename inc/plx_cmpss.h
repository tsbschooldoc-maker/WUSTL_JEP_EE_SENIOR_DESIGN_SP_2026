/*
   Copyright (c) 2024 by Plexim GmbH
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

#ifndef PLX_CMPSS_H_
#define PLX_CMPSS_H_

#define VDDA_VOLTAGE 3.3  // Analog supply voltage
#define CMPSS_DAC_REFERENCE_VOLTAGE VDDA_VOLTAGE  // DAC reference voltage tied to VDDA

// CMPSS DAC configuration without ramp functionality (12-bit mode)
#define CMPSS_DAC_RESOLUTION 4096  // 12-bit DAC resolution (2^12)
#define CMPSS_DAC_MAX_COUNT 4095   // Maximum 12-bit DAC count value (2^12 - 1)
#define CMPSS_DAC_VOLTS_TO_COUNTS ((CMPSS_DAC_RESOLUTION) / (CMPSS_DAC_REFERENCE_VOLTAGE))

// CMPSS ramp configuration (16-bit DAC with delay extension)
#define CMPSS_RAMP_DELAY_MAX_COUNT 0x1FFF  // Maximum ramp delay count (13-bit)
#define CMPSS_RAMP_STEP_MIN 1  // Minimum ramp step value (prevents divide-by-zero)
#define CMPSS_RAMP_RESOLUTION 65536  // 16-bit ramp resolution (2^16)
#define CMPSS_RAMP_MAX_COUNT UINT16_MAX   // Maximum 16-bit ramp count value (2^16 - 1)
#define CMPSS_RAMP_VOLTS_TO_COUNTS ((CMPSS_RAMP_RESOLUTION) / (CMPSS_DAC_REFERENCE_VOLTAGE))

#include "includes.h"

#include "cmpss.h"
//#include "plx_cmpss_impl.h" // implementation specific

typedef struct PLX_CMPSS_OBJ
{
	uint32_t base;
  uint16_t rampStepVal;
} PLX_CMPSS_Obj_t;

typedef PLX_CMPSS_Obj_t *PLX_CMPSS_Handle_t;

// Initialize CMPSS handle with provided memory.
// Returns NULL if insufficient memory is provided.
PLX_CMPSS_Handle_t PLX_CMPSS_init(void *aMemory, const size_t aNumBytes)
{
	PLX_CMPSS_Handle_t handle;

	if(aNumBytes < sizeof(PLX_CMPSS_Obj_t)){
		return((PLX_CMPSS_Handle_t)NULL);
  }

	// set handle
	handle = (PLX_CMPSS_Handle_t)aMemory;
	return handle;
}

// Configure CMPSS module with base address and ramp step value.
// Ramp step is clamped to CMPSS_RAMP_STEP_MIN to prevent divide-by-zero.
void PLX_CMPSS_configure(PLX_CMPSS_Handle_t aHandle, uint32_t aCmpssBase, uint16_t aRampStepVal){
  PLX_CMPSS_Obj_t *obj = (PLX_CMPSS_Obj_t *)aHandle;
  obj->base = aCmpssBase;

  if(aRampStepVal < CMPSS_RAMP_STEP_MIN){
    // saturate to minimum allowed ramp
    obj->rampStepVal = CMPSS_RAMP_STEP_MIN;  
  }else {
    obj->rampStepVal = aRampStepVal;
  }
  
}

// Set the high DAC threshold voltage for the CMPSS module without ramp functionality.
// Converts voltage to 12-bit DAC counts with saturation to valid range.
static inline void PLX_CMPSS_setDacHigh(PLX_CMPSS_Handle_t aHandle, float aVal){
  PLX_CMPSS_Obj_t *obj = (PLX_CMPSS_Obj_t *)aHandle;
  uint32_t base = obj->base;

  float val = CMPSS_DAC_VOLTS_TO_COUNTS * aVal;
  uint16_t valInt = 0;
  if (val > CMPSS_DAC_MAX_COUNT){
      valInt = CMPSS_DAC_MAX_COUNT;
  } else if (val > 0){
      valInt = (uint16_t)val;
  }
  CMPSS_setDACValueHigh(base, valInt);
}

// Calculates and sets the peak ramp value, applying a ramp delay
// when the desired value exceeds the DAC range.
static inline void PLX_CMPSS_setPeak(PLX_CMPSS_Handle_t aHandle, float aPeak){
  PLX_CMPSS_Obj_t *obj = (PLX_CMPSS_Obj_t *)aHandle;
  uint32_t base = obj->base;

  // Convert peak voltage to DAC counts with saturation protection to prevent overflow
  float val = CMPSS_RAMP_VOLTS_TO_COUNTS * aPeak;
  int32_t valInt = 0;
  if (val > (float)INT32_MAX) {
      valInt = INT32_MAX;
  } else if (val < (float)INT32_MIN) {
      valInt = INT32_MIN;
  } else {
      valInt = (int32_t)val;
  }

  uint16_t rampStepVal = obj->rampStepVal;
  uint32_t rampDelay;

  // Clamp valInt to the DAC resolution and use a ramp delay to compensate
  // for the out-of-range portion. The ramp delay extends the time at the
  // clamped value to achieve the desired behavior.
  // PLX_CMPSS_configure enforces rampStepVal >= 1, preventing divide-by-zero.
  if (valInt > CMPSS_RAMP_MAX_COUNT){
    rampDelay = (uint32_t)((valInt - CMPSS_RAMP_MAX_COUNT) / rampStepVal);     
    valInt = CMPSS_RAMP_MAX_COUNT;
  } else if(valInt < 0) {
    rampDelay = (uint32_t)((0 - valInt) / rampStepVal);         
    valInt = 0;   
  } else {
    rampDelay = 0;     
  }

  // Saturate ramp delay to maximum allowable value
  if (rampDelay > CMPSS_RAMP_DELAY_MAX_COUNT){
    rampDelay = CMPSS_RAMP_DELAY_MAX_COUNT;
  }

  CMPSS_setRampDelayValue(base, (uint16_t)rampDelay);
  CMPSS_setMaxRampValue(base, ((uint16_t)valInt));
}

#endif /* PLX_CMPSS_H_ */
