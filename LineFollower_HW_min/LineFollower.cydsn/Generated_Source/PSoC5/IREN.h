/*******************************************************************************
* File Name: IREN.h  
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

#if !defined(CY_PINS_IREN_H) /* Pins IREN_H */
#define CY_PINS_IREN_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "IREN_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 IREN__PORT == 15 && ((IREN__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    IREN_Write(uint8 value);
void    IREN_SetDriveMode(uint8 mode);
uint8   IREN_ReadDataReg(void);
uint8   IREN_Read(void);
void    IREN_SetInterruptMode(uint16 position, uint16 mode);
uint8   IREN_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the IREN_SetDriveMode() function.
     *  @{
     */
        #define IREN_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define IREN_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define IREN_DM_RES_UP          PIN_DM_RES_UP
        #define IREN_DM_RES_DWN         PIN_DM_RES_DWN
        #define IREN_DM_OD_LO           PIN_DM_OD_LO
        #define IREN_DM_OD_HI           PIN_DM_OD_HI
        #define IREN_DM_STRONG          PIN_DM_STRONG
        #define IREN_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define IREN_MASK               IREN__MASK
#define IREN_SHIFT              IREN__SHIFT
#define IREN_WIDTH              1u

/* Interrupt constants */
#if defined(IREN__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in IREN_SetInterruptMode() function.
     *  @{
     */
        #define IREN_INTR_NONE      (uint16)(0x0000u)
        #define IREN_INTR_RISING    (uint16)(0x0001u)
        #define IREN_INTR_FALLING   (uint16)(0x0002u)
        #define IREN_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define IREN_INTR_MASK      (0x01u) 
#endif /* (IREN__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define IREN_PS                     (* (reg8 *) IREN__PS)
/* Data Register */
#define IREN_DR                     (* (reg8 *) IREN__DR)
/* Port Number */
#define IREN_PRT_NUM                (* (reg8 *) IREN__PRT) 
/* Connect to Analog Globals */                                                  
#define IREN_AG                     (* (reg8 *) IREN__AG)                       
/* Analog MUX bux enable */
#define IREN_AMUX                   (* (reg8 *) IREN__AMUX) 
/* Bidirectional Enable */                                                        
#define IREN_BIE                    (* (reg8 *) IREN__BIE)
/* Bit-mask for Aliased Register Access */
#define IREN_BIT_MASK               (* (reg8 *) IREN__BIT_MASK)
/* Bypass Enable */
#define IREN_BYP                    (* (reg8 *) IREN__BYP)
/* Port wide control signals */                                                   
#define IREN_CTL                    (* (reg8 *) IREN__CTL)
/* Drive Modes */
#define IREN_DM0                    (* (reg8 *) IREN__DM0) 
#define IREN_DM1                    (* (reg8 *) IREN__DM1)
#define IREN_DM2                    (* (reg8 *) IREN__DM2) 
/* Input Buffer Disable Override */
#define IREN_INP_DIS                (* (reg8 *) IREN__INP_DIS)
/* LCD Common or Segment Drive */
#define IREN_LCD_COM_SEG            (* (reg8 *) IREN__LCD_COM_SEG)
/* Enable Segment LCD */
#define IREN_LCD_EN                 (* (reg8 *) IREN__LCD_EN)
/* Slew Rate Control */
#define IREN_SLW                    (* (reg8 *) IREN__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define IREN_PRTDSI__CAPS_SEL       (* (reg8 *) IREN__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define IREN_PRTDSI__DBL_SYNC_IN    (* (reg8 *) IREN__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define IREN_PRTDSI__OE_SEL0        (* (reg8 *) IREN__PRTDSI__OE_SEL0) 
#define IREN_PRTDSI__OE_SEL1        (* (reg8 *) IREN__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define IREN_PRTDSI__OUT_SEL0       (* (reg8 *) IREN__PRTDSI__OUT_SEL0) 
#define IREN_PRTDSI__OUT_SEL1       (* (reg8 *) IREN__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define IREN_PRTDSI__SYNC_OUT       (* (reg8 *) IREN__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(IREN__SIO_CFG)
    #define IREN_SIO_HYST_EN        (* (reg8 *) IREN__SIO_HYST_EN)
    #define IREN_SIO_REG_HIFREQ     (* (reg8 *) IREN__SIO_REG_HIFREQ)
    #define IREN_SIO_CFG            (* (reg8 *) IREN__SIO_CFG)
    #define IREN_SIO_DIFF           (* (reg8 *) IREN__SIO_DIFF)
#endif /* (IREN__SIO_CFG) */

/* Interrupt Registers */
#if defined(IREN__INTSTAT)
    #define IREN_INTSTAT            (* (reg8 *) IREN__INTSTAT)
    #define IREN_SNAP               (* (reg8 *) IREN__SNAP)
    
	#define IREN_0_INTTYPE_REG 		(* (reg8 *) IREN__0__INTTYPE)
#endif /* (IREN__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_IREN_H */


/* [] END OF FILE */
