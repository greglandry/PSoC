/*******************************************************************************
* File Name: PIN_IREN.h  
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

#if !defined(CY_PINS_PIN_IREN_H) /* Pins PIN_IREN_H */
#define CY_PINS_PIN_IREN_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PIN_IREN_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PIN_IREN__PORT == 15 && ((PIN_IREN__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    PIN_IREN_Write(uint8 value) ;
void    PIN_IREN_SetDriveMode(uint8 mode) ;
uint8   PIN_IREN_ReadDataReg(void) ;
uint8   PIN_IREN_Read(void) ;
uint8   PIN_IREN_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PIN_IREN_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PIN_IREN_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PIN_IREN_DM_RES_UP          PIN_DM_RES_UP
#define PIN_IREN_DM_RES_DWN         PIN_DM_RES_DWN
#define PIN_IREN_DM_OD_LO           PIN_DM_OD_LO
#define PIN_IREN_DM_OD_HI           PIN_DM_OD_HI
#define PIN_IREN_DM_STRONG          PIN_DM_STRONG
#define PIN_IREN_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PIN_IREN_MASK               PIN_IREN__MASK
#define PIN_IREN_SHIFT              PIN_IREN__SHIFT
#define PIN_IREN_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PIN_IREN_PS                     (* (reg8 *) PIN_IREN__PS)
/* Data Register */
#define PIN_IREN_DR                     (* (reg8 *) PIN_IREN__DR)
/* Port Number */
#define PIN_IREN_PRT_NUM                (* (reg8 *) PIN_IREN__PRT) 
/* Connect to Analog Globals */                                                  
#define PIN_IREN_AG                     (* (reg8 *) PIN_IREN__AG)                       
/* Analog MUX bux enable */
#define PIN_IREN_AMUX                   (* (reg8 *) PIN_IREN__AMUX) 
/* Bidirectional Enable */                                                        
#define PIN_IREN_BIE                    (* (reg8 *) PIN_IREN__BIE)
/* Bit-mask for Aliased Register Access */
#define PIN_IREN_BIT_MASK               (* (reg8 *) PIN_IREN__BIT_MASK)
/* Bypass Enable */
#define PIN_IREN_BYP                    (* (reg8 *) PIN_IREN__BYP)
/* Port wide control signals */                                                   
#define PIN_IREN_CTL                    (* (reg8 *) PIN_IREN__CTL)
/* Drive Modes */
#define PIN_IREN_DM0                    (* (reg8 *) PIN_IREN__DM0) 
#define PIN_IREN_DM1                    (* (reg8 *) PIN_IREN__DM1)
#define PIN_IREN_DM2                    (* (reg8 *) PIN_IREN__DM2) 
/* Input Buffer Disable Override */
#define PIN_IREN_INP_DIS                (* (reg8 *) PIN_IREN__INP_DIS)
/* LCD Common or Segment Drive */
#define PIN_IREN_LCD_COM_SEG            (* (reg8 *) PIN_IREN__LCD_COM_SEG)
/* Enable Segment LCD */
#define PIN_IREN_LCD_EN                 (* (reg8 *) PIN_IREN__LCD_EN)
/* Slew Rate Control */
#define PIN_IREN_SLW                    (* (reg8 *) PIN_IREN__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PIN_IREN_PRTDSI__CAPS_SEL       (* (reg8 *) PIN_IREN__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PIN_IREN_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PIN_IREN__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PIN_IREN_PRTDSI__OE_SEL0        (* (reg8 *) PIN_IREN__PRTDSI__OE_SEL0) 
#define PIN_IREN_PRTDSI__OE_SEL1        (* (reg8 *) PIN_IREN__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PIN_IREN_PRTDSI__OUT_SEL0       (* (reg8 *) PIN_IREN__PRTDSI__OUT_SEL0) 
#define PIN_IREN_PRTDSI__OUT_SEL1       (* (reg8 *) PIN_IREN__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PIN_IREN_PRTDSI__SYNC_OUT       (* (reg8 *) PIN_IREN__PRTDSI__SYNC_OUT) 


#if defined(PIN_IREN__INTSTAT)  /* Interrupt Registers */

    #define PIN_IREN_INTSTAT                (* (reg8 *) PIN_IREN__INTSTAT)
    #define PIN_IREN_SNAP                   (* (reg8 *) PIN_IREN__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PIN_IREN_H */


/* [] END OF FILE */
