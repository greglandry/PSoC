/*******************************************************************************
* File Name: CounterR2.h  
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
    
#if !defined(CY_COUNTER_CounterR2_H)
#define CY_COUNTER_CounterR2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 CounterR2_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Counter_v2_40 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults        
**************************************/

#define CounterR2_Resolution            16u
#define CounterR2_UsingFixedFunction    1u
#define CounterR2_ControlRegRemoved     0u
#define CounterR2_COMPARE_MODE_SOFTWARE 0u
#define CounterR2_CAPTURE_MODE_SOFTWARE 0u
#define CounterR2_RunModeUsed           0u


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

    #if (!CounterR2_ControlRegRemoved)
        uint8 CounterControlRegister;               /* Counter Control Register */
    #endif /* (!CounterR2_ControlRegRemoved) */

}CounterR2_backupStruct;


/**************************************
 *  Function Prototypes
 *************************************/
void    CounterR2_Start(void) ;
void    CounterR2_Stop(void) ;
void    CounterR2_SetInterruptMode(uint8 interruptsMask) ;
uint8   CounterR2_ReadStatusRegister(void) ;
#define CounterR2_GetInterruptSource() CounterR2_ReadStatusRegister()
#if(!CounterR2_ControlRegRemoved)
    uint8   CounterR2_ReadControlRegister(void) ;
    void    CounterR2_WriteControlRegister(uint8 control) \
        ;
#endif /* (!CounterR2_ControlRegRemoved) */
#if (!(CounterR2_UsingFixedFunction && (CY_PSOC5A)))
    void    CounterR2_WriteCounter(uint16 counter) \
            ; 
#endif /* (!(CounterR2_UsingFixedFunction && (CY_PSOC5A))) */
uint16  CounterR2_ReadCounter(void) ;
uint16  CounterR2_ReadCapture(void) ;
void    CounterR2_WritePeriod(uint16 period) \
    ;
uint16  CounterR2_ReadPeriod( void ) ;
#if (!CounterR2_UsingFixedFunction)
    void    CounterR2_WriteCompare(uint16 compare) \
        ;
    uint16  CounterR2_ReadCompare( void ) \
        ;
#endif /* (!CounterR2_UsingFixedFunction) */

#if (CounterR2_COMPARE_MODE_SOFTWARE)
    void    CounterR2_SetCompareMode(uint8 compareMode) ;
#endif /* (CounterR2_COMPARE_MODE_SOFTWARE) */
#if (CounterR2_CAPTURE_MODE_SOFTWARE)
    void    CounterR2_SetCaptureMode(uint8 captureMode) ;
#endif /* (CounterR2_CAPTURE_MODE_SOFTWARE) */
void CounterR2_ClearFIFO(void)     ;
void CounterR2_Init(void)          ;
void CounterR2_Enable(void)        ;
void CounterR2_SaveConfig(void)    ;
void CounterR2_RestoreConfig(void) ;
void CounterR2_Sleep(void)         ;
void CounterR2_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Counter__CompareModes, Used in Compare Mode retained for backward compatibility of tests*/
#define CounterR2__B_COUNTER__LESS_THAN 1
#define CounterR2__B_COUNTER__LESS_THAN_OR_EQUAL 2
#define CounterR2__B_COUNTER__EQUAL 0
#define CounterR2__B_COUNTER__GREATER_THAN 3
#define CounterR2__B_COUNTER__GREATER_THAN_OR_EQUAL 4
#define CounterR2__B_COUNTER__SOFTWARE 5

/* Enumerated Type Counter_CompareModes */
#define CounterR2_CMP_MODE_LT 1u
#define CounterR2_CMP_MODE_LTE 2u
#define CounterR2_CMP_MODE_EQ 0u
#define CounterR2_CMP_MODE_GT 3u
#define CounterR2_CMP_MODE_GTE 4u
#define CounterR2_CMP_MODE_SOFTWARE_CONTROLLED 5u

/* Enumerated Type B_Counter__CaptureModes, Used in Capture Mode retained for backward compatibility of tests*/
#define CounterR2__B_COUNTER__NONE 0
#define CounterR2__B_COUNTER__RISING_EDGE 1
#define CounterR2__B_COUNTER__FALLING_EDGE 2
#define CounterR2__B_COUNTER__EITHER_EDGE 3
#define CounterR2__B_COUNTER__SOFTWARE_CONTROL 4

/* Enumerated Type Counter_CompareModes */
#define CounterR2_CAP_MODE_NONE 0u
#define CounterR2_CAP_MODE_RISE 1u
#define CounterR2_CAP_MODE_FALL 2u
#define CounterR2_CAP_MODE_BOTH 3u
#define CounterR2_CAP_MODE_SOFTWARE_CONTROLLED 4u


/***************************************
 *  Initialization Values
 **************************************/
#define CounterR2_CAPTURE_MODE_CONF       0u
#define CounterR2_INIT_PERIOD_VALUE       65535u
#define CounterR2_INIT_COUNTER_VALUE      65535u
#if (CounterR2_UsingFixedFunction)
#define CounterR2_INIT_INTERRUPTS_MASK    ((uint8)((uint8)0u << CounterR2_STATUS_ZERO_INT_EN_MASK_SHIFT))
#else
#define CounterR2_INIT_COMPARE_VALUE      128u
#define CounterR2_INIT_INTERRUPTS_MASK ((uint8)((uint8)0u << CounterR2_STATUS_ZERO_INT_EN_MASK_SHIFT) | \
        ((uint8)((uint8)0u << CounterR2_STATUS_CAPTURE_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << CounterR2_STATUS_CMP_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << CounterR2_STATUS_OVERFLOW_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << CounterR2_STATUS_UNDERFLOW_INT_EN_MASK_SHIFT)))
#define CounterR2_DEFAULT_COMPARE_MODE    1u

#if( 0 != CounterR2_CAPTURE_MODE_CONF)
    #define CounterR2_DEFAULT_CAPTURE_MODE    ((uint8)((uint8)0u << CounterR2_CTRL_CAPMODE0_SHIFT))
#else    
    #define CounterR2_DEFAULT_CAPTURE_MODE    (0u )
#endif /* ( 0 != CounterR2_CAPTURE_MODE_CONF) */

#endif /* (CounterR2_UsingFixedFunction) */


/**************************************
 *  Registers
 *************************************/
#if (CounterR2_UsingFixedFunction)
    #define CounterR2_STATICCOUNT_LSB     (*(reg16 *) CounterR2_CounterHW__CAP0 )
    #define CounterR2_STATICCOUNT_LSB_PTR ( (reg16 *) CounterR2_CounterHW__CAP0 )
    #define CounterR2_PERIOD_LSB          (*(reg16 *) CounterR2_CounterHW__PER0 )
    #define CounterR2_PERIOD_LSB_PTR      ( (reg16 *) CounterR2_CounterHW__PER0 )
    /* MODE must be set to 1 to set the compare value */
    #define CounterR2_COMPARE_LSB         (*(reg16 *) CounterR2_CounterHW__CNT_CMP0 )
    #define CounterR2_COMPARE_LSB_PTR     ( (reg16 *) CounterR2_CounterHW__CNT_CMP0 )
    /* MODE must be set to 0 to get the count */
    #define CounterR2_COUNTER_LSB         (*(reg16 *) CounterR2_CounterHW__CNT_CMP0 )
    #define CounterR2_COUNTER_LSB_PTR     ( (reg16 *) CounterR2_CounterHW__CNT_CMP0 )
    #define CounterR2_RT1                 (*(reg8 *) CounterR2_CounterHW__RT1)
    #define CounterR2_RT1_PTR             ( (reg8 *) CounterR2_CounterHW__RT1)
#else
    
    #if (CounterR2_Resolution <= 8u) /* 8-bit Counter */
    
        #define CounterR2_STATICCOUNT_LSB     (*(reg8 *) \
            CounterR2_CounterUDB_sC16_counterdp_u0__F0_REG )
        #define CounterR2_STATICCOUNT_LSB_PTR ( (reg8 *) \
            CounterR2_CounterUDB_sC16_counterdp_u0__F0_REG )
        #define CounterR2_PERIOD_LSB          (*(reg8 *) \
            CounterR2_CounterUDB_sC16_counterdp_u0__D0_REG )
        #define CounterR2_PERIOD_LSB_PTR      ( (reg8 *) \
            CounterR2_CounterUDB_sC16_counterdp_u0__D0_REG )
        #define CounterR2_COMPARE_LSB         (*(reg8 *) \
            CounterR2_CounterUDB_sC16_counterdp_u0__D1_REG )
        #define CounterR2_COMPARE_LSB_PTR     ( (reg8 *) \
            CounterR2_CounterUDB_sC16_counterdp_u0__D1_REG )
        #define CounterR2_COUNTER_LSB         (*(reg8 *) \
            CounterR2_CounterUDB_sC16_counterdp_u0__A0_REG )  
        #define CounterR2_COUNTER_LSB_PTR     ( (reg8 *)\
            CounterR2_CounterUDB_sC16_counterdp_u0__A0_REG )
    
    #elif(CounterR2_Resolution <= 16u) /* 16-bit Counter */
        #if(CY_PSOC3) /* 8-bit address space */ 
            #define CounterR2_STATICCOUNT_LSB     (*(reg16 *) \
                CounterR2_CounterUDB_sC16_counterdp_u0__F0_REG )
            #define CounterR2_STATICCOUNT_LSB_PTR ( (reg16 *) \
                CounterR2_CounterUDB_sC16_counterdp_u0__F0_REG )
            #define CounterR2_PERIOD_LSB          (*(reg16 *) \
                CounterR2_CounterUDB_sC16_counterdp_u0__D0_REG )
            #define CounterR2_PERIOD_LSB_PTR      ( (reg16 *) \
                CounterR2_CounterUDB_sC16_counterdp_u0__D0_REG )
            #define CounterR2_COMPARE_LSB         (*(reg16 *) \
                CounterR2_CounterUDB_sC16_counterdp_u0__D1_REG )
            #define CounterR2_COMPARE_LSB_PTR     ( (reg16 *) \
                CounterR2_CounterUDB_sC16_counterdp_u0__D1_REG )
            #define CounterR2_COUNTER_LSB         (*(reg16 *) \
                CounterR2_CounterUDB_sC16_counterdp_u0__A0_REG )  
            #define CounterR2_COUNTER_LSB_PTR     ( (reg16 *)\
                CounterR2_CounterUDB_sC16_counterdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define CounterR2_STATICCOUNT_LSB     (*(reg16 *) \
                CounterR2_CounterUDB_sC16_counterdp_u0__16BIT_F0_REG )
            #define CounterR2_STATICCOUNT_LSB_PTR ( (reg16 *) \
                CounterR2_CounterUDB_sC16_counterdp_u0__16BIT_F0_REG )
            #define CounterR2_PERIOD_LSB          (*(reg16 *) \
                CounterR2_CounterUDB_sC16_counterdp_u0__16BIT_D0_REG )
            #define CounterR2_PERIOD_LSB_PTR      ( (reg16 *) \
                CounterR2_CounterUDB_sC16_counterdp_u0__16BIT_D0_REG )
            #define CounterR2_COMPARE_LSB         (*(reg16 *) \
                CounterR2_CounterUDB_sC16_counterdp_u0__16BIT_D1_REG )
            #define CounterR2_COMPARE_LSB_PTR     ( (reg16 *) \
                CounterR2_CounterUDB_sC16_counterdp_u0__16BIT_D1_REG )
            #define CounterR2_COUNTER_LSB         (*(reg16 *) \
                CounterR2_CounterUDB_sC16_counterdp_u0__16BIT_A0_REG )  
            #define CounterR2_COUNTER_LSB_PTR     ( (reg16 *)\
                CounterR2_CounterUDB_sC16_counterdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */   
    #elif(CounterR2_Resolution <= 24u) /* 24-bit Counter */
        
        #define CounterR2_STATICCOUNT_LSB     (*(reg32 *) \
            CounterR2_CounterUDB_sC16_counterdp_u0__F0_REG )
        #define CounterR2_STATICCOUNT_LSB_PTR ( (reg32 *) \
            CounterR2_CounterUDB_sC16_counterdp_u0__F0_REG )
        #define CounterR2_PERIOD_LSB          (*(reg32 *) \
            CounterR2_CounterUDB_sC16_counterdp_u0__D0_REG )
        #define CounterR2_PERIOD_LSB_PTR      ( (reg32 *) \
            CounterR2_CounterUDB_sC16_counterdp_u0__D0_REG )
        #define CounterR2_COMPARE_LSB         (*(reg32 *) \
            CounterR2_CounterUDB_sC16_counterdp_u0__D1_REG )
        #define CounterR2_COMPARE_LSB_PTR     ( (reg32 *) \
            CounterR2_CounterUDB_sC16_counterdp_u0__D1_REG )
        #define CounterR2_COUNTER_LSB         (*(reg32 *) \
            CounterR2_CounterUDB_sC16_counterdp_u0__A0_REG )  
        #define CounterR2_COUNTER_LSB_PTR     ( (reg32 *)\
            CounterR2_CounterUDB_sC16_counterdp_u0__A0_REG )
    
    #else /* 32-bit Counter */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define CounterR2_STATICCOUNT_LSB     (*(reg32 *) \
                CounterR2_CounterUDB_sC16_counterdp_u0__F0_REG )
            #define CounterR2_STATICCOUNT_LSB_PTR ( (reg32 *) \
                CounterR2_CounterUDB_sC16_counterdp_u0__F0_REG )
            #define CounterR2_PERIOD_LSB          (*(reg32 *) \
                CounterR2_CounterUDB_sC16_counterdp_u0__D0_REG )
            #define CounterR2_PERIOD_LSB_PTR      ( (reg32 *) \
                CounterR2_CounterUDB_sC16_counterdp_u0__D0_REG )
            #define CounterR2_COMPARE_LSB         (*(reg32 *) \
                CounterR2_CounterUDB_sC16_counterdp_u0__D1_REG )
            #define CounterR2_COMPARE_LSB_PTR     ( (reg32 *) \
                CounterR2_CounterUDB_sC16_counterdp_u0__D1_REG )
            #define CounterR2_COUNTER_LSB         (*(reg32 *) \
                CounterR2_CounterUDB_sC16_counterdp_u0__A0_REG )  
            #define CounterR2_COUNTER_LSB_PTR     ( (reg32 *)\
                CounterR2_CounterUDB_sC16_counterdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define CounterR2_STATICCOUNT_LSB     (*(reg32 *) \
                CounterR2_CounterUDB_sC16_counterdp_u0__32BIT_F0_REG )
            #define CounterR2_STATICCOUNT_LSB_PTR ( (reg32 *) \
                CounterR2_CounterUDB_sC16_counterdp_u0__32BIT_F0_REG )
            #define CounterR2_PERIOD_LSB          (*(reg32 *) \
                CounterR2_CounterUDB_sC16_counterdp_u0__32BIT_D0_REG )
            #define CounterR2_PERIOD_LSB_PTR      ( (reg32 *) \
                CounterR2_CounterUDB_sC16_counterdp_u0__32BIT_D0_REG )
            #define CounterR2_COMPARE_LSB         (*(reg32 *) \
                CounterR2_CounterUDB_sC16_counterdp_u0__32BIT_D1_REG )
            #define CounterR2_COMPARE_LSB_PTR     ( (reg32 *) \
                CounterR2_CounterUDB_sC16_counterdp_u0__32BIT_D1_REG )
            #define CounterR2_COUNTER_LSB         (*(reg32 *) \
                CounterR2_CounterUDB_sC16_counterdp_u0__32BIT_A0_REG )  
            #define CounterR2_COUNTER_LSB_PTR     ( (reg32 *)\
                CounterR2_CounterUDB_sC16_counterdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */   
    #endif

	#define CounterR2_COUNTER_LSB_PTR_8BIT     ( (reg8 *)\
                CounterR2_CounterUDB_sC16_counterdp_u0__A0_REG )
				
    #define CounterR2_AUX_CONTROLDP0 \
        (*(reg8 *) CounterR2_CounterUDB_sC16_counterdp_u0__DP_AUX_CTL_REG)
    
    #define CounterR2_AUX_CONTROLDP0_PTR \
        ( (reg8 *) CounterR2_CounterUDB_sC16_counterdp_u0__DP_AUX_CTL_REG)
    
    #if (CounterR2_Resolution == 16 || CounterR2_Resolution == 24 || CounterR2_Resolution == 32)
       #define CounterR2_AUX_CONTROLDP1 \
           (*(reg8 *) CounterR2_CounterUDB_sC16_counterdp_u1__DP_AUX_CTL_REG)
       #define CounterR2_AUX_CONTROLDP1_PTR \
           ( (reg8 *) CounterR2_CounterUDB_sC16_counterdp_u1__DP_AUX_CTL_REG)
    #endif /* (CounterR2_Resolution == 16 || CounterR2_Resolution == 24 || CounterR2_Resolution == 32) */
    
    #if (CounterR2_Resolution == 24 || CounterR2_Resolution == 32)
       #define CounterR2_AUX_CONTROLDP2 \
           (*(reg8 *) CounterR2_CounterUDB_sC16_counterdp_u2__DP_AUX_CTL_REG)
       #define CounterR2_AUX_CONTROLDP2_PTR \
           ( (reg8 *) CounterR2_CounterUDB_sC16_counterdp_u2__DP_AUX_CTL_REG)
    #endif /* (CounterR2_Resolution == 24 || CounterR2_Resolution == 32) */
    
    #if (CounterR2_Resolution == 32)
       #define CounterR2_AUX_CONTROLDP3 \
           (*(reg8 *) CounterR2_CounterUDB_sC16_counterdp_u3__DP_AUX_CTL_REG)
       #define CounterR2_AUX_CONTROLDP3_PTR \
           ( (reg8 *) CounterR2_CounterUDB_sC16_counterdp_u3__DP_AUX_CTL_REG)
    #endif /* (CounterR2_Resolution == 32) */

#endif  /* (CounterR2_UsingFixedFunction) */

#if (CounterR2_UsingFixedFunction)
    #define CounterR2_STATUS         (*(reg8 *) CounterR2_CounterHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define CounterR2_STATUS_MASK             (*(reg8 *) CounterR2_CounterHW__SR0 )
    #define CounterR2_STATUS_MASK_PTR         ( (reg8 *) CounterR2_CounterHW__SR0 )
    #define CounterR2_CONTROL                 (*(reg8 *) CounterR2_CounterHW__CFG0)
    #define CounterR2_CONTROL_PTR             ( (reg8 *) CounterR2_CounterHW__CFG0)
    #define CounterR2_CONTROL2                (*(reg8 *) CounterR2_CounterHW__CFG1)
    #define CounterR2_CONTROL2_PTR            ( (reg8 *) CounterR2_CounterHW__CFG1)
    #if (CY_PSOC3 || CY_PSOC5LP)
        #define CounterR2_CONTROL3       (*(reg8 *) CounterR2_CounterHW__CFG2)
        #define CounterR2_CONTROL3_PTR   ( (reg8 *) CounterR2_CounterHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define CounterR2_GLOBAL_ENABLE           (*(reg8 *) CounterR2_CounterHW__PM_ACT_CFG)
    #define CounterR2_GLOBAL_ENABLE_PTR       ( (reg8 *) CounterR2_CounterHW__PM_ACT_CFG)
    #define CounterR2_GLOBAL_STBY_ENABLE      (*(reg8 *) CounterR2_CounterHW__PM_STBY_CFG)
    #define CounterR2_GLOBAL_STBY_ENABLE_PTR  ( (reg8 *) CounterR2_CounterHW__PM_STBY_CFG)
    

    /********************************
    *    Constants
    ********************************/

    /* Fixed Function Block Chosen */
    #define CounterR2_BLOCK_EN_MASK          CounterR2_CounterHW__PM_ACT_MSK
    #define CounterR2_BLOCK_STBY_EN_MASK     CounterR2_CounterHW__PM_STBY_MSK 
    
    /* Control Register Bit Locations */    
    /* As defined in Register Map, part of TMRX_CFG0 register */
    #define CounterR2_CTRL_ENABLE_SHIFT      0x00u
    #define CounterR2_ONESHOT_SHIFT          0x02u
    /* Control Register Bit Masks */
    #define CounterR2_CTRL_ENABLE            ((uint8)((uint8)0x01u << CounterR2_CTRL_ENABLE_SHIFT))         
    #define CounterR2_ONESHOT                ((uint8)((uint8)0x01u << CounterR2_ONESHOT_SHIFT))

    /* Control2 Register Bit Masks */
    /* Set the mask for run mode */
    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        #define CounterR2_CTRL_MODE_SHIFT        0x01u    
        #define CounterR2_CTRL_MODE_MASK         ((uint8)((uint8)0x07u << CounterR2_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Use CFG2 Mode bits to set run mode */
        #define CounterR2_CTRL_MODE_SHIFT        0x00u    
        #define CounterR2_CTRL_MODE_MASK         ((uint8)((uint8)0x03u << CounterR2_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    /* Set the mask for interrupt (raw/status register) */
    #define CounterR2_CTRL2_IRQ_SEL_SHIFT     0x00u
    #define CounterR2_CTRL2_IRQ_SEL          ((uint8)((uint8)0x01u << CounterR2_CTRL2_IRQ_SEL_SHIFT))     
    
    /* Status Register Bit Locations */
    #define CounterR2_STATUS_ZERO_SHIFT      0x07u  /* As defined in Register Map, part of TMRX_SR0 register */ 

    /* Status Register Interrupt Enable Bit Locations */
    #define CounterR2_STATUS_ZERO_INT_EN_MASK_SHIFT      (CounterR2_STATUS_ZERO_SHIFT - 0x04u)

    /* Status Register Bit Masks */                           
    #define CounterR2_STATUS_ZERO            ((uint8)((uint8)0x01u << CounterR2_STATUS_ZERO_SHIFT))

    /* Status Register Interrupt Bit Masks*/
    #define CounterR2_STATUS_ZERO_INT_EN_MASK       ((uint8)((uint8)CounterR2_STATUS_ZERO >> 0x04u))
    
    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define CounterR2_RT1_SHIFT            0x04u
    #define CounterR2_RT1_MASK             ((uint8)((uint8)0x03u << CounterR2_RT1_SHIFT))  /* Sync TC and CMP bit masks */
    #define CounterR2_SYNC                 ((uint8)((uint8)0x03u << CounterR2_RT1_SHIFT))
    #define CounterR2_SYNCDSI_SHIFT        0x00u
    #define CounterR2_SYNCDSI_MASK         ((uint8)((uint8)0x0Fu << CounterR2_SYNCDSI_SHIFT)) /* Sync all DSI inputs */
    #define CounterR2_SYNCDSI_EN           ((uint8)((uint8)0x0Fu << CounterR2_SYNCDSI_SHIFT)) /* Sync all DSI inputs */
    
#else /* !CounterR2_UsingFixedFunction */
    #define CounterR2_STATUS               (* (reg8 *) CounterR2_CounterUDB_sSTSReg_rstSts_stsreg__STATUS_REG )
    #define CounterR2_STATUS_PTR           (  (reg8 *) CounterR2_CounterUDB_sSTSReg_rstSts_stsreg__STATUS_REG )
    #define CounterR2_STATUS_MASK          (* (reg8 *) CounterR2_CounterUDB_sSTSReg_rstSts_stsreg__MASK_REG )
    #define CounterR2_STATUS_MASK_PTR      (  (reg8 *) CounterR2_CounterUDB_sSTSReg_rstSts_stsreg__MASK_REG )
    #define CounterR2_STATUS_AUX_CTRL      (*(reg8 *) CounterR2_CounterUDB_sSTSReg_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define CounterR2_STATUS_AUX_CTRL_PTR  ( (reg8 *) CounterR2_CounterUDB_sSTSReg_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define CounterR2_CONTROL              (* (reg8 *) CounterR2_CounterUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    #define CounterR2_CONTROL_PTR          (  (reg8 *) CounterR2_CounterUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )


    /********************************
    *    Constants
    ********************************/
    /* Control Register Bit Locations */
    #define CounterR2_CTRL_CAPMODE0_SHIFT    0x03u       /* As defined by Verilog Implementation */
    #define CounterR2_CTRL_RESET_SHIFT       0x06u       /* As defined by Verilog Implementation */
    #define CounterR2_CTRL_ENABLE_SHIFT      0x07u       /* As defined by Verilog Implementation */
    /* Control Register Bit Masks */
    #define CounterR2_CTRL_CMPMODE_MASK      0x07u 
    #define CounterR2_CTRL_CAPMODE_MASK      0x03u  
    #define CounterR2_CTRL_RESET             ((uint8)((uint8)0x01u << CounterR2_CTRL_RESET_SHIFT))  
    #define CounterR2_CTRL_ENABLE            ((uint8)((uint8)0x01u << CounterR2_CTRL_ENABLE_SHIFT)) 

    /* Status Register Bit Locations */
    #define CounterR2_STATUS_CMP_SHIFT       0x00u       /* As defined by Verilog Implementation */
    #define CounterR2_STATUS_ZERO_SHIFT      0x01u       /* As defined by Verilog Implementation */
    #define CounterR2_STATUS_OVERFLOW_SHIFT  0x02u       /* As defined by Verilog Implementation */
    #define CounterR2_STATUS_UNDERFLOW_SHIFT 0x03u       /* As defined by Verilog Implementation */
    #define CounterR2_STATUS_CAPTURE_SHIFT   0x04u       /* As defined by Verilog Implementation */
    #define CounterR2_STATUS_FIFOFULL_SHIFT  0x05u       /* As defined by Verilog Implementation */
    #define CounterR2_STATUS_FIFONEMP_SHIFT  0x06u       /* As defined by Verilog Implementation */
    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define CounterR2_STATUS_CMP_INT_EN_MASK_SHIFT       CounterR2_STATUS_CMP_SHIFT       
    #define CounterR2_STATUS_ZERO_INT_EN_MASK_SHIFT      CounterR2_STATUS_ZERO_SHIFT      
    #define CounterR2_STATUS_OVERFLOW_INT_EN_MASK_SHIFT  CounterR2_STATUS_OVERFLOW_SHIFT  
    #define CounterR2_STATUS_UNDERFLOW_INT_EN_MASK_SHIFT CounterR2_STATUS_UNDERFLOW_SHIFT 
    #define CounterR2_STATUS_CAPTURE_INT_EN_MASK_SHIFT   CounterR2_STATUS_CAPTURE_SHIFT   
    #define CounterR2_STATUS_FIFOFULL_INT_EN_MASK_SHIFT  CounterR2_STATUS_FIFOFULL_SHIFT  
    #define CounterR2_STATUS_FIFONEMP_INT_EN_MASK_SHIFT  CounterR2_STATUS_FIFONEMP_SHIFT  
    /* Status Register Bit Masks */                
    #define CounterR2_STATUS_CMP             ((uint8)((uint8)0x01u << CounterR2_STATUS_CMP_SHIFT))  
    #define CounterR2_STATUS_ZERO            ((uint8)((uint8)0x01u << CounterR2_STATUS_ZERO_SHIFT)) 
    #define CounterR2_STATUS_OVERFLOW        ((uint8)((uint8)0x01u << CounterR2_STATUS_OVERFLOW_SHIFT)) 
    #define CounterR2_STATUS_UNDERFLOW       ((uint8)((uint8)0x01u << CounterR2_STATUS_UNDERFLOW_SHIFT)) 
    #define CounterR2_STATUS_CAPTURE         ((uint8)((uint8)0x01u << CounterR2_STATUS_CAPTURE_SHIFT)) 
    #define CounterR2_STATUS_FIFOFULL        ((uint8)((uint8)0x01u << CounterR2_STATUS_FIFOFULL_SHIFT))
    #define CounterR2_STATUS_FIFONEMP        ((uint8)((uint8)0x01u << CounterR2_STATUS_FIFONEMP_SHIFT))
    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define CounterR2_STATUS_CMP_INT_EN_MASK            CounterR2_STATUS_CMP                    
    #define CounterR2_STATUS_ZERO_INT_EN_MASK           CounterR2_STATUS_ZERO            
    #define CounterR2_STATUS_OVERFLOW_INT_EN_MASK       CounterR2_STATUS_OVERFLOW        
    #define CounterR2_STATUS_UNDERFLOW_INT_EN_MASK      CounterR2_STATUS_UNDERFLOW       
    #define CounterR2_STATUS_CAPTURE_INT_EN_MASK        CounterR2_STATUS_CAPTURE         
    #define CounterR2_STATUS_FIFOFULL_INT_EN_MASK       CounterR2_STATUS_FIFOFULL        
    #define CounterR2_STATUS_FIFONEMP_INT_EN_MASK       CounterR2_STATUS_FIFONEMP         
    

    /* StatusI Interrupt Enable bit Location in the Auxilliary Control Register */
    #define CounterR2_STATUS_ACTL_INT_EN     0x10u /* As defined for the ACTL Register */
    
    /* Datapath Auxillary Control Register definitions */
    #define CounterR2_AUX_CTRL_FIFO0_CLR         0x01u   /* As defined by Register map */
    #define CounterR2_AUX_CTRL_FIFO1_CLR         0x02u   /* As defined by Register map */
    #define CounterR2_AUX_CTRL_FIFO0_LVL         0x04u   /* As defined by Register map */
    #define CounterR2_AUX_CTRL_FIFO1_LVL         0x08u   /* As defined by Register map */
    #define CounterR2_STATUS_ACTL_INT_EN_MASK    0x10u   /* As defined for the ACTL Register */
    
#endif /* CounterR2_UsingFixedFunction */

#endif  /* CY_COUNTER_CounterR2_H */


/* [] END OF FILE */

