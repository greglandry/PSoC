/*******************************************************************************
* File Name: Left2.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Left2_H) /* Pins Left2_H */
#define CY_PINS_Left2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Left2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Left2__PORT == 15 && ((Left2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Left2_Write(uint8 value);
void    Left2_SetDriveMode(uint8 mode);
uint8   Left2_ReadDataReg(void);
uint8   Left2_Read(void);
void    Left2_SetInterruptMode(uint16 position, uint16 mode);
uint8   Left2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Left2_SetDriveMode() function.
     *  @{
     */
        #define Left2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Left2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Left2_DM_RES_UP          PIN_DM_RES_UP
        #define Left2_DM_RES_DWN         PIN_DM_RES_DWN
        #define Left2_DM_OD_LO           PIN_DM_OD_LO
        #define Left2_DM_OD_HI           PIN_DM_OD_HI
        #define Left2_DM_STRONG          PIN_DM_STRONG
        #define Left2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Left2_MASK               Left2__MASK
#define Left2_SHIFT              Left2__SHIFT
#define Left2_WIDTH              1u

/* Interrupt constants */
#if defined(Left2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Left2_SetInterruptMode() function.
     *  @{
     */
        #define Left2_INTR_NONE      (uint16)(0x0000u)
        #define Left2_INTR_RISING    (uint16)(0x0001u)
        #define Left2_INTR_FALLING   (uint16)(0x0002u)
        #define Left2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Left2_INTR_MASK      (0x01u) 
#endif /* (Left2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Left2_PS                     (* (reg8 *) Left2__PS)
/* Data Register */
#define Left2_DR                     (* (reg8 *) Left2__DR)
/* Port Number */
#define Left2_PRT_NUM                (* (reg8 *) Left2__PRT) 
/* Connect to Analog Globals */                                                  
#define Left2_AG                     (* (reg8 *) Left2__AG)                       
/* Analog MUX bux enable */
#define Left2_AMUX                   (* (reg8 *) Left2__AMUX) 
/* Bidirectional Enable */                                                        
#define Left2_BIE                    (* (reg8 *) Left2__BIE)
/* Bit-mask for Aliased Register Access */
#define Left2_BIT_MASK               (* (reg8 *) Left2__BIT_MASK)
/* Bypass Enable */
#define Left2_BYP                    (* (reg8 *) Left2__BYP)
/* Port wide control signals */                                                   
#define Left2_CTL                    (* (reg8 *) Left2__CTL)
/* Drive Modes */
#define Left2_DM0                    (* (reg8 *) Left2__DM0) 
#define Left2_DM1                    (* (reg8 *) Left2__DM1)
#define Left2_DM2                    (* (reg8 *) Left2__DM2) 
/* Input Buffer Disable Override */
#define Left2_INP_DIS                (* (reg8 *) Left2__INP_DIS)
/* LCD Common or Segment Drive */
#define Left2_LCD_COM_SEG            (* (reg8 *) Left2__LCD_COM_SEG)
/* Enable Segment LCD */
#define Left2_LCD_EN                 (* (reg8 *) Left2__LCD_EN)
/* Slew Rate Control */
#define Left2_SLW                    (* (reg8 *) Left2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Left2_PRTDSI__CAPS_SEL       (* (reg8 *) Left2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Left2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Left2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Left2_PRTDSI__OE_SEL0        (* (reg8 *) Left2__PRTDSI__OE_SEL0) 
#define Left2_PRTDSI__OE_SEL1        (* (reg8 *) Left2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Left2_PRTDSI__OUT_SEL0       (* (reg8 *) Left2__PRTDSI__OUT_SEL0) 
#define Left2_PRTDSI__OUT_SEL1       (* (reg8 *) Left2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Left2_PRTDSI__SYNC_OUT       (* (reg8 *) Left2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Left2__SIO_CFG)
    #define Left2_SIO_HYST_EN        (* (reg8 *) Left2__SIO_HYST_EN)
    #define Left2_SIO_REG_HIFREQ     (* (reg8 *) Left2__SIO_REG_HIFREQ)
    #define Left2_SIO_CFG            (* (reg8 *) Left2__SIO_CFG)
    #define Left2_SIO_DIFF           (* (reg8 *) Left2__SIO_DIFF)
#endif /* (Left2__SIO_CFG) */

/* Interrupt Registers */
#if defined(Left2__INTSTAT)
    #define Left2_INTSTAT            (* (reg8 *) Left2__INTSTAT)
    #define Left2_SNAP               (* (reg8 *) Left2__SNAP)
    
	#define Left2_0_INTTYPE_REG 		(* (reg8 *) Left2__0__INTTYPE)
#endif /* (Left2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Left2_H */


/* [] END OF FILE */
