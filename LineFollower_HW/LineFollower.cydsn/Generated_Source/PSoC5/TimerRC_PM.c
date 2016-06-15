/*******************************************************************************
* File Name: TimerRC_PM.c
* Version 2.50
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "TimerRC.h"
static TimerRC_backupStruct TimerRC_backup;


/*******************************************************************************
* Function Name: TimerRC_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  TimerRC_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void TimerRC_SaveConfig(void) 
{
    #if (!TimerRC_UsingFixedFunction)
        /* Backup the UDB non-rentention registers for CY_UDB_V0 */
        #if (CY_UDB_V0)
            TimerRC_backup.TimerUdb = TimerRC_ReadCounter();
            TimerRC_backup.TimerPeriod = TimerRC_ReadPeriod();
            TimerRC_backup.InterruptMaskValue = TimerRC_STATUS_MASK;
            #if (TimerRC_UsingHWCaptureCounter)
                TimerRC_backup.TimerCaptureCounter = TimerRC_ReadCaptureCount();
            #endif /* Backup the UDB non-rentention register capture counter for CY_UDB_V0 */
        #endif /* Backup the UDB non-rentention registers for CY_UDB_V0 */

        #if (CY_UDB_V1)
            TimerRC_backup.TimerUdb = TimerRC_ReadCounter();
            TimerRC_backup.InterruptMaskValue = TimerRC_STATUS_MASK;
            #if (TimerRC_UsingHWCaptureCounter)
                TimerRC_backup.TimerCaptureCounter = TimerRC_ReadCaptureCount();
            #endif /* Back Up capture counter register  */
        #endif /* Backup non retention registers, interrupt mask and capture counter for CY_UDB_V1 */

        #if(!TimerRC_ControlRegRemoved)
            TimerRC_backup.TimerControlRegister = TimerRC_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: TimerRC_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  TimerRC_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void TimerRC_RestoreConfig(void) 
{   
    #if (!TimerRC_UsingFixedFunction)
        /* Restore the UDB non-rentention registers for CY_UDB_V0 */
        #if (CY_UDB_V0)
            /* Interrupt State Backup for Critical Region*/
            uint8 TimerRC_interruptState;

            TimerRC_WriteCounter(TimerRC_backup.TimerUdb);
            TimerRC_WritePeriod(TimerRC_backup.TimerPeriod);
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            TimerRC_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            TimerRC_STATUS_AUX_CTRL |= TimerRC_STATUS_ACTL_INT_EN_MASK;
            /* Exit Critical Region*/
            CyExitCriticalSection(TimerRC_interruptState);
            TimerRC_STATUS_MASK =TimerRC_backup.InterruptMaskValue;
            #if (TimerRC_UsingHWCaptureCounter)
                TimerRC_SetCaptureCount(TimerRC_backup.TimerCaptureCounter);
            #endif /* Restore the UDB non-rentention register capture counter for CY_UDB_V0 */
        #endif /* Restore the UDB non-rentention registers for CY_UDB_V0 */

        #if (CY_UDB_V1)
            TimerRC_WriteCounter(TimerRC_backup.TimerUdb);
            TimerRC_STATUS_MASK =TimerRC_backup.InterruptMaskValue;
            #if (TimerRC_UsingHWCaptureCounter)
                TimerRC_SetCaptureCount(TimerRC_backup.TimerCaptureCounter);
            #endif /* Restore Capture counter register*/
        #endif /* Restore up non retention registers, interrupt mask and capture counter for CY_UDB_V1 */

        #if(!TimerRC_ControlRegRemoved)
            TimerRC_WriteControlRegister(TimerRC_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: TimerRC_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  TimerRC_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void TimerRC_Sleep(void) 
{
    #if(!TimerRC_ControlRegRemoved)
        /* Save Counter's enable state */
        if(TimerRC_CTRL_ENABLE == (TimerRC_CONTROL & TimerRC_CTRL_ENABLE))
        {
            /* Timer is enabled */
            TimerRC_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            TimerRC_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    TimerRC_Stop();
    TimerRC_SaveConfig();
}


/*******************************************************************************
* Function Name: TimerRC_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  TimerRC_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void TimerRC_Wakeup(void) 
{
    TimerRC_RestoreConfig();
    #if(!TimerRC_ControlRegRemoved)
        if(TimerRC_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                TimerRC_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
