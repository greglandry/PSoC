/*******************************************************************************
* File Name: IRR.h  
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

#if !defined(CY_PINS_IRR_H) /* Pins IRR_H */
#define CY_PINS_IRR_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "IRR_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 IRR__PORT == 15 && ((IRR__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    IRR_Write(uint8 value) ;
void    IRR_SetDriveMode(uint8 mode) ;
uint8   IRR_ReadDataReg(void) ;
uint8   IRR_Read(void) ;
uint8   IRR_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define IRR_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define IRR_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define IRR_DM_RES_UP          PIN_DM_RES_UP
#define IRR_DM_RES_DWN         PIN_DM_RES_DWN
#define IRR_DM_OD_LO           PIN_DM_OD_LO
#define IRR_DM_OD_HI           PIN_DM_OD_HI
#define IRR_DM_STRONG          PIN_DM_STRONG
#define IRR_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define IRR_MASK               IRR__MASK
#define IRR_SHIFT              IRR__SHIFT
#define IRR_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define IRR_PS                     (* (reg8 *) IRR__PS)
/* Data Register */
#define IRR_DR                     (* (reg8 *) IRR__DR)
/* Port Number */
#define IRR_PRT_NUM                (* (reg8 *) IRR__PRT) 
/* Connect to Analog Globals */                                                  
#define IRR_AG                     (* (reg8 *) IRR__AG)                       
/* Analog MUX bux enable */
#define IRR_AMUX                   (* (reg8 *) IRR__AMUX) 
/* Bidirectional Enable */                                                        
#define IRR_BIE                    (* (reg8 *) IRR__BIE)
/* Bit-mask for Aliased Register Access */
#define IRR_BIT_MASK               (* (reg8 *) IRR__BIT_MASK)
/* Bypass Enable */
#define IRR_BYP                    (* (reg8 *) IRR__BYP)
/* Port wide control signals */                                                   
#define IRR_CTL                    (* (reg8 *) IRR__CTL)
/* Drive Modes */
#define IRR_DM0                    (* (reg8 *) IRR__DM0) 
#define IRR_DM1                    (* (reg8 *) IRR__DM1)
#define IRR_DM2                    (* (reg8 *) IRR__DM2) 
/* Input Buffer Disable Override */
#define IRR_INP_DIS                (* (reg8 *) IRR__INP_DIS)
/* LCD Common or Segment Drive */
#define IRR_LCD_COM_SEG            (* (reg8 *) IRR__LCD_COM_SEG)
/* Enable Segment LCD */
#define IRR_LCD_EN                 (* (reg8 *) IRR__LCD_EN)
/* Slew Rate Control */
#define IRR_SLW                    (* (reg8 *) IRR__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define IRR_PRTDSI__CAPS_SEL       (* (reg8 *) IRR__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define IRR_PRTDSI__DBL_SYNC_IN    (* (reg8 *) IRR__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define IRR_PRTDSI__OE_SEL0        (* (reg8 *) IRR__PRTDSI__OE_SEL0) 
#define IRR_PRTDSI__OE_SEL1        (* (reg8 *) IRR__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define IRR_PRTDSI__OUT_SEL0       (* (reg8 *) IRR__PRTDSI__OUT_SEL0) 
#define IRR_PRTDSI__OUT_SEL1       (* (reg8 *) IRR__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define IRR_PRTDSI__SYNC_OUT       (* (reg8 *) IRR__PRTDSI__SYNC_OUT) 


#if defined(IRR__INTSTAT)  /* Interrupt Registers */

    #define IRR_INTSTAT                (* (reg8 *) IRR__INTSTAT)
    #define IRR_SNAP                   (* (reg8 *) IRR__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_IRR_H */


/* [] END OF FILE */
