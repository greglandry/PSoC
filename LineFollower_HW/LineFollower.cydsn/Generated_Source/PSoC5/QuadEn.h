/*******************************************************************************
* File Name: QuadEn.h  
* Version 2.0
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

#if !defined(CY_PINS_QuadEn_H) /* Pins QuadEn_H */
#define CY_PINS_QuadEn_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "QuadEn_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 QuadEn__PORT == 15 && ((QuadEn__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    QuadEn_Write(uint8 value) ;
void    QuadEn_SetDriveMode(uint8 mode) ;
uint8   QuadEn_ReadDataReg(void) ;
uint8   QuadEn_Read(void) ;
uint8   QuadEn_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define QuadEn_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define QuadEn_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define QuadEn_DM_RES_UP          PIN_DM_RES_UP
#define QuadEn_DM_RES_DWN         PIN_DM_RES_DWN
#define QuadEn_DM_OD_LO           PIN_DM_OD_LO
#define QuadEn_DM_OD_HI           PIN_DM_OD_HI
#define QuadEn_DM_STRONG          PIN_DM_STRONG
#define QuadEn_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define QuadEn_MASK               QuadEn__MASK
#define QuadEn_SHIFT              QuadEn__SHIFT
#define QuadEn_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define QuadEn_PS                     (* (reg8 *) QuadEn__PS)
/* Data Register */
#define QuadEn_DR                     (* (reg8 *) QuadEn__DR)
/* Port Number */
#define QuadEn_PRT_NUM                (* (reg8 *) QuadEn__PRT) 
/* Connect to Analog Globals */                                                  
#define QuadEn_AG                     (* (reg8 *) QuadEn__AG)                       
/* Analog MUX bux enable */
#define QuadEn_AMUX                   (* (reg8 *) QuadEn__AMUX) 
/* Bidirectional Enable */                                                        
#define QuadEn_BIE                    (* (reg8 *) QuadEn__BIE)
/* Bit-mask for Aliased Register Access */
#define QuadEn_BIT_MASK               (* (reg8 *) QuadEn__BIT_MASK)
/* Bypass Enable */
#define QuadEn_BYP                    (* (reg8 *) QuadEn__BYP)
/* Port wide control signals */                                                   
#define QuadEn_CTL                    (* (reg8 *) QuadEn__CTL)
/* Drive Modes */
#define QuadEn_DM0                    (* (reg8 *) QuadEn__DM0) 
#define QuadEn_DM1                    (* (reg8 *) QuadEn__DM1)
#define QuadEn_DM2                    (* (reg8 *) QuadEn__DM2) 
/* Input Buffer Disable Override */
#define QuadEn_INP_DIS                (* (reg8 *) QuadEn__INP_DIS)
/* LCD Common or Segment Drive */
#define QuadEn_LCD_COM_SEG            (* (reg8 *) QuadEn__LCD_COM_SEG)
/* Enable Segment LCD */
#define QuadEn_LCD_EN                 (* (reg8 *) QuadEn__LCD_EN)
/* Slew Rate Control */
#define QuadEn_SLW                    (* (reg8 *) QuadEn__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define QuadEn_PRTDSI__CAPS_SEL       (* (reg8 *) QuadEn__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define QuadEn_PRTDSI__DBL_SYNC_IN    (* (reg8 *) QuadEn__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define QuadEn_PRTDSI__OE_SEL0        (* (reg8 *) QuadEn__PRTDSI__OE_SEL0) 
#define QuadEn_PRTDSI__OE_SEL1        (* (reg8 *) QuadEn__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define QuadEn_PRTDSI__OUT_SEL0       (* (reg8 *) QuadEn__PRTDSI__OUT_SEL0) 
#define QuadEn_PRTDSI__OUT_SEL1       (* (reg8 *) QuadEn__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define QuadEn_PRTDSI__SYNC_OUT       (* (reg8 *) QuadEn__PRTDSI__SYNC_OUT) 


#if defined(QuadEn__INTSTAT)  /* Interrupt Registers */

    #define QuadEn_INTSTAT                (* (reg8 *) QuadEn__INTSTAT)
    #define QuadEn_SNAP                   (* (reg8 *) QuadEn__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_QuadEn_H */


/* [] END OF FILE */
