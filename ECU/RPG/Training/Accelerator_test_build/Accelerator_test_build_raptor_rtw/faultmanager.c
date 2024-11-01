/*****************************************************************************
   faultmanager.c
   Generated By:
   Raptor 2022b_1.0.14751 (6897)
   Matlab (R2022b) 9.13

   Copyright (c) 2018 New Eagle Products, Inc.
   All rights reserved.

   Code Generated at: Fri Apr 19 15:40:22 2024
 *****************************************************************************/

#include "faultmanager.h"
#include "Accelerator_test_build.h"
#include "Accelerator_test_build_private.h"

typedef void (* FaultActionTrigger) (int16_T faultIdx);
const FaultActionTrigger actionTriggerList[] = {
  NULL,
};

const int16_T persistMap[] = {
  -1,                                  /* POT1_InputHi */
  -1,                                  /* POT1_InputLow */
};

void updateFaultInput(int16_T faultIdx, boolean_T inSample, uint32_T xLimit,
                      uint32_T yLimit, boolean_T sticky)
{
  boolean_T input;
  switch (getFaultOperation(faultIdx))
  {
   case FLTOP_FALSE:
    input = 0;
    break;

   case FLTOP_TRUE:
    input = 1;
    break;

   default:
    input = inSample;
  }

  setSuspectedState(faultIdx, input);
  if (input) {
    raptorFaultCounts_X_Data()[faultIdx-1]++;
  }

  raptorFaultCounts_Y_Data()[faultIdx-1]++;

  // After the window has expired, check to see if the x limit has been exceeded
  if (raptorFaultCounts_Y_Data()[faultIdx-1] >= yLimit) {
    if (raptorFaultCounts_X_Data()[faultIdx-1] < xLimit) {
      if (!sticky) {
        if (getFaultState(faultIdx, FAULT_ACTIVE)) {
          setOccurredState(faultIdx, 1);
        }

        setActiveState(faultIdx, 0);
      }

      setActiveAtShutdownState(faultIdx, 0);
    } else {
      setActiveState(faultIdx, 1);
      setActiveAtShutdownState(faultIdx, 1);
    }

    raptorFaultCounts_X_Data()[faultIdx-1] = 0;
    raptorFaultCounts_Y_Data()[faultIdx-1] = 0;
  } else if (raptorFaultCounts_X_Data()[faultIdx-1] >= xLimit) {
    // If X failures have occurred, finish the window early and report as active
    setActiveState(faultIdx, 1);
    setActiveAtShutdownState(faultIdx, 1);

    // Reset the window now that the active flag is set
    raptorFaultCounts_X_Data()[faultIdx-1] = 0;
    raptorFaultCounts_Y_Data()[faultIdx-1] = 0;
  }
}

void setActiveAtShutdownState(int16_T faultIdx, boolean_T nextValue)
{
  if (nextValue ) {
    raptorFaultNonVolatileBits_Data()[faultIdx-1] |= FAULT_ACTIVEATSHUTDOWN_MASK;
  } else {
    raptorFaultNonVolatileBits_Data()[faultIdx-1] &= (uint8_T)
      (~(FAULT_ACTIVEATSHUTDOWN_MASK));
  }
}

void setOccurredState(int16_T faultIdx, boolean_T nextValue)
{
  boolean_T curr_occurred_value = (boolean_T)((raptorFaultNonVolatileBits_Data()
    [faultIdx-1] & FAULT_OCCURRED_MASK) != 0);
  boolean_T curr_notoccurred_value = (boolean_T)
    ((raptorFaultNonVolatileBits_Data()[faultIdx-1] & FAULT_NOTOCCURRED_MASK) !=
     0);
  boolean_T occurred_changed = (curr_occurred_value != nextValue);
  boolean_T notoccurred_changed = (curr_notoccurred_value != (!nextValue));
  if (occurred_changed) {
    if (nextValue ) {
      raptorFaultNonVolatileBits_Data()[faultIdx-1] |= FAULT_OCCURRED_MASK;
    } else {
      raptorFaultNonVolatileBits_Data()[faultIdx-1] &= (uint8_T)
        (~(FAULT_OCCURRED_MASK));
    }
  }

  if (notoccurred_changed) {
    if (!nextValue ) {
      raptorFaultNonVolatileBits_Data()[faultIdx-1] |= FAULT_NOTOCCURRED_MASK;
    } else {
      raptorFaultNonVolatileBits_Data()[faultIdx-1] &= (uint8_T)
        (~(FAULT_NOTOCCURRED_MASK));
    }
  }
}

void setActiveState(int16_T faultIdx, boolean_T nextValue)
{
  boolean_T curr_value = (boolean_T)((raptorFaultNonVolatileBits_Data()[faultIdx
    -1] & FAULT_ACTIVE_MASK) != 0);
  if (curr_value != nextValue) {
    if (nextValue ) {
      raptorFaultNonVolatileBits_Data()[faultIdx-1] |= FAULT_ACTIVE_MASK;
    } else {
      raptorFaultNonVolatileBits_Data()[faultIdx-1] &= (uint8_T)
        (~(FAULT_ACTIVE_MASK));
      setOccurredState(faultIdx, 1);
    }
  }
}

void setSuspectedState(int16_T faultIdx, boolean_T nextValue)
{
  boolean_T curr_value = (boolean_T)((raptorFaultNonVolatileBits_Data()[faultIdx
    -1] & FAULT_SUSPECTED_MASK) != 0);
  if (curr_value != nextValue) {
    if (nextValue ) {
      raptorFaultNonVolatileBits_Data()[faultIdx-1] |= FAULT_SUSPECTED_MASK;
    } else {
      raptorFaultNonVolatileBits_Data()[faultIdx-1] &= (uint8_T)
        (~(FAULT_SUSPECTED_MASK));
    }
  }
}

void clearFault(int16_T faultIdx)
{
  setSuspectedState(faultIdx, 0);
  setActiveState(faultIdx, 0);
  setOccurredState(faultIdx, 0);
  setActiveAtShutdownState(faultIdx, 0);
  raptorFaultCounts_X_Data()[faultIdx-1] = 0;
  raptorFaultCounts_Y_Data()[faultIdx-1] = 0;
}

void clearFaults(void)
{
  int16_T faultIdx;
  for (faultIdx = 1; faultIdx <= 2; faultIdx++) {
    clearFault(faultIdx);
  }
}

boolean_T getFaultState(int16_T faultIdx, E_FaultState state)
{
  return (boolean_T)( (uint8_T)(raptorFaultNonVolatileBits_Data()[faultIdx-1] &
    state) != 0);
}

boolean_T getFaultPersistent(int16_T faultIdx)
{
  FM_UNUSED(faultIdx);
  return 0;
}

E_FaultOperation getFaultOperation(int16_T faultIdx)
{
  return raptorFaultOperation_Data()[faultIdx-1];
}

int16_T getNextFaultByState(E_FaultState state, boolean_T onlyEmissRelated,
  int16_T startIdx)
{
  int16_T faultIdx;
  int16_T nextIdx = startIdx;
  FM_UNUSED(onlyEmissRelated);
  if (nextIdx < 0)
    nextIdx = 0;
  nextIdx++;
  for (faultIdx = nextIdx; faultIdx <= 2; faultIdx++)
    if (getFaultState(faultIdx, state))
      return faultIdx;
  return 0;
}

int16_T getNextFault(int16_T startIdx)
{
  int16_T nextIdx = startIdx;
  if (nextIdx < 0)
    nextIdx = 0;
  nextIdx++;
  if (nextIdx > 2)
    return 0;
  else
    return nextIdx;
}

uint16_T getFaultStateCount(E_FaultState state)
{
  int16_T faultIdx = getNextFaultByState(state, 0, 0);
  uint16_T count = 0;
  while (faultIdx > 0) {
    count ++;
    faultIdx = getNextFaultByState(state, 0, faultIdx);
  }

  return count;
}

void initFaultManager()
{
  int16_T faultIdx;
  for (faultIdx = 1; faultIdx <= 2; faultIdx++) {
    if (getFaultState(faultIdx, FAULT_ACTIVEATSHUTDOWN)) {
      setOccurredState(faultIdx, 1);
    } else {
      setOccurredState(faultIdx, getFaultState(faultIdx, FAULT_OCCURRED));
    }

    setActiveAtShutdownState(faultIdx, 0);
    if (!getFaultPersistent(faultIdx))
      setActiveState(faultIdx, 0);
    setSuspectedState(faultIdx, 0);
  }
}
