/*
 * Header file for: PLECS_to_CCS
 * Generated with : PLECS 4.9.8
 *                  TI28004x 2.2.1
 * Generated on   : 10 Apr 2026 19:05:08
 */
#ifndef PLECS_HEADER_PLECS_to_CCS_h_
#define PLECS_HEADER_PLECS_to_CCS_h_

#include <stdbool.h>
#include <stdint.h>

/* Target typedefs */
typedef int_fast8_t int8_t;
typedef uint_fast8_t uint8_t;


/* Model floating point type */
typedef float PLECS_to_CCS_FloatType;

/* Target declarations */
extern void PLECS_to_CCS_background(void);
#pragma diag_suppress 552


/* Model checksum */
extern const char * const PLECS_to_CCS_checksum;

/* Model error status */
extern const char * PLECS_to_CCS_errorStatus;


/* Model sample time */
extern const float PLECS_to_CCS_sampleTime;


/*
 * Model states */
typedef struct
{
   int8_t DiscreteIntegrator_first; /* PLECS_to_CCS/Control Logic/MPPT PI/Discrete Time/Ki Integrator/Ki ~= 0/Discrete Integrator/edge_triggered/Discrete Integrator */
   float DiscreteIntegrator_i1_x;   /* PLECS_to_CCS/Control Logic/MPPT PI/Discrete Time/Ki Integrator/Ki ~= 0/Discrete Integrator/edge_triggered/Discrete Integrator */
   float DiscreteIntegrator_i2_prevU; /* PLECS_to_CCS/Control Logic/MPPT PI/Discrete Time/Ki Integrator/Ki ~= 0/Discrete Integrator/edge_triggered/Discrete Integrator */
   bool DiscreteIntegrator_i3_prevReset; /* PLECS_to_CCS/Control Logic/MPPT PI/Discrete Time/Ki Integrator/Ki ~= 0/Discrete Integrator/edge_triggered/Discrete Integrator */
   int8_t DiscreteIntegrator_1_first; /* PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI/Discrete Time/Ki Integrator/Ki ~= 0/Discrete Integrator/edge_triggered/Discrete Integrator */
   float DiscreteIntegrator_1_i1_x; /* PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI/Discrete Time/Ki Integrator/Ki ~= 0/Discrete Integrator/edge_triggered/Discrete Integrator */
   float DiscreteIntegrator_1_i2_prevU; /* PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI/Discrete Time/Ki Integrator/Ki ~= 0/Discrete Integrator/edge_triggered/Discrete Integrator */
   bool DiscreteIntegrator_1_i3_prevReset; /* PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI/Discrete Time/Ki Integrator/Ki ~= 0/Discrete Integrator/edge_triggered/Discrete Integrator */
   int8_t DiscreteIntegrator_2_first; /* PLECS_to_CCS/Control Logic/Buck Current PI/Discrete Time/Ki Integrator/Ki ~= 0/Discrete Integrator/edge_triggered/Discrete Integrator */
   float DiscreteIntegrator_2_i1_x; /* PLECS_to_CCS/Control Logic/Buck Current PI/Discrete Time/Ki Integrator/Ki ~= 0/Discrete Integrator/edge_triggered/Discrete Integrator */
   float DiscreteIntegrator_2_i2_prevU; /* PLECS_to_CCS/Control Logic/Buck Current PI/Discrete Time/Ki Integrator/Ki ~= 0/Discrete Integrator/edge_triggered/Discrete Integrator */
   bool DiscreteIntegrator_2_i3_prevReset; /* PLECS_to_CCS/Control Logic/Buck Current PI/Discrete Time/Ki Integrator/Ki ~= 0/Discrete Integrator/edge_triggered/Discrete Integrator */
   int8_t DiscreteIntegrator_3_first; /* PLECS_to_CCS/Control Logic/Buck Voltage PI/Discrete Time/Ki Integrator/Ki ~= 0/Discrete Integrator/edge_triggered/Discrete Integrator */
   float DiscreteIntegrator_3_i1_x; /* PLECS_to_CCS/Control Logic/Buck Voltage PI/Discrete Time/Ki Integrator/Ki ~= 0/Discrete Integrator/edge_triggered/Discrete Integrator */
   float DiscreteIntegrator_3_i2_prevU; /* PLECS_to_CCS/Control Logic/Buck Voltage PI/Discrete Time/Ki Integrator/Ki ~= 0/Discrete Integrator/edge_triggered/Discrete Integrator */
   bool DiscreteIntegrator_3_i3_prevReset; /* PLECS_to_CCS/Control Logic/Buck Voltage PI/Discrete Time/Ki Integrator/Ki ~= 0/Discrete Integrator/edge_triggered/Discrete Integrator */
   int8_t DiscreteIntegrator_4_first; /* PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI1/Discrete Time/Ki Integrator/Ki ~= 0/Discrete Integrator/edge_triggered/Discrete Integrator */
   float DiscreteIntegrator_4_i1_x; /* PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI1/Discrete Time/Ki Integrator/Ki ~= 0/Discrete Integrator/edge_triggered/Discrete Integrator */
   float DiscreteIntegrator_4_i2_prevU; /* PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI1/Discrete Time/Ki Integrator/Ki ~= 0/Discrete Integrator/edge_triggered/Discrete Integrator */
   bool DiscreteIntegrator_4_i3_prevReset; /* PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI1/Discrete Time/Ki Integrator/Ki ~= 0/Discrete Integrator/edge_triggered/Discrete Integrator */
} PLECS_to_CCS_ModelStates;
extern PLECS_to_CCS_ModelStates PLECS_to_CCS_X;


/* Block outputs */
typedef struct
{
   float C_Script[6];               /* PLECS_to_CCS/C-Script */
   float MPPTLogic;                 /* PLECS_to_CCS/Control Logic/MPPT Logic */
   float DiscreteIntegrator;        /* PLECS_to_CCS/Control Logic/MPPT PI/Discrete Time/Ki Integrator/Ki ~= 0/Discrete Integrator/edge_triggered/Discrete Integrator */
   float Saturation;                /* PLECS_to_CCS/Control Logic/MPPT PI/Saturation/internal/Saturation Select/constant/Saturation */
   float DiscreteIntegrator_1;      /* PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI/Discrete Time/Ki Integrator/Ki ~= 0/Discrete Integrator/edge_triggered/Discrete Integrator */
   float Saturation_1;              /* PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI/Saturation/internal/Saturation Select/constant/Saturation */
   float Min;                       /* PLECS_to_CCS/Control Logic/Min */
   float StateMachine[2];           /* PLECS_to_CCS/Control Logic/State Machine */
   float RoutingLogic[2];           /* PLECS_to_CCS/Control Logic/Routing Logic */
   float DiscreteIntegrator_2;      /* PLECS_to_CCS/Control Logic/Buck Current PI/Discrete Time/Ki Integrator/Ki ~= 0/Discrete Integrator/edge_triggered/Discrete Integrator */
   float Saturation_2;              /* PLECS_to_CCS/Control Logic/Buck Current PI/Saturation/internal/Saturation Select/constant/Saturation */
   float DiscreteIntegrator_3;      /* PLECS_to_CCS/Control Logic/Buck Voltage PI/Discrete Time/Ki Integrator/Ki ~= 0/Discrete Integrator/edge_triggered/Discrete Integrator */
   float Saturation_3;              /* PLECS_to_CCS/Control Logic/Buck Voltage PI/Saturation/internal/Saturation Select/constant/Saturation */
   float Min_Max;                   /* PLECS_to_CCS/Control Logic/Min/Max */
   float DiscreteIntegrator_4;      /* PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI1/Discrete Time/Ki Integrator/Ki ~= 0/Discrete Integrator/edge_triggered/Discrete Integrator */
   float Saturation_4;              /* PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI1/Saturation/internal/Saturation Select/constant/Saturation */
   float Zero_OrderHold;            /* PLECS_to_CCS/Control Logic/MPPT PI/Discrete Time/Zero-Order Hold */
   float IntialCondition;           /* PLECS_to_CCS/Control Logic/Intial Condition */
   float Sum;                       /* PLECS_to_CCS/Control Logic/MPPT PI/Discrete Time/Sum */
   float Zero_OrderHold_1;          /* PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI/Discrete Time/Zero-Order Hold */
   float Sum_1;                     /* PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI/Discrete Time/Sum */
   float Product3;                  /* PLECS_to_CCS/Control Logic/Product3 */
   float Zero_OrderHold_2;          /* PLECS_to_CCS/Control Logic/Buck Current PI/Discrete Time/Zero-Order Hold */
   float Sum_2;                     /* PLECS_to_CCS/Control Logic/Buck Current PI/Discrete Time/Sum */
   float Zero_OrderHold_3;          /* PLECS_to_CCS/Control Logic/Buck Voltage PI/Discrete Time/Zero-Order Hold */
   float Sum_3;                     /* PLECS_to_CCS/Control Logic/Buck Voltage PI/Discrete Time/Sum */
   float Zero_OrderHold_4;          /* PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI1/Discrete Time/Zero-Order Hold */
   float Sum_4;                     /* PLECS_to_CCS/Control Logic/Buck-Boost Voltage PI1/Discrete Time/Sum */
   float Product;                   /* PLECS_to_CCS/Control Logic/Product */
   float CurrentADC[3];             /* PLECS_to_CCS/Current ADC */
   float VoltageADC[3];             /* PLECS_to_CCS/Voltage ADC */
} PLECS_to_CCS_BlockOutputs;
extern PLECS_to_CCS_BlockOutputs PLECS_to_CCS_B;

/* Entry point functions */
void PLECS_to_CCS_initialize(void);
void PLECS_to_CCS_step(void);
void PLECS_to_CCS_terminate(void);

#endif /* PLECS_HEADER_PLECS_to_CCS_h_ */
