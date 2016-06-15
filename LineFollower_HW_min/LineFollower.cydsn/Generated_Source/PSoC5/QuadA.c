/*******************************************************************************
* File Name: QuadA.c  
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
#include "QuadA.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 QuadA__PORT == 15 && ((QuadA__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: QuadA_Write
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
void QuadA_Write(uint8 value) 
{
    uint8 staticBits = (QuadA_DR & (uint8)(~QuadA_MASK));
    QuadA_DR = staticBits | ((uint8)(value << QuadA_SHIFT) & QuadA_MASK);
}


/*******************************************************************************
* Function Name: QuadA_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  QuadA_DM_STRONG     Strong Drive 
*  QuadA_DM_OD_HI      Open Drain, Drives High 
*  QuadA_DM_OD_LO      Open Drain, Drives Low 
*  QuadA_DM_RES_UP     Resistive Pull Up 
*  QuadA_DM_RES_DWN    Resistive Pull Down 
*  QuadA_DM_RES_UPDWN  Resistive Pull Up/Down 
*  QuadA_DM_DIG_HIZ    High Impedance Digital 
*  QuadA_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void QuadA_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(QuadA_0, mode);
}


/*******************************************************************************
* Function Name: QuadA_Read
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
*  Macro QuadA_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 QuadA_Read(void) 
{
    return (QuadA_PS & QuadA_MASK) >> QuadA_SHIFT;
}


/*******************************************************************************
* Function Name: QuadA_ReadDataReg
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
uint8 QuadA_ReadDataReg(void) 
{
    return (QuadA_DR & QuadA_MASK) >> QuadA_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(QuadA_INTSTAT) 

    /*******************************************************************************
    * Function Name: QuadA_ClearInterrupt
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
    uint8 QuadA_ClearInterrupt(void) 
    {
        return (QuadA_INTSTAT & QuadA_MASK) >> QuadA_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
