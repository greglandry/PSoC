/*******************************************************************************
* File Name: CounterL.c  
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

#include "CounterL.h"

uint8 CounterL_initVar = 0u;


/*******************************************************************************
* Function Name: CounterL_Init
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
void CounterL_Init(void) 
{
        #if (!CounterL_UsingFixedFunction && !CounterL_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!CounterL_UsingFixedFunction && !CounterL_ControlRegRemoved) */
        
        #if(!CounterL_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 CounterL_interruptState;
        #endif /* (!CounterL_UsingFixedFunction) */
        
        #if (CounterL_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            CounterL_CONTROL &= CounterL_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                CounterL_CONTROL2 &= ((uint8)(~CounterL_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                CounterL_CONTROL3 &= ((uint8)(~CounterL_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (CounterL_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                CounterL_CONTROL |= CounterL_ONESHOT;
            #endif /* (CounterL_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            CounterL_CONTROL2 |= CounterL_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            CounterL_RT1 &= ((uint8)(~CounterL_RT1_MASK));
            CounterL_RT1 |= CounterL_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            CounterL_RT1 &= ((uint8)(~CounterL_SYNCDSI_MASK));
            CounterL_RT1 |= CounterL_SYNCDSI_EN;

        #else
            #if(!CounterL_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = CounterL_CONTROL & ((uint8)(~CounterL_CTRL_CMPMODE_MASK));
            CounterL_CONTROL = ctrl | CounterL_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = CounterL_CONTROL & ((uint8)(~CounterL_CTRL_CAPMODE_MASK));
            
            #if( 0 != CounterL_CAPTURE_MODE_CONF)
                CounterL_CONTROL = ctrl | CounterL_DEFAULT_CAPTURE_MODE;
            #else
                CounterL_CONTROL = ctrl;
            #endif /* 0 != CounterL_CAPTURE_MODE */ 
            
            #endif /* (!CounterL_ControlRegRemoved) */
        #endif /* (CounterL_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!CounterL_UsingFixedFunction)
            CounterL_ClearFIFO();
        #endif /* (!CounterL_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        CounterL_WritePeriod(CounterL_INIT_PERIOD_VALUE);
        #if (!(CounterL_UsingFixedFunction && (CY_PSOC5A)))
            CounterL_WriteCounter(CounterL_INIT_COUNTER_VALUE);
        #endif /* (!(CounterL_UsingFixedFunction && (CY_PSOC5A))) */
        CounterL_SetInterruptMode(CounterL_INIT_INTERRUPTS_MASK);
        
        #if (!CounterL_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)CounterL_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            CounterL_WriteCompare(CounterL_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            CounterL_interruptState = CyEnterCriticalSection();
            
            CounterL_STATUS_AUX_CTRL |= CounterL_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(CounterL_interruptState);
            
        #endif /* (!CounterL_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterL_Enable
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
void CounterL_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (CounterL_UsingFixedFunction)
        CounterL_GLOBAL_ENABLE |= CounterL_BLOCK_EN_MASK;
        CounterL_GLOBAL_STBY_ENABLE |= CounterL_BLOCK_STBY_EN_MASK;
    #endif /* (CounterL_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!CounterL_ControlRegRemoved || CounterL_UsingFixedFunction)
        CounterL_CONTROL |= CounterL_CTRL_ENABLE;                
    #endif /* (!CounterL_ControlRegRemoved || CounterL_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: CounterL_Start
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
*  CounterL_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void CounterL_Start(void) 
{
    if(CounterL_initVar == 0u)
    {
        CounterL_Init();
        
        CounterL_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    CounterL_Enable();        
}


/*******************************************************************************
* Function Name: CounterL_Stop
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
void CounterL_Stop(void) 
{
    /* Disable Counter */
    #if(!CounterL_ControlRegRemoved || CounterL_UsingFixedFunction)
        CounterL_CONTROL &= ((uint8)(~CounterL_CTRL_ENABLE));        
    #endif /* (!CounterL_ControlRegRemoved || CounterL_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (CounterL_UsingFixedFunction)
        CounterL_GLOBAL_ENABLE &= ((uint8)(~CounterL_BLOCK_EN_MASK));
        CounterL_GLOBAL_STBY_ENABLE &= ((uint8)(~CounterL_BLOCK_STBY_EN_MASK));
    #endif /* (CounterL_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterL_SetInterruptMode
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
void CounterL_SetInterruptMode(uint8 interruptsMask) 
{
    CounterL_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: CounterL_ReadStatusRegister
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
uint8   CounterL_ReadStatusRegister(void) 
{
    return CounterL_STATUS;
}


#if(!CounterL_ControlRegRemoved)
/*******************************************************************************
* Function Name: CounterL_ReadControlRegister
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
uint8   CounterL_ReadControlRegister(void) 
{
    return CounterL_CONTROL;
}


/*******************************************************************************
* Function Name: CounterL_WriteControlRegister
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
void    CounterL_WriteControlRegister(uint8 control) 
{
    CounterL_CONTROL = control;
}

#endif  /* (!CounterL_ControlRegRemoved) */


#if (!(CounterL_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: CounterL_WriteCounter
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
void CounterL_WriteCounter(uint8 counter) \
                                   
{
    #if(CounterL_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (CounterL_GLOBAL_ENABLE & CounterL_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        CounterL_GLOBAL_ENABLE |= CounterL_BLOCK_EN_MASK;
        CY_SET_REG16(CounterL_COUNTER_LSB_PTR, (uint16)counter);
        CounterL_GLOBAL_ENABLE &= ((uint8)(~CounterL_BLOCK_EN_MASK));
    #else
        CY_SET_REG8(CounterL_COUNTER_LSB_PTR, counter);
    #endif /* (CounterL_UsingFixedFunction) */
}
#endif /* (!(CounterL_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: CounterL_ReadCounter
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
uint8 CounterL_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(CounterL_UsingFixedFunction)
		(void)CY_GET_REG16(CounterL_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(CounterL_COUNTER_LSB_PTR_8BIT);
	#endif/* (CounterL_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(CounterL_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(CounterL_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG8(CounterL_STATICCOUNT_LSB_PTR));
    #endif /* (CounterL_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterL_ReadCapture
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
uint8 CounterL_ReadCapture(void) 
{
    #if(CounterL_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(CounterL_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG8(CounterL_STATICCOUNT_LSB_PTR));
    #endif /* (CounterL_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterL_WritePeriod
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
void CounterL_WritePeriod(uint8 period) 
{
    #if(CounterL_UsingFixedFunction)
        CY_SET_REG16(CounterL_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG8(CounterL_PERIOD_LSB_PTR, period);
    #endif /* (CounterL_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterL_ReadPeriod
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
uint8 CounterL_ReadPeriod(void) 
{
    #if(CounterL_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(CounterL_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG8(CounterL_PERIOD_LSB_PTR));
    #endif /* (CounterL_UsingFixedFunction) */
}


#if (!CounterL_UsingFixedFunction)
/*******************************************************************************
* Function Name: CounterL_WriteCompare
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
void CounterL_WriteCompare(uint8 compare) \
                                   
{
    #if(CounterL_UsingFixedFunction)
        CY_SET_REG16(CounterL_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG8(CounterL_COMPARE_LSB_PTR, compare);
    #endif /* (CounterL_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterL_ReadCompare
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
uint8 CounterL_ReadCompare(void) 
{
    return (CY_GET_REG8(CounterL_COMPARE_LSB_PTR));
}


#if (CounterL_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: CounterL_SetCompareMode
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
void CounterL_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    CounterL_CONTROL &= ((uint8)(~CounterL_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    CounterL_CONTROL |= compareMode;
}
#endif  /* (CounterL_COMPARE_MODE_SOFTWARE) */


#if (CounterL_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: CounterL_SetCaptureMode
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
void CounterL_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    CounterL_CONTROL &= ((uint8)(~CounterL_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    CounterL_CONTROL |= ((uint8)((uint8)captureMode << CounterL_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (CounterL_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: CounterL_ClearFIFO
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
void CounterL_ClearFIFO(void) 
{

    while(0u != (CounterL_ReadStatusRegister() & CounterL_STATUS_FIFONEMP))
    {
        (void)CounterL_ReadCapture();
    }

}
#endif  /* (!CounterL_UsingFixedFunction) */


/* [] END OF FILE */

