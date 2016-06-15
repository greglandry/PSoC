/*******************************************************************************
* File Name: LEDRC.c  
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
#include "LEDRC.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 LEDRC__PORT == 15 && ((LEDRC__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: LEDRC_Write
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
void LEDRC_Write(uint8 value) 
{
    uint8 staticBits = (LEDRC_DR & (uint8)(~LEDRC_MASK));
    LEDRC_DR = staticBits | ((uint8)(value << LEDRC_SHIFT) & LEDRC_MASK);
}


/*******************************************************************************
* Function Name: LEDRC_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  LEDRC_DM_STRONG     Strong Drive 
*  LEDRC_DM_OD_HI      Open Drain, Drives High 
*  LEDRC_DM_OD_LO      Open Drain, Drives Low 
*  LEDRC_DM_RES_UP     Resistive Pull Up 
*  LEDRC_DM_RES_DWN    Resistive Pull Down 
*  LEDRC_DM_RES_UPDWN  Resistive Pull Up/Down 
*  LEDRC_DM_DIG_HIZ    High Impedance Digital 
*  LEDRC_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void LEDRC_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(LEDRC_0, mode);
}


/*******************************************************************************
* Function Name: LEDRC_Read
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
*  Macro LEDRC_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 LEDRC_Read(void) 
{
    return (LEDRC_PS & LEDRC_MASK) >> LEDRC_SHIFT;
}


/*******************************************************************************
* Function Name: LEDRC_ReadDataReg
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
uint8 LEDRC_ReadDataReg(void) 
{
    return (LEDRC_DR & LEDRC_MASK) >> LEDRC_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(LEDRC_INTSTAT) 

    /*******************************************************************************
    * Function Name: LEDRC_ClearInterrupt
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
    uint8 LEDRC_ClearInterrupt(void) 
    {
        return (LEDRC_INTSTAT & LEDRC_MASK) >> LEDRC_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
