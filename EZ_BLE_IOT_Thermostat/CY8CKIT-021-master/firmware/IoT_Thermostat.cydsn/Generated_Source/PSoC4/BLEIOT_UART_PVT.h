/*******************************************************************************
* File Name: .h
* Version 3.10
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PVT_BLEIOT_UART_H)
#define CY_SCB_PVT_BLEIOT_UART_H

#include "BLEIOT_UART.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define BLEIOT_UART_SetI2CExtClkInterruptMode(interruptMask) BLEIOT_UART_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define BLEIOT_UART_ClearI2CExtClkInterruptSource(interruptMask) BLEIOT_UART_CLEAR_INTR_I2C_EC(interruptMask)
#define BLEIOT_UART_GetI2CExtClkInterruptSource()                (BLEIOT_UART_INTR_I2C_EC_REG)
#define BLEIOT_UART_GetI2CExtClkInterruptMode()                  (BLEIOT_UART_INTR_I2C_EC_MASK_REG)
#define BLEIOT_UART_GetI2CExtClkInterruptSourceMasked()          (BLEIOT_UART_INTR_I2C_EC_MASKED_REG)

#if (!BLEIOT_UART_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define BLEIOT_UART_SetSpiExtClkInterruptMode(interruptMask) \
                                                                BLEIOT_UART_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define BLEIOT_UART_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                BLEIOT_UART_CLEAR_INTR_SPI_EC(interruptMask)
    #define BLEIOT_UART_GetExtSpiClkInterruptSource()                 (BLEIOT_UART_INTR_SPI_EC_REG)
    #define BLEIOT_UART_GetExtSpiClkInterruptMode()                   (BLEIOT_UART_INTR_SPI_EC_MASK_REG)
    #define BLEIOT_UART_GetExtSpiClkInterruptSourceMasked()           (BLEIOT_UART_INTR_SPI_EC_MASKED_REG)
#endif /* (!BLEIOT_UART_CY_SCBIP_V1) */

#if(BLEIOT_UART_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void BLEIOT_UART_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (BLEIOT_UART_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (BLEIOT_UART_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_BLEIOT_UART_CUSTOM_INTR_HANDLER)
    extern cyisraddress BLEIOT_UART_customIntrHandler;
#endif /* !defined (CY_REMOVE_BLEIOT_UART_CUSTOM_INTR_HANDLER) */
#endif /* (BLEIOT_UART_SCB_IRQ_INTERNAL) */

extern BLEIOT_UART_BACKUP_STRUCT BLEIOT_UART_backup;

#if(BLEIOT_UART_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 BLEIOT_UART_scbMode;
    extern uint8 BLEIOT_UART_scbEnableWake;
    extern uint8 BLEIOT_UART_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 BLEIOT_UART_mode;
    extern uint8 BLEIOT_UART_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * BLEIOT_UART_rxBuffer;
    extern uint8   BLEIOT_UART_rxDataBits;
    extern uint32  BLEIOT_UART_rxBufferSize;

    extern volatile uint8 * BLEIOT_UART_txBuffer;
    extern uint8   BLEIOT_UART_txDataBits;
    extern uint32  BLEIOT_UART_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 BLEIOT_UART_numberOfAddr;
    extern uint8 BLEIOT_UART_subAddrSize;
#endif /* (BLEIOT_UART_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*        Conditional Macro
****************************************/

#if(BLEIOT_UART_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define BLEIOT_UART_SCB_MODE_I2C_RUNTM_CFG     (BLEIOT_UART_SCB_MODE_I2C      == BLEIOT_UART_scbMode)
    #define BLEIOT_UART_SCB_MODE_SPI_RUNTM_CFG     (BLEIOT_UART_SCB_MODE_SPI      == BLEIOT_UART_scbMode)
    #define BLEIOT_UART_SCB_MODE_UART_RUNTM_CFG    (BLEIOT_UART_SCB_MODE_UART     == BLEIOT_UART_scbMode)
    #define BLEIOT_UART_SCB_MODE_EZI2C_RUNTM_CFG   (BLEIOT_UART_SCB_MODE_EZI2C    == BLEIOT_UART_scbMode)
    #define BLEIOT_UART_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (BLEIOT_UART_SCB_MODE_UNCONFIG == BLEIOT_UART_scbMode)

    /* Defines wakeup enable */
    #define BLEIOT_UART_SCB_WAKE_ENABLE_CHECK       (0u != BLEIOT_UART_scbEnableWake)
#endif /* (BLEIOT_UART_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!BLEIOT_UART_CY_SCBIP_V1)
    #define BLEIOT_UART_SCB_PINS_NUMBER    (7u)
#else
    #define BLEIOT_UART_SCB_PINS_NUMBER    (2u)
#endif /* (!BLEIOT_UART_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_BLEIOT_UART_H) */


/* [] END OF FILE */
