/*******************************************************************************
* File Name: BLEIOT_UART_SPI_UART_PVT.h
* Version 3.10
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component in SPI and UART modes.
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

#if !defined(CY_SCB_SPI_UART_PVT_BLEIOT_UART_H)
#define CY_SCB_SPI_UART_PVT_BLEIOT_UART_H

#include "BLEIOT_UART_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (BLEIOT_UART_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  BLEIOT_UART_rxBufferHead;
    extern volatile uint32  BLEIOT_UART_rxBufferTail;
    extern volatile uint8   BLEIOT_UART_rxBufferOverflow;
#endif /* (BLEIOT_UART_INTERNAL_RX_SW_BUFFER_CONST) */

#if (BLEIOT_UART_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  BLEIOT_UART_txBufferHead;
    extern volatile uint32  BLEIOT_UART_txBufferTail;
#endif /* (BLEIOT_UART_INTERNAL_TX_SW_BUFFER_CONST) */

#if (BLEIOT_UART_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 BLEIOT_UART_rxBufferInternal[BLEIOT_UART_INTERNAL_RX_BUFFER_SIZE];
#endif /* (BLEIOT_UART_INTERNAL_RX_SW_BUFFER) */

#if (BLEIOT_UART_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 BLEIOT_UART_txBufferInternal[BLEIOT_UART_TX_BUFFER_SIZE];
#endif /* (BLEIOT_UART_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void BLEIOT_UART_SpiPostEnable(void);
void BLEIOT_UART_SpiStop(void);

#if (BLEIOT_UART_SCB_MODE_SPI_CONST_CFG)
    void BLEIOT_UART_SpiInit(void);
#endif /* (BLEIOT_UART_SCB_MODE_SPI_CONST_CFG) */

#if (BLEIOT_UART_SPI_WAKE_ENABLE_CONST)
    void BLEIOT_UART_SpiSaveConfig(void);
    void BLEIOT_UART_SpiRestoreConfig(void);
#endif /* (BLEIOT_UART_SPI_WAKE_ENABLE_CONST) */

void BLEIOT_UART_UartPostEnable(void);
void BLEIOT_UART_UartStop(void);

#if (BLEIOT_UART_SCB_MODE_UART_CONST_CFG)
    void BLEIOT_UART_UartInit(void);
#endif /* (BLEIOT_UART_SCB_MODE_UART_CONST_CFG) */

#if (BLEIOT_UART_UART_WAKE_ENABLE_CONST)
    void BLEIOT_UART_UartSaveConfig(void);
    void BLEIOT_UART_UartRestoreConfig(void);
#endif /* (BLEIOT_UART_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in BLEIOT_UART_SetPins() */
#define BLEIOT_UART_UART_RX_PIN_ENABLE    (BLEIOT_UART_UART_RX)
#define BLEIOT_UART_UART_TX_PIN_ENABLE    (BLEIOT_UART_UART_TX)

/* UART RTS and CTS position to be used in  BLEIOT_UART_SetPins() */
#define BLEIOT_UART_UART_RTS_PIN_ENABLE    (0x10u)
#define BLEIOT_UART_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define BLEIOT_UART_SpiUartEnableIntRx(intSourceMask)  BLEIOT_UART_SetRxInterruptMode(intSourceMask)
#define BLEIOT_UART_SpiUartEnableIntTx(intSourceMask)  BLEIOT_UART_SetTxInterruptMode(intSourceMask)
uint32  BLEIOT_UART_SpiUartDisableIntRx(void);
uint32  BLEIOT_UART_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_BLEIOT_UART_H) */


/* [] END OF FILE */
