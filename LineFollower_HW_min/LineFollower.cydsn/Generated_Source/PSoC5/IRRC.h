/*******************************************************************************
* File Name: IRRC.h  
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

#if !defined(CY_PINS_IRRC_H) /* Pins IRRC_H */
#define CY_PINS_IRRC_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "IRRC_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 IRRC__PORT == 15 && ((IRRC__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    IRRC_Write(uint8 value) ;
void    IRRC_SetDriveMode(uint8 mode) ;
uint8   IRRC_ReadDataReg(void) ;
uint8   IRRC_Read(void) ;
uint8   IRRC_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define IRRC_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define IRRC_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define IRRC_DM_RES_UP          PIN_DM_RES_UP
#define IRRC_DM_RES_DWN         PIN_DM_RES_DWN
#define IRRC_DM_OD_LO           PIN_DM_OD_LO
#define IRRC_DM_OD_HI           PIN_DM_OD_HI
#define IRRC_DM_STRONG          PIN_DM_STRONG
#define IRRC_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define IRRC_MASK               IRRC__MASK
#define IRRC_SHIFT              IRRC__SHIFT
#define IRRC_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define IRRC_PS                     (* (reg8 *) IRRC__PS)
/* Data Register */
#define IRRC_DR                     (* (reg8 *) IRRC__DR)
/* Port Number */
#define IRRC_PRT_NUM                (* (reg8 *) IRRC__PRT) 
/* Connect to Analog Globals */                                                  
#define IRRC_AG                     (* (reg8 *) IRRC__AG)                       
/* Analog MUX bux enable */
#define IRRC_AMUX                   (* (reg8 *) IRRC__AMUX) 
/* Bidirectional Enable */                                                        
#define IRRC_BIE                    (* (reg8 *) IRRC__BIE)
/* Bit-mask for Aliased Register Access */
#define IRRC_BIT_MASK               (* (reg8 *) IRRC__BIT_MASK)
/* Bypass Enable */
#define IRRC_BYP                    (* (reg8 *) IRRC__BYP)
/* Port wide control signals */                                                   
#define IRRC_CTL                    (* (reg8 *) IRRC__CTL)
/* Drive Modes */
#define IRRC_DM0                    (* (reg8 *) IRRC__DM0) 
#define IRRC_DM1                    (* (reg8 *) IRRC__DM1)
#define IRRC_DM2                    (* (reg8 *) IRRC__DM2) 
/* Input Buffer Disable Override */
#define IRRC_INP_DIS                (* (reg8 *) IRRC__INP_DIS)
/* LCD Common or Segment Drive */
#define IRRC_LCD_COM_SEG            (* (reg8 *) IRRC__LCD_COM_SEG)
/* Enable Segment LCD */
#define IRRC_LCD_EN                 (* (reg8 *) IRRC__LCD_EN)
/* Slew Rate Control */
#define IRRC_SLW                    (* (reg8 *) IRRC__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define IRRC_PRTDSI__CAPS_SEL       (* (reg8 *) IRRC__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define IRRC_PRTDSI__DBL_SYNC_IN    (* (reg8 *) IRRC__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define IRRC_PRTDSI__OE_SEL0        (* (reg8 *) IRRC__PRTDSI__OE_SEL0) 
#define IRRC_PRTDSI__OE_SEL1        (* (reg8 *) IRRC__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define IRRC_PRTDSI__OUT_SEL0       (* (reg8 *) IRRC__PRTDSI__OUT_SEL0) 
#define IRRC_PRTDSI__OUT_SEL1       (* (reg8 *) IRRC__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define IRRC_PRTDSI__SYNC_OUT       (* (reg8 *) IRRC__PRTDSI__SYNC_OUT) 


#if defined(IRRC__INTSTAT)  /* Interrupt Registers */

    #define IRRC_INTSTAT                (* (reg8 *) IRRC__INTSTAT)
    #define IRRC_SNAP                   (* (reg8 *) IRRC__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_IRRC_H */


/* [] END OF FILE */
