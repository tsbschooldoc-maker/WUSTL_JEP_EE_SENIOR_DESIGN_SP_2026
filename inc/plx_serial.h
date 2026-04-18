
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

#ifndef PLX_SERIAL_H_
#define PLX_SERIAL_H_

#include "includes.h"

typedef enum PLX_SERIAL_TYPE {
  PLX_SERIAL_UART = 0,
  PLX_SERIAL_SCI,
} PLX_Serial_Type_t;

typedef struct PLX_SERIAL_INTERFACE {
  void      (*configure)(void* instance, void* resource, uint32_t clk);
  bool      (*setupPort)(void* instance, uint32_t baudrate);
  bool      (*rxReady)(void* instance);
  bool      (*txIsBusy)(void* instance);
  uint16_t  (*getChar)(void* instance);
  void      (*putChar)(void* instance, uint16_t c);
  bool      (*breakOccurred)(void* instance);
  void      (*reset)(void* instance);

  // deprecated
  void      (*configViaPinset)(void* instance, uint16_t port, uint32_t clk);
} PLX_Serial_Interface_t;

typedef struct PLX_SERIAL_OBJ {
  void* instance;
  PLX_Serial_Interface_t impl;
} PLX_Serial_Obj_t;

typedef PLX_Serial_Obj_t* PLX_Serial_Handle_t;

inline PLX_Serial_Handle_t PLX_Serial_init(void *aMemory, const size_t aNumBytes){
  if(aNumBytes < sizeof(PLX_Serial_Obj_t))
	{
		return((PLX_Serial_Handle_t)NULL);
	}
	PLX_Serial_Handle_t handle = (PLX_Serial_Handle_t)aMemory;
	return handle;
}

inline void PLX_Serial_setInstance(PLX_Serial_Handle_t aHandle, void *instance){
  PLX_Serial_Obj_t *obj = (PLX_Serial_Obj_t *)aHandle;
  obj->instance = instance;
}

inline void PLX_Serial_config(PLX_Serial_Handle_t aHandle, void *resource, uint32_t aClk){
  PLX_Serial_Obj_t *obj = (PLX_Serial_Obj_t *)aHandle;
  if(obj->impl.configure != NULL){
    obj->impl.configure(obj->instance, resource, aClk);
  } else {
    PLX_ASSERT(0);
  }
}

inline void PLX_Serial_setupPort(PLX_Serial_Handle_t aHandle, uint32_t baudrate){
  PLX_Serial_Obj_t *obj = (PLX_Serial_Obj_t *)aHandle;
  if(obj->impl.setupPort != NULL){
    obj->impl.setupPort(obj->instance, baudrate);
  } else {
    PLX_ASSERT(0);
  }
}

inline bool PLX_Serial_rxReady(PLX_Serial_Handle_t aHandle){
  PLX_Serial_Obj_t *obj = (PLX_Serial_Obj_t *)aHandle;
  if(obj->impl.rxReady != NULL){
    return obj->impl.rxReady(obj->instance);
  } else {
    PLX_ASSERT(0);
  }
}

inline bool PLX_Serial_txIsBusy(PLX_Serial_Handle_t aHandle){
  PLX_Serial_Obj_t *obj = (PLX_Serial_Obj_t *)aHandle;
  if(obj->impl.txIsBusy != NULL){
    return obj->impl.txIsBusy(obj->instance);
  } else {
    PLX_ASSERT(0);
  }
}

inline uint16_t PLX_Serial_getChar(PLX_Serial_Handle_t aHandle){
  PLX_Serial_Obj_t *obj = (PLX_Serial_Obj_t *)aHandle;
  if(obj->impl.getChar != NULL){
    return obj->impl.getChar(obj->instance);
  } else {
    PLX_ASSERT(0);
  }
}

inline void PLX_Serial_putChar(PLX_Serial_Handle_t aHandle, uint16_t c){
  PLX_Serial_Obj_t *obj = (PLX_Serial_Obj_t *)aHandle;
  if(obj->impl.putChar != NULL){
    obj->impl.putChar(obj->instance, c);
  } else {
    PLX_ASSERT(0);
  }
}

inline bool PLX_Serial_breakOccurred(PLX_Serial_Handle_t aHandle){
  PLX_Serial_Obj_t *obj = (PLX_Serial_Obj_t *)aHandle;
  if(obj->impl.breakOccurred != NULL){
    return obj->impl.breakOccurred(obj->instance);
  } else {
    PLX_ASSERT(0);
  }
}

inline void PLX_Serial_reset(PLX_Serial_Handle_t aHandle){
  PLX_Serial_Obj_t *obj = (PLX_Serial_Obj_t *)aHandle;
  if(obj->impl.breakOccurred != NULL){
    obj->impl.reset(obj->instance);
  } else {
    PLX_ASSERT(0);
  }
}

// deprecated 
inline void PLX_Serial_configViaPinset(PLX_Serial_Handle_t aHandle,
                                       uint16_t aPort, uint32_t aClk){
  PLX_Serial_Obj_t *obj = (PLX_Serial_Obj_t *)aHandle;
  if(obj->impl.configViaPinset != NULL){
    obj->impl.configViaPinset(obj->instance, aPort, aClk);
  } else {
    PLX_ASSERT(0);
  }
}

#endif /* PLX_SERIAL_H_ */
