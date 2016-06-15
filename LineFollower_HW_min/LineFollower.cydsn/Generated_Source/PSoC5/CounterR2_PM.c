/*******************************************************************************
* File Name: CounterR2_PM.c  
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

#include "CounterR2.h"

static CounterR2_backupStruct CounterR2_backup;


/*******************************************************************************
* Function Name: CounterR2_SaveConfig
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
*  CounterR2_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void CounterR2_SaveConfig(void) 
{
    #if (!CounterR2_UsingFixedFunction)

        CounterR2_backup.CounterUdb = CounterR2_ReadCounter();

        #if (CY_UDB_V0)
            CounterR2_backup.CounterPeriod = CounterR2_ReadPeriod();
            CounterR2_backup.CompareValue = CounterR2_ReadCompare();
            CounterR2_backup.InterruptMaskValue = CounterR2_STATUS_MASK;
        #endif /* CY_UDB_V0 */

        #if(!CounterR2_ControlRegRemoved)
            CounterR2_backup.CounterControlRegister = CounterR2_ReadControlRegister();
        #endif /* (!CounterR2_ControlRegRemoved) */

    #endif /* (!CounterR2_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterR2_RestoreConfig
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
*  CounterR2_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void CounterR2_RestoreConfig(void) 
{      
    #if (!CounterR2_UsingFixedFunction)

        #if (CY_UDB_V0)
            uint8 CounterR2_interruptState;
        #endif  /* (CY_UDB_V0) */

       CounterR2_WriteCounter(CounterR2_backup.CounterUdb);

        #if (CY_UDB_V0)
            CounterR2_WritePeriod(CounterR2_backup.CounterPeriod);
            CounterR2_WriteCompare(CounterR2_backup.CompareValue);

            CounterR2_interruptState = CyEnterCriticalSection();
            CounterR2_STATUS_AUX_CTRL |= CounterR2_STATUS_ACTL_INT_EN_MASK;
            CyExitCriticalSection(CounterR2_interruptState);

            CounterR2_STATUS_MASK = CounterR2_backup.InterruptMaskValue;
        #endif  /* (CY_UDB_V0) */

        #if(!CounterR2_ControlRegRemoved)
            CounterR2_WriteControlRegister(CounterR2_backup.CounterControlRegister);
        #endif /* (!CounterR2_ControlRegRemoved) */

    #endif /* (!CounterR2_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterR2_Sleep
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
*  CounterR2_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void CounterR2_Sleep(void) 
{
    #if(!CounterR2_ControlRegRemoved)
        /* Save Counter's enable state */
        if(CounterR2_CTRL_ENABLE == (CounterR2_CONTROL & CounterR2_CTRL_ENABLE))
        {
            /* Counter is enabled */
            CounterR2_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            CounterR2_backup.CounterEnableState = 0u;
        }
    #else
        CounterR2_backup.CounterEnableState = 1u;
        if(CounterR2_backup.CounterEnableState != 0u)
        {
            CounterR2_backup.CounterEnableState = 0u;
        }
    #endif /* (!CounterR2_ControlRegRemoved) */
    
    CounterR2_Stop();
    CounterR2_SaveConfig();
}


/*******************************************************************************
* Function Name: CounterR2_Wakeup
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
*  CounterR2_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void CounterR2_Wakeup(void) 
{
    CounterR2_RestoreConfig();
    #if(!CounterR2_ControlRegRemoved)
        if(CounterR2_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            CounterR2_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!CounterR2_ControlRegRemoved) */
    
}


/* [] END OF FILE */
