/*******************************************************************************
* File Name: LEDC.c  
* Version 2.5
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "LEDC.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 LEDC__PORT == 15 && ((LEDC__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: LEDC_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None
*  
*******************************************************************************/
void LEDC_Write(uint8 value) 
{
    uint8 staticBits = (LEDC_DR & (uint8)(~LEDC_MASK));
    LEDC_DR = staticBits | ((uint8)(value << LEDC_SHIFT) & LEDC_MASK);
}


/*******************************************************************************
* Function Name: LEDC_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  LEDC_DM_STRONG     Strong Drive 
*  LEDC_DM_OD_HI      Open Drain, Drives High 
*  LEDC_DM_OD_LO      Open Drain, Drives Low 
*  LEDC_DM_RES_UP     Resistive Pull Up 
*  LEDC_DM_RES_DWN    Resistive Pull Down 
*  LEDC_DM_RES_UPDWN  Resistive Pull Up/Down 
*  LEDC_DM_DIG_HIZ    High Impedance Digital 
*  LEDC_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void LEDC_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(LEDC_0, mode);
}


/*******************************************************************************
* Function Name: LEDC_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro LEDC_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 LEDC_Read(void) 
{
    return (LEDC_PS & LEDC_MASK) >> LEDC_SHIFT;
}


/*******************************************************************************
* Function Name: LEDC_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 LEDC_ReadDataReg(void) 
{
    return (LEDC_DR & LEDC_MASK) >> LEDC_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(LEDC_INTSTAT) 

    /*******************************************************************************
    * Function Name: LEDC_ClearInterrupt
    ********************************************************************************
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 LEDC_ClearInterrupt(void) 
    {
        return (LEDC_INTSTAT & LEDC_MASK) >> LEDC_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
