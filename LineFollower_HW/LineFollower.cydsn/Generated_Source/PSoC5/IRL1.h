/*******************************************************************************
* File Name: IRL1.h  
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

#if !defined(CY_PINS_IRL1_H) /* Pins IRL1_H */
#define CY_PINS_IRL1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "IRL1_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 IRL1__PORT == 15 && ((IRL1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    IRL1_Write(uint8 value) ;
void    IRL1_SetDriveMode(uint8 mode) ;
uint8   IRL1_ReadDataReg(void) ;
uint8   IRL1_Read(void) ;
uint8   IRL1_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define IRL1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define IRL1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define IRL1_DM_RES_UP          PIN_DM_RES_UP
#define IRL1_DM_RES_DWN         PIN_DM_RES_DWN
#define IRL1_DM_OD_LO           PIN_DM_OD_LO
#define IRL1_DM_OD_HI           PIN_DM_OD_HI
#define IRL1_DM_STRONG          PIN_DM_STRONG
#define IRL1_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define IRL1_MASK               IRL1__MASK
#define IRL1_SHIFT              IRL1__SHIFT
#define IRL1_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define IRL1_PS                     (* (reg8 *) IRL1__PS)
/* Data Register */
#define IRL1_DR                     (* (reg8 *) IRL1__DR)
/* Port Number */
#define IRL1_PRT_NUM                (* (reg8 *) IRL1__PRT) 
/* Connect to Analog Globals */                                                  
#define IRL1_AG                     (* (reg8 *) IRL1__AG)                       
/* Analog MUX bux enable */
#define IRL1_AMUX                   (* (reg8 *) IRL1__AMUX) 
/* Bidirectional Enable */                                                        
#define IRL1_BIE                    (* (reg8 *) IRL1__BIE)
/* Bit-mask for Aliased Register Access */
#define IRL1_BIT_MASK               (* (reg8 *) IRL1__BIT_MASK)
/* Bypass Enable */
#define IRL1_BYP                    (* (reg8 *) IRL1__BYP)
/* Port wide control signals */                                                   
#define IRL1_CTL                    (* (reg8 *) IRL1__CTL)
/* Drive Modes */
#define IRL1_DM0                    (* (reg8 *) IRL1__DM0) 
#define IRL1_DM1                    (* (reg8 *) IRL1__DM1)
#define IRL1_DM2                    (* (reg8 *) IRL1__DM2) 
/* Input Buffer Disable Override */
#define IRL1_INP_DIS                (* (reg8 *) IRL1__INP_DIS)
/* LCD Common or Segment Drive */
#define IRL1_LCD_COM_SEG            (* (reg8 *) IRL1__LCD_COM_SEG)
/* Enable Segment LCD */
#define IRL1_LCD_EN                 (* (reg8 *) IRL1__LCD_EN)
/* Slew Rate Control */
#define IRL1_SLW                    (* (reg8 *) IRL1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define IRL1_PRTDSI__CAPS_SEL       (* (reg8 *) IRL1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define IRL1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) IRL1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define IRL1_PRTDSI__OE_SEL0        (* (reg8 *) IRL1__PRTDSI__OE_SEL0) 
#define IRL1_PRTDSI__OE_SEL1        (* (reg8 *) IRL1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define IRL1_PRTDSI__OUT_SEL0       (* (reg8 *) IRL1__PRTDSI__OUT_SEL0) 
#define IRL1_PRTDSI__OUT_SEL1       (* (reg8 *) IRL1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define IRL1_PRTDSI__SYNC_OUT       (* (reg8 *) IRL1__PRTDSI__SYNC_OUT) 


#if defined(IRL1__INTSTAT)  /* Interrupt Registers */

    #define IRL1_INTSTAT                (* (reg8 *) IRL1__INTSTAT)
    #define IRL1_SNAP                   (* (reg8 *) IRL1__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_IRL1_H */


/* [] END OF FILE */
