/*****************************************************************************
   can_CAN2.h
   Generated By:
   Raptor 2022b_1.0.14751 (6897)
   Matlab (R2022b) 9.13

   Copyright (c) 2018 New Eagle Products, Inc.
   All rights reserved.

   Code Generated at: Thu May  9 15:17:16 2024
 *****************************************************************************/

#ifndef __CAN_CAN2_H
#define __CAN_CAN2_H

/*  CAN Bus : CAN2 	*/
/*  Resource: CAN2 	*/
/*  Bus Enum: CAN_BUS_B */
/* Baud Rate: 250k 	*/

/* FUNCTION PROTOTYPES */
/* CAN initialization */
extern void pre_start_CAN_CAN2(void);
extern void post_start_CAN_CAN2(void);
extern void can_process_CAN2(void);
extern void can_errorCheck_CAN2(void);
extern void CAN2_TX_Queue_Get_Status(uint8_T* queueSize, uint8_T* depth, uint8_T*
  maxDepth, uint32_T* overruns );
extern void CAN2_RX_Queue_Get_Status(uint8_T* queueSize, uint8_T* depth, uint8_T*
  maxDepth, uint32_T* overruns );

/* Receive CAN object declarations */
extern void can_update_CAN2(uint32_T id, uint8_T extended, uint8_T length, const
  uint8_T *data);

/* Transmit CAN object declarations */
#endif