/*
   Copyright (c) 2022-2025 by Plexim GmbH
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

/*
  Lock-free double-buffered IPC for dual-core communication.

  Uses two data buffers with three semaphores per channel for coordination:
    writeBufferSema: Which buffer producer is writing (0, 1, or -1=none)
    readBufferSema:  Which buffer consumer is reading (0, 1, or -1=none)
    lastWrittenSema: Which buffer contains most recent data (0 or 1)

  Protocol ensures producer and consumer never access the same buffer.
  Critical sections only protect semaphore access; data copy happens
  with interrupts enabled to minimize latency.
 */

#include "plx_ipc.h"
#include "plx_dispatcher.h"

PLX_IPC_Handle_t PLX_IPC_init(void *aMemory, const size_t aNumBytes) {
  if (aNumBytes < sizeof(PLX_IPC_Obj_t)) {
    return ((PLX_IPC_Handle_t)NULL);
  }
  PLX_IPC_Handle_t handle = (PLX_IPC_Handle_t)aMemory;
  return handle;
}

void PLX_IPC_setup(PLX_IPC_Handle_t aHandle, void *aAddr1, void *aAddr2) {
  PLX_IPC_Obj_t *obj = (PLX_IPC_Obj_t *)aHandle;

  obj->addr[0] = aAddr1;
  obj->addr[1] = aAddr2;
}

void PLX_IPC_semaphoreSetup(PLX_IPC_Handle_t aHandle,
                            volatile int16_t *aWriteSema,
                            volatile int16_t *aReadSema,
                            volatile int16_t *aLastWrittenSema) {
  PLX_IPC_Obj_t *obj = (PLX_IPC_Obj_t *)aHandle;

  obj->writeBufferSema = aWriteSema;
  obj->readBufferSema = aReadSema;
  obj->lastWrittenSema = aLastWrittenSema;
}

void *PLX_IPC_startTx(PLX_IPC_Handle_t aHandle) {
  PLX_IPC_Obj_t *obj = (PLX_IPC_Obj_t *)aHandle;
  int16_t selectedBuffer;
  
  // select buffer based on consumer access
  DISPR_ENTER_CRITICAL;
  int16_t readSema = *obj->readBufferSema;
  switch (readSema) {
    case 0:
      // consumer is using buffer 0, write to buffer 1 */
      selectedBuffer = 1;
      break;
    case 1:
      // consumer is using buffer 1, write to buffer 0 */
      selectedBuffer = 0;
      break;
    default:
      // consumer is not active, alternate from last written buffer
      selectedBuffer = !*obj->lastWrittenSema;
  }
  
  // mark the selected buffer as being written
  *obj->writeBufferSema = selectedBuffer;
  DISPR_EXIT_CRITICAL;

  return obj->addr[selectedBuffer];
}

void PLX_IPC_stopTx(PLX_IPC_Handle_t aHandle) {
  PLX_IPC_Obj_t *obj = (PLX_IPC_Obj_t *)aHandle;
  
  DISPR_ENTER_CRITICAL;
  // read which buffer was being written
  int16_t writtenBuffer = *obj->writeBufferSema;
  // indicate which buffer has valid data
  *obj->lastWrittenSema = writtenBuffer;
  // release the write lock by setting writeBufferSema to -1
  *obj->writeBufferSema = -1;
  DISPR_EXIT_CRITICAL;
}

void *PLX_IPC_startRx(PLX_IPC_Handle_t aHandle) {
  PLX_IPC_Obj_t *obj = (PLX_IPC_Obj_t *)aHandle;
  int16_t selectedBuffer;
  
  // select buffer based on producer access
  DISPR_ENTER_CRITICAL;
  int16_t writeSema = *obj->writeBufferSema;
  switch (writeSema) {
    case 0:
      // producer is using buffer 0, read from buffer 1
      selectedBuffer = 1;
      break;
    case 1:
      // producer is using buffer 1, read from buffer 0
      selectedBuffer = 0;
      break;
    default:
      // producer is not active, read from last written buffer
      selectedBuffer = *obj->lastWrittenSema;
  }
  // mark the selected buffer as being read
  *obj->readBufferSema = selectedBuffer;
  DISPR_EXIT_CRITICAL;

  // return pointer to the selected buffer
  return obj->addr[selectedBuffer];
}

void PLX_IPC_stopRx(PLX_IPC_Handle_t aHandle) {
  PLX_IPC_Obj_t *obj = (PLX_IPC_Obj_t *)aHandle;
  
  DISPR_ENTER_CRITICAL;
  // release the read lock
  *obj->readBufferSema = -1;
  DISPR_EXIT_CRITICAL;
}
