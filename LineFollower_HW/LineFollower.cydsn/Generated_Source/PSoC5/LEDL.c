/*******************************************************************************
* File Name: LEDL.c  
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
#include "LEDL.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 LEDL__PORT == 15 && ((LEDL__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: LEDL_Write
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
void LEDL_Write(uint8 value) 
{
    uint8 staticBits = (LEDL_DR & (uint8)(~LEDL_MASK));
    LEDL_DR = staticBits | ((uint8)(value << LEDL_SHIFT) & LEDL_MASK);
}


/*******************************************************************************
* Function Name: LEDL_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  LEDL_DM_STRONG     Strong Drive 
*  LEDL_DM_OD_HI      Open Drain, Drives High 
*  LEDL_DM_OD_LO      Open Drain, Drives Low 
*  LEDL_DM_RES_UP     Resistive Pull Up 
*  LEDL_DM_RES_DWN    Resistive Pull Down 
*  LEDL_DM_RES_UPDWN  Resistive Pull Up/Down 
*  LEDL_DM_DIG_HIZ    High Impedance Digital 
*  LEDL_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void LEDL_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(LEDL_0, mode);
}


/*******************************************************************************
* Function Name: LEDL_Read
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
*  Macro LEDL_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 LEDL_Read(void) 
{
    return (LEDL_PS & LEDL_MASK) >> LEDL_SHIFT;
}


/*******************************************************************************
* Function Name: LEDL_ReadDataReg
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
uint8 LEDL_ReadDataReg(void) 
{
    return (LEDL_DR & LEDL_MASK) >> LEDL_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(LEDL_INTSTAT) 

    /*******************************************************************************
    * Function Name: LEDL_ClearInterrupt
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
    uint8 LEDL_ClearInterrupt(void) 
    {
        return (LEDL_INTSTAT & LEDL_MASK) >> LEDL_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
