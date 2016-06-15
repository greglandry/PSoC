/*******************************************************************************
* File Name: IRR2.h  
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

#if !defined(CY_PINS_IRR2_H) /* Pins IRR2_H */
#define CY_PINS_IRR2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "IRR2_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 IRR2__PORT == 15 && ((IRR2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    IRR2_Write(uint8 value) ;
void    IRR2_SetDriveMode(uint8 mode) ;
uint8   IRR2_ReadDataReg(void) ;
uint8   IRR2_Read(void) ;
uint8   IRR2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define IRR2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define IRR2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define IRR2_DM_RES_UP          PIN_DM_RES_UP
#define IRR2_DM_RES_DWN         PIN_DM_RES_DWN
#define IRR2_DM_OD_LO           PIN_DM_OD_LO
#define IRR2_DM_OD_HI           PIN_DM_OD_HI
#define IRR2_DM_STRONG          PIN_DM_STRONG
#define IRR2_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define IRR2_MASK               IRR2__MASK
#define IRR2_SHIFT              IRR2__SHIFT
#define IRR2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define IRR2_PS                     (* (reg8 *) IRR2__PS)
/* Data Register */
#define IRR2_DR                     (* (reg8 *) IRR2__DR)
/* Port Number */
#define IRR2_PRT_NUM                (* (reg8 *) IRR2__PRT) 
/* Connect to Analog Globals */                                                  
#define IRR2_AG                     (* (reg8 *) IRR2__AG)                       
/* Analog MUX bux enable */
#define IRR2_AMUX                   (* (reg8 *) IRR2__AMUX) 
/* Bidirectional Enable */                                                        
#define IRR2_BIE                    (* (reg8 *) IRR2__BIE)
/* Bit-mask for Aliased Register Access */
#define IRR2_BIT_MASK               (* (reg8 *) IRR2__BIT_MASK)
/* Bypass Enable */
#define IRR2_BYP                    (* (reg8 *) IRR2__BYP)
/* Port wide control signals */                                                   
#define IRR2_CTL                    (* (reg8 *) IRR2__CTL)
/* Drive Modes */
#define IRR2_DM0                    (* (reg8 *) IRR2__DM0) 
#define IRR2_DM1                    (* (reg8 *) IRR2__DM1)
#define IRR2_DM2                    (* (reg8 *) IRR2__DM2) 
/* Input Buffer Disable Override */
#define IRR2_INP_DIS                (* (reg8 *) IRR2__INP_DIS)
/* LCD Common or Segment Drive */
#define IRR2_LCD_COM_SEG            (* (reg8 *) IRR2__LCD_COM_SEG)
/* Enable Segment LCD */
#define IRR2_LCD_EN                 (* (reg8 *) IRR2__LCD_EN)
/* Slew Rate Control */
#define IRR2_SLW                    (* (reg8 *) IRR2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define IRR2_PRTDSI__CAPS_SEL       (* (reg8 *) IRR2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define IRR2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) IRR2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define IRR2_PRTDSI__OE_SEL0        (* (reg8 *) IRR2__PRTDSI__OE_SEL0) 
#define IRR2_PRTDSI__OE_SEL1        (* (reg8 *) IRR2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define IRR2_PRTDSI__OUT_SEL0       (* (reg8 *) IRR2__PRTDSI__OUT_SEL0) 
#define IRR2_PRTDSI__OUT_SEL1       (* (reg8 *) IRR2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define IRR2_PRTDSI__SYNC_OUT       (* (reg8 *) IRR2__PRTDSI__SYNC_OUT) 


#if defined(IRR2__INTSTAT)  /* Interrupt Registers */

    #define IRR2_INTSTAT                (* (reg8 *) IRR2__INTSTAT)
    #define IRR2_SNAP                   (* (reg8 *) IRR2__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_IRR2_H */


/* [] END OF FILE */
