/*******************************************************************************
* File Name: CounterR_PM.c  
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

#include "CounterR.h"

static CounterR_backupStruct CounterR_backup;


/*******************************************************************************
* Function Name: CounterR_SaveConfig
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
*  CounterR_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void CounterR_SaveConfig(void) 
{
    #if (!CounterR_UsingFixedFunction)

        CounterR_backup.CounterUdb = CounterR_ReadCounter();

        #if (CY_UDB_V0)
            CounterR_backup.CounterPeriod = CounterR_ReadPeriod();
            CounterR_backup.CompareValue = CounterR_ReadCompare();
            CounterR_backup.InterruptMaskValue = CounterR_STATUS_MASK;
        #endif /* CY_UDB_V0 */

        #if(!CounterR_ControlRegRemoved)
            CounterR_backup.CounterControlRegister = CounterR_ReadControlRegister();
        #endif /* (!CounterR_ControlRegRemoved) */

    #endif /* (!CounterR_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterR_RestoreConfig
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
*  CounterR_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void CounterR_RestoreConfig(void) 
{      
    #if (!CounterR_UsingFixedFunction)

        #if (CY_UDB_V0)
            uint8 CounterR_interruptState;
        #endif  /* (CY_UDB_V0) */

       CounterR_WriteCounter(CounterR_backup.CounterUdb);

        #if (CY_UDB_V0)
            CounterR_WritePeriod(CounterR_backup.CounterPeriod);
            CounterR_WriteCompare(CounterR_backup.CompareValue);

            CounterR_interruptState = CyEnterCriticalSection();
            CounterR_STATUS_AUX_CTRL |= CounterR_STATUS_ACTL_INT_EN_MASK;
            CyExitCriticalSection(CounterR_interruptState);

            CounterR_STATUS_MASK = CounterR_backup.InterruptMaskValue;
        #endif  /* (CY_UDB_V0) */

        #if(!CounterR_ControlRegRemoved)
            CounterR_WriteControlRegister(CounterR_backup.CounterControlRegister);
        #endif /* (!CounterR_ControlRegRemoved) */

    #endif /* (!CounterR_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterR_Sleep
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
*  CounterR_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void CounterR_Sleep(void) 
{
    #if(!CounterR_ControlRegRemoved)
        /* Save Counter's enable state */
        if(CounterR_CTRL_ENABLE == (CounterR_CONTROL & CounterR_CTRL_ENABLE))
        {
            /* Counter is enabled */
            CounterR_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            CounterR_backup.CounterEnableState = 0u;
        }
    #else
        CounterR_backup.CounterEnableState = 1u;
        if(CounterR_backup.CounterEnableState != 0u)
        {
            CounterR_backup.CounterEnableState = 0u;
        }
    #endif /* (!CounterR_ControlRegRemoved) */
    
    CounterR_Stop();
    CounterR_SaveConfig();
}


/*******************************************************************************
* Function Name: CounterR_Wakeup
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
*  CounterR_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void CounterR_Wakeup(void) 
{
    CounterR_RestoreConfig();
    #if(!CounterR_ControlRegRemoved)
        if(CounterR_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            CounterR_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!CounterR_ControlRegRemoved) */
    
}


/* [] END OF FILE */
