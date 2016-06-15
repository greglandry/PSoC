/*******************************************************************************
* File Name: CounterL_PM.c  
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

#include "CounterL.h"

static CounterL_backupStruct CounterL_backup;


/*******************************************************************************
* Function Name: CounterL_SaveConfig
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
*  CounterL_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void CounterL_SaveConfig(void) 
{
    #if (!CounterL_UsingFixedFunction)

        CounterL_backup.CounterUdb = CounterL_ReadCounter();

        #if (CY_UDB_V0)
            CounterL_backup.CounterPeriod = CounterL_ReadPeriod();
            CounterL_backup.CompareValue = CounterL_ReadCompare();
            CounterL_backup.InterruptMaskValue = CounterL_STATUS_MASK;
        #endif /* CY_UDB_V0 */

        #if(!CounterL_ControlRegRemoved)
            CounterL_backup.CounterControlRegister = CounterL_ReadControlRegister();
        #endif /* (!CounterL_ControlRegRemoved) */

    #endif /* (!CounterL_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterL_RestoreConfig
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
*  CounterL_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void CounterL_RestoreConfig(void) 
{      
    #if (!CounterL_UsingFixedFunction)

        #if (CY_UDB_V0)
            uint8 CounterL_interruptState;
        #endif  /* (CY_UDB_V0) */

       CounterL_WriteCounter(CounterL_backup.CounterUdb);

        #if (CY_UDB_V0)
            CounterL_WritePeriod(CounterL_backup.CounterPeriod);
            CounterL_WriteCompare(CounterL_backup.CompareValue);

            CounterL_interruptState = CyEnterCriticalSection();
            CounterL_STATUS_AUX_CTRL |= CounterL_STATUS_ACTL_INT_EN_MASK;
            CyExitCriticalSection(CounterL_interruptState);

            CounterL_STATUS_MASK = CounterL_backup.InterruptMaskValue;
        #endif  /* (CY_UDB_V0) */

        #if(!CounterL_ControlRegRemoved)
            CounterL_WriteControlRegister(CounterL_backup.CounterControlRegister);
        #endif /* (!CounterL_ControlRegRemoved) */

    #endif /* (!CounterL_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterL_Sleep
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
*  CounterL_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void CounterL_Sleep(void) 
{
    #if(!CounterL_ControlRegRemoved)
        /* Save Counter's enable state */
        if(CounterL_CTRL_ENABLE == (CounterL_CONTROL & CounterL_CTRL_ENABLE))
        {
            /* Counter is enabled */
            CounterL_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            CounterL_backup.CounterEnableState = 0u;
        }
    #else
        CounterL_backup.CounterEnableState = 1u;
        if(CounterL_backup.CounterEnableState != 0u)
        {
            CounterL_backup.CounterEnableState = 0u;
        }
    #endif /* (!CounterL_ControlRegRemoved) */
    
    CounterL_Stop();
    CounterL_SaveConfig();
}


/*******************************************************************************
* Function Name: CounterL_Wakeup
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
*  CounterL_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void CounterL_Wakeup(void) 
{
    CounterL_RestoreConfig();
    #if(!CounterL_ControlRegRemoved)
        if(CounterL_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            CounterL_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!CounterL_ControlRegRemoved) */
    
}


/* [] END OF FILE */
