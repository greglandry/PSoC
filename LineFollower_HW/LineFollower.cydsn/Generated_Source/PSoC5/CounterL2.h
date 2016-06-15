/*******************************************************************************
* File Name: CounterL2.h  
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
    
#if !defined(CY_COUNTER_CounterL2_H)
#define CY_COUNTER_CounterL2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 CounterL2_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Counter_v2_40 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults        
**************************************/

#define CounterL2_Resolution            16u
#define CounterL2_UsingFixedFunction    1u
#define CounterL2_ControlRegRemoved     0u
#define CounterL2_COMPARE_MODE_SOFTWARE 0u
#define CounterL2_CAPTURE_MODE_SOFTWARE 0u
#define CounterL2_RunModeUsed           0u


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
    uint16 CounterUdb;         /* Current Counter Value */

    #if (CY_UDB_V0)
        uint16 CounterPeriod;  /* Counter Period Value */
        uint16 CompareValue;   /* Counter Compare Value */           
        uint8 InterruptMaskValue;                   /* Counter Interrupt Mask Value */
    #endif /* (CY_UDB_V0) */

    #if (!CounterL2_ControlRegRemoved)
        uint8 CounterControlRegister;               /* Counter Control Register */
    #endif /* (!CounterL2_ControlRegRemoved) */

}CounterL2_backupStruct;


/**************************************
 *  Function Prototypes
 *************************************/
void    CounterL2_Start(void) ;
void    CounterL2_Stop(void) ;
void    CounterL2_SetInterruptMode(uint8 interruptsMask) ;
uint8   CounterL2_ReadStatusRegister(void) ;
#define CounterL2_GetInterruptSource() CounterL2_ReadStatusRegister()
#if(!CounterL2_ControlRegRemoved)
    uint8   CounterL2_ReadControlRegister(void) ;
    void    CounterL2_WriteControlRegister(uint8 control) \
        ;
#endif /* (!CounterL2_ControlRegRemoved) */
#if (!(CounterL2_UsingFixedFunction && (CY_PSOC5A)))
    void    CounterL2_WriteCounter(uint16 counter) \
            ; 
#endif /* (!(CounterL2_UsingFixedFunction && (CY_PSOC5A))) */
uint16  CounterL2_ReadCounter(void) ;
uint16  CounterL2_ReadCapture(void) ;
void    CounterL2_WritePeriod(uint16 period) \
    ;
uint16  CounterL2_ReadPeriod( void ) ;
#if (!CounterL2_UsingFixedFunction)
    void    CounterL2_WriteCompare(uint16 compare) \
        ;
    uint16  CounterL2_ReadCompare( void ) \
        ;
#endif /* (!CounterL2_UsingFixedFunction) */

#if (CounterL2_COMPARE_MODE_SOFTWARE)
    void    CounterL2_SetCompareMode(uint8 compareMode) ;
#endif /* (CounterL2_COMPARE_MODE_SOFTWARE) */
#if (CounterL2_CAPTURE_MODE_SOFTWARE)
    void    CounterL2_SetCaptureMode(uint8 captureMode) ;
#endif /* (CounterL2_CAPTURE_MODE_SOFTWARE) */
void CounterL2_ClearFIFO(void)     ;
void CounterL2_Init(void)          ;
void CounterL2_Enable(void)        ;
void CounterL2_SaveConfig(void)    ;
void CounterL2_RestoreConfig(void) ;
void CounterL2_Sleep(void)         ;
void CounterL2_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Counter__CompareModes, Used in Compare Mode retained for backward compatibility of tests*/
#define CounterL2__B_COUNTER__LESS_THAN 1
#define CounterL2__B_COUNTER__LESS_THAN_OR_EQUAL 2
#define CounterL2__B_COUNTER__EQUAL 0
#define CounterL2__B_COUNTER__GREATER_THAN 3
#define CounterL2__B_COUNTER__GREATER_THAN_OR_EQUAL 4
#define CounterL2__B_COUNTER__SOFTWARE 5

/* Enumerated Type Counter_CompareModes */
#define CounterL2_CMP_MODE_LT 1u
#define CounterL2_CMP_MODE_LTE 2u
#define CounterL2_CMP_MODE_EQ 0u
#define CounterL2_CMP_MODE_GT 3u
#define CounterL2_CMP_MODE_GTE 4u
#define CounterL2_CMP_MODE_SOFTWARE_CONTROLLED 5u

/* Enumerated Type B_Counter__CaptureModes, Used in Capture Mode retained for backward compatibility of tests*/
#define CounterL2__B_COUNTER__NONE 0
#define CounterL2__B_COUNTER__RISING_EDGE 1
#define CounterL2__B_COUNTER__FALLING_EDGE 2
#define CounterL2__B_COUNTER__EITHER_EDGE 3
#define CounterL2__B_COUNTER__SOFTWARE_CONTROL 4

/* Enumerated Type Counter_CompareModes */
#define CounterL2_CAP_MODE_NONE 0u
#define CounterL2_CAP_MODE_RISE 1u
#define CounterL2_CAP_MODE_FALL 2u
#define CounterL2_CAP_MODE_BOTH 3u
#define CounterL2_CAP_MODE_SOFTWARE_CONTROLLED 4u


/***************************************
 *  Initialization Values
 **************************************/
#define CounterL2_CAPTURE_MODE_CONF       0u
#define CounterL2_INIT_PERIOD_VALUE       65535u
#define CounterL2_INIT_COUNTER_VALUE      65535u
#if (CounterL2_UsingFixedFunction)
#define CounterL2_INIT_INTERRUPTS_MASK    ((uint8)((uint8)0u << CounterL2_STATUS_ZERO_INT_EN_MASK_SHIFT))
#else
#define CounterL2_INIT_COMPARE_VALUE      128u
#define CounterL2_INIT_INTERRUPTS_MASK ((uint8)((uint8)0u << CounterL2_STATUS_ZERO_INT_EN_MASK_SHIFT) | \
        ((uint8)((uint8)0u << CounterL2_STATUS_CAPTURE_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << CounterL2_STATUS_CMP_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << CounterL2_STATUS_OVERFLOW_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << CounterL2_STATUS_UNDERFLOW_INT_EN_MASK_SHIFT)))
#define CounterL2_DEFAULT_COMPARE_MODE    1u

#if( 0 != CounterL2_CAPTURE_MODE_CONF)
    #define CounterL2_DEFAULT_CAPTURE_MODE    ((uint8)((uint8)0u << CounterL2_CTRL_CAPMODE0_SHIFT))
#else    
    #define CounterL2_DEFAULT_CAPTURE_MODE    (0u )
#endif /* ( 0 != CounterL2_CAPTURE_MODE_CONF) */

#endif /* (CounterL2_UsingFixedFunction) */


/**************************************
 *  Registers
 *************************************/
#if (CounterL2_UsingFixedFunction)
    #define CounterL2_STATICCOUNT_LSB     (*(reg16 *) CounterL2_CounterHW__CAP0 )
    #define CounterL2_STATICCOUNT_LSB_PTR ( (reg16 *) CounterL2_CounterHW__CAP0 )
    #define CounterL2_PERIOD_LSB          (*(reg16 *) CounterL2_CounterHW__PER0 )
    #define CounterL2_PERIOD_LSB_PTR      ( (reg16 *) CounterL2_CounterHW__PER0 )
    /* MODE must be set to 1 to set the compare value */
    #define CounterL2_COMPARE_LSB         (*(reg16 *) CounterL2_CounterHW__CNT_CMP0 )
    #define CounterL2_COMPARE_LSB_PTR     ( (reg16 *) CounterL2_CounterHW__CNT_CMP0 )
    /* MODE must be set to 0 to get the count */
    #define CounterL2_COUNTER_LSB         (*(reg16 *) CounterL2_CounterHW__CNT_CMP0 )
    #define CounterL2_COUNTER_LSB_PTR     ( (reg16 *) CounterL2_CounterHW__CNT_CMP0 )
    #define CounterL2_RT1                 (*(reg8 *) CounterL2_CounterHW__RT1)
    #define CounterL2_RT1_PTR             ( (reg8 *) CounterL2_CounterHW__RT1)
#else
    
    #if (CounterL2_Resolution <= 8u) /* 8-bit Counter */
    
        #define CounterL2_STATICCOUNT_LSB     (*(reg8 *) \
            CounterL2_CounterUDB_sC16_counterdp_u0__F0_REG )
        #define CounterL2_STATICCOUNT_LSB_PTR ( (reg8 *) \
            CounterL2_CounterUDB_sC16_counterdp_u0__F0_REG )
        #define CounterL2_PERIOD_LSB          (*(reg8 *) \
            CounterL2_CounterUDB_sC16_counterdp_u0__D0_REG )
        #define CounterL2_PERIOD_LSB_PTR      ( (reg8 *) \
            CounterL2_CounterUDB_sC16_counterdp_u0__D0_REG )
        #define CounterL2_COMPARE_LSB         (*(reg8 *) \
            CounterL2_CounterUDB_sC16_counterdp_u0__D1_REG )
        #define CounterL2_COMPARE_LSB_PTR     ( (reg8 *) \
            CounterL2_CounterUDB_sC16_counterdp_u0__D1_REG )
        #define CounterL2_COUNTER_LSB         (*(reg8 *) \
            CounterL2_CounterUDB_sC16_counterdp_u0__A0_REG )  
        #define CounterL2_COUNTER_LSB_PTR     ( (reg8 *)\
            CounterL2_CounterUDB_sC16_counterdp_u0__A0_REG )
    
    #elif(CounterL2_Resolution <= 16u) /* 16-bit Counter */
        #if(CY_PSOC3) /* 8-bit address space */ 
            #define CounterL2_STATICCOUNT_LSB     (*(reg16 *) \
                CounterL2_CounterUDB_sC16_counterdp_u0__F0_REG )
            #define CounterL2_STATICCOUNT_LSB_PTR ( (reg16 *) \
                CounterL2_CounterUDB_sC16_counterdp_u0__F0_REG )
            #define CounterL2_PERIOD_LSB          (*(reg16 *) \
                CounterL2_CounterUDB_sC16_counterdp_u0__D0_REG )
            #define CounterL2_PERIOD_LSB_PTR      ( (reg16 *) \
                CounterL2_CounterUDB_sC16_counterdp_u0__D0_REG )
            #define CounterL2_COMPARE_LSB         (*(reg16 *) \
                CounterL2_CounterUDB_sC16_counterdp_u0__D1_REG )
            #define CounterL2_COMPARE_LSB_PTR     ( (reg16 *) \
                CounterL2_CounterUDB_sC16_counterdp_u0__D1_REG )
            #define CounterL2_COUNTER_LSB         (*(reg16 *) \
                CounterL2_CounterUDB_sC16_counterdp_u0__A0_REG )  
            #define CounterL2_COUNTER_LSB_PTR     ( (reg16 *)\
                CounterL2_CounterUDB_sC16_counterdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define CounterL2_STATICCOUNT_LSB     (*(reg16 *) \
                CounterL2_CounterUDB_sC16_counterdp_u0__16BIT_F0_REG )
            #define CounterL2_STATICCOUNT_LSB_PTR ( (reg16 *) \
                CounterL2_CounterUDB_sC16_counterdp_u0__16BIT_F0_REG )
            #define CounterL2_PERIOD_LSB          (*(reg16 *) \
                CounterL2_CounterUDB_sC16_counterdp_u0__16BIT_D0_REG )
            #define CounterL2_PERIOD_LSB_PTR      ( (reg16 *) \
                CounterL2_CounterUDB_sC16_counterdp_u0__16BIT_D0_REG )
            #define CounterL2_COMPARE_LSB         (*(reg16 *) \
                CounterL2_CounterUDB_sC16_counterdp_u0__16BIT_D1_REG )
            #define CounterL2_COMPARE_LSB_PTR     ( (reg16 *) \
                CounterL2_CounterUDB_sC16_counterdp_u0__16BIT_D1_REG )
            #define CounterL2_COUNTER_LSB         (*(reg16 *) \
                CounterL2_CounterUDB_sC16_counterdp_u0__16BIT_A0_REG )  
            #define CounterL2_COUNTER_LSB_PTR     ( (reg16 *)\
                CounterL2_CounterUDB_sC16_counterdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */   
    #elif(CounterL2_Resolution <= 24u) /* 24-bit Counter */
        
        #define CounterL2_STATICCOUNT_LSB     (*(reg32 *) \
            CounterL2_CounterUDB_sC16_counterdp_u0__F0_REG )
        #define CounterL2_STATICCOUNT_LSB_PTR ( (reg32 *) \
            CounterL2_CounterUDB_sC16_counterdp_u0__F0_REG )
        #define CounterL2_PERIOD_LSB          (*(reg32 *) \
            CounterL2_CounterUDB_sC16_counterdp_u0__D0_REG )
        #define CounterL2_PERIOD_LSB_PTR      ( (reg32 *) \
            CounterL2_CounterUDB_sC16_counterdp_u0__D0_REG )
        #define CounterL2_COMPARE_LSB         (*(reg32 *) \
            CounterL2_CounterUDB_sC16_counterdp_u0__D1_REG )
        #define CounterL2_COMPARE_LSB_PTR     ( (reg32 *) \
            CounterL2_CounterUDB_sC16_counterdp_u0__D1_REG )
        #define CounterL2_COUNTER_LSB         (*(reg32 *) \
            CounterL2_CounterUDB_sC16_counterdp_u0__A0_REG )  
        #define CounterL2_COUNTER_LSB_PTR     ( (reg32 *)\
            CounterL2_CounterUDB_sC16_counterdp_u0__A0_REG )
    
    #else /* 32-bit Counter */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define CounterL2_STATICCOUNT_LSB     (*(reg32 *) \
                CounterL2_CounterUDB_sC16_counterdp_u0__F0_REG )
            #define CounterL2_STATICCOUNT_LSB_PTR ( (reg32 *) \
                CounterL2_CounterUDB_sC16_counterdp_u0__F0_REG )
            #define CounterL2_PERIOD_LSB          (*(reg32 *) \
                CounterL2_CounterUDB_sC16_counterdp_u0__D0_REG )
            #define CounterL2_PERIOD_LSB_PTR      ( (reg32 *) \
                CounterL2_CounterUDB_sC16_counterdp_u0__D0_REG )
            #define CounterL2_COMPARE_LSB         (*(reg32 *) \
                CounterL2_CounterUDB_sC16_counterdp_u0__D1_REG )
            #define CounterL2_COMPARE_LSB_PTR     ( (reg32 *) \
                CounterL2_CounterUDB_sC16_counterdp_u0__D1_REG )
            #define CounterL2_COUNTER_LSB         (*(reg32 *) \
                CounterL2_CounterUDB_sC16_counterdp_u0__A0_REG )  
            #define CounterL2_COUNTER_LSB_PTR     ( (reg32 *)\
                CounterL2_CounterUDB_sC16_counterdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define CounterL2_STATICCOUNT_LSB     (*(reg32 *) \
                CounterL2_CounterUDB_sC16_counterdp_u0__32BIT_F0_REG )
            #define CounterL2_STATICCOUNT_LSB_PTR ( (reg32 *) \
                CounterL2_CounterUDB_sC16_counterdp_u0__32BIT_F0_REG )
            #define CounterL2_PERIOD_LSB          (*(reg32 *) \
                CounterL2_CounterUDB_sC16_counterdp_u0__32BIT_D0_REG )
            #define CounterL2_PERIOD_LSB_PTR      ( (reg32 *) \
                CounterL2_CounterUDB_sC16_counterdp_u0__32BIT_D0_REG )
            #define CounterL2_COMPARE_LSB         (*(reg32 *) \
                CounterL2_CounterUDB_sC16_counterdp_u0__32BIT_D1_REG )
            #define CounterL2_COMPARE_LSB_PTR     ( (reg32 *) \
                CounterL2_CounterUDB_sC16_counterdp_u0__32BIT_D1_REG )
            #define CounterL2_COUNTER_LSB         (*(reg32 *) \
                CounterL2_CounterUDB_sC16_counterdp_u0__32BIT_A0_REG )  
            #define CounterL2_COUNTER_LSB_PTR     ( (reg32 *)\
                CounterL2_CounterUDB_sC16_counterdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */   
    #endif

	#define CounterL2_COUNTER_LSB_PTR_8BIT     ( (reg8 *)\
                CounterL2_CounterUDB_sC16_counterdp_u0__A0_REG )
				
    #define CounterL2_AUX_CONTROLDP0 \
        (*(reg8 *) CounterL2_CounterUDB_sC16_counterdp_u0__DP_AUX_CTL_REG)
    
    #define CounterL2_AUX_CONTROLDP0_PTR \
        ( (reg8 *) CounterL2_CounterUDB_sC16_counterdp_u0__DP_AUX_CTL_REG)
    
    #if (CounterL2_Resolution == 16 || CounterL2_Resolution == 24 || CounterL2_Resolution == 32)
       #define CounterL2_AUX_CONTROLDP1 \
           (*(reg8 *) CounterL2_CounterUDB_sC16_counterdp_u1__DP_AUX_CTL_REG)
       #define CounterL2_AUX_CONTROLDP1_PTR \
           ( (reg8 *) CounterL2_CounterUDB_sC16_counterdp_u1__DP_AUX_CTL_REG)
    #endif /* (CounterL2_Resolution == 16 || CounterL2_Resolution == 24 || CounterL2_Resolution == 32) */
    
    #if (CounterL2_Resolution == 24 || CounterL2_Resolution == 32)
       #define CounterL2_AUX_CONTROLDP2 \
           (*(reg8 *) CounterL2_CounterUDB_sC16_counterdp_u2__DP_AUX_CTL_REG)
       #define CounterL2_AUX_CONTROLDP2_PTR \
           ( (reg8 *) CounterL2_CounterUDB_sC16_counterdp_u2__DP_AUX_CTL_REG)
    #endif /* (CounterL2_Resolution == 24 || CounterL2_Resolution == 32) */
    
    #if (CounterL2_Resolution == 32)
       #define CounterL2_AUX_CONTROLDP3 \
           (*(reg8 *) CounterL2_CounterUDB_sC16_counterdp_u3__DP_AUX_CTL_REG)
       #define CounterL2_AUX_CONTROLDP3_PTR \
           ( (reg8 *) CounterL2_CounterUDB_sC16_counterdp_u3__DP_AUX_CTL_REG)
    #endif /* (CounterL2_Resolution == 32) */

#endif  /* (CounterL2_UsingFixedFunction) */

#if (CounterL2_UsingFixedFunction)
    #define CounterL2_STATUS         (*(reg8 *) CounterL2_CounterHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define CounterL2_STATUS_MASK             (*(reg8 *) CounterL2_CounterHW__SR0 )
    #define CounterL2_STATUS_MASK_PTR         ( (reg8 *) CounterL2_CounterHW__SR0 )
    #define CounterL2_CONTROL                 (*(reg8 *) CounterL2_CounterHW__CFG0)
    #define CounterL2_CONTROL_PTR             ( (reg8 *) CounterL2_CounterHW__CFG0)
    #define CounterL2_CONTROL2                (*(reg8 *) CounterL2_CounterHW__CFG1)
    #define CounterL2_CONTROL2_PTR            ( (reg8 *) CounterL2_CounterHW__CFG1)
    #if (CY_PSOC3 || CY_PSOC5LP)
        #define CounterL2_CONTROL3       (*(reg8 *) CounterL2_CounterHW__CFG2)
        #define CounterL2_CONTROL3_PTR   ( (reg8 *) CounterL2_CounterHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define CounterL2_GLOBAL_ENABLE           (*(reg8 *) CounterL2_CounterHW__PM_ACT_CFG)
    #define CounterL2_GLOBAL_ENABLE_PTR       ( (reg8 *) CounterL2_CounterHW__PM_ACT_CFG)
    #define CounterL2_GLOBAL_STBY_ENABLE      (*(reg8 *) CounterL2_CounterHW__PM_STBY_CFG)
    #define CounterL2_GLOBAL_STBY_ENABLE_PTR  ( (reg8 *) CounterL2_CounterHW__PM_STBY_CFG)
    

    /********************************
    *    Constants
    ********************************/

    /* Fixed Function Block Chosen */
    #define CounterL2_BLOCK_EN_MASK          CounterL2_CounterHW__PM_ACT_MSK
    #define CounterL2_BLOCK_STBY_EN_MASK     CounterL2_CounterHW__PM_STBY_MSK 
    
    /* Control Register Bit Locations */    
    /* As defined in Register Map, part of TMRX_CFG0 register */
    #define CounterL2_CTRL_ENABLE_SHIFT      0x00u
    #define CounterL2_ONESHOT_SHIFT          0x02u
    /* Control Register Bit Masks */
    #define CounterL2_CTRL_ENABLE            ((uint8)((uint8)0x01u << CounterL2_CTRL_ENABLE_SHIFT))         
    #define CounterL2_ONESHOT                ((uint8)((uint8)0x01u << CounterL2_ONESHOT_SHIFT))

    /* Control2 Register Bit Masks */
    /* Set the mask for run mode */
    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        #define CounterL2_CTRL_MODE_SHIFT        0x01u    
        #define CounterL2_CTRL_MODE_MASK         ((uint8)((uint8)0x07u << CounterL2_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Use CFG2 Mode bits to set run mode */
        #define CounterL2_CTRL_MODE_SHIFT        0x00u    
        #define CounterL2_CTRL_MODE_MASK         ((uint8)((uint8)0x03u << CounterL2_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    /* Set the mask for interrupt (raw/status register) */
    #define CounterL2_CTRL2_IRQ_SEL_SHIFT     0x00u
    #define CounterL2_CTRL2_IRQ_SEL          ((uint8)((uint8)0x01u << CounterL2_CTRL2_IRQ_SEL_SHIFT))     
    
    /* Status Register Bit Locations */
    #define CounterL2_STATUS_ZERO_SHIFT      0x07u  /* As defined in Register Map, part of TMRX_SR0 register */ 

    /* Status Register Interrupt Enable Bit Locations */
    #define CounterL2_STATUS_ZERO_INT_EN_MASK_SHIFT      (CounterL2_STATUS_ZERO_SHIFT - 0x04u)

    /* Status Register Bit Masks */                           
    #define CounterL2_STATUS_ZERO            ((uint8)((uint8)0x01u << CounterL2_STATUS_ZERO_SHIFT))

    /* Status Register Interrupt Bit Masks*/
    #define CounterL2_STATUS_ZERO_INT_EN_MASK       ((uint8)((uint8)CounterL2_STATUS_ZERO >> 0x04u))
    
    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define CounterL2_RT1_SHIFT            0x04u
    #define CounterL2_RT1_MASK             ((uint8)((uint8)0x03u << CounterL2_RT1_SHIFT))  /* Sync TC and CMP bit masks */
    #define CounterL2_SYNC                 ((uint8)((uint8)0x03u << CounterL2_RT1_SHIFT))
    #define CounterL2_SYNCDSI_SHIFT        0x00u
    #define CounterL2_SYNCDSI_MASK         ((uint8)((uint8)0x0Fu << CounterL2_SYNCDSI_SHIFT)) /* Sync all DSI inputs */
    #define CounterL2_SYNCDSI_EN           ((uint8)((uint8)0x0Fu << CounterL2_SYNCDSI_SHIFT)) /* Sync all DSI inputs */
    
#else /* !CounterL2_UsingFixedFunction */
    #define CounterL2_STATUS               (* (reg8 *) CounterL2_CounterUDB_sSTSReg_rstSts_stsreg__STATUS_REG )
    #define CounterL2_STATUS_PTR           (  (reg8 *) CounterL2_CounterUDB_sSTSReg_rstSts_stsreg__STATUS_REG )
    #define CounterL2_STATUS_MASK          (* (reg8 *) CounterL2_CounterUDB_sSTSReg_rstSts_stsreg__MASK_REG )
    #define CounterL2_STATUS_MASK_PTR      (  (reg8 *) CounterL2_CounterUDB_sSTSReg_rstSts_stsreg__MASK_REG )
    #define CounterL2_STATUS_AUX_CTRL      (*(reg8 *) CounterL2_CounterUDB_sSTSReg_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define CounterL2_STATUS_AUX_CTRL_PTR  ( (reg8 *) CounterL2_CounterUDB_sSTSReg_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define CounterL2_CONTROL              (* (reg8 *) CounterL2_CounterUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    #define CounterL2_CONTROL_PTR          (  (reg8 *) CounterL2_CounterUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )


    /********************************
    *    Constants
    ********************************/
    /* Control Register Bit Locations */
    #define CounterL2_CTRL_CAPMODE0_SHIFT    0x03u       /* As defined by Verilog Implementation */
    #define CounterL2_CTRL_RESET_SHIFT       0x06u       /* As defined by Verilog Implementation */
    #define CounterL2_CTRL_ENABLE_SHIFT      0x07u       /* As defined by Verilog Implementation */
    /* Control Register Bit Masks */
    #define CounterL2_CTRL_CMPMODE_MASK      0x07u 
    #define CounterL2_CTRL_CAPMODE_MASK      0x03u  
    #define CounterL2_CTRL_RESET             ((uint8)((uint8)0x01u << CounterL2_CTRL_RESET_SHIFT))  
    #define CounterL2_CTRL_ENABLE            ((uint8)((uint8)0x01u << CounterL2_CTRL_ENABLE_SHIFT)) 

    /* Status Register Bit Locations */
    #define CounterL2_STATUS_CMP_SHIFT       0x00u       /* As defined by Verilog Implementation */
    #define CounterL2_STATUS_ZERO_SHIFT      0x01u       /* As defined by Verilog Implementation */
    #define CounterL2_STATUS_OVERFLOW_SHIFT  0x02u       /* As defined by Verilog Implementation */
    #define CounterL2_STATUS_UNDERFLOW_SHIFT 0x03u       /* As defined by Verilog Implementation */
    #define CounterL2_STATUS_CAPTURE_SHIFT   0x04u       /* As defined by Verilog Implementation */
    #define CounterL2_STATUS_FIFOFULL_SHIFT  0x05u       /* As defined by Verilog Implementation */
    #define CounterL2_STATUS_FIFONEMP_SHIFT  0x06u       /* As defined by Verilog Implementation */
    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define CounterL2_STATUS_CMP_INT_EN_MASK_SHIFT       CounterL2_STATUS_CMP_SHIFT       
    #define CounterL2_STATUS_ZERO_INT_EN_MASK_SHIFT      CounterL2_STATUS_ZERO_SHIFT      
    #define CounterL2_STATUS_OVERFLOW_INT_EN_MASK_SHIFT  CounterL2_STATUS_OVERFLOW_SHIFT  
    #define CounterL2_STATUS_UNDERFLOW_INT_EN_MASK_SHIFT CounterL2_STATUS_UNDERFLOW_SHIFT 
    #define CounterL2_STATUS_CAPTURE_INT_EN_MASK_SHIFT   CounterL2_STATUS_CAPTURE_SHIFT   
    #define CounterL2_STATUS_FIFOFULL_INT_EN_MASK_SHIFT  CounterL2_STATUS_FIFOFULL_SHIFT  
    #define CounterL2_STATUS_FIFONEMP_INT_EN_MASK_SHIFT  CounterL2_STATUS_FIFONEMP_SHIFT  
    /* Status Register Bit Masks */                
    #define CounterL2_STATUS_CMP             ((uint8)((uint8)0x01u << CounterL2_STATUS_CMP_SHIFT))  
    #define CounterL2_STATUS_ZERO            ((uint8)((uint8)0x01u << CounterL2_STATUS_ZERO_SHIFT)) 
    #define CounterL2_STATUS_OVERFLOW        ((uint8)((uint8)0x01u << CounterL2_STATUS_OVERFLOW_SHIFT)) 
    #define CounterL2_STATUS_UNDERFLOW       ((uint8)((uint8)0x01u << CounterL2_STATUS_UNDERFLOW_SHIFT)) 
    #define CounterL2_STATUS_CAPTURE         ((uint8)((uint8)0x01u << CounterL2_STATUS_CAPTURE_SHIFT)) 
    #define CounterL2_STATUS_FIFOFULL        ((uint8)((uint8)0x01u << CounterL2_STATUS_FIFOFULL_SHIFT))
    #define CounterL2_STATUS_FIFONEMP        ((uint8)((uint8)0x01u << CounterL2_STATUS_FIFONEMP_SHIFT))
    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define CounterL2_STATUS_CMP_INT_EN_MASK            CounterL2_STATUS_CMP                    
    #define CounterL2_STATUS_ZERO_INT_EN_MASK           CounterL2_STATUS_ZERO            
    #define CounterL2_STATUS_OVERFLOW_INT_EN_MASK       CounterL2_STATUS_OVERFLOW        
    #define CounterL2_STATUS_UNDERFLOW_INT_EN_MASK      CounterL2_STATUS_UNDERFLOW       
    #define CounterL2_STATUS_CAPTURE_INT_EN_MASK        CounterL2_STATUS_CAPTURE         
    #define CounterL2_STATUS_FIFOFULL_INT_EN_MASK       CounterL2_STATUS_FIFOFULL        
    #define CounterL2_STATUS_FIFONEMP_INT_EN_MASK       CounterL2_STATUS_FIFONEMP         
    

    /* StatusI Interrupt Enable bit Location in the Auxilliary Control Register */
    #define CounterL2_STATUS_ACTL_INT_EN     0x10u /* As defined for the ACTL Register */
    
    /* Datapath Auxillary Control Register definitions */
    #define CounterL2_AUX_CTRL_FIFO0_CLR         0x01u   /* As defined by Register map */
    #define CounterL2_AUX_CTRL_FIFO1_CLR         0x02u   /* As defined by Register map */
    #define CounterL2_AUX_CTRL_FIFO0_LVL         0x04u   /* As defined by Register map */
    #define CounterL2_AUX_CTRL_FIFO1_LVL         0x08u   /* As defined by Register map */
    #define CounterL2_STATUS_ACTL_INT_EN_MASK    0x10u   /* As defined for the ACTL Register */
    
#endif /* CounterL2_UsingFixedFunction */

#endif  /* CY_COUNTER_CounterL2_H */


/* [] END OF FILE */

