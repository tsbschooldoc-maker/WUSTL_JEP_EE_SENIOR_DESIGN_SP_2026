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

#ifndef PLX_SDFM_H_
#define PLX_SDFM_H_

#include "includes.h"
#include "plx_sdfm_impl.h"

#ifndef PLX_SDFM_UNSUPPORTED

extern PLX_SDFM_Handle_t PLX_SDFM_init(void *aMemory, const size_t aNumBytes);
extern void PLX_SDFM_configFilter(PLX_SDFM_Handle_t aHandle, uint32_t baseAddr,
                                  SDFM_FilterNumber filterNumber, 
                                  SDFM_FilterType filterType, 
                                  SDFM_OutputDataFormat dataFormat, 
                                  uint16_t osr, uint16_t shift);

extern int16_t PLX_SDFM_getFilterData16(PLX_SDFM_Handle_t aHandle);
extern int32_t PLX_SDFM_getFilterData32(PLX_SDFM_Handle_t aHandle);

extern void PLX_SDFM_configCompOSR(PLX_SDFM_Handle_t, uint16_t osr);
extern void PLX_SDFM_setCompFilterType(PLX_SDFM_Handle_t, SDFM_FilterType filterType);
extern void PLX_SDFM_configCompHighThreshold(PLX_SDFM_Handle_t aHandle,
                                             uint16_t highThreshold);
extern void PLX_SDFM_configCompLowThreshold(PLX_SDFM_Handle_t aHandle,
                                            uint16_t lowThreshold);

#ifndef PLX_SDFM_2837x_LEGACY
extern void PLX_SDFM_enableComparator(PLX_SDFM_Handle_t aHandle);
#endif /* PLX_SDFM_2837x_LEGACY */

#ifndef PLX_SDFM_DIGITAL_FILTER_UNSUPPORTED

extern void PLX_SDFM_configCompDigitalFilter(PLX_SDFM_Handle_t aHandle,
                                             bool highCompEnabled,
                                             bool lowCompEnabled,
                                             SDFM_CompEventFilterConfig *config);

#endif /* PLX_SDFM_DIGITAL_FILTER_UNSUPPORTED */
#endif /* PLX_SDFM_UNSUPPORTED */
#endif /* PLX_SDFM_H_ */
