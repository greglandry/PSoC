/*******************************************************************************
* File Name: QuadB.c  
* Version 2.0
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
#include "QuadB.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 QuadB__PORT == 15 && ((QuadB__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: QuadB_Write
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
void QuadB_Write(uint8 value) 
{
    uint8 staticBits = (QuadB_DR & (uint8)(~QuadB_MASK));
    QuadB_DR = staticBits | ((uint8)(value << QuadB_SHIFT) & QuadB_MASK);
}


/*******************************************************************************
* Function Name: QuadB_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  QuadB_DM_STRONG     Strong Drive 
*  QuadB_DM_OD_HI      Open Drain, Drives High 
*  QuadB_DM_OD_LO      Open Drain, Drives Low 
*  QuadB_DM_RES_UP     Resistive Pull Up 
*  QuadB_DM_RES_DWN    Resistive Pull Down 
*  QuadB_DM_RES_UPDWN  Resistive Pull Up/Down 
*  QuadB_DM_DIG_HIZ    High Impedance Digital 
*  QuadB_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void QuadB_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(QuadB_0, mode);
}


/*******************************************************************************
* Function Name: QuadB_Read
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
*  Macro QuadB_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 QuadB_Read(void) 
{
    return (QuadB_PS & QuadB_MASK) >> QuadB_SHIFT;
}


/*******************************************************************************
* Function Name: QuadB_ReadDataReg
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
uint8 QuadB_ReadDataReg(void) 
{
    return (QuadB_DR & QuadB_MASK) >> QuadB_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(QuadB_INTSTAT) 

    /*******************************************************************************
    * Function Name: QuadB_ClearInterrupt
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
    uint8 QuadB_ClearInterrupt(void) 
    {
        return (QuadB_INTSTAT & QuadB_MASK) >> QuadB_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
