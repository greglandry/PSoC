/*******************************************************************************
* File Name: Right1.h  
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

#if !defined(CY_PINS_Right1_H) /* Pins Right1_H */
#define CY_PINS_Right1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Right1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Right1__PORT == 15 && ((Right1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Right1_Write(uint8 value);
void    Right1_SetDriveMode(uint8 mode);
uint8   Right1_ReadDataReg(void);
uint8   Right1_Read(void);
void    Right1_SetInterruptMode(uint16 position, uint16 mode);
uint8   Right1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Right1_SetDriveMode() function.
     *  @{
     */
        #define Right1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Right1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Right1_DM_RES_UP          PIN_DM_RES_UP
        #define Right1_DM_RES_DWN         PIN_DM_RES_DWN
        #define Right1_DM_OD_LO           PIN_DM_OD_LO
        #define Right1_DM_OD_HI           PIN_DM_OD_HI
        #define Right1_DM_STRONG          PIN_DM_STRONG
        #define Right1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Right1_MASK               Right1__MASK
#define Right1_SHIFT              Right1__SHIFT
#define Right1_WIDTH              1u

/* Interrupt constants */
#if defined(Right1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Right1_SetInterruptMode() function.
     *  @{
     */
        #define Right1_INTR_NONE      (uint16)(0x0000u)
        #define Right1_INTR_RISING    (uint16)(0x0001u)
        #define Right1_INTR_FALLING   (uint16)(0x0002u)
        #define Right1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Right1_INTR_MASK      (0x01u) 
#endif /* (Right1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Right1_PS                     (* (reg8 *) Right1__PS)
/* Data Register */
#define Right1_DR                     (* (reg8 *) Right1__DR)
/* Port Number */
#define Right1_PRT_NUM                (* (reg8 *) Right1__PRT) 
/* Connect to Analog Globals */                                                  
#define Right1_AG                     (* (reg8 *) Right1__AG)                       
/* Analog MUX bux enable */
#define Right1_AMUX                   (* (reg8 *) Right1__AMUX) 
/* Bidirectional Enable */                                                        
#define Right1_BIE                    (* (reg8 *) Right1__BIE)
/* Bit-mask for Aliased Register Access */
#define Right1_BIT_MASK               (* (reg8 *) Right1__BIT_MASK)
/* Bypass Enable */
#define Right1_BYP                    (* (reg8 *) Right1__BYP)
/* Port wide control signals */                                                   
#define Right1_CTL                    (* (reg8 *) Right1__CTL)
/* Drive Modes */
#define Right1_DM0                    (* (reg8 *) Right1__DM0) 
#define Right1_DM1                    (* (reg8 *) Right1__DM1)
#define Right1_DM2                    (* (reg8 *) Right1__DM2) 
/* Input Buffer Disable Override */
#define Right1_INP_DIS                (* (reg8 *) Right1__INP_DIS)
/* LCD Common or Segment Drive */
#define Right1_LCD_COM_SEG            (* (reg8 *) Right1__LCD_COM_SEG)
/* Enable Segment LCD */
#define Right1_LCD_EN                 (* (reg8 *) Right1__LCD_EN)
/* Slew Rate Control */
#define Right1_SLW                    (* (reg8 *) Right1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Right1_PRTDSI__CAPS_SEL       (* (reg8 *) Right1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Right1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Right1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Right1_PRTDSI__OE_SEL0        (* (reg8 *) Right1__PRTDSI__OE_SEL0) 
#define Right1_PRTDSI__OE_SEL1        (* (reg8 *) Right1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Right1_PRTDSI__OUT_SEL0       (* (reg8 *) Right1__PRTDSI__OUT_SEL0) 
#define Right1_PRTDSI__OUT_SEL1       (* (reg8 *) Right1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Right1_PRTDSI__SYNC_OUT       (* (reg8 *) Right1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Right1__SIO_CFG)
    #define Right1_SIO_HYST_EN        (* (reg8 *) Right1__SIO_HYST_EN)
    #define Right1_SIO_REG_HIFREQ     (* (reg8 *) Right1__SIO_REG_HIFREQ)
    #define Right1_SIO_CFG            (* (reg8 *) Right1__SIO_CFG)
    #define Right1_SIO_DIFF           (* (reg8 *) Right1__SIO_DIFF)
#endif /* (Right1__SIO_CFG) */

/* Interrupt Registers */
#if defined(Right1__INTSTAT)
    #define Right1_INTSTAT            (* (reg8 *) Right1__INTSTAT)
    #define Right1_SNAP               (* (reg8 *) Right1__SNAP)
    
	#define Right1_0_INTTYPE_REG 		(* (reg8 *) Right1__0__INTTYPE)
#endif /* (Right1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Right1_H */


/* [] END OF FILE */
