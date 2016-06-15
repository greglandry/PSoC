/*******************************************************************************
* File Name: CounterL1_PM.c  
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

#include "CounterL1.h"

static CounterL1_backupStruct CounterL1_backup;


/*******************************************************************************
* Function Name: CounterL1_SaveConfig
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
*  CounterL1_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void CounterL1_SaveConfig(void) 
{
    #if (!CounterL1_UsingFixedFunction)

        CounterL1_backup.CounterUdb = CounterL1_ReadCounter();

        #if (CY_UDB_V0)
            CounterL1_backup.CounterPeriod = CounterL1_ReadPeriod();
            CounterL1_backup.CompareValue = CounterL1_ReadCompare();
            CounterL1_backup.InterruptMaskValue = CounterL1_STATUS_MASK;
        #endif /* CY_UDB_V0 */

        #if(!CounterL1_ControlRegRemoved)
            CounterL1_backup.CounterControlRegister = CounterL1_ReadControlRegister();
        #endif /* (!CounterL1_ControlRegRemoved) */

    #endif /* (!CounterL1_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterL1_RestoreConfig
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
*  CounterL1_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void CounterL1_RestoreConfig(void) 
{      
    #if (!CounterL1_UsingFixedFunction)

        #if (CY_UDB_V0)
            uint8 CounterL1_interruptState;
        #endif  /* (CY_UDB_V0) */

       CounterL1_WriteCounter(CounterL1_backup.CounterUdb);

        #if (CY_UDB_V0)
            CounterL1_WritePeriod(CounterL1_backup.CounterPeriod);
            CounterL1_WriteCompare(CounterL1_backup.CompareValue);

            CounterL1_interruptState = CyEnterCriticalSection();
            CounterL1_STATUS_AUX_CTRL |= CounterL1_STATUS_ACTL_INT_EN_MASK;
            CyExitCriticalSection(CounterL1_interruptState);

            CounterL1_STATUS_MASK = CounterL1_backup.InterruptMaskValue;
        #endif  /* (CY_UDB_V0) */

        #if(!CounterL1_ControlRegRemoved)
            CounterL1_WriteControlRegister(CounterL1_backup.CounterControlRegister);
        #endif /* (!CounterL1_ControlRegRemoved) */

    #endif /* (!CounterL1_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterL1_Sleep
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
*  CounterL1_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void CounterL1_Sleep(void) 
{
    #if(!CounterL1_ControlRegRemoved)
        /* Save Counter's enable state */
        if(CounterL1_CTRL_ENABLE == (CounterL1_CONTROL & CounterL1_CTRL_ENABLE))
        {
            /* Counter is enabled */
            CounterL1_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            CounterL1_backup.CounterEnableState = 0u;
        }
    #else
        CounterL1_backup.CounterEnableState = 1u;
        if(CounterL1_backup.CounterEnableState != 0u)
        {
            CounterL1_backup.CounterEnableState = 0u;
        }
    #endif /* (!CounterL1_ControlRegRemoved) */
    
    CounterL1_Stop();
    CounterL1_SaveConfig();
}


/*******************************************************************************
* Function Name: CounterL1_Wakeup
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
*  CounterL1_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void CounterL1_Wakeup(void) 
{
    CounterL1_RestoreConfig();
    #if(!CounterL1_ControlRegRemoved)
        if(CounterL1_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            CounterL1_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!CounterL1_ControlRegRemoved) */
    
}


/* [] END OF FILE */
