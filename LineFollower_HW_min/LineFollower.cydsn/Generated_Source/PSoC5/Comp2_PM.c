/*******************************************************************************
* File Name: Comp2.c
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

#include "Comp2.h"

static Comp2_backupStruct Comp2_backup;


/*******************************************************************************
* Function Name: Comp2_SaveConfig
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
void Comp2_SaveConfig(void) 
{
    /* Empty since all are system reset for retention flops */
}


/*******************************************************************************
* Function Name: Comp2_RestoreConfig
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
void Comp2_RestoreConfig(void) 
{
    /* Empty since all are system reset for retention flops */    
}


/*******************************************************************************
* Function Name: Comp2_Sleep
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
*  Comp2_backup.enableState:  Is modified depending on the enable 
*   state of the block before entering sleep mode.
*
*******************************************************************************/
void Comp2_Sleep(void) 
{
    /* Save Comp's enable state */    
    if(Comp2_ACT_PWR_EN == (Comp2_PWRMGR & Comp2_ACT_PWR_EN))
    {
        /* Comp is enabled */
        Comp2_backup.enableState = 1u;
    }
    else
    {
        /* Comp is disabled */
        Comp2_backup.enableState = 0u;
    }    
    
    Comp2_Stop();
    Comp2_SaveConfig();
}


/*******************************************************************************
* Function Name: Comp2_Wakeup
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
*  Comp2_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Comp2_Wakeup(void) 
{
    Comp2_RestoreConfig();
    
    if(Comp2_backup.enableState == 1u)
    {
        /* Enable Comp's operation */
        Comp2_Enable();

    } /* Do nothing if Comp was disabled before */ 
}


/* [] END OF FILE */
