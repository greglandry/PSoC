/*******************************************************************************
* File Name: LEDs.h  
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

#if !defined(CY_PINS_LEDs_ALIASES_H) /* Pins LEDs_ALIASES_H */
#define CY_PINS_LEDs_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define LEDs_0			(LEDs__0__PC)
#define LEDs_0_INTR	((uint16)((uint16)0x0001u << LEDs__0__SHIFT))

#define LEDs_1			(LEDs__1__PC)
#define LEDs_1_INTR	((uint16)((uint16)0x0001u << LEDs__1__SHIFT))

#define LEDs_2			(LEDs__2__PC)
#define LEDs_2_INTR	((uint16)((uint16)0x0001u << LEDs__2__SHIFT))

#define LEDs_3			(LEDs__3__PC)
#define LEDs_3_INTR	((uint16)((uint16)0x0001u << LEDs__3__SHIFT))

#define LEDs_4			(LEDs__4__PC)
#define LEDs_4_INTR	((uint16)((uint16)0x0001u << LEDs__4__SHIFT))

#define LEDs_INTR_ALL	 ((uint16)(LEDs_0_INTR| LEDs_1_INTR| LEDs_2_INTR| LEDs_3_INTR| LEDs_4_INTR))

#endif /* End Pins LEDs_ALIASES_H */


/* [] END OF FILE */
