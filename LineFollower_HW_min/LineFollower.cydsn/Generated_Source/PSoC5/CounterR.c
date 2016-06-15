/*******************************************************************************
* File Name: CounterR.c  
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

#include "CounterR.h"

uint8 CounterR_initVar = 0u;


/*******************************************************************************
* Function Name: CounterR_Init
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
void CounterR_Init(void) 
{
        #if (!CounterR_UsingFixedFunction && !CounterR_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!CounterR_UsingFixedFunction && !CounterR_ControlRegRemoved) */
        
        #if(!CounterR_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 CounterR_interruptState;
        #endif /* (!CounterR_UsingFixedFunction) */
        
        #if (CounterR_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            CounterR_CONTROL &= CounterR_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                CounterR_CONTROL2 &= ((uint8)(~CounterR_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                CounterR_CONTROL3 &= ((uint8)(~CounterR_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (CounterR_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                CounterR_CONTROL |= CounterR_ONESHOT;
            #endif /* (CounterR_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            CounterR_CONTROL2 |= CounterR_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            CounterR_RT1 &= ((uint8)(~CounterR_RT1_MASK));
            CounterR_RT1 |= CounterR_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            CounterR_RT1 &= ((uint8)(~CounterR_SYNCDSI_MASK));
            CounterR_RT1 |= CounterR_SYNCDSI_EN;

        #else
            #if(!CounterR_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = CounterR_CONTROL & ((uint8)(~CounterR_CTRL_CMPMODE_MASK));
            CounterR_CONTROL = ctrl | CounterR_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = CounterR_CONTROL & ((uint8)(~CounterR_CTRL_CAPMODE_MASK));
            
            #if( 0 != CounterR_CAPTURE_MODE_CONF)
                CounterR_CONTROL = ctrl | CounterR_DEFAULT_CAPTURE_MODE;
            #else
                CounterR_CONTROL = ctrl;
            #endif /* 0 != CounterR_CAPTURE_MODE */ 
            
            #endif /* (!CounterR_ControlRegRemoved) */
        #endif /* (CounterR_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!CounterR_UsingFixedFunction)
            CounterR_ClearFIFO();
        #endif /* (!CounterR_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        CounterR_WritePeriod(CounterR_INIT_PERIOD_VALUE);
        #if (!(CounterR_UsingFixedFunction && (CY_PSOC5A)))
            CounterR_WriteCounter(CounterR_INIT_COUNTER_VALUE);
        #endif /* (!(CounterR_UsingFixedFunction && (CY_PSOC5A))) */
        CounterR_SetInterruptMode(CounterR_INIT_INTERRUPTS_MASK);
        
        #if (!CounterR_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)CounterR_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            CounterR_WriteCompare(CounterR_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            CounterR_interruptState = CyEnterCriticalSection();
            
            CounterR_STATUS_AUX_CTRL |= CounterR_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(CounterR_interruptState);
            
        #endif /* (!CounterR_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterR_Enable
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
void CounterR_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (CounterR_UsingFixedFunction)
        CounterR_GLOBAL_ENABLE |= CounterR_BLOCK_EN_MASK;
        CounterR_GLOBAL_STBY_ENABLE |= CounterR_BLOCK_STBY_EN_MASK;
    #endif /* (CounterR_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!CounterR_ControlRegRemoved || CounterR_UsingFixedFunction)
        CounterR_CONTROL |= CounterR_CTRL_ENABLE;                
    #endif /* (!CounterR_ControlRegRemoved || CounterR_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: CounterR_Start
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
*  CounterR_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void CounterR_Start(void) 
{
    if(CounterR_initVar == 0u)
    {
        CounterR_Init();
        
        CounterR_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    CounterR_Enable();        
}


/*******************************************************************************
* Function Name: CounterR_Stop
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
void CounterR_Stop(void) 
{
    /* Disable Counter */
    #if(!CounterR_ControlRegRemoved || CounterR_UsingFixedFunction)
        CounterR_CONTROL &= ((uint8)(~CounterR_CTRL_ENABLE));        
    #endif /* (!CounterR_ControlRegRemoved || CounterR_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (CounterR_UsingFixedFunction)
        CounterR_GLOBAL_ENABLE &= ((uint8)(~CounterR_BLOCK_EN_MASK));
        CounterR_GLOBAL_STBY_ENABLE &= ((uint8)(~CounterR_BLOCK_STBY_EN_MASK));
    #endif /* (CounterR_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterR_SetInterruptMode
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
void CounterR_SetInterruptMode(uint8 interruptsMask) 
{
    CounterR_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: CounterR_ReadStatusRegister
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
uint8   CounterR_ReadStatusRegister(void) 
{
    return CounterR_STATUS;
}


#if(!CounterR_ControlRegRemoved)
/*******************************************************************************
* Function Name: CounterR_ReadControlRegister
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
uint8   CounterR_ReadControlRegister(void) 
{
    return CounterR_CONTROL;
}


/*******************************************************************************
* Function Name: CounterR_WriteControlRegister
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
void    CounterR_WriteControlRegister(uint8 control) 
{
    CounterR_CONTROL = control;
}

#endif  /* (!CounterR_ControlRegRemoved) */


#if (!(CounterR_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: CounterR_WriteCounter
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
void CounterR_WriteCounter(uint8 counter) \
                                   
{
    #if(CounterR_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (CounterR_GLOBAL_ENABLE & CounterR_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        CounterR_GLOBAL_ENABLE |= CounterR_BLOCK_EN_MASK;
        CY_SET_REG16(CounterR_COUNTER_LSB_PTR, (uint16)counter);
        CounterR_GLOBAL_ENABLE &= ((uint8)(~CounterR_BLOCK_EN_MASK));
    #else
        CY_SET_REG8(CounterR_COUNTER_LSB_PTR, counter);
    #endif /* (CounterR_UsingFixedFunction) */
}
#endif /* (!(CounterR_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: CounterR_ReadCounter
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
uint8 CounterR_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(CounterR_UsingFixedFunction)
		(void)CY_GET_REG16(CounterR_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(CounterR_COUNTER_LSB_PTR_8BIT);
	#endif/* (CounterR_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(CounterR_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(CounterR_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG8(CounterR_STATICCOUNT_LSB_PTR));
    #endif /* (CounterR_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterR_ReadCapture
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
uint8 CounterR_ReadCapture(void) 
{
    #if(CounterR_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(CounterR_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG8(CounterR_STATICCOUNT_LSB_PTR));
    #endif /* (CounterR_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterR_WritePeriod
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
void CounterR_WritePeriod(uint8 period) 
{
    #if(CounterR_UsingFixedFunction)
        CY_SET_REG16(CounterR_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG8(CounterR_PERIOD_LSB_PTR, period);
    #endif /* (CounterR_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterR_ReadPeriod
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
uint8 CounterR_ReadPeriod(void) 
{
    #if(CounterR_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(CounterR_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG8(CounterR_PERIOD_LSB_PTR));
    #endif /* (CounterR_UsingFixedFunction) */
}


#if (!CounterR_UsingFixedFunction)
/*******************************************************************************
* Function Name: CounterR_WriteCompare
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
void CounterR_WriteCompare(uint8 compare) \
                                   
{
    #if(CounterR_UsingFixedFunction)
        CY_SET_REG16(CounterR_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG8(CounterR_COMPARE_LSB_PTR, compare);
    #endif /* (CounterR_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterR_ReadCompare
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
uint8 CounterR_ReadCompare(void) 
{
    return (CY_GET_REG8(CounterR_COMPARE_LSB_PTR));
}


#if (CounterR_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: CounterR_SetCompareMode
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
void CounterR_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    CounterR_CONTROL &= ((uint8)(~CounterR_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    CounterR_CONTROL |= compareMode;
}
#endif  /* (CounterR_COMPARE_MODE_SOFTWARE) */


#if (CounterR_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: CounterR_SetCaptureMode
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
void CounterR_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    CounterR_CONTROL &= ((uint8)(~CounterR_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    CounterR_CONTROL |= ((uint8)((uint8)captureMode << CounterR_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (CounterR_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: CounterR_ClearFIFO
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
void CounterR_ClearFIFO(void) 
{

    while(0u != (CounterR_ReadStatusRegister() & CounterR_STATUS_FIFONEMP))
    {
        (void)CounterR_ReadCapture();
    }

}
#endif  /* (!CounterR_UsingFixedFunction) */


/* [] END OF FILE */

