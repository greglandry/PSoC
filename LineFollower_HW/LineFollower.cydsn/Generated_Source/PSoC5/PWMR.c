/*******************************************************************************
* File Name: PWMR.c  
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
#include "PWMR.h"

uint8 PWMR_initVar = 0u;


/*******************************************************************************
* Function Name: PWMR_Start
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
*  PWMR_initVar: Is modified when this function is called for the 
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void PWMR_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(PWMR_initVar == 0u)
    {
        PWMR_Init();
        PWMR_initVar = 1u;
    }
    PWMR_Enable();

}


/*******************************************************************************
* Function Name: PWMR_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  PWMR_Start().
*
* Parameters:  
*  None
*
* Return: 
*  None
*
*******************************************************************************/
void PWMR_Init(void) 
{
    #if (PWMR_UsingFixedFunction || PWMR_UseControl)
        uint8 ctrl;
    #endif /* (PWMR_UsingFixedFunction || PWMR_UseControl) */
    
    #if(!PWMR_UsingFixedFunction) 
        #if(PWMR_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 PWMR_interruptState;
        #endif /* (PWMR_UseStatus) */
    #endif /* (!PWMR_UsingFixedFunction) */
    
    #if (PWMR_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        PWMR_CONTROL |= PWMR_CFG0_MODE;
        #if (PWMR_DeadBand2_4)
            PWMR_CONTROL |= PWMR_CFG0_DB;
        #endif /* (PWMR_DeadBand2_4) */
                
        ctrl = PWMR_CONTROL3 & ((uint8 )(~PWMR_CTRL_CMPMODE1_MASK));
        PWMR_CONTROL3 = ctrl | PWMR_DEFAULT_COMPARE1_MODE;
        
         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        PWMR_RT1 &= ((uint8)(~PWMR_RT1_MASK));
        PWMR_RT1 |= PWMR_SYNC;     
                
        /*Enable DSI Sync all all inputs of the PWM*/
        PWMR_RT1 &= ((uint8)(~PWMR_SYNCDSI_MASK));
        PWMR_RT1 |= PWMR_SYNCDSI_EN;
       
    #elif (PWMR_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = PWMR_CONTROL & ((uint8)(~PWMR_CTRL_CMPMODE2_MASK)) & ((uint8)(~PWMR_CTRL_CMPMODE1_MASK));
        PWMR_CONTROL = ctrl | PWMR_DEFAULT_COMPARE2_MODE | 
                                   PWMR_DEFAULT_COMPARE1_MODE;
    #endif /* (PWMR_UsingFixedFunction) */
        
    #if (!PWMR_UsingFixedFunction)
        #if (PWMR_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            PWMR_AUX_CONTROLDP0 |= (PWMR_AUX_CTRL_FIFO0_CLR);
        #else /* (PWMR_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            PWMR_AUX_CONTROLDP0 |= (PWMR_AUX_CTRL_FIFO0_CLR);
            PWMR_AUX_CONTROLDP1 |= (PWMR_AUX_CTRL_FIFO0_CLR);
        #endif /* (PWMR_Resolution == 8) */

        PWMR_WriteCounter(PWMR_INIT_PERIOD_VALUE);
    #endif /* (!PWMR_UsingFixedFunction) */
        
    PWMR_WritePeriod(PWMR_INIT_PERIOD_VALUE);

        #if (PWMR_UseOneCompareMode)
            PWMR_WriteCompare(PWMR_INIT_COMPARE_VALUE1);
        #else
            PWMR_WriteCompare1(PWMR_INIT_COMPARE_VALUE1);
            PWMR_WriteCompare2(PWMR_INIT_COMPARE_VALUE2);
        #endif /* (PWMR_UseOneCompareMode) */
        
        #if (PWMR_KillModeMinTime)
            PWMR_WriteKillTime(PWMR_MinimumKillTime);
        #endif /* (PWMR_KillModeMinTime) */
        
        #if (PWMR_DeadBandUsed)
            PWMR_WriteDeadTime(PWMR_INIT_DEAD_TIME);
        #endif /* (PWMR_DeadBandUsed) */

    #if (PWMR_UseStatus || PWMR_UsingFixedFunction)
        PWMR_SetInterruptMode(PWMR_INIT_INTERRUPTS_MODE);
    #endif /* (PWMR_UseStatus || PWMR_UsingFixedFunction) */
        
    #if (PWMR_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        PWMR_GLOBAL_ENABLE |= PWMR_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        PWMR_CONTROL2 |= PWMR_CTRL2_IRQ_SEL;
    #else
        #if(PWMR_UseStatus)
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            PWMR_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            PWMR_STATUS_AUX_CTRL |= PWMR_STATUS_ACTL_INT_EN_MASK;
            
             /* Exit Critical Region*/
            CyExitCriticalSection(PWMR_interruptState);
            
            /* Clear the FIFO to enable the PWMR_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            PWMR_ClearFIFO();
        #endif /* (PWMR_UseStatus) */
    #endif /* (PWMR_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWMR_Enable
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
void PWMR_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (PWMR_UsingFixedFunction)
        PWMR_GLOBAL_ENABLE |= PWMR_BLOCK_EN_MASK;
        PWMR_GLOBAL_STBY_ENABLE |= PWMR_BLOCK_STBY_EN_MASK;
    #endif /* (PWMR_UsingFixedFunction) */
    
    /* Enable the PWM from the control register  */
    #if (PWMR_UseControl || PWMR_UsingFixedFunction)
        PWMR_CONTROL |= PWMR_CTRL_ENABLE;
    #endif /* (PWMR_UseControl || PWMR_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWMR_Stop
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
void PWMR_Stop(void) 
{
    #if (PWMR_UseControl || PWMR_UsingFixedFunction)
        PWMR_CONTROL &= ((uint8)(~PWMR_CTRL_ENABLE));
    #endif /* (PWMR_UseControl || PWMR_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (PWMR_UsingFixedFunction)
        PWMR_GLOBAL_ENABLE &= ((uint8)(~PWMR_BLOCK_EN_MASK));
        PWMR_GLOBAL_STBY_ENABLE &= ((uint8)(~PWMR_BLOCK_STBY_EN_MASK));
    #endif /* (PWMR_UsingFixedFunction) */
}


#if (PWMR_UseOneCompareMode)
	#if (PWMR_CompareMode1SW)


		/*******************************************************************************
		* Function Name: PWMR_SetCompareMode
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
		void PWMR_SetCompareMode(uint8 comparemode) 
		{
		    #if(PWMR_UsingFixedFunction)
            
                #if(0 != PWMR_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << PWMR_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != PWMR_CTRL_CMPMODE1_SHIFT) */
            
	            PWMR_CONTROL3 &= ((uint8)(~PWMR_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
	            PWMR_CONTROL3 |= comparemodemasked;     
		                
		    #elif (PWMR_UseControl)
		        
                #if(0 != PWMR_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << PWMR_CTRL_CMPMODE1_SHIFT)) & 
    		                                    PWMR_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & PWMR_CTRL_CMPMODE1_MASK;                
                #endif /* (0 != PWMR_CTRL_CMPMODE1_SHIFT) */
                
                #if(0 != PWMR_CTRL_CMPMODE2_SHIFT)                            
    		        uint8 comparemode2masked = ((uint8)((uint8)comparemode << PWMR_CTRL_CMPMODE2_SHIFT)) & 
    		                                   PWMR_CTRL_CMPMODE2_MASK;
                #else
    		        uint8 comparemode2masked = comparemode & PWMR_CTRL_CMPMODE2_MASK;                
                #endif /* (0 != PWMR_CTRL_CMPMODE2_SHIFT) */
                
		        /*Clear existing mode */
		        PWMR_CONTROL &= ((uint8)(~(PWMR_CTRL_CMPMODE1_MASK | PWMR_CTRL_CMPMODE2_MASK))); 
		        PWMR_CONTROL |= (comparemode1masked | comparemode2masked);
		        
		    #else
		        uint8 temp = comparemode;
		    #endif /* (PWMR_UsingFixedFunction) */
		}
	#endif /* PWMR_CompareMode1SW */

#else /* UseOneCompareMode */

	#if (PWMR_CompareMode1SW)


		/*******************************************************************************
		* Function Name: PWMR_SetCompareMode1
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
		void PWMR_SetCompareMode1(uint8 comparemode) 
		{
		    #if(0 != PWMR_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << PWMR_CTRL_CMPMODE1_SHIFT)) & 
    		                               PWMR_CTRL_CMPMODE1_MASK;
		    #else
                uint8 comparemodemasked = comparemode & PWMR_CTRL_CMPMODE1_MASK;                
            #endif /* (0 != PWMR_CTRL_CMPMODE1_SHIFT) */
                   
		    #if (PWMR_UseControl)
		        PWMR_CONTROL &= ((uint8)(~PWMR_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
		        PWMR_CONTROL |= comparemodemasked;
		    #endif /* (PWMR_UseControl) */
		}
	#endif /* PWMR_CompareMode1SW */

#if (PWMR_CompareMode2SW)


    /*******************************************************************************
    * Function Name: PWMR_SetCompareMode2
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
    void PWMR_SetCompareMode2(uint8 comparemode) 
    {

        #if(0 != PWMR_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << PWMR_CTRL_CMPMODE2_SHIFT)) & 
                                                 PWMR_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & PWMR_CTRL_CMPMODE2_MASK;            
        #endif /* (0 != PWMR_CTRL_CMPMODE2_SHIFT) */
        
        #if (PWMR_UseControl)
            PWMR_CONTROL &= ((uint8)(~PWMR_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            PWMR_CONTROL |= comparemodemasked;
        #endif /* (PWMR_UseControl) */
    }
    #endif /*PWMR_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!PWMR_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: PWMR_WriteCounter
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
    void PWMR_WriteCounter(uint8 counter) \
                                       
    {
        CY_SET_REG8(PWMR_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: PWMR_ReadCounter
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
    uint8 PWMR_ReadCounter(void) 
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
        (void)PWMR_COUNTERCAP_LSB;
        
        /* Read the data from the FIFO (or capture register for Fixed Function)*/
        return (CY_GET_REG8(PWMR_CAPTURE_LSB_PTR));
    }

        #if (PWMR_UseStatus)


            /*******************************************************************************
            * Function Name: PWMR_ClearFIFO
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
            void PWMR_ClearFIFO(void) 
            {
                while(0u != (PWMR_ReadStatusRegister() & PWMR_STATUS_FIFONEMPTY))
                {
                    (void)PWMR_ReadCapture();
                }
            }

        #endif /* PWMR_UseStatus */

#endif /* !PWMR_UsingFixedFunction */


/*******************************************************************************
* Function Name: PWMR_WritePeriod
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
void PWMR_WritePeriod(uint8 period) 
{
    #if(PWMR_UsingFixedFunction)
        CY_SET_REG16(PWMR_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG8(PWMR_PERIOD_LSB_PTR, period);
    #endif /* (PWMR_UsingFixedFunction) */
}

#if (PWMR_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: PWMR_WriteCompare
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
    void PWMR_WriteCompare(uint8 compare) \
                                       
    {	
		#if(PWMR_UsingFixedFunction)
			CY_SET_REG16(PWMR_COMPARE1_LSB_PTR, (uint16)compare);
		#else
	        CY_SET_REG8(PWMR_COMPARE1_LSB_PTR, compare);	
		#endif /* (PWMR_UsingFixedFunction) */
        
        #if (PWMR_PWMMode == PWMR__B_PWM__DITHER)
            #if(PWMR_UsingFixedFunction)
    			CY_SET_REG16(PWMR_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
    		#else
    	        CY_SET_REG8(PWMR_COMPARE2_LSB_PTR, (compare + 1u));	
    		#endif /* (PWMR_UsingFixedFunction) */
        #endif /* (PWMR_PWMMode == PWMR__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: PWMR_WriteCompare1
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
    void PWMR_WriteCompare1(uint8 compare) \
                                        
    {
        #if(PWMR_UsingFixedFunction)
            CY_SET_REG16(PWMR_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG8(PWMR_COMPARE1_LSB_PTR, compare);
        #endif /* (PWMR_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: PWMR_WriteCompare2
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
    void PWMR_WriteCompare2(uint8 compare) \
                                        
    {
        #if(PWMR_UsingFixedFunction)
            CY_SET_REG16(PWMR_COMPARE2_LSB_PTR, compare);
        #else
            CY_SET_REG8(PWMR_COMPARE2_LSB_PTR, compare);
        #endif /* (PWMR_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (PWMR_DeadBandUsed)


    /*******************************************************************************
    * Function Name: PWMR_WriteDeadTime
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
    void PWMR_WriteDeadTime(uint8 deadtime) 
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!PWMR_DeadBand2_4)
            CY_SET_REG8(PWMR_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */        
            /* Clear existing data */
            PWMR_DEADBAND_COUNT &= ((uint8)(~PWMR_DEADBAND_COUNT_MASK));
            
            /* Set new dead time */
            #if(PWMR_DEADBAND_COUNT_SHIFT)        
                PWMR_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << PWMR_DEADBAND_COUNT_SHIFT)) & 
                                                    PWMR_DEADBAND_COUNT_MASK;
            #else
                PWMR_DEADBAND_COUNT |= deadtime & PWMR_DEADBAND_COUNT_MASK;        
            #endif /* (PWMR_DEADBAND_COUNT_SHIFT) */
        
        #endif /* (!PWMR_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: PWMR_ReadDeadTime
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
    uint8 PWMR_ReadDeadTime(void) 
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!PWMR_DeadBand2_4)
            return (CY_GET_REG8(PWMR_DEADBAND_COUNT_PTR));
        #else
        
            /* Otherwise the data has to be masked and offset */
            #if(PWMR_DEADBAND_COUNT_SHIFT)      
                return ((uint8)(((uint8)(PWMR_DEADBAND_COUNT & PWMR_DEADBAND_COUNT_MASK)) >> 
                                                                           PWMR_DEADBAND_COUNT_SHIFT));
            #else
                return (PWMR_DEADBAND_COUNT & PWMR_DEADBAND_COUNT_MASK);
            #endif /* (PWMR_DEADBAND_COUNT_SHIFT) */
        #endif /* (!PWMR_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (PWMR_UseStatus || PWMR_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: PWMR_SetInterruptMode
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
    void PWMR_SetInterruptMode(uint8 interruptMode)  
    {
    	CY_SET_REG8(PWMR_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: PWMR_ReadStatusRegister
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
    uint8 PWMR_ReadStatusRegister(void)   
    {
    	uint8 result;
    	
    	result = CY_GET_REG8(PWMR_STATUS_PTR);
    	return (result);
    }

#endif /* (PWMR_UseStatus || PWMR_UsingFixedFunction) */


#if (PWMR_UseControl)


    /*******************************************************************************
    * Function Name: PWMR_ReadControlRegister
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
    uint8 PWMR_ReadControlRegister(void) 
    {
    	uint8 result;
    	
    	result = CY_GET_REG8(PWMR_CONTROL_PTR);
    	return (result);
    }


    /*******************************************************************************
    * Function Name: PWMR_WriteControlRegister
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
    void PWMR_WriteControlRegister(uint8 control) 
    {
    	CY_SET_REG8(PWMR_CONTROL_PTR, control);
    }
	
#endif /* (PWMR_UseControl) */


#if (!PWMR_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: PWMR_ReadCapture
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
    uint8 PWMR_ReadCapture(void)  
    {
    	return (CY_GET_REG8(PWMR_CAPTURE_LSB_PTR));
    }
	
#endif /* (!PWMR_UsingFixedFunction) */


#if (PWMR_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: PWMR_ReadCompare
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
    uint8 PWMR_ReadCompare(void)  
    {
		#if(PWMR_UsingFixedFunction)
            return ((uint8)CY_GET_REG16(PWMR_COMPARE1_LSB_PTR));
        #else
            return (CY_GET_REG8(PWMR_COMPARE1_LSB_PTR));
        #endif /* (PWMR_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: PWMR_ReadCompare1
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
    uint8 PWMR_ReadCompare1(void) 
    {
		return (CY_GET_REG8(PWMR_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: PWMR_ReadCompare2
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
    uint8 PWMR_ReadCompare2(void)  
    {
		return (CY_GET_REG8(PWMR_COMPARE2_LSB_PTR));
    }

#endif /* (PWMR_UseOneCompareMode) */


/*******************************************************************************
* Function Name: PWMR_ReadPeriod
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
uint8 PWMR_ReadPeriod(void) 
{
	#if(PWMR_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(PWMR_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG8(PWMR_PERIOD_LSB_PTR));
    #endif /* (PWMR_UsingFixedFunction) */
}

#if ( PWMR_KillModeMinTime)


    /*******************************************************************************
    * Function Name: PWMR_WriteKillTime
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
    void PWMR_WriteKillTime(uint8 killtime) 
    {
    	CY_SET_REG8(PWMR_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: PWMR_ReadKillTime
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
    uint8 PWMR_ReadKillTime(void) 
    {
    	return (CY_GET_REG8(PWMR_KILLMODEMINTIME_PTR));
    }

#endif /* ( PWMR_KillModeMinTime) */

/* [] END OF FILE */
