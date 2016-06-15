/*******************************************************************************
* File Name: TimerLC.h
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

#if !defined(CY_Timer_v2_30_TimerLC_H)
#define CY_Timer_v2_30_TimerLC_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 TimerLC_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_50 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define TimerLC_Resolution                 8u
#define TimerLC_UsingFixedFunction         1u
#define TimerLC_UsingHWCaptureCounter      0u
#define TimerLC_SoftwareCaptureMode        0u
#define TimerLC_SoftwareTriggerMode        0u
#define TimerLC_UsingHWEnable              0u
#define TimerLC_EnableTriggerMode          0u
#define TimerLC_InterruptOnCaptureCount    0u
#define TimerLC_RunModeUsed                0u
#define TimerLC_ControlRegRemoved          0u


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!TimerLC_UsingFixedFunction)
        #if (CY_UDB_V0)
            uint8 TimerUdb;                 /* Timer internal counter value */
            uint8 TimerPeriod;              /* Timer Period value       */
            uint8 InterruptMaskValue;       /* Timer Compare Value */
            #if (TimerLC_UsingHWCaptureCounter)
                uint8 TimerCaptureCounter;  /* Timer Capture Counter Value */
            #endif /* variable declaration for backing up Capture Counter value*/
        #endif /* variables for non retention registers in CY_UDB_V0 */

        #if (CY_UDB_V1)
            uint8 TimerUdb;
            uint8 InterruptMaskValue;
            #if (TimerLC_UsingHWCaptureCounter)
                uint8 TimerCaptureCounter;
            #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */
        #endif /* (CY_UDB_V1) */

        #if (!TimerLC_ControlRegRemoved)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */
}TimerLC_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    TimerLC_Start(void) ;
void    TimerLC_Stop(void) ;

void    TimerLC_SetInterruptMode(uint8 interruptMode) ;
uint8   TimerLC_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define TimerLC_GetInterruptSource() TimerLC_ReadStatusRegister()

#if(!TimerLC_ControlRegRemoved)
    uint8   TimerLC_ReadControlRegister(void) ;
    void    TimerLC_WriteControlRegister(uint8 control) \
        ;
#endif /* (!TimerLC_ControlRegRemoved) */

uint8  TimerLC_ReadPeriod(void) ;
void    TimerLC_WritePeriod(uint8 period) \
    ;
uint8  TimerLC_ReadCounter(void) ;
void    TimerLC_WriteCounter(uint8 counter) \
    ;
uint8  TimerLC_ReadCapture(void) ;
void    TimerLC_SoftwareCapture(void) ;


#if(!TimerLC_UsingFixedFunction) /* UDB Prototypes */
    #if (TimerLC_SoftwareCaptureMode)
        void    TimerLC_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!TimerLC_UsingFixedFunction) */

    #if (TimerLC_SoftwareTriggerMode)
        void    TimerLC_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (TimerLC_SoftwareTriggerMode) */
    #if (TimerLC_EnableTriggerMode)
        void    TimerLC_EnableTrigger(void) ;
        void    TimerLC_DisableTrigger(void) ;
    #endif /* (TimerLC_EnableTriggerMode) */

    #if(TimerLC_InterruptOnCaptureCount)
        #if(!TimerLC_ControlRegRemoved)
            void    TimerLC_SetInterruptCount(uint8 interruptCount) \
                ;
        #endif /* (!TimerLC_ControlRegRemoved) */
    #endif /* (TimerLC_InterruptOnCaptureCount) */

    #if (TimerLC_UsingHWCaptureCounter)
        void    TimerLC_SetCaptureCount(uint8 captureCount) \
            ;
        uint8   TimerLC_ReadCaptureCount(void) ;
    #endif /* (TimerLC_UsingHWCaptureCounter) */

    void TimerLC_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void TimerLC_Init(void)          ;
void TimerLC_Enable(void)        ;
void TimerLC_SaveConfig(void)    ;
void TimerLC_RestoreConfig(void) ;
void TimerLC_Sleep(void)         ;
void TimerLC_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define TimerLC__B_TIMER__CM_NONE 0
#define TimerLC__B_TIMER__CM_RISINGEDGE 1
#define TimerLC__B_TIMER__CM_FALLINGEDGE 2
#define TimerLC__B_TIMER__CM_EITHEREDGE 3
#define TimerLC__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define TimerLC__B_TIMER__TM_NONE 0x00u
#define TimerLC__B_TIMER__TM_RISINGEDGE 0x04u
#define TimerLC__B_TIMER__TM_FALLINGEDGE 0x08u
#define TimerLC__B_TIMER__TM_EITHEREDGE 0x0Cu
#define TimerLC__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define TimerLC_INIT_PERIOD             255u
#define TimerLC_INIT_CAPTURE_MODE       ((uint8)((uint8)1u << TimerLC_CTRL_CAP_MODE_SHIFT))
#define TimerLC_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << TimerLC_CTRL_TRIG_MODE_SHIFT))
#if (TimerLC_UsingFixedFunction)
    #define TimerLC_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << TimerLC_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << TimerLC_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define TimerLC_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << TimerLC_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << TimerLC_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << TimerLC_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (TimerLC_UsingFixedFunction) */
#define TimerLC_INIT_CAPTURE_COUNT      (2u)
#define TimerLC_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << TimerLC_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (TimerLC_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define TimerLC_STATUS         (*(reg8 *) TimerLC_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define TimerLC_STATUS_MASK    (*(reg8 *) TimerLC_TimerHW__SR0 )
    #define TimerLC_CONTROL        (*(reg8 *) TimerLC_TimerHW__CFG0)
    #define TimerLC_CONTROL2       (*(reg8 *) TimerLC_TimerHW__CFG1)
    #define TimerLC_CONTROL2_PTR   ( (reg8 *) TimerLC_TimerHW__CFG1)
    #define TimerLC_RT1            (*(reg8 *) TimerLC_TimerHW__RT1)
    #define TimerLC_RT1_PTR        ( (reg8 *) TimerLC_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define TimerLC_CONTROL3       (*(reg8 *) TimerLC_TimerHW__CFG2)
        #define TimerLC_CONTROL3_PTR   ( (reg8 *) TimerLC_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define TimerLC_GLOBAL_ENABLE  (*(reg8 *) TimerLC_TimerHW__PM_ACT_CFG)
    #define TimerLC_GLOBAL_STBY_ENABLE  (*(reg8 *) TimerLC_TimerHW__PM_STBY_CFG)

    #define TimerLC_CAPTURE_LSB         (* (reg16 *) TimerLC_TimerHW__CAP0 )
    #define TimerLC_CAPTURE_LSB_PTR       ((reg16 *) TimerLC_TimerHW__CAP0 )
    #define TimerLC_PERIOD_LSB          (* (reg16 *) TimerLC_TimerHW__PER0 )
    #define TimerLC_PERIOD_LSB_PTR        ((reg16 *) TimerLC_TimerHW__PER0 )
    #define TimerLC_COUNTER_LSB         (* (reg16 *) TimerLC_TimerHW__CNT_CMP0 )
    #define TimerLC_COUNTER_LSB_PTR       ((reg16 *) TimerLC_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define TimerLC_BLOCK_EN_MASK                     TimerLC_TimerHW__PM_ACT_MSK
    #define TimerLC_BLOCK_STBY_EN_MASK                TimerLC_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define TimerLC_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define TimerLC_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define TimerLC_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define TimerLC_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define TimerLC_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define TimerLC_CTRL_ENABLE                        ((uint8)((uint8)0x01u << TimerLC_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define TimerLC_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define TimerLC_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << TimerLC_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define TimerLC_CTRL_MODE_SHIFT                     0x01u
        #define TimerLC_CTRL_MODE_MASK                     ((uint8)((uint8)0x07u << TimerLC_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define TimerLC_CTRL_RCOD_SHIFT        0x02u
        #define TimerLC_CTRL_ENBL_SHIFT        0x00u
        #define TimerLC_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define TimerLC_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << TimerLC_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define TimerLC_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << TimerLC_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define TimerLC_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << TimerLC_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define TimerLC_CTRL_RCOD       ((uint8)((uint8)0x03u << TimerLC_CTRL_RCOD_SHIFT))
        #define TimerLC_CTRL_ENBL       ((uint8)((uint8)0x80u << TimerLC_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define TimerLC_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define TimerLC_RT1_MASK                        ((uint8)((uint8)0x03u << TimerLC_RT1_SHIFT))
    #define TimerLC_SYNC                            ((uint8)((uint8)0x03u << TimerLC_RT1_SHIFT))
    #define TimerLC_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define TimerLC_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << TimerLC_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define TimerLC_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << TimerLC_SYNCDSI_SHIFT))

    #define TimerLC_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << TimerLC_CTRL_MODE_SHIFT))
    #define TimerLC_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << TimerLC_CTRL_MODE_SHIFT))
    #define TimerLC_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << TimerLC_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define TimerLC_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define TimerLC_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define TimerLC_STATUS_TC_INT_MASK_SHIFT        (TimerLC_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define TimerLC_STATUS_CAPTURE_INT_MASK_SHIFT   (TimerLC_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define TimerLC_STATUS_TC                       ((uint8)((uint8)0x01u << TimerLC_STATUS_TC_SHIFT))
    #define TimerLC_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << TimerLC_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define TimerLC_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << TimerLC_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define TimerLC_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << TimerLC_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define TimerLC_STATUS              (* (reg8 *) TimerLC_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define TimerLC_STATUS_MASK         (* (reg8 *) TimerLC_TimerUDB_rstSts_stsreg__MASK_REG)
    #define TimerLC_STATUS_AUX_CTRL     (* (reg8 *) TimerLC_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define TimerLC_CONTROL             (* (reg8 *) TimerLC_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(TimerLC_Resolution <= 8u) /* 8-bit Timer */
        #define TimerLC_CAPTURE_LSB         (* (reg8 *) TimerLC_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define TimerLC_CAPTURE_LSB_PTR       ((reg8 *) TimerLC_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define TimerLC_PERIOD_LSB          (* (reg8 *) TimerLC_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define TimerLC_PERIOD_LSB_PTR        ((reg8 *) TimerLC_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define TimerLC_COUNTER_LSB         (* (reg8 *) TimerLC_TimerUDB_sT8_timerdp_u0__A0_REG )
        #define TimerLC_COUNTER_LSB_PTR       ((reg8 *) TimerLC_TimerUDB_sT8_timerdp_u0__A0_REG )
    #elif(TimerLC_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define TimerLC_CAPTURE_LSB         (* (reg16 *) TimerLC_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define TimerLC_CAPTURE_LSB_PTR       ((reg16 *) TimerLC_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define TimerLC_PERIOD_LSB          (* (reg16 *) TimerLC_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define TimerLC_PERIOD_LSB_PTR        ((reg16 *) TimerLC_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define TimerLC_COUNTER_LSB         (* (reg16 *) TimerLC_TimerUDB_sT8_timerdp_u0__A0_REG )
            #define TimerLC_COUNTER_LSB_PTR       ((reg16 *) TimerLC_TimerUDB_sT8_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define TimerLC_CAPTURE_LSB         (* (reg16 *) TimerLC_TimerUDB_sT8_timerdp_u0__16BIT_F0_REG )
            #define TimerLC_CAPTURE_LSB_PTR       ((reg16 *) TimerLC_TimerUDB_sT8_timerdp_u0__16BIT_F0_REG )
            #define TimerLC_PERIOD_LSB          (* (reg16 *) TimerLC_TimerUDB_sT8_timerdp_u0__16BIT_D0_REG )
            #define TimerLC_PERIOD_LSB_PTR        ((reg16 *) TimerLC_TimerUDB_sT8_timerdp_u0__16BIT_D0_REG )
            #define TimerLC_COUNTER_LSB         (* (reg16 *) TimerLC_TimerUDB_sT8_timerdp_u0__16BIT_A0_REG )
            #define TimerLC_COUNTER_LSB_PTR       ((reg16 *) TimerLC_TimerUDB_sT8_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(TimerLC_Resolution <= 24u)/* 24-bit Timer */
        #define TimerLC_CAPTURE_LSB         (* (reg32 *) TimerLC_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define TimerLC_CAPTURE_LSB_PTR       ((reg32 *) TimerLC_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define TimerLC_PERIOD_LSB          (* (reg32 *) TimerLC_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define TimerLC_PERIOD_LSB_PTR        ((reg32 *) TimerLC_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define TimerLC_COUNTER_LSB         (* (reg32 *) TimerLC_TimerUDB_sT8_timerdp_u0__A0_REG )
        #define TimerLC_COUNTER_LSB_PTR       ((reg32 *) TimerLC_TimerUDB_sT8_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define TimerLC_CAPTURE_LSB         (* (reg32 *) TimerLC_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define TimerLC_CAPTURE_LSB_PTR       ((reg32 *) TimerLC_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define TimerLC_PERIOD_LSB          (* (reg32 *) TimerLC_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define TimerLC_PERIOD_LSB_PTR        ((reg32 *) TimerLC_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define TimerLC_COUNTER_LSB         (* (reg32 *) TimerLC_TimerUDB_sT8_timerdp_u0__A0_REG )
            #define TimerLC_COUNTER_LSB_PTR       ((reg32 *) TimerLC_TimerUDB_sT8_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define TimerLC_CAPTURE_LSB         (* (reg32 *) TimerLC_TimerUDB_sT8_timerdp_u0__32BIT_F0_REG )
            #define TimerLC_CAPTURE_LSB_PTR       ((reg32 *) TimerLC_TimerUDB_sT8_timerdp_u0__32BIT_F0_REG )
            #define TimerLC_PERIOD_LSB          (* (reg32 *) TimerLC_TimerUDB_sT8_timerdp_u0__32BIT_D0_REG )
            #define TimerLC_PERIOD_LSB_PTR        ((reg32 *) TimerLC_TimerUDB_sT8_timerdp_u0__32BIT_D0_REG )
            #define TimerLC_COUNTER_LSB         (* (reg32 *) TimerLC_TimerUDB_sT8_timerdp_u0__32BIT_A0_REG )
            #define TimerLC_COUNTER_LSB_PTR       ((reg32 *) TimerLC_TimerUDB_sT8_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #if (TimerLC_UsingHWCaptureCounter)
        #define TimerLC_CAP_COUNT              (*(reg8 *) TimerLC_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define TimerLC_CAP_COUNT_PTR          ( (reg8 *) TimerLC_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define TimerLC_CAPTURE_COUNT_CTRL     (*(reg8 *) TimerLC_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define TimerLC_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) TimerLC_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (TimerLC_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define TimerLC_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define TimerLC_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define TimerLC_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define TimerLC_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define TimerLC_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define TimerLC_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << TimerLC_CTRL_INTCNT_SHIFT))
    #define TimerLC_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << TimerLC_CTRL_TRIG_MODE_SHIFT))
    #define TimerLC_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << TimerLC_CTRL_TRIG_EN_SHIFT))
    #define TimerLC_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << TimerLC_CTRL_CAP_MODE_SHIFT))
    #define TimerLC_CTRL_ENABLE                    ((uint8)((uint8)0x01u << TimerLC_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define TimerLC_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define TimerLC_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define TimerLC_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define TimerLC_STATUS_TC_INT_MASK_SHIFT       TimerLC_STATUS_TC_SHIFT
    #define TimerLC_STATUS_CAPTURE_INT_MASK_SHIFT  TimerLC_STATUS_CAPTURE_SHIFT
    #define TimerLC_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define TimerLC_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define TimerLC_STATUS_FIFOFULL_INT_MASK_SHIFT TimerLC_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define TimerLC_STATUS_TC                      ((uint8)((uint8)0x01u << TimerLC_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define TimerLC_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << TimerLC_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define TimerLC_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << TimerLC_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define TimerLC_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << TimerLC_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define TimerLC_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << TimerLC_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define TimerLC_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << TimerLC_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define TimerLC_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << TimerLC_STATUS_FIFOFULL_SHIFT))

    #define TimerLC_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define TimerLC_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define TimerLC_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define TimerLC_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define TimerLC_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define TimerLC_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_Timer_v2_30_TimerLC_H */


/* [] END OF FILE */
