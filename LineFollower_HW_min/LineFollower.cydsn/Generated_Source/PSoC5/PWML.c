/*******************************************************************************
* File Name: PWML.c  
* Version 3.0
*
* Description:
*  The PWM User Module consist of an 8 or 16-bit counter with two 8 or 16-bit
*  comparitors. Each instance of this user module is capable of generating
*  two PWM outputs with the same period. The pulse width is selectable between
*  1 and 255/65535. The period is selectable between 2 and 255/65536 clocks. 
*  The compare value output may be configured to be active when the present 
*  counter is less than or less than/equal to the compare value.
*  A terminal count output is also provided. It generates a pulse one clock
*  width wide when the counter is equal to zero.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "cytypes.h"
#include "PWML.h"

uint8 PWML_initVar = 0u;


/*******************************************************************************
* Function Name: PWML_Start
********************************************************************************
*
* Summary:
*  The start function initializes the pwm with the default values, the 
*  enables the counter to begin counting.  It does not enable interrupts,
*  the EnableInt command should be called if interrupt generation is required.
*
* Parameters:  
*  None  
*
* Return: 
*  None
*
* Global variables:
*  PWML_initVar: Is modified when this function is called for the 
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void PWML_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(PWML_initVar == 0u)
    {
        PWML_Init();
        PWML_initVar = 1u;
    }
    PWML_Enable();

}


/*******************************************************************************
* Function Name: PWML_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  PWML_Start().
*
* Parameters:  
*  None
*
* Return: 
*  None
*
*******************************************************************************/
void PWML_Init(void) 
{
    #if (PWML_UsingFixedFunction || PWML_UseControl)
        uint8 ctrl;
    #endif /* (PWML_UsingFixedFunction || PWML_UseControl) */
    
    #if(!PWML_UsingFixedFunction) 
        #if(PWML_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 PWML_interruptState;
        #endif /* (PWML_UseStatus) */
    #endif /* (!PWML_UsingFixedFunction) */
    
    #if (PWML_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        PWML_CONTROL |= PWML_CFG0_MODE;
        #if (PWML_DeadBand2_4)
            PWML_CONTROL |= PWML_CFG0_DB;
        #endif /* (PWML_DeadBand2_4) */
                
        ctrl = PWML_CONTROL3 & ((uint8 )(~PWML_CTRL_CMPMODE1_MASK));
        PWML_CONTROL3 = ctrl | PWML_DEFAULT_COMPARE1_MODE;
        
         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        PWML_RT1 &= ((uint8)(~PWML_RT1_MASK));
        PWML_RT1 |= PWML_SYNC;     
                
        /*Enable DSI Sync all all inputs of the PWM*/
        PWML_RT1 &= ((uint8)(~PWML_SYNCDSI_MASK));
        PWML_RT1 |= PWML_SYNCDSI_EN;
       
    #elif (PWML_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = PWML_CONTROL & ((uint8)(~PWML_CTRL_CMPMODE2_MASK)) & ((uint8)(~PWML_CTRL_CMPMODE1_MASK));
        PWML_CONTROL = ctrl | PWML_DEFAULT_COMPARE2_MODE | 
                                   PWML_DEFAULT_COMPARE1_MODE;
    #endif /* (PWML_UsingFixedFunction) */
        
    #if (!PWML_UsingFixedFunction)
        #if (PWML_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            PWML_AUX_CONTROLDP0 |= (PWML_AUX_CTRL_FIFO0_CLR);
        #else /* (PWML_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            PWML_AUX_CONTROLDP0 |= (PWML_AUX_CTRL_FIFO0_CLR);
            PWML_AUX_CONTROLDP1 |= (PWML_AUX_CTRL_FIFO0_CLR);
        #endif /* (PWML_Resolution == 8) */

        PWML_WriteCounter(PWML_INIT_PERIOD_VALUE);
    #endif /* (!PWML_UsingFixedFunction) */
        
    PWML_WritePeriod(PWML_INIT_PERIOD_VALUE);

        #if (PWML_UseOneCompareMode)
            PWML_WriteCompare(PWML_INIT_COMPARE_VALUE1);
        #else
            PWML_WriteCompare1(PWML_INIT_COMPARE_VALUE1);
            PWML_WriteCompare2(PWML_INIT_COMPARE_VALUE2);
        #endif /* (PWML_UseOneCompareMode) */
        
        #if (PWML_KillModeMinTime)
            PWML_WriteKillTime(PWML_MinimumKillTime);
        #endif /* (PWML_KillModeMinTime) */
        
        #if (PWML_DeadBandUsed)
            PWML_WriteDeadTime(PWML_INIT_DEAD_TIME);
        #endif /* (PWML_DeadBandUsed) */

    #if (PWML_UseStatus || PWML_UsingFixedFunction)
        PWML_SetInterruptMode(PWML_INIT_INTERRUPTS_MODE);
    #endif /* (PWML_UseStatus || PWML_UsingFixedFunction) */
        
    #if (PWML_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        PWML_GLOBAL_ENABLE |= PWML_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        PWML_CONTROL2 |= PWML_CTRL2_IRQ_SEL;
    #else
        #if(PWML_UseStatus)
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            PWML_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            PWML_STATUS_AUX_CTRL |= PWML_STATUS_ACTL_INT_EN_MASK;
            
             /* Exit Critical Region*/
            CyExitCriticalSection(PWML_interruptState);
            
            /* Clear the FIFO to enable the PWML_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            PWML_ClearFIFO();
        #endif /* (PWML_UseStatus) */
    #endif /* (PWML_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWML_Enable
********************************************************************************
*
* Summary: 
*  Enables the PWM block operation
*
* Parameters:  
*  None
*
* Return: 
*  None
*
* Side Effects: 
*  This works only if software enable mode is chosen
*
*******************************************************************************/
void PWML_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (PWML_UsingFixedFunction)
        PWML_GLOBAL_ENABLE |= PWML_BLOCK_EN_MASK;
        PWML_GLOBAL_STBY_ENABLE |= PWML_BLOCK_STBY_EN_MASK;
    #endif /* (PWML_UsingFixedFunction) */
    
    /* Enable the PWM from the control register  */
    #if (PWML_UseControl || PWML_UsingFixedFunction)
        PWML_CONTROL |= PWML_CTRL_ENABLE;
    #endif /* (PWML_UseControl || PWML_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWML_Stop
********************************************************************************
*
* Summary:
*  The stop function halts the PWM, but does not change any modes or disable
*  interrupts.
*
* Parameters:  
*  None  
*
* Return: 
*  None
*
* Side Effects:
*  If the Enable mode is set to Hardware only then this function
*  has no effect on the operation of the PWM
*
*******************************************************************************/
void PWML_Stop(void) 
{
    #if (PWML_UseControl || PWML_UsingFixedFunction)
        PWML_CONTROL &= ((uint8)(~PWML_CTRL_ENABLE));
    #endif /* (PWML_UseControl || PWML_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (PWML_UsingFixedFunction)
        PWML_GLOBAL_ENABLE &= ((uint8)(~PWML_BLOCK_EN_MASK));
        PWML_GLOBAL_STBY_ENABLE &= ((uint8)(~PWML_BLOCK_STBY_EN_MASK));
    #endif /* (PWML_UsingFixedFunction) */
}


#if (PWML_UseOneCompareMode)
	#if (PWML_CompareMode1SW)


		/*******************************************************************************
		* Function Name: PWML_SetCompareMode
		********************************************************************************
		* 
		* Summary:
		*  This function writes the Compare Mode for the pwm output when in Dither mode,
		*  Center Align Mode or One Output Mode.
		*
		* Parameters:
		*  comparemode:  The new compare mode for the PWM output. Use the compare types
		*                defined in the H file as input arguments.
		*
		* Return:
		*  None
		*
		*******************************************************************************/
		void PWML_SetCompareMode(uint8 comparemode) 
		{
		    #if(PWML_UsingFixedFunction)
            
                #if(0 != PWML_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << PWML_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != PWML_CTRL_CMPMODE1_SHIFT) */
            
	            PWML_CONTROL3 &= ((uint8)(~PWML_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
	            PWML_CONTROL3 |= comparemodemasked;     
		                
		    #elif (PWML_UseControl)
		        
                #if(0 != PWML_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << PWML_CTRL_CMPMODE1_SHIFT)) & 
    		                                    PWML_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & PWML_CTRL_CMPMODE1_MASK;                
                #endif /* (0 != PWML_CTRL_CMPMODE1_SHIFT) */
                
                #if(0 != PWML_CTRL_CMPMODE2_SHIFT)                            
    		        uint8 comparemode2masked = ((uint8)((uint8)comparemode << PWML_CTRL_CMPMODE2_SHIFT)) & 
    		                                   PWML_CTRL_CMPMODE2_MASK;
                #else
    		        uint8 comparemode2masked = comparemode & PWML_CTRL_CMPMODE2_MASK;                
                #endif /* (0 != PWML_CTRL_CMPMODE2_SHIFT) */
                
		        /*Clear existing mode */
		        PWML_CONTROL &= ((uint8)(~(PWML_CTRL_CMPMODE1_MASK | PWML_CTRL_CMPMODE2_MASK))); 
		        PWML_CONTROL |= (comparemode1masked | comparemode2masked);
		        
		    #else
		        uint8 temp = comparemode;
		    #endif /* (PWML_UsingFixedFunction) */
		}
	#endif /* PWML_CompareMode1SW */

#else /* UseOneCompareMode */

	#if (PWML_CompareMode1SW)


		/*******************************************************************************
		* Function Name: PWML_SetCompareMode1
		********************************************************************************
		* 
		* Summary:
		*  This function writes the Compare Mode for the pwm or pwm1 output
		*
		* Parameters:  
		*  comparemode:  The new compare mode for the PWM output. Use the compare types
		*                defined in the H file as input arguments.
		*
		* Return: 
		*  None
		*
		*******************************************************************************/
		void PWML_SetCompareMode1(uint8 comparemode) 
		{
		    #if(0 != PWML_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << PWML_CTRL_CMPMODE1_SHIFT)) & 
    		                               PWML_CTRL_CMPMODE1_MASK;
		    #else
                uint8 comparemodemasked = comparemode & PWML_CTRL_CMPMODE1_MASK;                
            #endif /* (0 != PWML_CTRL_CMPMODE1_SHIFT) */
                   
		    #if (PWML_UseControl)
		        PWML_CONTROL &= ((uint8)(~PWML_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
		        PWML_CONTROL |= comparemodemasked;
		    #endif /* (PWML_UseControl) */
		}
	#endif /* PWML_CompareMode1SW */

#if (PWML_CompareMode2SW)


    /*******************************************************************************
    * Function Name: PWML_SetCompareMode2
    ********************************************************************************
    * 
    * Summary:
    *  This function writes the Compare Mode for the pwm or pwm2 output
    *
    * Parameters:  
    *  comparemode:  The new compare mode for the PWM output. Use the compare types
    *                defined in the H file as input arguments.
    *
    * Return: 
    *  None
    *
    *******************************************************************************/
    void PWML_SetCompareMode2(uint8 comparemode) 
    {

        #if(0 != PWML_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << PWML_CTRL_CMPMODE2_SHIFT)) & 
                                                 PWML_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & PWML_CTRL_CMPMODE2_MASK;            
        #endif /* (0 != PWML_CTRL_CMPMODE2_SHIFT) */
        
        #if (PWML_UseControl)
            PWML_CONTROL &= ((uint8)(~PWML_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            PWML_CONTROL |= comparemodemasked;
        #endif /* (PWML_UseControl) */
    }
    #endif /*PWML_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!PWML_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: PWML_WriteCounter
    ********************************************************************************
    * 
    * Summary:
    *  Writes a new counter value directly to the counter register. This will be 
    *  implemented for that currently running period and only that period. This API 
    *  is valid only for UDB implementation and not available for fixed function 
    *  PWM implementation.    
    *
    * Parameters:  
    *  counter:  The period new period counter value.
    *
    * Return: 
    *  None
    *
    * Side Effects: 
    *  The PWM Period will be reloaded when a counter value will be a zero
    *
    *******************************************************************************/
    void PWML_WriteCounter(uint8 counter) \
                                       
    {
        CY_SET_REG8(PWML_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: PWML_ReadCounter
    ********************************************************************************
    * 
    * Summary:
    *  This function returns the current value of the counter.  It doesn't matter
    *  if the counter is enabled or running.
    *
    * Parameters:  
    *  None  
    *
    * Return: 
    *  The current value of the counter.
    *
    *******************************************************************************/
    uint8 PWML_ReadCounter(void) 
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
        (void)PWML_COUNTERCAP_LSB;
        
        /* Read the data from the FIFO (or capture register for Fixed Function)*/
        return (CY_GET_REG8(PWML_CAPTURE_LSB_PTR));
    }

        #if (PWML_UseStatus)


            /*******************************************************************************
            * Function Name: PWML_ClearFIFO
            ********************************************************************************
            * 
            * Summary:
            *  This function clears all capture data from the capture FIFO
            *
            * Parameters:  
            *  None
            *
            * Return: 
            *  None
            *
            *******************************************************************************/
            void PWML_ClearFIFO(void) 
            {
                while(0u != (PWML_ReadStatusRegister() & PWML_STATUS_FIFONEMPTY))
                {
                    (void)PWML_ReadCapture();
                }
            }

        #endif /* PWML_UseStatus */

#endif /* !PWML_UsingFixedFunction */


/*******************************************************************************
* Function Name: PWML_WritePeriod
********************************************************************************
* 
* Summary:
*  This function is used to change the period of the counter.  The new period 
*  will be loaded the next time terminal count is detected.
*
* Parameters:  
*  period:  Period value. May be between 1 and (2^Resolution)-1.  A value of 0 
*           will result in the counter remaining at zero.
*
* Return: 
*  None
*
*******************************************************************************/
void PWML_WritePeriod(uint8 period) 
{
    #if(PWML_UsingFixedFunction)
        CY_SET_REG16(PWML_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG8(PWML_PERIOD_LSB_PTR, period);
    #endif /* (PWML_UsingFixedFunction) */
}

#if (PWML_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: PWML_WriteCompare
    ********************************************************************************
    * 
    * Summary:
    *  This funtion is used to change the compare1 value when the PWM is in Dither
    *  mode. The compare output will reflect the new value on the next UDB clock. 
    *  The compare output will be driven high when the present counter value is 
    *  compared to the compare value based on the compare mode defined in 
    *  Dither Mode.
    *
    * Parameters:  
    *  compare:  New compare value.  
    *
    * Return: 
    *  None
    *
    * Side Effects:
    *  This function is only available if the PWM mode parameter is set to
    *  Dither Mode, Center Aligned Mode or One Output Mode
    *
    *******************************************************************************/
    void PWML_WriteCompare(uint8 compare) \
                                       
    {	
		#if(PWML_UsingFixedFunction)
			CY_SET_REG16(PWML_COMPARE1_LSB_PTR, (uint16)compare);
		#else
	        CY_SET_REG8(PWML_COMPARE1_LSB_PTR, compare);	
		#endif /* (PWML_UsingFixedFunction) */
        
        #if (PWML_PWMMode == PWML__B_PWM__DITHER)
            #if(PWML_UsingFixedFunction)
    			CY_SET_REG16(PWML_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
    		#else
    	        CY_SET_REG8(PWML_COMPARE2_LSB_PTR, (compare + 1u));	
    		#endif /* (PWML_UsingFixedFunction) */
        #endif /* (PWML_PWMMode == PWML__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: PWML_WriteCompare1
    ********************************************************************************
    * 
    * Summary:
    *  This funtion is used to change the compare1 value.  The compare output will 
    *  reflect the new value on the next UDB clock.  The compare output will be 
    *  driven high when the present counter value is less than or less than or 
    *  equal to the compare register, depending on the mode.
    *
    * Parameters:  
    *  compare:  New compare value.  
    *
    * Return: 
    *  None
    *
    *******************************************************************************/
    void PWML_WriteCompare1(uint8 compare) \
                                        
    {
        #if(PWML_UsingFixedFunction)
            CY_SET_REG16(PWML_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG8(PWML_COMPARE1_LSB_PTR, compare);
        #endif /* (PWML_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: PWML_WriteCompare2
    ********************************************************************************
    * 
    * Summary:
    *  This funtion is used to change the compare value, for compare1 output.  
    *  The compare output will reflect the new value on the next UDB clock.  
    *  The compare output will be driven high when the present counter value is 
    *  less than or less than or equal to the compare register, depending on the 
    *  mode.
    *
    * Parameters:  
    *  compare:  New compare value.  
    *
    * Return: 
    *  None
    *
    *******************************************************************************/
    void PWML_WriteCompare2(uint8 compare) \
                                        
    {
        #if(PWML_UsingFixedFunction)
            CY_SET_REG16(PWML_COMPARE2_LSB_PTR, compare);
        #else
            CY_SET_REG8(PWML_COMPARE2_LSB_PTR, compare);
        #endif /* (PWML_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (PWML_DeadBandUsed)


    /*******************************************************************************
    * Function Name: PWML_WriteDeadTime
    ********************************************************************************
    * 
    * Summary:
    *  This function writes the dead-band counts to the corresponding register
    *
    * Parameters:  
    *  deadtime:  Number of counts for dead time 
    *
    * Return: 
    *  None
    *
    *******************************************************************************/
    void PWML_WriteDeadTime(uint8 deadtime) 
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!PWML_DeadBand2_4)
            CY_SET_REG8(PWML_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */        
            /* Clear existing data */
            PWML_DEADBAND_COUNT &= ((uint8)(~PWML_DEADBAND_COUNT_MASK));
            
            /* Set new dead time */
            #if(PWML_DEADBAND_COUNT_SHIFT)        
                PWML_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << PWML_DEADBAND_COUNT_SHIFT)) & 
                                                    PWML_DEADBAND_COUNT_MASK;
            #else
                PWML_DEADBAND_COUNT |= deadtime & PWML_DEADBAND_COUNT_MASK;        
            #endif /* (PWML_DEADBAND_COUNT_SHIFT) */
        
        #endif /* (!PWML_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: PWML_ReadDeadTime
    ********************************************************************************
    * 
    * Summary:
    *  This function reads the dead-band counts from the corresponding register
    *
    * Parameters:  
    *  None
    *
    * Return: 
    *  Dead Band Counts
    *
    *******************************************************************************/
    uint8 PWML_ReadDeadTime(void) 
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!PWML_DeadBand2_4)
            return (CY_GET_REG8(PWML_DEADBAND_COUNT_PTR));
        #else
        
            /* Otherwise the data has to be masked and offset */
            #if(PWML_DEADBAND_COUNT_SHIFT)      
                return ((uint8)(((uint8)(PWML_DEADBAND_COUNT & PWML_DEADBAND_COUNT_MASK)) >> 
                                                                           PWML_DEADBAND_COUNT_SHIFT));
            #else
                return (PWML_DEADBAND_COUNT & PWML_DEADBAND_COUNT_MASK);
            #endif /* (PWML_DEADBAND_COUNT_SHIFT) */
        #endif /* (!PWML_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (PWML_UseStatus || PWML_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: PWML_SetInterruptMode
    ********************************************************************************
    * 
    * Summary:
    *  This function configures the interrupts mask control of theinterrupt 
    *  source status register.
    *
    * Parameters:  
    *  uint8 interruptMode: Bit field containing the interrupt sources enabled 
    *
    * Return: 
    *  None
    *
    *******************************************************************************/
    void PWML_SetInterruptMode(uint8 interruptMode)  
    {
    	CY_SET_REG8(PWML_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: PWML_ReadStatusRegister
    ********************************************************************************
    * 
    * Summary:
    *  This function returns the current state of the status register. 
    *
    * Parameters:  
    *  None
    *
    * Return: 
    *  uint8 : Current status register value. The status register bits are:
    *  [7:6] : Unused(0)
    *  [5]   : Kill event output
    *  [4]   : FIFO not empty
    *  [3]   : FIFO full
    *  [2]   : Terminal count
    *  [1]   : Compare output 2
    *  [0]   : Compare output 1
    *
    *******************************************************************************/
    uint8 PWML_ReadStatusRegister(void)   
    {
    	uint8 result;
    	
    	result = CY_GET_REG8(PWML_STATUS_PTR);
    	return (result);
    }

#endif /* (PWML_UseStatus || PWML_UsingFixedFunction) */


#if (PWML_UseControl)


    /*******************************************************************************
    * Function Name: PWML_ReadControlRegister
    ********************************************************************************
    * 
    * Summary:
    *  Returns the current state of the control register. This API is available 
    *  only if the control register is not removed.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  uint8 : Current control register value
    *
    *******************************************************************************/    
    uint8 PWML_ReadControlRegister(void) 
    {
    	uint8 result;
    	
    	result = CY_GET_REG8(PWML_CONTROL_PTR);
    	return (result);
    }


    /*******************************************************************************
    * Function Name: PWML_WriteControlRegister
    ********************************************************************************
    * 
    * Summary:
    *  Sets the bit field of the control register. This API is available only if 
    *  the control register is not removed.
    *
    * Parameters:  
    *  uint8 control: Control register bit field, The status register bits are:
    *  [7]   : PWM Enable
    *  [6]   : Reset
    *  [5:3] : Compare Mode2
    *  [2:0] : Compare Mode2
    *
    * Return: 
    *  None
    *
    *******************************************************************************/  
    void PWML_WriteControlRegister(uint8 control) 
    {
    	CY_SET_REG8(PWML_CONTROL_PTR, control);
    }
	
#endif /* (PWML_UseControl) */


#if (!PWML_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: PWML_ReadCapture
    ********************************************************************************
    * 
    * Summary:
    *  Reads the capture value from the capture FIFO.
    *
    * Parameters:  
    *  None
    *
    * Return: 
    *  uint8/uint16: The current capture value
    *
    *******************************************************************************/  
    uint8 PWML_ReadCapture(void)  
    {
    	return (CY_GET_REG8(PWML_CAPTURE_LSB_PTR));
    }
	
#endif /* (!PWML_UsingFixedFunction) */


#if (PWML_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: PWML_ReadCompare
    ********************************************************************************
    * 
    * Summary:
    *  Reads the compare value for the compare output when the PWM Mode parameter is 
    *  set to Dither mode, Center Aligned mode, or One Output mode.
    *
    * Parameters:  
    *  None
    *
    * Return: 
    *  uint8/uint16: Current compare value
    *
    *******************************************************************************/  
    uint8 PWML_ReadCompare(void)  
    {
		#if(PWML_UsingFixedFunction)
            return ((uint8)CY_GET_REG16(PWML_COMPARE1_LSB_PTR));
        #else
            return (CY_GET_REG8(PWML_COMPARE1_LSB_PTR));
        #endif /* (PWML_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: PWML_ReadCompare1
    ********************************************************************************
    * 
    * Summary:
    *  Reads the compare value for the compare1 output.
    *
    * Parameters:  
    *  None
    *
    * Return: 
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/  
    uint8 PWML_ReadCompare1(void) 
    {
		return (CY_GET_REG8(PWML_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: PWML_ReadCompare2
    ********************************************************************************
    * 
    * Summary:
    *  Reads the compare value for the compare2 output.
    *
    * Parameters:  
    *  None
    *
    * Return: 
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/  
    uint8 PWML_ReadCompare2(void)  
    {
		return (CY_GET_REG8(PWML_COMPARE2_LSB_PTR));
    }

#endif /* (PWML_UseOneCompareMode) */


/*******************************************************************************
* Function Name: PWML_ReadPeriod
********************************************************************************
* 
* Summary:
*  Reads the period value used by the PWM hardware.
*
* Parameters:  
*  None
*
* Return: 
*  uint8/16: Period value
*
*******************************************************************************/ 
uint8 PWML_ReadPeriod(void) 
{
	#if(PWML_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(PWML_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG8(PWML_PERIOD_LSB_PTR));
    #endif /* (PWML_UsingFixedFunction) */
}

#if ( PWML_KillModeMinTime)


    /*******************************************************************************
    * Function Name: PWML_WriteKillTime
    ********************************************************************************
    * 
    * Summary:
    *  Writes the kill time value used by the hardware when the Kill Mode 
    *  is set to Minimum Time.
    *
    * Parameters:  
    *  uint8: Minimum Time kill counts
    *
    * Return: 
    *  None
    *
    *******************************************************************************/ 
    void PWML_WriteKillTime(uint8 killtime) 
    {
    	CY_SET_REG8(PWML_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: PWML_ReadKillTime
    ********************************************************************************
    * 
    * Summary:
    *  Reads the kill time value used by the hardware when the Kill Mode is set 
    *  to Minimum Time.
    *
    * Parameters:  
    *  None
    *
    * Return: 
    *  uint8: The current Minimum Time kill counts
    *
    *******************************************************************************/ 
    uint8 PWML_ReadKillTime(void) 
    {
    	return (CY_GET_REG8(PWML_KILLMODEMINTIME_PTR));
    }

#endif /* ( PWML_KillModeMinTime) */

/* [] END OF FILE */
