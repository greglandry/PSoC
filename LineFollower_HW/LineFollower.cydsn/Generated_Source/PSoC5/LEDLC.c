/*******************************************************************************
* File Name: LEDLC.c  
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
#include "LEDLC.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 LEDLC__PORT == 15 && ((LEDLC__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: LEDLC_Write
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
void LEDLC_Write(uint8 value) 
{
    uint8 staticBits = (LEDLC_DR & (uint8)(~LEDLC_MASK));
    LEDLC_DR = staticBits | ((uint8)(value << LEDLC_SHIFT) & LEDLC_MASK);
}


/*******************************************************************************
* Function Name: LEDLC_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  LEDLC_DM_STRONG     Strong Drive 
*  LEDLC_DM_OD_HI      Open Drain, Drives High 
*  LEDLC_DM_OD_LO      Open Drain, Drives Low 
*  LEDLC_DM_RES_UP     Resistive Pull Up 
*  LEDLC_DM_RES_DWN    Resistive Pull Down 
*  LEDLC_DM_RES_UPDWN  Resistive Pull Up/Down 
*  LEDLC_DM_DIG_HIZ    High Impedance Digital 
*  LEDLC_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void LEDLC_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(LEDLC_0, mode);
}


/*******************************************************************************
* Function Name: LEDLC_Read
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
*  Macro LEDLC_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 LEDLC_Read(void) 
{
    return (LEDLC_PS & LEDLC_MASK) >> LEDLC_SHIFT;
}


/*******************************************************************************
* Function Name: LEDLC_ReadDataReg
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
uint8 LEDLC_ReadDataReg(void) 
{
    return (LEDLC_DR & LEDLC_MASK) >> LEDLC_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(LEDLC_INTSTAT) 

    /*******************************************************************************
    * Function Name: LEDLC_ClearInterrupt
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
    uint8 LEDLC_ClearInterrupt(void) 
    {
        return (LEDLC_INTSTAT & LEDLC_MASK) >> LEDLC_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
