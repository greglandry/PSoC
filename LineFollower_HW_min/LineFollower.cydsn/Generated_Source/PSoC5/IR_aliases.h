/*******************************************************************************
* File Name: IR.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_IR_ALIASES_H) /* Pins IR_ALIASES_H */
#define CY_PINS_IR_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define IR_0			(IR__0__PC)
#define IR_0_INTR	((uint16)((uint16)0x0001u << IR__0__SHIFT))

#define IR_1			(IR__1__PC)
#define IR_1_INTR	((uint16)((uint16)0x0001u << IR__1__SHIFT))

#define IR_INTR_ALL	 ((uint16)(IR_0_INTR| IR_1_INTR))
#define IR_L			(IR__L__PC)
#define IR_L_INTR	((uint16)((uint16)0x0001u << IR__0__SHIFT))

#define IR_R			(IR__R__PC)
#define IR_R_INTR	((uint16)((uint16)0x0001u << IR__1__SHIFT))

#endif /* End Pins IR_ALIASES_H */


/* [] END OF FILE */
