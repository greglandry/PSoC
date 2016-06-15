/*******************************************************************************
* File Name: IRL2_int.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_IRL2_int_H)
#define CY_ISR_IRL2_int_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void IRL2_int_Start(void);
void IRL2_int_StartEx(cyisraddress address);
void IRL2_int_Stop(void);

CY_ISR_PROTO(IRL2_int_Interrupt);

void IRL2_int_SetVector(cyisraddress address);
cyisraddress IRL2_int_GetVector(void);

void IRL2_int_SetPriority(uint8 priority);
uint8 IRL2_int_GetPriority(void);

void IRL2_int_Enable(void);
uint8 IRL2_int_GetState(void);
void IRL2_int_Disable(void);

void IRL2_int_SetPending(void);
void IRL2_int_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the IRL2_int ISR. */
#define IRL2_int_INTC_VECTOR            ((reg32 *) IRL2_int__INTC_VECT)

/* Address of the IRL2_int ISR priority. */
#define IRL2_int_INTC_PRIOR             ((reg8 *) IRL2_int__INTC_PRIOR_REG)

/* Priority of the IRL2_int interrupt. */
#define IRL2_int_INTC_PRIOR_NUMBER      IRL2_int__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable IRL2_int interrupt. */
#define IRL2_int_INTC_SET_EN            ((reg32 *) IRL2_int__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the IRL2_int interrupt. */
#define IRL2_int_INTC_CLR_EN            ((reg32 *) IRL2_int__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the IRL2_int interrupt state to pending. */
#define IRL2_int_INTC_SET_PD            ((reg32 *) IRL2_int__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the IRL2_int interrupt. */
#define IRL2_int_INTC_CLR_PD            ((reg32 *) IRL2_int__INTC_CLR_PD_REG)


#endif /* CY_ISR_IRL2_int_H */


/* [] END OF FILE */
