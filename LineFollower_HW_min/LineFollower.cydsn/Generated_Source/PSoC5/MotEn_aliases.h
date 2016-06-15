/*******************************************************************************
* File Name: MotEn.h  
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

#if !defined(CY_PINS_MotEn_ALIASES_H) /* Pins MotEn_ALIASES_H */
#define CY_PINS_MotEn_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define MotEn_0			(MotEn__0__PC)
#define MotEn_0_INTR	((uint16)((uint16)0x0001u << MotEn__0__SHIFT))

#define MotEn_INTR_ALL	 ((uint16)(MotEn_0_INTR))

#endif /* End Pins MotEn_ALIASES_H */


/* [] END OF FILE */
