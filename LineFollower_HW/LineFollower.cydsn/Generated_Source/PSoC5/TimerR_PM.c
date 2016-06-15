/*******************************************************************************
* File Name: TimerR_PM.c
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

#include "TimerR.h"
static TimerR_backupStruct TimerR_backup;


/*******************************************************************************
* Function Name: TimerR_SaveConfig
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
*  TimerR_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void TimerR_SaveConfig(void) 
{
    #if (!TimerR_UsingFixedFunction)
        /* Backup the UDB non-rentention registers for CY_UDB_V0 */
        #if (CY_UDB_V0)
            TimerR_backup.TimerUdb = TimerR_ReadCounter();
            TimerR_backup.TimerPeriod = TimerR_ReadPeriod();
            TimerR_backup.InterruptMaskValue = TimerR_STATUS_MASK;
            #if (TimerR_UsingHWCaptureCounter)
                TimerR_backup.TimerCaptureCounter = TimerR_ReadCaptureCount();
            #endif /* Backup the UDB non-rentention register capture counter for CY_UDB_V0 */
        #endif /* Backup the UDB non-rentention registers for CY_UDB_V0 */

        #if (CY_UDB_V1)
            TimerR_backup.TimerUdb = TimerR_ReadCounter();
            TimerR_backup.InterruptMaskValue = TimerR_STATUS_MASK;
            #if (TimerR_UsingHWCaptureCounter)
                TimerR_backup.TimerCaptureCounter = TimerR_ReadCaptureCount();
            #endif /* Back Up capture counter register  */
        #endif /* Backup non retention registers, interrupt mask and capture counter for CY_UDB_V1 */

        #if(!TimerR_ControlRegRemoved)
            TimerR_backup.TimerControlRegister = TimerR_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: TimerR_RestoreConfig
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
*  TimerR_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void TimerR_RestoreConfig(void) 
{   
    #if (!TimerR_UsingFixedFunction)
        /* Restore the UDB non-rentention registers for CY_UDB_V0 */
        #if (CY_UDB_V0)
            /* Interrupt State Backup for Critical Region*/
            uint8 TimerR_interruptState;

            TimerR_WriteCounter(TimerR_backup.TimerUdb);
            TimerR_WritePeriod(TimerR_backup.TimerPeriod);
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            TimerR_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            TimerR_STATUS_AUX_CTRL |= TimerR_STATUS_ACTL_INT_EN_MASK;
            /* Exit Critical Region*/
            CyExitCriticalSection(TimerR_interruptState);
            TimerR_STATUS_MASK =TimerR_backup.InterruptMaskValue;
            #if (TimerR_UsingHWCaptureCounter)
                TimerR_SetCaptureCount(TimerR_backup.TimerCaptureCounter);
            #endif /* Restore the UDB non-rentention register capture counter for CY_UDB_V0 */
        #endif /* Restore the UDB non-rentention registers for CY_UDB_V0 */

        #if (CY_UDB_V1)
            TimerR_WriteCounter(TimerR_backup.TimerUdb);
            TimerR_STATUS_MASK =TimerR_backup.InterruptMaskValue;
            #if (TimerR_UsingHWCaptureCounter)
                TimerR_SetCaptureCount(TimerR_backup.TimerCaptureCounter);
            #endif /* Restore Capture counter register*/
        #endif /* Restore up non retention registers, interrupt mask and capture counter for CY_UDB_V1 */

        #if(!TimerR_ControlRegRemoved)
            TimerR_WriteControlRegister(TimerR_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: TimerR_Sleep
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
*  TimerR_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void TimerR_Sleep(void) 
{
    #if(!TimerR_ControlRegRemoved)
        /* Save Counter's enable state */
        if(TimerR_CTRL_ENABLE == (TimerR_CONTROL & TimerR_CTRL_ENABLE))
        {
            /* Timer is enabled */
            TimerR_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            TimerR_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    TimerR_Stop();
    TimerR_SaveConfig();
}


/*******************************************************************************
* Function Name: TimerR_Wakeup
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
*  TimerR_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void TimerR_Wakeup(void) 
{
    TimerR_RestoreConfig();
    #if(!TimerR_ControlRegRemoved)
        if(TimerR_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                TimerR_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
