
/*
   Copyright (c) 2025 by Plexim GmbH
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

#ifndef PLX_UART_H_
#define PLX_UART_H_

#include "includes.h"
#include "plx_serial.h"

typedef struct PLX_UART_OBJ {
  uint32_t baseAddr;
  uint32_t baud;
  uint32_t clk;
} PLX_UART_Obj_t;

typedef PLX_UART_Obj_t *PLX_UART_Handle_t;

extern PLX_UART_Handle_t PLX_UART_init(void *aMemory, const size_t aNumBytes);
extern void PLX_UART_configure(void* aHandle, void *baseAddr, uint32_t aClk);

extern bool PLX_UART_setupPort(void* aHandle, uint32_t baudrate);

extern bool PLX_UART_rxReady(void* aHandle);
extern bool PLX_UART_txIsBusy(void* aHandle);

extern uint16_t PLX_UART_getChar(void* aHandle);
extern void PLX_UART_putChar(void* aHandle, uint16_t c);

extern bool PLX_UART_breakOccurred(void* aHandle);
extern void PLX_UART_reset(void* aHandle);

extern void PLX_UART_setInterface(PLX_Serial_Handle_t aHandle,
                                  PLX_UART_Handle_t bHandle);

#endif /* PLX_TI_UART_H_ */
