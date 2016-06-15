/*******************************************************************************
* File Name: PWM_MOT_PM.c
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

#include "PWM_MOT.h"

static PWM_MOT_backupStruct PWM_MOT_backup;


/*******************************************************************************
* Function Name: PWM_MOT_SaveConfig
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
*  PWM_MOT_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_MOT_SaveConfig(void) 
{

    #if(!PWM_MOT_UsingFixedFunction)
        #if(!PWM_MOT_PWMModeIsCenterAligned)
            PWM_MOT_backup.PWMPeriod = PWM_MOT_ReadPeriod();
        #endif /* (!PWM_MOT_PWMModeIsCenterAligned) */
        PWM_MOT_backup.PWMUdb = PWM_MOT_ReadCounter();
        #if (PWM_MOT_UseStatus)
            PWM_MOT_backup.InterruptMaskValue = PWM_MOT_STATUS_MASK;
        #endif /* (PWM_MOT_UseStatus) */

        #if(PWM_MOT_DeadBandMode == PWM_MOT__B_PWM__DBM_256_CLOCKS || \
            PWM_MOT_DeadBandMode == PWM_MOT__B_PWM__DBM_2_4_CLOCKS)
            PWM_MOT_backup.PWMdeadBandValue = PWM_MOT_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_MOT_KillModeMinTime)
             PWM_MOT_backup.PWMKillCounterPeriod = PWM_MOT_ReadKillTime();
        #endif /* (PWM_MOT_KillModeMinTime) */

        #if(PWM_MOT_UseControl)
            PWM_MOT_backup.PWMControlRegister = PWM_MOT_ReadControlRegister();
        #endif /* (PWM_MOT_UseControl) */
    #endif  /* (!PWM_MOT_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_MOT_RestoreConfig
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
*  PWM_MOT_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_MOT_RestoreConfig(void) 
{
        #if(!PWM_MOT_UsingFixedFunction)
            #if(!PWM_MOT_PWMModeIsCenterAligned)
                PWM_MOT_WritePeriod(PWM_MOT_backup.PWMPeriod);
            #endif /* (!PWM_MOT_PWMModeIsCenterAligned) */

            PWM_MOT_WriteCounter(PWM_MOT_backup.PWMUdb);

            #if (PWM_MOT_UseStatus)
                PWM_MOT_STATUS_MASK = PWM_MOT_backup.InterruptMaskValue;
            #endif /* (PWM_MOT_UseStatus) */

            #if(PWM_MOT_DeadBandMode == PWM_MOT__B_PWM__DBM_256_CLOCKS || \
                PWM_MOT_DeadBandMode == PWM_MOT__B_PWM__DBM_2_4_CLOCKS)
                PWM_MOT_WriteDeadTime(PWM_MOT_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_MOT_KillModeMinTime)
                PWM_MOT_WriteKillTime(PWM_MOT_backup.PWMKillCounterPeriod);
            #endif /* (PWM_MOT_KillModeMinTime) */

            #if(PWM_MOT_UseControl)
                PWM_MOT_WriteControlRegister(PWM_MOT_backup.PWMControlRegister);
            #endif /* (PWM_MOT_UseControl) */
        #endif  /* (!PWM_MOT_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_MOT_Sleep
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
*  PWM_MOT_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_MOT_Sleep(void) 
{
    #if(PWM_MOT_UseControl)
        if(PWM_MOT_CTRL_ENABLE == (PWM_MOT_CONTROL & PWM_MOT_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_MOT_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_MOT_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_MOT_UseControl) */

    /* Stop component */
    PWM_MOT_Stop();

    /* Save registers configuration */
    PWM_MOT_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_MOT_Wakeup
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
*  PWM_MOT_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_MOT_Wakeup(void) 
{
     /* Restore registers values */
    PWM_MOT_RestoreConfig();

    if(PWM_MOT_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_MOT_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
