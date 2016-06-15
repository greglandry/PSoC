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

#define IR_2			(IR__2__PC)
#define IR_2_INTR	((uint16)((uint16)0x0001u << IR__2__SHIFT))

#define IR_3			(IR__3__PC)
#define IR_3_INTR	((uint16)((uint16)0x0001u << IR__3__SHIFT))

#define IR_4			(IR__4__PC)
#define IR_4_INTR	((uint16)((uint16)0x0001u << IR__4__SHIFT))

#define IR_INTR_ALL	 ((uint16)(IR_0_INTR| IR_1_INTR| IR_2_INTR| IR_3_INTR| IR_4_INTR))
#define IR_R			(IR__R__PC)
#define IR_R_INTR	((uint16)((uint16)0x0001u << IR__0__SHIFT))

#define IR_RC			(IR__RC__PC)
#define IR_RC_INTR	((uint16)((uint16)0x0001u << IR__1__SHIFT))

#define IR_C			(IR__C__PC)
#define IR_C_INTR	((uint16)((uint16)0x0001u << IR__2__SHIFT))

#define IR_LC			(IR__LC__PC)
#define IR_LC_INTR	((uint16)((uint16)0x0001u << IR__3__SHIFT))

#define IR_L			(IR__L__PC)
#define IR_L_INTR	((uint16)((uint16)0x0001u << IR__4__SHIFT))

#endif /* End Pins IR_ALIASES_H */


/* [] END OF FILE */
