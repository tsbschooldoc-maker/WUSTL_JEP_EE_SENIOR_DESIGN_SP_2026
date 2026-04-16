/*
 * C-Script file for: PLECS_to_CCS/Control Logic/MPPT Logic
 * Generated with   : PLECS 4.9.8
 * Generated on     : 10 Apr 2026 19:05:08
 */
typedef float real_t;
#define REAL_MAX FLT_MAX
#define REAL_MIN FLT_MIN
#define REAL_EPSILON FLT_EPSILON
static float P_previous = 0.0;
static float V_previous = 0.0;
static float V_ref = 0; // Start at 0V
static int initialized = 0;
static float Step = 0.01;   // Move 0.001V at a time
// Declare the counter and initialize it to 0
static int slow_loop_counter = 0;

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

void PLECS_to_CCS_1_cScriptStart(const struct CScriptStruct *cScriptStruct)
{
}

#pragma CODE_SECTION(PLECS_to_CCS_1_cScriptOutput, "ramfuncs")



void PLECS_to_CCS_1_cScriptOutput(const struct CScriptStruct *cScriptStruct)
{
   // 1. Read Inputs (happens at full 50 kHz)
   float V_pv = InputSignal(0, 0);
   float I_pv = InputSignal(1, 0);

   // 2. Multirate Counter
   slow_loop_counter++;

   // Run the MPPT logic at 100 Hz (Every 500th cycle)
   if (slow_loop_counter >= 500)
   {

      float Power = V_pv * I_pv;

      // Physical implementation V_ref startup
      if (initialized == 0)
      {
         V_ref = V_pv; // record starting pv voltage
         initialized = 1;    // Never run this block again
      }

      // Only run P&O if power flow is above 0.5 W
      if (Power > 0.5)
      {
         float dP = Power - P_previous;
         float dV = V_pv - V_previous;

         if (dP > 0)
         {
            if (dV > 0)
               V_ref += Step;
            else
               V_ref -= Step;
         }
         else
         {
            if (dV > 0)
               V_ref -= Step;
            else
               V_ref += Step;
         }
      }
      // Kickstart - If power is zero, slowly crawl down to find the knee
      else
      {
         V_ref -= 0.01; //step to avoid overshooting
      }

      // Clamping
      if (V_ref > 20.0)
         V_ref = 20.0;              // Voc
      if (V_ref < 5.0)
         V_ref = 5.0;

      // Save history for the next 100 Hz cycle
      P_previous = Power;
      V_previous = V_pv;

      // Reset the counter
      slow_loop_counter = 0;
   }

   // 3. Write Output to the PI Loop (happens at full 50 kHz)
   OutputSignal(0, 0) = V_ref;
}

void PLECS_to_CCS_1_cScriptUpdate(const struct CScriptStruct *cScriptStruct)
{
}

void PLECS_to_CCS_1_cScriptDerivative(
                                      const struct CScriptStruct *cScriptStruct)
{
}

void PLECS_to_CCS_1_cScriptTerminate(const struct CScriptStruct *cScriptStruct)
{
}
