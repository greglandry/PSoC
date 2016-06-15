/*******************************************************************************
* File Name: PWMR.h  
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

#if !defined(CY_PWM_PWMR_H)
#define CY_PWM_PWMR_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 PWMR_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define PWMR_Resolution 8u
#define PWMR_UsingFixedFunction 0u
#define PWMR_DeadBandMode 0u
#define PWMR_KillModeMinTime 0u
#define PWMR_KillMode 0u
#define PWMR_PWMMode 0u
#define PWMR_PWMModeIsCenterAligned 0u
#define PWMR_DeadBandUsed 0u
#define PWMR_DeadBand2_4 0u

#if !defined(PWMR_PWMUDB_genblk8_stsreg__REMOVED)
    #define PWMR_UseStatus 1u
#else
    #define PWMR_UseStatus 0u
#endif /* !defined(PWMR_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(PWMR_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define PWMR_UseControl 1u
#else
    #define PWMR_UseControl 0u
#endif /* !defined(PWMR_PWMUDB_genblk1_ctrlreg__REMOVED) */
#define PWMR_UseOneCompareMode 1u
#define PWMR_MinimumKillTime 1u
#define PWMR_EnableMode 0u

#define PWMR_CompareMode1SW 0u
#define PWMR_CompareMode2SW 0u

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_0 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define PWMR__B_PWM__DISABLED 0
#define PWMR__B_PWM__ASYNCHRONOUS 1
#define PWMR__B_PWM__SINGLECYCLE 2
#define PWMR__B_PWM__LATCHED 3
#define PWMR__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define PWMR__B_PWM__DBMDISABLED 0
#define PWMR__B_PWM__DBM_2_4_CLOCKS 1
#define PWMR__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define PWMR__B_PWM__ONE_OUTPUT 0
#define PWMR__B_PWM__TWO_OUTPUTS 1
#define PWMR__B_PWM__DUAL_EDGE 2
#define PWMR__B_PWM__CENTER_ALIGN 3
#define PWMR__B_PWM__DITHER 5
#define PWMR__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define PWMR__B_PWM__LESS_THAN 1
#define PWMR__B_PWM__LESS_THAN_OR_EQUAL 2
#define PWMR__B_PWM__GREATER_THAN 3
#define PWMR__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define PWMR__B_PWM__EQUAL 0
#define PWMR__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{
    
    uint8 PWMEnableState;
       
    #if(!PWMR_UsingFixedFunction)
        uint8 PWMUdb;               /* PWM Current Counter value  */
        #if(!PWMR_PWMModeIsCenterAligned)
            uint8 PWMPeriod;
        #endif /* (!PWMR_PWMModeIsCenterAligned) */
        #if (PWMR_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (PWMR_UseStatus) */
        
        /* Backup for Deadband parameters */
        #if(PWMR_DeadBandMode == PWMR__B_PWM__DBM_256_CLOCKS || \
            PWMR_DeadBandMode == PWMR__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */
        
        /* Backup Kill Mode Counter*/
        #if(PWMR_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (PWMR_KillModeMinTime) */
       
        /* Backup control register */
        #if(PWMR_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (PWMR_UseControl) */
        
    #endif /* (!PWMR_UsingFixedFunction) */
   
}PWMR_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/
 
void    PWMR_Start(void) ;
void    PWMR_Stop(void) ;

#if (PWMR_UseStatus || PWMR_UsingFixedFunction)
    void  PWMR_SetInterruptMode(uint8 interruptMode) ;
    uint8 PWMR_ReadStatusRegister(void) ;
#endif /* (PWMR_UseStatus || PWMR_UsingFixedFunction) */

#define PWMR_GetInterruptSource() PWMR_ReadStatusRegister()

#if (PWMR_UseControl)
    uint8 PWMR_ReadControlRegister(void) ; 
    void  PWMR_WriteControlRegister(uint8 control) ;
#endif /* (PWMR_UseControl) */

#if (PWMR_UseOneCompareMode)
   #if (PWMR_CompareMode1SW)
       void    PWMR_SetCompareMode(uint8 comparemode) ;
   #endif /* (PWMR_CompareMode1SW) */
#else
    #if (PWMR_CompareMode1SW)
        void    PWMR_SetCompareMode1(uint8 comparemode) ;
    #endif /* (PWMR_CompareMode1SW) */
    #if (PWMR_CompareMode2SW)
        void    PWMR_SetCompareMode2(uint8 comparemode) ;
    #endif /* (PWMR_CompareMode2SW) */
#endif /* (PWMR_UseOneCompareMode) */

#if (!PWMR_UsingFixedFunction)
    uint8   PWMR_ReadCounter(void) ;
    uint8 PWMR_ReadCapture(void) ;
    
	#if (PWMR_UseStatus)
	        void PWMR_ClearFIFO(void) ;
	#endif /* (PWMR_UseStatus) */

    void    PWMR_WriteCounter(uint8 counter) ;
#endif /* (!PWMR_UsingFixedFunction) */

void    PWMR_WritePeriod(uint8 period) ;
uint8 PWMR_ReadPeriod(void) ;

#if (PWMR_UseOneCompareMode)
    void    PWMR_WriteCompare(uint8 compare) ;
    uint8 PWMR_ReadCompare(void) ; 
#else
    void    PWMR_WriteCompare1(uint8 compare) ;
    uint8 PWMR_ReadCompare1(void) ; 
    void    PWMR_WriteCompare2(uint8 compare) ;
    uint8 PWMR_ReadCompare2(void) ; 
#endif /* (PWMR_UseOneCompareMode) */


#if (PWMR_DeadBandUsed)
    void    PWMR_WriteDeadTime(uint8 deadtime) ;
    uint8   PWMR_ReadDeadTime(void) ;
#endif /* (PWMR_DeadBandUsed) */

#if ( PWMR_KillModeMinTime)
    void PWMR_WriteKillTime(uint8 killtime) ;
    uint8 PWMR_ReadKillTime(void) ; 
#endif /* ( PWMR_KillModeMinTime) */

void PWMR_Init(void) ;
void PWMR_Enable(void) ;
void PWMR_Sleep(void) ;
void PWMR_Wakeup(void) ;
void PWMR_SaveConfig(void) ;
void PWMR_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define PWMR_INIT_PERIOD_VALUE        255u
#define PWMR_INIT_COMPARE_VALUE1      100u
#define PWMR_INIT_COMPARE_VALUE2      63u
#define PWMR_INIT_INTERRUPTS_MODE     (uint8)(((uint8)(0u << PWMR_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                  (uint8)((uint8)(0u << PWMR_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                  (uint8)((uint8)(0u << PWMR_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                  (uint8)((uint8)(0u << PWMR_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define PWMR_DEFAULT_COMPARE2_MODE    (uint8)((uint8)1u << PWMR_CTRL_CMPMODE2_SHIFT)
#define PWMR_DEFAULT_COMPARE1_MODE    (uint8)((uint8)1u << PWMR_CTRL_CMPMODE1_SHIFT)
#define PWMR_INIT_DEAD_TIME           1u


/********************************
*         Registers
******************************** */

#if (PWMR_UsingFixedFunction)
   #define PWMR_PERIOD_LSB          (*(reg16 *) PWMR_PWMHW__PER0)
   #define PWMR_PERIOD_LSB_PTR      ( (reg16 *) PWMR_PWMHW__PER0)
   #define PWMR_COMPARE1_LSB        (*(reg16 *) PWMR_PWMHW__CNT_CMP0)
   #define PWMR_COMPARE1_LSB_PTR    ( (reg16 *) PWMR_PWMHW__CNT_CMP0)
   #define PWMR_COMPARE2_LSB        0x00u
   #define PWMR_COMPARE2_LSB_PTR    0x00u
   #define PWMR_COUNTER_LSB         (*(reg16 *) PWMR_PWMHW__CNT_CMP0)
   #define PWMR_COUNTER_LSB_PTR     ( (reg16 *) PWMR_PWMHW__CNT_CMP0)
   #define PWMR_CAPTURE_LSB         (*(reg16 *) PWMR_PWMHW__CAP0)
   #define PWMR_CAPTURE_LSB_PTR     ( (reg16 *) PWMR_PWMHW__CAP0)
   #define PWMR_RT1                 (*(reg8 *)  PWMR_PWMHW__RT1)
   #define PWMR_RT1_PTR             ( (reg8 *)  PWMR_PWMHW__RT1)
      
#else
   #if (PWMR_Resolution == 8u) /* 8bit - PWM */
	   
	   #if(PWMR_PWMModeIsCenterAligned)
	       #define PWMR_PERIOD_LSB      (*(reg8 *) PWMR_PWMUDB_sP8_pwmdp_u0__D1_REG)
	       #define PWMR_PERIOD_LSB_PTR   ((reg8 *) PWMR_PWMUDB_sP8_pwmdp_u0__D1_REG)
	   #else
	       #define PWMR_PERIOD_LSB      (*(reg8 *) PWMR_PWMUDB_sP8_pwmdp_u0__F0_REG)
	       #define PWMR_PERIOD_LSB_PTR   ((reg8 *) PWMR_PWMUDB_sP8_pwmdp_u0__F0_REG)
	   #endif /* (PWMR_PWMModeIsCenterAligned) */
	   
	   #define PWMR_COMPARE1_LSB    (*(reg8 *) PWMR_PWMUDB_sP8_pwmdp_u0__D0_REG)
	   #define PWMR_COMPARE1_LSB_PTR ((reg8 *) PWMR_PWMUDB_sP8_pwmdp_u0__D0_REG)
	   #define PWMR_COMPARE2_LSB    (*(reg8 *) PWMR_PWMUDB_sP8_pwmdp_u0__D1_REG)
	   #define PWMR_COMPARE2_LSB_PTR ((reg8 *) PWMR_PWMUDB_sP8_pwmdp_u0__D1_REG)
	   #define PWMR_COUNTERCAP_LSB   (*(reg8 *) PWMR_PWMUDB_sP8_pwmdp_u0__A1_REG)
	   #define PWMR_COUNTERCAP_LSB_PTR ((reg8 *) PWMR_PWMUDB_sP8_pwmdp_u0__A1_REG)
	   #define PWMR_COUNTER_LSB     (*(reg8 *) PWMR_PWMUDB_sP8_pwmdp_u0__A0_REG)
	   #define PWMR_COUNTER_LSB_PTR  ((reg8 *) PWMR_PWMUDB_sP8_pwmdp_u0__A0_REG)
	   #define PWMR_CAPTURE_LSB     (*(reg8 *) PWMR_PWMUDB_sP8_pwmdp_u0__F1_REG)
	   #define PWMR_CAPTURE_LSB_PTR  ((reg8 *) PWMR_PWMUDB_sP8_pwmdp_u0__F1_REG)
   
   #else
   		#if(CY_PSOC3) /* 8-bit address space */	
			#if(PWMR_PWMModeIsCenterAligned)
		       #define PWMR_PERIOD_LSB      (*(reg16 *) PWMR_PWMUDB_sP8_pwmdp_u0__D1_REG)
		       #define PWMR_PERIOD_LSB_PTR   ((reg16 *) PWMR_PWMUDB_sP8_pwmdp_u0__D1_REG)
		    #else
		       #define PWMR_PERIOD_LSB      (*(reg16 *) PWMR_PWMUDB_sP8_pwmdp_u0__F0_REG)
		       #define PWMR_PERIOD_LSB_PTR   ((reg16 *) PWMR_PWMUDB_sP8_pwmdp_u0__F0_REG)
		    #endif /* (PWMR_PWMModeIsCenterAligned) */
		   
		    #define PWMR_COMPARE1_LSB    (*(reg16 *) PWMR_PWMUDB_sP8_pwmdp_u0__D0_REG)
		    #define PWMR_COMPARE1_LSB_PTR ((reg16 *) PWMR_PWMUDB_sP8_pwmdp_u0__D0_REG)
		    #define PWMR_COMPARE2_LSB    (*(reg16 *) PWMR_PWMUDB_sP8_pwmdp_u0__D1_REG)
		    #define PWMR_COMPARE2_LSB_PTR ((reg16 *) PWMR_PWMUDB_sP8_pwmdp_u0__D1_REG)
		    #define PWMR_COUNTERCAP_LSB   (*(reg16 *) PWMR_PWMUDB_sP8_pwmdp_u0__A1_REG)
		    #define PWMR_COUNTERCAP_LSB_PTR ((reg16 *) PWMR_PWMUDB_sP8_pwmdp_u0__A1_REG)
		    #define PWMR_COUNTER_LSB     (*(reg16 *) PWMR_PWMUDB_sP8_pwmdp_u0__A0_REG)
		    #define PWMR_COUNTER_LSB_PTR  ((reg16 *) PWMR_PWMUDB_sP8_pwmdp_u0__A0_REG)
		    #define PWMR_CAPTURE_LSB     (*(reg16 *) PWMR_PWMUDB_sP8_pwmdp_u0__F1_REG)
		    #define PWMR_CAPTURE_LSB_PTR  ((reg16 *) PWMR_PWMUDB_sP8_pwmdp_u0__F1_REG)
		#else
			#if(PWMR_PWMModeIsCenterAligned)
		       #define PWMR_PERIOD_LSB      (*(reg16 *) PWMR_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
		       #define PWMR_PERIOD_LSB_PTR   ((reg16 *) PWMR_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
		    #else
		       #define PWMR_PERIOD_LSB      (*(reg16 *) PWMR_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG)
		       #define PWMR_PERIOD_LSB_PTR   ((reg16 *) PWMR_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG)
		    #endif /* (PWMR_PWMModeIsCenterAligned) */
		   
		    #define PWMR_COMPARE1_LSB    (*(reg16 *) PWMR_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG)
		    #define PWMR_COMPARE1_LSB_PTR ((reg16 *) PWMR_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG)
		    #define PWMR_COMPARE2_LSB    (*(reg16 *) PWMR_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
		    #define PWMR_COMPARE2_LSB_PTR ((reg16 *) PWMR_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
		    #define PWMR_COUNTERCAP_LSB   (*(reg16 *) PWMR_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG)
		    #define PWMR_COUNTERCAP_LSB_PTR ((reg16 *) PWMR_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG)
		    #define PWMR_COUNTER_LSB     (*(reg16 *) PWMR_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG)
		    #define PWMR_COUNTER_LSB_PTR  ((reg16 *) PWMR_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG)
		    #define PWMR_CAPTURE_LSB     (*(reg16 *) PWMR_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG)
		    #define PWMR_CAPTURE_LSB_PTR  ((reg16 *) PWMR_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG)
		#endif
		
	   #define PWMR_AUX_CONTROLDP1    (*(reg8 *) PWMR_PWMUDB_sP8_pwmdp_u1__DP_AUX_CTL_REG)
       #define PWMR_AUX_CONTROLDP1_PTR  ((reg8 *) PWMR_PWMUDB_sP8_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (PWMR_Resolution == 8) */
   
   #define PWMR_AUX_CONTROLDP0      (*(reg8 *) PWMR_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG)
   #define PWMR_AUX_CONTROLDP0_PTR  ((reg8 *) PWMR_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (PWMR_UsingFixedFunction) */
   
#if(PWMR_KillModeMinTime )
    #define PWMR_KILLMODEMINTIME      (*(reg8 *) PWMR_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define PWMR_KILLMODEMINTIME_PTR   ((reg8 *) PWMR_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (PWMR_KillModeMinTime ) */

#if(PWMR_DeadBandMode == PWMR__B_PWM__DBM_256_CLOCKS)
    #define PWMR_DEADBAND_COUNT      (*(reg8 *) PWMR_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define PWMR_DEADBAND_COUNT_PTR  ((reg8 *) PWMR_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define PWMR_DEADBAND_LSB_PTR    ((reg8 *) PWMR_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define PWMR_DEADBAND_LSB        (*(reg8 *) PWMR_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(PWMR_DeadBandMode == PWMR__B_PWM__DBM_2_4_CLOCKS)
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (PWMR_UsingFixedFunction)
        #define PWMR_DEADBAND_COUNT        (*(reg8 *) PWMR_PWMHW__CFG0) 
        #define PWMR_DEADBAND_COUNT_PTR     ((reg8 *) PWMR_PWMHW__CFG0)
        #define PWMR_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << PWMR_DEADBAND_COUNT_SHIFT)
        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define PWMR_DEADBAND_COUNT_SHIFT   0x06u  
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define PWMR_DEADBAND_COUNT        (*(reg8 *) PWMR_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define PWMR_DEADBAND_COUNT_PTR     ((reg8 *) PWMR_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define PWMR_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << PWMR_DEADBAND_COUNT_SHIFT) 
        /* As defined by the verilog implementation of the Control Register */
        #define PWMR_DEADBAND_COUNT_SHIFT   0x00u 
    #endif /* (PWMR_UsingFixedFunction) */
#endif /* (PWMR_DeadBandMode == PWMR__B_PWM__DBM_256_CLOCKS) */



#if (PWMR_UsingFixedFunction)
    #define PWMR_STATUS                (*(reg8 *) PWMR_PWMHW__SR0)
    #define PWMR_STATUS_PTR            ((reg8 *) PWMR_PWMHW__SR0)
    #define PWMR_STATUS_MASK           (*(reg8 *) PWMR_PWMHW__SR0)
    #define PWMR_STATUS_MASK_PTR       ((reg8 *) PWMR_PWMHW__SR0)
    #define PWMR_CONTROL               (*(reg8 *) PWMR_PWMHW__CFG0)
    #define PWMR_CONTROL_PTR           ((reg8 *) PWMR_PWMHW__CFG0)    
    #define PWMR_CONTROL2              (*(reg8 *) PWMR_PWMHW__CFG1)    
    #define PWMR_CONTROL3              (*(reg8 *) PWMR_PWMHW__CFG2)
    #define PWMR_GLOBAL_ENABLE         (*(reg8 *) PWMR_PWMHW__PM_ACT_CFG)
    #define PWMR_GLOBAL_ENABLE_PTR       ( (reg8 *) PWMR_PWMHW__PM_ACT_CFG)
    #define PWMR_GLOBAL_STBY_ENABLE      (*(reg8 *) PWMR_PWMHW__PM_STBY_CFG)
    #define PWMR_GLOBAL_STBY_ENABLE_PTR  ( (reg8 *) PWMR_PWMHW__PM_STBY_CFG)
  
  
    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define PWMR_BLOCK_EN_MASK          PWMR_PWMHW__PM_ACT_MSK
    #define PWMR_BLOCK_STBY_EN_MASK     PWMR_PWMHW__PM_STBY_MSK 
    /* Control Register definitions */
    #define PWMR_CTRL_ENABLE_SHIFT      0x00u
    
    #define PWMR_CTRL_CMPMODE1_SHIFT    0x04u  /* As defined by Register map as MODE_CFG bits in CFG2*/
    
    #define PWMR_CTRL_DEAD_TIME_SHIFT   0x06u   /* As defined by Register map */

    /* Fixed Function Block Only CFG register bit definitions */
    #define PWMR_CFG0_MODE              0x02u   /*  Set to compare mode */
    
    /* #define PWMR_CFG0_ENABLE            0x01u */  /* Enable the block to run */
    #define PWMR_CFG0_DB                0x20u   /* As defined by Register map as DB bit in CFG0 */

    /* Control Register Bit Masks */
    #define PWMR_CTRL_ENABLE            (uint8)((uint8)0x01u << PWMR_CTRL_ENABLE_SHIFT)
    #define PWMR_CTRL_RESET             (uint8)((uint8)0x01u << PWMR_CTRL_RESET_SHIFT)
    #define PWMR_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << PWMR_CTRL_CMPMODE2_SHIFT)
    #define PWMR_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << PWMR_CTRL_CMPMODE1_SHIFT)
    
    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define PWMR_CTRL2_IRQ_SEL_SHIFT    0x00u       
    #define PWMR_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << PWMR_CTRL2_IRQ_SEL_SHIFT)  
    
    /* Status Register Bit Locations */
    #define PWMR_STATUS_TC_SHIFT            0x07u   /* As defined by Register map as TC in SR0 */
    #define PWMR_STATUS_CMP1_SHIFT          0x06u   /* As defined by the Register map as CAP_CMP in SR0 */
    
    /* Status Register Interrupt Enable Bit Locations */
    #define PWMR_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)    
    #define PWMR_STATUS_TC_INT_EN_MASK_SHIFT            (PWMR_STATUS_TC_SHIFT - 4u)
    #define PWMR_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)  
    #define PWMR_STATUS_CMP1_INT_EN_MASK_SHIFT          (PWMR_STATUS_CMP1_SHIFT - 4u)
    
    /* Status Register Bit Masks */
    #define PWMR_STATUS_TC              (uint8)((uint8)0x01u << PWMR_STATUS_TC_SHIFT)
    #define PWMR_STATUS_CMP1            (uint8)((uint8)0x01u << PWMR_STATUS_CMP1_SHIFT)
    
    /* Status Register Interrupt Bit Masks */
    #define PWMR_STATUS_TC_INT_EN_MASK              (uint8)((uint8)PWMR_STATUS_TC >> 4u)
    #define PWMR_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)PWMR_STATUS_CMP1 >> 4u)
    
    /*RT1 Synch Constants */
    #define PWMR_RT1_SHIFT             0x04u
    #define PWMR_RT1_MASK              (uint8)((uint8)0x03u << PWMR_RT1_SHIFT)/* Sync TC and CMP bit masks */
    #define PWMR_SYNC                  (uint8)((uint8)0x03u << PWMR_RT1_SHIFT)
    #define PWMR_SYNCDSI_SHIFT         0x00u
    #define PWMR_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << PWMR_SYNCDSI_SHIFT) /* Sync all DSI inputs */
    #define PWMR_SYNCDSI_EN            (uint8)((uint8)0x0Fu << PWMR_SYNCDSI_SHIFT) /* Sync all DSI inputs */
    

#else
    #define PWMR_STATUS                (*(reg8 *) PWMR_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define PWMR_STATUS_PTR            ((reg8 *) PWMR_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define PWMR_STATUS_MASK           (*(reg8 *) PWMR_PWMUDB_genblk8_stsreg__MASK_REG)
    #define PWMR_STATUS_MASK_PTR       ((reg8 *) PWMR_PWMUDB_genblk8_stsreg__MASK_REG)
    #define PWMR_STATUS_AUX_CTRL       (*(reg8 *) PWMR_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define PWMR_CONTROL               (*(reg8 *) PWMR_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define PWMR_CONTROL_PTR           ((reg8 *) PWMR_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    
    
    /***********************************
    *          Constants
    ***********************************/

    /* Control Register definitions */
    #define PWMR_CTRL_ENABLE_SHIFT      0x07u
    #define PWMR_CTRL_RESET_SHIFT       0x06u
    #define PWMR_CTRL_CMPMODE2_SHIFT    0x03u
    #define PWMR_CTRL_CMPMODE1_SHIFT    0x00u
    #define PWMR_CTRL_DEAD_TIME_SHIFT   0x00u   /* No Shift Needed for UDB block */
    /* Control Register Bit Masks */
    #define PWMR_CTRL_ENABLE            (uint8)((uint8)0x01u << PWMR_CTRL_ENABLE_SHIFT)
    #define PWMR_CTRL_RESET             (uint8)((uint8)0x01u << PWMR_CTRL_RESET_SHIFT)
    #define PWMR_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << PWMR_CTRL_CMPMODE2_SHIFT)
    #define PWMR_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << PWMR_CTRL_CMPMODE1_SHIFT) 
    
    /* Status Register Bit Locations */
    #define PWMR_STATUS_KILL_SHIFT          0x05u
    #define PWMR_STATUS_FIFONEMPTY_SHIFT    0x04u
    #define PWMR_STATUS_FIFOFULL_SHIFT      0x03u  
    #define PWMR_STATUS_TC_SHIFT            0x02u
    #define PWMR_STATUS_CMP2_SHIFT          0x01u
    #define PWMR_STATUS_CMP1_SHIFT          0x00u
    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define PWMR_STATUS_KILL_INT_EN_MASK_SHIFT          PWMR_STATUS_KILL_SHIFT          
    #define PWMR_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    PWMR_STATUS_FIFONEMPTY_SHIFT    
    #define PWMR_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      PWMR_STATUS_FIFOFULL_SHIFT        
    #define PWMR_STATUS_TC_INT_EN_MASK_SHIFT            PWMR_STATUS_TC_SHIFT            
    #define PWMR_STATUS_CMP2_INT_EN_MASK_SHIFT          PWMR_STATUS_CMP2_SHIFT          
    #define PWMR_STATUS_CMP1_INT_EN_MASK_SHIFT          PWMR_STATUS_CMP1_SHIFT   
    /* Status Register Bit Masks */
    #define PWMR_STATUS_KILL            (uint8)((uint8)0x00u << PWMR_STATUS_KILL_SHIFT )
    #define PWMR_STATUS_FIFOFULL        (uint8)((uint8)0x01u << PWMR_STATUS_FIFOFULL_SHIFT)
    #define PWMR_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << PWMR_STATUS_FIFONEMPTY_SHIFT)
    #define PWMR_STATUS_TC              (uint8)((uint8)0x01u << PWMR_STATUS_TC_SHIFT)
    #define PWMR_STATUS_CMP2            (uint8)((uint8)0x01u << PWMR_STATUS_CMP2_SHIFT) 
    #define PWMR_STATUS_CMP1            (uint8)((uint8)0x01u << PWMR_STATUS_CMP1_SHIFT)
    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define PWMR_STATUS_KILL_INT_EN_MASK            PWMR_STATUS_KILL
    #define PWMR_STATUS_FIFOFULL_INT_EN_MASK        PWMR_STATUS_FIFOFULL
    #define PWMR_STATUS_FIFONEMPTY_INT_EN_MASK      PWMR_STATUS_FIFONEMPTY
    #define PWMR_STATUS_TC_INT_EN_MASK              PWMR_STATUS_TC
    #define PWMR_STATUS_CMP2_INT_EN_MASK            PWMR_STATUS_CMP2
    #define PWMR_STATUS_CMP1_INT_EN_MASK            PWMR_STATUS_CMP1
                                                          
    /* Datapath Auxillary Control Register definitions */
    #define PWMR_AUX_CTRL_FIFO0_CLR     0x01u
    #define PWMR_AUX_CTRL_FIFO1_CLR     0x02u
    #define PWMR_AUX_CTRL_FIFO0_LVL     0x04u
    #define PWMR_AUX_CTRL_FIFO1_LVL     0x08u
    #define PWMR_STATUS_ACTL_INT_EN_MASK  0x10u /* As defined for the ACTL Register */
#endif /* PWMR_UsingFixedFunction */

#endif  /* CY_PWM_PWMR_H */


/* [] END OF FILE */
