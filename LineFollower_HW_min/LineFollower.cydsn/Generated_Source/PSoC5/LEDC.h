/*******************************************************************************
* File Name: LEDC.h  
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

#if !defined(CY_PINS_LEDC_H) /* Pins LEDC_H */
#define CY_PINS_LEDC_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LEDC_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_5 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LEDC__PORT == 15 && ((LEDC__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    LEDC_Write(uint8 value) ;
void    LEDC_SetDriveMode(uint8 mode) ;
uint8   LEDC_ReadDataReg(void) ;
uint8   LEDC_Read(void) ;
uint8   LEDC_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define LEDC_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define LEDC_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define LEDC_DM_RES_UP          PIN_DM_RES_UP
#define LEDC_DM_RES_DWN         PIN_DM_RES_DWN
#define LEDC_DM_OD_LO           PIN_DM_OD_LO
#define LEDC_DM_OD_HI           PIN_DM_OD_HI
#define LEDC_DM_STRONG          PIN_DM_STRONG
#define LEDC_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define LEDC_MASK               LEDC__MASK
#define LEDC_SHIFT              LEDC__SHIFT
#define LEDC_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LEDC_PS                     (* (reg8 *) LEDC__PS)
/* Data Register */
#define LEDC_DR                     (* (reg8 *) LEDC__DR)
/* Port Number */
#define LEDC_PRT_NUM                (* (reg8 *) LEDC__PRT) 
/* Connect to Analog Globals */                                                  
#define LEDC_AG                     (* (reg8 *) LEDC__AG)                       
/* Analog MUX bux enable */
#define LEDC_AMUX                   (* (reg8 *) LEDC__AMUX) 
/* Bidirectional Enable */                                                        
#define LEDC_BIE                    (* (reg8 *) LEDC__BIE)
/* Bit-mask for Aliased Register Access */
#define LEDC_BIT_MASK               (* (reg8 *) LEDC__BIT_MASK)
/* Bypass Enable */
#define LEDC_BYP                    (* (reg8 *) LEDC__BYP)
/* Port wide control signals */                                                   
#define LEDC_CTL                    (* (reg8 *) LEDC__CTL)
/* Drive Modes */
#define LEDC_DM0                    (* (reg8 *) LEDC__DM0) 
#define LEDC_DM1                    (* (reg8 *) LEDC__DM1)
#define LEDC_DM2                    (* (reg8 *) LEDC__DM2) 
/* Input Buffer Disable Override */
#define LEDC_INP_DIS                (* (reg8 *) LEDC__INP_DIS)
/* LCD Common or Segment Drive */
#define LEDC_LCD_COM_SEG            (* (reg8 *) LEDC__LCD_COM_SEG)
/* Enable Segment LCD */
#define LEDC_LCD_EN                 (* (reg8 *) LEDC__LCD_EN)
/* Slew Rate Control */
#define LEDC_SLW                    (* (reg8 *) LEDC__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LEDC_PRTDSI__CAPS_SEL       (* (reg8 *) LEDC__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LEDC_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LEDC__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LEDC_PRTDSI__OE_SEL0        (* (reg8 *) LEDC__PRTDSI__OE_SEL0) 
#define LEDC_PRTDSI__OE_SEL1        (* (reg8 *) LEDC__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LEDC_PRTDSI__OUT_SEL0       (* (reg8 *) LEDC__PRTDSI__OUT_SEL0) 
#define LEDC_PRTDSI__OUT_SEL1       (* (reg8 *) LEDC__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LEDC_PRTDSI__SYNC_OUT       (* (reg8 *) LEDC__PRTDSI__SYNC_OUT) 


#if defined(LEDC__INTSTAT)  /* Interrupt Registers */

    #define LEDC_INTSTAT                (* (reg8 *) LEDC__INTSTAT)
    #define LEDC_SNAP                   (* (reg8 *) LEDC__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LEDC_H */


/* [] END OF FILE */
