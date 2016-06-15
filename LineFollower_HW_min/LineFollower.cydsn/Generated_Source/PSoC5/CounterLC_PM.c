/*******************************************************************************
* File Name: CounterLC_PM.c  
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

#include "CounterLC.h"

static CounterLC_backupStruct CounterLC_backup;


/*******************************************************************************
* Function Name: CounterLC_SaveConfig
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
*  CounterLC_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void CounterLC_SaveConfig(void) 
{
    #if (!CounterLC_UsingFixedFunction)

        CounterLC_backup.CounterUdb = CounterLC_ReadCounter();

        #if (CY_UDB_V0)
            CounterLC_backup.CounterPeriod = CounterLC_ReadPeriod();
            CounterLC_backup.CompareValue = CounterLC_ReadCompare();
            CounterLC_backup.InterruptMaskValue = CounterLC_STATUS_MASK;
        #endif /* CY_UDB_V0 */

        #if(!CounterLC_ControlRegRemoved)
            CounterLC_backup.CounterControlRegister = CounterLC_ReadControlRegister();
        #endif /* (!CounterLC_ControlRegRemoved) */

    #endif /* (!CounterLC_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterLC_RestoreConfig
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
*  CounterLC_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void CounterLC_RestoreConfig(void) 
{      
    #if (!CounterLC_UsingFixedFunction)

        #if (CY_UDB_V0)
            uint8 CounterLC_interruptState;
        #endif  /* (CY_UDB_V0) */

       CounterLC_WriteCounter(CounterLC_backup.CounterUdb);

        #if (CY_UDB_V0)
            CounterLC_WritePeriod(CounterLC_backup.CounterPeriod);
            CounterLC_WriteCompare(CounterLC_backup.CompareValue);

            CounterLC_interruptState = CyEnterCriticalSection();
            CounterLC_STATUS_AUX_CTRL |= CounterLC_STATUS_ACTL_INT_EN_MASK;
            CyExitCriticalSection(CounterLC_interruptState);

            CounterLC_STATUS_MASK = CounterLC_backup.InterruptMaskValue;
        #endif  /* (CY_UDB_V0) */

        #if(!CounterLC_ControlRegRemoved)
            CounterLC_WriteControlRegister(CounterLC_backup.CounterControlRegister);
        #endif /* (!CounterLC_ControlRegRemoved) */

    #endif /* (!CounterLC_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterLC_Sleep
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
*  CounterLC_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void CounterLC_Sleep(void) 
{
    #if(!CounterLC_ControlRegRemoved)
        /* Save Counter's enable state */
        if(CounterLC_CTRL_ENABLE == (CounterLC_CONTROL & CounterLC_CTRL_ENABLE))
        {
            /* Counter is enabled */
            CounterLC_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            CounterLC_backup.CounterEnableState = 0u;
        }
    #else
        CounterLC_backup.CounterEnableState = 1u;
        if(CounterLC_backup.CounterEnableState != 0u)
        {
            CounterLC_backup.CounterEnableState = 0u;
        }
    #endif /* (!CounterLC_ControlRegRemoved) */
    
    CounterLC_Stop();
    CounterLC_SaveConfig();
}


/*******************************************************************************
* Function Name: CounterLC_Wakeup
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
*  CounterLC_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void CounterLC_Wakeup(void) 
{
    CounterLC_RestoreConfig();
    #if(!CounterLC_ControlRegRemoved)
        if(CounterLC_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            CounterLC_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!CounterLC_ControlRegRemoved) */
    
}


/* [] END OF FILE */
