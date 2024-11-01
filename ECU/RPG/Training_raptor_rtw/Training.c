/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Training.c
 *
 * Code generated for Simulink model 'Training'.
 *
 * Model version                  : 8.2
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Tue Jan 17 17:54:55 2023
 *
 * Target selection: raptor.tlc
 * Embedded hardware selection: Infineon->TriCore
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Training.h"
#include "Training_private.h"
#include "rtwtypes.h"
#include "zero_crossing_types.h"
#include <string.h>

/* Block states (default storage) */
D_Work_Training Training_DWork;

/* Previous zero-crossings (trigger) states */
PrevZCSigStates_Training Training_PrevZCSigState;

// Block : Training/raptor_timed_trigger
void Timer_ooqlV(void)
{
  /* Timer_ooqlV  ------   Foreground  */
  {
    {
      Training_Foreground();
    }
  }
}

// Block : Training/Power Up_Down/raptor_timed_trigger
void Timer_BGND_G6Wyo(void)
{
  /* Timer_BGND_G6Wyo  ------   Background  */
  {
    {
      Training_Background();
    }
  }
}

/* System initialize for function-call system: '<S2>/Background' */
void Training_Background_Init(void)
{
  /* Start for S-Function (raptor_sfun_digital_in): '<S4>/raptor_digital_in' */

  /* S-Function Block: WAKE_INPUT1 */
  {
  }

  /* Start for S-Function (raptor_sfun_digital_out): '<S4>/raptor_digital_out' */

  /* S-Function Block: POWER_HOLD */
  {
  }

  /* InitializeConditions for S-Function (raptor_sfun_delta_time): '<S5>/raptor_delta_time' */
  Training_DWork.raptor_delta_time_DWORK1_d = ticks();

  /* InitializeConditions for UnitDelay: '<S5>/Unit Delay2' */
  Training_DWork.UnitDelay2_DSTATE = true;
}

/* System reset for function-call system: '<S2>/Background' */
void Training_Background_Reset(void)
{
  /* InitializeConditions for S-Function (raptor_sfun_delta_time): '<S5>/raptor_delta_time' */
  Training_DWork.raptor_delta_time_DWORK1_d = ticks();

  /* InitializeConditions for UnitDelay: '<S5>/Unit Delay2' */
  Training_DWork.UnitDelay2_DSTATE = true;
}

/* Output and update for function-call system: '<S2>/Background' */
void Training_Background(void)
{
  /* local block i/o variables */
  real_T rtb_raptor_delta_time;
  boolean_T rtb_raptor_digital_in;
  real_T rtb_MultiportSwitch1;
  boolean_T rtb_Logic;
  boolean_T rtb_LogicalOperator1_h;
  boolean_T rtb_LogicalOperator2_c;
  boolean_T rtb_raptor_sfun_nv_status;

  /* S-Function (raptor_sfun_digital_in): '<S4>/raptor_digital_in' */
  /* S-Function Block: WAKE_INPUT1 */
  {
    rtb_raptor_digital_in = swsh_ignswSt();
  }

  /* S-Function (raptor_sfun_delta_time): '<S5>/raptor_delta_time' */
  {
    rtb_raptor_delta_time = (GetDeltaTime_ms
      (&Training_DWork.raptor_delta_time_DWORK1_d) * 0.001f);
  }

  /* MultiPortSwitch: '<S5>/Multiport Switch1' incorporates:
   *  Constant: '<S5>/Constant'
   *  RelationalOperator: '<S9>/FixPt Relational Operator'
   *  Sum: '<S5>/Add'
   *  UnitDelay: '<S5>/Unit Delay'
   *  UnitDelay: '<S9>/Delay Input1'
   */
  if (rtb_raptor_digital_in == Training_DWork.DelayInput1_DSTATE) {
    rtb_MultiportSwitch1 = rtb_raptor_delta_time +
      Training_DWork.UnitDelay_DSTATE;
  } else {
    rtb_MultiportSwitch1 = 0.0;
  }

  /* End of MultiPortSwitch: '<S5>/Multiport Switch1' */
  /* UnitDelay: '<S5>/Unit Delay2' */
  rtb_raptor_sfun_nv_status = Training_DWork.UnitDelay2_DSTATE;

  /* CombinatorialLogic: '<S5>/Logic' incorporates:
   *  Logic: '<S5>/Logical Operator1'
   *  Logic: '<S5>/Logical Operator2'
   *  Logic: '<S5>/Logical Operator3'
   *  RelationalOperator: '<S5>/Relational Operator'
   *  RelationalOperator: '<S5>/Relational Operator1'
   *  S-Function (raptor_sfun_adjustment): '<S5>/raptor_adjustment3'
   *  S-Function (raptor_sfun_adjustment): '<S5>/raptor_adjustment4'
   */
  rtb_Logic = Training_ConstP.Logic_table[((((uint32_T)(rtb_raptor_digital_in &&
    (rtb_MultiportSwitch1 >= (KeySwHiTimeThr_Data()))) << 1) + (uint32_T)
    ((!rtb_raptor_digital_in) && (rtb_MultiportSwitch1 >= (KeySwLoTimeThr_Data()))))
    << 1) + rtb_raptor_sfun_nv_status];

  /* Logic: '<S4>/Logical Operator1' incorporates:
   *  S-Function (raptor_sfun_data_read): '<S4>/raptor_data_read1'
   */
  rtb_LogicalOperator1_h = (rtb_Logic || KeepModuleOn_Data());

  /* Outputs for Triggered SubSystem: '<S4>/Raise Shutdown Event' incorporates:
   *  TriggerPort: '<S6>/Trigger'
   */
  if ((!rtb_LogicalOperator1_h) &&
      (Training_PrevZCSigState.RaiseShutdownEvent_Trig_ZCE != ZERO_ZCSIG)) {
    /* S-Function (raptor_sfun_data_write): '<S6>/raptor_data_write' incorporates:
     *  Constant: '<S6>/Constant'
     */
    FgndTasksStopped_Data() = true;

    /* S-Function (fcgen): '<S6>/Function-Call Generator' incorporates:
     *  SubSystem: '<S6>/raptor_shutdown'
     */
    /* S-Function (raptor_sfun_shutdown): '<S10>/raptor_data_write' */
    /* S-Function Block */
    {
      extern void App_Shutdown(void);
      App_Shutdown();
    }

    /* End of Outputs for S-Function (fcgen): '<S6>/Function-Call Generator' */
  }

  Training_PrevZCSigState.RaiseShutdownEvent_Trig_ZCE = rtb_LogicalOperator1_h;

  /* End of Outputs for SubSystem: '<S4>/Raise Shutdown Event' */
  /* Outputs for Enabled and Triggered SubSystem: '<S4>/Raise Startup Event' incorporates:
   *  EnablePort: '<S7>/Enable'
   *  TriggerPort: '<S7>/Trigger'
   */
  if (FgndTasksStopped_Data() && (rtb_LogicalOperator1_h &&
       (Training_PrevZCSigState.RaiseStartupEvent_Trig_ZCE != POS_ZCSIG))) {
    /* S-Function (fcgen): '<S7>/Function-Call Generator' incorporates:
     *  SubSystem: '<S7>/raptor_startup'
     */
    /* S-Function (raptor_sfun_startup): '<S11>/raptor_data_write' */
    /* S-Function Block */
    {
      extern void App_Startup(void);
      App_Startup();
    }

    /* End of Outputs for S-Function (fcgen): '<S7>/Function-Call Generator' */
  }

  /* End of S-Function (raptor_sfun_data_read): '<S4>/raptor_data_read' */

  /* Outputs for Triggered SubSystem: '<S4>/Raise Shutdown Event' incorporates:
   *  TriggerPort: '<S6>/Trigger'
   */
  Training_PrevZCSigState.RaiseStartupEvent_Trig_ZCE = rtb_LogicalOperator1_h;

  /* End of Outputs for SubSystem: '<S4>/Raise Shutdown Event' */
  /* End of Outputs for SubSystem: '<S4>/Raise Startup Event' */

  /* UnitDelay: '<S4>/Unit Delay' */
  rtb_LogicalOperator2_c = Training_DWork.UnitDelay_DSTATE_e;

  /* Outputs for Triggered SubSystem: '<S4>/Store EEPROM' incorporates:
   *  TriggerPort: '<S8>/Trigger'
   */
  if ((!Training_DWork.UnitDelay_DSTATE_e) &&
      (Training_PrevZCSigState.StoreEEPROM_Trig_ZCE != ZERO_ZCSIG)) {
    /* S-Function (fcgen): '<S8>/Function-Call Generator' incorporates:
     *  SubSystem: '<S8>/raptor_store_nv'
     */
    /* S-Function (raptor_sfun_store_nv): '<S12>/raptor_data_write' */
    /* S-Function Block */
    {
      App_EE_Store();
    }

    /* End of Outputs for S-Function (fcgen): '<S8>/Function-Call Generator' */
  }

  /* End of UnitDelay: '<S4>/Unit Delay' */
  Training_PrevZCSigState.StoreEEPROM_Trig_ZCE = rtb_LogicalOperator2_c;

  /* End of Outputs for SubSystem: '<S4>/Store EEPROM' */

  /* S-Function (raptor_sfun_data_write): '<S4>/raptor_data_write' */
  KeySw_Bgnd_Data() = rtb_Logic;

  /* S-Function (raptor_sfun_nv_status): '<S4>/raptor_sfun_nv_status' */
  /* S-Function Block */
  {
    rtb_raptor_sfun_nv_status = (EEPROM_State_Data() == EE_STORE_IN_PROGESS);
  }

  /* Logic: '<S4>/Logical Operator2' incorporates:
   *  UnitDelay: '<S4>/Unit Delay1'
   */
  rtb_raptor_sfun_nv_status = (rtb_raptor_sfun_nv_status ||
    rtb_LogicalOperator1_h || Training_DWork.UnitDelay1_DSTATE);

  /* S-Function (raptor_sfun_digital_out): '<S4>/raptor_digital_out' */
  /* S-Function Block: POWER_HOLD */
  {
    {
      if (rtb_raptor_sfun_nv_status && !swsh_ignswSt()) {
        SyC_WaitPostDrv();
      }
    }
  }

  /* Update for UnitDelay: '<S9>/Delay Input1' */
  Training_DWork.DelayInput1_DSTATE = rtb_raptor_digital_in;

  /* Update for UnitDelay: '<S5>/Unit Delay' */
  Training_DWork.UnitDelay_DSTATE = rtb_MultiportSwitch1;

  /* Update for UnitDelay: '<S5>/Unit Delay2' */
  Training_DWork.UnitDelay2_DSTATE = rtb_Logic;

  /* Update for UnitDelay: '<S4>/Unit Delay' */
  Training_DWork.UnitDelay_DSTATE_e = rtb_LogicalOperator1_h;

  /* Update for UnitDelay: '<S4>/Unit Delay1' */
  Training_DWork.UnitDelay1_DSTATE = rtb_LogicalOperator2_c;
}

/* System initialize for function-call system: '<Root>/Foreground' */
void Training_Foreground_Init(void)
{
  /* InitializeConditions for S-Function (raptor_sfun_delta_time): '<S1>/raptor_delta_time' */
  Training_DWork.raptor_delta_time_DWORK1 = ticks();
}

/* System reset for function-call system: '<Root>/Foreground' */
void Training_Foreground_Reset(void)
{
  /* InitializeConditions for S-Function (raptor_sfun_delta_time): '<S1>/raptor_delta_time' */
  Training_DWork.raptor_delta_time_DWORK1 = ticks();
}

/* Output and update for function-call system: '<Root>/Foreground' */
void Training_Foreground(void)
{
  /* local block i/o variables */
  real_T rtb_raptor_delta_time_n;

  /* S-Function (raptor_sfun_delta_time): '<S1>/raptor_delta_time' */
  {
    rtb_raptor_delta_time_n = (GetDeltaTime_ms
      (&Training_DWork.raptor_delta_time_DWORK1) * 0.001f);
  }

  /* S-Function (raptor_sfun_measurement): '<S1>/raptor_measurement1' */
  Delta_Time_Data() = rtb_raptor_delta_time_n;

  /* S-Function (raptor_sfun_measurement): '<S1>/raptor_measurement' incorporates:
   *  S-Function (raptor_sfun_time): '<S1>/raptor_time'
   */
  Absolute_Time_Data() = (GetAbsTime());
}

/* Model step function */
void Training_step(void)
{
  /* S-Function (raptor_sfun_target_def): '<Root>/raptor_target_def' */

  /*
   * New Eagle LLC 2011
   */
}

/* Model initialize function */
void Training_initialize(void)
{
  /* Registration code */

  /* states (dwork) */
  (void) memset((void *)&Training_DWork, 0,
                sizeof(D_Work_Training));
  Training_DWork.UnitDelay_DSTATE = 0.0;

  /* Start for S-Function (raptor_sfun_xcp): '<S3>/raptor_xcp_update' */

  /* S-Function Block - Start: <S3>/raptor_xcp_update */
  {
    CAN1_XCP_CAN_PreStart(CAN1__XCP_BC_ID_Data(), CAN1__XCP_RX_ID_Data(),
                          CAN1__XCP_TX_ID_Data());
  }

  Training_PrevZCSigState.RaiseShutdownEvent_Trig_ZCE = ZERO_ZCSIG;
  Training_PrevZCSigState.RaiseStartupEvent_Trig_ZCE = POS_ZCSIG;
  Training_PrevZCSigState.StoreEEPROM_Trig_ZCE = ZERO_ZCSIG;

  /* SystemInitialize for S-Function (raptor_sfun_timed_trigger): '<Root>/raptor_timed_trigger' incorporates:
   *  SubSystem: '<Root>/Foreground'
   */
  Training_Foreground_Init();

  /* End of SystemInitialize for S-Function (raptor_sfun_timed_trigger): '<Root>/raptor_timed_trigger' */

  /* SystemInitialize for S-Function (raptor_sfun_timed_trigger): '<S2>/raptor_timed_trigger' incorporates:
   *  SubSystem: '<S2>/Background'
   */
  Training_Background_Init();

  /* End of SystemInitialize for S-Function (raptor_sfun_timed_trigger): '<S2>/raptor_timed_trigger' */

  /* Enable for S-Function (raptor_sfun_timed_trigger): '<Root>/raptor_timed_trigger' */

  /* Level2 S-Function Block: '<Root>/raptor_timed_trigger' (raptor_sfun_timed_trigger) */

  /* Enable Subsystem */

  /* End of Enable for S-Function (raptor_sfun_timed_trigger): '<Root>/raptor_timed_trigger' */

  /* Enable for S-Function (raptor_sfun_timed_trigger): '<S2>/raptor_timed_trigger' */

  /* Level2 S-Function Block: '<S2>/raptor_timed_trigger' (raptor_sfun_timed_trigger) */

  /* Enable Subsystem */

  /* End of Enable for S-Function (raptor_sfun_timed_trigger): '<S2>/raptor_timed_trigger' */
}

/* Model terminate function */
void Training_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
