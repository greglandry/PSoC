/*******************************************************************************
* File Name: P06.h  
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

#if !defined(CY_PINS_P06_ALIASES_H) /* Pins P06_ALIASES_H */
#define CY_PINS_P06_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define P06_0			(P06__0__PC)
#define P06_0_PS		(P06__0__PS)
#define P06_0_PC		(P06__0__PC)
#define P06_0_DR		(P06__0__DR)
#define P06_0_SHIFT	(P06__0__SHIFT)
#define P06_0_INTR	((uint16)((uint16)0x0003u << (P06__0__SHIFT*2u)))

#define P06_INTR_ALL	 ((uint16)(P06_0_INTR))


#endif /* End Pins P06_ALIASES_H */


/* [] END OF FILE */
