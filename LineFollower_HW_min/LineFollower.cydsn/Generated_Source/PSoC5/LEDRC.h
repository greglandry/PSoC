/*******************************************************************************
* File Name: LEDRC.h  
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

#if !defined(CY_PINS_LEDRC_H) /* Pins LEDRC_H */
#define CY_PINS_LEDRC_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LEDRC_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_5 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LEDRC__PORT == 15 && ((LEDRC__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    LEDRC_Write(uint8 value) ;
void    LEDRC_SetDriveMode(uint8 mode) ;
uint8   LEDRC_ReadDataReg(void) ;
uint8   LEDRC_Read(void) ;
uint8   LEDRC_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define LEDRC_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define LEDRC_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define LEDRC_DM_RES_UP          PIN_DM_RES_UP
#define LEDRC_DM_RES_DWN         PIN_DM_RES_DWN
#define LEDRC_DM_OD_LO           PIN_DM_OD_LO
#define LEDRC_DM_OD_HI           PIN_DM_OD_HI
#define LEDRC_DM_STRONG          PIN_DM_STRONG
#define LEDRC_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define LEDRC_MASK               LEDRC__MASK
#define LEDRC_SHIFT              LEDRC__SHIFT
#define LEDRC_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LEDRC_PS                     (* (reg8 *) LEDRC__PS)
/* Data Register */
#define LEDRC_DR                     (* (reg8 *) LEDRC__DR)
/* Port Number */
#define LEDRC_PRT_NUM                (* (reg8 *) LEDRC__PRT) 
/* Connect to Analog Globals */                                                  
#define LEDRC_AG                     (* (reg8 *) LEDRC__AG)                       
/* Analog MUX bux enable */
#define LEDRC_AMUX                   (* (reg8 *) LEDRC__AMUX) 
/* Bidirectional Enable */                                                        
#define LEDRC_BIE                    (* (reg8 *) LEDRC__BIE)
/* Bit-mask for Aliased Register Access */
#define LEDRC_BIT_MASK               (* (reg8 *) LEDRC__BIT_MASK)
/* Bypass Enable */
#define LEDRC_BYP                    (* (reg8 *) LEDRC__BYP)
/* Port wide control signals */                                                   
#define LEDRC_CTL                    (* (reg8 *) LEDRC__CTL)
/* Drive Modes */
#define LEDRC_DM0                    (* (reg8 *) LEDRC__DM0) 
#define LEDRC_DM1                    (* (reg8 *) LEDRC__DM1)
#define LEDRC_DM2                    (* (reg8 *) LEDRC__DM2) 
/* Input Buffer Disable Override */
#define LEDRC_INP_DIS                (* (reg8 *) LEDRC__INP_DIS)
/* LCD Common or Segment Drive */
#define LEDRC_LCD_COM_SEG            (* (reg8 *) LEDRC__LCD_COM_SEG)
/* Enable Segment LCD */
#define LEDRC_LCD_EN                 (* (reg8 *) LEDRC__LCD_EN)
/* Slew Rate Control */
#define LEDRC_SLW                    (* (reg8 *) LEDRC__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LEDRC_PRTDSI__CAPS_SEL       (* (reg8 *) LEDRC__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LEDRC_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LEDRC__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LEDRC_PRTDSI__OE_SEL0        (* (reg8 *) LEDRC__PRTDSI__OE_SEL0) 
#define LEDRC_PRTDSI__OE_SEL1        (* (reg8 *) LEDRC__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LEDRC_PRTDSI__OUT_SEL0       (* (reg8 *) LEDRC__PRTDSI__OUT_SEL0) 
#define LEDRC_PRTDSI__OUT_SEL1       (* (reg8 *) LEDRC__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LEDRC_PRTDSI__SYNC_OUT       (* (reg8 *) LEDRC__PRTDSI__SYNC_OUT) 


#if defined(LEDRC__INTSTAT)  /* Interrupt Registers */

    #define LEDRC_INTSTAT                (* (reg8 *) LEDRC__INTSTAT)
    #define LEDRC_SNAP                   (* (reg8 *) LEDRC__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LEDRC_H */


/* [] END OF FILE */
