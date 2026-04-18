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


#include "plx_sdfm.h"

#ifndef PLX_SDFM_UNSUPPORTED
#include "gpio.h"

extern PLX_SDFM_Handle_t PLX_SDFM_init(void *aMemory, const size_t aNumBytes) {
  PLX_SDFM_Handle_t handle;

  if (aNumBytes < sizeof(PLX_SDFM_Obj_t)){
    return((PLX_SDFM_Handle_t)NULL);
  }

  // set handle
  handle = (PLX_SDFM_Handle_t)aMemory;

  return handle;
}

extern void PLX_SDFM_configFilter(PLX_SDFM_Handle_t aHandle, uint32_t baseAddr,
                                  SDFM_FilterNumber filterNumber,
                                  SDFM_FilterType filterType,
                                  SDFM_OutputDataFormat dataFormat,
                                  uint16_t osr, uint16_t shift) {
  aHandle->baseAddr = baseAddr;
  aHandle->filterNumber = filterNumber;
  aHandle->filterType = filterType;
  aHandle->dataFormat = dataFormat;
  aHandle->osr = osr;
  aHandle->shift = shift;

  SDFM_setupModulatorClock(baseAddr, filterNumber, SDFM_MODULATOR_CLK_EQUAL_DATA_RATE);
  SDFM_configDataFilter(baseAddr, (filterNumber | filterType | SDFM_SET_OSR(osr)),
                        (dataFormat | SDFM_FILTER_ENABLE | SDFM_SHIFT_VALUE(shift)));
}

extern int16_t PLX_SDFM_getFilterData16(PLX_SDFM_Handle_t aHandle){
  return (int16_t)(SDFM_getFilterData(aHandle->baseAddr, aHandle->filterNumber)>>16U);
}

extern int32_t PLX_SDFM_getFilterData32(PLX_SDFM_Handle_t aHandle){
  return SDFM_getFilterData(aHandle->baseAddr, aHandle->filterNumber);
}

extern void PLX_SDFM_configCompOSR(PLX_SDFM_Handle_t aHandle, uint16_t osr){
  SDFM_setCompFilterOverSamplingRatio(aHandle->baseAddr, aHandle->filterNumber, osr);
}

extern void PLX_SDFM_setCompFilterType(PLX_SDFM_Handle_t aHandle, SDFM_FilterType filterType){
  SDFM_setComparatorFilterType(aHandle->baseAddr, aHandle->filterNumber, filterType);
}
extern void PLX_SDFM_configCompHighThreshold(PLX_SDFM_Handle_t aHandle, uint16_t highThreshold){
  SDFM_setCompFilterHighThreshold(aHandle->baseAddr, aHandle->filterNumber, highThreshold);
}

extern void PLX_SDFM_configCompLowThreshold(PLX_SDFM_Handle_t aHandle, uint16_t lowThreshold){
  SDFM_setCompFilterLowThreshold(aHandle->baseAddr, aHandle->filterNumber, lowThreshold);
}

#ifndef PLX_SDFM_2837x_LEGACY
extern void PLX_SDFM_enableComparator(PLX_SDFM_Handle_t aHandle){
  SDFM_enableComparator(aHandle->baseAddr, aHandle->filterNumber);
}
#endif /* PLX_SDFM_2837x_LEGACY */

#ifndef PLX_SDFM_DIGITAL_FILTER_UNSUPPORTED
extern void PLX_SDFM_configCompDigitalFilter(PLX_SDFM_Handle_t aHandle,
                                             bool highCompEnabled,
                                             bool lowCompEnabled,
                                             SDFM_CompEventFilterConfig *config){

  if (highCompEnabled) {
    SDFM_selectCompEventSource(aHandle->baseAddr, aHandle->filterNumber,
                               SDFM_COMP_EVENT_1, SDFM_COMP_EVENT_SRC_COMPH1);
    SDFM_configCompEventHighFilter(aHandle->baseAddr, aHandle->filterNumber, config);
    SDFM_selectCompEventHighSource(aHandle->baseAddr, aHandle->filterNumber,
                                  SDFM_COMPHOUT_SOURCE_FILTER);
    SDFM_initCompEventHighFilter(aHandle->baseAddr, aHandle->filterNumber);
  } 
  if (lowCompEnabled) {
    SDFM_selectCompEventSource(aHandle->baseAddr, aHandle->filterNumber,
                               SDFM_COMP_EVENT_2, SDFM_COMP_EVENT_SRC_COMPL1);
    SDFM_configCompEventLowFilter(aHandle->baseAddr, aHandle->filterNumber, config);
    SDFM_selectCompEventLowSource(aHandle->baseAddr, aHandle->filterNumber,
                                  SDFM_COMPLOUT_SOURCE_FILTER);
    SDFM_initCompEventLowFilter(aHandle->baseAddr, aHandle->filterNumber);
  }

  if (!(highCompEnabled || lowCompEnabled)){
    // if neither threshold is set, we shouldn't be calling this function
    PLX_ASSERT(0);
  }
}

#endif /* PLX_SDFM_DIGITAL_FILTER_UNSUPPORTED */
#endif /* PLX_SDFM_UNSUPPORTED */
