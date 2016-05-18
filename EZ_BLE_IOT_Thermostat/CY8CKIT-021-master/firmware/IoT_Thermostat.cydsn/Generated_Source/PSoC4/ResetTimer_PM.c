/*******************************************************************************
* File Name: ResetTimer_PM.c
* Version 2.10
*
* Description:
*  This file contains the setup, control, and status commands to support
*  the component operations in the low power mode.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ResetTimer.h"

static ResetTimer_BACKUP_STRUCT ResetTimer_backup;


/*******************************************************************************
* Function Name: ResetTimer_SaveConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to save here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ResetTimer_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: ResetTimer_Sleep
********************************************************************************
*
* Summary:
*  Stops the component operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ResetTimer_Sleep(void)
{
    if(0u != (ResetTimer_BLOCK_CONTROL_REG & ResetTimer_MASK))
    {
        ResetTimer_backup.enableState = 1u;
    }
    else
    {
        ResetTimer_backup.enableState = 0u;
    }

    ResetTimer_Stop();
    ResetTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: ResetTimer_RestoreConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to restore here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ResetTimer_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: ResetTimer_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and restores the enable state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ResetTimer_Wakeup(void)
{
    ResetTimer_RestoreConfig();

    if(0u != ResetTimer_backup.enableState)
    {
        ResetTimer_Enable();
    }
}


/* [] END OF FILE */
