/*******************************************************************************
* File Name: TimerL.h
* Version 2.50
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_Timer_v2_30_TimerL_H)
#define CY_Timer_v2_30_TimerL_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 TimerL_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_50 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define TimerL_Resolution                 8u
#define TimerL_UsingFixedFunction         1u
#define TimerL_UsingHWCaptureCounter      0u
#define TimerL_SoftwareCaptureMode        0u
#define TimerL_SoftwareTriggerMode        0u
#define TimerL_UsingHWEnable              0u
#define TimerL_EnableTriggerMode          0u
#define TimerL_InterruptOnCaptureCount    0u
#define TimerL_RunModeUsed                0u
#define TimerL_ControlRegRemoved          0u


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!TimerL_UsingFixedFunction)
        #if (CY_UDB_V0)
            uint8 TimerUdb;                 /* Timer internal counter value */
            uint8 TimerPeriod;              /* Timer Period value       */
            uint8 InterruptMaskValue;       /* Timer Compare Value */
            #if (TimerL_UsingHWCaptureCounter)
                uint8 TimerCaptureCounter;  /* Timer Capture Counter Value */
            #endif /* variable declaration for backing up Capture Counter value*/
        #endif /* variables for non retention registers in CY_UDB_V0 */

        #if (CY_UDB_V1)
            uint8 TimerUdb;
            uint8 InterruptMaskValue;
            #if (TimerL_UsingHWCaptureCounter)
                uint8 TimerCaptureCounter;
            #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */
        #endif /* (CY_UDB_V1) */

        #if (!TimerL_ControlRegRemoved)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */
}TimerL_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    TimerL_Start(void) ;
void    TimerL_Stop(void) ;

void    TimerL_SetInterruptMode(uint8 interruptMode) ;
uint8   TimerL_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define TimerL_GetInterruptSource() TimerL_ReadStatusRegister()

#if(!TimerL_ControlRegRemoved)
    uint8   TimerL_ReadControlRegister(void) ;
    void    TimerL_WriteControlRegister(uint8 control) \
        ;
#endif /* (!TimerL_ControlRegRemoved) */

uint8  TimerL_ReadPeriod(void) ;
void    TimerL_WritePeriod(uint8 period) \
    ;
uint8  TimerL_ReadCounter(void) ;
void    TimerL_WriteCounter(uint8 counter) \
    ;
uint8  TimerL_ReadCapture(void) ;
void    TimerL_SoftwareCapture(void) ;


#if(!TimerL_UsingFixedFunction) /* UDB Prototypes */
    #if (TimerL_SoftwareCaptureMode)
        void    TimerL_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!TimerL_UsingFixedFunction) */

    #if (TimerL_SoftwareTriggerMode)
        void    TimerL_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (TimerL_SoftwareTriggerMode) */
    #if (TimerL_EnableTriggerMode)
        void    TimerL_EnableTrigger(void) ;
        void    TimerL_DisableTrigger(void) ;
    #endif /* (TimerL_EnableTriggerMode) */

    #if(TimerL_InterruptOnCaptureCount)
        #if(!TimerL_ControlRegRemoved)
            void    TimerL_SetInterruptCount(uint8 interruptCount) \
                ;
        #endif /* (!TimerL_ControlRegRemoved) */
    #endif /* (TimerL_InterruptOnCaptureCount) */

    #if (TimerL_UsingHWCaptureCounter)
        void    TimerL_SetCaptureCount(uint8 captureCount) \
            ;
        uint8   TimerL_ReadCaptureCount(void) ;
    #endif /* (TimerL_UsingHWCaptureCounter) */

    void TimerL_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void TimerL_Init(void)          ;
void TimerL_Enable(void)        ;
void TimerL_SaveConfig(void)    ;
void TimerL_RestoreConfig(void) ;
void TimerL_Sleep(void)         ;
void TimerL_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define TimerL__B_TIMER__CM_NONE 0
#define TimerL__B_TIMER__CM_RISINGEDGE 1
#define TimerL__B_TIMER__CM_FALLINGEDGE 2
#define TimerL__B_TIMER__CM_EITHEREDGE 3
#define TimerL__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define TimerL__B_TIMER__TM_NONE 0x00u
#define TimerL__B_TIMER__TM_RISINGEDGE 0x04u
#define TimerL__B_TIMER__TM_FALLINGEDGE 0x08u
#define TimerL__B_TIMER__TM_EITHEREDGE 0x0Cu
#define TimerL__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define TimerL_INIT_PERIOD             255u
#define TimerL_INIT_CAPTURE_MODE       ((uint8)((uint8)1u << TimerL_CTRL_CAP_MODE_SHIFT))
#define TimerL_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << TimerL_CTRL_TRIG_MODE_SHIFT))
#if (TimerL_UsingFixedFunction)
    #define TimerL_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << TimerL_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << TimerL_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define TimerL_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << TimerL_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << TimerL_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << TimerL_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (TimerL_UsingFixedFunction) */
#define TimerL_INIT_CAPTURE_COUNT      (2u)
#define TimerL_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << TimerL_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (TimerL_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define TimerL_STATUS         (*(reg8 *) TimerL_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define TimerL_STATUS_MASK    (*(reg8 *) TimerL_TimerHW__SR0 )
    #define TimerL_CONTROL        (*(reg8 *) TimerL_TimerHW__CFG0)
    #define TimerL_CONTROL2       (*(reg8 *) TimerL_TimerHW__CFG1)
    #define TimerL_CONTROL2_PTR   ( (reg8 *) TimerL_TimerHW__CFG1)
    #define TimerL_RT1            (*(reg8 *) TimerL_TimerHW__RT1)
    #define TimerL_RT1_PTR        ( (reg8 *) TimerL_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define TimerL_CONTROL3       (*(reg8 *) TimerL_TimerHW__CFG2)
        #define TimerL_CONTROL3_PTR   ( (reg8 *) TimerL_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define TimerL_GLOBAL_ENABLE  (*(reg8 *) TimerL_TimerHW__PM_ACT_CFG)
    #define TimerL_GLOBAL_STBY_ENABLE  (*(reg8 *) TimerL_TimerHW__PM_STBY_CFG)

    #define TimerL_CAPTURE_LSB         (* (reg16 *) TimerL_TimerHW__CAP0 )
    #define TimerL_CAPTURE_LSB_PTR       ((reg16 *) TimerL_TimerHW__CAP0 )
    #define TimerL_PERIOD_LSB          (* (reg16 *) TimerL_TimerHW__PER0 )
    #define TimerL_PERIOD_LSB_PTR        ((reg16 *) TimerL_TimerHW__PER0 )
    #define TimerL_COUNTER_LSB         (* (reg16 *) TimerL_TimerHW__CNT_CMP0 )
    #define TimerL_COUNTER_LSB_PTR       ((reg16 *) TimerL_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define TimerL_BLOCK_EN_MASK                     TimerL_TimerHW__PM_ACT_MSK
    #define TimerL_BLOCK_STBY_EN_MASK                TimerL_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define TimerL_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define TimerL_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define TimerL_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define TimerL_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define TimerL_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define TimerL_CTRL_ENABLE                        ((uint8)((uint8)0x01u << TimerL_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define TimerL_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define TimerL_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << TimerL_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define TimerL_CTRL_MODE_SHIFT                     0x01u
        #define TimerL_CTRL_MODE_MASK                     ((uint8)((uint8)0x07u << TimerL_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define TimerL_CTRL_RCOD_SHIFT        0x02u
        #define TimerL_CTRL_ENBL_SHIFT        0x00u
        #define TimerL_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define TimerL_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << TimerL_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define TimerL_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << TimerL_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define TimerL_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << TimerL_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define TimerL_CTRL_RCOD       ((uint8)((uint8)0x03u << TimerL_CTRL_RCOD_SHIFT))
        #define TimerL_CTRL_ENBL       ((uint8)((uint8)0x80u << TimerL_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define TimerL_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define TimerL_RT1_MASK                        ((uint8)((uint8)0x03u << TimerL_RT1_SHIFT))
    #define TimerL_SYNC                            ((uint8)((uint8)0x03u << TimerL_RT1_SHIFT))
    #define TimerL_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define TimerL_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << TimerL_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define TimerL_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << TimerL_SYNCDSI_SHIFT))

    #define TimerL_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << TimerL_CTRL_MODE_SHIFT))
    #define TimerL_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << TimerL_CTRL_MODE_SHIFT))
    #define TimerL_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << TimerL_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define TimerL_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define TimerL_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define TimerL_STATUS_TC_INT_MASK_SHIFT        (TimerL_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define TimerL_STATUS_CAPTURE_INT_MASK_SHIFT   (TimerL_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define TimerL_STATUS_TC                       ((uint8)((uint8)0x01u << TimerL_STATUS_TC_SHIFT))
    #define TimerL_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << TimerL_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define TimerL_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << TimerL_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define TimerL_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << TimerL_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define TimerL_STATUS              (* (reg8 *) TimerL_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define TimerL_STATUS_MASK         (* (reg8 *) TimerL_TimerUDB_rstSts_stsreg__MASK_REG)
    #define TimerL_STATUS_AUX_CTRL     (* (reg8 *) TimerL_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define TimerL_CONTROL             (* (reg8 *) TimerL_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(TimerL_Resolution <= 8u) /* 8-bit Timer */
        #define TimerL_CAPTURE_LSB         (* (reg8 *) TimerL_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define TimerL_CAPTURE_LSB_PTR       ((reg8 *) TimerL_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define TimerL_PERIOD_LSB          (* (reg8 *) TimerL_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define TimerL_PERIOD_LSB_PTR        ((reg8 *) TimerL_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define TimerL_COUNTER_LSB         (* (reg8 *) TimerL_TimerUDB_sT8_timerdp_u0__A0_REG )
        #define TimerL_COUNTER_LSB_PTR       ((reg8 *) TimerL_TimerUDB_sT8_timerdp_u0__A0_REG )
    #elif(TimerL_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define TimerL_CAPTURE_LSB         (* (reg16 *) TimerL_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define TimerL_CAPTURE_LSB_PTR       ((reg16 *) TimerL_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define TimerL_PERIOD_LSB          (* (reg16 *) TimerL_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define TimerL_PERIOD_LSB_PTR        ((reg16 *) TimerL_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define TimerL_COUNTER_LSB         (* (reg16 *) TimerL_TimerUDB_sT8_timerdp_u0__A0_REG )
            #define TimerL_COUNTER_LSB_PTR       ((reg16 *) TimerL_TimerUDB_sT8_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define TimerL_CAPTURE_LSB         (* (reg16 *) TimerL_TimerUDB_sT8_timerdp_u0__16BIT_F0_REG )
            #define TimerL_CAPTURE_LSB_PTR       ((reg16 *) TimerL_TimerUDB_sT8_timerdp_u0__16BIT_F0_REG )
            #define TimerL_PERIOD_LSB          (* (reg16 *) TimerL_TimerUDB_sT8_timerdp_u0__16BIT_D0_REG )
            #define TimerL_PERIOD_LSB_PTR        ((reg16 *) TimerL_TimerUDB_sT8_timerdp_u0__16BIT_D0_REG )
            #define TimerL_COUNTER_LSB         (* (reg16 *) TimerL_TimerUDB_sT8_timerdp_u0__16BIT_A0_REG )
            #define TimerL_COUNTER_LSB_PTR       ((reg16 *) TimerL_TimerUDB_sT8_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(TimerL_Resolution <= 24u)/* 24-bit Timer */
        #define TimerL_CAPTURE_LSB         (* (reg32 *) TimerL_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define TimerL_CAPTURE_LSB_PTR       ((reg32 *) TimerL_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define TimerL_PERIOD_LSB          (* (reg32 *) TimerL_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define TimerL_PERIOD_LSB_PTR        ((reg32 *) TimerL_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define TimerL_COUNTER_LSB         (* (reg32 *) TimerL_TimerUDB_sT8_timerdp_u0__A0_REG )
        #define TimerL_COUNTER_LSB_PTR       ((reg32 *) TimerL_TimerUDB_sT8_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define TimerL_CAPTURE_LSB         (* (reg32 *) TimerL_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define TimerL_CAPTURE_LSB_PTR       ((reg32 *) TimerL_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define TimerL_PERIOD_LSB          (* (reg32 *) TimerL_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define TimerL_PERIOD_LSB_PTR        ((reg32 *) TimerL_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define TimerL_COUNTER_LSB         (* (reg32 *) TimerL_TimerUDB_sT8_timerdp_u0__A0_REG )
            #define TimerL_COUNTER_LSB_PTR       ((reg32 *) TimerL_TimerUDB_sT8_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define TimerL_CAPTURE_LSB         (* (reg32 *) TimerL_TimerUDB_sT8_timerdp_u0__32BIT_F0_REG )
            #define TimerL_CAPTURE_LSB_PTR       ((reg32 *) TimerL_TimerUDB_sT8_timerdp_u0__32BIT_F0_REG )
            #define TimerL_PERIOD_LSB          (* (reg32 *) TimerL_TimerUDB_sT8_timerdp_u0__32BIT_D0_REG )
            #define TimerL_PERIOD_LSB_PTR        ((reg32 *) TimerL_TimerUDB_sT8_timerdp_u0__32BIT_D0_REG )
            #define TimerL_COUNTER_LSB         (* (reg32 *) TimerL_TimerUDB_sT8_timerdp_u0__32BIT_A0_REG )
            #define TimerL_COUNTER_LSB_PTR       ((reg32 *) TimerL_TimerUDB_sT8_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #if (TimerL_UsingHWCaptureCounter)
        #define TimerL_CAP_COUNT              (*(reg8 *) TimerL_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define TimerL_CAP_COUNT_PTR          ( (reg8 *) TimerL_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define TimerL_CAPTURE_COUNT_CTRL     (*(reg8 *) TimerL_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define TimerL_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) TimerL_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (TimerL_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define TimerL_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define TimerL_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define TimerL_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define TimerL_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define TimerL_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define TimerL_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << TimerL_CTRL_INTCNT_SHIFT))
    #define TimerL_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << TimerL_CTRL_TRIG_MODE_SHIFT))
    #define TimerL_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << TimerL_CTRL_TRIG_EN_SHIFT))
    #define TimerL_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << TimerL_CTRL_CAP_MODE_SHIFT))
    #define TimerL_CTRL_ENABLE                    ((uint8)((uint8)0x01u << TimerL_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define TimerL_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define TimerL_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define TimerL_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define TimerL_STATUS_TC_INT_MASK_SHIFT       TimerL_STATUS_TC_SHIFT
    #define TimerL_STATUS_CAPTURE_INT_MASK_SHIFT  TimerL_STATUS_CAPTURE_SHIFT
    #define TimerL_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define TimerL_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define TimerL_STATUS_FIFOFULL_INT_MASK_SHIFT TimerL_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define TimerL_STATUS_TC                      ((uint8)((uint8)0x01u << TimerL_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define TimerL_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << TimerL_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define TimerL_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << TimerL_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define TimerL_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << TimerL_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define TimerL_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << TimerL_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define TimerL_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << TimerL_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define TimerL_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << TimerL_STATUS_FIFOFULL_SHIFT))

    #define TimerL_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define TimerL_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define TimerL_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define TimerL_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define TimerL_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define TimerL_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_Timer_v2_30_TimerL_H */


/* [] END OF FILE */
