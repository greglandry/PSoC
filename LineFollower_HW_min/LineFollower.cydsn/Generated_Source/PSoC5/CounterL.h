/*******************************************************************************
* File Name: CounterL.h  
* Version 2.40
*
*  Description:
*   Contains the function prototypes and constants available to the counter
*   user module.
*
*   Note:
*    None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/
    
#if !defined(CY_COUNTER_CounterL_H)
#define CY_COUNTER_CounterL_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 CounterL_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Counter_v2_40 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults        
**************************************/

#define CounterL_Resolution            8u
#define CounterL_UsingFixedFunction    1u
#define CounterL_ControlRegRemoved     0u
#define CounterL_COMPARE_MODE_SOFTWARE 0u
#define CounterL_CAPTURE_MODE_SOFTWARE 0u
#define CounterL_RunModeUsed           0u


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Mode API Support
 * Backup structure for Sleep Wake up operations
 *************************************************************************/
typedef struct
{
    uint8 CounterEnableState; 
    uint8 CounterUdb;         /* Current Counter Value */

    #if (CY_UDB_V0)
        uint8 CounterPeriod;  /* Counter Period Value */
        uint8 CompareValue;   /* Counter Compare Value */           
        uint8 InterruptMaskValue;                   /* Counter Interrupt Mask Value */
    #endif /* (CY_UDB_V0) */

    #if (!CounterL_ControlRegRemoved)
        uint8 CounterControlRegister;               /* Counter Control Register */
    #endif /* (!CounterL_ControlRegRemoved) */

}CounterL_backupStruct;


/**************************************
 *  Function Prototypes
 *************************************/
void    CounterL_Start(void) ;
void    CounterL_Stop(void) ;
void    CounterL_SetInterruptMode(uint8 interruptsMask) ;
uint8   CounterL_ReadStatusRegister(void) ;
#define CounterL_GetInterruptSource() CounterL_ReadStatusRegister()
#if(!CounterL_ControlRegRemoved)
    uint8   CounterL_ReadControlRegister(void) ;
    void    CounterL_WriteControlRegister(uint8 control) \
        ;
#endif /* (!CounterL_ControlRegRemoved) */
#if (!(CounterL_UsingFixedFunction && (CY_PSOC5A)))
    void    CounterL_WriteCounter(uint8 counter) \
            ; 
#endif /* (!(CounterL_UsingFixedFunction && (CY_PSOC5A))) */
uint8  CounterL_ReadCounter(void) ;
uint8  CounterL_ReadCapture(void) ;
void    CounterL_WritePeriod(uint8 period) \
    ;
uint8  CounterL_ReadPeriod( void ) ;
#if (!CounterL_UsingFixedFunction)
    void    CounterL_WriteCompare(uint8 compare) \
        ;
    uint8  CounterL_ReadCompare( void ) \
        ;
#endif /* (!CounterL_UsingFixedFunction) */

#if (CounterL_COMPARE_MODE_SOFTWARE)
    void    CounterL_SetCompareMode(uint8 compareMode) ;
#endif /* (CounterL_COMPARE_MODE_SOFTWARE) */
#if (CounterL_CAPTURE_MODE_SOFTWARE)
    void    CounterL_SetCaptureMode(uint8 captureMode) ;
#endif /* (CounterL_CAPTURE_MODE_SOFTWARE) */
void CounterL_ClearFIFO(void)     ;
void CounterL_Init(void)          ;
void CounterL_Enable(void)        ;
void CounterL_SaveConfig(void)    ;
void CounterL_RestoreConfig(void) ;
void CounterL_Sleep(void)         ;
void CounterL_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Counter__CompareModes, Used in Compare Mode retained for backward compatibility of tests*/
#define CounterL__B_COUNTER__LESS_THAN 1
#define CounterL__B_COUNTER__LESS_THAN_OR_EQUAL 2
#define CounterL__B_COUNTER__EQUAL 0
#define CounterL__B_COUNTER__GREATER_THAN 3
#define CounterL__B_COUNTER__GREATER_THAN_OR_EQUAL 4
#define CounterL__B_COUNTER__SOFTWARE 5

/* Enumerated Type Counter_CompareModes */
#define CounterL_CMP_MODE_LT 1u
#define CounterL_CMP_MODE_LTE 2u
#define CounterL_CMP_MODE_EQ 0u
#define CounterL_CMP_MODE_GT 3u
#define CounterL_CMP_MODE_GTE 4u
#define CounterL_CMP_MODE_SOFTWARE_CONTROLLED 5u

/* Enumerated Type B_Counter__CaptureModes, Used in Capture Mode retained for backward compatibility of tests*/
#define CounterL__B_COUNTER__NONE 0
#define CounterL__B_COUNTER__RISING_EDGE 1
#define CounterL__B_COUNTER__FALLING_EDGE 2
#define CounterL__B_COUNTER__EITHER_EDGE 3
#define CounterL__B_COUNTER__SOFTWARE_CONTROL 4

/* Enumerated Type Counter_CompareModes */
#define CounterL_CAP_MODE_NONE 0u
#define CounterL_CAP_MODE_RISE 1u
#define CounterL_CAP_MODE_FALL 2u
#define CounterL_CAP_MODE_BOTH 3u
#define CounterL_CAP_MODE_SOFTWARE_CONTROLLED 4u


/***************************************
 *  Initialization Values
 **************************************/
#define CounterL_CAPTURE_MODE_CONF       0u
#define CounterL_INIT_PERIOD_VALUE       255u
#define CounterL_INIT_COUNTER_VALUE      255u
#if (CounterL_UsingFixedFunction)
#define CounterL_INIT_INTERRUPTS_MASK    ((uint8)((uint8)0u << CounterL_STATUS_ZERO_INT_EN_MASK_SHIFT))
#else
#define CounterL_INIT_COMPARE_VALUE      128u
#define CounterL_INIT_INTERRUPTS_MASK ((uint8)((uint8)0u << CounterL_STATUS_ZERO_INT_EN_MASK_SHIFT) | \
        ((uint8)((uint8)0u << CounterL_STATUS_CAPTURE_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << CounterL_STATUS_CMP_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << CounterL_STATUS_OVERFLOW_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << CounterL_STATUS_UNDERFLOW_INT_EN_MASK_SHIFT)))
#define CounterL_DEFAULT_COMPARE_MODE    1u

#if( 0 != CounterL_CAPTURE_MODE_CONF)
    #define CounterL_DEFAULT_CAPTURE_MODE    ((uint8)((uint8)0u << CounterL_CTRL_CAPMODE0_SHIFT))
#else    
    #define CounterL_DEFAULT_CAPTURE_MODE    (0u )
#endif /* ( 0 != CounterL_CAPTURE_MODE_CONF) */

#endif /* (CounterL_UsingFixedFunction) */


/**************************************
 *  Registers
 *************************************/
#if (CounterL_UsingFixedFunction)
    #define CounterL_STATICCOUNT_LSB     (*(reg16 *) CounterL_CounterHW__CAP0 )
    #define CounterL_STATICCOUNT_LSB_PTR ( (reg16 *) CounterL_CounterHW__CAP0 )
    #define CounterL_PERIOD_LSB          (*(reg16 *) CounterL_CounterHW__PER0 )
    #define CounterL_PERIOD_LSB_PTR      ( (reg16 *) CounterL_CounterHW__PER0 )
    /* MODE must be set to 1 to set the compare value */
    #define CounterL_COMPARE_LSB         (*(reg16 *) CounterL_CounterHW__CNT_CMP0 )
    #define CounterL_COMPARE_LSB_PTR     ( (reg16 *) CounterL_CounterHW__CNT_CMP0 )
    /* MODE must be set to 0 to get the count */
    #define CounterL_COUNTER_LSB         (*(reg16 *) CounterL_CounterHW__CNT_CMP0 )
    #define CounterL_COUNTER_LSB_PTR     ( (reg16 *) CounterL_CounterHW__CNT_CMP0 )
    #define CounterL_RT1                 (*(reg8 *) CounterL_CounterHW__RT1)
    #define CounterL_RT1_PTR             ( (reg8 *) CounterL_CounterHW__RT1)
#else
    
    #if (CounterL_Resolution <= 8u) /* 8-bit Counter */
    
        #define CounterL_STATICCOUNT_LSB     (*(reg8 *) \
            CounterL_CounterUDB_sC8_counterdp_u0__F0_REG )
        #define CounterL_STATICCOUNT_LSB_PTR ( (reg8 *) \
            CounterL_CounterUDB_sC8_counterdp_u0__F0_REG )
        #define CounterL_PERIOD_LSB          (*(reg8 *) \
            CounterL_CounterUDB_sC8_counterdp_u0__D0_REG )
        #define CounterL_PERIOD_LSB_PTR      ( (reg8 *) \
            CounterL_CounterUDB_sC8_counterdp_u0__D0_REG )
        #define CounterL_COMPARE_LSB         (*(reg8 *) \
            CounterL_CounterUDB_sC8_counterdp_u0__D1_REG )
        #define CounterL_COMPARE_LSB_PTR     ( (reg8 *) \
            CounterL_CounterUDB_sC8_counterdp_u0__D1_REG )
        #define CounterL_COUNTER_LSB         (*(reg8 *) \
            CounterL_CounterUDB_sC8_counterdp_u0__A0_REG )  
        #define CounterL_COUNTER_LSB_PTR     ( (reg8 *)\
            CounterL_CounterUDB_sC8_counterdp_u0__A0_REG )
    
    #elif(CounterL_Resolution <= 16u) /* 16-bit Counter */
        #if(CY_PSOC3) /* 8-bit address space */ 
            #define CounterL_STATICCOUNT_LSB     (*(reg16 *) \
                CounterL_CounterUDB_sC8_counterdp_u0__F0_REG )
            #define CounterL_STATICCOUNT_LSB_PTR ( (reg16 *) \
                CounterL_CounterUDB_sC8_counterdp_u0__F0_REG )
            #define CounterL_PERIOD_LSB          (*(reg16 *) \
                CounterL_CounterUDB_sC8_counterdp_u0__D0_REG )
            #define CounterL_PERIOD_LSB_PTR      ( (reg16 *) \
                CounterL_CounterUDB_sC8_counterdp_u0__D0_REG )
            #define CounterL_COMPARE_LSB         (*(reg16 *) \
                CounterL_CounterUDB_sC8_counterdp_u0__D1_REG )
            #define CounterL_COMPARE_LSB_PTR     ( (reg16 *) \
                CounterL_CounterUDB_sC8_counterdp_u0__D1_REG )
            #define CounterL_COUNTER_LSB         (*(reg16 *) \
                CounterL_CounterUDB_sC8_counterdp_u0__A0_REG )  
            #define CounterL_COUNTER_LSB_PTR     ( (reg16 *)\
                CounterL_CounterUDB_sC8_counterdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define CounterL_STATICCOUNT_LSB     (*(reg16 *) \
                CounterL_CounterUDB_sC8_counterdp_u0__16BIT_F0_REG )
            #define CounterL_STATICCOUNT_LSB_PTR ( (reg16 *) \
                CounterL_CounterUDB_sC8_counterdp_u0__16BIT_F0_REG )
            #define CounterL_PERIOD_LSB          (*(reg16 *) \
                CounterL_CounterUDB_sC8_counterdp_u0__16BIT_D0_REG )
            #define CounterL_PERIOD_LSB_PTR      ( (reg16 *) \
                CounterL_CounterUDB_sC8_counterdp_u0__16BIT_D0_REG )
            #define CounterL_COMPARE_LSB         (*(reg16 *) \
                CounterL_CounterUDB_sC8_counterdp_u0__16BIT_D1_REG )
            #define CounterL_COMPARE_LSB_PTR     ( (reg16 *) \
                CounterL_CounterUDB_sC8_counterdp_u0__16BIT_D1_REG )
            #define CounterL_COUNTER_LSB         (*(reg16 *) \
                CounterL_CounterUDB_sC8_counterdp_u0__16BIT_A0_REG )  
            #define CounterL_COUNTER_LSB_PTR     ( (reg16 *)\
                CounterL_CounterUDB_sC8_counterdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */   
    #elif(CounterL_Resolution <= 24u) /* 24-bit Counter */
        
        #define CounterL_STATICCOUNT_LSB     (*(reg32 *) \
            CounterL_CounterUDB_sC8_counterdp_u0__F0_REG )
        #define CounterL_STATICCOUNT_LSB_PTR ( (reg32 *) \
            CounterL_CounterUDB_sC8_counterdp_u0__F0_REG )
        #define CounterL_PERIOD_LSB          (*(reg32 *) \
            CounterL_CounterUDB_sC8_counterdp_u0__D0_REG )
        #define CounterL_PERIOD_LSB_PTR      ( (reg32 *) \
            CounterL_CounterUDB_sC8_counterdp_u0__D0_REG )
        #define CounterL_COMPARE_LSB         (*(reg32 *) \
            CounterL_CounterUDB_sC8_counterdp_u0__D1_REG )
        #define CounterL_COMPARE_LSB_PTR     ( (reg32 *) \
            CounterL_CounterUDB_sC8_counterdp_u0__D1_REG )
        #define CounterL_COUNTER_LSB         (*(reg32 *) \
            CounterL_CounterUDB_sC8_counterdp_u0__A0_REG )  
        #define CounterL_COUNTER_LSB_PTR     ( (reg32 *)\
            CounterL_CounterUDB_sC8_counterdp_u0__A0_REG )
    
    #else /* 32-bit Counter */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define CounterL_STATICCOUNT_LSB     (*(reg32 *) \
                CounterL_CounterUDB_sC8_counterdp_u0__F0_REG )
            #define CounterL_STATICCOUNT_LSB_PTR ( (reg32 *) \
                CounterL_CounterUDB_sC8_counterdp_u0__F0_REG )
            #define CounterL_PERIOD_LSB          (*(reg32 *) \
                CounterL_CounterUDB_sC8_counterdp_u0__D0_REG )
            #define CounterL_PERIOD_LSB_PTR      ( (reg32 *) \
                CounterL_CounterUDB_sC8_counterdp_u0__D0_REG )
            #define CounterL_COMPARE_LSB         (*(reg32 *) \
                CounterL_CounterUDB_sC8_counterdp_u0__D1_REG )
            #define CounterL_COMPARE_LSB_PTR     ( (reg32 *) \
                CounterL_CounterUDB_sC8_counterdp_u0__D1_REG )
            #define CounterL_COUNTER_LSB         (*(reg32 *) \
                CounterL_CounterUDB_sC8_counterdp_u0__A0_REG )  
            #define CounterL_COUNTER_LSB_PTR     ( (reg32 *)\
                CounterL_CounterUDB_sC8_counterdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define CounterL_STATICCOUNT_LSB     (*(reg32 *) \
                CounterL_CounterUDB_sC8_counterdp_u0__32BIT_F0_REG )
            #define CounterL_STATICCOUNT_LSB_PTR ( (reg32 *) \
                CounterL_CounterUDB_sC8_counterdp_u0__32BIT_F0_REG )
            #define CounterL_PERIOD_LSB          (*(reg32 *) \
                CounterL_CounterUDB_sC8_counterdp_u0__32BIT_D0_REG )
            #define CounterL_PERIOD_LSB_PTR      ( (reg32 *) \
                CounterL_CounterUDB_sC8_counterdp_u0__32BIT_D0_REG )
            #define CounterL_COMPARE_LSB         (*(reg32 *) \
                CounterL_CounterUDB_sC8_counterdp_u0__32BIT_D1_REG )
            #define CounterL_COMPARE_LSB_PTR     ( (reg32 *) \
                CounterL_CounterUDB_sC8_counterdp_u0__32BIT_D1_REG )
            #define CounterL_COUNTER_LSB         (*(reg32 *) \
                CounterL_CounterUDB_sC8_counterdp_u0__32BIT_A0_REG )  
            #define CounterL_COUNTER_LSB_PTR     ( (reg32 *)\
                CounterL_CounterUDB_sC8_counterdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */   
    #endif

	#define CounterL_COUNTER_LSB_PTR_8BIT     ( (reg8 *)\
                CounterL_CounterUDB_sC8_counterdp_u0__A0_REG )
				
    #define CounterL_AUX_CONTROLDP0 \
        (*(reg8 *) CounterL_CounterUDB_sC8_counterdp_u0__DP_AUX_CTL_REG)
    
    #define CounterL_AUX_CONTROLDP0_PTR \
        ( (reg8 *) CounterL_CounterUDB_sC8_counterdp_u0__DP_AUX_CTL_REG)
    
    #if (CounterL_Resolution == 16 || CounterL_Resolution == 24 || CounterL_Resolution == 32)
       #define CounterL_AUX_CONTROLDP1 \
           (*(reg8 *) CounterL_CounterUDB_sC8_counterdp_u1__DP_AUX_CTL_REG)
       #define CounterL_AUX_CONTROLDP1_PTR \
           ( (reg8 *) CounterL_CounterUDB_sC8_counterdp_u1__DP_AUX_CTL_REG)
    #endif /* (CounterL_Resolution == 16 || CounterL_Resolution == 24 || CounterL_Resolution == 32) */
    
    #if (CounterL_Resolution == 24 || CounterL_Resolution == 32)
       #define CounterL_AUX_CONTROLDP2 \
           (*(reg8 *) CounterL_CounterUDB_sC8_counterdp_u2__DP_AUX_CTL_REG)
       #define CounterL_AUX_CONTROLDP2_PTR \
           ( (reg8 *) CounterL_CounterUDB_sC8_counterdp_u2__DP_AUX_CTL_REG)
    #endif /* (CounterL_Resolution == 24 || CounterL_Resolution == 32) */
    
    #if (CounterL_Resolution == 32)
       #define CounterL_AUX_CONTROLDP3 \
           (*(reg8 *) CounterL_CounterUDB_sC8_counterdp_u3__DP_AUX_CTL_REG)
       #define CounterL_AUX_CONTROLDP3_PTR \
           ( (reg8 *) CounterL_CounterUDB_sC8_counterdp_u3__DP_AUX_CTL_REG)
    #endif /* (CounterL_Resolution == 32) */

#endif  /* (CounterL_UsingFixedFunction) */

#if (CounterL_UsingFixedFunction)
    #define CounterL_STATUS         (*(reg8 *) CounterL_CounterHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define CounterL_STATUS_MASK             (*(reg8 *) CounterL_CounterHW__SR0 )
    #define CounterL_STATUS_MASK_PTR         ( (reg8 *) CounterL_CounterHW__SR0 )
    #define CounterL_CONTROL                 (*(reg8 *) CounterL_CounterHW__CFG0)
    #define CounterL_CONTROL_PTR             ( (reg8 *) CounterL_CounterHW__CFG0)
    #define CounterL_CONTROL2                (*(reg8 *) CounterL_CounterHW__CFG1)
    #define CounterL_CONTROL2_PTR            ( (reg8 *) CounterL_CounterHW__CFG1)
    #if (CY_PSOC3 || CY_PSOC5LP)
        #define CounterL_CONTROL3       (*(reg8 *) CounterL_CounterHW__CFG2)
        #define CounterL_CONTROL3_PTR   ( (reg8 *) CounterL_CounterHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define CounterL_GLOBAL_ENABLE           (*(reg8 *) CounterL_CounterHW__PM_ACT_CFG)
    #define CounterL_GLOBAL_ENABLE_PTR       ( (reg8 *) CounterL_CounterHW__PM_ACT_CFG)
    #define CounterL_GLOBAL_STBY_ENABLE      (*(reg8 *) CounterL_CounterHW__PM_STBY_CFG)
    #define CounterL_GLOBAL_STBY_ENABLE_PTR  ( (reg8 *) CounterL_CounterHW__PM_STBY_CFG)
    

    /********************************
    *    Constants
    ********************************/

    /* Fixed Function Block Chosen */
    #define CounterL_BLOCK_EN_MASK          CounterL_CounterHW__PM_ACT_MSK
    #define CounterL_BLOCK_STBY_EN_MASK     CounterL_CounterHW__PM_STBY_MSK 
    
    /* Control Register Bit Locations */    
    /* As defined in Register Map, part of TMRX_CFG0 register */
    #define CounterL_CTRL_ENABLE_SHIFT      0x00u
    #define CounterL_ONESHOT_SHIFT          0x02u
    /* Control Register Bit Masks */
    #define CounterL_CTRL_ENABLE            ((uint8)((uint8)0x01u << CounterL_CTRL_ENABLE_SHIFT))         
    #define CounterL_ONESHOT                ((uint8)((uint8)0x01u << CounterL_ONESHOT_SHIFT))

    /* Control2 Register Bit Masks */
    /* Set the mask for run mode */
    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        #define CounterL_CTRL_MODE_SHIFT        0x01u    
        #define CounterL_CTRL_MODE_MASK         ((uint8)((uint8)0x07u << CounterL_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Use CFG2 Mode bits to set run mode */
        #define CounterL_CTRL_MODE_SHIFT        0x00u    
        #define CounterL_CTRL_MODE_MASK         ((uint8)((uint8)0x03u << CounterL_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    /* Set the mask for interrupt (raw/status register) */
    #define CounterL_CTRL2_IRQ_SEL_SHIFT     0x00u
    #define CounterL_CTRL2_IRQ_SEL          ((uint8)((uint8)0x01u << CounterL_CTRL2_IRQ_SEL_SHIFT))     
    
    /* Status Register Bit Locations */
    #define CounterL_STATUS_ZERO_SHIFT      0x07u  /* As defined in Register Map, part of TMRX_SR0 register */ 

    /* Status Register Interrupt Enable Bit Locations */
    #define CounterL_STATUS_ZERO_INT_EN_MASK_SHIFT      (CounterL_STATUS_ZERO_SHIFT - 0x04u)

    /* Status Register Bit Masks */                           
    #define CounterL_STATUS_ZERO            ((uint8)((uint8)0x01u << CounterL_STATUS_ZERO_SHIFT))

    /* Status Register Interrupt Bit Masks*/
    #define CounterL_STATUS_ZERO_INT_EN_MASK       ((uint8)((uint8)CounterL_STATUS_ZERO >> 0x04u))
    
    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define CounterL_RT1_SHIFT            0x04u
    #define CounterL_RT1_MASK             ((uint8)((uint8)0x03u << CounterL_RT1_SHIFT))  /* Sync TC and CMP bit masks */
    #define CounterL_SYNC                 ((uint8)((uint8)0x03u << CounterL_RT1_SHIFT))
    #define CounterL_SYNCDSI_SHIFT        0x00u
    #define CounterL_SYNCDSI_MASK         ((uint8)((uint8)0x0Fu << CounterL_SYNCDSI_SHIFT)) /* Sync all DSI inputs */
    #define CounterL_SYNCDSI_EN           ((uint8)((uint8)0x0Fu << CounterL_SYNCDSI_SHIFT)) /* Sync all DSI inputs */
    
#else /* !CounterL_UsingFixedFunction */
    #define CounterL_STATUS               (* (reg8 *) CounterL_CounterUDB_sSTSReg_rstSts_stsreg__STATUS_REG )
    #define CounterL_STATUS_PTR           (  (reg8 *) CounterL_CounterUDB_sSTSReg_rstSts_stsreg__STATUS_REG )
    #define CounterL_STATUS_MASK          (* (reg8 *) CounterL_CounterUDB_sSTSReg_rstSts_stsreg__MASK_REG )
    #define CounterL_STATUS_MASK_PTR      (  (reg8 *) CounterL_CounterUDB_sSTSReg_rstSts_stsreg__MASK_REG )
    #define CounterL_STATUS_AUX_CTRL      (*(reg8 *) CounterL_CounterUDB_sSTSReg_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define CounterL_STATUS_AUX_CTRL_PTR  ( (reg8 *) CounterL_CounterUDB_sSTSReg_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define CounterL_CONTROL              (* (reg8 *) CounterL_CounterUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    #define CounterL_CONTROL_PTR          (  (reg8 *) CounterL_CounterUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )


    /********************************
    *    Constants
    ********************************/
    /* Control Register Bit Locations */
    #define CounterL_CTRL_CAPMODE0_SHIFT    0x03u       /* As defined by Verilog Implementation */
    #define CounterL_CTRL_RESET_SHIFT       0x06u       /* As defined by Verilog Implementation */
    #define CounterL_CTRL_ENABLE_SHIFT      0x07u       /* As defined by Verilog Implementation */
    /* Control Register Bit Masks */
    #define CounterL_CTRL_CMPMODE_MASK      0x07u 
    #define CounterL_CTRL_CAPMODE_MASK      0x03u  
    #define CounterL_CTRL_RESET             ((uint8)((uint8)0x01u << CounterL_CTRL_RESET_SHIFT))  
    #define CounterL_CTRL_ENABLE            ((uint8)((uint8)0x01u << CounterL_CTRL_ENABLE_SHIFT)) 

    /* Status Register Bit Locations */
    #define CounterL_STATUS_CMP_SHIFT       0x00u       /* As defined by Verilog Implementation */
    #define CounterL_STATUS_ZERO_SHIFT      0x01u       /* As defined by Verilog Implementation */
    #define CounterL_STATUS_OVERFLOW_SHIFT  0x02u       /* As defined by Verilog Implementation */
    #define CounterL_STATUS_UNDERFLOW_SHIFT 0x03u       /* As defined by Verilog Implementation */
    #define CounterL_STATUS_CAPTURE_SHIFT   0x04u       /* As defined by Verilog Implementation */
    #define CounterL_STATUS_FIFOFULL_SHIFT  0x05u       /* As defined by Verilog Implementation */
    #define CounterL_STATUS_FIFONEMP_SHIFT  0x06u       /* As defined by Verilog Implementation */
    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define CounterL_STATUS_CMP_INT_EN_MASK_SHIFT       CounterL_STATUS_CMP_SHIFT       
    #define CounterL_STATUS_ZERO_INT_EN_MASK_SHIFT      CounterL_STATUS_ZERO_SHIFT      
    #define CounterL_STATUS_OVERFLOW_INT_EN_MASK_SHIFT  CounterL_STATUS_OVERFLOW_SHIFT  
    #define CounterL_STATUS_UNDERFLOW_INT_EN_MASK_SHIFT CounterL_STATUS_UNDERFLOW_SHIFT 
    #define CounterL_STATUS_CAPTURE_INT_EN_MASK_SHIFT   CounterL_STATUS_CAPTURE_SHIFT   
    #define CounterL_STATUS_FIFOFULL_INT_EN_MASK_SHIFT  CounterL_STATUS_FIFOFULL_SHIFT  
    #define CounterL_STATUS_FIFONEMP_INT_EN_MASK_SHIFT  CounterL_STATUS_FIFONEMP_SHIFT  
    /* Status Register Bit Masks */                
    #define CounterL_STATUS_CMP             ((uint8)((uint8)0x01u << CounterL_STATUS_CMP_SHIFT))  
    #define CounterL_STATUS_ZERO            ((uint8)((uint8)0x01u << CounterL_STATUS_ZERO_SHIFT)) 
    #define CounterL_STATUS_OVERFLOW        ((uint8)((uint8)0x01u << CounterL_STATUS_OVERFLOW_SHIFT)) 
    #define CounterL_STATUS_UNDERFLOW       ((uint8)((uint8)0x01u << CounterL_STATUS_UNDERFLOW_SHIFT)) 
    #define CounterL_STATUS_CAPTURE         ((uint8)((uint8)0x01u << CounterL_STATUS_CAPTURE_SHIFT)) 
    #define CounterL_STATUS_FIFOFULL        ((uint8)((uint8)0x01u << CounterL_STATUS_FIFOFULL_SHIFT))
    #define CounterL_STATUS_FIFONEMP        ((uint8)((uint8)0x01u << CounterL_STATUS_FIFONEMP_SHIFT))
    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define CounterL_STATUS_CMP_INT_EN_MASK            CounterL_STATUS_CMP                    
    #define CounterL_STATUS_ZERO_INT_EN_MASK           CounterL_STATUS_ZERO            
    #define CounterL_STATUS_OVERFLOW_INT_EN_MASK       CounterL_STATUS_OVERFLOW        
    #define CounterL_STATUS_UNDERFLOW_INT_EN_MASK      CounterL_STATUS_UNDERFLOW       
    #define CounterL_STATUS_CAPTURE_INT_EN_MASK        CounterL_STATUS_CAPTURE         
    #define CounterL_STATUS_FIFOFULL_INT_EN_MASK       CounterL_STATUS_FIFOFULL        
    #define CounterL_STATUS_FIFONEMP_INT_EN_MASK       CounterL_STATUS_FIFONEMP         
    

    /* StatusI Interrupt Enable bit Location in the Auxilliary Control Register */
    #define CounterL_STATUS_ACTL_INT_EN     0x10u /* As defined for the ACTL Register */
    
    /* Datapath Auxillary Control Register definitions */
    #define CounterL_AUX_CTRL_FIFO0_CLR         0x01u   /* As defined by Register map */
    #define CounterL_AUX_CTRL_FIFO1_CLR         0x02u   /* As defined by Register map */
    #define CounterL_AUX_CTRL_FIFO0_LVL         0x04u   /* As defined by Register map */
    #define CounterL_AUX_CTRL_FIFO1_LVL         0x08u   /* As defined by Register map */
    #define CounterL_STATUS_ACTL_INT_EN_MASK    0x10u   /* As defined for the ACTL Register */
    
#endif /* CounterL_UsingFixedFunction */

#endif  /* CY_COUNTER_CounterL_H */


/* [] END OF FILE */

