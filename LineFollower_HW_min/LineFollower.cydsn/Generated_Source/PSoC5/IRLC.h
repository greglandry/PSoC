/*******************************************************************************
* File Name: IRLC.h  
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

#if !defined(CY_PINS_IRLC_H) /* Pins IRLC_H */
#define CY_PINS_IRLC_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "IRLC_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 IRLC__PORT == 15 && ((IRLC__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    IRLC_Write(uint8 value) ;
void    IRLC_SetDriveMode(uint8 mode) ;
uint8   IRLC_ReadDataReg(void) ;
uint8   IRLC_Read(void) ;
uint8   IRLC_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define IRLC_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define IRLC_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define IRLC_DM_RES_UP          PIN_DM_RES_UP
#define IRLC_DM_RES_DWN         PIN_DM_RES_DWN
#define IRLC_DM_OD_LO           PIN_DM_OD_LO
#define IRLC_DM_OD_HI           PIN_DM_OD_HI
#define IRLC_DM_STRONG          PIN_DM_STRONG
#define IRLC_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define IRLC_MASK               IRLC__MASK
#define IRLC_SHIFT              IRLC__SHIFT
#define IRLC_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define IRLC_PS                     (* (reg8 *) IRLC__PS)
/* Data Register */
#define IRLC_DR                     (* (reg8 *) IRLC__DR)
/* Port Number */
#define IRLC_PRT_NUM                (* (reg8 *) IRLC__PRT) 
/* Connect to Analog Globals */                                                  
#define IRLC_AG                     (* (reg8 *) IRLC__AG)                       
/* Analog MUX bux enable */
#define IRLC_AMUX                   (* (reg8 *) IRLC__AMUX) 
/* Bidirectional Enable */                                                        
#define IRLC_BIE                    (* (reg8 *) IRLC__BIE)
/* Bit-mask for Aliased Register Access */
#define IRLC_BIT_MASK               (* (reg8 *) IRLC__BIT_MASK)
/* Bypass Enable */
#define IRLC_BYP                    (* (reg8 *) IRLC__BYP)
/* Port wide control signals */                                                   
#define IRLC_CTL                    (* (reg8 *) IRLC__CTL)
/* Drive Modes */
#define IRLC_DM0                    (* (reg8 *) IRLC__DM0) 
#define IRLC_DM1                    (* (reg8 *) IRLC__DM1)
#define IRLC_DM2                    (* (reg8 *) IRLC__DM2) 
/* Input Buffer Disable Override */
#define IRLC_INP_DIS                (* (reg8 *) IRLC__INP_DIS)
/* LCD Common or Segment Drive */
#define IRLC_LCD_COM_SEG            (* (reg8 *) IRLC__LCD_COM_SEG)
/* Enable Segment LCD */
#define IRLC_LCD_EN                 (* (reg8 *) IRLC__LCD_EN)
/* Slew Rate Control */
#define IRLC_SLW                    (* (reg8 *) IRLC__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define IRLC_PRTDSI__CAPS_SEL       (* (reg8 *) IRLC__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define IRLC_PRTDSI__DBL_SYNC_IN    (* (reg8 *) IRLC__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define IRLC_PRTDSI__OE_SEL0        (* (reg8 *) IRLC__PRTDSI__OE_SEL0) 
#define IRLC_PRTDSI__OE_SEL1        (* (reg8 *) IRLC__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define IRLC_PRTDSI__OUT_SEL0       (* (reg8 *) IRLC__PRTDSI__OUT_SEL0) 
#define IRLC_PRTDSI__OUT_SEL1       (* (reg8 *) IRLC__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define IRLC_PRTDSI__SYNC_OUT       (* (reg8 *) IRLC__PRTDSI__SYNC_OUT) 


#if defined(IRLC__INTSTAT)  /* Interrupt Registers */

    #define IRLC_INTSTAT                (* (reg8 *) IRLC__INTSTAT)
    #define IRLC_SNAP                   (* (reg8 *) IRLC__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_IRLC_H */


/* [] END OF FILE */
