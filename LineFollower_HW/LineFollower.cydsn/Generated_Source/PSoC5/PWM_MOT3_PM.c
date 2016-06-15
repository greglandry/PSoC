/*******************************************************************************
* File Name: PWM_MOT3_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PWM_MOT3.h"

static PWM_MOT3_backupStruct PWM_MOT3_backup;


/*******************************************************************************
* Function Name: PWM_MOT3_SaveConfig
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
*  PWM_MOT3_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_MOT3_SaveConfig(void) 
{

    #if(!PWM_MOT3_UsingFixedFunction)
        #if(!PWM_MOT3_PWMModeIsCenterAligned)
            PWM_MOT3_backup.PWMPeriod = PWM_MOT3_ReadPeriod();
        #endif /* (!PWM_MOT3_PWMModeIsCenterAligned) */
        PWM_MOT3_backup.PWMUdb = PWM_MOT3_ReadCounter();
        #if (PWM_MOT3_UseStatus)
            PWM_MOT3_backup.InterruptMaskValue = PWM_MOT3_STATUS_MASK;
        #endif /* (PWM_MOT3_UseStatus) */

        #if(PWM_MOT3_DeadBandMode == PWM_MOT3__B_PWM__DBM_256_CLOCKS || \
            PWM_MOT3_DeadBandMode == PWM_MOT3__B_PWM__DBM_2_4_CLOCKS)
            PWM_MOT3_backup.PWMdeadBandValue = PWM_MOT3_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_MOT3_KillModeMinTime)
             PWM_MOT3_backup.PWMKillCounterPeriod = PWM_MOT3_ReadKillTime();
        #endif /* (PWM_MOT3_KillModeMinTime) */

        #if(PWM_MOT3_UseControl)
            PWM_MOT3_backup.PWMControlRegister = PWM_MOT3_ReadControlRegister();
        #endif /* (PWM_MOT3_UseControl) */
    #endif  /* (!PWM_MOT3_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_MOT3_RestoreConfig
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
*  PWM_MOT3_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_MOT3_RestoreConfig(void) 
{
        #if(!PWM_MOT3_UsingFixedFunction)
            #if(!PWM_MOT3_PWMModeIsCenterAligned)
                PWM_MOT3_WritePeriod(PWM_MOT3_backup.PWMPeriod);
            #endif /* (!PWM_MOT3_PWMModeIsCenterAligned) */

            PWM_MOT3_WriteCounter(PWM_MOT3_backup.PWMUdb);

            #if (PWM_MOT3_UseStatus)
                PWM_MOT3_STATUS_MASK = PWM_MOT3_backup.InterruptMaskValue;
            #endif /* (PWM_MOT3_UseStatus) */

            #if(PWM_MOT3_DeadBandMode == PWM_MOT3__B_PWM__DBM_256_CLOCKS || \
                PWM_MOT3_DeadBandMode == PWM_MOT3__B_PWM__DBM_2_4_CLOCKS)
                PWM_MOT3_WriteDeadTime(PWM_MOT3_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_MOT3_KillModeMinTime)
                PWM_MOT3_WriteKillTime(PWM_MOT3_backup.PWMKillCounterPeriod);
            #endif /* (PWM_MOT3_KillModeMinTime) */

            #if(PWM_MOT3_UseControl)
                PWM_MOT3_WriteControlRegister(PWM_MOT3_backup.PWMControlRegister);
            #endif /* (PWM_MOT3_UseControl) */
        #endif  /* (!PWM_MOT3_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_MOT3_Sleep
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
*  PWM_MOT3_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_MOT3_Sleep(void) 
{
    #if(PWM_MOT3_UseControl)
        if(PWM_MOT3_CTRL_ENABLE == (PWM_MOT3_CONTROL & PWM_MOT3_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_MOT3_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_MOT3_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_MOT3_UseControl) */

    /* Stop component */
    PWM_MOT3_Stop();

    /* Save registers configuration */
    PWM_MOT3_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_MOT3_Wakeup
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
*  PWM_MOT3_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_MOT3_Wakeup(void) 
{
     /* Restore registers values */
    PWM_MOT3_RestoreConfig();

    if(PWM_MOT3_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_MOT3_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
