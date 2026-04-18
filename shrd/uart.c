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

#include "includes.h"
#include "plx_uart.h"

#if defined(TARGET_28p65x) || defined(TARGET_29h85x)
#include "uart.h"

extern PLX_UART_Handle_t PLX_UART_init(void *aMemory, const size_t aNumBytes) {
  PLX_UART_Handle_t handle;

  if (aNumBytes < sizeof(PLX_UART_Obj_t)){
    return((PLX_UART_Handle_t)NULL);
  }

  // set handle
  handle = (PLX_UART_Handle_t)aMemory;

  return handle;
}

extern void PLX_UART_configure(void* aHandle, void* baseAddr, uint32_t aClk){
  PLX_UART_Obj_t *obj = (PLX_UART_Obj_t *)aHandle;
  obj->baseAddr = *(uint32_t *)baseAddr;
  obj->clk = aClk;
}

extern bool PLX_UART_setupPort(void* aHandle, uint32_t baudrate){
  PLX_UART_Obj_t *obj = (PLX_UART_Obj_t *)aHandle;
  obj->baud = baudrate;

  switch(obj->baseAddr)
  {
      case UARTA_BASE: 
          SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_UARTA);
          break;

      case UARTB_BASE:
          SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_UARTB);
          break;

#ifdef UARTC_BASE
      case UARTC_BASE: 
          SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_UARTC);
          break;
#endif
#ifdef UARTD_BASE
      case UARTD_BASE: 
          SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_UARTD);
          break;
#endif
#ifdef UARTE_BASE
      case UARTE_BASE: 
          SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_UARTE);
          break;
#endif
#ifdef UARTF_BASE
      case UARTF_BASE: 
          SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_UARTF);
          break;
#endif

      default:
          PLX_ASSERT(0);
  }

  // default data format is one stopbit, 8 bit transmission
  uint32_t dataFormat = (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE);

  UART_setConfig(obj->baseAddr, obj->clk, obj->baud, dataFormat);
  UART_enableModule(obj->baseAddr);

  // To stay consistent with the older SCI function
  // interfaces, we must return a bool.
  return true;
}

extern bool PLX_UART_rxReady(void* aHandle){
  PLX_UART_Obj_t *obj = (PLX_UART_Obj_t *)aHandle;

  return UART_isDataAvailable(obj->baseAddr);
}

extern bool PLX_UART_txIsBusy(void* aHandle){
  PLX_UART_Obj_t *obj = (PLX_UART_Obj_t *)aHandle;

  return !UART_isSpaceAvailable(obj->baseAddr);
}

extern uint16_t PLX_UART_getChar(void* aHandle){
  PLX_UART_Obj_t *obj = (PLX_UART_Obj_t *)aHandle;

  return (uint16_t) UART_readCharNonBlocking(obj->baseAddr);
}

extern void PLX_UART_putChar(void* aHandle, uint16_t c){
  PLX_UART_Obj_t *obj = (PLX_UART_Obj_t *)aHandle;

  UART_writeCharNonBlocking(obj->baseAddr, c);
}

extern bool PLX_UART_breakOccurred(void* aHandle){
  PLX_UART_Obj_t *obj = (PLX_UART_Obj_t *)aHandle;

  return (UART_getRxError(obj->baseAddr) & UART_RXERROR_BREAK);
}

extern void PLX_UART_reset(void* aHandle){
  PLX_UART_Obj_t *obj = (PLX_UART_Obj_t *)aHandle;
  UART_disableModule(obj->baseAddr);
  UART_enableModule(obj->baseAddr);
  UART_clearRxError(obj->baseAddr);
}

extern void PLX_UART_setInterface(PLX_Serial_Handle_t aHandle,
                                  PLX_UART_Handle_t bHandle){
  PLX_Serial_Obj_t *obj = (PLX_Serial_Obj_t *)aHandle;
  PLX_Serial_Interface_t impl;

  impl.configure =      PLX_UART_configure;
  impl.setupPort =      PLX_UART_setupPort;
  impl.rxReady =        PLX_UART_rxReady;
  impl.txIsBusy =       PLX_UART_txIsBusy;
  impl.putChar =        PLX_UART_putChar;
  impl.getChar =        PLX_UART_getChar;
  impl.breakOccurred =  PLX_UART_breakOccurred;
  impl.reset =          PLX_UART_reset;

  obj->instance = bHandle;
  obj->impl = impl;
}
#endif // target-specific defines
