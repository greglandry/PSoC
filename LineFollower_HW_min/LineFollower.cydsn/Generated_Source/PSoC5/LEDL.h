/*******************************************************************************
* File Name: LEDL.h  
* Version 2.5
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_LEDL_H) /* Pins LEDL_H */
#define CY_PINS_LEDL_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LEDL_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_5 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LEDL__PORT == 15 && ((LEDL__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    LEDL_Write(uint8 value) ;
void    LEDL_SetDriveMode(uint8 mode) ;
uint8   LEDL_ReadDataReg(void) ;
uint8   LEDL_Read(void) ;
uint8   LEDL_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define LEDL_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define LEDL_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define LEDL_DM_RES_UP          PIN_DM_RES_UP
#define LEDL_DM_RES_DWN         PIN_DM_RES_DWN
#define LEDL_DM_OD_LO           PIN_DM_OD_LO
#define LEDL_DM_OD_HI           PIN_DM_OD_HI
#define LEDL_DM_STRONG          PIN_DM_STRONG
#define LEDL_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define LEDL_MASK               LEDL__MASK
#define LEDL_SHIFT              LEDL__SHIFT
#define LEDL_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LEDL_PS                     (* (reg8 *) LEDL__PS)
/* Data Register */
#define LEDL_DR                     (* (reg8 *) LEDL__DR)
/* Port Number */
#define LEDL_PRT_NUM                (* (reg8 *) LEDL__PRT) 
/* Connect to Analog Globals */                                                  
#define LEDL_AG                     (* (reg8 *) LEDL__AG)                       
/* Analog MUX bux enable */
#define LEDL_AMUX                   (* (reg8 *) LEDL__AMUX) 
/* Bidirectional Enable */                                                        
#define LEDL_BIE                    (* (reg8 *) LEDL__BIE)
/* Bit-mask for Aliased Register Access */
#define LEDL_BIT_MASK               (* (reg8 *) LEDL__BIT_MASK)
/* Bypass Enable */
#define LEDL_BYP                    (* (reg8 *) LEDL__BYP)
/* Port wide control signals */                                                   
#define LEDL_CTL                    (* (reg8 *) LEDL__CTL)
/* Drive Modes */
#define LEDL_DM0                    (* (reg8 *) LEDL__DM0) 
#define LEDL_DM1                    (* (reg8 *) LEDL__DM1)
#define LEDL_DM2                    (* (reg8 *) LEDL__DM2) 
/* Input Buffer Disable Override */
#define LEDL_INP_DIS                (* (reg8 *) LEDL__INP_DIS)
/* LCD Common or Segment Drive */
#define LEDL_LCD_COM_SEG            (* (reg8 *) LEDL__LCD_COM_SEG)
/* Enable Segment LCD */
#define LEDL_LCD_EN                 (* (reg8 *) LEDL__LCD_EN)
/* Slew Rate Control */
#define LEDL_SLW                    (* (reg8 *) LEDL__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LEDL_PRTDSI__CAPS_SEL       (* (reg8 *) LEDL__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LEDL_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LEDL__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LEDL_PRTDSI__OE_SEL0        (* (reg8 *) LEDL__PRTDSI__OE_SEL0) 
#define LEDL_PRTDSI__OE_SEL1        (* (reg8 *) LEDL__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LEDL_PRTDSI__OUT_SEL0       (* (reg8 *) LEDL__PRTDSI__OUT_SEL0) 
#define LEDL_PRTDSI__OUT_SEL1       (* (reg8 *) LEDL__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LEDL_PRTDSI__SYNC_OUT       (* (reg8 *) LEDL__PRTDSI__SYNC_OUT) 


#if defined(LEDL__INTSTAT)  /* Interrupt Registers */

    #define LEDL_INTSTAT                (* (reg8 *) LEDL__INTSTAT)
    #define LEDL_SNAP                   (* (reg8 *) LEDL__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LEDL_H */


/* [] END OF FILE */
