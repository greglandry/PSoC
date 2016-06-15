/*******************************************************************************
* File Name: TimerL_PM.c
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

#include "TimerL.h"
static TimerL_backupStruct TimerL_backup;


/*******************************************************************************
* Function Name: TimerL_SaveConfig
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
*  TimerL_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void TimerL_SaveConfig(void) 
{
    #if (!TimerL_UsingFixedFunction)
        /* Backup the UDB non-rentention registers for CY_UDB_V0 */
        #if (CY_UDB_V0)
            TimerL_backup.TimerUdb = TimerL_ReadCounter();
            TimerL_backup.TimerPeriod = TimerL_ReadPeriod();
            TimerL_backup.InterruptMaskValue = TimerL_STATUS_MASK;
            #if (TimerL_UsingHWCaptureCounter)
                TimerL_backup.TimerCaptureCounter = TimerL_ReadCaptureCount();
            #endif /* Backup the UDB non-rentention register capture counter for CY_UDB_V0 */
        #endif /* Backup the UDB non-rentention registers for CY_UDB_V0 */

        #if (CY_UDB_V1)
            TimerL_backup.TimerUdb = TimerL_ReadCounter();
            TimerL_backup.InterruptMaskValue = TimerL_STATUS_MASK;
            #if (TimerL_UsingHWCaptureCounter)
                TimerL_backup.TimerCaptureCounter = TimerL_ReadCaptureCount();
            #endif /* Back Up capture counter register  */
        #endif /* Backup non retention registers, interrupt mask and capture counter for CY_UDB_V1 */

        #if(!TimerL_ControlRegRemoved)
            TimerL_backup.TimerControlRegister = TimerL_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: TimerL_RestoreConfig
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
*  TimerL_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void TimerL_RestoreConfig(void) 
{   
    #if (!TimerL_UsingFixedFunction)
        /* Restore the UDB non-rentention registers for CY_UDB_V0 */
        #if (CY_UDB_V0)
            /* Interrupt State Backup for Critical Region*/
            uint8 TimerL_interruptState;

            TimerL_WriteCounter(TimerL_backup.TimerUdb);
            TimerL_WritePeriod(TimerL_backup.TimerPeriod);
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            TimerL_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            TimerL_STATUS_AUX_CTRL |= TimerL_STATUS_ACTL_INT_EN_MASK;
            /* Exit Critical Region*/
            CyExitCriticalSection(TimerL_interruptState);
            TimerL_STATUS_MASK =TimerL_backup.InterruptMaskValue;
            #if (TimerL_UsingHWCaptureCounter)
                TimerL_SetCaptureCount(TimerL_backup.TimerCaptureCounter);
            #endif /* Restore the UDB non-rentention register capture counter for CY_UDB_V0 */
        #endif /* Restore the UDB non-rentention registers for CY_UDB_V0 */

        #if (CY_UDB_V1)
            TimerL_WriteCounter(TimerL_backup.TimerUdb);
            TimerL_STATUS_MASK =TimerL_backup.InterruptMaskValue;
            #if (TimerL_UsingHWCaptureCounter)
                TimerL_SetCaptureCount(TimerL_backup.TimerCaptureCounter);
            #endif /* Restore Capture counter register*/
        #endif /* Restore up non retention registers, interrupt mask and capture counter for CY_UDB_V1 */

        #if(!TimerL_ControlRegRemoved)
            TimerL_WriteControlRegister(TimerL_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: TimerL_Sleep
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
*  TimerL_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void TimerL_Sleep(void) 
{
    #if(!TimerL_ControlRegRemoved)
        /* Save Counter's enable state */
        if(TimerL_CTRL_ENABLE == (TimerL_CONTROL & TimerL_CTRL_ENABLE))
        {
            /* Timer is enabled */
            TimerL_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            TimerL_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    TimerL_Stop();
    TimerL_SaveConfig();
}


/*******************************************************************************
* Function Name: TimerL_Wakeup
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
*  TimerL_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void TimerL_Wakeup(void) 
{
    TimerL_RestoreConfig();
    #if(!TimerL_ControlRegRemoved)
        if(TimerL_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                TimerL_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
