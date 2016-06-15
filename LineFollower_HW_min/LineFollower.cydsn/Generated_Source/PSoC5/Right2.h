/*******************************************************************************
* File Name: Right2.h  
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

#if !defined(CY_PINS_Right2_H) /* Pins Right2_H */
#define CY_PINS_Right2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Right2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Right2__PORT == 15 && ((Right2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Right2_Write(uint8 value);
void    Right2_SetDriveMode(uint8 mode);
uint8   Right2_ReadDataReg(void);
uint8   Right2_Read(void);
void    Right2_SetInterruptMode(uint16 position, uint16 mode);
uint8   Right2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Right2_SetDriveMode() function.
     *  @{
     */
        #define Right2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Right2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Right2_DM_RES_UP          PIN_DM_RES_UP
        #define Right2_DM_RES_DWN         PIN_DM_RES_DWN
        #define Right2_DM_OD_LO           PIN_DM_OD_LO
        #define Right2_DM_OD_HI           PIN_DM_OD_HI
        #define Right2_DM_STRONG          PIN_DM_STRONG
        #define Right2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Right2_MASK               Right2__MASK
#define Right2_SHIFT              Right2__SHIFT
#define Right2_WIDTH              1u

/* Interrupt constants */
#if defined(Right2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Right2_SetInterruptMode() function.
     *  @{
     */
        #define Right2_INTR_NONE      (uint16)(0x0000u)
        #define Right2_INTR_RISING    (uint16)(0x0001u)
        #define Right2_INTR_FALLING   (uint16)(0x0002u)
        #define Right2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Right2_INTR_MASK      (0x01u) 
#endif /* (Right2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Right2_PS                     (* (reg8 *) Right2__PS)
/* Data Register */
#define Right2_DR                     (* (reg8 *) Right2__DR)
/* Port Number */
#define Right2_PRT_NUM                (* (reg8 *) Right2__PRT) 
/* Connect to Analog Globals */                                                  
#define Right2_AG                     (* (reg8 *) Right2__AG)                       
/* Analog MUX bux enable */
#define Right2_AMUX                   (* (reg8 *) Right2__AMUX) 
/* Bidirectional Enable */                                                        
#define Right2_BIE                    (* (reg8 *) Right2__BIE)
/* Bit-mask for Aliased Register Access */
#define Right2_BIT_MASK               (* (reg8 *) Right2__BIT_MASK)
/* Bypass Enable */
#define Right2_BYP                    (* (reg8 *) Right2__BYP)
/* Port wide control signals */                                                   
#define Right2_CTL                    (* (reg8 *) Right2__CTL)
/* Drive Modes */
#define Right2_DM0                    (* (reg8 *) Right2__DM0) 
#define Right2_DM1                    (* (reg8 *) Right2__DM1)
#define Right2_DM2                    (* (reg8 *) Right2__DM2) 
/* Input Buffer Disable Override */
#define Right2_INP_DIS                (* (reg8 *) Right2__INP_DIS)
/* LCD Common or Segment Drive */
#define Right2_LCD_COM_SEG            (* (reg8 *) Right2__LCD_COM_SEG)
/* Enable Segment LCD */
#define Right2_LCD_EN                 (* (reg8 *) Right2__LCD_EN)
/* Slew Rate Control */
#define Right2_SLW                    (* (reg8 *) Right2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Right2_PRTDSI__CAPS_SEL       (* (reg8 *) Right2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Right2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Right2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Right2_PRTDSI__OE_SEL0        (* (reg8 *) Right2__PRTDSI__OE_SEL0) 
#define Right2_PRTDSI__OE_SEL1        (* (reg8 *) Right2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Right2_PRTDSI__OUT_SEL0       (* (reg8 *) Right2__PRTDSI__OUT_SEL0) 
#define Right2_PRTDSI__OUT_SEL1       (* (reg8 *) Right2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Right2_PRTDSI__SYNC_OUT       (* (reg8 *) Right2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Right2__SIO_CFG)
    #define Right2_SIO_HYST_EN        (* (reg8 *) Right2__SIO_HYST_EN)
    #define Right2_SIO_REG_HIFREQ     (* (reg8 *) Right2__SIO_REG_HIFREQ)
    #define Right2_SIO_CFG            (* (reg8 *) Right2__SIO_CFG)
    #define Right2_SIO_DIFF           (* (reg8 *) Right2__SIO_DIFF)
#endif /* (Right2__SIO_CFG) */

/* Interrupt Registers */
#if defined(Right2__INTSTAT)
    #define Right2_INTSTAT            (* (reg8 *) Right2__INTSTAT)
    #define Right2_SNAP               (* (reg8 *) Right2__SNAP)
    
	#define Right2_0_INTTYPE_REG 		(* (reg8 *) Right2__0__INTTYPE)
#endif /* (Right2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Right2_H */


/* [] END OF FILE */
