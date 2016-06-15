/*******************************************************************************
* File Name: TimerLC_PM.c
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

#include "TimerLC.h"
static TimerLC_backupStruct TimerLC_backup;


/*******************************************************************************
* Function Name: TimerLC_SaveConfig
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
*  TimerLC_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void TimerLC_SaveConfig(void) 
{
    #if (!TimerLC_UsingFixedFunction)
        /* Backup the UDB non-rentention registers for CY_UDB_V0 */
        #if (CY_UDB_V0)
            TimerLC_backup.TimerUdb = TimerLC_ReadCounter();
            TimerLC_backup.TimerPeriod = TimerLC_ReadPeriod();
            TimerLC_backup.InterruptMaskValue = TimerLC_STATUS_MASK;
            #if (TimerLC_UsingHWCaptureCounter)
                TimerLC_backup.TimerCaptureCounter = TimerLC_ReadCaptureCount();
            #endif /* Backup the UDB non-rentention register capture counter for CY_UDB_V0 */
        #endif /* Backup the UDB non-rentention registers for CY_UDB_V0 */

        #if (CY_UDB_V1)
            TimerLC_backup.TimerUdb = TimerLC_ReadCounter();
            TimerLC_backup.InterruptMaskValue = TimerLC_STATUS_MASK;
            #if (TimerLC_UsingHWCaptureCounter)
                TimerLC_backup.TimerCaptureCounter = TimerLC_ReadCaptureCount();
            #endif /* Back Up capture counter register  */
        #endif /* Backup non retention registers, interrupt mask and capture counter for CY_UDB_V1 */

        #if(!TimerLC_ControlRegRemoved)
            TimerLC_backup.TimerControlRegister = TimerLC_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: TimerLC_RestoreConfig
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
*  TimerLC_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void TimerLC_RestoreConfig(void) 
{   
    #if (!TimerLC_UsingFixedFunction)
        /* Restore the UDB non-rentention registers for CY_UDB_V0 */
        #if (CY_UDB_V0)
            /* Interrupt State Backup for Critical Region*/
            uint8 TimerLC_interruptState;

            TimerLC_WriteCounter(TimerLC_backup.TimerUdb);
            TimerLC_WritePeriod(TimerLC_backup.TimerPeriod);
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            TimerLC_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            TimerLC_STATUS_AUX_CTRL |= TimerLC_STATUS_ACTL_INT_EN_MASK;
            /* Exit Critical Region*/
            CyExitCriticalSection(TimerLC_interruptState);
            TimerLC_STATUS_MASK =TimerLC_backup.InterruptMaskValue;
            #if (TimerLC_UsingHWCaptureCounter)
                TimerLC_SetCaptureCount(TimerLC_backup.TimerCaptureCounter);
            #endif /* Restore the UDB non-rentention register capture counter for CY_UDB_V0 */
        #endif /* Restore the UDB non-rentention registers for CY_UDB_V0 */

        #if (CY_UDB_V1)
            TimerLC_WriteCounter(TimerLC_backup.TimerUdb);
            TimerLC_STATUS_MASK =TimerLC_backup.InterruptMaskValue;
            #if (TimerLC_UsingHWCaptureCounter)
                TimerLC_SetCaptureCount(TimerLC_backup.TimerCaptureCounter);
            #endif /* Restore Capture counter register*/
        #endif /* Restore up non retention registers, interrupt mask and capture counter for CY_UDB_V1 */

        #if(!TimerLC_ControlRegRemoved)
            TimerLC_WriteControlRegister(TimerLC_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: TimerLC_Sleep
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
*  TimerLC_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void TimerLC_Sleep(void) 
{
    #if(!TimerLC_ControlRegRemoved)
        /* Save Counter's enable state */
        if(TimerLC_CTRL_ENABLE == (TimerLC_CONTROL & TimerLC_CTRL_ENABLE))
        {
            /* Timer is enabled */
            TimerLC_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            TimerLC_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    TimerLC_Stop();
    TimerLC_SaveConfig();
}


/*******************************************************************************
* Function Name: TimerLC_Wakeup
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
*  TimerLC_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void TimerLC_Wakeup(void) 
{
    TimerLC_RestoreConfig();
    #if(!TimerLC_ControlRegRemoved)
        if(TimerLC_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                TimerLC_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
