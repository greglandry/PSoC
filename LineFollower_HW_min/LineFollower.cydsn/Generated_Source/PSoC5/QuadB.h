/*******************************************************************************
* File Name: QuadB.h  
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

#if !defined(CY_PINS_QuadB_H) /* Pins QuadB_H */
#define CY_PINS_QuadB_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "QuadB_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 QuadB__PORT == 15 && ((QuadB__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    QuadB_Write(uint8 value) ;
void    QuadB_SetDriveMode(uint8 mode) ;
uint8   QuadB_ReadDataReg(void) ;
uint8   QuadB_Read(void) ;
uint8   QuadB_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define QuadB_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define QuadB_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define QuadB_DM_RES_UP          PIN_DM_RES_UP
#define QuadB_DM_RES_DWN         PIN_DM_RES_DWN
#define QuadB_DM_OD_LO           PIN_DM_OD_LO
#define QuadB_DM_OD_HI           PIN_DM_OD_HI
#define QuadB_DM_STRONG          PIN_DM_STRONG
#define QuadB_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define QuadB_MASK               QuadB__MASK
#define QuadB_SHIFT              QuadB__SHIFT
#define QuadB_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define QuadB_PS                     (* (reg8 *) QuadB__PS)
/* Data Register */
#define QuadB_DR                     (* (reg8 *) QuadB__DR)
/* Port Number */
#define QuadB_PRT_NUM                (* (reg8 *) QuadB__PRT) 
/* Connect to Analog Globals */                                                  
#define QuadB_AG                     (* (reg8 *) QuadB__AG)                       
/* Analog MUX bux enable */
#define QuadB_AMUX                   (* (reg8 *) QuadB__AMUX) 
/* Bidirectional Enable */                                                        
#define QuadB_BIE                    (* (reg8 *) QuadB__BIE)
/* Bit-mask for Aliased Register Access */
#define QuadB_BIT_MASK               (* (reg8 *) QuadB__BIT_MASK)
/* Bypass Enable */
#define QuadB_BYP                    (* (reg8 *) QuadB__BYP)
/* Port wide control signals */                                                   
#define QuadB_CTL                    (* (reg8 *) QuadB__CTL)
/* Drive Modes */
#define QuadB_DM0                    (* (reg8 *) QuadB__DM0) 
#define QuadB_DM1                    (* (reg8 *) QuadB__DM1)
#define QuadB_DM2                    (* (reg8 *) QuadB__DM2) 
/* Input Buffer Disable Override */
#define QuadB_INP_DIS                (* (reg8 *) QuadB__INP_DIS)
/* LCD Common or Segment Drive */
#define QuadB_LCD_COM_SEG            (* (reg8 *) QuadB__LCD_COM_SEG)
/* Enable Segment LCD */
#define QuadB_LCD_EN                 (* (reg8 *) QuadB__LCD_EN)
/* Slew Rate Control */
#define QuadB_SLW                    (* (reg8 *) QuadB__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define QuadB_PRTDSI__CAPS_SEL       (* (reg8 *) QuadB__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define QuadB_PRTDSI__DBL_SYNC_IN    (* (reg8 *) QuadB__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define QuadB_PRTDSI__OE_SEL0        (* (reg8 *) QuadB__PRTDSI__OE_SEL0) 
#define QuadB_PRTDSI__OE_SEL1        (* (reg8 *) QuadB__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define QuadB_PRTDSI__OUT_SEL0       (* (reg8 *) QuadB__PRTDSI__OUT_SEL0) 
#define QuadB_PRTDSI__OUT_SEL1       (* (reg8 *) QuadB__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define QuadB_PRTDSI__SYNC_OUT       (* (reg8 *) QuadB__PRTDSI__SYNC_OUT) 


#if defined(QuadB__INTSTAT)  /* Interrupt Registers */

    #define QuadB_INTSTAT                (* (reg8 *) QuadB__INTSTAT)
    #define QuadB_SNAP                   (* (reg8 *) QuadB__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_QuadB_H */


/* [] END OF FILE */
