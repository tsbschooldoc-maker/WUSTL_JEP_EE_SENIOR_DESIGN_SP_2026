/*
   Copyright (c) 2018 by Plexim GmbH
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

#ifndef PLX_SCI_H_
#define PLX_SCI_H_

#include "includes.h"
#include "plx_sci_impl.h"  // implementation specific
#include "plx_serial.h"

extern PLX_SCI_Handle_t PLX_SCI_init(void *aMemory, const size_t aNumBytes);
extern void PLX_SCI_configure(PLX_SCI_Handle_t aHandle, PLX_SCI_Unit_t aUnit, uint32_t aClk);

extern bool PLX_SCI_setupPort(PLX_SCI_Handle_t aHandle, uint32_t baudrate);

extern bool PLX_SCI_rxReady(PLX_SCI_Handle_t aHandle);
extern bool PLX_SCI_txIsBusy(PLX_SCI_Handle_t aHandle);

extern uint16_t PLX_SCI_getChar(PLX_SCI_Handle_t aHandle);
extern void PLX_SCI_putChar(PLX_SCI_Handle_t aHandle, uint16_t c);

extern bool PLX_SCI_breakOccurred(PLX_SCI_Handle_t aHandle);
extern void PLX_SCI_reset(PLX_SCI_Handle_t aHandle);

// deprecated
extern void PLX_SCI_configureViaPinSet(PLX_SCI_Handle_t aHandle, uint16_t port, uint32_t clk);

/* 
   Trampoline functions make versions of the common SCI files that work with 
   void* inputs, to match the function signatures expected by plx_serial.h
 */

inline static void PLX_SCI_configure_trampoline(void* instance, void* aUnit, uint32_t aClk){
#if !defined(TARGET_2806x) && !defined(TARGET_2833x)
  PLX_SCI_Handle_t aHandle = (PLX_SCI_Handle_t)instance;
  PLX_SCI_Unit_t unit = *(PLX_SCI_Unit_t*)aUnit;
  PLX_SCI_configure(aHandle, unit, aClk);
#endif
}

inline static bool PLX_SCI_setupPort_trampoline(void* instance, uint32_t baudrate){
  PLX_SCI_Handle_t aHandle = (PLX_SCI_Handle_t)instance;
  return PLX_SCI_setupPort(aHandle, baudrate);
}

inline static bool PLX_SCI_rxReady_trampoline(void* instance){
  PLX_SCI_Handle_t aHandle = (PLX_SCI_Handle_t)instance;
  return PLX_SCI_rxReady(aHandle);
}

inline static bool PLX_SCI_txIsBusy_trampoline(void* instance){
  PLX_SCI_Handle_t aHandle = (PLX_SCI_Handle_t)instance;
  return PLX_SCI_txIsBusy(aHandle);
}

inline static uint16_t PLX_SCI_getChar_trampoline(void* instance){
  PLX_SCI_Handle_t aHandle = (PLX_SCI_Handle_t)instance;
  return PLX_SCI_getChar(aHandle);
}

inline static void PLX_SCI_putChar_trampoline(void* instance, uint16_t c){
  PLX_SCI_Handle_t aHandle = (PLX_SCI_Handle_t)instance;
  PLX_SCI_putChar(aHandle, c);
}

inline static bool PLX_SCI_breakOccurred_trampoline(void* instance){
  PLX_SCI_Handle_t aHandle = (PLX_SCI_Handle_t)instance;
  return PLX_SCI_breakOccurred(aHandle);
}

inline static void PLX_SCI_reset_trampoline(void* instance){
  PLX_SCI_Handle_t aHandle = (PLX_SCI_Handle_t)instance;
  PLX_SCI_reset(aHandle);
}

inline static void PLX_SCI_configureViaPinset_trampoline(void* instance, uint16_t aPort, uint32_t aClk){
#if defined(TARGET_2806x) || defined(TARGET_2833x)
  PLX_SCI_Handle_t aHandle = (PLX_SCI_Handle_t)instance;
  PLX_SCI_configureViaPinSet(aHandle, aPort, aClk);
#endif
}

inline static void PLX_SCI_setInterface(PLX_Serial_Handle_t aHandle,
                                        PLX_SCI_Handle_t bHandle){
  PLX_Serial_Obj_t *obj = (PLX_Serial_Obj_t *)aHandle;
  PLX_Serial_Interface_t impl;

  impl.configure =        PLX_SCI_configure_trampoline;
  impl.setupPort =        PLX_SCI_setupPort_trampoline;
  impl.rxReady =          PLX_SCI_rxReady_trampoline;
  impl.txIsBusy =         PLX_SCI_txIsBusy_trampoline;
  impl.putChar =          PLX_SCI_putChar_trampoline;
  impl.getChar =          PLX_SCI_getChar_trampoline;
  impl.breakOccurred =    PLX_SCI_breakOccurred_trampoline;
  impl.reset =            PLX_SCI_reset_trampoline;
  impl.configViaPinset =  PLX_SCI_configureViaPinset_trampoline;

  obj->instance = bHandle;
  obj->impl = impl; 
}

#endif /* PLX_SCI_H_ */
