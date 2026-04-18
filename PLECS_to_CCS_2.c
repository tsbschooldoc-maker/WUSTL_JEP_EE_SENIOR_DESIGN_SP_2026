/*
 * C-Script file for: PLECS_to_CCS/Control Logic/State Machine
 * Generated with   : PLECS 4.9.8
 * Generated on     : 10 Apr 2026 19:05:08
 */
typedef float real_t;
#define REAL_MAX FLT_MAX
#define REAL_MIN FLT_MIN
#define REAL_EPSILON FLT_EPSILON
// State Machine Thresholds
float V_PV_MIN  = 5.0;      // Minimum voltage from PV
float V_Storage_Max = 14.4;   // 100% SOC for Storage
float V_Storage_Min = 10;   // 20% SOC (Low Voltage Disconnect)
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
    // 1. Read Inputs
    float Voltage_Pv = InputSignal(0, 0);
    float Voltage_Bat = InputSignal(1, 0);

    // 2. State Memory & Counter (MUST BE STATIC!)
    static float enable_4sw = 0.0;
    static float enable_buck = 0.0;
    static int state_counter = 0;

    // Increment counter
    state_counter++;

    // 3. Run State Machine at 100 Hz (Every 500th tick of the 50 kHz loop)
    if (state_counter >= 500) 
    {
        if (Voltage_Pv < V_PV_MIN) {
            enable_4sw = 0.0; 
            if (Voltage_Bat > V_Storage_Min) {
                enable_buck = 1.0; 
            } else {
                enable_buck = 0.0;
            }
        } 
        else {
            enable_4sw = 1.0; 
            enable_buck = 1.0; 
        }
        
        // Reset the counter
        state_counter = 0;
    }

    // 4. Outputs (Written to the Routing Logic at full 50 kHz using the saved memory)
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
