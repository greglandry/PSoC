/*******************************************************************************
* File Name: Comp3.c
* Version 2.0
*
* Description:
*  This file provides the power management source code APIs for the
*  Comparator.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Comp3.h"

static Comp3_backupStruct Comp3_backup;


/*******************************************************************************
* Function Name: Comp3_SaveConfig
********************************************************************************
*
* Summary:
*  Save the current user configuration
*
* Parameters:
*  void:
*
* Return:
*  void
*
*******************************************************************************/
void Comp3_SaveConfig(void) 
{
    /* Empty since all are system reset for retention flops */
}


/*******************************************************************************
* Function Name: Comp3_RestoreConfig
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
********************************************************************************/
void Comp3_RestoreConfig(void) 
{
    /* Empty since all are system reset for retention flops */    
}


/*******************************************************************************
* Function Name: Comp3_Sleep
********************************************************************************
*
* Summary:
*  Stop and Save the user configuration
*
* Parameters:
*  void:
*
* Return:
*  void
*
* Global variables:
*  Comp3_backup.enableState:  Is modified depending on the enable 
*   state of the block before entering sleep mode.
*
*******************************************************************************/
void Comp3_Sleep(void) 
{
    /* Save Comp's enable state */    
    if(Comp3_ACT_PWR_EN == (Comp3_PWRMGR & Comp3_ACT_PWR_EN))
    {
        /* Comp is enabled */
        Comp3_backup.enableState = 1u;
    }
    else
    {
        /* Comp is disabled */
        Comp3_backup.enableState = 0u;
    }    
    
    Comp3_Stop();
    Comp3_SaveConfig();
}


/*******************************************************************************
* Function Name: Comp3_Wakeup
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
*  Comp3_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Comp3_Wakeup(void) 
{
    Comp3_RestoreConfig();
    
    if(Comp3_backup.enableState == 1u)
    {
        /* Enable Comp's operation */
        Comp3_Enable();

    } /* Do nothing if Comp was disabled before */ 
}


/* [] END OF FILE */
