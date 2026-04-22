/*
 * Implementation file for: PLECS_to_CCS
 * Generated with         : PLECS 4.9.8
 *                          TI28004x 2.2.1
 * Generated on           : 10 Apr 2026 19:05:08
 */
 // ==========================================================
// CUSTOM HARDWARE & TELEMETRY DEFINITIONS
// ==========================================================

// 1. Gives this file access to the TI hardware registers (AdcbResultRegs, etc.)
#include "includes.h" 

// 2. Tells this file that these variables are defined globally somewhere else
extern  float ext_V_EV;
extern  float ext_I_EV;
extern  float ext_V_PV;
extern  float ext_I_PV;
extern  float ext_V_Bat;
extern  float ext_I_Bat;
// Tells this file that your custom I2C functions exist in main.c
extern void update_telemetry_data(void);
extern void respond_to_ESP32(void);



// Live debugging variables (Must be volatile to show up in Watch window!)
float v_pin_V_PV  = 0.0f;
float v_pin_V_Bat = 0.0f;
float v_pin_V_EV  = 0.0f;
float v_pin_I_PV  = 0.0f;
float v_pin_I_Bat = 0.0f;
float v_pin_I_EV  = 0.0f;

volatile uint32_t abcounter = 0;
// 3. Tells this file that these functions exist in another file
extern void update_telemetry_data(void);
extern void respond_to_ESP32(void);

#include "PLECS_to_CCS.h"
#ifndef PLECS_HEADER_PLECS_to_CCS_h_
#error The wrong header file "PLECS_to_CCS.h" was included. Please check
#error your include path to see whether this file name conflicts with the
#error name of another header file.
#endif /* PLECS_HEADER_PLECS_to_CCS_h_ */
#if defined(__GNUC__) && (__GNUC__ > 4)
#   define _ALIGNMENT 16
#   define _RESTRICT __restrict
#   define _ALIGN __attribute__((aligned(_ALIGNMENT)))
#   if defined(__clang__)
#      if __has_builtin(__builtin_assume_aligned)
#         define _ASSUME_ALIGNED(a) __builtin_assume_aligned(a, _ALIGNMENT)
#      else
#         define _ASSUME_ALIGNED(a) a
#      endif
#   else
#      define _ASSUME_ALIGNED(a) __builtin_assume_aligned(a, _ALIGNMENT)
#   endif
#else
#   ifndef _RESTRICT
#      define _RESTRICT
#   endif
#   ifndef _ALIGN
#      define _ALIGN
#   endif
#   ifndef _ASSUME_ALIGNED
#      define _ASSUME_ALIGNED(a) a
#   endif
#endif
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "plx_hal.h"
#include <stdlib.h>
#define PLECSRunTimeError(msg) PLECS_to_CCS_errorStatus = msg
struct CScriptStruct
{
   int numInputTerminals;
   int numOutputTerminals;
   int* numInputSignals;
   int* numOutputSignals;
   int numContStates;
   int numDiscStates;
   int numZCSignals;
   int numSampleTimes;
   int numParameters;
   int isMajorTimeStep;
   float time;
   const float ***inputs;
   float ***outputs;
   float *contStates;
   float *contDerivs;
   float *discStates;
   float *zCSignals;
   const int *paramNumDims;
   const int **paramDims;
   const int *paramNumElements;
   const float **paramRealData;
   const char **paramStringData;
   const char * const *sampleHits;
   const float *sampleTimePeriods;
   const float *sampleTimeOffsets;
   const float * const *inputSampleTimePeriods;
   const float * const *inputSampleTimeOffsets;
   float *nextSampleHit;
   const char** errorStatus;
   const char** warningStatus;
   const char** rangeErrorMsg;
   int* rangeErrorLine;
   void (*writeCustomStateDouble)(void*, float);
   float (*readCustomStateDouble)(void*);
   void (*writeCustomStateInt)(void*, int);
   void (*writeCustomStateData)(void*, const void*, int);
   void (*readCustomStateData)(void*, void*, int);
};
static struct CScriptStruct PLECS_to_CCS_cScriptStruct[4];
static char PLECS_to_CCS_isMajorStep = '\001';
static const uint32_t PLECS_to_CCS_subTaskPeriod[1]= {
   /* [0.00022, 0], [0, 0] */
   11
};
static uint32_t PLECS_to_CCS_subTaskTick[1];
static char PLECS_to_CCS_subTaskHit[1];
#define PLECS_to_CCS_UNCONNECTED 0
void PLECS_to_CCS_0_cScriptStart(const struct CScriptStruct *cScriptStruct);
void PLECS_to_CCS_0_cScriptOutput(const struct CScriptStruct *cScriptStruct);
void PLECS_to_CCS_0_cScriptUpdate(const struct CScriptStruct *cScriptStruct);
void PLECS_to_CCS_0_cScriptDerivative(
                                      const struct CScriptStruct *cScriptStruct);
void PLECS_to_CCS_0_cScriptTerminate(const struct CScriptStruct *cScriptStruct);
void PLECS_to_CCS_1_cScriptStart(const struct CScriptStruct *cScriptStruct);
void PLECS_to_CCS_1_cScriptOutput(const struct CScriptStruct *cScriptStruct);
void PLECS_to_CCS_1_cScriptUpdate(const struct CScriptStruct *cScriptStruct);
void PLECS_to_CCS_1_cScriptDerivative(
                                      const struct CScriptStruct *cScriptStruct);
void PLECS_to_CCS_1_cScriptTerminate(const struct CScriptStruct *cScriptStruct);
void PLECS_to_CCS_2_cScriptStart(const struct CScriptStruct *cScriptStruct);
void PLECS_to_CCS_2_cScriptOutput(const struct CScriptStruct *cScriptStruct);
void PLECS_to_CCS_2_cScriptUpdate(const struct CScriptStruct *cScriptStruct);
void PLECS_to_CCS_2_cScriptDerivative(
                                      const struct CScriptStruct *cScriptStruct);
void PLECS_to_CCS_2_cScriptTerminate(const struct CScriptStruct *cScriptStruct);
void PLECS_to_CCS_3_cScriptStart(const struct CScriptStruct *cScriptStruct);
void PLECS_to_CCS_3_cScriptOutput(const struct CScriptStruct *cScriptStruct);
void PLECS_to_CCS_3_cScriptUpdate(const struct CScriptStruct *cScriptStruct);
void PLECS_to_CCS_3_cScriptDerivative(
                                      const struct CScriptStruct *cScriptStruct);
void PLECS_to_CCS_3_cScriptTerminate(const struct CScriptStruct *cScriptStruct);
static uint32_t PLECS_to_CCS_tickLo;
static int32_t PLECS_to_CCS_tickHi;
PLECS_to_CCS_BlockOutputs PLECS_to_CCS_B;
PLECS_to_CCS_ModelStates PLECS_to_CCS_X _ALIGN;
const char * PLECS_to_CCS_errorStatus;
const float PLECS_to_CCS_sampleTime = 2e-05f;
const char * const PLECS_to_CCS_checksum =
   "7bdbdf82fb0a2ab20dc9e80706737b97daa786b4";
/* Target declarations */
// tag step function to allow special linking
// Force the 50kHz loop into high-speed RAM!
#pragma CODE_SECTION(PLECS_to_CCS_step, "ramfuncs")
extern void PLECS_to_CCS_initHal();

void PLECS_to_CCS_initialize(void)
{
   PLECS_to_CCS_tickHi = 0;
   PLECS_to_CCS_tickLo = 0;
   /* Initialize sub-task tick counters */
   PLECS_to_CCS_subTaskTick[0] = 0; /* [0, 0], [0.00022, 0] */
   memset(&PLECS_to_CCS_X, 0, sizeof(PLECS_to_CCS_X));

   /* Target pre-initialization */
   PLECS_to_CCS_initHal();


   /* Initialization for C-Script : 'PLECS_to_CCS/C-Script' */
   {
      static int numInputSignals[] = {
         1, 1, 1, 1, 1, 1
      };
      static const float* inputPtrs[] = {
         &PLECS_to_CCS_B.CurrentADC[2], &PLECS_to_CCS_B.VoltageADC[2],
         &PLECS_to_CCS_B.CurrentADC[0], &PLECS_to_CCS_B.VoltageADC[0],
         &PLECS_to_CCS_B.VoltageADC[1], &PLECS_to_CCS_B.CurrentADC[1]
      };
      static const float** inputs[] = {
         &inputPtrs[0], &inputPtrs[1], &inputPtrs[2], &inputPtrs[3],
         &inputPtrs[4], &inputPtrs[5]
      };
      static int numOutputSignals[] = {
         1, 1, 1, 1, 1, 1
      };
      static float* outputPtrs[] = {
         &PLECS_to_CCS_B.C_Script[0], &PLECS_to_CCS_B.C_Script[1],
         &PLECS_to_CCS_B.C_Script[2], &PLECS_to_CCS_B.C_Script[3],
         &PLECS_to_CCS_B.C_Script[4], &PLECS_to_CCS_B.C_Script[5]
      };
      static float** outputs[] = {
         &outputPtrs[0], &outputPtrs[1], &outputPtrs[2], &outputPtrs[3],
         &outputPtrs[4], &outputPtrs[5]
      };
      static float nextSampleHit;
      static const char * sampleHits[] = {
         &PLECS_to_CCS_isMajorStep
      };
      static float sampleTimePeriods[] = {
         2e-05
      };
      static float sampleTimeOffsets[] = {
         0
      };
      static float terminalSampleTimePeriods[] = {
         0.f, 0.f, 0.f, 0.f, 0.f, 0.f
      };
      static float terminalSampleTimeOffsets[] = {
         -1.f, -1.f, -1.f, -1.f, -1.f, -1.f
      };
      static const float* terminalSampleTimePeriodPtrs[] = {
         &terminalSampleTimePeriods[0], &terminalSampleTimePeriods[1],
         &terminalSampleTimePeriods[2], &terminalSampleTimePeriods[3],
         &terminalSampleTimePeriods[4], &terminalSampleTimePeriods[5]
      };
      static const float* terminalSampleTimeOffsetPtrs[] = {
         &terminalSampleTimeOffsets[0], &terminalSampleTimeOffsets[1],
         &terminalSampleTimeOffsets[2], &terminalSampleTimeOffsets[3],
         &terminalSampleTimeOffsets[4], &terminalSampleTimeOffsets[5]
      };
      static const char* errorStatus;
      static const char* warningStatus;
      static const char* rangeErrorMsg;
      errorStatus = NULL;
      warningStatus = NULL;
      rangeErrorMsg = NULL;
      PLECS_to_CCS_cScriptStruct[0].isMajorTimeStep = 1;
      PLECS_to_CCS_cScriptStruct[0].numInputTerminals = 6;
      PLECS_to_CCS_cScriptStruct[0].numInputSignals = numInputSignals;
      PLECS_to_CCS_cScriptStruct[0].inputs = inputs;
      PLECS_to_CCS_cScriptStruct[0].numOutputTerminals = 6;
      PLECS_to_CCS_cScriptStruct[0].numOutputSignals = numOutputSignals;
      PLECS_to_CCS_cScriptStruct[0].outputs = outputs;
      PLECS_to_CCS_cScriptStruct[0].numContStates = 0;
      PLECS_to_CCS_cScriptStruct[0].contStates = NULL;
      PLECS_to_CCS_cScriptStruct[0].contDerivs = NULL;
      PLECS_to_CCS_cScriptStruct[0].numDiscStates = 0;
      PLECS_to_CCS_cScriptStruct[0].discStates = NULL;
      PLECS_to_CCS_cScriptStruct[0].numZCSignals = 0;
      PLECS_to_CCS_cScriptStruct[0].numParameters = 0;
      PLECS_to_CCS_cScriptStruct[0].paramNumDims = NULL;
      PLECS_to_CCS_cScriptStruct[0].paramDims = NULL;
      PLECS_to_CCS_cScriptStruct[0].paramNumElements = NULL;
      PLECS_to_CCS_cScriptStruct[0].paramRealData = NULL;
      PLECS_to_CCS_cScriptStruct[0].paramStringData = NULL;
      PLECS_to_CCS_cScriptStruct[0].numSampleTimes = 1;
      PLECS_to_CCS_cScriptStruct[0].sampleTimePeriods = sampleTimePeriods;
      PLECS_to_CCS_cScriptStruct[0].sampleTimeOffsets = sampleTimeOffsets;
      PLECS_to_CCS_cScriptStruct[0].inputSampleTimePeriods =
         terminalSampleTimePeriodPtrs;
      PLECS_to_CCS_cScriptStruct[0].inputSampleTimeOffsets =
         terminalSampleTimeOffsetPtrs;
      PLECS_to_CCS_cScriptStruct[0].sampleHits = sampleHits;
      PLECS_to_CCS_cScriptStruct[0].nextSampleHit = &nextSampleHit;
      PLECS_to_CCS_cScriptStruct[0].errorStatus = &errorStatus;
      PLECS_to_CCS_cScriptStruct[0].warningStatus = &warningStatus;
      PLECS_to_CCS_cScriptStruct[0].rangeErrorMsg = &rangeErrorMsg;
      PLECS_to_CCS_0_cScriptStart(&PLECS_to_CCS_cScriptStruct[0]);
      if (*PLECS_to_CCS_cScriptStruct[0].errorStatus)
         PLECS_to_CCS_errorStatus =
            *PLECS_to_CCS_cScriptStruct[0].errorStatus;
   }

   /* Initialization for C-Script : 'PLECS_to_CCS/Control Logic/MPPT Logic' */
   {
      static int numInputSignals[] = {
         1, 1, 1, 1
      };
      static const float* inputPtrs[] = {
         &PLECS_to_CCS_B.C_Script[3], &PLECS_to_CCS_B.C_Script[2],
         &PLECS_to_CCS_B.C_Script[4], &PLECS_to_CCS_B.C_Script[5]
      };
      static const float** inputs[] = {
         &inputPtrs[0], &inputPtrs[1], &inputPtrs[2], &inputPtrs[3]
      };
      static int numOutputSignals[] = {
         1
      };
      static float* outputPtrs[] = {
         &PLECS_to_CCS_B.MPPTLogic
      };
      static float** outputs[] = {
         &outputPtrs[0]
      };
      static float nextSampleHit;
      static const char * sampleHits[] = {
         &PLECS_to_CCS_isMajorStep
      };
      static float sampleTimePeriods[] = {
         2e-05
      };
      static float sampleTimeOffsets[] = {
         0
      };
      static float terminalSampleTimePeriods[] = {
         2e-05f, 2e-05f, 2e-05f, 2e-05f
      };
      static float terminalSampleTimeOffsets[] = {
         0.f, 0.f, 0.f, 0.f
      };
      static const float* terminalSampleTimePeriodPtrs[] = {
         &terminalSampleTimePeriods[0], &terminalSampleTimePeriods[1],
         &terminalSampleTimePeriods[2], &terminalSampleTimePeriods[3]
      };
      static const float* terminalSampleTimeOffsetPtrs[] = {
         &terminalSampleTimeOffsets[0], &terminalSampleTimeOffsets[1],
         &terminalSampleTimeOffsets[2], &terminalSampleTimeOffsets[3]
      };
      static const char* errorStatus;
      static const char* warningStatus;
      static const char* rangeErrorMsg;
      errorStatus = NULL;
      warningStatus = NULL;
      rangeErrorMsg = NULL;
      PLECS_to_CCS_cScriptStruct[1].isMajorTimeStep = 1;
      PLECS_to_CCS_cScriptStruct[1].numInputTerminals = 4;
      PLECS_to_CCS_cScriptStruct[1].numInputSignals = numInputSignals;
      PLECS_to_CCS_cScriptStruct[1].inputs = inputs;
      PLECS_to_CCS_cScriptStruct[1].numOutputTerminals = 1;
      PLECS_to_CCS_cScriptStruct[1].numOutputSignals = numOutputSignals;
      PLECS_to_CCS_cScriptStruct[1].outputs = outputs;
      PLECS_to_CCS_cScriptStruct[1].numContStates = 0;
      PLECS_to_CCS_cScriptStruct[1].contStates = NULL;
      PLECS_to_CCS_cScriptStruct[1].contDerivs = NULL;
      PLECS_to_CCS_cScriptStruct[1].numDiscStates = 0;
      PLECS_to_CCS_cScriptStruct[1].discStates = NULL;
      PLECS_to_CCS_cScriptStruct[1].numZCSignals = 0;
      PLECS_to_CCS_cScriptStruct[1].numParameters = 0;
      PLECS_to_CCS_cScriptStruct[1].paramNumDims = NULL;
      PLECS_to_CCS_cScriptStruct[1].paramDims = NULL;
      PLECS_to_CCS_cScriptStruct[1].paramNumElements = NULL;
      PLECS_to_CCS_cScriptStruct[1].paramRealData = NULL;
      PLECS_to_CCS_cScriptStruct[1].paramStringData = NULL;
      PLECS_to_CCS_cScriptStruct[1].numSampleTimes = 1;
      PLECS_to_CCS_cScriptStruct[1].sampleTimePeriods = sampleTimePeriods;
      PLECS_to_CCS_cScriptStruct[1].sampleTimeOffsets = sampleTimeOffsets;
      PLECS_to_CCS_cScriptStruct[1].inputSampleTimePeriods =
         terminalSampleTimePeriodPtrs;
      PLECS_to_CCS_cScriptStruct[1].inputSampleTimeOffsets =
         terminalSampleTimeOffsetPtrs;
      PLECS_to_CCS_cScriptStruct[1].sampleHits = sampleHits;
      PLECS_to_CCS_cScriptStruct[1].nextSampleHit = &nextSampleHit;
      PLECS_to_CCS_cScriptStruct[1].errorStatus = &errorStatus;
      PLECS_to_CCS_cScriptStruct[1].warningStatus = &warningStatus;
      PLECS_to_CCS_cScriptStruct[1].rangeErrorMsg = &rangeErrorMsg;
      PLECS_to_CCS_1_cScriptStart(&PLECS_to_CCS_cScriptStruct[1]);
      if (*PLECS_to_CCS_cScriptStruct[1].errorStatus)
         PLECS_to_CCS_errorStatus =
            *PLECS_to_CCS_cScriptStruct[1].errorStatus;
   }

   /* Initialization for Discrete Integrator : 'PLECS_to_CCS/Control Logic/MPPT PI/Discrete Time/Ki Integrator/Ki ~= 0/Discrete\nIntegrator/edge_triggered/Discrete\nIntegrator' */
   PLECS_to_CCS_X.DiscreteIntegrator_first = -1;
   PLECS_to_CCS_X.DiscreteIntegrator_i1_x = 0;
   PLECS_to_CCS_X.DiscreteIntegrator_i2_prevU = 0.f;
   PLECS_to_CCS_X.DiscreteIntegrator_i3_prevReset = 0.f;

   /* Initialization for Discrete Integrator : 'PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI/Discrete Time/Ki Integrator/Ki ~= 0/Discrete\nIntegrator/edge_triggered/Discrete\nIntegrator' */
   PLECS_to_CCS_X.DiscreteIntegrator_1_first = -1;
   PLECS_to_CCS_X.DiscreteIntegrator_1_i1_x = 0;
   PLECS_to_CCS_X.DiscreteIntegrator_1_i2_prevU = 0.f;
   PLECS_to_CCS_X.DiscreteIntegrator_1_i3_prevReset = 0.f;

   /* Initialization for C-Script : 'PLECS_to_CCS/Control Logic/State Machine' */
   {
      static int numInputSignals[] = {
         1, 1
      };
      static const float* inputPtrs[] = {
         &PLECS_to_CCS_B.C_Script[3], &PLECS_to_CCS_B.C_Script[4]
      };
      static const float** inputs[] = {
         &inputPtrs[0], &inputPtrs[1]
      };
      static int numOutputSignals[] = {
         1, 1
      };
      static float* outputPtrs[] = {
         &PLECS_to_CCS_B.StateMachine[0], &PLECS_to_CCS_B.StateMachine[1]
      };
      static float** outputs[] = {
         &outputPtrs[0], &outputPtrs[1]
      };
      static float nextSampleHit;
      static const char * sampleHits[] = {
         &PLECS_to_CCS_isMajorStep
      };
      static float sampleTimePeriods[] = {
         2e-05
      };
      static float sampleTimeOffsets[] = {
         0
      };
      static float terminalSampleTimePeriods[] = {
         2e-05f, 2e-05f
      };
      static float terminalSampleTimeOffsets[] = {
         0.f, 0.f
      };
      static const float* terminalSampleTimePeriodPtrs[] = {
         &terminalSampleTimePeriods[0], &terminalSampleTimePeriods[1]
      };
      static const float* terminalSampleTimeOffsetPtrs[] = {
         &terminalSampleTimeOffsets[0], &terminalSampleTimeOffsets[1]
      };
      static const char* errorStatus;
      static const char* warningStatus;
      static const char* rangeErrorMsg;
      errorStatus = NULL;
      warningStatus = NULL;
      rangeErrorMsg = NULL;
      PLECS_to_CCS_cScriptStruct[2].isMajorTimeStep = 1;
      PLECS_to_CCS_cScriptStruct[2].numInputTerminals = 2;
      PLECS_to_CCS_cScriptStruct[2].numInputSignals = numInputSignals;
      PLECS_to_CCS_cScriptStruct[2].inputs = inputs;
      PLECS_to_CCS_cScriptStruct[2].numOutputTerminals = 2;
      PLECS_to_CCS_cScriptStruct[2].numOutputSignals = numOutputSignals;
      PLECS_to_CCS_cScriptStruct[2].outputs = outputs;
      PLECS_to_CCS_cScriptStruct[2].numContStates = 0;
      PLECS_to_CCS_cScriptStruct[2].contStates = NULL;
      PLECS_to_CCS_cScriptStruct[2].contDerivs = NULL;
      PLECS_to_CCS_cScriptStruct[2].numDiscStates = 0;
      PLECS_to_CCS_cScriptStruct[2].discStates = NULL;
      PLECS_to_CCS_cScriptStruct[2].numZCSignals = 0;
      PLECS_to_CCS_cScriptStruct[2].numParameters = 0;
      PLECS_to_CCS_cScriptStruct[2].paramNumDims = NULL;
      PLECS_to_CCS_cScriptStruct[2].paramDims = NULL;
      PLECS_to_CCS_cScriptStruct[2].paramNumElements = NULL;
      PLECS_to_CCS_cScriptStruct[2].paramRealData = NULL;
      PLECS_to_CCS_cScriptStruct[2].paramStringData = NULL;
      PLECS_to_CCS_cScriptStruct[2].numSampleTimes = 1;
      PLECS_to_CCS_cScriptStruct[2].sampleTimePeriods = sampleTimePeriods;
      PLECS_to_CCS_cScriptStruct[2].sampleTimeOffsets = sampleTimeOffsets;
      PLECS_to_CCS_cScriptStruct[2].inputSampleTimePeriods =
         terminalSampleTimePeriodPtrs;
      PLECS_to_CCS_cScriptStruct[2].inputSampleTimeOffsets =
         terminalSampleTimeOffsetPtrs;
      PLECS_to_CCS_cScriptStruct[2].sampleHits = sampleHits;
      PLECS_to_CCS_cScriptStruct[2].nextSampleHit = &nextSampleHit;
      PLECS_to_CCS_cScriptStruct[2].errorStatus = &errorStatus;
      PLECS_to_CCS_cScriptStruct[2].warningStatus = &warningStatus;
      PLECS_to_CCS_cScriptStruct[2].rangeErrorMsg = &rangeErrorMsg;
      PLECS_to_CCS_2_cScriptStart(&PLECS_to_CCS_cScriptStruct[2]);
      if (*PLECS_to_CCS_cScriptStruct[2].errorStatus)
         PLECS_to_CCS_errorStatus =
            *PLECS_to_CCS_cScriptStruct[2].errorStatus;
   }

   /* Initialization for C-Script : 'PLECS_to_CCS/Control Logic/Routing Logic' */
   {
      static int numInputSignals[] = {
         1
      };
      static const float* inputPtrs[] = {
         &PLECS_to_CCS_B.Product3
      };
      static const float** inputs[] = {
         &inputPtrs[0]
      };
      static int numOutputSignals[] = {
         1, 1
      };
      static float* outputPtrs[] = {
         &PLECS_to_CCS_B.RoutingLogic[0], &PLECS_to_CCS_B.RoutingLogic[1]
      };
      static float** outputs[] = {
         &outputPtrs[0], &outputPtrs[1]
      };
      static float nextSampleHit;
      static const char * sampleHits[] = {
         &PLECS_to_CCS_isMajorStep
      };
      static float sampleTimePeriods[] = {
         2e-05
      };
      static float sampleTimeOffsets[] = {
         0
      };
      static float terminalSampleTimePeriods[] = {
         2e-05f
      };
      static float terminalSampleTimeOffsets[] = {
         0.f
      };
      static const float* terminalSampleTimePeriodPtrs[] = {
         &terminalSampleTimePeriods[0]
      };
      static const float* terminalSampleTimeOffsetPtrs[] = {
         &terminalSampleTimeOffsets[0]
      };
      static const char* errorStatus;
      static const char* warningStatus;
      static const char* rangeErrorMsg;
      errorStatus = NULL;
      warningStatus = NULL;
      rangeErrorMsg = NULL;
      PLECS_to_CCS_cScriptStruct[3].isMajorTimeStep = 1;
      PLECS_to_CCS_cScriptStruct[3].numInputTerminals = 1;
      PLECS_to_CCS_cScriptStruct[3].numInputSignals = numInputSignals;
      PLECS_to_CCS_cScriptStruct[3].inputs = inputs;
      PLECS_to_CCS_cScriptStruct[3].numOutputTerminals = 2;
      PLECS_to_CCS_cScriptStruct[3].numOutputSignals = numOutputSignals;
      PLECS_to_CCS_cScriptStruct[3].outputs = outputs;
      PLECS_to_CCS_cScriptStruct[3].numContStates = 0;
      PLECS_to_CCS_cScriptStruct[3].contStates = NULL;
      PLECS_to_CCS_cScriptStruct[3].contDerivs = NULL;
      PLECS_to_CCS_cScriptStruct[3].numDiscStates = 0;
      PLECS_to_CCS_cScriptStruct[3].discStates = NULL;
      PLECS_to_CCS_cScriptStruct[3].numZCSignals = 0;
      PLECS_to_CCS_cScriptStruct[3].numParameters = 0;
      PLECS_to_CCS_cScriptStruct[3].paramNumDims = NULL;
      PLECS_to_CCS_cScriptStruct[3].paramDims = NULL;
      PLECS_to_CCS_cScriptStruct[3].paramNumElements = NULL;
      PLECS_to_CCS_cScriptStruct[3].paramRealData = NULL;
      PLECS_to_CCS_cScriptStruct[3].paramStringData = NULL;
      PLECS_to_CCS_cScriptStruct[3].numSampleTimes = 1;
      PLECS_to_CCS_cScriptStruct[3].sampleTimePeriods = sampleTimePeriods;
      PLECS_to_CCS_cScriptStruct[3].sampleTimeOffsets = sampleTimeOffsets;
      PLECS_to_CCS_cScriptStruct[3].inputSampleTimePeriods =
         terminalSampleTimePeriodPtrs;
      PLECS_to_CCS_cScriptStruct[3].inputSampleTimeOffsets =
         terminalSampleTimeOffsetPtrs;
      PLECS_to_CCS_cScriptStruct[3].sampleHits = sampleHits;
      PLECS_to_CCS_cScriptStruct[3].nextSampleHit = &nextSampleHit;
      PLECS_to_CCS_cScriptStruct[3].errorStatus = &errorStatus;
      PLECS_to_CCS_cScriptStruct[3].warningStatus = &warningStatus;
      PLECS_to_CCS_cScriptStruct[3].rangeErrorMsg = &rangeErrorMsg;
      PLECS_to_CCS_3_cScriptStart(&PLECS_to_CCS_cScriptStruct[3]);
      if (*PLECS_to_CCS_cScriptStruct[3].errorStatus)
         PLECS_to_CCS_errorStatus =
            *PLECS_to_CCS_cScriptStruct[3].errorStatus;
   }

   /* Initialization for Discrete Integrator : 'PLECS_to_CCS/Control Logic/Buck Current PI/Discrete Time/Ki Integrator/Ki ~= 0/Discrete\nIntegrator/edge_triggered/Discrete\nIntegrator' */
   PLECS_to_CCS_X.DiscreteIntegrator_2_first = -1;
   PLECS_to_CCS_X.DiscreteIntegrator_2_i1_x = 0;
   PLECS_to_CCS_X.DiscreteIntegrator_2_i2_prevU = 0.f;
   PLECS_to_CCS_X.DiscreteIntegrator_2_i3_prevReset = 0.f;

   /* Initialization for Discrete Integrator : 'PLECS_to_CCS/Control Logic/Buck Voltage PI/Discrete Time/Ki Integrator/Ki ~= 0/Discrete\nIntegrator/edge_triggered/Discrete\nIntegrator' */
   PLECS_to_CCS_X.DiscreteIntegrator_3_first = -1;
   PLECS_to_CCS_X.DiscreteIntegrator_3_i1_x = 0;
   PLECS_to_CCS_X.DiscreteIntegrator_3_i2_prevU = 0.f;
   PLECS_to_CCS_X.DiscreteIntegrator_3_i3_prevReset = 0.f;

   /* Initialization for Discrete Integrator : 'PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI1/Discrete Time/Ki Integrator/Ki ~= 0/Discrete\nIntegrator/edge_triggered/Discrete\nIntegrator' */
   PLECS_to_CCS_X.DiscreteIntegrator_4_first = -1;
   PLECS_to_CCS_X.DiscreteIntegrator_4_i1_x = 0;
   PLECS_to_CCS_X.DiscreteIntegrator_4_i2_prevU = 0.f;
   PLECS_to_CCS_X.DiscreteIntegrator_4_i3_prevReset = 0.f;
}

void PLECS_to_CCS_step(void)
{

// 1. READ RAW ADC REGISTERS & SCALE TO PIN VOLTAGE (0-3.3V)

   
    // --- VOLTAGES (ADCB Module) ---
    // Pin 24: ADCINB0 -> PV Voltage
   v_pin_V_PV  = (float)AdcbResultRegs.ADCRESULT0 * (3.3f / 4096.0f); 
    
    // Pin 26: ADCINB1 -> Battery Voltage
   v_pin_V_Bat = (float)AdcbResultRegs.ADCRESULT1 * (3.3f / 4096.0f); 
    
    // Pin 27: ADCINB2 -> EV Voltage
    v_pin_V_EV  = (float)AdcbResultRegs.ADCRESULT2 * (3.3f / 4096.0f); 


    // --- CURRENTS (ADCC Module) ---
    // Pin 66: ADCINC1 -> PV Current
    v_pin_I_PV  = (float)AdccResultRegs.ADCRESULT0 * (3.3f / 4096.0f); 
    
    // Pin 67: ADCINC3 -> Battery Current
    v_pin_I_Bat = (float)AdccResultRegs.ADCRESULT1 * (3.3f / 4096.0f); 
    
    // Pin 68: ADCINC5 -> EV Current
    v_pin_I_EV  = (float)AdccResultRegs.ADCRESULT2 * (3.3f / 4096.0f); 


    // 2. SCALE PIN VOLTAGES TO Actual AMPS & VOLTS
   
    // --- Current Sensor Math (ACS725) ---
    ext_I_Bat = ((v_pin_I_Bat*7.6541f)-12.62f) ; // Bidirectional Storage
    ext_I_PV  = ((3.8549f*v_pin_I_PV)-1.2705f);   // Unidirectional PV
    ext_I_EV  = ((v_pin_I_EV*3.8358f)-1.2658f);   // Unidirectional EV

    // Current Sensor Noise Clamp 
    if (ext_I_PV < 0.0f) { ext_I_PV = 0.0f; }
    if (ext_I_EV < 0.0f) { ext_I_EV = 0.0f; }

    // --- Voltage Divider Math ---
    ext_V_PV  = v_pin_V_PV  * 7.353f; 
    ext_V_Bat = v_pin_V_Bat * 4.993f; 
    ext_V_EV  = v_pin_V_EV  * 2.480f; 
   

   /*
   ext_V_PV = 18.0f;
   ext_I_PV= 1.0f;
   ext_V_Bat = 12.5f;
   ext_I_Bat = 1.2f;
   ext_V_EV = 5.8f;
   ext_I_EV = 0.0f;
   */
    abcounter++;
      

    // ==========================================================
    // 3. TELEMETRY & I2C EXECUTION
    // ==========================================================
  // Run telemetry only once every 500 cycles (100 Hz instead of 50 kHz)
  // ==========================================================
    // 3. TELEMETRY & I2C EXECUTION
    // ==========================================================
    // Run telemetry only once every 500 cycles (100 Hz instead of 50 kHz)
    static uint16_t telemetry_tick = 0;
    if (++telemetry_tick >= 500) {
        update_telemetry_data();  
        telemetry_tick = 0;
            
    }
respond_to_ESP32();


   if (PLECS_to_CCS_errorStatus)
   {
      return;
   }
   {
      size_t i;
      for (i = 0; i < 1; ++i)
      {
         PLECS_to_CCS_subTaskHit[i] = (PLECS_to_CCS_subTaskTick[i] == 0);
      }
   }

   /* C-Script : 'PLECS_to_CCS/C-Script' */
   PLECS_to_CCS_0_cScriptOutput(&PLECS_to_CCS_cScriptStruct[0]);
   if (*PLECS_to_CCS_cScriptStruct[0].errorStatus)
      PLECS_to_CCS_errorStatus = *PLECS_to_CCS_cScriptStruct[0].errorStatus;

   /* C-Script : 'PLECS_to_CCS/Control Logic/MPPT Logic' */
   PLECS_to_CCS_1_cScriptOutput(&PLECS_to_CCS_cScriptStruct[1]);
   if (*PLECS_to_CCS_cScriptStruct[1].errorStatus)
      PLECS_to_CCS_errorStatus = *PLECS_to_CCS_cScriptStruct[1].errorStatus;

   /* Zero-Order Hold : 'PLECS_to_CCS/Control Logic/MPPT PI/Discrete Time/Zero-Order\nHold'
    * incorporates
    *  Sum : 'PLECS_to_CCS/Control Logic/Sum'
    */
   PLECS_to_CCS_B.Zero_OrderHold = -PLECS_to_CCS_B.MPPTLogic +
                                   PLECS_to_CCS_B.C_Script[3];

   /* Signal Switch : 'PLECS_to_CCS/Control Logic/Intial Condition'
    * incorporates
    *  Relational Operator : 'PLECS_to_CCS/Control Logic/MODE'
    *  Product : 'PLECS_to_CCS/Control Logic/Divide1'
    *  Sum : 'PLECS_to_CCS/Control Logic/Sum5'
    *  Constant : 'PLECS_to_CCS/Control Logic/Constant'
    *  Sum : 'PLECS_to_CCS/Control Logic/Subtract'
    *  Constant : 'PLECS_to_CCS/Control Logic/Duty'
    *  Product : 'PLECS_to_CCS/Control Logic/Divide2'
    */
   PLECS_to_CCS_B.IntialCondition =
      ((PLECS_to_CCS_B.C_Script[3] >=
        PLECS_to_CCS_B.C_Script[4]) != false) ? (PLECS_to_CCS_B.C_Script[4] /
                                                 (PLECS_to_CCS_B.C_Script[3] +
                                                  0.001f)) : (2.f -
                                                              (PLECS_to_CCS_B.
                                                               C_Script[3] /
   PLECS_to_CCS_B.C_Script[4]));

   /* Discrete Integrator : 'PLECS_to_CCS/Control Logic/MPPT PI/Discrete Time/Ki Integrator/Ki ~= 0/Discrete\nIntegrator/edge_triggered/Discrete\nIntegrator'
    * incorporates
    *  Constant : 'PLECS_to_CCS/Control Logic/MPPT PI/Reset select/None/Constant'
    */
   if (PLECS_to_CCS_X.DiscreteIntegrator_first < 0 ||
       (!PLECS_to_CCS_X.DiscreteIntegrator_i3_prevReset && 0.f))
   {
      PLECS_to_CCS_B.DiscreteIntegrator = PLECS_to_CCS_B.IntialCondition;
   }
   else if (PLECS_to_CCS_X.DiscreteIntegrator_first)
   {
      PLECS_to_CCS_B.DiscreteIntegrator =
         PLECS_to_CCS_X.DiscreteIntegrator_i1_x;
   }
   else
   {
      PLECS_to_CCS_B.DiscreteIntegrator =
         PLECS_to_CCS_X.DiscreteIntegrator_i1_x + 2e-05f*
         PLECS_to_CCS_X.DiscreteIntegrator_i2_prevU;
   }

   /* Sum : 'PLECS_to_CCS/Control Logic/MPPT PI/Discrete Time/Sum'
    * incorporates
    *  Product : 'PLECS_to_CCS/Control Logic/MPPT PI/Discrete Time/Product'
    *  Constant : 'PLECS_to_CCS/Control Logic/MPPT PI/Source Select/internal/Constant'
    *  Subsystem : 'PLECS_to_CCS'
    */
   PLECS_to_CCS_B.Sum =
      (PLECS_to_CCS_B.Zero_OrderHold *
       0.05f) + PLECS_to_CCS_UNCONNECTED + PLECS_to_CCS_B.DiscreteIntegrator;

   /* Saturation : 'PLECS_to_CCS/Control Logic/MPPT PI/Saturation/internal/Saturation Select/constant/Saturation' */
   PLECS_to_CCS_B.Saturation = PLECS_to_CCS_B.Sum;
   if (PLECS_to_CCS_B.Saturation > 1.95f)
   {
      PLECS_to_CCS_B.Saturation = 1.95f;
   }
   else if (PLECS_to_CCS_B.Saturation < 0.05f)
   {
      PLECS_to_CCS_B.Saturation = 0.05f;
   }
   if (PLECS_to_CCS_subTaskHit[0])
   {
      /* Zero-Order Hold : 'PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI/Discrete Time/Zero-Order\nHold'
       * incorporates
       *  Sum : 'PLECS_to_CCS/Control Logic/Sum3'
       *  Constant : 'PLECS_to_CCS/Control Logic/Storage Voltage Max'
       */
      PLECS_to_CCS_B.Zero_OrderHold_1 = 14.4f - PLECS_to_CCS_B.C_Script[4];

      /* Discrete Integrator : 'PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI/Discrete Time/Ki Integrator/Ki ~= 0/Discrete\nIntegrator/edge_triggered/Discrete\nIntegrator'
       * incorporates
       *  Constant : 'PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI/Reset select/None/Constant'
       *  Constant : 'PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI/Init select/internal/Constant'
       */
      if (PLECS_to_CCS_X.DiscreteIntegrator_1_first < 0 ||
          (!PLECS_to_CCS_X.DiscreteIntegrator_1_i3_prevReset && 0.f))
      {
         PLECS_to_CCS_B.DiscreteIntegrator_1 = 1.f;
      }
      else if (PLECS_to_CCS_X.DiscreteIntegrator_1_first)
      {
         PLECS_to_CCS_B.DiscreteIntegrator_1 =
            PLECS_to_CCS_X.DiscreteIntegrator_1_i1_x;
      }
      else
      {
         PLECS_to_CCS_B.DiscreteIntegrator_1 =
            PLECS_to_CCS_X.DiscreteIntegrator_1_i1_x + 0.00022f*
            PLECS_to_CCS_X.DiscreteIntegrator_1_i2_prevU;
      }

      /* Sum : 'PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI/Discrete Time/Sum'
       * incorporates
       *  Product : 'PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI/Discrete Time/Product'
       *  Constant : 'PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI/Source Select/internal/Constant'
       *  Subsystem : 'PLECS_to_CCS'
       */
      PLECS_to_CCS_B.Sum_1 =
         (PLECS_to_CCS_B.Zero_OrderHold_1 *
          0.05f) + PLECS_to_CCS_UNCONNECTED +
         PLECS_to_CCS_B.DiscreteIntegrator_1;

      /* Saturation : 'PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI/Saturation/internal/Saturation Select/constant/Saturation' */
      PLECS_to_CCS_B.Saturation_1 = PLECS_to_CCS_B.Sum_1;
      if (PLECS_to_CCS_B.Saturation_1 > 1.95f)
      {
         PLECS_to_CCS_B.Saturation_1 = 1.95f;
      }
      else if (PLECS_to_CCS_B.Saturation_1 < 0.f)
      {
         PLECS_to_CCS_B.Saturation_1 = 0.f;
      }
   }
   /* Minimum / Maximum : 'PLECS_to_CCS/Control Logic/Min' */
   {
      float u, y;
      y = PLECS_to_CCS_B.Saturation;
      u = PLECS_to_CCS_B.Saturation_1;
      if (u < y)
         y = u;
      PLECS_to_CCS_B.Min = y;
   }

   /* C-Script : 'PLECS_to_CCS/Control Logic/State Machine' */
   PLECS_to_CCS_2_cScriptOutput(&PLECS_to_CCS_cScriptStruct[2]);
   if (*PLECS_to_CCS_cScriptStruct[2].errorStatus)
      PLECS_to_CCS_errorStatus = *PLECS_to_CCS_cScriptStruct[2].errorStatus;

   /* Product : 'PLECS_to_CCS/Control Logic/Product3' */
   PLECS_to_CCS_B.Product3 = PLECS_to_CCS_B.Min *
                             PLECS_to_CCS_B.StateMachine[0];

   /* C-Script : 'PLECS_to_CCS/Control Logic/Routing Logic' */
   PLECS_to_CCS_3_cScriptOutput(&PLECS_to_CCS_cScriptStruct[3]);
   if (*PLECS_to_CCS_cScriptStruct[3].errorStatus)
      PLECS_to_CCS_errorStatus = *PLECS_to_CCS_cScriptStruct[3].errorStatus;

   /* PWM : 'PLECS_to_CCS/Leg1_Q1_Q2\nePWM1A & B' */
/* Compare to Constant : 'PLECS_to_CCS/Shut-Off_Leg_1' */
   PLECS_to_CCS_B.Shut_Off_Leg_1 = PLECS_to_CCS_B.RoutingLogic[0] > 0.04f;
   
   /* PWM : 'PLECS_to_CCS/Leg1_Q1_Q2\nePWM1A & B' */
   if((PLECS_to_CCS_B.Shut_Off_Leg_1) == 0)
   {
      PLXHAL_PWM_setToPassive(0);
   }
   else
   {
      PLXHAL_PWM_setDuty(0, PLECS_to_CCS_B.RoutingLogic[0]);
      PLXHAL_PWM_setToOperational(0);
   }

   /* Compare to Constant : 'PLECS_to_CCS/Shut-Off_Leg 2' */
   PLECS_to_CCS_B.Shut_Off_Leg2 = PLECS_to_CCS_B.RoutingLogic[1] > 0.04f;
   
   /* PWM : 'PLECS_to_CCS/Leg2_Q3_Q4\nePWM4A & B' */
   if((PLECS_to_CCS_B.Shut_Off_Leg2) == 0)
   {
      PLXHAL_PWM_setToPassive(1);
   }
   else
   {
      PLXHAL_PWM_setDuty(1, PLECS_to_CCS_B.RoutingLogic[1]);
      PLXHAL_PWM_setToOperational(1);
   }

   /* Zero-Order Hold : 'PLECS_to_CCS/Control Logic/Buck Current PI/Discrete Time/Zero-Order\nHold'
    * incorporates
    *  Sum : 'PLECS_to_CCS/Control Logic/Sum1'
    *  Constant : 'PLECS_to_CCS/Control Logic/EV target current'
    */
   PLECS_to_CCS_B.Zero_OrderHold_2 = 1.2f - PLECS_to_CCS_B.C_Script[0];

   /* Discrete Integrator : 'PLECS_to_CCS/Control Logic/Buck Current PI/Discrete Time/Ki Integrator/Ki ~= 0/Discrete\nIntegrator/edge_triggered/Discrete\nIntegrator'
    * incorporates
    *  Constant : 'PLECS_to_CCS/Control Logic/Buck Current PI/Reset select/None/Constant'
    *  Constant : 'PLECS_to_CCS/Control Logic/Buck Current PI/Init select/internal/Constant'
    */
   if (PLECS_to_CCS_X.DiscreteIntegrator_2_first < 0 ||
       (!PLECS_to_CCS_X.DiscreteIntegrator_2_i3_prevReset && 0.f))
   {
      PLECS_to_CCS_B.DiscreteIntegrator_2 = 0.f;
   }
   else if (PLECS_to_CCS_X.DiscreteIntegrator_2_first)
   {
      PLECS_to_CCS_B.DiscreteIntegrator_2 =
         PLECS_to_CCS_X.DiscreteIntegrator_2_i1_x;
   }
   else
   {
      PLECS_to_CCS_B.DiscreteIntegrator_2 =
         PLECS_to_CCS_X.DiscreteIntegrator_2_i1_x + 2e-05f*
         PLECS_to_CCS_X.DiscreteIntegrator_2_i2_prevU;
   }

   /* Sum : 'PLECS_to_CCS/Control Logic/Buck Current PI/Discrete Time/Sum'
    * incorporates
    *  Product : 'PLECS_to_CCS/Control Logic/Buck Current PI/Discrete Time/Product'
    *  Constant : 'PLECS_to_CCS/Control Logic/Buck Current PI/Source Select/internal/Constant'
    *  Subsystem : 'PLECS_to_CCS'
    */
   PLECS_to_CCS_B.Sum_2 =
      (PLECS_to_CCS_B.Zero_OrderHold_2 *
       0.05f) + PLECS_to_CCS_UNCONNECTED +
      PLECS_to_CCS_B.DiscreteIntegrator_2;

   /* Saturation : 'PLECS_to_CCS/Control Logic/Buck Current PI/Saturation/internal/Saturation Select/constant/Saturation' */
   PLECS_to_CCS_B.Saturation_2 = PLECS_to_CCS_B.Sum_2;
   if (PLECS_to_CCS_B.Saturation_2 > 0.7f)
   {
      PLECS_to_CCS_B.Saturation_2 = 0.7f;
   }
   else if (PLECS_to_CCS_B.Saturation_2 < 0.f)
   {
      PLECS_to_CCS_B.Saturation_2 = 0.f;
   }

   /* Zero-Order Hold : 'PLECS_to_CCS/Control Logic/Buck Voltage PI/Discrete Time/Zero-Order\nHold'
    * incorporates
    *  Sum : 'PLECS_to_CCS/Control Logic/Sum2'
    *  Constant : 'PLECS_to_CCS/Control Logic/Storage Voltage min'
    */
   PLECS_to_CCS_B.Zero_OrderHold_3 = PLECS_to_CCS_B.C_Script[4] - 10.f;

   /* Discrete Integrator : 'PLECS_to_CCS/Control Logic/Buck Voltage PI/Discrete Time/Ki Integrator/Ki ~= 0/Discrete\nIntegrator/edge_triggered/Discrete\nIntegrator'
    * incorporates
    *  Constant : 'PLECS_to_CCS/Control Logic/Buck Voltage PI/Reset select/None/Constant'
    *  Constant : 'PLECS_to_CCS/Control Logic/Buck Voltage PI/Init select/internal/Constant'
    */
   if (PLECS_to_CCS_X.DiscreteIntegrator_3_first < 0 ||
       (!PLECS_to_CCS_X.DiscreteIntegrator_3_i3_prevReset && 0.f))
   {
      PLECS_to_CCS_B.DiscreteIntegrator_3 = 0.f;
   }
   else if (PLECS_to_CCS_X.DiscreteIntegrator_3_first)
   {
      PLECS_to_CCS_B.DiscreteIntegrator_3 =
         PLECS_to_CCS_X.DiscreteIntegrator_3_i1_x;
   }
   else
   {
      PLECS_to_CCS_B.DiscreteIntegrator_3 =
         PLECS_to_CCS_X.DiscreteIntegrator_3_i1_x + 2e-05f*
         PLECS_to_CCS_X.DiscreteIntegrator_3_i2_prevU;
   }

   /* Sum : 'PLECS_to_CCS/Control Logic/Buck Voltage PI/Discrete Time/Sum'
    * incorporates
    *  Product : 'PLECS_to_CCS/Control Logic/Buck Voltage PI/Discrete Time/Product'
    *  Constant : 'PLECS_to_CCS/Control Logic/Buck Voltage PI/Source Select/internal/Constant'
    *  Subsystem : 'PLECS_to_CCS'
    */
   PLECS_to_CCS_B.Sum_3 =
      (PLECS_to_CCS_B.Zero_OrderHold_3 *
       0.05f) + PLECS_to_CCS_UNCONNECTED +
      PLECS_to_CCS_B.DiscreteIntegrator_3;

   /* Saturation : 'PLECS_to_CCS/Control Logic/Buck Voltage PI/Saturation/internal/Saturation Select/constant/Saturation' */
   PLECS_to_CCS_B.Saturation_3 = PLECS_to_CCS_B.Sum_3;
   if (PLECS_to_CCS_B.Saturation_3 > 0.95f)
   {
      PLECS_to_CCS_B.Saturation_3 = 0.95f;
   }
   else if (PLECS_to_CCS_B.Saturation_3 < 0.f)
   {
      PLECS_to_CCS_B.Saturation_3 = 0.f;
   }

   if (PLECS_to_CCS_subTaskHit[0])
   {
      /* Zero-Order Hold : 'PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI1/Discrete Time/Zero-Order\nHold'
       * incorporates
       *  Sum : 'PLECS_to_CCS/Control Logic/Sum4'
       *  Constant : 'PLECS_to_CCS/Control Logic/EV Voltage Max'
       */
      PLECS_to_CCS_B.Zero_OrderHold_4 = 7.4f - PLECS_to_CCS_B.C_Script[1];

      /* Discrete Integrator : 'PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI1/Discrete Time/Ki Integrator/Ki ~= 0/Discrete\nIntegrator/edge_triggered/Discrete\nIntegrator'
       * incorporates
       *  Constant : 'PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI1/Reset select/None/Constant'
       *  Constant : 'PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI1/Init select/internal/Constant'
       */
      if (PLECS_to_CCS_X.DiscreteIntegrator_4_first < 0 ||
          (!PLECS_to_CCS_X.DiscreteIntegrator_4_i3_prevReset && 0.f))
      {
         PLECS_to_CCS_B.DiscreteIntegrator_4 = 0.f;
      }
      else if (PLECS_to_CCS_X.DiscreteIntegrator_4_first)
      {
         PLECS_to_CCS_B.DiscreteIntegrator_4 =
            PLECS_to_CCS_X.DiscreteIntegrator_4_i1_x;
      }
      else
      {
         PLECS_to_CCS_B.DiscreteIntegrator_4 =
            PLECS_to_CCS_X.DiscreteIntegrator_4_i1_x + 0.00022f*
            PLECS_to_CCS_X.DiscreteIntegrator_4_i2_prevU;
      }

      /* Sum : 'PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI1/Discrete Time/Sum'
       * incorporates
       *  Product : 'PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI1/Discrete Time/Product'
       *  Constant : 'PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI1/Source Select/internal/Constant'
       *  Subsystem : 'PLECS_to_CCS'
       */
      PLECS_to_CCS_B.Sum_4 =
         (PLECS_to_CCS_B.Zero_OrderHold_4 *
          0.05f) + PLECS_to_CCS_UNCONNECTED +
         PLECS_to_CCS_B.DiscreteIntegrator_4;

      /* Saturation : 'PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI1/Saturation/internal/Saturation Select/constant/Saturation' */
      PLECS_to_CCS_B.Saturation_4 = PLECS_to_CCS_B.Sum_4;
      if (PLECS_to_CCS_B.Saturation_4 > 0.95f)
      {
         PLECS_to_CCS_B.Saturation_4 = 0.95f;
      }
      else if (PLECS_to_CCS_B.Saturation_4 < 0.f)
      {
         PLECS_to_CCS_B.Saturation_4 = 0.f;
      }
   }
  /* Minimum / Maximum : 'PLECS_to_CCS/Control Logic/Min\/Max' 
    * (Updated to cascade all 4 hardware limits)
    */
   {
      float u, y;
      y = PLECS_to_CCS_B.Saturation_2;        // 1. Buck Current PI Limit
      
      u = PLECS_to_CCS_B.Saturation_3;        // 2. Storage Min Voltage PI Limit
      if (u < y) y = u;
      
      u = 2.5f > PLECS_to_CCS_B.C_Script[0];  // 3. Hardware Overcurrent Relay (2.5A)
      if (u < y) y = u;
      
      u = PLECS_to_CCS_B.Saturation_4;        // 4. EV Max Voltage PI Limit
      if (u < y) y = u;
      
      PLECS_to_CCS_B.Min_Max = y;             // The absolute safest limit wins
   }

   /* Product : 'PLECS_to_CCS/Control Logic/Product' */
   // The safest duty cycle is now strictly multiplied by the On/Off State Machine
   PLECS_to_CCS_B.Product = PLECS_to_CCS_B.StateMachine[1] *
                            PLECS_to_CCS_B.Min_Max;

 /* Compare to Constant : 'PLECS_to_CCS/Shut-Off_Leg_3' */
   PLECS_to_CCS_B.Shut_Off_Leg_3 = PLECS_to_CCS_B.Product > 0.04f;
   
   /* PWM : 'PLECS_to_CCS/Buck_leg\nePWM2A & B' */
   if((PLECS_to_CCS_B.Shut_Off_Leg_3) == 0)
   {
      PLXHAL_PWM_setToPassive(2);
   }
   else
   {
      PLXHAL_PWM_setDuty(2, PLECS_to_CCS_B.Product);
      PLXHAL_PWM_setToOperational(2);
   }
   
   /* ADC : 'PLECS_to_CCS/Current ADC' */
   PLECS_to_CCS_B.CurrentADC[0] = PLXHAL_ADC_getIn(0, 0);
   PLECS_to_CCS_B.CurrentADC[1] = PLXHAL_ADC_getIn(0, 1);
   PLECS_to_CCS_B.CurrentADC[2] = PLXHAL_ADC_getIn(0, 2);

   /* ADC : 'PLECS_to_CCS/Voltage ADC' */
   PLECS_to_CCS_B.VoltageADC[0] = PLXHAL_ADC_getIn(1, 0);
   PLECS_to_CCS_B.VoltageADC[1] = PLXHAL_ADC_getIn(1, 1);
   PLECS_to_CCS_B.VoltageADC[2] = PLXHAL_ADC_getIn(1, 2);
   if (PLECS_to_CCS_errorStatus)
   {
      return;
   }

   /* Update for C-Script : 'PLECS_to_CCS/C-Script' */
   PLECS_to_CCS_0_cScriptUpdate(&PLECS_to_CCS_cScriptStruct[0]);
   if (*PLECS_to_CCS_cScriptStruct[0].errorStatus)
      PLECS_to_CCS_errorStatus = *PLECS_to_CCS_cScriptStruct[0].errorStatus;

   /* Update for C-Script : 'PLECS_to_CCS/Control Logic/MPPT Logic' */
   PLECS_to_CCS_1_cScriptUpdate(&PLECS_to_CCS_cScriptStruct[1]);
   if (*PLECS_to_CCS_cScriptStruct[1].errorStatus)
      PLECS_to_CCS_errorStatus = *PLECS_to_CCS_cScriptStruct[1].errorStatus;

   /* Update for Discrete Integrator : 'PLECS_to_CCS/Control Logic/MPPT PI/Discrete Time/Ki Integrator/Ki ~= 0/Discrete\nIntegrator/edge_triggered/Discrete\nIntegrator'
    * incorporates
    *  Sum : 'PLECS_to_CCS/Control Logic/MPPT PI/Discrete Time/Sum2'
    *  Product : 'PLECS_to_CCS/Control Logic/MPPT PI/Discrete Time/Product4'
    *  Constant : 'PLECS_to_CCS/Control Logic/MPPT PI/Source Select/internal/Constant1'
    *  Constant : 'PLECS_to_CCS/Control Logic/MPPT PI/Anti-windup\nmethod/Back-Calculation/Constant'
    *  Product : 'PLECS_to_CCS/Control Logic/MPPT PI/Anti-windup\nmethod/Back-Calculation/Product'
    *  Sum : 'PLECS_to_CCS/Control Logic/MPPT PI/Anti-windup\nmethod/Back-Calculation/Sum'
    *  Constant : 'PLECS_to_CCS/Control Logic/MPPT PI/Source Select/internal/Anti-windup\nmethod/Back-Calculation/Constant'
    *  Constant : 'PLECS_to_CCS/Control Logic/MPPT PI/Reset select/None/Constant'
    */
   PLECS_to_CCS_X.DiscreteIntegrator_first = 0;
   PLECS_to_CCS_X.DiscreteIntegrator_i1_x = PLECS_to_CCS_B.DiscreteIntegrator;
   PLECS_to_CCS_X.DiscreteIntegrator_i2_prevU =
      (PLECS_to_CCS_B.Zero_OrderHold * 1.f *
       1.f) + ((-PLECS_to_CCS_B.Sum + PLECS_to_CCS_B.Saturation) * 1.f);
   PLECS_to_CCS_X.DiscreteIntegrator_i3_prevReset = !!(0.f);
   if (PLECS_to_CCS_subTaskHit[0])
   {
      /* Update for Discrete Integrator : 'PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI/Discrete Time/Ki Integrator/Ki ~= 0/Discrete\nIntegrator/edge_triggered/Discrete\nIntegrator'
       * incorporates
       *  Sum : 'PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI/Discrete Time/Sum2'
       *  Product : 'PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI/Discrete Time/Product4'
       *  Constant : 'PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI/Source Select/internal/Constant1'
       *  Constant : 'PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI/Anti-windup\nmethod/Back-Calculation/Constant'
       *  Product : 'PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI/Anti-windup\nmethod/Back-Calculation/Product'
       *  Sum : 'PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI/Anti-windup\nmethod/Back-Calculation/Sum'
       *  Constant : 'PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI/Source Select/internal/Anti-windup\nmethod/Back-Calculation/Constant'
       *  Constant : 'PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI/Reset select/None/Constant'
       */
      PLECS_to_CCS_X.DiscreteIntegrator_1_first = 0;
      PLECS_to_CCS_X.DiscreteIntegrator_1_i1_x =
         PLECS_to_CCS_B.DiscreteIntegrator_1;
      PLECS_to_CCS_X.DiscreteIntegrator_1_i2_prevU =
         (PLECS_to_CCS_B.Zero_OrderHold_1 * 1.f *
          1.f) +
         ((-PLECS_to_CCS_B.Sum_1 + PLECS_to_CCS_B.Saturation_1) * 1.f);
      PLECS_to_CCS_X.DiscreteIntegrator_1_i3_prevReset = !!(0.f);
   }
   /* Update for C-Script : 'PLECS_to_CCS/Control Logic/State Machine' */
   PLECS_to_CCS_2_cScriptUpdate(&PLECS_to_CCS_cScriptStruct[2]);
   if (*PLECS_to_CCS_cScriptStruct[2].errorStatus)
      PLECS_to_CCS_errorStatus = *PLECS_to_CCS_cScriptStruct[2].errorStatus;

   /* Update for C-Script : 'PLECS_to_CCS/Control Logic/Routing Logic' */
   PLECS_to_CCS_3_cScriptUpdate(&PLECS_to_CCS_cScriptStruct[3]);
   if (*PLECS_to_CCS_cScriptStruct[3].errorStatus)
      PLECS_to_CCS_errorStatus = *PLECS_to_CCS_cScriptStruct[3].errorStatus;

   /* Update for PWM : 'PLECS_to_CCS/Leg1_Q1_Q2\nePWM1A & B' */
   PLXHAL_PWM_enableAllOutputs();
   /* Update for Discrete Integrator : 'PLECS_to_CCS/Control Logic/Buck Current PI/Discrete Time/Ki Integrator/Ki ~= 0/Discrete\nIntegrator/edge_triggered/Discrete\nIntegrator'
    * incorporates
    *  Sum : 'PLECS_to_CCS/Control Logic/Buck Current PI/Discrete Time/Sum2'
    *  Product : 'PLECS_to_CCS/Control Logic/Buck Current PI/Discrete Time/Product4'
    *  Constant : 'PLECS_to_CCS/Control Logic/Buck Current PI/Source Select/internal/Constant1'
    *  Constant : 'PLECS_to_CCS/Control Logic/Buck Current PI/Anti-windup\nmethod/Back-Calculation/Constant'
    *  Product : 'PLECS_to_CCS/Control Logic/Buck Current PI/Anti-windup\nmethod/Back-Calculation/Product'
    *  Sum : 'PLECS_to_CCS/Control Logic/Buck Current PI/Anti-windup\nmethod/Back-Calculation/Sum'
    *  Constant : 'PLECS_to_CCS/Control Logic/Buck Current PI/Source Select/internal/Anti-windup\nmethod/Back-Calculation/Constant'
    *  Constant : 'PLECS_to_CCS/Control Logic/Buck Current PI/Reset select/None/Constant'
    */
   PLECS_to_CCS_X.DiscreteIntegrator_2_first = 0;
   PLECS_to_CCS_X.DiscreteIntegrator_2_i1_x =
      PLECS_to_CCS_B.DiscreteIntegrator_2;
   PLECS_to_CCS_X.DiscreteIntegrator_2_i2_prevU =
      (PLECS_to_CCS_B.Zero_OrderHold_2 * 0.3f *
       1.f) + ((-PLECS_to_CCS_B.Sum_2 + PLECS_to_CCS_B.Saturation_2) * 1.f);
   PLECS_to_CCS_X.DiscreteIntegrator_2_i3_prevReset = !!(0.f);

   /* Update for Discrete Integrator : 'PLECS_to_CCS/Control Logic/Buck Voltage PI/Discrete Time/Ki Integrator/Ki ~= 0/Discrete\nIntegrator/edge_triggered/Discrete\nIntegrator'
    * incorporates
    *  Sum : 'PLECS_to_CCS/Control Logic/Buck Voltage PI/Discrete Time/Sum2'
    *  Product : 'PLECS_to_CCS/Control Logic/Buck Voltage PI/Discrete Time/Product4'
    *  Constant : 'PLECS_to_CCS/Control Logic/Buck Voltage PI/Source Select/internal/Constant1'
    *  Constant : 'PLECS_to_CCS/Control Logic/Buck Voltage PI/Anti-windup\nmethod/Back-Calculation/Constant'
    *  Product : 'PLECS_to_CCS/Control Logic/Buck Voltage PI/Anti-windup\nmethod/Back-Calculation/Product'
    *  Sum : 'PLECS_to_CCS/Control Logic/Buck Voltage PI/Anti-windup\nmethod/Back-Calculation/Sum'
    *  Constant : 'PLECS_to_CCS/Control Logic/Buck Voltage PI/Source Select/internal/Anti-windup\nmethod/Back-Calculation/Constant'
    *  Constant : 'PLECS_to_CCS/Control Logic/Buck Voltage PI/Reset select/None/Constant'
    */
   PLECS_to_CCS_X.DiscreteIntegrator_3_first = 0;
   PLECS_to_CCS_X.DiscreteIntegrator_3_i1_x =
      PLECS_to_CCS_B.DiscreteIntegrator_3;
   PLECS_to_CCS_X.DiscreteIntegrator_3_i2_prevU =
      (PLECS_to_CCS_B.Zero_OrderHold_3 * 1.f *
       1.f) + ((-PLECS_to_CCS_B.Sum_3 + PLECS_to_CCS_B.Saturation_3) * 1.f);
   PLECS_to_CCS_X.DiscreteIntegrator_3_i3_prevReset = !!(0.f);
   if (PLECS_to_CCS_subTaskHit[0])
   {
      /* Update for Discrete Integrator : 'PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI1/Discrete Time/Ki Integrator/Ki ~= 0/Discrete\nIntegrator/edge_triggered/Discrete\nIntegrator'
       * incorporates
       *  Sum : 'PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI1/Discrete Time/Sum2'
       *  Product : 'PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI1/Discrete Time/Product4'
       *  Constant : 'PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI1/Source Select/internal/Constant1'
       *  Constant : 'PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI1/Anti-windup\nmethod/Back-Calculation/Constant'
       *  Product : 'PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI1/Anti-windup\nmethod/Back-Calculation/Product'
       *  Sum : 'PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI1/Anti-windup\nmethod/Back-Calculation/Sum'
       *  Constant : 'PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI1/Source Select/internal/Anti-windup\nmethod/Back-Calculation/Constant'
       *  Constant : 'PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI1/Reset select/None/Constant'
       */
      PLECS_to_CCS_X.DiscreteIntegrator_4_first = 0;
      PLECS_to_CCS_X.DiscreteIntegrator_4_i1_x =
         PLECS_to_CCS_B.DiscreteIntegrator_4;
      PLECS_to_CCS_X.DiscreteIntegrator_4_i2_prevU =
         (PLECS_to_CCS_B.Zero_OrderHold_4 * 1.f *
          1.f) +
         ((-PLECS_to_CCS_B.Sum_4 + PLECS_to_CCS_B.Saturation_4) * 1.f);
      PLECS_to_CCS_X.DiscreteIntegrator_4_i3_prevReset = !!(0.f);
   }

   /* Increment sub-task tick counters */
   {
      size_t i;
      for (i = 0; i < 1; ++i)
      {
         PLECS_to_CCS_subTaskTick[i]++;
         if (PLECS_to_CCS_subTaskTick[i] >= PLECS_to_CCS_subTaskPeriod[i])
         {
            PLECS_to_CCS_subTaskTick[i] = 0;
         }
      }
   }
}

void PLECS_to_CCS_terminate(void)
{
   /* Target termination */
#pragma diag_default 552

   /* Termination for C-Script : 'PLECS_to_CCS/C-Script' */
   PLECS_to_CCS_0_cScriptTerminate(&PLECS_to_CCS_cScriptStruct[0]);
   if (*PLECS_to_CCS_cScriptStruct[0].errorStatus)
      PLECS_to_CCS_errorStatus = *PLECS_to_CCS_cScriptStruct[0].errorStatus;
   /* Termination for C-Script : 'PLECS_to_CCS/Control Logic/MPPT Logic' */
   PLECS_to_CCS_1_cScriptTerminate(&PLECS_to_CCS_cScriptStruct[1]);
   if (*PLECS_to_CCS_cScriptStruct[1].errorStatus)
      PLECS_to_CCS_errorStatus = *PLECS_to_CCS_cScriptStruct[1].errorStatus;
   /* Termination for C-Script : 'PLECS_to_CCS/Control Logic/State Machine' */
   PLECS_to_CCS_2_cScriptTerminate(&PLECS_to_CCS_cScriptStruct[2]);
   if (*PLECS_to_CCS_cScriptStruct[2].errorStatus)
      PLECS_to_CCS_errorStatus = *PLECS_to_CCS_cScriptStruct[2].errorStatus;
   /* Termination for C-Script : 'PLECS_to_CCS/Control Logic/Routing Logic' */
   PLECS_to_CCS_3_cScriptTerminate(&PLECS_to_CCS_cScriptStruct[3]);
   if (*PLECS_to_CCS_cScriptStruct[3].errorStatus)
      PLECS_to_CCS_errorStatus = *PLECS_to_CCS_cScriptStruct[3].errorStatus;
}
