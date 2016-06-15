/*******************************************************************************
* File Name: CounterL2_PM.c  
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

#include "CounterL2.h"

static CounterL2_backupStruct CounterL2_backup;


/*******************************************************************************
* Function Name: CounterL2_SaveConfig
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
*  CounterL2_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void CounterL2_SaveConfig(void) 
{
    #if (!CounterL2_UsingFixedFunction)

        CounterL2_backup.CounterUdb = CounterL2_ReadCounter();

        #if (CY_UDB_V0)
            CounterL2_backup.CounterPeriod = CounterL2_ReadPeriod();
            CounterL2_backup.CompareValue = CounterL2_ReadCompare();
            CounterL2_backup.InterruptMaskValue = CounterL2_STATUS_MASK;
        #endif /* CY_UDB_V0 */

        #if(!CounterL2_ControlRegRemoved)
            CounterL2_backup.CounterControlRegister = CounterL2_ReadControlRegister();
        #endif /* (!CounterL2_ControlRegRemoved) */

    #endif /* (!CounterL2_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterL2_RestoreConfig
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
*  CounterL2_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void CounterL2_RestoreConfig(void) 
{      
    #if (!CounterL2_UsingFixedFunction)

        #if (CY_UDB_V0)
            uint8 CounterL2_interruptState;
        #endif  /* (CY_UDB_V0) */

       CounterL2_WriteCounter(CounterL2_backup.CounterUdb);

        #if (CY_UDB_V0)
            CounterL2_WritePeriod(CounterL2_backup.CounterPeriod);
            CounterL2_WriteCompare(CounterL2_backup.CompareValue);

            CounterL2_interruptState = CyEnterCriticalSection();
            CounterL2_STATUS_AUX_CTRL |= CounterL2_STATUS_ACTL_INT_EN_MASK;
            CyExitCriticalSection(CounterL2_interruptState);

            CounterL2_STATUS_MASK = CounterL2_backup.InterruptMaskValue;
        #endif  /* (CY_UDB_V0) */

        #if(!CounterL2_ControlRegRemoved)
            CounterL2_WriteControlRegister(CounterL2_backup.CounterControlRegister);
        #endif /* (!CounterL2_ControlRegRemoved) */

    #endif /* (!CounterL2_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterL2_Sleep
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
*  CounterL2_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void CounterL2_Sleep(void) 
{
    #if(!CounterL2_ControlRegRemoved)
        /* Save Counter's enable state */
        if(CounterL2_CTRL_ENABLE == (CounterL2_CONTROL & CounterL2_CTRL_ENABLE))
        {
            /* Counter is enabled */
            CounterL2_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            CounterL2_backup.CounterEnableState = 0u;
        }
    #else
        CounterL2_backup.CounterEnableState = 1u;
        if(CounterL2_backup.CounterEnableState != 0u)
        {
            CounterL2_backup.CounterEnableState = 0u;
        }
    #endif /* (!CounterL2_ControlRegRemoved) */
    
    CounterL2_Stop();
    CounterL2_SaveConfig();
}


/*******************************************************************************
* Function Name: CounterL2_Wakeup
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
*  CounterL2_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void CounterL2_Wakeup(void) 
{
    CounterL2_RestoreConfig();
    #if(!CounterL2_ControlRegRemoved)
        if(CounterL2_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            CounterL2_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!CounterL2_ControlRegRemoved) */
    
}


/* [] END OF FILE */
