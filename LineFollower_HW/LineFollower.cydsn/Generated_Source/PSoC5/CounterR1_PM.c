/*******************************************************************************
* File Name: CounterR1_PM.c  
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

#include "CounterR1.h"

static CounterR1_backupStruct CounterR1_backup;


/*******************************************************************************
* Function Name: CounterR1_SaveConfig
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
*  CounterR1_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void CounterR1_SaveConfig(void) 
{
    #if (!CounterR1_UsingFixedFunction)

        CounterR1_backup.CounterUdb = CounterR1_ReadCounter();

        #if (CY_UDB_V0)
            CounterR1_backup.CounterPeriod = CounterR1_ReadPeriod();
            CounterR1_backup.CompareValue = CounterR1_ReadCompare();
            CounterR1_backup.InterruptMaskValue = CounterR1_STATUS_MASK;
        #endif /* CY_UDB_V0 */

        #if(!CounterR1_ControlRegRemoved)
            CounterR1_backup.CounterControlRegister = CounterR1_ReadControlRegister();
        #endif /* (!CounterR1_ControlRegRemoved) */

    #endif /* (!CounterR1_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterR1_RestoreConfig
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
*  CounterR1_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void CounterR1_RestoreConfig(void) 
{      
    #if (!CounterR1_UsingFixedFunction)

        #if (CY_UDB_V0)
            uint8 CounterR1_interruptState;
        #endif  /* (CY_UDB_V0) */

       CounterR1_WriteCounter(CounterR1_backup.CounterUdb);

        #if (CY_UDB_V0)
            CounterR1_WritePeriod(CounterR1_backup.CounterPeriod);
            CounterR1_WriteCompare(CounterR1_backup.CompareValue);

            CounterR1_interruptState = CyEnterCriticalSection();
            CounterR1_STATUS_AUX_CTRL |= CounterR1_STATUS_ACTL_INT_EN_MASK;
            CyExitCriticalSection(CounterR1_interruptState);

            CounterR1_STATUS_MASK = CounterR1_backup.InterruptMaskValue;
        #endif  /* (CY_UDB_V0) */

        #if(!CounterR1_ControlRegRemoved)
            CounterR1_WriteControlRegister(CounterR1_backup.CounterControlRegister);
        #endif /* (!CounterR1_ControlRegRemoved) */

    #endif /* (!CounterR1_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterR1_Sleep
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
*  CounterR1_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void CounterR1_Sleep(void) 
{
    #if(!CounterR1_ControlRegRemoved)
        /* Save Counter's enable state */
        if(CounterR1_CTRL_ENABLE == (CounterR1_CONTROL & CounterR1_CTRL_ENABLE))
        {
            /* Counter is enabled */
            CounterR1_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            CounterR1_backup.CounterEnableState = 0u;
        }
    #else
        CounterR1_backup.CounterEnableState = 1u;
        if(CounterR1_backup.CounterEnableState != 0u)
        {
            CounterR1_backup.CounterEnableState = 0u;
        }
    #endif /* (!CounterR1_ControlRegRemoved) */
    
    CounterR1_Stop();
    CounterR1_SaveConfig();
}


/*******************************************************************************
* Function Name: CounterR1_Wakeup
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
*  CounterR1_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void CounterR1_Wakeup(void) 
{
    CounterR1_RestoreConfig();
    #if(!CounterR1_ControlRegRemoved)
        if(CounterR1_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            CounterR1_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!CounterR1_ControlRegRemoved) */
    
}


/* [] END OF FILE */
