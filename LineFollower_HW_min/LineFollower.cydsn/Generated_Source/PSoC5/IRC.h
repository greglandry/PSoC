/*******************************************************************************
* File Name: IRC.h  
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

#if !defined(CY_PINS_IRC_H) /* Pins IRC_H */
#define CY_PINS_IRC_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "IRC_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 IRC__PORT == 15 && ((IRC__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    IRC_Write(uint8 value) ;
void    IRC_SetDriveMode(uint8 mode) ;
uint8   IRC_ReadDataReg(void) ;
uint8   IRC_Read(void) ;
uint8   IRC_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define IRC_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define IRC_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define IRC_DM_RES_UP          PIN_DM_RES_UP
#define IRC_DM_RES_DWN         PIN_DM_RES_DWN
#define IRC_DM_OD_LO           PIN_DM_OD_LO
#define IRC_DM_OD_HI           PIN_DM_OD_HI
#define IRC_DM_STRONG          PIN_DM_STRONG
#define IRC_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define IRC_MASK               IRC__MASK
#define IRC_SHIFT              IRC__SHIFT
#define IRC_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define IRC_PS                     (* (reg8 *) IRC__PS)
/* Data Register */
#define IRC_DR                     (* (reg8 *) IRC__DR)
/* Port Number */
#define IRC_PRT_NUM                (* (reg8 *) IRC__PRT) 
/* Connect to Analog Globals */                                                  
#define IRC_AG                     (* (reg8 *) IRC__AG)                       
/* Analog MUX bux enable */
#define IRC_AMUX                   (* (reg8 *) IRC__AMUX) 
/* Bidirectional Enable */                                                        
#define IRC_BIE                    (* (reg8 *) IRC__BIE)
/* Bit-mask for Aliased Register Access */
#define IRC_BIT_MASK               (* (reg8 *) IRC__BIT_MASK)
/* Bypass Enable */
#define IRC_BYP                    (* (reg8 *) IRC__BYP)
/* Port wide control signals */                                                   
#define IRC_CTL                    (* (reg8 *) IRC__CTL)
/* Drive Modes */
#define IRC_DM0                    (* (reg8 *) IRC__DM0) 
#define IRC_DM1                    (* (reg8 *) IRC__DM1)
#define IRC_DM2                    (* (reg8 *) IRC__DM2) 
/* Input Buffer Disable Override */
#define IRC_INP_DIS                (* (reg8 *) IRC__INP_DIS)
/* LCD Common or Segment Drive */
#define IRC_LCD_COM_SEG            (* (reg8 *) IRC__LCD_COM_SEG)
/* Enable Segment LCD */
#define IRC_LCD_EN                 (* (reg8 *) IRC__LCD_EN)
/* Slew Rate Control */
#define IRC_SLW                    (* (reg8 *) IRC__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define IRC_PRTDSI__CAPS_SEL       (* (reg8 *) IRC__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define IRC_PRTDSI__DBL_SYNC_IN    (* (reg8 *) IRC__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define IRC_PRTDSI__OE_SEL0        (* (reg8 *) IRC__PRTDSI__OE_SEL0) 
#define IRC_PRTDSI__OE_SEL1        (* (reg8 *) IRC__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define IRC_PRTDSI__OUT_SEL0       (* (reg8 *) IRC__PRTDSI__OUT_SEL0) 
#define IRC_PRTDSI__OUT_SEL1       (* (reg8 *) IRC__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define IRC_PRTDSI__SYNC_OUT       (* (reg8 *) IRC__PRTDSI__SYNC_OUT) 


#if defined(IRC__INTSTAT)  /* Interrupt Registers */

    #define IRC_INTSTAT                (* (reg8 *) IRC__INTSTAT)
    #define IRC_SNAP                   (* (reg8 *) IRC__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_IRC_H */


/* [] END OF FILE */
