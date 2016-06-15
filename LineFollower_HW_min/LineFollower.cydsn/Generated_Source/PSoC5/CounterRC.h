/*******************************************************************************
* File Name: CounterRC.h  
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
    
#if !defined(CY_COUNTER_CounterRC_H)
#define CY_COUNTER_CounterRC_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 CounterRC_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Counter_v2_40 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults        
**************************************/

#define CounterRC_Resolution            8u
#define CounterRC_UsingFixedFunction    1u
#define CounterRC_ControlRegRemoved     0u
#define CounterRC_COMPARE_MODE_SOFTWARE 0u
#define CounterRC_CAPTURE_MODE_SOFTWARE 0u
#define CounterRC_RunModeUsed           0u


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

    #if (!CounterRC_ControlRegRemoved)
        uint8 CounterControlRegister;               /* Counter Control Register */
    #endif /* (!CounterRC_ControlRegRemoved) */

}CounterRC_backupStruct;


/**************************************
 *  Function Prototypes
 *************************************/
void    CounterRC_Start(void) ;
void    CounterRC_Stop(void) ;
void    CounterRC_SetInterruptMode(uint8 interruptsMask) ;
uint8   CounterRC_ReadStatusRegister(void) ;
#define CounterRC_GetInterruptSource() CounterRC_ReadStatusRegister()
#if(!CounterRC_ControlRegRemoved)
    uint8   CounterRC_ReadControlRegister(void) ;
    void    CounterRC_WriteControlRegister(uint8 control) \
        ;
#endif /* (!CounterRC_ControlRegRemoved) */
#if (!(CounterRC_UsingFixedFunction && (CY_PSOC5A)))
    void    CounterRC_WriteCounter(uint8 counter) \
            ; 
#endif /* (!(CounterRC_UsingFixedFunction && (CY_PSOC5A))) */
uint8  CounterRC_ReadCounter(void) ;
uint8  CounterRC_ReadCapture(void) ;
void    CounterRC_WritePeriod(uint8 period) \
    ;
uint8  CounterRC_ReadPeriod( void ) ;
#if (!CounterRC_UsingFixedFunction)
    void    CounterRC_WriteCompare(uint8 compare) \
        ;
    uint8  CounterRC_ReadCompare( void ) \
        ;
#endif /* (!CounterRC_UsingFixedFunction) */

#if (CounterRC_COMPARE_MODE_SOFTWARE)
    void    CounterRC_SetCompareMode(uint8 compareMode) ;
#endif /* (CounterRC_COMPARE_MODE_SOFTWARE) */
#if (CounterRC_CAPTURE_MODE_SOFTWARE)
    void    CounterRC_SetCaptureMode(uint8 captureMode) ;
#endif /* (CounterRC_CAPTURE_MODE_SOFTWARE) */
void CounterRC_ClearFIFO(void)     ;
void CounterRC_Init(void)          ;
void CounterRC_Enable(void)        ;
void CounterRC_SaveConfig(void)    ;
void CounterRC_RestoreConfig(void) ;
void CounterRC_Sleep(void)         ;
void CounterRC_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Counter__CompareModes, Used in Compare Mode retained for backward compatibility of tests*/
#define CounterRC__B_COUNTER__LESS_THAN 1
#define CounterRC__B_COUNTER__LESS_THAN_OR_EQUAL 2
#define CounterRC__B_COUNTER__EQUAL 0
#define CounterRC__B_COUNTER__GREATER_THAN 3
#define CounterRC__B_COUNTER__GREATER_THAN_OR_EQUAL 4
#define CounterRC__B_COUNTER__SOFTWARE 5

/* Enumerated Type Counter_CompareModes */
#define CounterRC_CMP_MODE_LT 1u
#define CounterRC_CMP_MODE_LTE 2u
#define CounterRC_CMP_MODE_EQ 0u
#define CounterRC_CMP_MODE_GT 3u
#define CounterRC_CMP_MODE_GTE 4u
#define CounterRC_CMP_MODE_SOFTWARE_CONTROLLED 5u

/* Enumerated Type B_Counter__CaptureModes, Used in Capture Mode retained for backward compatibility of tests*/
#define CounterRC__B_COUNTER__NONE 0
#define CounterRC__B_COUNTER__RISING_EDGE 1
#define CounterRC__B_COUNTER__FALLING_EDGE 2
#define CounterRC__B_COUNTER__EITHER_EDGE 3
#define CounterRC__B_COUNTER__SOFTWARE_CONTROL 4

/* Enumerated Type Counter_CompareModes */
#define CounterRC_CAP_MODE_NONE 0u
#define CounterRC_CAP_MODE_RISE 1u
#define CounterRC_CAP_MODE_FALL 2u
#define CounterRC_CAP_MODE_BOTH 3u
#define CounterRC_CAP_MODE_SOFTWARE_CONTROLLED 4u


/***************************************
 *  Initialization Values
 **************************************/
#define CounterRC_CAPTURE_MODE_CONF       0u
#define CounterRC_INIT_PERIOD_VALUE       255u
#define CounterRC_INIT_COUNTER_VALUE      255u
#if (CounterRC_UsingFixedFunction)
#define CounterRC_INIT_INTERRUPTS_MASK    ((uint8)((uint8)0u << CounterRC_STATUS_ZERO_INT_EN_MASK_SHIFT))
#else
#define CounterRC_INIT_COMPARE_VALUE      128u
#define CounterRC_INIT_INTERRUPTS_MASK ((uint8)((uint8)0u << CounterRC_STATUS_ZERO_INT_EN_MASK_SHIFT) | \
        ((uint8)((uint8)0u << CounterRC_STATUS_CAPTURE_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << CounterRC_STATUS_CMP_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << CounterRC_STATUS_OVERFLOW_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << CounterRC_STATUS_UNDERFLOW_INT_EN_MASK_SHIFT)))
#define CounterRC_DEFAULT_COMPARE_MODE    1u

#if( 0 != CounterRC_CAPTURE_MODE_CONF)
    #define CounterRC_DEFAULT_CAPTURE_MODE    ((uint8)((uint8)0u << CounterRC_CTRL_CAPMODE0_SHIFT))
#else    
    #define CounterRC_DEFAULT_CAPTURE_MODE    (0u )
#endif /* ( 0 != CounterRC_CAPTURE_MODE_CONF) */

#endif /* (CounterRC_UsingFixedFunction) */


/**************************************
 *  Registers
 *************************************/
#if (CounterRC_UsingFixedFunction)
    #define CounterRC_STATICCOUNT_LSB     (*(reg16 *) CounterRC_CounterHW__CAP0 )
    #define CounterRC_STATICCOUNT_LSB_PTR ( (reg16 *) CounterRC_CounterHW__CAP0 )
    #define CounterRC_PERIOD_LSB          (*(reg16 *) CounterRC_CounterHW__PER0 )
    #define CounterRC_PERIOD_LSB_PTR      ( (reg16 *) CounterRC_CounterHW__PER0 )
    /* MODE must be set to 1 to set the compare value */
    #define CounterRC_COMPARE_LSB         (*(reg16 *) CounterRC_CounterHW__CNT_CMP0 )
    #define CounterRC_COMPARE_LSB_PTR     ( (reg16 *) CounterRC_CounterHW__CNT_CMP0 )
    /* MODE must be set to 0 to get the count */
    #define CounterRC_COUNTER_LSB         (*(reg16 *) CounterRC_CounterHW__CNT_CMP0 )
    #define CounterRC_COUNTER_LSB_PTR     ( (reg16 *) CounterRC_CounterHW__CNT_CMP0 )
    #define CounterRC_RT1                 (*(reg8 *) CounterRC_CounterHW__RT1)
    #define CounterRC_RT1_PTR             ( (reg8 *) CounterRC_CounterHW__RT1)
#else
    
    #if (CounterRC_Resolution <= 8u) /* 8-bit Counter */
    
        #define CounterRC_STATICCOUNT_LSB     (*(reg8 *) \
            CounterRC_CounterUDB_sC8_counterdp_u0__F0_REG )
        #define CounterRC_STATICCOUNT_LSB_PTR ( (reg8 *) \
            CounterRC_CounterUDB_sC8_counterdp_u0__F0_REG )
        #define CounterRC_PERIOD_LSB          (*(reg8 *) \
            CounterRC_CounterUDB_sC8_counterdp_u0__D0_REG )
        #define CounterRC_PERIOD_LSB_PTR      ( (reg8 *) \
            CounterRC_CounterUDB_sC8_counterdp_u0__D0_REG )
        #define CounterRC_COMPARE_LSB         (*(reg8 *) \
            CounterRC_CounterUDB_sC8_counterdp_u0__D1_REG )
        #define CounterRC_COMPARE_LSB_PTR     ( (reg8 *) \
            CounterRC_CounterUDB_sC8_counterdp_u0__D1_REG )
        #define CounterRC_COUNTER_LSB         (*(reg8 *) \
            CounterRC_CounterUDB_sC8_counterdp_u0__A0_REG )  
        #define CounterRC_COUNTER_LSB_PTR     ( (reg8 *)\
            CounterRC_CounterUDB_sC8_counterdp_u0__A0_REG )
    
    #elif(CounterRC_Resolution <= 16u) /* 16-bit Counter */
        #if(CY_PSOC3) /* 8-bit address space */ 
            #define CounterRC_STATICCOUNT_LSB     (*(reg16 *) \
                CounterRC_CounterUDB_sC8_counterdp_u0__F0_REG )
            #define CounterRC_STATICCOUNT_LSB_PTR ( (reg16 *) \
                CounterRC_CounterUDB_sC8_counterdp_u0__F0_REG )
            #define CounterRC_PERIOD_LSB          (*(reg16 *) \
                CounterRC_CounterUDB_sC8_counterdp_u0__D0_REG )
            #define CounterRC_PERIOD_LSB_PTR      ( (reg16 *) \
                CounterRC_CounterUDB_sC8_counterdp_u0__D0_REG )
            #define CounterRC_COMPARE_LSB         (*(reg16 *) \
                CounterRC_CounterUDB_sC8_counterdp_u0__D1_REG )
            #define CounterRC_COMPARE_LSB_PTR     ( (reg16 *) \
                CounterRC_CounterUDB_sC8_counterdp_u0__D1_REG )
            #define CounterRC_COUNTER_LSB         (*(reg16 *) \
                CounterRC_CounterUDB_sC8_counterdp_u0__A0_REG )  
            #define CounterRC_COUNTER_LSB_PTR     ( (reg16 *)\
                CounterRC_CounterUDB_sC8_counterdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define CounterRC_STATICCOUNT_LSB     (*(reg16 *) \
                CounterRC_CounterUDB_sC8_counterdp_u0__16BIT_F0_REG )
            #define CounterRC_STATICCOUNT_LSB_PTR ( (reg16 *) \
                CounterRC_CounterUDB_sC8_counterdp_u0__16BIT_F0_REG )
            #define CounterRC_PERIOD_LSB          (*(reg16 *) \
                CounterRC_CounterUDB_sC8_counterdp_u0__16BIT_D0_REG )
            #define CounterRC_PERIOD_LSB_PTR      ( (reg16 *) \
                CounterRC_CounterUDB_sC8_counterdp_u0__16BIT_D0_REG )
            #define CounterRC_COMPARE_LSB         (*(reg16 *) \
                CounterRC_CounterUDB_sC8_counterdp_u0__16BIT_D1_REG )
            #define CounterRC_COMPARE_LSB_PTR     ( (reg16 *) \
                CounterRC_CounterUDB_sC8_counterdp_u0__16BIT_D1_REG )
            #define CounterRC_COUNTER_LSB         (*(reg16 *) \
                CounterRC_CounterUDB_sC8_counterdp_u0__16BIT_A0_REG )  
            #define CounterRC_COUNTER_LSB_PTR     ( (reg16 *)\
                CounterRC_CounterUDB_sC8_counterdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */   
    #elif(CounterRC_Resolution <= 24u) /* 24-bit Counter */
        
        #define CounterRC_STATICCOUNT_LSB     (*(reg32 *) \
            CounterRC_CounterUDB_sC8_counterdp_u0__F0_REG )
        #define CounterRC_STATICCOUNT_LSB_PTR ( (reg32 *) \
            CounterRC_CounterUDB_sC8_counterdp_u0__F0_REG )
        #define CounterRC_PERIOD_LSB          (*(reg32 *) \
            CounterRC_CounterUDB_sC8_counterdp_u0__D0_REG )
        #define CounterRC_PERIOD_LSB_PTR      ( (reg32 *) \
            CounterRC_CounterUDB_sC8_counterdp_u0__D0_REG )
        #define CounterRC_COMPARE_LSB         (*(reg32 *) \
            CounterRC_CounterUDB_sC8_counterdp_u0__D1_REG )
        #define CounterRC_COMPARE_LSB_PTR     ( (reg32 *) \
            CounterRC_CounterUDB_sC8_counterdp_u0__D1_REG )
        #define CounterRC_COUNTER_LSB         (*(reg32 *) \
            CounterRC_CounterUDB_sC8_counterdp_u0__A0_REG )  
        #define CounterRC_COUNTER_LSB_PTR     ( (reg32 *)\
            CounterRC_CounterUDB_sC8_counterdp_u0__A0_REG )
    
    #else /* 32-bit Counter */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define CounterRC_STATICCOUNT_LSB     (*(reg32 *) \
                CounterRC_CounterUDB_sC8_counterdp_u0__F0_REG )
            #define CounterRC_STATICCOUNT_LSB_PTR ( (reg32 *) \
                CounterRC_CounterUDB_sC8_counterdp_u0__F0_REG )
            #define CounterRC_PERIOD_LSB          (*(reg32 *) \
                CounterRC_CounterUDB_sC8_counterdp_u0__D0_REG )
            #define CounterRC_PERIOD_LSB_PTR      ( (reg32 *) \
                CounterRC_CounterUDB_sC8_counterdp_u0__D0_REG )
            #define CounterRC_COMPARE_LSB         (*(reg32 *) \
                CounterRC_CounterUDB_sC8_counterdp_u0__D1_REG )
            #define CounterRC_COMPARE_LSB_PTR     ( (reg32 *) \
                CounterRC_CounterUDB_sC8_counterdp_u0__D1_REG )
            #define CounterRC_COUNTER_LSB         (*(reg32 *) \
                CounterRC_CounterUDB_sC8_counterdp_u0__A0_REG )  
            #define CounterRC_COUNTER_LSB_PTR     ( (reg32 *)\
                CounterRC_CounterUDB_sC8_counterdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define CounterRC_STATICCOUNT_LSB     (*(reg32 *) \
                CounterRC_CounterUDB_sC8_counterdp_u0__32BIT_F0_REG )
            #define CounterRC_STATICCOUNT_LSB_PTR ( (reg32 *) \
                CounterRC_CounterUDB_sC8_counterdp_u0__32BIT_F0_REG )
            #define CounterRC_PERIOD_LSB          (*(reg32 *) \
                CounterRC_CounterUDB_sC8_counterdp_u0__32BIT_D0_REG )
            #define CounterRC_PERIOD_LSB_PTR      ( (reg32 *) \
                CounterRC_CounterUDB_sC8_counterdp_u0__32BIT_D0_REG )
            #define CounterRC_COMPARE_LSB         (*(reg32 *) \
                CounterRC_CounterUDB_sC8_counterdp_u0__32BIT_D1_REG )
            #define CounterRC_COMPARE_LSB_PTR     ( (reg32 *) \
                CounterRC_CounterUDB_sC8_counterdp_u0__32BIT_D1_REG )
            #define CounterRC_COUNTER_LSB         (*(reg32 *) \
                CounterRC_CounterUDB_sC8_counterdp_u0__32BIT_A0_REG )  
            #define CounterRC_COUNTER_LSB_PTR     ( (reg32 *)\
                CounterRC_CounterUDB_sC8_counterdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */   
    #endif

	#define CounterRC_COUNTER_LSB_PTR_8BIT     ( (reg8 *)\
                CounterRC_CounterUDB_sC8_counterdp_u0__A0_REG )
				
    #define CounterRC_AUX_CONTROLDP0 \
        (*(reg8 *) CounterRC_CounterUDB_sC8_counterdp_u0__DP_AUX_CTL_REG)
    
    #define CounterRC_AUX_CONTROLDP0_PTR \
        ( (reg8 *) CounterRC_CounterUDB_sC8_counterdp_u0__DP_AUX_CTL_REG)
    
    #if (CounterRC_Resolution == 16 || CounterRC_Resolution == 24 || CounterRC_Resolution == 32)
       #define CounterRC_AUX_CONTROLDP1 \
           (*(reg8 *) CounterRC_CounterUDB_sC8_counterdp_u1__DP_AUX_CTL_REG)
       #define CounterRC_AUX_CONTROLDP1_PTR \
           ( (reg8 *) CounterRC_CounterUDB_sC8_counterdp_u1__DP_AUX_CTL_REG)
    #endif /* (CounterRC_Resolution == 16 || CounterRC_Resolution == 24 || CounterRC_Resolution == 32) */
    
    #if (CounterRC_Resolution == 24 || CounterRC_Resolution == 32)
       #define CounterRC_AUX_CONTROLDP2 \
           (*(reg8 *) CounterRC_CounterUDB_sC8_counterdp_u2__DP_AUX_CTL_REG)
       #define CounterRC_AUX_CONTROLDP2_PTR \
           ( (reg8 *) CounterRC_CounterUDB_sC8_counterdp_u2__DP_AUX_CTL_REG)
    #endif /* (CounterRC_Resolution == 24 || CounterRC_Resolution == 32) */
    
    #if (CounterRC_Resolution == 32)
       #define CounterRC_AUX_CONTROLDP3 \
           (*(reg8 *) CounterRC_CounterUDB_sC8_counterdp_u3__DP_AUX_CTL_REG)
       #define CounterRC_AUX_CONTROLDP3_PTR \
           ( (reg8 *) CounterRC_CounterUDB_sC8_counterdp_u3__DP_AUX_CTL_REG)
    #endif /* (CounterRC_Resolution == 32) */

#endif  /* (CounterRC_UsingFixedFunction) */

#if (CounterRC_UsingFixedFunction)
    #define CounterRC_STATUS         (*(reg8 *) CounterRC_CounterHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define CounterRC_STATUS_MASK             (*(reg8 *) CounterRC_CounterHW__SR0 )
    #define CounterRC_STATUS_MASK_PTR         ( (reg8 *) CounterRC_CounterHW__SR0 )
    #define CounterRC_CONTROL                 (*(reg8 *) CounterRC_CounterHW__CFG0)
    #define CounterRC_CONTROL_PTR             ( (reg8 *) CounterRC_CounterHW__CFG0)
    #define CounterRC_CONTROL2                (*(reg8 *) CounterRC_CounterHW__CFG1)
    #define CounterRC_CONTROL2_PTR            ( (reg8 *) CounterRC_CounterHW__CFG1)
    #if (CY_PSOC3 || CY_PSOC5LP)
        #define CounterRC_CONTROL3       (*(reg8 *) CounterRC_CounterHW__CFG2)
        #define CounterRC_CONTROL3_PTR   ( (reg8 *) CounterRC_CounterHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define CounterRC_GLOBAL_ENABLE           (*(reg8 *) CounterRC_CounterHW__PM_ACT_CFG)
    #define CounterRC_GLOBAL_ENABLE_PTR       ( (reg8 *) CounterRC_CounterHW__PM_ACT_CFG)
    #define CounterRC_GLOBAL_STBY_ENABLE      (*(reg8 *) CounterRC_CounterHW__PM_STBY_CFG)
    #define CounterRC_GLOBAL_STBY_ENABLE_PTR  ( (reg8 *) CounterRC_CounterHW__PM_STBY_CFG)
    

    /********************************
    *    Constants
    ********************************/

    /* Fixed Function Block Chosen */
    #define CounterRC_BLOCK_EN_MASK          CounterRC_CounterHW__PM_ACT_MSK
    #define CounterRC_BLOCK_STBY_EN_MASK     CounterRC_CounterHW__PM_STBY_MSK 
    
    /* Control Register Bit Locations */    
    /* As defined in Register Map, part of TMRX_CFG0 register */
    #define CounterRC_CTRL_ENABLE_SHIFT      0x00u
    #define CounterRC_ONESHOT_SHIFT          0x02u
    /* Control Register Bit Masks */
    #define CounterRC_CTRL_ENABLE            ((uint8)((uint8)0x01u << CounterRC_CTRL_ENABLE_SHIFT))         
    #define CounterRC_ONESHOT                ((uint8)((uint8)0x01u << CounterRC_ONESHOT_SHIFT))

    /* Control2 Register Bit Masks */
    /* Set the mask for run mode */
    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        #define CounterRC_CTRL_MODE_SHIFT        0x01u    
        #define CounterRC_CTRL_MODE_MASK         ((uint8)((uint8)0x07u << CounterRC_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Use CFG2 Mode bits to set run mode */
        #define CounterRC_CTRL_MODE_SHIFT        0x00u    
        #define CounterRC_CTRL_MODE_MASK         ((uint8)((uint8)0x03u << CounterRC_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    /* Set the mask for interrupt (raw/status register) */
    #define CounterRC_CTRL2_IRQ_SEL_SHIFT     0x00u
    #define CounterRC_CTRL2_IRQ_SEL          ((uint8)((uint8)0x01u << CounterRC_CTRL2_IRQ_SEL_SHIFT))     
    
    /* Status Register Bit Locations */
    #define CounterRC_STATUS_ZERO_SHIFT      0x07u  /* As defined in Register Map, part of TMRX_SR0 register */ 

    /* Status Register Interrupt Enable Bit Locations */
    #define CounterRC_STATUS_ZERO_INT_EN_MASK_SHIFT      (CounterRC_STATUS_ZERO_SHIFT - 0x04u)

    /* Status Register Bit Masks */                           
    #define CounterRC_STATUS_ZERO            ((uint8)((uint8)0x01u << CounterRC_STATUS_ZERO_SHIFT))

    /* Status Register Interrupt Bit Masks*/
    #define CounterRC_STATUS_ZERO_INT_EN_MASK       ((uint8)((uint8)CounterRC_STATUS_ZERO >> 0x04u))
    
    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define CounterRC_RT1_SHIFT            0x04u
    #define CounterRC_RT1_MASK             ((uint8)((uint8)0x03u << CounterRC_RT1_SHIFT))  /* Sync TC and CMP bit masks */
    #define CounterRC_SYNC                 ((uint8)((uint8)0x03u << CounterRC_RT1_SHIFT))
    #define CounterRC_SYNCDSI_SHIFT        0x00u
    #define CounterRC_SYNCDSI_MASK         ((uint8)((uint8)0x0Fu << CounterRC_SYNCDSI_SHIFT)) /* Sync all DSI inputs */
    #define CounterRC_SYNCDSI_EN           ((uint8)((uint8)0x0Fu << CounterRC_SYNCDSI_SHIFT)) /* Sync all DSI inputs */
    
#else /* !CounterRC_UsingFixedFunction */
    #define CounterRC_STATUS               (* (reg8 *) CounterRC_CounterUDB_sSTSReg_rstSts_stsreg__STATUS_REG )
    #define CounterRC_STATUS_PTR           (  (reg8 *) CounterRC_CounterUDB_sSTSReg_rstSts_stsreg__STATUS_REG )
    #define CounterRC_STATUS_MASK          (* (reg8 *) CounterRC_CounterUDB_sSTSReg_rstSts_stsreg__MASK_REG )
    #define CounterRC_STATUS_MASK_PTR      (  (reg8 *) CounterRC_CounterUDB_sSTSReg_rstSts_stsreg__MASK_REG )
    #define CounterRC_STATUS_AUX_CTRL      (*(reg8 *) CounterRC_CounterUDB_sSTSReg_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define CounterRC_STATUS_AUX_CTRL_PTR  ( (reg8 *) CounterRC_CounterUDB_sSTSReg_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define CounterRC_CONTROL              (* (reg8 *) CounterRC_CounterUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    #define CounterRC_CONTROL_PTR          (  (reg8 *) CounterRC_CounterUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )


    /********************************
    *    Constants
    ********************************/
    /* Control Register Bit Locations */
    #define CounterRC_CTRL_CAPMODE0_SHIFT    0x03u       /* As defined by Verilog Implementation */
    #define CounterRC_CTRL_RESET_SHIFT       0x06u       /* As defined by Verilog Implementation */
    #define CounterRC_CTRL_ENABLE_SHIFT      0x07u       /* As defined by Verilog Implementation */
    /* Control Register Bit Masks */
    #define CounterRC_CTRL_CMPMODE_MASK      0x07u 
    #define CounterRC_CTRL_CAPMODE_MASK      0x03u  
    #define CounterRC_CTRL_RESET             ((uint8)((uint8)0x01u << CounterRC_CTRL_RESET_SHIFT))  
    #define CounterRC_CTRL_ENABLE            ((uint8)((uint8)0x01u << CounterRC_CTRL_ENABLE_SHIFT)) 

    /* Status Register Bit Locations */
    #define CounterRC_STATUS_CMP_SHIFT       0x00u       /* As defined by Verilog Implementation */
    #define CounterRC_STATUS_ZERO_SHIFT      0x01u       /* As defined by Verilog Implementation */
    #define CounterRC_STATUS_OVERFLOW_SHIFT  0x02u       /* As defined by Verilog Implementation */
    #define CounterRC_STATUS_UNDERFLOW_SHIFT 0x03u       /* As defined by Verilog Implementation */
    #define CounterRC_STATUS_CAPTURE_SHIFT   0x04u       /* As defined by Verilog Implementation */
    #define CounterRC_STATUS_FIFOFULL_SHIFT  0x05u       /* As defined by Verilog Implementation */
    #define CounterRC_STATUS_FIFONEMP_SHIFT  0x06u       /* As defined by Verilog Implementation */
    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define CounterRC_STATUS_CMP_INT_EN_MASK_SHIFT       CounterRC_STATUS_CMP_SHIFT       
    #define CounterRC_STATUS_ZERO_INT_EN_MASK_SHIFT      CounterRC_STATUS_ZERO_SHIFT      
    #define CounterRC_STATUS_OVERFLOW_INT_EN_MASK_SHIFT  CounterRC_STATUS_OVERFLOW_SHIFT  
    #define CounterRC_STATUS_UNDERFLOW_INT_EN_MASK_SHIFT CounterRC_STATUS_UNDERFLOW_SHIFT 
    #define CounterRC_STATUS_CAPTURE_INT_EN_MASK_SHIFT   CounterRC_STATUS_CAPTURE_SHIFT   
    #define CounterRC_STATUS_FIFOFULL_INT_EN_MASK_SHIFT  CounterRC_STATUS_FIFOFULL_SHIFT  
    #define CounterRC_STATUS_FIFONEMP_INT_EN_MASK_SHIFT  CounterRC_STATUS_FIFONEMP_SHIFT  
    /* Status Register Bit Masks */                
    #define CounterRC_STATUS_CMP             ((uint8)((uint8)0x01u << CounterRC_STATUS_CMP_SHIFT))  
    #define CounterRC_STATUS_ZERO            ((uint8)((uint8)0x01u << CounterRC_STATUS_ZERO_SHIFT)) 
    #define CounterRC_STATUS_OVERFLOW        ((uint8)((uint8)0x01u << CounterRC_STATUS_OVERFLOW_SHIFT)) 
    #define CounterRC_STATUS_UNDERFLOW       ((uint8)((uint8)0x01u << CounterRC_STATUS_UNDERFLOW_SHIFT)) 
    #define CounterRC_STATUS_CAPTURE         ((uint8)((uint8)0x01u << CounterRC_STATUS_CAPTURE_SHIFT)) 
    #define CounterRC_STATUS_FIFOFULL        ((uint8)((uint8)0x01u << CounterRC_STATUS_FIFOFULL_SHIFT))
    #define CounterRC_STATUS_FIFONEMP        ((uint8)((uint8)0x01u << CounterRC_STATUS_FIFONEMP_SHIFT))
    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define CounterRC_STATUS_CMP_INT_EN_MASK            CounterRC_STATUS_CMP                    
    #define CounterRC_STATUS_ZERO_INT_EN_MASK           CounterRC_STATUS_ZERO            
    #define CounterRC_STATUS_OVERFLOW_INT_EN_MASK       CounterRC_STATUS_OVERFLOW        
    #define CounterRC_STATUS_UNDERFLOW_INT_EN_MASK      CounterRC_STATUS_UNDERFLOW       
    #define CounterRC_STATUS_CAPTURE_INT_EN_MASK        CounterRC_STATUS_CAPTURE         
    #define CounterRC_STATUS_FIFOFULL_INT_EN_MASK       CounterRC_STATUS_FIFOFULL        
    #define CounterRC_STATUS_FIFONEMP_INT_EN_MASK       CounterRC_STATUS_FIFONEMP         
    

    /* StatusI Interrupt Enable bit Location in the Auxilliary Control Register */
    #define CounterRC_STATUS_ACTL_INT_EN     0x10u /* As defined for the ACTL Register */
    
    /* Datapath Auxillary Control Register definitions */
    #define CounterRC_AUX_CTRL_FIFO0_CLR         0x01u   /* As defined by Register map */
    #define CounterRC_AUX_CTRL_FIFO1_CLR         0x02u   /* As defined by Register map */
    #define CounterRC_AUX_CTRL_FIFO0_LVL         0x04u   /* As defined by Register map */
    #define CounterRC_AUX_CTRL_FIFO1_LVL         0x08u   /* As defined by Register map */
    #define CounterRC_STATUS_ACTL_INT_EN_MASK    0x10u   /* As defined for the ACTL Register */
    
#endif /* CounterRC_UsingFixedFunction */

#endif  /* CY_COUNTER_CounterRC_H */


/* [] END OF FILE */

