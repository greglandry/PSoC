/*******************************************************************************
* File Name: IRL2.h  
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

#if !defined(CY_PINS_IRL2_H) /* Pins IRL2_H */
#define CY_PINS_IRL2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "IRL2_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 IRL2__PORT == 15 && ((IRL2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    IRL2_Write(uint8 value) ;
void    IRL2_SetDriveMode(uint8 mode) ;
uint8   IRL2_ReadDataReg(void) ;
uint8   IRL2_Read(void) ;
uint8   IRL2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define IRL2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define IRL2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define IRL2_DM_RES_UP          PIN_DM_RES_UP
#define IRL2_DM_RES_DWN         PIN_DM_RES_DWN
#define IRL2_DM_OD_LO           PIN_DM_OD_LO
#define IRL2_DM_OD_HI           PIN_DM_OD_HI
#define IRL2_DM_STRONG          PIN_DM_STRONG
#define IRL2_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define IRL2_MASK               IRL2__MASK
#define IRL2_SHIFT              IRL2__SHIFT
#define IRL2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define IRL2_PS                     (* (reg8 *) IRL2__PS)
/* Data Register */
#define IRL2_DR                     (* (reg8 *) IRL2__DR)
/* Port Number */
#define IRL2_PRT_NUM                (* (reg8 *) IRL2__PRT) 
/* Connect to Analog Globals */                                                  
#define IRL2_AG                     (* (reg8 *) IRL2__AG)                       
/* Analog MUX bux enable */
#define IRL2_AMUX                   (* (reg8 *) IRL2__AMUX) 
/* Bidirectional Enable */                                                        
#define IRL2_BIE                    (* (reg8 *) IRL2__BIE)
/* Bit-mask for Aliased Register Access */
#define IRL2_BIT_MASK               (* (reg8 *) IRL2__BIT_MASK)
/* Bypass Enable */
#define IRL2_BYP                    (* (reg8 *) IRL2__BYP)
/* Port wide control signals */                                                   
#define IRL2_CTL                    (* (reg8 *) IRL2__CTL)
/* Drive Modes */
#define IRL2_DM0                    (* (reg8 *) IRL2__DM0) 
#define IRL2_DM1                    (* (reg8 *) IRL2__DM1)
#define IRL2_DM2                    (* (reg8 *) IRL2__DM2) 
/* Input Buffer Disable Override */
#define IRL2_INP_DIS                (* (reg8 *) IRL2__INP_DIS)
/* LCD Common or Segment Drive */
#define IRL2_LCD_COM_SEG            (* (reg8 *) IRL2__LCD_COM_SEG)
/* Enable Segment LCD */
#define IRL2_LCD_EN                 (* (reg8 *) IRL2__LCD_EN)
/* Slew Rate Control */
#define IRL2_SLW                    (* (reg8 *) IRL2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define IRL2_PRTDSI__CAPS_SEL       (* (reg8 *) IRL2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define IRL2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) IRL2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define IRL2_PRTDSI__OE_SEL0        (* (reg8 *) IRL2__PRTDSI__OE_SEL0) 
#define IRL2_PRTDSI__OE_SEL1        (* (reg8 *) IRL2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define IRL2_PRTDSI__OUT_SEL0       (* (reg8 *) IRL2__PRTDSI__OUT_SEL0) 
#define IRL2_PRTDSI__OUT_SEL1       (* (reg8 *) IRL2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define IRL2_PRTDSI__SYNC_OUT       (* (reg8 *) IRL2__PRTDSI__SYNC_OUT) 


#if defined(IRL2__INTSTAT)  /* Interrupt Registers */

    #define IRL2_INTSTAT                (* (reg8 *) IRL2__INTSTAT)
    #define IRL2_SNAP                   (* (reg8 *) IRL2__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_IRL2_H */


/* [] END OF FILE */
