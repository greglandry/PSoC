/*******************************************************************************
* File Name: PWML.h  
* Version 3.0
*
* Description:
*  Contains the prototypes and constants for the functions available to the 
*  PWM user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PWM_PWML_H)
#define CY_PWM_PWML_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 PWML_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define PWML_Resolution 8u
#define PWML_UsingFixedFunction 0u
#define PWML_DeadBandMode 0u
#define PWML_KillModeMinTime 0u
#define PWML_KillMode 0u
#define PWML_PWMMode 0u
#define PWML_PWMModeIsCenterAligned 0u
#define PWML_DeadBandUsed 0u
#define PWML_DeadBand2_4 0u

#if !defined(PWML_PWMUDB_genblk8_stsreg__REMOVED)
    #define PWML_UseStatus 1u
#else
    #define PWML_UseStatus 0u
#endif /* !defined(PWML_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(PWML_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define PWML_UseControl 1u
#else
    #define PWML_UseControl 0u
#endif /* !defined(PWML_PWMUDB_genblk1_ctrlreg__REMOVED) */
#define PWML_UseOneCompareMode 1u
#define PWML_MinimumKillTime 1u
#define PWML_EnableMode 0u

#define PWML_CompareMode1SW 0u
#define PWML_CompareMode2SW 0u

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_0 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define PWML__B_PWM__DISABLED 0
#define PWML__B_PWM__ASYNCHRONOUS 1
#define PWML__B_PWM__SINGLECYCLE 2
#define PWML__B_PWM__LATCHED 3
#define PWML__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define PWML__B_PWM__DBMDISABLED 0
#define PWML__B_PWM__DBM_2_4_CLOCKS 1
#define PWML__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define PWML__B_PWM__ONE_OUTPUT 0
#define PWML__B_PWM__TWO_OUTPUTS 1
#define PWML__B_PWM__DUAL_EDGE 2
#define PWML__B_PWM__CENTER_ALIGN 3
#define PWML__B_PWM__DITHER 5
#define PWML__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define PWML__B_PWM__LESS_THAN 1
#define PWML__B_PWM__LESS_THAN_OR_EQUAL 2
#define PWML__B_PWM__GREATER_THAN 3
#define PWML__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define PWML__B_PWM__EQUAL 0
#define PWML__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{
    
    uint8 PWMEnableState;
       
    #if(!PWML_UsingFixedFunction)
        uint8 PWMUdb;               /* PWM Current Counter value  */
        #if(!PWML_PWMModeIsCenterAligned)
            uint8 PWMPeriod;
        #endif /* (!PWML_PWMModeIsCenterAligned) */
        #if (PWML_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (PWML_UseStatus) */
        
        /* Backup for Deadband parameters */
        #if(PWML_DeadBandMode == PWML__B_PWM__DBM_256_CLOCKS || \
            PWML_DeadBandMode == PWML__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */
        
        /* Backup Kill Mode Counter*/
        #if(PWML_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (PWML_KillModeMinTime) */
       
        /* Backup control register */
        #if(PWML_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (PWML_UseControl) */
        
    #endif /* (!PWML_UsingFixedFunction) */
   
}PWML_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/
 
void    PWML_Start(void) ;
void    PWML_Stop(void) ;

#if (PWML_UseStatus || PWML_UsingFixedFunction)
    void  PWML_SetInterruptMode(uint8 interruptMode) ;
    uint8 PWML_ReadStatusRegister(void) ;
#endif /* (PWML_UseStatus || PWML_UsingFixedFunction) */

#define PWML_GetInterruptSource() PWML_ReadStatusRegister()

#if (PWML_UseControl)
    uint8 PWML_ReadControlRegister(void) ; 
    void  PWML_WriteControlRegister(uint8 control) ;
#endif /* (PWML_UseControl) */

#if (PWML_UseOneCompareMode)
   #if (PWML_CompareMode1SW)
       void    PWML_SetCompareMode(uint8 comparemode) ;
   #endif /* (PWML_CompareMode1SW) */
#else
    #if (PWML_CompareMode1SW)
        void    PWML_SetCompareMode1(uint8 comparemode) ;
    #endif /* (PWML_CompareMode1SW) */
    #if (PWML_CompareMode2SW)
        void    PWML_SetCompareMode2(uint8 comparemode) ;
    #endif /* (PWML_CompareMode2SW) */
#endif /* (PWML_UseOneCompareMode) */

#if (!PWML_UsingFixedFunction)
    uint8   PWML_ReadCounter(void) ;
    uint8 PWML_ReadCapture(void) ;
    
	#if (PWML_UseStatus)
	        void PWML_ClearFIFO(void) ;
	#endif /* (PWML_UseStatus) */

    void    PWML_WriteCounter(uint8 counter) ;
#endif /* (!PWML_UsingFixedFunction) */

void    PWML_WritePeriod(uint8 period) ;
uint8 PWML_ReadPeriod(void) ;

#if (PWML_UseOneCompareMode)
    void    PWML_WriteCompare(uint8 compare) ;
    uint8 PWML_ReadCompare(void) ; 
#else
    void    PWML_WriteCompare1(uint8 compare) ;
    uint8 PWML_ReadCompare1(void) ; 
    void    PWML_WriteCompare2(uint8 compare) ;
    uint8 PWML_ReadCompare2(void) ; 
#endif /* (PWML_UseOneCompareMode) */


#if (PWML_DeadBandUsed)
    void    PWML_WriteDeadTime(uint8 deadtime) ;
    uint8   PWML_ReadDeadTime(void) ;
#endif /* (PWML_DeadBandUsed) */

#if ( PWML_KillModeMinTime)
    void PWML_WriteKillTime(uint8 killtime) ;
    uint8 PWML_ReadKillTime(void) ; 
#endif /* ( PWML_KillModeMinTime) */

void PWML_Init(void) ;
void PWML_Enable(void) ;
void PWML_Sleep(void) ;
void PWML_Wakeup(void) ;
void PWML_SaveConfig(void) ;
void PWML_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define PWML_INIT_PERIOD_VALUE        255u
#define PWML_INIT_COMPARE_VALUE1      100u
#define PWML_INIT_COMPARE_VALUE2      63u
#define PWML_INIT_INTERRUPTS_MODE     (uint8)(((uint8)(0u << PWML_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                  (uint8)((uint8)(0u << PWML_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                  (uint8)((uint8)(0u << PWML_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                  (uint8)((uint8)(0u << PWML_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define PWML_DEFAULT_COMPARE2_MODE    (uint8)((uint8)1u << PWML_CTRL_CMPMODE2_SHIFT)
#define PWML_DEFAULT_COMPARE1_MODE    (uint8)((uint8)1u << PWML_CTRL_CMPMODE1_SHIFT)
#define PWML_INIT_DEAD_TIME           1u


/********************************
*         Registers
******************************** */

#if (PWML_UsingFixedFunction)
   #define PWML_PERIOD_LSB          (*(reg16 *) PWML_PWMHW__PER0)
   #define PWML_PERIOD_LSB_PTR      ( (reg16 *) PWML_PWMHW__PER0)
   #define PWML_COMPARE1_LSB        (*(reg16 *) PWML_PWMHW__CNT_CMP0)
   #define PWML_COMPARE1_LSB_PTR    ( (reg16 *) PWML_PWMHW__CNT_CMP0)
   #define PWML_COMPARE2_LSB        0x00u
   #define PWML_COMPARE2_LSB_PTR    0x00u
   #define PWML_COUNTER_LSB         (*(reg16 *) PWML_PWMHW__CNT_CMP0)
   #define PWML_COUNTER_LSB_PTR     ( (reg16 *) PWML_PWMHW__CNT_CMP0)
   #define PWML_CAPTURE_LSB         (*(reg16 *) PWML_PWMHW__CAP0)
   #define PWML_CAPTURE_LSB_PTR     ( (reg16 *) PWML_PWMHW__CAP0)
   #define PWML_RT1                 (*(reg8 *)  PWML_PWMHW__RT1)
   #define PWML_RT1_PTR             ( (reg8 *)  PWML_PWMHW__RT1)
      
#else
   #if (PWML_Resolution == 8u) /* 8bit - PWM */
	   
	   #if(PWML_PWMModeIsCenterAligned)
	       #define PWML_PERIOD_LSB      (*(reg8 *) PWML_PWMUDB_sP8_pwmdp_u0__D1_REG)
	       #define PWML_PERIOD_LSB_PTR   ((reg8 *) PWML_PWMUDB_sP8_pwmdp_u0__D1_REG)
	   #else
	       #define PWML_PERIOD_LSB      (*(reg8 *) PWML_PWMUDB_sP8_pwmdp_u0__F0_REG)
	       #define PWML_PERIOD_LSB_PTR   ((reg8 *) PWML_PWMUDB_sP8_pwmdp_u0__F0_REG)
	   #endif /* (PWML_PWMModeIsCenterAligned) */
	   
	   #define PWML_COMPARE1_LSB    (*(reg8 *) PWML_PWMUDB_sP8_pwmdp_u0__D0_REG)
	   #define PWML_COMPARE1_LSB_PTR ((reg8 *) PWML_PWMUDB_sP8_pwmdp_u0__D0_REG)
	   #define PWML_COMPARE2_LSB    (*(reg8 *) PWML_PWMUDB_sP8_pwmdp_u0__D1_REG)
	   #define PWML_COMPARE2_LSB_PTR ((reg8 *) PWML_PWMUDB_sP8_pwmdp_u0__D1_REG)
	   #define PWML_COUNTERCAP_LSB   (*(reg8 *) PWML_PWMUDB_sP8_pwmdp_u0__A1_REG)
	   #define PWML_COUNTERCAP_LSB_PTR ((reg8 *) PWML_PWMUDB_sP8_pwmdp_u0__A1_REG)
	   #define PWML_COUNTER_LSB     (*(reg8 *) PWML_PWMUDB_sP8_pwmdp_u0__A0_REG)
	   #define PWML_COUNTER_LSB_PTR  ((reg8 *) PWML_PWMUDB_sP8_pwmdp_u0__A0_REG)
	   #define PWML_CAPTURE_LSB     (*(reg8 *) PWML_PWMUDB_sP8_pwmdp_u0__F1_REG)
	   #define PWML_CAPTURE_LSB_PTR  ((reg8 *) PWML_PWMUDB_sP8_pwmdp_u0__F1_REG)
   
   #else
   		#if(CY_PSOC3) /* 8-bit address space */	
			#if(PWML_PWMModeIsCenterAligned)
		       #define PWML_PERIOD_LSB      (*(reg16 *) PWML_PWMUDB_sP8_pwmdp_u0__D1_REG)
		       #define PWML_PERIOD_LSB_PTR   ((reg16 *) PWML_PWMUDB_sP8_pwmdp_u0__D1_REG)
		    #else
		       #define PWML_PERIOD_LSB      (*(reg16 *) PWML_PWMUDB_sP8_pwmdp_u0__F0_REG)
		       #define PWML_PERIOD_LSB_PTR   ((reg16 *) PWML_PWMUDB_sP8_pwmdp_u0__F0_REG)
		    #endif /* (PWML_PWMModeIsCenterAligned) */
		   
		    #define PWML_COMPARE1_LSB    (*(reg16 *) PWML_PWMUDB_sP8_pwmdp_u0__D0_REG)
		    #define PWML_COMPARE1_LSB_PTR ((reg16 *) PWML_PWMUDB_sP8_pwmdp_u0__D0_REG)
		    #define PWML_COMPARE2_LSB    (*(reg16 *) PWML_PWMUDB_sP8_pwmdp_u0__D1_REG)
		    #define PWML_COMPARE2_LSB_PTR ((reg16 *) PWML_PWMUDB_sP8_pwmdp_u0__D1_REG)
		    #define PWML_COUNTERCAP_LSB   (*(reg16 *) PWML_PWMUDB_sP8_pwmdp_u0__A1_REG)
		    #define PWML_COUNTERCAP_LSB_PTR ((reg16 *) PWML_PWMUDB_sP8_pwmdp_u0__A1_REG)
		    #define PWML_COUNTER_LSB     (*(reg16 *) PWML_PWMUDB_sP8_pwmdp_u0__A0_REG)
		    #define PWML_COUNTER_LSB_PTR  ((reg16 *) PWML_PWMUDB_sP8_pwmdp_u0__A0_REG)
		    #define PWML_CAPTURE_LSB     (*(reg16 *) PWML_PWMUDB_sP8_pwmdp_u0__F1_REG)
		    #define PWML_CAPTURE_LSB_PTR  ((reg16 *) PWML_PWMUDB_sP8_pwmdp_u0__F1_REG)
		#else
			#if(PWML_PWMModeIsCenterAligned)
		       #define PWML_PERIOD_LSB      (*(reg16 *) PWML_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
		       #define PWML_PERIOD_LSB_PTR   ((reg16 *) PWML_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
		    #else
		       #define PWML_PERIOD_LSB      (*(reg16 *) PWML_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG)
		       #define PWML_PERIOD_LSB_PTR   ((reg16 *) PWML_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG)
		    #endif /* (PWML_PWMModeIsCenterAligned) */
		   
		    #define PWML_COMPARE1_LSB    (*(reg16 *) PWML_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG)
		    #define PWML_COMPARE1_LSB_PTR ((reg16 *) PWML_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG)
		    #define PWML_COMPARE2_LSB    (*(reg16 *) PWML_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
		    #define PWML_COMPARE2_LSB_PTR ((reg16 *) PWML_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
		    #define PWML_COUNTERCAP_LSB   (*(reg16 *) PWML_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG)
		    #define PWML_COUNTERCAP_LSB_PTR ((reg16 *) PWML_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG)
		    #define PWML_COUNTER_LSB     (*(reg16 *) PWML_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG)
		    #define PWML_COUNTER_LSB_PTR  ((reg16 *) PWML_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG)
		    #define PWML_CAPTURE_LSB     (*(reg16 *) PWML_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG)
		    #define PWML_CAPTURE_LSB_PTR  ((reg16 *) PWML_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG)
		#endif
		
	   #define PWML_AUX_CONTROLDP1    (*(reg8 *) PWML_PWMUDB_sP8_pwmdp_u1__DP_AUX_CTL_REG)
       #define PWML_AUX_CONTROLDP1_PTR  ((reg8 *) PWML_PWMUDB_sP8_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (PWML_Resolution == 8) */
   
   #define PWML_AUX_CONTROLDP0      (*(reg8 *) PWML_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG)
   #define PWML_AUX_CONTROLDP0_PTR  ((reg8 *) PWML_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (PWML_UsingFixedFunction) */
   
#if(PWML_KillModeMinTime )
    #define PWML_KILLMODEMINTIME      (*(reg8 *) PWML_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define PWML_KILLMODEMINTIME_PTR   ((reg8 *) PWML_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (PWML_KillModeMinTime ) */

#if(PWML_DeadBandMode == PWML__B_PWM__DBM_256_CLOCKS)
    #define PWML_DEADBAND_COUNT      (*(reg8 *) PWML_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define PWML_DEADBAND_COUNT_PTR  ((reg8 *) PWML_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define PWML_DEADBAND_LSB_PTR    ((reg8 *) PWML_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define PWML_DEADBAND_LSB        (*(reg8 *) PWML_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(PWML_DeadBandMode == PWML__B_PWM__DBM_2_4_CLOCKS)
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (PWML_UsingFixedFunction)
        #define PWML_DEADBAND_COUNT        (*(reg8 *) PWML_PWMHW__CFG0) 
        #define PWML_DEADBAND_COUNT_PTR     ((reg8 *) PWML_PWMHW__CFG0)
        #define PWML_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << PWML_DEADBAND_COUNT_SHIFT)
        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define PWML_DEADBAND_COUNT_SHIFT   0x06u  
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define PWML_DEADBAND_COUNT        (*(reg8 *) PWML_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define PWML_DEADBAND_COUNT_PTR     ((reg8 *) PWML_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define PWML_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << PWML_DEADBAND_COUNT_SHIFT) 
        /* As defined by the verilog implementation of the Control Register */
        #define PWML_DEADBAND_COUNT_SHIFT   0x00u 
    #endif /* (PWML_UsingFixedFunction) */
#endif /* (PWML_DeadBandMode == PWML__B_PWM__DBM_256_CLOCKS) */



#if (PWML_UsingFixedFunction)
    #define PWML_STATUS                (*(reg8 *) PWML_PWMHW__SR0)
    #define PWML_STATUS_PTR            ((reg8 *) PWML_PWMHW__SR0)
    #define PWML_STATUS_MASK           (*(reg8 *) PWML_PWMHW__SR0)
    #define PWML_STATUS_MASK_PTR       ((reg8 *) PWML_PWMHW__SR0)
    #define PWML_CONTROL               (*(reg8 *) PWML_PWMHW__CFG0)
    #define PWML_CONTROL_PTR           ((reg8 *) PWML_PWMHW__CFG0)    
    #define PWML_CONTROL2              (*(reg8 *) PWML_PWMHW__CFG1)    
    #define PWML_CONTROL3              (*(reg8 *) PWML_PWMHW__CFG2)
    #define PWML_GLOBAL_ENABLE         (*(reg8 *) PWML_PWMHW__PM_ACT_CFG)
    #define PWML_GLOBAL_ENABLE_PTR       ( (reg8 *) PWML_PWMHW__PM_ACT_CFG)
    #define PWML_GLOBAL_STBY_ENABLE      (*(reg8 *) PWML_PWMHW__PM_STBY_CFG)
    #define PWML_GLOBAL_STBY_ENABLE_PTR  ( (reg8 *) PWML_PWMHW__PM_STBY_CFG)
  
  
    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define PWML_BLOCK_EN_MASK          PWML_PWMHW__PM_ACT_MSK
    #define PWML_BLOCK_STBY_EN_MASK     PWML_PWMHW__PM_STBY_MSK 
    /* Control Register definitions */
    #define PWML_CTRL_ENABLE_SHIFT      0x00u
    
    #define PWML_CTRL_CMPMODE1_SHIFT    0x04u  /* As defined by Register map as MODE_CFG bits in CFG2*/
    
    #define PWML_CTRL_DEAD_TIME_SHIFT   0x06u   /* As defined by Register map */

    /* Fixed Function Block Only CFG register bit definitions */
    #define PWML_CFG0_MODE              0x02u   /*  Set to compare mode */
    
    /* #define PWML_CFG0_ENABLE            0x01u */  /* Enable the block to run */
    #define PWML_CFG0_DB                0x20u   /* As defined by Register map as DB bit in CFG0 */

    /* Control Register Bit Masks */
    #define PWML_CTRL_ENABLE            (uint8)((uint8)0x01u << PWML_CTRL_ENABLE_SHIFT)
    #define PWML_CTRL_RESET             (uint8)((uint8)0x01u << PWML_CTRL_RESET_SHIFT)
    #define PWML_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << PWML_CTRL_CMPMODE2_SHIFT)
    #define PWML_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << PWML_CTRL_CMPMODE1_SHIFT)
    
    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define PWML_CTRL2_IRQ_SEL_SHIFT    0x00u       
    #define PWML_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << PWML_CTRL2_IRQ_SEL_SHIFT)  
    
    /* Status Register Bit Locations */
    #define PWML_STATUS_TC_SHIFT            0x07u   /* As defined by Register map as TC in SR0 */
    #define PWML_STATUS_CMP1_SHIFT          0x06u   /* As defined by the Register map as CAP_CMP in SR0 */
    
    /* Status Register Interrupt Enable Bit Locations */
    #define PWML_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)    
    #define PWML_STATUS_TC_INT_EN_MASK_SHIFT            (PWML_STATUS_TC_SHIFT - 4u)
    #define PWML_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)  
    #define PWML_STATUS_CMP1_INT_EN_MASK_SHIFT          (PWML_STATUS_CMP1_SHIFT - 4u)
    
    /* Status Register Bit Masks */
    #define PWML_STATUS_TC              (uint8)((uint8)0x01u << PWML_STATUS_TC_SHIFT)
    #define PWML_STATUS_CMP1            (uint8)((uint8)0x01u << PWML_STATUS_CMP1_SHIFT)
    
    /* Status Register Interrupt Bit Masks */
    #define PWML_STATUS_TC_INT_EN_MASK              (uint8)((uint8)PWML_STATUS_TC >> 4u)
    #define PWML_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)PWML_STATUS_CMP1 >> 4u)
    
    /*RT1 Synch Constants */
    #define PWML_RT1_SHIFT             0x04u
    #define PWML_RT1_MASK              (uint8)((uint8)0x03u << PWML_RT1_SHIFT)/* Sync TC and CMP bit masks */
    #define PWML_SYNC                  (uint8)((uint8)0x03u << PWML_RT1_SHIFT)
    #define PWML_SYNCDSI_SHIFT         0x00u
    #define PWML_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << PWML_SYNCDSI_SHIFT) /* Sync all DSI inputs */
    #define PWML_SYNCDSI_EN            (uint8)((uint8)0x0Fu << PWML_SYNCDSI_SHIFT) /* Sync all DSI inputs */
    

#else
    #define PWML_STATUS                (*(reg8 *) PWML_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define PWML_STATUS_PTR            ((reg8 *) PWML_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define PWML_STATUS_MASK           (*(reg8 *) PWML_PWMUDB_genblk8_stsreg__MASK_REG)
    #define PWML_STATUS_MASK_PTR       ((reg8 *) PWML_PWMUDB_genblk8_stsreg__MASK_REG)
    #define PWML_STATUS_AUX_CTRL       (*(reg8 *) PWML_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define PWML_CONTROL               (*(reg8 *) PWML_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define PWML_CONTROL_PTR           ((reg8 *) PWML_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    
    
    /***********************************
    *          Constants
    ***********************************/

    /* Control Register definitions */
    #define PWML_CTRL_ENABLE_SHIFT      0x07u
    #define PWML_CTRL_RESET_SHIFT       0x06u
    #define PWML_CTRL_CMPMODE2_SHIFT    0x03u
    #define PWML_CTRL_CMPMODE1_SHIFT    0x00u
    #define PWML_CTRL_DEAD_TIME_SHIFT   0x00u   /* No Shift Needed for UDB block */
    /* Control Register Bit Masks */
    #define PWML_CTRL_ENABLE            (uint8)((uint8)0x01u << PWML_CTRL_ENABLE_SHIFT)
    #define PWML_CTRL_RESET             (uint8)((uint8)0x01u << PWML_CTRL_RESET_SHIFT)
    #define PWML_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << PWML_CTRL_CMPMODE2_SHIFT)
    #define PWML_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << PWML_CTRL_CMPMODE1_SHIFT) 
    
    /* Status Register Bit Locations */
    #define PWML_STATUS_KILL_SHIFT          0x05u
    #define PWML_STATUS_FIFONEMPTY_SHIFT    0x04u
    #define PWML_STATUS_FIFOFULL_SHIFT      0x03u  
    #define PWML_STATUS_TC_SHIFT            0x02u
    #define PWML_STATUS_CMP2_SHIFT          0x01u
    #define PWML_STATUS_CMP1_SHIFT          0x00u
    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define PWML_STATUS_KILL_INT_EN_MASK_SHIFT          PWML_STATUS_KILL_SHIFT          
    #define PWML_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    PWML_STATUS_FIFONEMPTY_SHIFT    
    #define PWML_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      PWML_STATUS_FIFOFULL_SHIFT        
    #define PWML_STATUS_TC_INT_EN_MASK_SHIFT            PWML_STATUS_TC_SHIFT            
    #define PWML_STATUS_CMP2_INT_EN_MASK_SHIFT          PWML_STATUS_CMP2_SHIFT          
    #define PWML_STATUS_CMP1_INT_EN_MASK_SHIFT          PWML_STATUS_CMP1_SHIFT   
    /* Status Register Bit Masks */
    #define PWML_STATUS_KILL            (uint8)((uint8)0x00u << PWML_STATUS_KILL_SHIFT )
    #define PWML_STATUS_FIFOFULL        (uint8)((uint8)0x01u << PWML_STATUS_FIFOFULL_SHIFT)
    #define PWML_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << PWML_STATUS_FIFONEMPTY_SHIFT)
    #define PWML_STATUS_TC              (uint8)((uint8)0x01u << PWML_STATUS_TC_SHIFT)
    #define PWML_STATUS_CMP2            (uint8)((uint8)0x01u << PWML_STATUS_CMP2_SHIFT) 
    #define PWML_STATUS_CMP1            (uint8)((uint8)0x01u << PWML_STATUS_CMP1_SHIFT)
    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define PWML_STATUS_KILL_INT_EN_MASK            PWML_STATUS_KILL
    #define PWML_STATUS_FIFOFULL_INT_EN_MASK        PWML_STATUS_FIFOFULL
    #define PWML_STATUS_FIFONEMPTY_INT_EN_MASK      PWML_STATUS_FIFONEMPTY
    #define PWML_STATUS_TC_INT_EN_MASK              PWML_STATUS_TC
    #define PWML_STATUS_CMP2_INT_EN_MASK            PWML_STATUS_CMP2
    #define PWML_STATUS_CMP1_INT_EN_MASK            PWML_STATUS_CMP1
                                                          
    /* Datapath Auxillary Control Register definitions */
    #define PWML_AUX_CTRL_FIFO0_CLR     0x01u
    #define PWML_AUX_CTRL_FIFO1_CLR     0x02u
    #define PWML_AUX_CTRL_FIFO0_LVL     0x04u
    #define PWML_AUX_CTRL_FIFO1_LVL     0x08u
    #define PWML_STATUS_ACTL_INT_EN_MASK  0x10u /* As defined for the ACTL Register */
#endif /* PWML_UsingFixedFunction */

#endif  /* CY_PWM_PWML_H */


/* [] END OF FILE */
