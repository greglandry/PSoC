/*******************************************************************************
* File Name: CounterLC.c  
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

#include "CounterLC.h"

uint8 CounterLC_initVar = 0u;


/*******************************************************************************
* Function Name: CounterLC_Init
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
void CounterLC_Init(void) 
{
        #if (!CounterLC_UsingFixedFunction && !CounterLC_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!CounterLC_UsingFixedFunction && !CounterLC_ControlRegRemoved) */
        
        #if(!CounterLC_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 CounterLC_interruptState;
        #endif /* (!CounterLC_UsingFixedFunction) */
        
        #if (CounterLC_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            CounterLC_CONTROL &= CounterLC_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                CounterLC_CONTROL2 &= ((uint8)(~CounterLC_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                CounterLC_CONTROL3 &= ((uint8)(~CounterLC_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (CounterLC_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                CounterLC_CONTROL |= CounterLC_ONESHOT;
            #endif /* (CounterLC_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            CounterLC_CONTROL2 |= CounterLC_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            CounterLC_RT1 &= ((uint8)(~CounterLC_RT1_MASK));
            CounterLC_RT1 |= CounterLC_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            CounterLC_RT1 &= ((uint8)(~CounterLC_SYNCDSI_MASK));
            CounterLC_RT1 |= CounterLC_SYNCDSI_EN;

        #else
            #if(!CounterLC_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = CounterLC_CONTROL & ((uint8)(~CounterLC_CTRL_CMPMODE_MASK));
            CounterLC_CONTROL = ctrl | CounterLC_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = CounterLC_CONTROL & ((uint8)(~CounterLC_CTRL_CAPMODE_MASK));
            
            #if( 0 != CounterLC_CAPTURE_MODE_CONF)
                CounterLC_CONTROL = ctrl | CounterLC_DEFAULT_CAPTURE_MODE;
            #else
                CounterLC_CONTROL = ctrl;
            #endif /* 0 != CounterLC_CAPTURE_MODE */ 
            
            #endif /* (!CounterLC_ControlRegRemoved) */
        #endif /* (CounterLC_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!CounterLC_UsingFixedFunction)
            CounterLC_ClearFIFO();
        #endif /* (!CounterLC_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        CounterLC_WritePeriod(CounterLC_INIT_PERIOD_VALUE);
        #if (!(CounterLC_UsingFixedFunction && (CY_PSOC5A)))
            CounterLC_WriteCounter(CounterLC_INIT_COUNTER_VALUE);
        #endif /* (!(CounterLC_UsingFixedFunction && (CY_PSOC5A))) */
        CounterLC_SetInterruptMode(CounterLC_INIT_INTERRUPTS_MASK);
        
        #if (!CounterLC_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)CounterLC_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            CounterLC_WriteCompare(CounterLC_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            CounterLC_interruptState = CyEnterCriticalSection();
            
            CounterLC_STATUS_AUX_CTRL |= CounterLC_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(CounterLC_interruptState);
            
        #endif /* (!CounterLC_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterLC_Enable
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
void CounterLC_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (CounterLC_UsingFixedFunction)
        CounterLC_GLOBAL_ENABLE |= CounterLC_BLOCK_EN_MASK;
        CounterLC_GLOBAL_STBY_ENABLE |= CounterLC_BLOCK_STBY_EN_MASK;
    #endif /* (CounterLC_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!CounterLC_ControlRegRemoved || CounterLC_UsingFixedFunction)
        CounterLC_CONTROL |= CounterLC_CTRL_ENABLE;                
    #endif /* (!CounterLC_ControlRegRemoved || CounterLC_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: CounterLC_Start
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
*  CounterLC_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void CounterLC_Start(void) 
{
    if(CounterLC_initVar == 0u)
    {
        CounterLC_Init();
        
        CounterLC_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    CounterLC_Enable();        
}


/*******************************************************************************
* Function Name: CounterLC_Stop
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
void CounterLC_Stop(void) 
{
    /* Disable Counter */
    #if(!CounterLC_ControlRegRemoved || CounterLC_UsingFixedFunction)
        CounterLC_CONTROL &= ((uint8)(~CounterLC_CTRL_ENABLE));        
    #endif /* (!CounterLC_ControlRegRemoved || CounterLC_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (CounterLC_UsingFixedFunction)
        CounterLC_GLOBAL_ENABLE &= ((uint8)(~CounterLC_BLOCK_EN_MASK));
        CounterLC_GLOBAL_STBY_ENABLE &= ((uint8)(~CounterLC_BLOCK_STBY_EN_MASK));
    #endif /* (CounterLC_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterLC_SetInterruptMode
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
void CounterLC_SetInterruptMode(uint8 interruptsMask) 
{
    CounterLC_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: CounterLC_ReadStatusRegister
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
uint8   CounterLC_ReadStatusRegister(void) 
{
    return CounterLC_STATUS;
}


#if(!CounterLC_ControlRegRemoved)
/*******************************************************************************
* Function Name: CounterLC_ReadControlRegister
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
uint8   CounterLC_ReadControlRegister(void) 
{
    return CounterLC_CONTROL;
}


/*******************************************************************************
* Function Name: CounterLC_WriteControlRegister
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
void    CounterLC_WriteControlRegister(uint8 control) 
{
    CounterLC_CONTROL = control;
}

#endif  /* (!CounterLC_ControlRegRemoved) */


#if (!(CounterLC_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: CounterLC_WriteCounter
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
void CounterLC_WriteCounter(uint8 counter) \
                                   
{
    #if(CounterLC_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (CounterLC_GLOBAL_ENABLE & CounterLC_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        CounterLC_GLOBAL_ENABLE |= CounterLC_BLOCK_EN_MASK;
        CY_SET_REG16(CounterLC_COUNTER_LSB_PTR, (uint16)counter);
        CounterLC_GLOBAL_ENABLE &= ((uint8)(~CounterLC_BLOCK_EN_MASK));
    #else
        CY_SET_REG8(CounterLC_COUNTER_LSB_PTR, counter);
    #endif /* (CounterLC_UsingFixedFunction) */
}
#endif /* (!(CounterLC_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: CounterLC_ReadCounter
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
uint8 CounterLC_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(CounterLC_UsingFixedFunction)
		(void)CY_GET_REG16(CounterLC_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(CounterLC_COUNTER_LSB_PTR_8BIT);
	#endif/* (CounterLC_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(CounterLC_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(CounterLC_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG8(CounterLC_STATICCOUNT_LSB_PTR));
    #endif /* (CounterLC_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterLC_ReadCapture
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
uint8 CounterLC_ReadCapture(void) 
{
    #if(CounterLC_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(CounterLC_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG8(CounterLC_STATICCOUNT_LSB_PTR));
    #endif /* (CounterLC_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterLC_WritePeriod
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
void CounterLC_WritePeriod(uint8 period) 
{
    #if(CounterLC_UsingFixedFunction)
        CY_SET_REG16(CounterLC_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG8(CounterLC_PERIOD_LSB_PTR, period);
    #endif /* (CounterLC_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterLC_ReadPeriod
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
uint8 CounterLC_ReadPeriod(void) 
{
    #if(CounterLC_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(CounterLC_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG8(CounterLC_PERIOD_LSB_PTR));
    #endif /* (CounterLC_UsingFixedFunction) */
}


#if (!CounterLC_UsingFixedFunction)
/*******************************************************************************
* Function Name: CounterLC_WriteCompare
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
void CounterLC_WriteCompare(uint8 compare) \
                                   
{
    #if(CounterLC_UsingFixedFunction)
        CY_SET_REG16(CounterLC_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG8(CounterLC_COMPARE_LSB_PTR, compare);
    #endif /* (CounterLC_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterLC_ReadCompare
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
uint8 CounterLC_ReadCompare(void) 
{
    return (CY_GET_REG8(CounterLC_COMPARE_LSB_PTR));
}


#if (CounterLC_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: CounterLC_SetCompareMode
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
void CounterLC_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    CounterLC_CONTROL &= ((uint8)(~CounterLC_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    CounterLC_CONTROL |= compareMode;
}
#endif  /* (CounterLC_COMPARE_MODE_SOFTWARE) */


#if (CounterLC_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: CounterLC_SetCaptureMode
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
void CounterLC_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    CounterLC_CONTROL &= ((uint8)(~CounterLC_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    CounterLC_CONTROL |= ((uint8)((uint8)captureMode << CounterLC_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (CounterLC_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: CounterLC_ClearFIFO
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
void CounterLC_ClearFIFO(void) 
{

    while(0u != (CounterLC_ReadStatusRegister() & CounterLC_STATUS_FIFONEMP))
    {
        (void)CounterLC_ReadCapture();
    }

}
#endif  /* (!CounterLC_UsingFixedFunction) */


/* [] END OF FILE */

