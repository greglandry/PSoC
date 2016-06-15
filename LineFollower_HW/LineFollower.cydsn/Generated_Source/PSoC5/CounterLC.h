/*******************************************************************************
* File Name: CounterLC.h  
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
    
#if !defined(CY_COUNTER_CounterLC_H)
#define CY_COUNTER_CounterLC_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 CounterLC_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Counter_v2_40 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults        
**************************************/

#define CounterLC_Resolution            8u
#define CounterLC_UsingFixedFunction    1u
#define CounterLC_ControlRegRemoved     0u
#define CounterLC_COMPARE_MODE_SOFTWARE 0u
#define CounterLC_CAPTURE_MODE_SOFTWARE 0u
#define CounterLC_RunModeUsed           0u


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

    #if (!CounterLC_ControlRegRemoved)
        uint8 CounterControlRegister;               /* Counter Control Register */
    #endif /* (!CounterLC_ControlRegRemoved) */

}CounterLC_backupStruct;


/**************************************
 *  Function Prototypes
 *************************************/
void    CounterLC_Start(void) ;
void    CounterLC_Stop(void) ;
void    CounterLC_SetInterruptMode(uint8 interruptsMask) ;
uint8   CounterLC_ReadStatusRegister(void) ;
#define CounterLC_GetInterruptSource() CounterLC_ReadStatusRegister()
#if(!CounterLC_ControlRegRemoved)
    uint8   CounterLC_ReadControlRegister(void) ;
    void    CounterLC_WriteControlRegister(uint8 control) \
        ;
#endif /* (!CounterLC_ControlRegRemoved) */
#if (!(CounterLC_UsingFixedFunction && (CY_PSOC5A)))
    void    CounterLC_WriteCounter(uint8 counter) \
            ; 
#endif /* (!(CounterLC_UsingFixedFunction && (CY_PSOC5A))) */
uint8  CounterLC_ReadCounter(void) ;
uint8  CounterLC_ReadCapture(void) ;
void    CounterLC_WritePeriod(uint8 period) \
    ;
uint8  CounterLC_ReadPeriod( void ) ;
#if (!CounterLC_UsingFixedFunction)
    void    CounterLC_WriteCompare(uint8 compare) \
        ;
    uint8  CounterLC_ReadCompare( void ) \
        ;
#endif /* (!CounterLC_UsingFixedFunction) */

#if (CounterLC_COMPARE_MODE_SOFTWARE)
    void    CounterLC_SetCompareMode(uint8 compareMode) ;
#endif /* (CounterLC_COMPARE_MODE_SOFTWARE) */
#if (CounterLC_CAPTURE_MODE_SOFTWARE)
    void    CounterLC_SetCaptureMode(uint8 captureMode) ;
#endif /* (CounterLC_CAPTURE_MODE_SOFTWARE) */
void CounterLC_ClearFIFO(void)     ;
void CounterLC_Init(void)          ;
void CounterLC_Enable(void)        ;
void CounterLC_SaveConfig(void)    ;
void CounterLC_RestoreConfig(void) ;
void CounterLC_Sleep(void)         ;
void CounterLC_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Counter__CompareModes, Used in Compare Mode retained for backward compatibility of tests*/
#define CounterLC__B_COUNTER__LESS_THAN 1
#define CounterLC__B_COUNTER__LESS_THAN_OR_EQUAL 2
#define CounterLC__B_COUNTER__EQUAL 0
#define CounterLC__B_COUNTER__GREATER_THAN 3
#define CounterLC__B_COUNTER__GREATER_THAN_OR_EQUAL 4
#define CounterLC__B_COUNTER__SOFTWARE 5

/* Enumerated Type Counter_CompareModes */
#define CounterLC_CMP_MODE_LT 1u
#define CounterLC_CMP_MODE_LTE 2u
#define CounterLC_CMP_MODE_EQ 0u
#define CounterLC_CMP_MODE_GT 3u
#define CounterLC_CMP_MODE_GTE 4u
#define CounterLC_CMP_MODE_SOFTWARE_CONTROLLED 5u

/* Enumerated Type B_Counter__CaptureModes, Used in Capture Mode retained for backward compatibility of tests*/
#define CounterLC__B_COUNTER__NONE 0
#define CounterLC__B_COUNTER__RISING_EDGE 1
#define CounterLC__B_COUNTER__FALLING_EDGE 2
#define CounterLC__B_COUNTER__EITHER_EDGE 3
#define CounterLC__B_COUNTER__SOFTWARE_CONTROL 4

/* Enumerated Type Counter_CompareModes */
#define CounterLC_CAP_MODE_NONE 0u
#define CounterLC_CAP_MODE_RISE 1u
#define CounterLC_CAP_MODE_FALL 2u
#define CounterLC_CAP_MODE_BOTH 3u
#define CounterLC_CAP_MODE_SOFTWARE_CONTROLLED 4u


/***************************************
 *  Initialization Values
 **************************************/
#define CounterLC_CAPTURE_MODE_CONF       0u
#define CounterLC_INIT_PERIOD_VALUE       255u
#define CounterLC_INIT_COUNTER_VALUE      255u
#if (CounterLC_UsingFixedFunction)
#define CounterLC_INIT_INTERRUPTS_MASK    ((uint8)((uint8)0u << CounterLC_STATUS_ZERO_INT_EN_MASK_SHIFT))
#else
#define CounterLC_INIT_COMPARE_VALUE      128u
#define CounterLC_INIT_INTERRUPTS_MASK ((uint8)((uint8)0u << CounterLC_STATUS_ZERO_INT_EN_MASK_SHIFT) | \
        ((uint8)((uint8)0u << CounterLC_STATUS_CAPTURE_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << CounterLC_STATUS_CMP_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << CounterLC_STATUS_OVERFLOW_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << CounterLC_STATUS_UNDERFLOW_INT_EN_MASK_SHIFT)))
#define CounterLC_DEFAULT_COMPARE_MODE    1u

#if( 0 != CounterLC_CAPTURE_MODE_CONF)
    #define CounterLC_DEFAULT_CAPTURE_MODE    ((uint8)((uint8)0u << CounterLC_CTRL_CAPMODE0_SHIFT))
#else    
    #define CounterLC_DEFAULT_CAPTURE_MODE    (0u )
#endif /* ( 0 != CounterLC_CAPTURE_MODE_CONF) */

#endif /* (CounterLC_UsingFixedFunction) */


/**************************************
 *  Registers
 *************************************/
#if (CounterLC_UsingFixedFunction)
    #define CounterLC_STATICCOUNT_LSB     (*(reg16 *) CounterLC_CounterHW__CAP0 )
    #define CounterLC_STATICCOUNT_LSB_PTR ( (reg16 *) CounterLC_CounterHW__CAP0 )
    #define CounterLC_PERIOD_LSB          (*(reg16 *) CounterLC_CounterHW__PER0 )
    #define CounterLC_PERIOD_LSB_PTR      ( (reg16 *) CounterLC_CounterHW__PER0 )
    /* MODE must be set to 1 to set the compare value */
    #define CounterLC_COMPARE_LSB         (*(reg16 *) CounterLC_CounterHW__CNT_CMP0 )
    #define CounterLC_COMPARE_LSB_PTR     ( (reg16 *) CounterLC_CounterHW__CNT_CMP0 )
    /* MODE must be set to 0 to get the count */
    #define CounterLC_COUNTER_LSB         (*(reg16 *) CounterLC_CounterHW__CNT_CMP0 )
    #define CounterLC_COUNTER_LSB_PTR     ( (reg16 *) CounterLC_CounterHW__CNT_CMP0 )
    #define CounterLC_RT1                 (*(reg8 *) CounterLC_CounterHW__RT1)
    #define CounterLC_RT1_PTR             ( (reg8 *) CounterLC_CounterHW__RT1)
#else
    
    #if (CounterLC_Resolution <= 8u) /* 8-bit Counter */
    
        #define CounterLC_STATICCOUNT_LSB     (*(reg8 *) \
            CounterLC_CounterUDB_sC8_counterdp_u0__F0_REG )
        #define CounterLC_STATICCOUNT_LSB_PTR ( (reg8 *) \
            CounterLC_CounterUDB_sC8_counterdp_u0__F0_REG )
        #define CounterLC_PERIOD_LSB          (*(reg8 *) \
            CounterLC_CounterUDB_sC8_counterdp_u0__D0_REG )
        #define CounterLC_PERIOD_LSB_PTR      ( (reg8 *) \
            CounterLC_CounterUDB_sC8_counterdp_u0__D0_REG )
        #define CounterLC_COMPARE_LSB         (*(reg8 *) \
            CounterLC_CounterUDB_sC8_counterdp_u0__D1_REG )
        #define CounterLC_COMPARE_LSB_PTR     ( (reg8 *) \
            CounterLC_CounterUDB_sC8_counterdp_u0__D1_REG )
        #define CounterLC_COUNTER_LSB         (*(reg8 *) \
            CounterLC_CounterUDB_sC8_counterdp_u0__A0_REG )  
        #define CounterLC_COUNTER_LSB_PTR     ( (reg8 *)\
            CounterLC_CounterUDB_sC8_counterdp_u0__A0_REG )
    
    #elif(CounterLC_Resolution <= 16u) /* 16-bit Counter */
        #if(CY_PSOC3) /* 8-bit address space */ 
            #define CounterLC_STATICCOUNT_LSB     (*(reg16 *) \
                CounterLC_CounterUDB_sC8_counterdp_u0__F0_REG )
            #define CounterLC_STATICCOUNT_LSB_PTR ( (reg16 *) \
                CounterLC_CounterUDB_sC8_counterdp_u0__F0_REG )
            #define CounterLC_PERIOD_LSB          (*(reg16 *) \
                CounterLC_CounterUDB_sC8_counterdp_u0__D0_REG )
            #define CounterLC_PERIOD_LSB_PTR      ( (reg16 *) \
                CounterLC_CounterUDB_sC8_counterdp_u0__D0_REG )
            #define CounterLC_COMPARE_LSB         (*(reg16 *) \
                CounterLC_CounterUDB_sC8_counterdp_u0__D1_REG )
            #define CounterLC_COMPARE_LSB_PTR     ( (reg16 *) \
                CounterLC_CounterUDB_sC8_counterdp_u0__D1_REG )
            #define CounterLC_COUNTER_LSB         (*(reg16 *) \
                CounterLC_CounterUDB_sC8_counterdp_u0__A0_REG )  
            #define CounterLC_COUNTER_LSB_PTR     ( (reg16 *)\
                CounterLC_CounterUDB_sC8_counterdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define CounterLC_STATICCOUNT_LSB     (*(reg16 *) \
                CounterLC_CounterUDB_sC8_counterdp_u0__16BIT_F0_REG )
            #define CounterLC_STATICCOUNT_LSB_PTR ( (reg16 *) \
                CounterLC_CounterUDB_sC8_counterdp_u0__16BIT_F0_REG )
            #define CounterLC_PERIOD_LSB          (*(reg16 *) \
                CounterLC_CounterUDB_sC8_counterdp_u0__16BIT_D0_REG )
            #define CounterLC_PERIOD_LSB_PTR      ( (reg16 *) \
                CounterLC_CounterUDB_sC8_counterdp_u0__16BIT_D0_REG )
            #define CounterLC_COMPARE_LSB         (*(reg16 *) \
                CounterLC_CounterUDB_sC8_counterdp_u0__16BIT_D1_REG )
            #define CounterLC_COMPARE_LSB_PTR     ( (reg16 *) \
                CounterLC_CounterUDB_sC8_counterdp_u0__16BIT_D1_REG )
            #define CounterLC_COUNTER_LSB         (*(reg16 *) \
                CounterLC_CounterUDB_sC8_counterdp_u0__16BIT_A0_REG )  
            #define CounterLC_COUNTER_LSB_PTR     ( (reg16 *)\
                CounterLC_CounterUDB_sC8_counterdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */   
    #elif(CounterLC_Resolution <= 24u) /* 24-bit Counter */
        
        #define CounterLC_STATICCOUNT_LSB     (*(reg32 *) \
            CounterLC_CounterUDB_sC8_counterdp_u0__F0_REG )
        #define CounterLC_STATICCOUNT_LSB_PTR ( (reg32 *) \
            CounterLC_CounterUDB_sC8_counterdp_u0__F0_REG )
        #define CounterLC_PERIOD_LSB          (*(reg32 *) \
            CounterLC_CounterUDB_sC8_counterdp_u0__D0_REG )
        #define CounterLC_PERIOD_LSB_PTR      ( (reg32 *) \
            CounterLC_CounterUDB_sC8_counterdp_u0__D0_REG )
        #define CounterLC_COMPARE_LSB         (*(reg32 *) \
            CounterLC_CounterUDB_sC8_counterdp_u0__D1_REG )
        #define CounterLC_COMPARE_LSB_PTR     ( (reg32 *) \
            CounterLC_CounterUDB_sC8_counterdp_u0__D1_REG )
        #define CounterLC_COUNTER_LSB         (*(reg32 *) \
            CounterLC_CounterUDB_sC8_counterdp_u0__A0_REG )  
        #define CounterLC_COUNTER_LSB_PTR     ( (reg32 *)\
            CounterLC_CounterUDB_sC8_counterdp_u0__A0_REG )
    
    #else /* 32-bit Counter */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define CounterLC_STATICCOUNT_LSB     (*(reg32 *) \
                CounterLC_CounterUDB_sC8_counterdp_u0__F0_REG )
            #define CounterLC_STATICCOUNT_LSB_PTR ( (reg32 *) \
                CounterLC_CounterUDB_sC8_counterdp_u0__F0_REG )
            #define CounterLC_PERIOD_LSB          (*(reg32 *) \
                CounterLC_CounterUDB_sC8_counterdp_u0__D0_REG )
            #define CounterLC_PERIOD_LSB_PTR      ( (reg32 *) \
                CounterLC_CounterUDB_sC8_counterdp_u0__D0_REG )
            #define CounterLC_COMPARE_LSB         (*(reg32 *) \
                CounterLC_CounterUDB_sC8_counterdp_u0__D1_REG )
            #define CounterLC_COMPARE_LSB_PTR     ( (reg32 *) \
                CounterLC_CounterUDB_sC8_counterdp_u0__D1_REG )
            #define CounterLC_COUNTER_LSB         (*(reg32 *) \
                CounterLC_CounterUDB_sC8_counterdp_u0__A0_REG )  
            #define CounterLC_COUNTER_LSB_PTR     ( (reg32 *)\
                CounterLC_CounterUDB_sC8_counterdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define CounterLC_STATICCOUNT_LSB     (*(reg32 *) \
                CounterLC_CounterUDB_sC8_counterdp_u0__32BIT_F0_REG )
            #define CounterLC_STATICCOUNT_LSB_PTR ( (reg32 *) \
                CounterLC_CounterUDB_sC8_counterdp_u0__32BIT_F0_REG )
            #define CounterLC_PERIOD_LSB          (*(reg32 *) \
                CounterLC_CounterUDB_sC8_counterdp_u0__32BIT_D0_REG )
            #define CounterLC_PERIOD_LSB_PTR      ( (reg32 *) \
                CounterLC_CounterUDB_sC8_counterdp_u0__32BIT_D0_REG )
            #define CounterLC_COMPARE_LSB         (*(reg32 *) \
                CounterLC_CounterUDB_sC8_counterdp_u0__32BIT_D1_REG )
            #define CounterLC_COMPARE_LSB_PTR     ( (reg32 *) \
                CounterLC_CounterUDB_sC8_counterdp_u0__32BIT_D1_REG )
            #define CounterLC_COUNTER_LSB         (*(reg32 *) \
                CounterLC_CounterUDB_sC8_counterdp_u0__32BIT_A0_REG )  
            #define CounterLC_COUNTER_LSB_PTR     ( (reg32 *)\
                CounterLC_CounterUDB_sC8_counterdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */   
    #endif

	#define CounterLC_COUNTER_LSB_PTR_8BIT     ( (reg8 *)\
                CounterLC_CounterUDB_sC8_counterdp_u0__A0_REG )
				
    #define CounterLC_AUX_CONTROLDP0 \
        (*(reg8 *) CounterLC_CounterUDB_sC8_counterdp_u0__DP_AUX_CTL_REG)
    
    #define CounterLC_AUX_CONTROLDP0_PTR \
        ( (reg8 *) CounterLC_CounterUDB_sC8_counterdp_u0__DP_AUX_CTL_REG)
    
    #if (CounterLC_Resolution == 16 || CounterLC_Resolution == 24 || CounterLC_Resolution == 32)
       #define CounterLC_AUX_CONTROLDP1 \
           (*(reg8 *) CounterLC_CounterUDB_sC8_counterdp_u1__DP_AUX_CTL_REG)
       #define CounterLC_AUX_CONTROLDP1_PTR \
           ( (reg8 *) CounterLC_CounterUDB_sC8_counterdp_u1__DP_AUX_CTL_REG)
    #endif /* (CounterLC_Resolution == 16 || CounterLC_Resolution == 24 || CounterLC_Resolution == 32) */
    
    #if (CounterLC_Resolution == 24 || CounterLC_Resolution == 32)
       #define CounterLC_AUX_CONTROLDP2 \
           (*(reg8 *) CounterLC_CounterUDB_sC8_counterdp_u2__DP_AUX_CTL_REG)
       #define CounterLC_AUX_CONTROLDP2_PTR \
           ( (reg8 *) CounterLC_CounterUDB_sC8_counterdp_u2__DP_AUX_CTL_REG)
    #endif /* (CounterLC_Resolution == 24 || CounterLC_Resolution == 32) */
    
    #if (CounterLC_Resolution == 32)
       #define CounterLC_AUX_CONTROLDP3 \
           (*(reg8 *) CounterLC_CounterUDB_sC8_counterdp_u3__DP_AUX_CTL_REG)
       #define CounterLC_AUX_CONTROLDP3_PTR \
           ( (reg8 *) CounterLC_CounterUDB_sC8_counterdp_u3__DP_AUX_CTL_REG)
    #endif /* (CounterLC_Resolution == 32) */

#endif  /* (CounterLC_UsingFixedFunction) */

#if (CounterLC_UsingFixedFunction)
    #define CounterLC_STATUS         (*(reg8 *) CounterLC_CounterHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define CounterLC_STATUS_MASK             (*(reg8 *) CounterLC_CounterHW__SR0 )
    #define CounterLC_STATUS_MASK_PTR         ( (reg8 *) CounterLC_CounterHW__SR0 )
    #define CounterLC_CONTROL                 (*(reg8 *) CounterLC_CounterHW__CFG0)
    #define CounterLC_CONTROL_PTR             ( (reg8 *) CounterLC_CounterHW__CFG0)
    #define CounterLC_CONTROL2                (*(reg8 *) CounterLC_CounterHW__CFG1)
    #define CounterLC_CONTROL2_PTR            ( (reg8 *) CounterLC_CounterHW__CFG1)
    #if (CY_PSOC3 || CY_PSOC5LP)
        #define CounterLC_CONTROL3       (*(reg8 *) CounterLC_CounterHW__CFG2)
        #define CounterLC_CONTROL3_PTR   ( (reg8 *) CounterLC_CounterHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define CounterLC_GLOBAL_ENABLE           (*(reg8 *) CounterLC_CounterHW__PM_ACT_CFG)
    #define CounterLC_GLOBAL_ENABLE_PTR       ( (reg8 *) CounterLC_CounterHW__PM_ACT_CFG)
    #define CounterLC_GLOBAL_STBY_ENABLE      (*(reg8 *) CounterLC_CounterHW__PM_STBY_CFG)
    #define CounterLC_GLOBAL_STBY_ENABLE_PTR  ( (reg8 *) CounterLC_CounterHW__PM_STBY_CFG)
    

    /********************************
    *    Constants
    ********************************/

    /* Fixed Function Block Chosen */
    #define CounterLC_BLOCK_EN_MASK          CounterLC_CounterHW__PM_ACT_MSK
    #define CounterLC_BLOCK_STBY_EN_MASK     CounterLC_CounterHW__PM_STBY_MSK 
    
    /* Control Register Bit Locations */    
    /* As defined in Register Map, part of TMRX_CFG0 register */
    #define CounterLC_CTRL_ENABLE_SHIFT      0x00u
    #define CounterLC_ONESHOT_SHIFT          0x02u
    /* Control Register Bit Masks */
    #define CounterLC_CTRL_ENABLE            ((uint8)((uint8)0x01u << CounterLC_CTRL_ENABLE_SHIFT))         
    #define CounterLC_ONESHOT                ((uint8)((uint8)0x01u << CounterLC_ONESHOT_SHIFT))

    /* Control2 Register Bit Masks */
    /* Set the mask for run mode */
    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        #define CounterLC_CTRL_MODE_SHIFT        0x01u    
        #define CounterLC_CTRL_MODE_MASK         ((uint8)((uint8)0x07u << CounterLC_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Use CFG2 Mode bits to set run mode */
        #define CounterLC_CTRL_MODE_SHIFT        0x00u    
        #define CounterLC_CTRL_MODE_MASK         ((uint8)((uint8)0x03u << CounterLC_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    /* Set the mask for interrupt (raw/status register) */
    #define CounterLC_CTRL2_IRQ_SEL_SHIFT     0x00u
    #define CounterLC_CTRL2_IRQ_SEL          ((uint8)((uint8)0x01u << CounterLC_CTRL2_IRQ_SEL_SHIFT))     
    
    /* Status Register Bit Locations */
    #define CounterLC_STATUS_ZERO_SHIFT      0x07u  /* As defined in Register Map, part of TMRX_SR0 register */ 

    /* Status Register Interrupt Enable Bit Locations */
    #define CounterLC_STATUS_ZERO_INT_EN_MASK_SHIFT      (CounterLC_STATUS_ZERO_SHIFT - 0x04u)

    /* Status Register Bit Masks */                           
    #define CounterLC_STATUS_ZERO            ((uint8)((uint8)0x01u << CounterLC_STATUS_ZERO_SHIFT))

    /* Status Register Interrupt Bit Masks*/
    #define CounterLC_STATUS_ZERO_INT_EN_MASK       ((uint8)((uint8)CounterLC_STATUS_ZERO >> 0x04u))
    
    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define CounterLC_RT1_SHIFT            0x04u
    #define CounterLC_RT1_MASK             ((uint8)((uint8)0x03u << CounterLC_RT1_SHIFT))  /* Sync TC and CMP bit masks */
    #define CounterLC_SYNC                 ((uint8)((uint8)0x03u << CounterLC_RT1_SHIFT))
    #define CounterLC_SYNCDSI_SHIFT        0x00u
    #define CounterLC_SYNCDSI_MASK         ((uint8)((uint8)0x0Fu << CounterLC_SYNCDSI_SHIFT)) /* Sync all DSI inputs */
    #define CounterLC_SYNCDSI_EN           ((uint8)((uint8)0x0Fu << CounterLC_SYNCDSI_SHIFT)) /* Sync all DSI inputs */
    
#else /* !CounterLC_UsingFixedFunction */
    #define CounterLC_STATUS               (* (reg8 *) CounterLC_CounterUDB_sSTSReg_rstSts_stsreg__STATUS_REG )
    #define CounterLC_STATUS_PTR           (  (reg8 *) CounterLC_CounterUDB_sSTSReg_rstSts_stsreg__STATUS_REG )
    #define CounterLC_STATUS_MASK          (* (reg8 *) CounterLC_CounterUDB_sSTSReg_rstSts_stsreg__MASK_REG )
    #define CounterLC_STATUS_MASK_PTR      (  (reg8 *) CounterLC_CounterUDB_sSTSReg_rstSts_stsreg__MASK_REG )
    #define CounterLC_STATUS_AUX_CTRL      (*(reg8 *) CounterLC_CounterUDB_sSTSReg_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define CounterLC_STATUS_AUX_CTRL_PTR  ( (reg8 *) CounterLC_CounterUDB_sSTSReg_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define CounterLC_CONTROL              (* (reg8 *) CounterLC_CounterUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    #define CounterLC_CONTROL_PTR          (  (reg8 *) CounterLC_CounterUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )


    /********************************
    *    Constants
    ********************************/
    /* Control Register Bit Locations */
    #define CounterLC_CTRL_CAPMODE0_SHIFT    0x03u       /* As defined by Verilog Implementation */
    #define CounterLC_CTRL_RESET_SHIFT       0x06u       /* As defined by Verilog Implementation */
    #define CounterLC_CTRL_ENABLE_SHIFT      0x07u       /* As defined by Verilog Implementation */
    /* Control Register Bit Masks */
    #define CounterLC_CTRL_CMPMODE_MASK      0x07u 
    #define CounterLC_CTRL_CAPMODE_MASK      0x03u  
    #define CounterLC_CTRL_RESET             ((uint8)((uint8)0x01u << CounterLC_CTRL_RESET_SHIFT))  
    #define CounterLC_CTRL_ENABLE            ((uint8)((uint8)0x01u << CounterLC_CTRL_ENABLE_SHIFT)) 

    /* Status Register Bit Locations */
    #define CounterLC_STATUS_CMP_SHIFT       0x00u       /* As defined by Verilog Implementation */
    #define CounterLC_STATUS_ZERO_SHIFT      0x01u       /* As defined by Verilog Implementation */
    #define CounterLC_STATUS_OVERFLOW_SHIFT  0x02u       /* As defined by Verilog Implementation */
    #define CounterLC_STATUS_UNDERFLOW_SHIFT 0x03u       /* As defined by Verilog Implementation */
    #define CounterLC_STATUS_CAPTURE_SHIFT   0x04u       /* As defined by Verilog Implementation */
    #define CounterLC_STATUS_FIFOFULL_SHIFT  0x05u       /* As defined by Verilog Implementation */
    #define CounterLC_STATUS_FIFONEMP_SHIFT  0x06u       /* As defined by Verilog Implementation */
    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define CounterLC_STATUS_CMP_INT_EN_MASK_SHIFT       CounterLC_STATUS_CMP_SHIFT       
    #define CounterLC_STATUS_ZERO_INT_EN_MASK_SHIFT      CounterLC_STATUS_ZERO_SHIFT      
    #define CounterLC_STATUS_OVERFLOW_INT_EN_MASK_SHIFT  CounterLC_STATUS_OVERFLOW_SHIFT  
    #define CounterLC_STATUS_UNDERFLOW_INT_EN_MASK_SHIFT CounterLC_STATUS_UNDERFLOW_SHIFT 
    #define CounterLC_STATUS_CAPTURE_INT_EN_MASK_SHIFT   CounterLC_STATUS_CAPTURE_SHIFT   
    #define CounterLC_STATUS_FIFOFULL_INT_EN_MASK_SHIFT  CounterLC_STATUS_FIFOFULL_SHIFT  
    #define CounterLC_STATUS_FIFONEMP_INT_EN_MASK_SHIFT  CounterLC_STATUS_FIFONEMP_SHIFT  
    /* Status Register Bit Masks */                
    #define CounterLC_STATUS_CMP             ((uint8)((uint8)0x01u << CounterLC_STATUS_CMP_SHIFT))  
    #define CounterLC_STATUS_ZERO            ((uint8)((uint8)0x01u << CounterLC_STATUS_ZERO_SHIFT)) 
    #define CounterLC_STATUS_OVERFLOW        ((uint8)((uint8)0x01u << CounterLC_STATUS_OVERFLOW_SHIFT)) 
    #define CounterLC_STATUS_UNDERFLOW       ((uint8)((uint8)0x01u << CounterLC_STATUS_UNDERFLOW_SHIFT)) 
    #define CounterLC_STATUS_CAPTURE         ((uint8)((uint8)0x01u << CounterLC_STATUS_CAPTURE_SHIFT)) 
    #define CounterLC_STATUS_FIFOFULL        ((uint8)((uint8)0x01u << CounterLC_STATUS_FIFOFULL_SHIFT))
    #define CounterLC_STATUS_FIFONEMP        ((uint8)((uint8)0x01u << CounterLC_STATUS_FIFONEMP_SHIFT))
    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define CounterLC_STATUS_CMP_INT_EN_MASK            CounterLC_STATUS_CMP                    
    #define CounterLC_STATUS_ZERO_INT_EN_MASK           CounterLC_STATUS_ZERO            
    #define CounterLC_STATUS_OVERFLOW_INT_EN_MASK       CounterLC_STATUS_OVERFLOW        
    #define CounterLC_STATUS_UNDERFLOW_INT_EN_MASK      CounterLC_STATUS_UNDERFLOW       
    #define CounterLC_STATUS_CAPTURE_INT_EN_MASK        CounterLC_STATUS_CAPTURE         
    #define CounterLC_STATUS_FIFOFULL_INT_EN_MASK       CounterLC_STATUS_FIFOFULL        
    #define CounterLC_STATUS_FIFONEMP_INT_EN_MASK       CounterLC_STATUS_FIFONEMP         
    

    /* StatusI Interrupt Enable bit Location in the Auxilliary Control Register */
    #define CounterLC_STATUS_ACTL_INT_EN     0x10u /* As defined for the ACTL Register */
    
    /* Datapath Auxillary Control Register definitions */
    #define CounterLC_AUX_CTRL_FIFO0_CLR         0x01u   /* As defined by Register map */
    #define CounterLC_AUX_CTRL_FIFO1_CLR         0x02u   /* As defined by Register map */
    #define CounterLC_AUX_CTRL_FIFO0_LVL         0x04u   /* As defined by Register map */
    #define CounterLC_AUX_CTRL_FIFO1_LVL         0x08u   /* As defined by Register map */
    #define CounterLC_STATUS_ACTL_INT_EN_MASK    0x10u   /* As defined for the ACTL Register */
    
#endif /* CounterLC_UsingFixedFunction */

#endif  /* CY_COUNTER_CounterLC_H */


/* [] END OF FILE */

