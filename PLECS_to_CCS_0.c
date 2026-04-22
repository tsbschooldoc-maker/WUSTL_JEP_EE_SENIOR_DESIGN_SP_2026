/*
 * C-Script file for: PLECS_to_CCS/C-Script
 * Generated with   : PLECS 4.9.8
 * Generated on     : 10 Apr 2026 19:05:08
 */
typedef float real_t;
#define REAL_MAX FLT_MAX
#define REAL_MIN FLT_MIN
#define REAL_EPSILON FLT_EPSILON
 float ext_V_EV = 0.0f;
 float ext_I_EV = 0.0f;
 float ext_V_PV = 0.0f;
 float ext_I_PV = 0.0f;
 float ext_V_Bat = 0.0f;
 float ext_I_Bat = 0.0f;
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

void PLECS_to_CCS_0_cScriptStart(const struct CScriptStruct *cScriptStruct)
{
}

#pragma CODE_SECTION(PLECS_to_CCS_0_cScriptOutput, "ramfuncs")

void PLECS_to_CCS_0_cScriptOutput(const struct CScriptStruct *cScriptStruct)
{
   OutputSignal(0, 0) = ext_I_EV; // Pin 1
   OutputSignal(1, 0) = ext_V_EV; // Pin 2
   OutputSignal(2, 0) = ext_I_PV; // Pin 3
   OutputSignal(3, 0) = ext_V_PV; // Pin 4
   OutputSignal(4, 0) = ext_V_Bat; // Pin 5
   OutputSignal(5, 0) = ext_I_Bat; // Pin 6
}

#pragma CODE_SECTION(PLECS_to_CCS_0_cScriptUpdate, "ramfuncs")
void PLECS_to_CCS_0_cScriptUpdate(const struct CScriptStruct *cScriptStruct)
{
   
}

void PLECS_to_CCS_0_cScriptDerivative(
                                      const struct CScriptStruct *cScriptStruct)
{
}

void PLECS_to_CCS_0_cScriptTerminate(const struct CScriptStruct *cScriptStruct)
{
}
