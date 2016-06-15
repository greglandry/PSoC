/*******************************************************************************
* File Name: LEDR.h  
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

#if !defined(CY_PINS_LEDR_H) /* Pins LEDR_H */
#define CY_PINS_LEDR_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LEDR_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_5 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LEDR__PORT == 15 && ((LEDR__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    LEDR_Write(uint8 value) ;
void    LEDR_SetDriveMode(uint8 mode) ;
uint8   LEDR_ReadDataReg(void) ;
uint8   LEDR_Read(void) ;
uint8   LEDR_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define LEDR_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define LEDR_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define LEDR_DM_RES_UP          PIN_DM_RES_UP
#define LEDR_DM_RES_DWN         PIN_DM_RES_DWN
#define LEDR_DM_OD_LO           PIN_DM_OD_LO
#define LEDR_DM_OD_HI           PIN_DM_OD_HI
#define LEDR_DM_STRONG          PIN_DM_STRONG
#define LEDR_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define LEDR_MASK               LEDR__MASK
#define LEDR_SHIFT              LEDR__SHIFT
#define LEDR_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LEDR_PS                     (* (reg8 *) LEDR__PS)
/* Data Register */
#define LEDR_DR                     (* (reg8 *) LEDR__DR)
/* Port Number */
#define LEDR_PRT_NUM                (* (reg8 *) LEDR__PRT) 
/* Connect to Analog Globals */                                                  
#define LEDR_AG                     (* (reg8 *) LEDR__AG)                       
/* Analog MUX bux enable */
#define LEDR_AMUX                   (* (reg8 *) LEDR__AMUX) 
/* Bidirectional Enable */                                                        
#define LEDR_BIE                    (* (reg8 *) LEDR__BIE)
/* Bit-mask for Aliased Register Access */
#define LEDR_BIT_MASK               (* (reg8 *) LEDR__BIT_MASK)
/* Bypass Enable */
#define LEDR_BYP                    (* (reg8 *) LEDR__BYP)
/* Port wide control signals */                                                   
#define LEDR_CTL                    (* (reg8 *) LEDR__CTL)
/* Drive Modes */
#define LEDR_DM0                    (* (reg8 *) LEDR__DM0) 
#define LEDR_DM1                    (* (reg8 *) LEDR__DM1)
#define LEDR_DM2                    (* (reg8 *) LEDR__DM2) 
/* Input Buffer Disable Override */
#define LEDR_INP_DIS                (* (reg8 *) LEDR__INP_DIS)
/* LCD Common or Segment Drive */
#define LEDR_LCD_COM_SEG            (* (reg8 *) LEDR__LCD_COM_SEG)
/* Enable Segment LCD */
#define LEDR_LCD_EN                 (* (reg8 *) LEDR__LCD_EN)
/* Slew Rate Control */
#define LEDR_SLW                    (* (reg8 *) LEDR__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LEDR_PRTDSI__CAPS_SEL       (* (reg8 *) LEDR__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LEDR_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LEDR__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LEDR_PRTDSI__OE_SEL0        (* (reg8 *) LEDR__PRTDSI__OE_SEL0) 
#define LEDR_PRTDSI__OE_SEL1        (* (reg8 *) LEDR__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LEDR_PRTDSI__OUT_SEL0       (* (reg8 *) LEDR__PRTDSI__OUT_SEL0) 
#define LEDR_PRTDSI__OUT_SEL1       (* (reg8 *) LEDR__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LEDR_PRTDSI__SYNC_OUT       (* (reg8 *) LEDR__PRTDSI__SYNC_OUT) 


#if defined(LEDR__INTSTAT)  /* Interrupt Registers */

    #define LEDR_INTSTAT                (* (reg8 *) LEDR__INTSTAT)
    #define LEDR_SNAP                   (* (reg8 *) LEDR__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LEDR_H */


/* [] END OF FILE */
