/*******************************************************************************
* File Name: ResetTimer.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the ResetTimer
*  component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_TCPWM_ResetTimer_H)
#define CY_TCPWM_ResetTimer_H


#include "CyLib.h"
#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} ResetTimer_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  ResetTimer_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define ResetTimer_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define ResetTimer_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define ResetTimer_CONFIG                         (1lu)

/* Quad Mode */
/* Parameters */
#define ResetTimer_QUAD_ENCODING_MODES            (0lu)
#define ResetTimer_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define ResetTimer_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define ResetTimer_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define ResetTimer_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define ResetTimer_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define ResetTimer_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define ResetTimer_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define ResetTimer_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define ResetTimer_TC_RUN_MODE                    (1lu)
#define ResetTimer_TC_COUNTER_MODE                (1lu)
#define ResetTimer_TC_COMP_CAP_MODE               (2lu)
#define ResetTimer_TC_PRESCALER                   (0lu)

/* Signal modes */
#define ResetTimer_TC_RELOAD_SIGNAL_MODE          (1lu)
#define ResetTimer_TC_COUNT_SIGNAL_MODE           (3lu)
#define ResetTimer_TC_START_SIGNAL_MODE           (1lu)
#define ResetTimer_TC_STOP_SIGNAL_MODE            (0lu)
#define ResetTimer_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define ResetTimer_TC_RELOAD_SIGNAL_PRESENT       (1lu)
#define ResetTimer_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define ResetTimer_TC_START_SIGNAL_PRESENT        (1lu)
#define ResetTimer_TC_STOP_SIGNAL_PRESENT         (1lu)
#define ResetTimer_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define ResetTimer_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define ResetTimer_PWM_KILL_EVENT                 (0lu)
#define ResetTimer_PWM_STOP_EVENT                 (0lu)
#define ResetTimer_PWM_MODE                       (4lu)
#define ResetTimer_PWM_OUT_N_INVERT               (0lu)
#define ResetTimer_PWM_OUT_INVERT                 (0lu)
#define ResetTimer_PWM_ALIGN                      (0lu)
#define ResetTimer_PWM_RUN_MODE                   (0lu)
#define ResetTimer_PWM_DEAD_TIME_CYCLE            (0lu)
#define ResetTimer_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define ResetTimer_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define ResetTimer_PWM_COUNT_SIGNAL_MODE          (3lu)
#define ResetTimer_PWM_START_SIGNAL_MODE          (0lu)
#define ResetTimer_PWM_STOP_SIGNAL_MODE           (0lu)
#define ResetTimer_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define ResetTimer_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define ResetTimer_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define ResetTimer_PWM_START_SIGNAL_PRESENT       (0lu)
#define ResetTimer_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define ResetTimer_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define ResetTimer_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define ResetTimer_TC_PERIOD_VALUE                (20000lu)
#define ResetTimer_TC_COMPARE_VALUE               (65535lu)
#define ResetTimer_TC_COMPARE_BUF_VALUE           (65535lu)
#define ResetTimer_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define ResetTimer_PWM_PERIOD_VALUE               (65535lu)
#define ResetTimer_PWM_PERIOD_BUF_VALUE           (65535lu)
#define ResetTimer_PWM_PERIOD_SWAP                (0lu)
#define ResetTimer_PWM_COMPARE_VALUE              (65535lu)
#define ResetTimer_PWM_COMPARE_BUF_VALUE          (65535lu)
#define ResetTimer_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define ResetTimer__LEFT 0
#define ResetTimer__RIGHT 1
#define ResetTimer__CENTER 2
#define ResetTimer__ASYMMETRIC 3

#define ResetTimer__X1 0
#define ResetTimer__X2 1
#define ResetTimer__X4 2

#define ResetTimer__PWM 4
#define ResetTimer__PWM_DT 5
#define ResetTimer__PWM_PR 6

#define ResetTimer__INVERSE 1
#define ResetTimer__DIRECT 0

#define ResetTimer__CAPTURE 2
#define ResetTimer__COMPARE 0

#define ResetTimer__TRIG_LEVEL 3
#define ResetTimer__TRIG_RISING 0
#define ResetTimer__TRIG_FALLING 1
#define ResetTimer__TRIG_BOTH 2

#define ResetTimer__INTR_MASK_TC 1
#define ResetTimer__INTR_MASK_CC_MATCH 2
#define ResetTimer__INTR_MASK_NONE 0
#define ResetTimer__INTR_MASK_TC_CC 3

#define ResetTimer__UNCONFIG 8
#define ResetTimer__TIMER 1
#define ResetTimer__QUAD 3
#define ResetTimer__PWM_SEL 7

#define ResetTimer__COUNT_UP 0
#define ResetTimer__COUNT_DOWN 1
#define ResetTimer__COUNT_UPDOWN0 2
#define ResetTimer__COUNT_UPDOWN1 3


/* Prescaler */
#define ResetTimer_PRESCALE_DIVBY1                ((uint32)(0u << ResetTimer_PRESCALER_SHIFT))
#define ResetTimer_PRESCALE_DIVBY2                ((uint32)(1u << ResetTimer_PRESCALER_SHIFT))
#define ResetTimer_PRESCALE_DIVBY4                ((uint32)(2u << ResetTimer_PRESCALER_SHIFT))
#define ResetTimer_PRESCALE_DIVBY8                ((uint32)(3u << ResetTimer_PRESCALER_SHIFT))
#define ResetTimer_PRESCALE_DIVBY16               ((uint32)(4u << ResetTimer_PRESCALER_SHIFT))
#define ResetTimer_PRESCALE_DIVBY32               ((uint32)(5u << ResetTimer_PRESCALER_SHIFT))
#define ResetTimer_PRESCALE_DIVBY64               ((uint32)(6u << ResetTimer_PRESCALER_SHIFT))
#define ResetTimer_PRESCALE_DIVBY128              ((uint32)(7u << ResetTimer_PRESCALER_SHIFT))

/* TCPWM set modes */
#define ResetTimer_MODE_TIMER_COMPARE             ((uint32)(ResetTimer__COMPARE         <<  \
                                                                  ResetTimer_MODE_SHIFT))
#define ResetTimer_MODE_TIMER_CAPTURE             ((uint32)(ResetTimer__CAPTURE         <<  \
                                                                  ResetTimer_MODE_SHIFT))
#define ResetTimer_MODE_QUAD                      ((uint32)(ResetTimer__QUAD            <<  \
                                                                  ResetTimer_MODE_SHIFT))
#define ResetTimer_MODE_PWM                       ((uint32)(ResetTimer__PWM             <<  \
                                                                  ResetTimer_MODE_SHIFT))
#define ResetTimer_MODE_PWM_DT                    ((uint32)(ResetTimer__PWM_DT          <<  \
                                                                  ResetTimer_MODE_SHIFT))
#define ResetTimer_MODE_PWM_PR                    ((uint32)(ResetTimer__PWM_PR          <<  \
                                                                  ResetTimer_MODE_SHIFT))

/* Quad Modes */
#define ResetTimer_MODE_X1                        ((uint32)(ResetTimer__X1              <<  \
                                                                  ResetTimer_QUAD_MODE_SHIFT))
#define ResetTimer_MODE_X2                        ((uint32)(ResetTimer__X2              <<  \
                                                                  ResetTimer_QUAD_MODE_SHIFT))
#define ResetTimer_MODE_X4                        ((uint32)(ResetTimer__X4              <<  \
                                                                  ResetTimer_QUAD_MODE_SHIFT))

/* Counter modes */
#define ResetTimer_COUNT_UP                       ((uint32)(ResetTimer__COUNT_UP        <<  \
                                                                  ResetTimer_UPDOWN_SHIFT))
#define ResetTimer_COUNT_DOWN                     ((uint32)(ResetTimer__COUNT_DOWN      <<  \
                                                                  ResetTimer_UPDOWN_SHIFT))
#define ResetTimer_COUNT_UPDOWN0                  ((uint32)(ResetTimer__COUNT_UPDOWN0   <<  \
                                                                  ResetTimer_UPDOWN_SHIFT))
#define ResetTimer_COUNT_UPDOWN1                  ((uint32)(ResetTimer__COUNT_UPDOWN1   <<  \
                                                                  ResetTimer_UPDOWN_SHIFT))

/* PWM output invert */
#define ResetTimer_INVERT_LINE                    ((uint32)(ResetTimer__INVERSE         <<  \
                                                                  ResetTimer_INV_OUT_SHIFT))
#define ResetTimer_INVERT_LINE_N                  ((uint32)(ResetTimer__INVERSE         <<  \
                                                                  ResetTimer_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define ResetTimer_TRIG_RISING                    ((uint32)ResetTimer__TRIG_RISING)
#define ResetTimer_TRIG_FALLING                   ((uint32)ResetTimer__TRIG_FALLING)
#define ResetTimer_TRIG_BOTH                      ((uint32)ResetTimer__TRIG_BOTH)
#define ResetTimer_TRIG_LEVEL                     ((uint32)ResetTimer__TRIG_LEVEL)

/* Interrupt mask */
#define ResetTimer_INTR_MASK_TC                   ((uint32)ResetTimer__INTR_MASK_TC)
#define ResetTimer_INTR_MASK_CC_MATCH             ((uint32)ResetTimer__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define ResetTimer_CC_MATCH_SET                   (0x00u)
#define ResetTimer_CC_MATCH_CLEAR                 (0x01u)
#define ResetTimer_CC_MATCH_INVERT                (0x02u)
#define ResetTimer_CC_MATCH_NO_CHANGE             (0x03u)
#define ResetTimer_OVERLOW_SET                    (0x00u)
#define ResetTimer_OVERLOW_CLEAR                  (0x04u)
#define ResetTimer_OVERLOW_INVERT                 (0x08u)
#define ResetTimer_OVERLOW_NO_CHANGE              (0x0Cu)
#define ResetTimer_UNDERFLOW_SET                  (0x00u)
#define ResetTimer_UNDERFLOW_CLEAR                (0x10u)
#define ResetTimer_UNDERFLOW_INVERT               (0x20u)
#define ResetTimer_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define ResetTimer_PWM_MODE_LEFT                  (ResetTimer_CC_MATCH_CLEAR        |   \
                                                         ResetTimer_OVERLOW_SET           |   \
                                                         ResetTimer_UNDERFLOW_NO_CHANGE)
#define ResetTimer_PWM_MODE_RIGHT                 (ResetTimer_CC_MATCH_SET          |   \
                                                         ResetTimer_OVERLOW_NO_CHANGE     |   \
                                                         ResetTimer_UNDERFLOW_CLEAR)
#define ResetTimer_PWM_MODE_ASYM                  (ResetTimer_CC_MATCH_INVERT       |   \
                                                         ResetTimer_OVERLOW_SET           |   \
                                                         ResetTimer_UNDERFLOW_CLEAR)

#if (ResetTimer_CY_TCPWM_V2)
    #if(ResetTimer_CY_TCPWM_4000)
        #define ResetTimer_PWM_MODE_CENTER                (ResetTimer_CC_MATCH_INVERT       |   \
                                                                 ResetTimer_OVERLOW_NO_CHANGE     |   \
                                                                 ResetTimer_UNDERFLOW_CLEAR)
    #else
        #define ResetTimer_PWM_MODE_CENTER                (ResetTimer_CC_MATCH_INVERT       |   \
                                                                 ResetTimer_OVERLOW_SET           |   \
                                                                 ResetTimer_UNDERFLOW_CLEAR)
    #endif /* (ResetTimer_CY_TCPWM_4000) */
#else
    #define ResetTimer_PWM_MODE_CENTER                (ResetTimer_CC_MATCH_INVERT       |   \
                                                             ResetTimer_OVERLOW_NO_CHANGE     |   \
                                                             ResetTimer_UNDERFLOW_CLEAR)
#endif /* (ResetTimer_CY_TCPWM_NEW) */

/* Command operations without condition */
#define ResetTimer_CMD_CAPTURE                    (0u)
#define ResetTimer_CMD_RELOAD                     (8u)
#define ResetTimer_CMD_STOP                       (16u)
#define ResetTimer_CMD_START                      (24u)

/* Status */
#define ResetTimer_STATUS_DOWN                    (1u)
#define ResetTimer_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   ResetTimer_Init(void);
void   ResetTimer_Enable(void);
void   ResetTimer_Start(void);
void   ResetTimer_Stop(void);

void   ResetTimer_SetMode(uint32 mode);
void   ResetTimer_SetCounterMode(uint32 counterMode);
void   ResetTimer_SetPWMMode(uint32 modeMask);
void   ResetTimer_SetQDMode(uint32 qdMode);

void   ResetTimer_SetPrescaler(uint32 prescaler);
void   ResetTimer_TriggerCommand(uint32 mask, uint32 command);
void   ResetTimer_SetOneShot(uint32 oneShotEnable);
uint32 ResetTimer_ReadStatus(void);

void   ResetTimer_SetPWMSyncKill(uint32 syncKillEnable);
void   ResetTimer_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   ResetTimer_SetPWMDeadTime(uint32 deadTime);
void   ResetTimer_SetPWMInvert(uint32 mask);

void   ResetTimer_SetInterruptMode(uint32 interruptMask);
uint32 ResetTimer_GetInterruptSourceMasked(void);
uint32 ResetTimer_GetInterruptSource(void);
void   ResetTimer_ClearInterrupt(uint32 interruptMask);
void   ResetTimer_SetInterrupt(uint32 interruptMask);

void   ResetTimer_WriteCounter(uint32 count);
uint32 ResetTimer_ReadCounter(void);

uint32 ResetTimer_ReadCapture(void);
uint32 ResetTimer_ReadCaptureBuf(void);

void   ResetTimer_WritePeriod(uint32 period);
uint32 ResetTimer_ReadPeriod(void);
void   ResetTimer_WritePeriodBuf(uint32 periodBuf);
uint32 ResetTimer_ReadPeriodBuf(void);

void   ResetTimer_WriteCompare(uint32 compare);
uint32 ResetTimer_ReadCompare(void);
void   ResetTimer_WriteCompareBuf(uint32 compareBuf);
uint32 ResetTimer_ReadCompareBuf(void);

void   ResetTimer_SetPeriodSwap(uint32 swapEnable);
void   ResetTimer_SetCompareSwap(uint32 swapEnable);

void   ResetTimer_SetCaptureMode(uint32 triggerMode);
void   ResetTimer_SetReloadMode(uint32 triggerMode);
void   ResetTimer_SetStartMode(uint32 triggerMode);
void   ResetTimer_SetStopMode(uint32 triggerMode);
void   ResetTimer_SetCountMode(uint32 triggerMode);

void   ResetTimer_SaveConfig(void);
void   ResetTimer_RestoreConfig(void);
void   ResetTimer_Sleep(void);
void   ResetTimer_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define ResetTimer_BLOCK_CONTROL_REG              (*(reg32 *) ResetTimer_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define ResetTimer_BLOCK_CONTROL_PTR              ( (reg32 *) ResetTimer_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define ResetTimer_COMMAND_REG                    (*(reg32 *) ResetTimer_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define ResetTimer_COMMAND_PTR                    ( (reg32 *) ResetTimer_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define ResetTimer_INTRRUPT_CAUSE_REG             (*(reg32 *) ResetTimer_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define ResetTimer_INTRRUPT_CAUSE_PTR             ( (reg32 *) ResetTimer_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define ResetTimer_CONTROL_REG                    (*(reg32 *) ResetTimer_cy_m0s8_tcpwm_1__CTRL )
#define ResetTimer_CONTROL_PTR                    ( (reg32 *) ResetTimer_cy_m0s8_tcpwm_1__CTRL )
#define ResetTimer_STATUS_REG                     (*(reg32 *) ResetTimer_cy_m0s8_tcpwm_1__STATUS )
#define ResetTimer_STATUS_PTR                     ( (reg32 *) ResetTimer_cy_m0s8_tcpwm_1__STATUS )
#define ResetTimer_COUNTER_REG                    (*(reg32 *) ResetTimer_cy_m0s8_tcpwm_1__COUNTER )
#define ResetTimer_COUNTER_PTR                    ( (reg32 *) ResetTimer_cy_m0s8_tcpwm_1__COUNTER )
#define ResetTimer_COMP_CAP_REG                   (*(reg32 *) ResetTimer_cy_m0s8_tcpwm_1__CC )
#define ResetTimer_COMP_CAP_PTR                   ( (reg32 *) ResetTimer_cy_m0s8_tcpwm_1__CC )
#define ResetTimer_COMP_CAP_BUF_REG               (*(reg32 *) ResetTimer_cy_m0s8_tcpwm_1__CC_BUFF )
#define ResetTimer_COMP_CAP_BUF_PTR               ( (reg32 *) ResetTimer_cy_m0s8_tcpwm_1__CC_BUFF )
#define ResetTimer_PERIOD_REG                     (*(reg32 *) ResetTimer_cy_m0s8_tcpwm_1__PERIOD )
#define ResetTimer_PERIOD_PTR                     ( (reg32 *) ResetTimer_cy_m0s8_tcpwm_1__PERIOD )
#define ResetTimer_PERIOD_BUF_REG                 (*(reg32 *) ResetTimer_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define ResetTimer_PERIOD_BUF_PTR                 ( (reg32 *) ResetTimer_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define ResetTimer_TRIG_CONTROL0_REG              (*(reg32 *) ResetTimer_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define ResetTimer_TRIG_CONTROL0_PTR              ( (reg32 *) ResetTimer_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define ResetTimer_TRIG_CONTROL1_REG              (*(reg32 *) ResetTimer_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define ResetTimer_TRIG_CONTROL1_PTR              ( (reg32 *) ResetTimer_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define ResetTimer_TRIG_CONTROL2_REG              (*(reg32 *) ResetTimer_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define ResetTimer_TRIG_CONTROL2_PTR              ( (reg32 *) ResetTimer_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define ResetTimer_INTERRUPT_REQ_REG              (*(reg32 *) ResetTimer_cy_m0s8_tcpwm_1__INTR )
#define ResetTimer_INTERRUPT_REQ_PTR              ( (reg32 *) ResetTimer_cy_m0s8_tcpwm_1__INTR )
#define ResetTimer_INTERRUPT_SET_REG              (*(reg32 *) ResetTimer_cy_m0s8_tcpwm_1__INTR_SET )
#define ResetTimer_INTERRUPT_SET_PTR              ( (reg32 *) ResetTimer_cy_m0s8_tcpwm_1__INTR_SET )
#define ResetTimer_INTERRUPT_MASK_REG             (*(reg32 *) ResetTimer_cy_m0s8_tcpwm_1__INTR_MASK )
#define ResetTimer_INTERRUPT_MASK_PTR             ( (reg32 *) ResetTimer_cy_m0s8_tcpwm_1__INTR_MASK )
#define ResetTimer_INTERRUPT_MASKED_REG           (*(reg32 *) ResetTimer_cy_m0s8_tcpwm_1__INTR_MASKED )
#define ResetTimer_INTERRUPT_MASKED_PTR           ( (reg32 *) ResetTimer_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define ResetTimer_MASK                           ((uint32)ResetTimer_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define ResetTimer_RELOAD_CC_SHIFT                (0u)
#define ResetTimer_RELOAD_PERIOD_SHIFT            (1u)
#define ResetTimer_PWM_SYNC_KILL_SHIFT            (2u)
#define ResetTimer_PWM_STOP_KILL_SHIFT            (3u)
#define ResetTimer_PRESCALER_SHIFT                (8u)
#define ResetTimer_UPDOWN_SHIFT                   (16u)
#define ResetTimer_ONESHOT_SHIFT                  (18u)
#define ResetTimer_QUAD_MODE_SHIFT                (20u)
#define ResetTimer_INV_OUT_SHIFT                  (20u)
#define ResetTimer_INV_COMPL_OUT_SHIFT            (21u)
#define ResetTimer_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define ResetTimer_RELOAD_CC_MASK                 ((uint32)(ResetTimer_1BIT_MASK        <<  \
                                                                            ResetTimer_RELOAD_CC_SHIFT))
#define ResetTimer_RELOAD_PERIOD_MASK             ((uint32)(ResetTimer_1BIT_MASK        <<  \
                                                                            ResetTimer_RELOAD_PERIOD_SHIFT))
#define ResetTimer_PWM_SYNC_KILL_MASK             ((uint32)(ResetTimer_1BIT_MASK        <<  \
                                                                            ResetTimer_PWM_SYNC_KILL_SHIFT))
#define ResetTimer_PWM_STOP_KILL_MASK             ((uint32)(ResetTimer_1BIT_MASK        <<  \
                                                                            ResetTimer_PWM_STOP_KILL_SHIFT))
#define ResetTimer_PRESCALER_MASK                 ((uint32)(ResetTimer_8BIT_MASK        <<  \
                                                                            ResetTimer_PRESCALER_SHIFT))
#define ResetTimer_UPDOWN_MASK                    ((uint32)(ResetTimer_2BIT_MASK        <<  \
                                                                            ResetTimer_UPDOWN_SHIFT))
#define ResetTimer_ONESHOT_MASK                   ((uint32)(ResetTimer_1BIT_MASK        <<  \
                                                                            ResetTimer_ONESHOT_SHIFT))
#define ResetTimer_QUAD_MODE_MASK                 ((uint32)(ResetTimer_3BIT_MASK        <<  \
                                                                            ResetTimer_QUAD_MODE_SHIFT))
#define ResetTimer_INV_OUT_MASK                   ((uint32)(ResetTimer_2BIT_MASK        <<  \
                                                                            ResetTimer_INV_OUT_SHIFT))
#define ResetTimer_MODE_MASK                      ((uint32)(ResetTimer_3BIT_MASK        <<  \
                                                                            ResetTimer_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define ResetTimer_CAPTURE_SHIFT                  (0u)
#define ResetTimer_COUNT_SHIFT                    (2u)
#define ResetTimer_RELOAD_SHIFT                   (4u)
#define ResetTimer_STOP_SHIFT                     (6u)
#define ResetTimer_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define ResetTimer_CAPTURE_MASK                   ((uint32)(ResetTimer_2BIT_MASK        <<  \
                                                                  ResetTimer_CAPTURE_SHIFT))
#define ResetTimer_COUNT_MASK                     ((uint32)(ResetTimer_2BIT_MASK        <<  \
                                                                  ResetTimer_COUNT_SHIFT))
#define ResetTimer_RELOAD_MASK                    ((uint32)(ResetTimer_2BIT_MASK        <<  \
                                                                  ResetTimer_RELOAD_SHIFT))
#define ResetTimer_STOP_MASK                      ((uint32)(ResetTimer_2BIT_MASK        <<  \
                                                                  ResetTimer_STOP_SHIFT))
#define ResetTimer_START_MASK                     ((uint32)(ResetTimer_2BIT_MASK        <<  \
                                                                  ResetTimer_START_SHIFT))

/* MASK */
#define ResetTimer_1BIT_MASK                      ((uint32)0x01u)
#define ResetTimer_2BIT_MASK                      ((uint32)0x03u)
#define ResetTimer_3BIT_MASK                      ((uint32)0x07u)
#define ResetTimer_6BIT_MASK                      ((uint32)0x3Fu)
#define ResetTimer_8BIT_MASK                      ((uint32)0xFFu)
#define ResetTimer_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define ResetTimer_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define ResetTimer_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(ResetTimer_QUAD_ENCODING_MODES     << ResetTimer_QUAD_MODE_SHIFT))       |\
         ((uint32)(ResetTimer_CONFIG                  << ResetTimer_MODE_SHIFT)))

#define ResetTimer_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(ResetTimer_PWM_STOP_EVENT          << ResetTimer_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(ResetTimer_PWM_OUT_INVERT          << ResetTimer_INV_OUT_SHIFT))         |\
         ((uint32)(ResetTimer_PWM_OUT_N_INVERT        << ResetTimer_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(ResetTimer_PWM_MODE                << ResetTimer_MODE_SHIFT)))

#define ResetTimer_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(ResetTimer_PWM_RUN_MODE         << ResetTimer_ONESHOT_SHIFT))
            
#define ResetTimer_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(ResetTimer_PWM_ALIGN            << ResetTimer_UPDOWN_SHIFT))

#define ResetTimer_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(ResetTimer_PWM_KILL_EVENT      << ResetTimer_PWM_SYNC_KILL_SHIFT))

#define ResetTimer_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(ResetTimer_PWM_DEAD_TIME_CYCLE  << ResetTimer_PRESCALER_SHIFT))

#define ResetTimer_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(ResetTimer_PWM_PRESCALER        << ResetTimer_PRESCALER_SHIFT))

#define ResetTimer_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(ResetTimer_TC_PRESCALER            << ResetTimer_PRESCALER_SHIFT))       |\
         ((uint32)(ResetTimer_TC_COUNTER_MODE         << ResetTimer_UPDOWN_SHIFT))          |\
         ((uint32)(ResetTimer_TC_RUN_MODE             << ResetTimer_ONESHOT_SHIFT))         |\
         ((uint32)(ResetTimer_TC_COMP_CAP_MODE        << ResetTimer_MODE_SHIFT)))
        
#define ResetTimer_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(ResetTimer_QUAD_PHIA_SIGNAL_MODE   << ResetTimer_COUNT_SHIFT))           |\
         ((uint32)(ResetTimer_QUAD_INDEX_SIGNAL_MODE  << ResetTimer_RELOAD_SHIFT))          |\
         ((uint32)(ResetTimer_QUAD_STOP_SIGNAL_MODE   << ResetTimer_STOP_SHIFT))            |\
         ((uint32)(ResetTimer_QUAD_PHIB_SIGNAL_MODE   << ResetTimer_START_SHIFT)))

#define ResetTimer_PWM_SIGNALS_MODES                                                              \
        (((uint32)(ResetTimer_PWM_SWITCH_SIGNAL_MODE  << ResetTimer_CAPTURE_SHIFT))         |\
         ((uint32)(ResetTimer_PWM_COUNT_SIGNAL_MODE   << ResetTimer_COUNT_SHIFT))           |\
         ((uint32)(ResetTimer_PWM_RELOAD_SIGNAL_MODE  << ResetTimer_RELOAD_SHIFT))          |\
         ((uint32)(ResetTimer_PWM_STOP_SIGNAL_MODE    << ResetTimer_STOP_SHIFT))            |\
         ((uint32)(ResetTimer_PWM_START_SIGNAL_MODE   << ResetTimer_START_SHIFT)))

#define ResetTimer_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(ResetTimer_TC_CAPTURE_SIGNAL_MODE  << ResetTimer_CAPTURE_SHIFT))         |\
         ((uint32)(ResetTimer_TC_COUNT_SIGNAL_MODE    << ResetTimer_COUNT_SHIFT))           |\
         ((uint32)(ResetTimer_TC_RELOAD_SIGNAL_MODE   << ResetTimer_RELOAD_SHIFT))          |\
         ((uint32)(ResetTimer_TC_STOP_SIGNAL_MODE     << ResetTimer_STOP_SHIFT))            |\
         ((uint32)(ResetTimer_TC_START_SIGNAL_MODE    << ResetTimer_START_SHIFT)))
        
#define ResetTimer_TIMER_UPDOWN_CNT_USED                                                          \
                ((ResetTimer__COUNT_UPDOWN0 == ResetTimer_TC_COUNTER_MODE)                  ||\
                 (ResetTimer__COUNT_UPDOWN1 == ResetTimer_TC_COUNTER_MODE))

#define ResetTimer_PWM_UPDOWN_CNT_USED                                                            \
                ((ResetTimer__CENTER == ResetTimer_PWM_ALIGN)                               ||\
                 (ResetTimer__ASYMMETRIC == ResetTimer_PWM_ALIGN))               
        
#define ResetTimer_PWM_PR_INIT_VALUE              (1u)
#define ResetTimer_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_ResetTimer_H */

/* [] END OF FILE */
