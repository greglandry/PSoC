/*******************************************************************************
* File Name: BLEIOT_UART_BOOT.h
* Version 3.10
*
* Description:
*  This file provides constants and parameter values of the bootloader
*  communication APIs for the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2014-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_BOOT_BLEIOT_UART_H)
#define CY_SCB_BOOT_BLEIOT_UART_H

#include "BLEIOT_UART_PVT.h"

#if (BLEIOT_UART_SCB_MODE_I2C_INC)
    #include "BLEIOT_UART_I2C.h"
#endif /* (BLEIOT_UART_SCB_MODE_I2C_INC) */

#if (BLEIOT_UART_SCB_MODE_EZI2C_INC)
    #include "BLEIOT_UART_EZI2C.h"
#endif /* (BLEIOT_UART_SCB_MODE_EZI2C_INC) */

#if (BLEIOT_UART_SCB_MODE_SPI_INC || BLEIOT_UART_SCB_MODE_UART_INC)
    #include "BLEIOT_UART_SPI_UART.h"
#endif /* (BLEIOT_UART_SCB_MODE_SPI_INC || BLEIOT_UART_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define BLEIOT_UART_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_BLEIOT_UART) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (BLEIOT_UART_SCB_MODE_I2C_INC)
    #define BLEIOT_UART_I2C_BTLDR_COMM_ENABLED     (BLEIOT_UART_BTLDR_COMM_ENABLED && \
                                                            (BLEIOT_UART_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             BLEIOT_UART_I2C_SLAVE_CONST))
#else
     #define BLEIOT_UART_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (BLEIOT_UART_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (BLEIOT_UART_SCB_MODE_EZI2C_INC)
    #define BLEIOT_UART_EZI2C_BTLDR_COMM_ENABLED   (BLEIOT_UART_BTLDR_COMM_ENABLED && \
                                                         BLEIOT_UART_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define BLEIOT_UART_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (BLEIOT_UART_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (BLEIOT_UART_SCB_MODE_SPI_INC)
    #define BLEIOT_UART_SPI_BTLDR_COMM_ENABLED     (BLEIOT_UART_BTLDR_COMM_ENABLED && \
                                                            (BLEIOT_UART_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             BLEIOT_UART_SPI_SLAVE_CONST))
#else
        #define BLEIOT_UART_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (BLEIOT_UART_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (BLEIOT_UART_SCB_MODE_UART_INC)
       #define BLEIOT_UART_UART_BTLDR_COMM_ENABLED    (BLEIOT_UART_BTLDR_COMM_ENABLED && \
                                                            (BLEIOT_UART_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (BLEIOT_UART_UART_RX_DIRECTION && \
                                                              BLEIOT_UART_UART_TX_DIRECTION)))
#else
     #define BLEIOT_UART_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (BLEIOT_UART_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define BLEIOT_UART_BTLDR_COMM_MODE_ENABLED    (BLEIOT_UART_I2C_BTLDR_COMM_ENABLED   || \
                                                     BLEIOT_UART_SPI_BTLDR_COMM_ENABLED   || \
                                                     BLEIOT_UART_EZI2C_BTLDR_COMM_ENABLED || \
                                                     BLEIOT_UART_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (BLEIOT_UART_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void BLEIOT_UART_I2CCyBtldrCommStart(void);
    void BLEIOT_UART_I2CCyBtldrCommStop (void);
    void BLEIOT_UART_I2CCyBtldrCommReset(void);
    cystatus BLEIOT_UART_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus BLEIOT_UART_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (BLEIOT_UART_SCB_MODE_I2C_CONST_CFG)
        #define BLEIOT_UART_CyBtldrCommStart   BLEIOT_UART_I2CCyBtldrCommStart
        #define BLEIOT_UART_CyBtldrCommStop    BLEIOT_UART_I2CCyBtldrCommStop
        #define BLEIOT_UART_CyBtldrCommReset   BLEIOT_UART_I2CCyBtldrCommReset
        #define BLEIOT_UART_CyBtldrCommRead    BLEIOT_UART_I2CCyBtldrCommRead
        #define BLEIOT_UART_CyBtldrCommWrite   BLEIOT_UART_I2CCyBtldrCommWrite
    #endif /* (BLEIOT_UART_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (BLEIOT_UART_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (BLEIOT_UART_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void BLEIOT_UART_EzI2CCyBtldrCommStart(void);
    void BLEIOT_UART_EzI2CCyBtldrCommStop (void);
    void BLEIOT_UART_EzI2CCyBtldrCommReset(void);
    cystatus BLEIOT_UART_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus BLEIOT_UART_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (BLEIOT_UART_SCB_MODE_EZI2C_CONST_CFG)
        #define BLEIOT_UART_CyBtldrCommStart   BLEIOT_UART_EzI2CCyBtldrCommStart
        #define BLEIOT_UART_CyBtldrCommStop    BLEIOT_UART_EzI2CCyBtldrCommStop
        #define BLEIOT_UART_CyBtldrCommReset   BLEIOT_UART_EzI2CCyBtldrCommReset
        #define BLEIOT_UART_CyBtldrCommRead    BLEIOT_UART_EzI2CCyBtldrCommRead
        #define BLEIOT_UART_CyBtldrCommWrite   BLEIOT_UART_EzI2CCyBtldrCommWrite
    #endif /* (BLEIOT_UART_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (BLEIOT_UART_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (BLEIOT_UART_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void BLEIOT_UART_SpiCyBtldrCommStart(void);
    void BLEIOT_UART_SpiCyBtldrCommStop (void);
    void BLEIOT_UART_SpiCyBtldrCommReset(void);
    cystatus BLEIOT_UART_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus BLEIOT_UART_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (BLEIOT_UART_SCB_MODE_SPI_CONST_CFG)
        #define BLEIOT_UART_CyBtldrCommStart   BLEIOT_UART_SpiCyBtldrCommStart
        #define BLEIOT_UART_CyBtldrCommStop    BLEIOT_UART_SpiCyBtldrCommStop
        #define BLEIOT_UART_CyBtldrCommReset   BLEIOT_UART_SpiCyBtldrCommReset
        #define BLEIOT_UART_CyBtldrCommRead    BLEIOT_UART_SpiCyBtldrCommRead
        #define BLEIOT_UART_CyBtldrCommWrite   BLEIOT_UART_SpiCyBtldrCommWrite
    #endif /* (BLEIOT_UART_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (BLEIOT_UART_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (BLEIOT_UART_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void BLEIOT_UART_UartCyBtldrCommStart(void);
    void BLEIOT_UART_UartCyBtldrCommStop (void);
    void BLEIOT_UART_UartCyBtldrCommReset(void);
    cystatus BLEIOT_UART_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus BLEIOT_UART_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (BLEIOT_UART_SCB_MODE_UART_CONST_CFG)
        #define BLEIOT_UART_CyBtldrCommStart   BLEIOT_UART_UartCyBtldrCommStart
        #define BLEIOT_UART_CyBtldrCommStop    BLEIOT_UART_UartCyBtldrCommStop
        #define BLEIOT_UART_CyBtldrCommReset   BLEIOT_UART_UartCyBtldrCommReset
        #define BLEIOT_UART_CyBtldrCommRead    BLEIOT_UART_UartCyBtldrCommRead
        #define BLEIOT_UART_CyBtldrCommWrite   BLEIOT_UART_UartCyBtldrCommWrite
    #endif /* (BLEIOT_UART_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (BLEIOT_UART_UART_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (BLEIOT_UART_BTLDR_COMM_ENABLED)
    #if (BLEIOT_UART_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void BLEIOT_UART_CyBtldrCommStart(void);
        void BLEIOT_UART_CyBtldrCommStop (void);
        void BLEIOT_UART_CyBtldrCommReset(void);
        cystatus BLEIOT_UART_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus BLEIOT_UART_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (BLEIOT_UART_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_BLEIOT_UART)
        #define CyBtldrCommStart    BLEIOT_UART_CyBtldrCommStart
        #define CyBtldrCommStop     BLEIOT_UART_CyBtldrCommStop
        #define CyBtldrCommReset    BLEIOT_UART_CyBtldrCommReset
        #define CyBtldrCommWrite    BLEIOT_UART_CyBtldrCommWrite
        #define CyBtldrCommRead     BLEIOT_UART_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_BLEIOT_UART) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (BLEIOT_UART_BTLDR_COMM_ENABLED) */


/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define BLEIOT_UART_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define BLEIOT_UART_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define BLEIOT_UART_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define BLEIOT_UART_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef BLEIOT_UART_SPI_BYTE_TO_BYTE
    #define BLEIOT_UART_SPI_BYTE_TO_BYTE   (160u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef BLEIOT_UART_UART_BYTE_TO_BYTE
    #define BLEIOT_UART_UART_BYTE_TO_BYTE  (175u)
#endif /* BLEIOT_UART_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_BLEIOT_UART_H) */


/* [] END OF FILE */
