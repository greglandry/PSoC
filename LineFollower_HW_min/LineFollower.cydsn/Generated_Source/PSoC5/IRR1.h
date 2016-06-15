/*******************************************************************************
* File Name: IRR1.h  
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

#if !defined(CY_PINS_IRR1_H) /* Pins IRR1_H */
#define CY_PINS_IRR1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "IRR1_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 IRR1__PORT == 15 && ((IRR1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    IRR1_Write(uint8 value) ;
void    IRR1_SetDriveMode(uint8 mode) ;
uint8   IRR1_ReadDataReg(void) ;
uint8   IRR1_Read(void) ;
uint8   IRR1_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define IRR1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define IRR1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define IRR1_DM_RES_UP          PIN_DM_RES_UP
#define IRR1_DM_RES_DWN         PIN_DM_RES_DWN
#define IRR1_DM_OD_LO           PIN_DM_OD_LO
#define IRR1_DM_OD_HI           PIN_DM_OD_HI
#define IRR1_DM_STRONG          PIN_DM_STRONG
#define IRR1_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define IRR1_MASK               IRR1__MASK
#define IRR1_SHIFT              IRR1__SHIFT
#define IRR1_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define IRR1_PS                     (* (reg8 *) IRR1__PS)
/* Data Register */
#define IRR1_DR                     (* (reg8 *) IRR1__DR)
/* Port Number */
#define IRR1_PRT_NUM                (* (reg8 *) IRR1__PRT) 
/* Connect to Analog Globals */                                                  
#define IRR1_AG                     (* (reg8 *) IRR1__AG)                       
/* Analog MUX bux enable */
#define IRR1_AMUX                   (* (reg8 *) IRR1__AMUX) 
/* Bidirectional Enable */                                                        
#define IRR1_BIE                    (* (reg8 *) IRR1__BIE)
/* Bit-mask for Aliased Register Access */
#define IRR1_BIT_MASK               (* (reg8 *) IRR1__BIT_MASK)
/* Bypass Enable */
#define IRR1_BYP                    (* (reg8 *) IRR1__BYP)
/* Port wide control signals */                                                   
#define IRR1_CTL                    (* (reg8 *) IRR1__CTL)
/* Drive Modes */
#define IRR1_DM0                    (* (reg8 *) IRR1__DM0) 
#define IRR1_DM1                    (* (reg8 *) IRR1__DM1)
#define IRR1_DM2                    (* (reg8 *) IRR1__DM2) 
/* Input Buffer Disable Override */
#define IRR1_INP_DIS                (* (reg8 *) IRR1__INP_DIS)
/* LCD Common or Segment Drive */
#define IRR1_LCD_COM_SEG            (* (reg8 *) IRR1__LCD_COM_SEG)
/* Enable Segment LCD */
#define IRR1_LCD_EN                 (* (reg8 *) IRR1__LCD_EN)
/* Slew Rate Control */
#define IRR1_SLW                    (* (reg8 *) IRR1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define IRR1_PRTDSI__CAPS_SEL       (* (reg8 *) IRR1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define IRR1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) IRR1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define IRR1_PRTDSI__OE_SEL0        (* (reg8 *) IRR1__PRTDSI__OE_SEL0) 
#define IRR1_PRTDSI__OE_SEL1        (* (reg8 *) IRR1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define IRR1_PRTDSI__OUT_SEL0       (* (reg8 *) IRR1__PRTDSI__OUT_SEL0) 
#define IRR1_PRTDSI__OUT_SEL1       (* (reg8 *) IRR1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define IRR1_PRTDSI__SYNC_OUT       (* (reg8 *) IRR1__PRTDSI__SYNC_OUT) 


#if defined(IRR1__INTSTAT)  /* Interrupt Registers */

    #define IRR1_INTSTAT                (* (reg8 *) IRR1__INTSTAT)
    #define IRR1_SNAP                   (* (reg8 *) IRR1__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_IRR1_H */


/* [] END OF FILE */
