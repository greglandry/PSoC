/*******************************************************************************
* File Name: TimerR.h
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

#if !defined(CY_Timer_v2_30_TimerR_H)
#define CY_Timer_v2_30_TimerR_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 TimerR_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_50 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define TimerR_Resolution                 8u
#define TimerR_UsingFixedFunction         1u
#define TimerR_UsingHWCaptureCounter      0u
#define TimerR_SoftwareCaptureMode        0u
#define TimerR_SoftwareTriggerMode        0u
#define TimerR_UsingHWEnable              0u
#define TimerR_EnableTriggerMode          0u
#define TimerR_InterruptOnCaptureCount    0u
#define TimerR_RunModeUsed                0u
#define TimerR_ControlRegRemoved          0u


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!TimerR_UsingFixedFunction)
        #if (CY_UDB_V0)
            uint8 TimerUdb;                 /* Timer internal counter value */
            uint8 TimerPeriod;              /* Timer Period value       */
            uint8 InterruptMaskValue;       /* Timer Compare Value */
            #if (TimerR_UsingHWCaptureCounter)
                uint8 TimerCaptureCounter;  /* Timer Capture Counter Value */
            #endif /* variable declaration for backing up Capture Counter value*/
        #endif /* variables for non retention registers in CY_UDB_V0 */

        #if (CY_UDB_V1)
            uint8 TimerUdb;
            uint8 InterruptMaskValue;
            #if (TimerR_UsingHWCaptureCounter)
                uint8 TimerCaptureCounter;
            #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */
        #endif /* (CY_UDB_V1) */

        #if (!TimerR_ControlRegRemoved)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */
}TimerR_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    TimerR_Start(void) ;
void    TimerR_Stop(void) ;

void    TimerR_SetInterruptMode(uint8 interruptMode) ;
uint8   TimerR_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define TimerR_GetInterruptSource() TimerR_ReadStatusRegister()

#if(!TimerR_ControlRegRemoved)
    uint8   TimerR_ReadControlRegister(void) ;
    void    TimerR_WriteControlRegister(uint8 control) \
        ;
#endif /* (!TimerR_ControlRegRemoved) */

uint8  TimerR_ReadPeriod(void) ;
void    TimerR_WritePeriod(uint8 period) \
    ;
uint8  TimerR_ReadCounter(void) ;
void    TimerR_WriteCounter(uint8 counter) \
    ;
uint8  TimerR_ReadCapture(void) ;
void    TimerR_SoftwareCapture(void) ;


#if(!TimerR_UsingFixedFunction) /* UDB Prototypes */
    #if (TimerR_SoftwareCaptureMode)
        void    TimerR_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!TimerR_UsingFixedFunction) */

    #if (TimerR_SoftwareTriggerMode)
        void    TimerR_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (TimerR_SoftwareTriggerMode) */
    #if (TimerR_EnableTriggerMode)
        void    TimerR_EnableTrigger(void) ;
        void    TimerR_DisableTrigger(void) ;
    #endif /* (TimerR_EnableTriggerMode) */

    #if(TimerR_InterruptOnCaptureCount)
        #if(!TimerR_ControlRegRemoved)
            void    TimerR_SetInterruptCount(uint8 interruptCount) \
                ;
        #endif /* (!TimerR_ControlRegRemoved) */
    #endif /* (TimerR_InterruptOnCaptureCount) */

    #if (TimerR_UsingHWCaptureCounter)
        void    TimerR_SetCaptureCount(uint8 captureCount) \
            ;
        uint8   TimerR_ReadCaptureCount(void) ;
    #endif /* (TimerR_UsingHWCaptureCounter) */

    void TimerR_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void TimerR_Init(void)          ;
void TimerR_Enable(void)        ;
void TimerR_SaveConfig(void)    ;
void TimerR_RestoreConfig(void) ;
void TimerR_Sleep(void)         ;
void TimerR_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define TimerR__B_TIMER__CM_NONE 0
#define TimerR__B_TIMER__CM_RISINGEDGE 1
#define TimerR__B_TIMER__CM_FALLINGEDGE 2
#define TimerR__B_TIMER__CM_EITHEREDGE 3
#define TimerR__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define TimerR__B_TIMER__TM_NONE 0x00u
#define TimerR__B_TIMER__TM_RISINGEDGE 0x04u
#define TimerR__B_TIMER__TM_FALLINGEDGE 0x08u
#define TimerR__B_TIMER__TM_EITHEREDGE 0x0Cu
#define TimerR__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define TimerR_INIT_PERIOD             255u
#define TimerR_INIT_CAPTURE_MODE       ((uint8)((uint8)1u << TimerR_CTRL_CAP_MODE_SHIFT))
#define TimerR_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << TimerR_CTRL_TRIG_MODE_SHIFT))
#if (TimerR_UsingFixedFunction)
    #define TimerR_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << TimerR_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << TimerR_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define TimerR_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << TimerR_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << TimerR_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << TimerR_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (TimerR_UsingFixedFunction) */
#define TimerR_INIT_CAPTURE_COUNT      (2u)
#define TimerR_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << TimerR_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (TimerR_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define TimerR_STATUS         (*(reg8 *) TimerR_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define TimerR_STATUS_MASK    (*(reg8 *) TimerR_TimerHW__SR0 )
    #define TimerR_CONTROL        (*(reg8 *) TimerR_TimerHW__CFG0)
    #define TimerR_CONTROL2       (*(reg8 *) TimerR_TimerHW__CFG1)
    #define TimerR_CONTROL2_PTR   ( (reg8 *) TimerR_TimerHW__CFG1)
    #define TimerR_RT1            (*(reg8 *) TimerR_TimerHW__RT1)
    #define TimerR_RT1_PTR        ( (reg8 *) TimerR_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define TimerR_CONTROL3       (*(reg8 *) TimerR_TimerHW__CFG2)
        #define TimerR_CONTROL3_PTR   ( (reg8 *) TimerR_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define TimerR_GLOBAL_ENABLE  (*(reg8 *) TimerR_TimerHW__PM_ACT_CFG)
    #define TimerR_GLOBAL_STBY_ENABLE  (*(reg8 *) TimerR_TimerHW__PM_STBY_CFG)

    #define TimerR_CAPTURE_LSB         (* (reg16 *) TimerR_TimerHW__CAP0 )
    #define TimerR_CAPTURE_LSB_PTR       ((reg16 *) TimerR_TimerHW__CAP0 )
    #define TimerR_PERIOD_LSB          (* (reg16 *) TimerR_TimerHW__PER0 )
    #define TimerR_PERIOD_LSB_PTR        ((reg16 *) TimerR_TimerHW__PER0 )
    #define TimerR_COUNTER_LSB         (* (reg16 *) TimerR_TimerHW__CNT_CMP0 )
    #define TimerR_COUNTER_LSB_PTR       ((reg16 *) TimerR_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define TimerR_BLOCK_EN_MASK                     TimerR_TimerHW__PM_ACT_MSK
    #define TimerR_BLOCK_STBY_EN_MASK                TimerR_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define TimerR_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define TimerR_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define TimerR_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define TimerR_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define TimerR_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define TimerR_CTRL_ENABLE                        ((uint8)((uint8)0x01u << TimerR_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define TimerR_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define TimerR_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << TimerR_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define TimerR_CTRL_MODE_SHIFT                     0x01u
        #define TimerR_CTRL_MODE_MASK                     ((uint8)((uint8)0x07u << TimerR_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define TimerR_CTRL_RCOD_SHIFT        0x02u
        #define TimerR_CTRL_ENBL_SHIFT        0x00u
        #define TimerR_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define TimerR_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << TimerR_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define TimerR_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << TimerR_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define TimerR_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << TimerR_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define TimerR_CTRL_RCOD       ((uint8)((uint8)0x03u << TimerR_CTRL_RCOD_SHIFT))
        #define TimerR_CTRL_ENBL       ((uint8)((uint8)0x80u << TimerR_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define TimerR_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define TimerR_RT1_MASK                        ((uint8)((uint8)0x03u << TimerR_RT1_SHIFT))
    #define TimerR_SYNC                            ((uint8)((uint8)0x03u << TimerR_RT1_SHIFT))
    #define TimerR_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define TimerR_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << TimerR_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define TimerR_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << TimerR_SYNCDSI_SHIFT))

    #define TimerR_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << TimerR_CTRL_MODE_SHIFT))
    #define TimerR_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << TimerR_CTRL_MODE_SHIFT))
    #define TimerR_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << TimerR_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define TimerR_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define TimerR_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define TimerR_STATUS_TC_INT_MASK_SHIFT        (TimerR_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define TimerR_STATUS_CAPTURE_INT_MASK_SHIFT   (TimerR_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define TimerR_STATUS_TC                       ((uint8)((uint8)0x01u << TimerR_STATUS_TC_SHIFT))
    #define TimerR_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << TimerR_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define TimerR_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << TimerR_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define TimerR_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << TimerR_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define TimerR_STATUS              (* (reg8 *) TimerR_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define TimerR_STATUS_MASK         (* (reg8 *) TimerR_TimerUDB_rstSts_stsreg__MASK_REG)
    #define TimerR_STATUS_AUX_CTRL     (* (reg8 *) TimerR_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define TimerR_CONTROL             (* (reg8 *) TimerR_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(TimerR_Resolution <= 8u) /* 8-bit Timer */
        #define TimerR_CAPTURE_LSB         (* (reg8 *) TimerR_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define TimerR_CAPTURE_LSB_PTR       ((reg8 *) TimerR_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define TimerR_PERIOD_LSB          (* (reg8 *) TimerR_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define TimerR_PERIOD_LSB_PTR        ((reg8 *) TimerR_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define TimerR_COUNTER_LSB         (* (reg8 *) TimerR_TimerUDB_sT8_timerdp_u0__A0_REG )
        #define TimerR_COUNTER_LSB_PTR       ((reg8 *) TimerR_TimerUDB_sT8_timerdp_u0__A0_REG )
    #elif(TimerR_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define TimerR_CAPTURE_LSB         (* (reg16 *) TimerR_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define TimerR_CAPTURE_LSB_PTR       ((reg16 *) TimerR_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define TimerR_PERIOD_LSB          (* (reg16 *) TimerR_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define TimerR_PERIOD_LSB_PTR        ((reg16 *) TimerR_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define TimerR_COUNTER_LSB         (* (reg16 *) TimerR_TimerUDB_sT8_timerdp_u0__A0_REG )
            #define TimerR_COUNTER_LSB_PTR       ((reg16 *) TimerR_TimerUDB_sT8_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define TimerR_CAPTURE_LSB         (* (reg16 *) TimerR_TimerUDB_sT8_timerdp_u0__16BIT_F0_REG )
            #define TimerR_CAPTURE_LSB_PTR       ((reg16 *) TimerR_TimerUDB_sT8_timerdp_u0__16BIT_F0_REG )
            #define TimerR_PERIOD_LSB          (* (reg16 *) TimerR_TimerUDB_sT8_timerdp_u0__16BIT_D0_REG )
            #define TimerR_PERIOD_LSB_PTR        ((reg16 *) TimerR_TimerUDB_sT8_timerdp_u0__16BIT_D0_REG )
            #define TimerR_COUNTER_LSB         (* (reg16 *) TimerR_TimerUDB_sT8_timerdp_u0__16BIT_A0_REG )
            #define TimerR_COUNTER_LSB_PTR       ((reg16 *) TimerR_TimerUDB_sT8_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(TimerR_Resolution <= 24u)/* 24-bit Timer */
        #define TimerR_CAPTURE_LSB         (* (reg32 *) TimerR_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define TimerR_CAPTURE_LSB_PTR       ((reg32 *) TimerR_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define TimerR_PERIOD_LSB          (* (reg32 *) TimerR_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define TimerR_PERIOD_LSB_PTR        ((reg32 *) TimerR_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define TimerR_COUNTER_LSB         (* (reg32 *) TimerR_TimerUDB_sT8_timerdp_u0__A0_REG )
        #define TimerR_COUNTER_LSB_PTR       ((reg32 *) TimerR_TimerUDB_sT8_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define TimerR_CAPTURE_LSB         (* (reg32 *) TimerR_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define TimerR_CAPTURE_LSB_PTR       ((reg32 *) TimerR_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define TimerR_PERIOD_LSB          (* (reg32 *) TimerR_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define TimerR_PERIOD_LSB_PTR        ((reg32 *) TimerR_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define TimerR_COUNTER_LSB         (* (reg32 *) TimerR_TimerUDB_sT8_timerdp_u0__A0_REG )
            #define TimerR_COUNTER_LSB_PTR       ((reg32 *) TimerR_TimerUDB_sT8_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define TimerR_CAPTURE_LSB         (* (reg32 *) TimerR_TimerUDB_sT8_timerdp_u0__32BIT_F0_REG )
            #define TimerR_CAPTURE_LSB_PTR       ((reg32 *) TimerR_TimerUDB_sT8_timerdp_u0__32BIT_F0_REG )
            #define TimerR_PERIOD_LSB          (* (reg32 *) TimerR_TimerUDB_sT8_timerdp_u0__32BIT_D0_REG )
            #define TimerR_PERIOD_LSB_PTR        ((reg32 *) TimerR_TimerUDB_sT8_timerdp_u0__32BIT_D0_REG )
            #define TimerR_COUNTER_LSB         (* (reg32 *) TimerR_TimerUDB_sT8_timerdp_u0__32BIT_A0_REG )
            #define TimerR_COUNTER_LSB_PTR       ((reg32 *) TimerR_TimerUDB_sT8_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #if (TimerR_UsingHWCaptureCounter)
        #define TimerR_CAP_COUNT              (*(reg8 *) TimerR_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define TimerR_CAP_COUNT_PTR          ( (reg8 *) TimerR_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define TimerR_CAPTURE_COUNT_CTRL     (*(reg8 *) TimerR_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define TimerR_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) TimerR_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (TimerR_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define TimerR_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define TimerR_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define TimerR_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define TimerR_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define TimerR_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define TimerR_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << TimerR_CTRL_INTCNT_SHIFT))
    #define TimerR_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << TimerR_CTRL_TRIG_MODE_SHIFT))
    #define TimerR_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << TimerR_CTRL_TRIG_EN_SHIFT))
    #define TimerR_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << TimerR_CTRL_CAP_MODE_SHIFT))
    #define TimerR_CTRL_ENABLE                    ((uint8)((uint8)0x01u << TimerR_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define TimerR_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define TimerR_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define TimerR_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define TimerR_STATUS_TC_INT_MASK_SHIFT       TimerR_STATUS_TC_SHIFT
    #define TimerR_STATUS_CAPTURE_INT_MASK_SHIFT  TimerR_STATUS_CAPTURE_SHIFT
    #define TimerR_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define TimerR_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define TimerR_STATUS_FIFOFULL_INT_MASK_SHIFT TimerR_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define TimerR_STATUS_TC                      ((uint8)((uint8)0x01u << TimerR_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define TimerR_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << TimerR_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define TimerR_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << TimerR_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define TimerR_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << TimerR_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define TimerR_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << TimerR_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define TimerR_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << TimerR_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define TimerR_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << TimerR_STATUS_FIFOFULL_SHIFT))

    #define TimerR_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define TimerR_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define TimerR_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define TimerR_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define TimerR_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define TimerR_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_Timer_v2_30_TimerR_H */


/* [] END OF FILE */
