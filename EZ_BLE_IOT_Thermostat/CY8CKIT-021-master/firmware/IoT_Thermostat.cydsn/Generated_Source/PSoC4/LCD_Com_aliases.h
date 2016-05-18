/*******************************************************************************
* File Name: LCD_Com.h  
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

#if !defined(CY_PINS_LCD_Com_ALIASES_H) /* Pins LCD_Com_ALIASES_H */
#define CY_PINS_LCD_Com_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define LCD_Com_0			(LCD_Com__0__PC)
#define LCD_Com_0_PS		(LCD_Com__0__PS)
#define LCD_Com_0_PC		(LCD_Com__0__PC)
#define LCD_Com_0_DR		(LCD_Com__0__DR)
#define LCD_Com_0_SHIFT	(LCD_Com__0__SHIFT)
#define LCD_Com_0_INTR	((uint16)((uint16)0x0003u << (LCD_Com__0__SHIFT*2u)))

#define LCD_Com_1			(LCD_Com__1__PC)
#define LCD_Com_1_PS		(LCD_Com__1__PS)
#define LCD_Com_1_PC		(LCD_Com__1__PC)
#define LCD_Com_1_DR		(LCD_Com__1__DR)
#define LCD_Com_1_SHIFT	(LCD_Com__1__SHIFT)
#define LCD_Com_1_INTR	((uint16)((uint16)0x0003u << (LCD_Com__1__SHIFT*2u)))

#define LCD_Com_2			(LCD_Com__2__PC)
#define LCD_Com_2_PS		(LCD_Com__2__PS)
#define LCD_Com_2_PC		(LCD_Com__2__PC)
#define LCD_Com_2_DR		(LCD_Com__2__DR)
#define LCD_Com_2_SHIFT	(LCD_Com__2__SHIFT)
#define LCD_Com_2_INTR	((uint16)((uint16)0x0003u << (LCD_Com__2__SHIFT*2u)))

#define LCD_Com_3			(LCD_Com__3__PC)
#define LCD_Com_3_PS		(LCD_Com__3__PS)
#define LCD_Com_3_PC		(LCD_Com__3__PC)
#define LCD_Com_3_DR		(LCD_Com__3__DR)
#define LCD_Com_3_SHIFT	(LCD_Com__3__SHIFT)
#define LCD_Com_3_INTR	((uint16)((uint16)0x0003u << (LCD_Com__3__SHIFT*2u)))

#define LCD_Com_INTR_ALL	 ((uint16)(LCD_Com_0_INTR| LCD_Com_1_INTR| LCD_Com_2_INTR| LCD_Com_3_INTR))


#endif /* End Pins LCD_Com_ALIASES_H */


/* [] END OF FILE */
