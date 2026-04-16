/*
 * C-Script file for: PLECS_to_CCS/Control Logic/State Machine
 * Generated with   : PLECS 4.9.8
 * Generated on     : 10 Apr 2026 19:05:08
 */
typedef float real_t;
#define REAL_MAX FLT_MAX
#define REAL_MIN FLT_MIN
#define REAL_EPSILON FLT_EPSILON
// Multirate Counter for 100 Hz execution
static int state_loop_counter = 0;

// State Machine Thresholds
static const float V_PV_MIN      = 5.0f;  // Minimum voltage from PV
//static const float V_Storage_Max = 14.4f; // 100% SOC for Storage
static const float V_Storage_Min = 11.0f; // 20% SOC (Low Voltage Disconnect)
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
#define NumInputTerminals cScriptStruct->numInputTerminals
#define NumOutputTerminals cScriptStruct->numOutputTerminals
#define NumInputSignals(terminalIdx) cScriptStruct->numInputSignals[ \
      terminalIdx]
#define NumOutputSignals(terminalIdx) cScriptStruct->numOutputSignals[ \
      terminalIdx]
#define InputSignal(terminalIdx, \
                    signalIdx) (*cScriptStruct->inputs[terminalIdx][signalIdx])
#define OutputSignal(terminalIdx, \
                     signalIdx) (*cScriptStruct->outputs[terminalIdx][ \
                                    signalIdx])
#define NumContStates cScriptStruct->numContStates
#define NumDiscStates cScriptStruct->numDiscStates
#define NumZCSignals cScriptStruct->numZCSignals
#define NumParameters cScriptStruct->numParameters
#define NumSampleTimes cScriptStruct->numSampleTimes
#define IsMajorStep cScriptStruct->isMajorTimeStep
#define CurrentTime cScriptStruct->time
#define NextSampleHit (*cScriptStruct->nextSampleHit)
#define SetErrorMessage(string) { *cScriptStruct->errorStatus=(string); }
#define SetWarningMessage(string)
#define ContState(idx) cScriptStruct->contStates[idx]
#define ContDeriv(idx) cScriptStruct->contDerivs[idx]
#define DiscState(idx) cScriptStruct->discStates[idx]
#define ZCSignal(idx) cScriptStruct->zCSignals[idx]
#define IsSampleHit(idx) (*cScriptStruct->sampleHits[idx])
#define SampleTimePeriod(idx) cScriptStruct->sampleTimePeriods[idx]
#define SampleTimeOffset(idx) cScriptStruct->sampleTimeOffsets[idx]
#define InputSampleTimePeriod(terminalIdx, \
                              signalIdx) cScriptStruct->inputSampleTimePeriods \
   [terminalIdx][signalIdx]
#define InputSampleTimeOffset(terminalIdx, \
                              signalIdx) cScriptStruct->inputSampleTimeOffsets \
   [terminalIdx][signalIdx]
#define ParamNumDims(idx) cScriptStruct->paramNumDims[idx]
#define ParamDim(pIdx, dIdx) cScriptStruct->paramDims[pIdx][dIdx]
#define ParamRealData(pIdx, dIdx) cScriptStruct->paramRealData[pIdx][dIdx]
#define ParamStringData(pIdx) cScriptStruct->paramStringData[pIdx]

void PLECS_to_CCS_2_cScriptStart(const struct CScriptStruct *cScriptStruct)
{
}

#pragma CODE_SECTION(PLECS_to_CCS_2_cScriptOutput, "ramfuncs")


void PLECS_to_CCS_2_cScriptOutput(const struct CScriptStruct *cScriptStruct)
{
   // 1. Read Inputs (happens at full 50 kHz)
   float Voltage_Pv = InputSignal(0, 0);
   float Voltage_Bat = InputSignal(1, 0);

   // Default state variables
   float enable_4sw = 0.0f;
   float enable_buck = 0.0f;

   // 2. Multirate Counter
   state_loop_counter++;

   // Run the State Machine logic at 100 Hz (Every 500th cycle)
   if (state_loop_counter >= 500)
   {

      // 3. Evaluate Conditions
      if (Voltage_Pv < V_PV_MIN)
      {
         // No power from PV panel, keep 4-Switch converter off
         enable_4sw = 0.0f;

         if (Voltage_Bat > V_Storage_Min)
         {
            // Mode 4: No panel output, Storage has SOC to give
            enable_buck = 1.0f;
         }
         else
         {
            // Mode 6: No panel output, Storage has no SOC to give
            enable_buck = 0.0f;
         }
      }
      else
      {
         // PV panel has more than min voltage
         enable_4sw = 1.0f;

         // In modes 2, 3, and 5 the Buck is enabled.
         // Throttling is handled by the external Min block.
         enable_buck = 1.0f;
      }

      // Reset the counter
      state_loop_counter = 0;
   }

   // 4. Outputs (Written to the pins at full 50 kHz)
   OutputSignal(0, 0) = enable_4sw;
   OutputSignal(1, 0) = enable_buck;
}


void PLECS_to_CCS_2_cScriptUpdate(const struct CScriptStruct *cScriptStruct)
{
}

void PLECS_to_CCS_2_cScriptDerivative(
                                      const struct CScriptStruct *cScriptStruct)
{
}

void PLECS_to_CCS_2_cScriptTerminate(const struct CScriptStruct *cScriptStruct)
{
}
