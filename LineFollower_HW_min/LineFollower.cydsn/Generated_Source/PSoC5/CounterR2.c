/*******************************************************************************
* File Name: CounterR2.c  
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

#include "CounterR2.h"

uint8 CounterR2_initVar = 0u;


/*******************************************************************************
* Function Name: CounterR2_Init
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
void CounterR2_Init(void) 
{
        #if (!CounterR2_UsingFixedFunction && !CounterR2_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!CounterR2_UsingFixedFunction && !CounterR2_ControlRegRemoved) */
        
        #if(!CounterR2_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 CounterR2_interruptState;
        #endif /* (!CounterR2_UsingFixedFunction) */
        
        #if (CounterR2_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            CounterR2_CONTROL &= CounterR2_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                CounterR2_CONTROL2 &= ((uint8)(~CounterR2_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                CounterR2_CONTROL3 &= ((uint8)(~CounterR2_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (CounterR2_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                CounterR2_CONTROL |= CounterR2_ONESHOT;
            #endif /* (CounterR2_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            CounterR2_CONTROL2 |= CounterR2_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            CounterR2_RT1 &= ((uint8)(~CounterR2_RT1_MASK));
            CounterR2_RT1 |= CounterR2_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            CounterR2_RT1 &= ((uint8)(~CounterR2_SYNCDSI_MASK));
            CounterR2_RT1 |= CounterR2_SYNCDSI_EN;

        #else
            #if(!CounterR2_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = CounterR2_CONTROL & ((uint8)(~CounterR2_CTRL_CMPMODE_MASK));
            CounterR2_CONTROL = ctrl | CounterR2_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = CounterR2_CONTROL & ((uint8)(~CounterR2_CTRL_CAPMODE_MASK));
            
            #if( 0 != CounterR2_CAPTURE_MODE_CONF)
                CounterR2_CONTROL = ctrl | CounterR2_DEFAULT_CAPTURE_MODE;
            #else
                CounterR2_CONTROL = ctrl;
            #endif /* 0 != CounterR2_CAPTURE_MODE */ 
            
            #endif /* (!CounterR2_ControlRegRemoved) */
        #endif /* (CounterR2_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!CounterR2_UsingFixedFunction)
            CounterR2_ClearFIFO();
        #endif /* (!CounterR2_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        CounterR2_WritePeriod(CounterR2_INIT_PERIOD_VALUE);
        #if (!(CounterR2_UsingFixedFunction && (CY_PSOC5A)))
            CounterR2_WriteCounter(CounterR2_INIT_COUNTER_VALUE);
        #endif /* (!(CounterR2_UsingFixedFunction && (CY_PSOC5A))) */
        CounterR2_SetInterruptMode(CounterR2_INIT_INTERRUPTS_MASK);
        
        #if (!CounterR2_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)CounterR2_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            CounterR2_WriteCompare(CounterR2_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            CounterR2_interruptState = CyEnterCriticalSection();
            
            CounterR2_STATUS_AUX_CTRL |= CounterR2_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(CounterR2_interruptState);
            
        #endif /* (!CounterR2_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterR2_Enable
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
void CounterR2_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (CounterR2_UsingFixedFunction)
        CounterR2_GLOBAL_ENABLE |= CounterR2_BLOCK_EN_MASK;
        CounterR2_GLOBAL_STBY_ENABLE |= CounterR2_BLOCK_STBY_EN_MASK;
    #endif /* (CounterR2_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!CounterR2_ControlRegRemoved || CounterR2_UsingFixedFunction)
        CounterR2_CONTROL |= CounterR2_CTRL_ENABLE;                
    #endif /* (!CounterR2_ControlRegRemoved || CounterR2_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: CounterR2_Start
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
*  CounterR2_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void CounterR2_Start(void) 
{
    if(CounterR2_initVar == 0u)
    {
        CounterR2_Init();
        
        CounterR2_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    CounterR2_Enable();        
}


/*******************************************************************************
* Function Name: CounterR2_Stop
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
void CounterR2_Stop(void) 
{
    /* Disable Counter */
    #if(!CounterR2_ControlRegRemoved || CounterR2_UsingFixedFunction)
        CounterR2_CONTROL &= ((uint8)(~CounterR2_CTRL_ENABLE));        
    #endif /* (!CounterR2_ControlRegRemoved || CounterR2_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (CounterR2_UsingFixedFunction)
        CounterR2_GLOBAL_ENABLE &= ((uint8)(~CounterR2_BLOCK_EN_MASK));
        CounterR2_GLOBAL_STBY_ENABLE &= ((uint8)(~CounterR2_BLOCK_STBY_EN_MASK));
    #endif /* (CounterR2_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterR2_SetInterruptMode
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
void CounterR2_SetInterruptMode(uint8 interruptsMask) 
{
    CounterR2_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: CounterR2_ReadStatusRegister
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
uint8   CounterR2_ReadStatusRegister(void) 
{
    return CounterR2_STATUS;
}


#if(!CounterR2_ControlRegRemoved)
/*******************************************************************************
* Function Name: CounterR2_ReadControlRegister
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
uint8   CounterR2_ReadControlRegister(void) 
{
    return CounterR2_CONTROL;
}


/*******************************************************************************
* Function Name: CounterR2_WriteControlRegister
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
void    CounterR2_WriteControlRegister(uint8 control) 
{
    CounterR2_CONTROL = control;
}

#endif  /* (!CounterR2_ControlRegRemoved) */


#if (!(CounterR2_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: CounterR2_WriteCounter
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
void CounterR2_WriteCounter(uint16 counter) \
                                   
{
    #if(CounterR2_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (CounterR2_GLOBAL_ENABLE & CounterR2_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        CounterR2_GLOBAL_ENABLE |= CounterR2_BLOCK_EN_MASK;
        CY_SET_REG16(CounterR2_COUNTER_LSB_PTR, (uint16)counter);
        CounterR2_GLOBAL_ENABLE &= ((uint8)(~CounterR2_BLOCK_EN_MASK));
    #else
        CY_SET_REG16(CounterR2_COUNTER_LSB_PTR, counter);
    #endif /* (CounterR2_UsingFixedFunction) */
}
#endif /* (!(CounterR2_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: CounterR2_ReadCounter
********************************************************************************
* Summary:
* Returns the current value of the counter.  It doesn't matter
* if the counter is enabled or running.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint16) The present value of the counter.
*
*******************************************************************************/
uint16 CounterR2_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(CounterR2_UsingFixedFunction)
		(void)CY_GET_REG16(CounterR2_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(CounterR2_COUNTER_LSB_PTR_8BIT);
	#endif/* (CounterR2_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(CounterR2_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(CounterR2_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(CounterR2_STATICCOUNT_LSB_PTR));
    #endif /* (CounterR2_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterR2_ReadCapture
********************************************************************************
* Summary:
*   This function returns the last value captured.
*
* Parameters:  
*  void
*
* Return: 
*  (uint16) Present Capture value.
*
*******************************************************************************/
uint16 CounterR2_ReadCapture(void) 
{
    #if(CounterR2_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(CounterR2_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(CounterR2_STATICCOUNT_LSB_PTR));
    #endif /* (CounterR2_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterR2_WritePeriod
********************************************************************************
* Summary:
* Changes the period of the counter.  The new period 
* will be loaded the next time terminal count is detected.
*
* Parameters:  
*  period: (uint16) A value of 0 will result in
*         the counter remaining at zero.  
*
* Return: 
*  void
*
*******************************************************************************/
void CounterR2_WritePeriod(uint16 period) 
{
    #if(CounterR2_UsingFixedFunction)
        CY_SET_REG16(CounterR2_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG16(CounterR2_PERIOD_LSB_PTR, period);
    #endif /* (CounterR2_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterR2_ReadPeriod
********************************************************************************
* Summary:
* Reads the current period value without affecting counter operation.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint16) Present period value.
*
*******************************************************************************/
uint16 CounterR2_ReadPeriod(void) 
{
    #if(CounterR2_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(CounterR2_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(CounterR2_PERIOD_LSB_PTR));
    #endif /* (CounterR2_UsingFixedFunction) */
}


#if (!CounterR2_UsingFixedFunction)
/*******************************************************************************
* Function Name: CounterR2_WriteCompare
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
void CounterR2_WriteCompare(uint16 compare) \
                                   
{
    #if(CounterR2_UsingFixedFunction)
        CY_SET_REG16(CounterR2_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG16(CounterR2_COMPARE_LSB_PTR, compare);
    #endif /* (CounterR2_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterR2_ReadCompare
********************************************************************************
* Summary:
* Returns the compare value.
*
* Parameters:  
*  void:
*
* Return: 
*  (uint16) Present compare value.
*
*******************************************************************************/
uint16 CounterR2_ReadCompare(void) 
{
    return (CY_GET_REG16(CounterR2_COMPARE_LSB_PTR));
}


#if (CounterR2_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: CounterR2_SetCompareMode
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
void CounterR2_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    CounterR2_CONTROL &= ((uint8)(~CounterR2_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    CounterR2_CONTROL |= compareMode;
}
#endif  /* (CounterR2_COMPARE_MODE_SOFTWARE) */


#if (CounterR2_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: CounterR2_SetCaptureMode
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
void CounterR2_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    CounterR2_CONTROL &= ((uint8)(~CounterR2_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    CounterR2_CONTROL |= ((uint8)((uint8)captureMode << CounterR2_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (CounterR2_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: CounterR2_ClearFIFO
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
void CounterR2_ClearFIFO(void) 
{

    while(0u != (CounterR2_ReadStatusRegister() & CounterR2_STATUS_FIFONEMP))
    {
        (void)CounterR2_ReadCapture();
    }

}
#endif  /* (!CounterR2_UsingFixedFunction) */


/* [] END OF FILE */

