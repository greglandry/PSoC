/*******************************************************************************
* File Name: IR_int.c  
* Version 1.70
*
*  Description:
*   API for controlling the state of an interrupt.
*
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/


#include <cydevice_trm.h>
#include <CyLib.h>
#include <IR_int.h>

#if !defined(IR_int__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START IR_int_intc` */

/* `#END` */

#ifndef CYINT_IRQ_BASE
#define CYINT_IRQ_BASE      16
#endif /* CYINT_IRQ_BASE */
#ifndef CYINT_VECT_TABLE
#define CYINT_VECT_TABLE    ((cyisraddress **) CYREG_NVIC_VECT_OFFSET)
#endif /* CYINT_VECT_TABLE */

/* Declared in startup, used to set unused interrupts to. */
CY_ISR_PROTO(IntDefaultHandler);


/*******************************************************************************
* Function Name: IR_int_Start
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void IR_int_Start(void)
{
    /* For all we know the interrupt is active. */
    IR_int_Disable();

    /* Set the ISR to point to the IR_int Interrupt. */
    IR_int_SetVector(&IR_int_Interrupt);

    /* Set the priority. */
    IR_int_SetPriority((uint8)IR_int_INTC_PRIOR_NUMBER);

    /* Enable it. */
    IR_int_Enable();
}


/*******************************************************************************
* Function Name: IR_int_StartEx
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void IR_int_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    IR_int_Disable();

    /* Set the ISR to point to the IR_int Interrupt. */
    IR_int_SetVector(address);

    /* Set the priority. */
    IR_int_SetPriority((uint8)IR_int_INTC_PRIOR_NUMBER);

    /* Enable it. */
    IR_int_Enable();
}


/*******************************************************************************
* Function Name: IR_int_Stop
********************************************************************************
*
* Summary:
*   Disables and removes the interrupt.
*
* Parameters:  
*
* Return:
*   None
*
*******************************************************************************/
void IR_int_Stop(void)
{
    /* Disable this interrupt. */
    IR_int_Disable();

    /* Set the ISR to point to the passive one. */
    IR_int_SetVector(&IntDefaultHandler);
}


/*******************************************************************************
* Function Name: IR_int_Interrupt
********************************************************************************
*
* Summary:
*   The default Interrupt Service Routine for IR_int.
*
*   Add custom code between the coments to keep the next version of this file
*   from over writting your code.
*
* Parameters:  
*
* Return:
*   None
*
*******************************************************************************/
CY_ISR(IR_int_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START IR_int_Interrupt` */

    /* `#END` */
}


/*******************************************************************************
* Function Name: IR_int_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling IR_int_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use IR_int_StartEx instead.
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void IR_int_SetVector(cyisraddress address)
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    ramVectorTable[CYINT_IRQ_BASE + (uint32)IR_int__INTC_NUMBER] = address;
}


/*******************************************************************************
* Function Name: IR_int_GetVector
********************************************************************************
*
* Summary:
*   Gets the "address" of the current ISR vector for the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Address of the ISR in the interrupt vector table.
*
*******************************************************************************/
cyisraddress IR_int_GetVector(void)
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    return ramVectorTable[CYINT_IRQ_BASE + (uint32)IR_int__INTC_NUMBER];
}


/*******************************************************************************
* Function Name: IR_int_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. Note calling IR_int_Start
*   or IR_int_StartEx will override any effect this method 
*   would have had. This method should only be called after 
*   IR_int_Start or IR_int_StartEx has been called. To set 
*   the initial priority for the component use the cydwr file in the tool.
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 7, 0 being the highest.
*
* Return:
*   None
*
*******************************************************************************/
void IR_int_SetPriority(uint8 priority)
{
    *IR_int_INTC_PRIOR = priority << 5;
}


/*******************************************************************************
* Function Name: IR_int_GetPriority
********************************************************************************
*
* Summary:
*   Gets the Priority of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Priority of the interrupt. 0 - 7, 0 being the highest.
*
*******************************************************************************/
uint8 IR_int_GetPriority(void)
{
    uint8 priority;


    priority = *IR_int_INTC_PRIOR >> 5;

    return priority;
}


/*******************************************************************************
* Function Name: IR_int_Enable
********************************************************************************
*
* Summary:
*   Enables the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void IR_int_Enable(void)
{
    /* Enable the general interrupt. */
    *IR_int_INTC_SET_EN = IR_int__INTC_MASK;
}


/*******************************************************************************
* Function Name: IR_int_GetState
********************************************************************************
*
* Summary:
*   Gets the state (enabled, disabled) of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   1 if enabled, 0 if disabled.
*
*******************************************************************************/
uint8 IR_int_GetState(void)
{
    /* Get the state of the general interrupt. */
    return ((*IR_int_INTC_SET_EN & (uint32)IR_int__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: IR_int_Disable
********************************************************************************
*
* Summary:
*   Disables the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void IR_int_Disable(void)
{
    /* Disable the general interrupt. */
    *IR_int_INTC_CLR_EN = IR_int__INTC_MASK;
}


/*******************************************************************************
* Function Name: IR_int_SetPending
********************************************************************************
*
* Summary:
*   Causes the Interrupt to enter the pending state, a software method of
*   generating the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void IR_int_SetPending(void)
{
    *IR_int_INTC_SET_PD = IR_int__INTC_MASK;
}


/*******************************************************************************
* Function Name: IR_int_ClearPending
********************************************************************************
*
* Summary:
*   Clears a pending interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void IR_int_ClearPending(void)
{
    *IR_int_INTC_CLR_PD = IR_int__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
