/*******************************************************************************
* File Name: TimerC_PM.c
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

#include "TimerC.h"
static TimerC_backupStruct TimerC_backup;


/*******************************************************************************
* Function Name: TimerC_SaveConfig
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
*  TimerC_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void TimerC_SaveConfig(void) 
{
    #if (!TimerC_UsingFixedFunction)
        /* Backup the UDB non-rentention registers for CY_UDB_V0 */
        #if (CY_UDB_V0)
            TimerC_backup.TimerUdb = TimerC_ReadCounter();
            TimerC_backup.TimerPeriod = TimerC_ReadPeriod();
            TimerC_backup.InterruptMaskValue = TimerC_STATUS_MASK;
            #if (TimerC_UsingHWCaptureCounter)
                TimerC_backup.TimerCaptureCounter = TimerC_ReadCaptureCount();
            #endif /* Backup the UDB non-rentention register capture counter for CY_UDB_V0 */
        #endif /* Backup the UDB non-rentention registers for CY_UDB_V0 */

        #if (CY_UDB_V1)
            TimerC_backup.TimerUdb = TimerC_ReadCounter();
            TimerC_backup.InterruptMaskValue = TimerC_STATUS_MASK;
            #if (TimerC_UsingHWCaptureCounter)
                TimerC_backup.TimerCaptureCounter = TimerC_ReadCaptureCount();
            #endif /* Back Up capture counter register  */
        #endif /* Backup non retention registers, interrupt mask and capture counter for CY_UDB_V1 */

        #if(!TimerC_ControlRegRemoved)
            TimerC_backup.TimerControlRegister = TimerC_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: TimerC_RestoreConfig
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
*  TimerC_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void TimerC_RestoreConfig(void) 
{   
    #if (!TimerC_UsingFixedFunction)
        /* Restore the UDB non-rentention registers for CY_UDB_V0 */
        #if (CY_UDB_V0)
            /* Interrupt State Backup for Critical Region*/
            uint8 TimerC_interruptState;

            TimerC_WriteCounter(TimerC_backup.TimerUdb);
            TimerC_WritePeriod(TimerC_backup.TimerPeriod);
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            TimerC_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            TimerC_STATUS_AUX_CTRL |= TimerC_STATUS_ACTL_INT_EN_MASK;
            /* Exit Critical Region*/
            CyExitCriticalSection(TimerC_interruptState);
            TimerC_STATUS_MASK =TimerC_backup.InterruptMaskValue;
            #if (TimerC_UsingHWCaptureCounter)
                TimerC_SetCaptureCount(TimerC_backup.TimerCaptureCounter);
            #endif /* Restore the UDB non-rentention register capture counter for CY_UDB_V0 */
        #endif /* Restore the UDB non-rentention registers for CY_UDB_V0 */

        #if (CY_UDB_V1)
            TimerC_WriteCounter(TimerC_backup.TimerUdb);
            TimerC_STATUS_MASK =TimerC_backup.InterruptMaskValue;
            #if (TimerC_UsingHWCaptureCounter)
                TimerC_SetCaptureCount(TimerC_backup.TimerCaptureCounter);
            #endif /* Restore Capture counter register*/
        #endif /* Restore up non retention registers, interrupt mask and capture counter for CY_UDB_V1 */

        #if(!TimerC_ControlRegRemoved)
            TimerC_WriteControlRegister(TimerC_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: TimerC_Sleep
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
*  TimerC_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void TimerC_Sleep(void) 
{
    #if(!TimerC_ControlRegRemoved)
        /* Save Counter's enable state */
        if(TimerC_CTRL_ENABLE == (TimerC_CONTROL & TimerC_CTRL_ENABLE))
        {
            /* Timer is enabled */
            TimerC_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            TimerC_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    TimerC_Stop();
    TimerC_SaveConfig();
}


/*******************************************************************************
* Function Name: TimerC_Wakeup
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
*  TimerC_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void TimerC_Wakeup(void) 
{
    TimerC_RestoreConfig();
    #if(!TimerC_ControlRegRemoved)
        if(TimerC_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                TimerC_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
