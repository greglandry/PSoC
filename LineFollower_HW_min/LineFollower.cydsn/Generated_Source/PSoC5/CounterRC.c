/*******************************************************************************
* File Name: CounterRC.c  
* Version 2.40
*
*  Description:
*     The Counter component consists of a 8, 16, 24 or 32-bit counter with
*     a selectable period between 2 and 2^Width - 1.  
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

uint8 CounterRC_initVar = 0u;


/*******************************************************************************
* Function Name: CounterRC_Init
********************************************************************************
* Summary:
*     Initialize to the schematic state
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void CounterRC_Init(void) 
{
        #if (!CounterRC_UsingFixedFunction && !CounterRC_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!CounterRC_UsingFixedFunction && !CounterRC_ControlRegRemoved) */
        
        #if(!CounterRC_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 CounterRC_interruptState;
        #endif /* (!CounterRC_UsingFixedFunction) */
        
        #if (CounterRC_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            CounterRC_CONTROL &= CounterRC_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                CounterRC_CONTROL2 &= ((uint8)(~CounterRC_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                CounterRC_CONTROL3 &= ((uint8)(~CounterRC_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (CounterRC_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                CounterRC_CONTROL |= CounterRC_ONESHOT;
            #endif /* (CounterRC_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            CounterRC_CONTROL2 |= CounterRC_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            CounterRC_RT1 &= ((uint8)(~CounterRC_RT1_MASK));
            CounterRC_RT1 |= CounterRC_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            CounterRC_RT1 &= ((uint8)(~CounterRC_SYNCDSI_MASK));
            CounterRC_RT1 |= CounterRC_SYNCDSI_EN;

        #else
            #if(!CounterRC_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = CounterRC_CONTROL & ((uint8)(~CounterRC_CTRL_CMPMODE_MASK));
            CounterRC_CONTROL = ctrl | CounterRC_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = CounterRC_CONTROL & ((uint8)(~CounterRC_CTRL_CAPMODE_MASK));
            
            #if( 0 != CounterRC_CAPTURE_MODE_CONF)
                CounterRC_CONTROL = ctrl | CounterRC_DEFAULT_CAPTURE_MODE;
            #else
                CounterRC_CONTROL = ctrl;
            #endif /* 0 != CounterRC_CAPTURE_MODE */ 
            
            #endif /* (!CounterRC_ControlRegRemoved) */
        #endif /* (CounterRC_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!CounterRC_UsingFixedFunction)
            CounterRC_ClearFIFO();
        #endif /* (!CounterRC_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        CounterRC_WritePeriod(CounterRC_INIT_PERIOD_VALUE);
        #if (!(CounterRC_UsingFixedFunction && (CY_PSOC5A)))
            CounterRC_WriteCounter(CounterRC_INIT_COUNTER_VALUE);
        #endif /* (!(CounterRC_UsingFixedFunction && (CY_PSOC5A))) */
        CounterRC_SetInterruptMode(CounterRC_INIT_INTERRUPTS_MASK);
        
        #if (!CounterRC_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)CounterRC_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            CounterRC_WriteCompare(CounterRC_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            CounterRC_interruptState = CyEnterCriticalSection();
            
            CounterRC_STATUS_AUX_CTRL |= CounterRC_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(CounterRC_interruptState);
            
        #endif /* (!CounterRC_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterRC_Enable
********************************************************************************
* Summary:
*     Enable the Counter
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: 
*   If the Enable mode is set to Hardware only then this function has no effect 
*   on the operation of the counter.
*
*******************************************************************************/
void CounterRC_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (CounterRC_UsingFixedFunction)
        CounterRC_GLOBAL_ENABLE |= CounterRC_BLOCK_EN_MASK;
        CounterRC_GLOBAL_STBY_ENABLE |= CounterRC_BLOCK_STBY_EN_MASK;
    #endif /* (CounterRC_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!CounterRC_ControlRegRemoved || CounterRC_UsingFixedFunction)
        CounterRC_CONTROL |= CounterRC_CTRL_ENABLE;                
    #endif /* (!CounterRC_ControlRegRemoved || CounterRC_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: CounterRC_Start
********************************************************************************
* Summary:
*  Enables the counter for operation 
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Global variables:
*  CounterRC_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void CounterRC_Start(void) 
{
    if(CounterRC_initVar == 0u)
    {
        CounterRC_Init();
        
        CounterRC_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    CounterRC_Enable();        
}


/*******************************************************************************
* Function Name: CounterRC_Stop
********************************************************************************
* Summary:
* Halts the counter, but does not change any modes or disable interrupts.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: If the Enable mode is set to Hardware only then this function
*               has no effect on the operation of the counter.
*
*******************************************************************************/
void CounterRC_Stop(void) 
{
    /* Disable Counter */
    #if(!CounterRC_ControlRegRemoved || CounterRC_UsingFixedFunction)
        CounterRC_CONTROL &= ((uint8)(~CounterRC_CTRL_ENABLE));        
    #endif /* (!CounterRC_ControlRegRemoved || CounterRC_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (CounterRC_UsingFixedFunction)
        CounterRC_GLOBAL_ENABLE &= ((uint8)(~CounterRC_BLOCK_EN_MASK));
        CounterRC_GLOBAL_STBY_ENABLE &= ((uint8)(~CounterRC_BLOCK_STBY_EN_MASK));
    #endif /* (CounterRC_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterRC_SetInterruptMode
********************************************************************************
* Summary:
* Configures which interrupt sources are enabled to generate the final interrupt
*
* Parameters:  
*  InterruptsMask: This parameter is an or'd collection of the status bits
*                   which will be allowed to generate the counters interrupt.   
*
* Return: 
*  void
*
*******************************************************************************/
void CounterRC_SetInterruptMode(uint8 interruptsMask) 
{
    CounterRC_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: CounterRC_ReadStatusRegister
********************************************************************************
* Summary:
*   Reads the status register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the status register
*
* Side Effects:
*   Status register bits may be clear on read. 
*
*******************************************************************************/
uint8   CounterRC_ReadStatusRegister(void) 
{
    return CounterRC_STATUS;
}


#if(!CounterRC_ControlRegRemoved)
/*******************************************************************************
* Function Name: CounterRC_ReadControlRegister
********************************************************************************
* Summary:
*   Reads the control register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
uint8   CounterRC_ReadControlRegister(void) 
{
    return CounterRC_CONTROL;
}


/*******************************************************************************
* Function Name: CounterRC_WriteControlRegister
********************************************************************************
* Summary:
*   Sets the bit-field of the control register.  This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
void    CounterRC_WriteControlRegister(uint8 control) 
{
    CounterRC_CONTROL = control;
}

#endif  /* (!CounterRC_ControlRegRemoved) */


#if (!(CounterRC_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: CounterRC_WriteCounter
********************************************************************************
* Summary:
*   This funtion is used to set the counter to a specific value
*
* Parameters:  
*  counter:  New counter value. 
*
* Return: 
*  void 
*
*******************************************************************************/
void CounterRC_WriteCounter(uint8 counter) \
                                   
{
    #if(CounterRC_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (CounterRC_GLOBAL_ENABLE & CounterRC_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        CounterRC_GLOBAL_ENABLE |= CounterRC_BLOCK_EN_MASK;
        CY_SET_REG16(CounterRC_COUNTER_LSB_PTR, (uint16)counter);
        CounterRC_GLOBAL_ENABLE &= ((uint8)(~CounterRC_BLOCK_EN_MASK));
    #else
        CY_SET_REG8(CounterRC_COUNTER_LSB_PTR, counter);
    #endif /* (CounterRC_UsingFixedFunction) */
}
#endif /* (!(CounterRC_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: CounterRC_ReadCounter
********************************************************************************
* Summary:
* Returns the current value of the counter.  It doesn't matter
* if the counter is enabled or running.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint8) The present value of the counter.
*
*******************************************************************************/
uint8 CounterRC_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(CounterRC_UsingFixedFunction)
		(void)CY_GET_REG16(CounterRC_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(CounterRC_COUNTER_LSB_PTR_8BIT);
	#endif/* (CounterRC_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(CounterRC_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(CounterRC_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG8(CounterRC_STATICCOUNT_LSB_PTR));
    #endif /* (CounterRC_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterRC_ReadCapture
********************************************************************************
* Summary:
*   This function returns the last value captured.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) Present Capture value.
*
*******************************************************************************/
uint8 CounterRC_ReadCapture(void) 
{
    #if(CounterRC_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(CounterRC_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG8(CounterRC_STATICCOUNT_LSB_PTR));
    #endif /* (CounterRC_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterRC_WritePeriod
********************************************************************************
* Summary:
* Changes the period of the counter.  The new period 
* will be loaded the next time terminal count is detected.
*
* Parameters:  
*  period: (uint8) A value of 0 will result in
*         the counter remaining at zero.  
*
* Return: 
*  void
*
*******************************************************************************/
void CounterRC_WritePeriod(uint8 period) 
{
    #if(CounterRC_UsingFixedFunction)
        CY_SET_REG16(CounterRC_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG8(CounterRC_PERIOD_LSB_PTR, period);
    #endif /* (CounterRC_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterRC_ReadPeriod
********************************************************************************
* Summary:
* Reads the current period value without affecting counter operation.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint8) Present period value.
*
*******************************************************************************/
uint8 CounterRC_ReadPeriod(void) 
{
    #if(CounterRC_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(CounterRC_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG8(CounterRC_PERIOD_LSB_PTR));
    #endif /* (CounterRC_UsingFixedFunction) */
}


#if (!CounterRC_UsingFixedFunction)
/*******************************************************************************
* Function Name: CounterRC_WriteCompare
********************************************************************************
* Summary:
* Changes the compare value.  The compare output will 
* reflect the new value on the next UDB clock.  The compare output will be 
* driven high when the present counter value compares true based on the 
* configured compare mode setting. 
*
* Parameters:  
*  Compare:  New compare value. 
*
* Return: 
*  void
*
*******************************************************************************/
void CounterRC_WriteCompare(uint8 compare) \
                                   
{
    #if(CounterRC_UsingFixedFunction)
        CY_SET_REG16(CounterRC_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG8(CounterRC_COMPARE_LSB_PTR, compare);
    #endif /* (CounterRC_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterRC_ReadCompare
********************************************************************************
* Summary:
* Returns the compare value.
*
* Parameters:  
*  void:
*
* Return: 
*  (uint8) Present compare value.
*
*******************************************************************************/
uint8 CounterRC_ReadCompare(void) 
{
    return (CY_GET_REG8(CounterRC_COMPARE_LSB_PTR));
}


#if (CounterRC_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: CounterRC_SetCompareMode
********************************************************************************
* Summary:
*  Sets the software controlled Compare Mode.
*
* Parameters:
*  compareMode:  Compare Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void CounterRC_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    CounterRC_CONTROL &= ((uint8)(~CounterRC_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    CounterRC_CONTROL |= compareMode;
}
#endif  /* (CounterRC_COMPARE_MODE_SOFTWARE) */


#if (CounterRC_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: CounterRC_SetCaptureMode
********************************************************************************
* Summary:
*  Sets the software controlled Capture Mode.
*
* Parameters:
*  captureMode:  Capture Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void CounterRC_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    CounterRC_CONTROL &= ((uint8)(~CounterRC_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    CounterRC_CONTROL |= ((uint8)((uint8)captureMode << CounterRC_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (CounterRC_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: CounterRC_ClearFIFO
********************************************************************************
* Summary:
*   This function clears all capture data from the capture FIFO
*
* Parameters:  
*  void:
*
* Return: 
*  None
*
*******************************************************************************/
void CounterRC_ClearFIFO(void) 
{

    while(0u != (CounterRC_ReadStatusRegister() & CounterRC_STATUS_FIFONEMP))
    {
        (void)CounterRC_ReadCapture();
    }

}
#endif  /* (!CounterRC_UsingFixedFunction) */


/* [] END OF FILE */

