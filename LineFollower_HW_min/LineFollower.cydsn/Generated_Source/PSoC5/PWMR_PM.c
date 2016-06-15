/*******************************************************************************
* File Name: PWMR_PM.c
* Version 3.0
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/
#include "cytypes.h"
#include "PWMR.h"

static PWMR_backupStruct PWMR_backup;


/*******************************************************************************
* Function Name: PWMR_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*  
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  PWMR_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void PWMR_SaveConfig(void) 
{
    
    #if(!PWMR_UsingFixedFunction)
        #if(!PWMR_PWMModeIsCenterAligned)
            PWMR_backup.PWMPeriod = PWMR_ReadPeriod();
        #endif /* (!PWMR_PWMModeIsCenterAligned) */
        PWMR_backup.PWMUdb = PWMR_ReadCounter();
        #if (PWMR_UseStatus)
            PWMR_backup.InterruptMaskValue = PWMR_STATUS_MASK;
        #endif /* (PWMR_UseStatus) */
        
        #if(PWMR_DeadBandMode == PWMR__B_PWM__DBM_256_CLOCKS || \
            PWMR_DeadBandMode == PWMR__B_PWM__DBM_2_4_CLOCKS)
            PWMR_backup.PWMdeadBandValue = PWMR_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */
        
        #if(PWMR_KillModeMinTime)
             PWMR_backup.PWMKillCounterPeriod = PWMR_ReadKillTime();
        #endif /* (PWMR_KillModeMinTime) */
        
        #if(PWMR_UseControl)
            PWMR_backup.PWMControlRegister = PWMR_ReadControlRegister();
        #endif /* (PWMR_UseControl) */
    #endif  /* (!PWMR_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWMR_RestoreConfig
********************************************************************************
* 
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  PWMR_backup:  Variables of this global structure are used to  
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWMR_RestoreConfig(void) 
{
        #if(!PWMR_UsingFixedFunction)
            #if(!PWMR_PWMModeIsCenterAligned)
                PWMR_WritePeriod(PWMR_backup.PWMPeriod);
            #endif /* (!PWMR_PWMModeIsCenterAligned) */
            PWMR_WriteCounter(PWMR_backup.PWMUdb);
            #if (PWMR_UseStatus)
                PWMR_STATUS_MASK = PWMR_backup.InterruptMaskValue;
            #endif /* (PWMR_UseStatus) */
            
            #if(PWMR_DeadBandMode == PWMR__B_PWM__DBM_256_CLOCKS || \
                PWMR_DeadBandMode == PWMR__B_PWM__DBM_2_4_CLOCKS)
                PWMR_WriteDeadTime(PWMR_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */
            
            #if(PWMR_KillModeMinTime)
                PWMR_WriteKillTime(PWMR_backup.PWMKillCounterPeriod);
            #endif /* (PWMR_KillModeMinTime) */
            
            #if(PWMR_UseControl)
                PWMR_WriteControlRegister(PWMR_backup.PWMControlRegister); 
            #endif /* (PWMR_UseControl) */
        #endif  /* (!PWMR_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWMR_Sleep
********************************************************************************
* 
* Summary:
*  Disables block's operation and saves the user configuration. Should be called 
*  just prior to entering sleep.
*  
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  PWMR_backup.PWMEnableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWMR_Sleep(void) 
{
    #if(PWMR_UseControl)
        if(PWMR_CTRL_ENABLE == (PWMR_CONTROL & PWMR_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWMR_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWMR_backup.PWMEnableState = 0u;
        }
    #endif /* (PWMR_UseControl) */

    /* Stop component */
    PWMR_Stop();
    
    /* Save registers configuration */
    PWMR_SaveConfig();
}


/*******************************************************************************
* Function Name: PWMR_Wakeup
********************************************************************************
* 
* Summary:
*  Restores and enables the user configuration. Should be called just after 
*  awaking from sleep.
*  
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  PWMR_backup.pwmEnable:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWMR_Wakeup(void) 
{
     /* Restore registers values */
    PWMR_RestoreConfig();
    
    if(PWMR_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWMR_Enable();
    } /* Do nothing if component's block was disabled before */
    
}


/* [] END OF FILE */
