/*******************************************************************************
* File Name: PWML_PM.c
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
#include "PWML.h"

static PWML_backupStruct PWML_backup;


/*******************************************************************************
* Function Name: PWML_SaveConfig
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
*  PWML_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void PWML_SaveConfig(void) 
{
    
    #if(!PWML_UsingFixedFunction)
        #if(!PWML_PWMModeIsCenterAligned)
            PWML_backup.PWMPeriod = PWML_ReadPeriod();
        #endif /* (!PWML_PWMModeIsCenterAligned) */
        PWML_backup.PWMUdb = PWML_ReadCounter();
        #if (PWML_UseStatus)
            PWML_backup.InterruptMaskValue = PWML_STATUS_MASK;
        #endif /* (PWML_UseStatus) */
        
        #if(PWML_DeadBandMode == PWML__B_PWM__DBM_256_CLOCKS || \
            PWML_DeadBandMode == PWML__B_PWM__DBM_2_4_CLOCKS)
            PWML_backup.PWMdeadBandValue = PWML_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */
        
        #if(PWML_KillModeMinTime)
             PWML_backup.PWMKillCounterPeriod = PWML_ReadKillTime();
        #endif /* (PWML_KillModeMinTime) */
        
        #if(PWML_UseControl)
            PWML_backup.PWMControlRegister = PWML_ReadControlRegister();
        #endif /* (PWML_UseControl) */
    #endif  /* (!PWML_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWML_RestoreConfig
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
*  PWML_backup:  Variables of this global structure are used to  
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWML_RestoreConfig(void) 
{
        #if(!PWML_UsingFixedFunction)
            #if(!PWML_PWMModeIsCenterAligned)
                PWML_WritePeriod(PWML_backup.PWMPeriod);
            #endif /* (!PWML_PWMModeIsCenterAligned) */
            PWML_WriteCounter(PWML_backup.PWMUdb);
            #if (PWML_UseStatus)
                PWML_STATUS_MASK = PWML_backup.InterruptMaskValue;
            #endif /* (PWML_UseStatus) */
            
            #if(PWML_DeadBandMode == PWML__B_PWM__DBM_256_CLOCKS || \
                PWML_DeadBandMode == PWML__B_PWM__DBM_2_4_CLOCKS)
                PWML_WriteDeadTime(PWML_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */
            
            #if(PWML_KillModeMinTime)
                PWML_WriteKillTime(PWML_backup.PWMKillCounterPeriod);
            #endif /* (PWML_KillModeMinTime) */
            
            #if(PWML_UseControl)
                PWML_WriteControlRegister(PWML_backup.PWMControlRegister); 
            #endif /* (PWML_UseControl) */
        #endif  /* (!PWML_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWML_Sleep
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
*  PWML_backup.PWMEnableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWML_Sleep(void) 
{
    #if(PWML_UseControl)
        if(PWML_CTRL_ENABLE == (PWML_CONTROL & PWML_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWML_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWML_backup.PWMEnableState = 0u;
        }
    #endif /* (PWML_UseControl) */

    /* Stop component */
    PWML_Stop();
    
    /* Save registers configuration */
    PWML_SaveConfig();
}


/*******************************************************************************
* Function Name: PWML_Wakeup
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
*  PWML_backup.pwmEnable:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWML_Wakeup(void) 
{
     /* Restore registers values */
    PWML_RestoreConfig();
    
    if(PWML_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWML_Enable();
    } /* Do nothing if component's block was disabled before */
    
}


/* [] END OF FILE */
