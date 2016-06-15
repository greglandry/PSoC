/*******************************************************************************
* File Name: MotEn.h  
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

#if !defined(CY_PINS_MotEn_H) /* Pins MotEn_H */
#define CY_PINS_MotEn_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "MotEn_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 MotEn__PORT == 15 && ((MotEn__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    MotEn_Write(uint8 value);
void    MotEn_SetDriveMode(uint8 mode);
uint8   MotEn_ReadDataReg(void);
uint8   MotEn_Read(void);
void    MotEn_SetInterruptMode(uint16 position, uint16 mode);
uint8   MotEn_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the MotEn_SetDriveMode() function.
     *  @{
     */
        #define MotEn_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define MotEn_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define MotEn_DM_RES_UP          PIN_DM_RES_UP
        #define MotEn_DM_RES_DWN         PIN_DM_RES_DWN
        #define MotEn_DM_OD_LO           PIN_DM_OD_LO
        #define MotEn_DM_OD_HI           PIN_DM_OD_HI
        #define MotEn_DM_STRONG          PIN_DM_STRONG
        #define MotEn_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define MotEn_MASK               MotEn__MASK
#define MotEn_SHIFT              MotEn__SHIFT
#define MotEn_WIDTH              1u

/* Interrupt constants */
#if defined(MotEn__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in MotEn_SetInterruptMode() function.
     *  @{
     */
        #define MotEn_INTR_NONE      (uint16)(0x0000u)
        #define MotEn_INTR_RISING    (uint16)(0x0001u)
        #define MotEn_INTR_FALLING   (uint16)(0x0002u)
        #define MotEn_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define MotEn_INTR_MASK      (0x01u) 
#endif /* (MotEn__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MotEn_PS                     (* (reg8 *) MotEn__PS)
/* Data Register */
#define MotEn_DR                     (* (reg8 *) MotEn__DR)
/* Port Number */
#define MotEn_PRT_NUM                (* (reg8 *) MotEn__PRT) 
/* Connect to Analog Globals */                                                  
#define MotEn_AG                     (* (reg8 *) MotEn__AG)                       
/* Analog MUX bux enable */
#define MotEn_AMUX                   (* (reg8 *) MotEn__AMUX) 
/* Bidirectional Enable */                                                        
#define MotEn_BIE                    (* (reg8 *) MotEn__BIE)
/* Bit-mask for Aliased Register Access */
#define MotEn_BIT_MASK               (* (reg8 *) MotEn__BIT_MASK)
/* Bypass Enable */
#define MotEn_BYP                    (* (reg8 *) MotEn__BYP)
/* Port wide control signals */                                                   
#define MotEn_CTL                    (* (reg8 *) MotEn__CTL)
/* Drive Modes */
#define MotEn_DM0                    (* (reg8 *) MotEn__DM0) 
#define MotEn_DM1                    (* (reg8 *) MotEn__DM1)
#define MotEn_DM2                    (* (reg8 *) MotEn__DM2) 
/* Input Buffer Disable Override */
#define MotEn_INP_DIS                (* (reg8 *) MotEn__INP_DIS)
/* LCD Common or Segment Drive */
#define MotEn_LCD_COM_SEG            (* (reg8 *) MotEn__LCD_COM_SEG)
/* Enable Segment LCD */
#define MotEn_LCD_EN                 (* (reg8 *) MotEn__LCD_EN)
/* Slew Rate Control */
#define MotEn_SLW                    (* (reg8 *) MotEn__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define MotEn_PRTDSI__CAPS_SEL       (* (reg8 *) MotEn__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define MotEn_PRTDSI__DBL_SYNC_IN    (* (reg8 *) MotEn__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define MotEn_PRTDSI__OE_SEL0        (* (reg8 *) MotEn__PRTDSI__OE_SEL0) 
#define MotEn_PRTDSI__OE_SEL1        (* (reg8 *) MotEn__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define MotEn_PRTDSI__OUT_SEL0       (* (reg8 *) MotEn__PRTDSI__OUT_SEL0) 
#define MotEn_PRTDSI__OUT_SEL1       (* (reg8 *) MotEn__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define MotEn_PRTDSI__SYNC_OUT       (* (reg8 *) MotEn__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(MotEn__SIO_CFG)
    #define MotEn_SIO_HYST_EN        (* (reg8 *) MotEn__SIO_HYST_EN)
    #define MotEn_SIO_REG_HIFREQ     (* (reg8 *) MotEn__SIO_REG_HIFREQ)
    #define MotEn_SIO_CFG            (* (reg8 *) MotEn__SIO_CFG)
    #define MotEn_SIO_DIFF           (* (reg8 *) MotEn__SIO_DIFF)
#endif /* (MotEn__SIO_CFG) */

/* Interrupt Registers */
#if defined(MotEn__INTSTAT)
    #define MotEn_INTSTAT            (* (reg8 *) MotEn__INTSTAT)
    #define MotEn_SNAP               (* (reg8 *) MotEn__SNAP)
    
	#define MotEn_0_INTTYPE_REG 		(* (reg8 *) MotEn__0__INTTYPE)
#endif /* (MotEn__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_MotEn_H */


/* [] END OF FILE */
