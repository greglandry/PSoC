/*******************************************************************************
* File Name: Comp1.c
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

#include "Comp1.h"

static Comp1_backupStruct Comp1_backup;


/*******************************************************************************
* Function Name: Comp1_SaveConfig
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
void Comp1_SaveConfig(void) 
{
    /* Empty since all are system reset for retention flops */
}


/*******************************************************************************
* Function Name: Comp1_RestoreConfig
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
void Comp1_RestoreConfig(void) 
{
    /* Empty since all are system reset for retention flops */    
}


/*******************************************************************************
* Function Name: Comp1_Sleep
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
*  Comp1_backup.enableState:  Is modified depending on the enable 
*   state of the block before entering sleep mode.
*
*******************************************************************************/
void Comp1_Sleep(void) 
{
    /* Save Comp's enable state */    
    if(Comp1_ACT_PWR_EN == (Comp1_PWRMGR & Comp1_ACT_PWR_EN))
    {
        /* Comp is enabled */
        Comp1_backup.enableState = 1u;
    }
    else
    {
        /* Comp is disabled */
        Comp1_backup.enableState = 0u;
    }    
    
    Comp1_Stop();
    Comp1_SaveConfig();
}


/*******************************************************************************
* Function Name: Comp1_Wakeup
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
*  Comp1_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Comp1_Wakeup(void) 
{
    Comp1_RestoreConfig();
    
    if(Comp1_backup.enableState == 1u)
    {
        /* Enable Comp's operation */
        Comp1_Enable();

    } /* Do nothing if Comp was disabled before */ 
}


/* [] END OF FILE */
