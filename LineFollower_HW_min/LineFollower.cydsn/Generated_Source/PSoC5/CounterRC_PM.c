/*******************************************************************************
* File Name: CounterRC_PM.c  
* Version 2.40
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
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

#include "CounterRC.h"

static CounterRC_backupStruct CounterRC_backup;


/*******************************************************************************
* Function Name: CounterRC_SaveConfig
********************************************************************************
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
*  CounterRC_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void CounterRC_SaveConfig(void) 
{
    #if (!CounterRC_UsingFixedFunction)

        CounterRC_backup.CounterUdb = CounterRC_ReadCounter();

        #if (CY_UDB_V0)
            CounterRC_backup.CounterPeriod = CounterRC_ReadPeriod();
            CounterRC_backup.CompareValue = CounterRC_ReadCompare();
            CounterRC_backup.InterruptMaskValue = CounterRC_STATUS_MASK;
        #endif /* CY_UDB_V0 */

        #if(!CounterRC_ControlRegRemoved)
            CounterRC_backup.CounterControlRegister = CounterRC_ReadControlRegister();
        #endif /* (!CounterRC_ControlRegRemoved) */

    #endif /* (!CounterRC_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterRC_RestoreConfig
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
*  CounterRC_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void CounterRC_RestoreConfig(void) 
{      
    #if (!CounterRC_UsingFixedFunction)

        #if (CY_UDB_V0)
            uint8 CounterRC_interruptState;
        #endif  /* (CY_UDB_V0) */

       CounterRC_WriteCounter(CounterRC_backup.CounterUdb);

        #if (CY_UDB_V0)
            CounterRC_WritePeriod(CounterRC_backup.CounterPeriod);
            CounterRC_WriteCompare(CounterRC_backup.CompareValue);

            CounterRC_interruptState = CyEnterCriticalSection();
            CounterRC_STATUS_AUX_CTRL |= CounterRC_STATUS_ACTL_INT_EN_MASK;
            CyExitCriticalSection(CounterRC_interruptState);

            CounterRC_STATUS_MASK = CounterRC_backup.InterruptMaskValue;
        #endif  /* (CY_UDB_V0) */

        #if(!CounterRC_ControlRegRemoved)
            CounterRC_WriteControlRegister(CounterRC_backup.CounterControlRegister);
        #endif /* (!CounterRC_ControlRegRemoved) */

    #endif /* (!CounterRC_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterRC_Sleep
********************************************************************************
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
*  CounterRC_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void CounterRC_Sleep(void) 
{
    #if(!CounterRC_ControlRegRemoved)
        /* Save Counter's enable state */
        if(CounterRC_CTRL_ENABLE == (CounterRC_CONTROL & CounterRC_CTRL_ENABLE))
        {
            /* Counter is enabled */
            CounterRC_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            CounterRC_backup.CounterEnableState = 0u;
        }
    #else
        CounterRC_backup.CounterEnableState = 1u;
        if(CounterRC_backup.CounterEnableState != 0u)
        {
            CounterRC_backup.CounterEnableState = 0u;
        }
    #endif /* (!CounterRC_ControlRegRemoved) */
    
    CounterRC_Stop();
    CounterRC_SaveConfig();
}


/*******************************************************************************
* Function Name: CounterRC_Wakeup
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
*  CounterRC_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void CounterRC_Wakeup(void) 
{
    CounterRC_RestoreConfig();
    #if(!CounterRC_ControlRegRemoved)
        if(CounterRC_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            CounterRC_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!CounterRC_ControlRegRemoved) */
    
}


/* [] END OF FILE */
