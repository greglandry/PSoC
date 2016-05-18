/*******************************************************************************
* File Name: BLEIOT_UART_SPI_UART.h
* Version 3.10
*
* Description:
*  This file provides constants and parameter values for the SCB Component in
*  SPI and UART modes.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_SPI_UART_BLEIOT_UART_H)
#define CY_SCB_SPI_UART_BLEIOT_UART_H

#include "BLEIOT_UART.h"


/***************************************
*   SPI Initial Parameter Constants
****************************************/

#define BLEIOT_UART_SPI_MODE                   (0u)
#define BLEIOT_UART_SPI_SUB_MODE               (0u)
#define BLEIOT_UART_SPI_CLOCK_MODE             (0u)
#define BLEIOT_UART_SPI_OVS_FACTOR             (16u)
#define BLEIOT_UART_SPI_MEDIAN_FILTER_ENABLE   (0u)
#define BLEIOT_UART_SPI_LATE_MISO_SAMPLE_ENABLE (0u)
#define BLEIOT_UART_SPI_RX_DATA_BITS_NUM       (8u)
#define BLEIOT_UART_SPI_TX_DATA_BITS_NUM       (8u)
#define BLEIOT_UART_SPI_WAKE_ENABLE            (0u)
#define BLEIOT_UART_SPI_BITS_ORDER             (1u)
#define BLEIOT_UART_SPI_TRANSFER_SEPARATION    (1u)
#define BLEIOT_UART_SPI_NUMBER_OF_SS_LINES     (1u)
#define BLEIOT_UART_SPI_RX_BUFFER_SIZE         (8u)
#define BLEIOT_UART_SPI_TX_BUFFER_SIZE         (8u)

#define BLEIOT_UART_SPI_INTERRUPT_MODE         (0u)

#define BLEIOT_UART_SPI_INTR_RX_MASK           (0u)
#define BLEIOT_UART_SPI_INTR_TX_MASK           (0u)

#define BLEIOT_UART_SPI_RX_TRIGGER_LEVEL       (7u)
#define BLEIOT_UART_SPI_TX_TRIGGER_LEVEL       (0u)

#define BLEIOT_UART_SPI_BYTE_MODE_ENABLE       (0u)
#define BLEIOT_UART_SPI_FREE_RUN_SCLK_ENABLE   (0u)
#define BLEIOT_UART_SPI_SS0_POLARITY           (0u)
#define BLEIOT_UART_SPI_SS1_POLARITY           (0u)
#define BLEIOT_UART_SPI_SS2_POLARITY           (0u)
#define BLEIOT_UART_SPI_SS3_POLARITY           (0u)


/***************************************
*   UART Initial Parameter Constants
****************************************/

#define BLEIOT_UART_UART_SUB_MODE              (0u)
#define BLEIOT_UART_UART_DIRECTION             (3u)
#define BLEIOT_UART_UART_DATA_BITS_NUM         (8u)
#define BLEIOT_UART_UART_PARITY_TYPE           (2u)
#define BLEIOT_UART_UART_STOP_BITS_NUM         (2u)
#define BLEIOT_UART_UART_OVS_FACTOR            (12u)
#define BLEIOT_UART_UART_IRDA_LOW_POWER        (0u)
#define BLEIOT_UART_UART_MEDIAN_FILTER_ENABLE  (0u)
#define BLEIOT_UART_UART_RETRY_ON_NACK         (0u)
#define BLEIOT_UART_UART_IRDA_POLARITY         (0u)
#define BLEIOT_UART_UART_DROP_ON_FRAME_ERR     (0u)
#define BLEIOT_UART_UART_DROP_ON_PARITY_ERR    (0u)
#define BLEIOT_UART_UART_WAKE_ENABLE           (0u)
#define BLEIOT_UART_UART_RX_BUFFER_SIZE        (32u)
#define BLEIOT_UART_UART_TX_BUFFER_SIZE        (32u)
#define BLEIOT_UART_UART_MP_MODE_ENABLE        (0u)
#define BLEIOT_UART_UART_MP_ACCEPT_ADDRESS     (0u)
#define BLEIOT_UART_UART_MP_RX_ADDRESS         (2u)
#define BLEIOT_UART_UART_MP_RX_ADDRESS_MASK    (255u)

#define BLEIOT_UART_UART_INTERRUPT_MODE        (1u)

#define BLEIOT_UART_UART_INTR_RX_MASK          (4u)
#define BLEIOT_UART_UART_INTR_TX_MASK          (0u)

#define BLEIOT_UART_UART_RX_TRIGGER_LEVEL      (7u)
#define BLEIOT_UART_UART_TX_TRIGGER_LEVEL      (0u)

#define BLEIOT_UART_UART_BYTE_MODE_ENABLE      (0u)
#define BLEIOT_UART_UART_CTS_ENABLE            (0u)
#define BLEIOT_UART_UART_CTS_POLARITY          (0u)
#define BLEIOT_UART_UART_RTS_ENABLE            (0u)
#define BLEIOT_UART_UART_RTS_POLARITY          (0u)
#define BLEIOT_UART_UART_RTS_FIFO_LEVEL        (4u)

/* SPI mode enum */
#define BLEIOT_UART_SPI_SLAVE  (0u)
#define BLEIOT_UART_SPI_MASTER (1u)

/* UART direction enum */
#define BLEIOT_UART_UART_RX    (1u)
#define BLEIOT_UART_UART_TX    (2u)
#define BLEIOT_UART_UART_TX_RX (3u)


/***************************************
*   Conditional Compilation Parameters
****************************************/

#if(BLEIOT_UART_SCB_MODE_UNCONFIG_CONST_CFG)

    /* Mode */
    #define BLEIOT_UART_SPI_SLAVE_CONST        (1u)
    #define BLEIOT_UART_SPI_MASTER_CONST       (1u)

    /* Direction */
    #define BLEIOT_UART_RX_DIRECTION           (1u)
    #define BLEIOT_UART_TX_DIRECTION           (1u)
    #define BLEIOT_UART_UART_RX_DIRECTION      (1u)
    #define BLEIOT_UART_UART_TX_DIRECTION      (1u)

    /* Only external RX and TX buffer for Uncofigured mode */
    #define BLEIOT_UART_INTERNAL_RX_SW_BUFFER   (0u)
    #define BLEIOT_UART_INTERNAL_TX_SW_BUFFER   (0u)

    /* Get RX and TX buffer size */
    #define BLEIOT_UART_INTERNAL_RX_BUFFER_SIZE    (BLEIOT_UART_rxBufferSize + 1u)
    #define BLEIOT_UART_RX_BUFFER_SIZE             (BLEIOT_UART_rxBufferSize)
    #define BLEIOT_UART_TX_BUFFER_SIZE             (BLEIOT_UART_txBufferSize)

    /* Return true if buffer is provided */
    #define BLEIOT_UART_CHECK_RX_SW_BUFFER (NULL != BLEIOT_UART_rxBuffer)
    #define BLEIOT_UART_CHECK_TX_SW_BUFFER (NULL != BLEIOT_UART_txBuffer)

    /* Always provide global variables to support RX and TX buffers */
    #define BLEIOT_UART_INTERNAL_RX_SW_BUFFER_CONST    (1u)
    #define BLEIOT_UART_INTERNAL_TX_SW_BUFFER_CONST    (1u)

    /* Get wakeup enable option */
    #define BLEIOT_UART_SPI_WAKE_ENABLE_CONST  (1u)
    #define BLEIOT_UART_CHECK_SPI_WAKE_ENABLE  (0u != BLEIOT_UART_scbEnableWake)
    #define BLEIOT_UART_UART_WAKE_ENABLE_CONST (1u)

    /* SPI/UART: TX or RX FIFO size */
    #if (BLEIOT_UART_CY_SCBIP_V0 || BLEIOT_UART_CY_SCBIP_V1)
        #define BLEIOT_UART_SPI_UART_FIFO_SIZE             (BLEIOT_UART_FIFO_SIZE)
        #define BLEIOT_UART_CHECK_UART_RTS_CONTROL_FLOW    (0u)
    #else
        #define BLEIOT_UART_SPI_UART_FIFO_SIZE (BLEIOT_UART_GET_FIFO_SIZE(BLEIOT_UART_CTRL_REG & \
                                                                                    BLEIOT_UART_CTRL_BYTE_MODE))

        #define BLEIOT_UART_CHECK_UART_RTS_CONTROL_FLOW \
                    ((BLEIOT_UART_SCB_MODE_UART_RUNTM_CFG) && \
                     (0u != BLEIOT_UART_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(BLEIOT_UART_UART_FLOW_CTRL_REG)))
    #endif /* (BLEIOT_UART_CY_SCBIP_V0 || BLEIOT_UART_CY_SCBIP_V1) */

#else

    /* Internal RX and TX buffer: for SPI or UART */
    #if (BLEIOT_UART_SCB_MODE_SPI_CONST_CFG)

        /* SPI Direction */
        #define BLEIOT_UART_SPI_RX_DIRECTION (1u)
        #define BLEIOT_UART_SPI_TX_DIRECTION (1u)

        /* Get FIFO size */
        #if (BLEIOT_UART_CY_SCBIP_V0 || BLEIOT_UART_CY_SCBIP_V1)
            #define BLEIOT_UART_SPI_UART_FIFO_SIZE    (BLEIOT_UART_FIFO_SIZE)
        #else
            #define BLEIOT_UART_SPI_UART_FIFO_SIZE \
                                           BLEIOT_UART_GET_FIFO_SIZE(BLEIOT_UART_SPI_BYTE_MODE_ENABLE)

        #endif /* (BLEIOT_UART_CY_SCBIP_V0 || BLEIOT_UART_CY_SCBIP_V1) */

        /* SPI internal RX and TX buffers */
        #define BLEIOT_UART_INTERNAL_SPI_RX_SW_BUFFER  (BLEIOT_UART_SPI_RX_BUFFER_SIZE > \
                                                                BLEIOT_UART_SPI_UART_FIFO_SIZE)
        #define BLEIOT_UART_INTERNAL_SPI_TX_SW_BUFFER  (BLEIOT_UART_SPI_TX_BUFFER_SIZE > \
                                                                BLEIOT_UART_SPI_UART_FIFO_SIZE)

        /* Internal SPI RX and TX buffer */
        #define BLEIOT_UART_INTERNAL_RX_SW_BUFFER  (BLEIOT_UART_INTERNAL_SPI_RX_SW_BUFFER)
        #define BLEIOT_UART_INTERNAL_TX_SW_BUFFER  (BLEIOT_UART_INTERNAL_SPI_TX_SW_BUFFER)

        /* Internal SPI RX and TX buffer size */
        #define BLEIOT_UART_INTERNAL_RX_BUFFER_SIZE    (BLEIOT_UART_SPI_RX_BUFFER_SIZE + 1u)
        #define BLEIOT_UART_RX_BUFFER_SIZE             (BLEIOT_UART_SPI_RX_BUFFER_SIZE)
        #define BLEIOT_UART_TX_BUFFER_SIZE             (BLEIOT_UART_SPI_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define BLEIOT_UART_SPI_WAKE_ENABLE_CONST  (0u != BLEIOT_UART_SPI_WAKE_ENABLE)
        #define BLEIOT_UART_UART_WAKE_ENABLE_CONST (0u)

    #else

        /* UART Direction */
        #define BLEIOT_UART_UART_RX_DIRECTION (0u != (BLEIOT_UART_UART_DIRECTION & BLEIOT_UART_UART_RX))
        #define BLEIOT_UART_UART_TX_DIRECTION (0u != (BLEIOT_UART_UART_DIRECTION & BLEIOT_UART_UART_TX))

        /* Get FIFO size */
        #if (BLEIOT_UART_CY_SCBIP_V0 || BLEIOT_UART_CY_SCBIP_V1)
            #define BLEIOT_UART_SPI_UART_FIFO_SIZE    (BLEIOT_UART_FIFO_SIZE)
        #else
            #define BLEIOT_UART_SPI_UART_FIFO_SIZE \
                                           BLEIOT_UART_GET_FIFO_SIZE(BLEIOT_UART_UART_BYTE_MODE_ENABLE)
        #endif /* (BLEIOT_UART_CY_SCBIP_V0 || BLEIOT_UART_CY_SCBIP_V1) */

        /* UART internal RX and TX buffers */
        #define BLEIOT_UART_INTERNAL_UART_RX_SW_BUFFER  (BLEIOT_UART_UART_RX_BUFFER_SIZE > \
                                                                BLEIOT_UART_SPI_UART_FIFO_SIZE)
        #define BLEIOT_UART_INTERNAL_UART_TX_SW_BUFFER  (BLEIOT_UART_UART_TX_BUFFER_SIZE > \
                                                                    BLEIOT_UART_SPI_UART_FIFO_SIZE)

        /* Internal UART RX and TX buffer */
        #define BLEIOT_UART_INTERNAL_RX_SW_BUFFER  (BLEIOT_UART_INTERNAL_UART_RX_SW_BUFFER)
        #define BLEIOT_UART_INTERNAL_TX_SW_BUFFER  (BLEIOT_UART_INTERNAL_UART_TX_SW_BUFFER)

        /* Internal UART RX and TX buffer size */
        #define BLEIOT_UART_INTERNAL_RX_BUFFER_SIZE    (BLEIOT_UART_UART_RX_BUFFER_SIZE + 1u)
        #define BLEIOT_UART_RX_BUFFER_SIZE             (BLEIOT_UART_UART_RX_BUFFER_SIZE)
        #define BLEIOT_UART_TX_BUFFER_SIZE             (BLEIOT_UART_UART_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define BLEIOT_UART_SPI_WAKE_ENABLE_CONST  (0u)
        #define BLEIOT_UART_UART_WAKE_ENABLE_CONST (0u != BLEIOT_UART_UART_WAKE_ENABLE)

    #endif /* (BLEIOT_UART_SCB_MODE_SPI_CONST_CFG) */

    /* Mode */
    #define BLEIOT_UART_SPI_SLAVE_CONST    (BLEIOT_UART_SPI_MODE == BLEIOT_UART_SPI_SLAVE)
    #define BLEIOT_UART_SPI_MASTER_CONST   (BLEIOT_UART_SPI_MODE == BLEIOT_UART_SPI_MASTER)

    /* Direction */
    #define BLEIOT_UART_RX_DIRECTION ((BLEIOT_UART_SCB_MODE_SPI_CONST_CFG) ? \
                                            (BLEIOT_UART_SPI_RX_DIRECTION) : (BLEIOT_UART_UART_RX_DIRECTION))

    #define BLEIOT_UART_TX_DIRECTION ((BLEIOT_UART_SCB_MODE_SPI_CONST_CFG) ? \
                                            (BLEIOT_UART_SPI_TX_DIRECTION) : (BLEIOT_UART_UART_TX_DIRECTION))

    /* Internal RX and TX buffer: for SPI or UART. Used in conditional compilation check */
    #define BLEIOT_UART_CHECK_RX_SW_BUFFER (BLEIOT_UART_INTERNAL_RX_SW_BUFFER)
    #define BLEIOT_UART_CHECK_TX_SW_BUFFER (BLEIOT_UART_INTERNAL_TX_SW_BUFFER)

    /* Provide global variables to support RX and TX buffers */
    #define BLEIOT_UART_INTERNAL_RX_SW_BUFFER_CONST    (BLEIOT_UART_INTERNAL_RX_SW_BUFFER)
    #define BLEIOT_UART_INTERNAL_TX_SW_BUFFER_CONST    (BLEIOT_UART_INTERNAL_TX_SW_BUFFER)

    /* SPI wakeup */
    #define BLEIOT_UART_CHECK_SPI_WAKE_ENABLE  (BLEIOT_UART_SPI_WAKE_ENABLE_CONST)

    /* UART flow control: not applicable for CY_SCBIP_V0 || CY_SCBIP_V1 */
    #define BLEIOT_UART_CHECK_UART_RTS_CONTROL_FLOW    (BLEIOT_UART_SCB_MODE_UART_CONST_CFG && \
                                                             BLEIOT_UART_UART_RTS_ENABLE)

#endif /* End (BLEIOT_UART_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*       Type Definitions
***************************************/

/* BLEIOT_UART_SPI_INIT_STRUCT */
typedef struct
{
    uint32 mode;
    uint32 submode;
    uint32 sclkMode;
    uint32 oversample;
    uint32 enableMedianFilter;
    uint32 enableLateSampling;
    uint32 enableWake;
    uint32 rxDataBits;
    uint32 txDataBits;
    uint32 bitOrder;
    uint32 transferSeperation;
    uint32 rxBufferSize;
    uint8* rxBuffer;
    uint32 txBufferSize;
    uint8* txBuffer;
    uint32 enableInterrupt;
    uint32 rxInterruptMask;
    uint32 rxTriggerLevel;
    uint32 txInterruptMask;
    uint32 txTriggerLevel;
    uint8 enableByteMode;
    uint8 enableFreeRunSclk;
    uint8 polaritySs;
} BLEIOT_UART_SPI_INIT_STRUCT;

/* BLEIOT_UART_UART_INIT_STRUCT */
typedef struct
{
    uint32 mode;
    uint32 direction;
    uint32 dataBits;
    uint32 parity;
    uint32 stopBits;
    uint32 oversample;
    uint32 enableIrdaLowPower;
    uint32 enableMedianFilter;
    uint32 enableRetryNack;
    uint32 enableInvertedRx;
    uint32 dropOnParityErr;
    uint32 dropOnFrameErr;
    uint32 enableWake;
    uint32 rxBufferSize;
    uint8* rxBuffer;
    uint32 txBufferSize;
    uint8* txBuffer;
    uint32 enableMultiproc;
    uint32 multiprocAcceptAddr;
    uint32 multiprocAddr;
    uint32 multiprocAddrMask;
    uint32 enableInterrupt;
    uint32 rxInterruptMask;
    uint32 rxTriggerLevel;
    uint32 txInterruptMask;
    uint32 txTriggerLevel;
    uint8 enableByteMode;
    uint8 enableCts;
    uint8 ctsPolarity;
    uint8 rtsRxFifoLevel;
    uint8 rtsPolarity;
} BLEIOT_UART_UART_INIT_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

/* SPI specific functions */
#if(BLEIOT_UART_SCB_MODE_UNCONFIG_CONST_CFG)
    void BLEIOT_UART_SpiInit(const BLEIOT_UART_SPI_INIT_STRUCT *config);
#endif /* (BLEIOT_UART_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(BLEIOT_UART_SCB_MODE_SPI_INC)
    #define BLEIOT_UART_SpiIsBusBusy() ((uint32) (0u != (BLEIOT_UART_SPI_STATUS_REG & \
                                                              BLEIOT_UART_SPI_STATUS_BUS_BUSY)))

    #if (BLEIOT_UART_SPI_MASTER_CONST)
        void BLEIOT_UART_SpiSetActiveSlaveSelect(uint32 slaveSelect);
    #endif /*(BLEIOT_UART_SPI_MASTER_CONST) */

    #if !(BLEIOT_UART_CY_SCBIP_V0 || BLEIOT_UART_CY_SCBIP_V1)
        void BLEIOT_UART_SpiSetSlaveSelectPolarity(uint32 slaveSelect, uint32 polarity);
    #endif /* !(BLEIOT_UART_CY_SCBIP_V0 || BLEIOT_UART_CY_SCBIP_V1) */
#endif /* (BLEIOT_UART_SCB_MODE_SPI_INC) */

/* UART specific functions */
#if(BLEIOT_UART_SCB_MODE_UNCONFIG_CONST_CFG)
    void BLEIOT_UART_UartInit(const BLEIOT_UART_UART_INIT_STRUCT *config);
#endif /* (BLEIOT_UART_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(BLEIOT_UART_SCB_MODE_UART_INC)
    void BLEIOT_UART_UartSetRxAddress(uint32 address);
    void BLEIOT_UART_UartSetRxAddressMask(uint32 addressMask);

    /* UART RX direction APIs */
    #if(BLEIOT_UART_UART_RX_DIRECTION)
        uint32 BLEIOT_UART_UartGetChar(void);
        uint32 BLEIOT_UART_UartGetByte(void);

        #if !(BLEIOT_UART_CY_SCBIP_V0 || BLEIOT_UART_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void BLEIOT_UART_UartSetRtsPolarity(uint32 polarity);
            void BLEIOT_UART_UartSetRtsFifoLevel(uint32 level);
        #endif /* !(BLEIOT_UART_CY_SCBIP_V0 || BLEIOT_UART_CY_SCBIP_V1) */
    #endif /* (BLEIOT_UART_UART_RX_DIRECTION) */

    /* UART TX direction APIs */
    #if(BLEIOT_UART_UART_TX_DIRECTION)
        #define BLEIOT_UART_UartPutChar(ch)    BLEIOT_UART_SpiUartWriteTxData((uint32)(ch))
        void BLEIOT_UART_UartPutString(const char8 string[]);
        void BLEIOT_UART_UartPutCRLF(uint32 txDataByte);

        #if !(BLEIOT_UART_CY_SCBIP_V0 || BLEIOT_UART_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void BLEIOT_UART_UartEnableCts(void);
            void BLEIOT_UART_UartDisableCts(void);
            void BLEIOT_UART_UartSetCtsPolarity(uint32 polarity);
        #endif /* !(BLEIOT_UART_CY_SCBIP_V0 || BLEIOT_UART_CY_SCBIP_V1) */
    #endif /* (BLEIOT_UART_UART_TX_DIRECTION) */
#endif /* (BLEIOT_UART_SCB_MODE_UART_INC) */

/* Common APIs RX direction */
#if(BLEIOT_UART_RX_DIRECTION)
    uint32 BLEIOT_UART_SpiUartReadRxData(void);
    uint32 BLEIOT_UART_SpiUartGetRxBufferSize(void);
    void   BLEIOT_UART_SpiUartClearRxBuffer(void);
#endif /* (BLEIOT_UART_RX_DIRECTION) */

/* Common APIs TX direction */
#if(BLEIOT_UART_TX_DIRECTION)
    void   BLEIOT_UART_SpiUartWriteTxData(uint32 txData);
    void   BLEIOT_UART_SpiUartPutArray(const uint8 wrBuf[], uint32 count);
    uint32 BLEIOT_UART_SpiUartGetTxBufferSize(void);
    void   BLEIOT_UART_SpiUartClearTxBuffer(void);
#endif /* (BLEIOT_UART_TX_DIRECTION) */

CY_ISR_PROTO(BLEIOT_UART_SPI_UART_ISR);

#if(BLEIOT_UART_UART_RX_WAKEUP_IRQ)
    CY_ISR_PROTO(BLEIOT_UART_UART_WAKEUP_ISR);
#endif /* (BLEIOT_UART_UART_RX_WAKEUP_IRQ) */


/***************************************
*     Buffer Access Macro Definitions
***************************************/

#if(BLEIOT_UART_SCB_MODE_UNCONFIG_CONST_CFG)
    /* RX direction */
    void   BLEIOT_UART_PutWordInRxBuffer  (uint32 idx, uint32 rxDataByte);
    uint32 BLEIOT_UART_GetWordFromRxBuffer(uint32 idx);

    /* TX direction */
    void   BLEIOT_UART_PutWordInTxBuffer  (uint32 idx, uint32 txDataByte);
    uint32 BLEIOT_UART_GetWordFromTxBuffer(uint32 idx);

#else
    /* RX direction */
    #if(BLEIOT_UART_INTERNAL_RX_SW_BUFFER_CONST)
        #define BLEIOT_UART_PutWordInRxBuffer(idx, rxDataByte) \
                do{                                                 \
                    BLEIOT_UART_rxBufferInternal[(idx)] = ((uint8) (rxDataByte)); \
                }while(0)

        #define BLEIOT_UART_GetWordFromRxBuffer(idx) BLEIOT_UART_rxBufferInternal[(idx)]

    #endif /* (BLEIOT_UART_INTERNAL_RX_SW_BUFFER_CONST) */

    /* TX direction */
    #if(BLEIOT_UART_INTERNAL_TX_SW_BUFFER_CONST)
        #define BLEIOT_UART_PutWordInTxBuffer(idx, txDataByte) \
                    do{                                             \
                        BLEIOT_UART_txBufferInternal[(idx)] = ((uint8) (txDataByte)); \
                    }while(0)

        #define BLEIOT_UART_GetWordFromTxBuffer(idx) BLEIOT_UART_txBufferInternal[(idx)]

    #endif /* (BLEIOT_UART_INTERNAL_TX_SW_BUFFER_CONST) */

#endif /* (BLEIOT_UART_TX_SW_BUFFER_ENABLE) */


/***************************************
*         SPI API Constants
***************************************/

/* SPI sub mode enum */
#define BLEIOT_UART_SPI_MODE_MOTOROLA      (0x00u)
#define BLEIOT_UART_SPI_MODE_TI_COINCIDES  (0x01u)
#define BLEIOT_UART_SPI_MODE_TI_PRECEDES   (0x11u)
#define BLEIOT_UART_SPI_MODE_NATIONAL      (0x02u)
#define BLEIOT_UART_SPI_MODE_MASK          (0x03u)
#define BLEIOT_UART_SPI_MODE_TI_PRECEDES_MASK  (0x10u)
#define BLEIOT_UART_SPI_MODE_NS_MICROWIRE  (BLEIOT_UART_SPI_MODE_NATIONAL)

/* SPI phase and polarity mode enum */
#define BLEIOT_UART_SPI_SCLK_CPHA0_CPOL0   (0x00u)
#define BLEIOT_UART_SPI_SCLK_CPHA0_CPOL1   (0x02u)
#define BLEIOT_UART_SPI_SCLK_CPHA1_CPOL0   (0x01u)
#define BLEIOT_UART_SPI_SCLK_CPHA1_CPOL1   (0x03u)

/* SPI bits order enum */
#define BLEIOT_UART_BITS_ORDER_LSB_FIRST   (0u)
#define BLEIOT_UART_BITS_ORDER_MSB_FIRST   (1u)

/* SPI transfer separation enum */
#define BLEIOT_UART_SPI_TRANSFER_SEPARATED     (0u)
#define BLEIOT_UART_SPI_TRANSFER_CONTINUOUS    (1u)

/* SPI slave select constants */
#define BLEIOT_UART_SPI_SLAVE_SELECT0    (BLEIOT_UART_SCB__SS0_POSISTION)
#define BLEIOT_UART_SPI_SLAVE_SELECT1    (BLEIOT_UART_SCB__SS1_POSISTION)
#define BLEIOT_UART_SPI_SLAVE_SELECT2    (BLEIOT_UART_SCB__SS2_POSISTION)
#define BLEIOT_UART_SPI_SLAVE_SELECT3    (BLEIOT_UART_SCB__SS3_POSISTION)

/* SPI slave select polarity settings */
#define BLEIOT_UART_SPI_SS_ACTIVE_LOW  (0u)
#define BLEIOT_UART_SPI_SS_ACTIVE_HIGH (1u)


/***************************************
*         UART API Constants
***************************************/

/* UART sub-modes enum */
#define BLEIOT_UART_UART_MODE_STD          (0u)
#define BLEIOT_UART_UART_MODE_SMARTCARD    (1u)
#define BLEIOT_UART_UART_MODE_IRDA         (2u)

/* UART direction enum */
#define BLEIOT_UART_UART_RX    (1u)
#define BLEIOT_UART_UART_TX    (2u)
#define BLEIOT_UART_UART_TX_RX (3u)

/* UART parity enum */
#define BLEIOT_UART_UART_PARITY_EVEN   (0u)
#define BLEIOT_UART_UART_PARITY_ODD    (1u)
#define BLEIOT_UART_UART_PARITY_NONE   (2u)

/* UART stop bits enum */
#define BLEIOT_UART_UART_STOP_BITS_1   (2u)
#define BLEIOT_UART_UART_STOP_BITS_1_5 (3u)
#define BLEIOT_UART_UART_STOP_BITS_2   (4u)

/* UART IrDA low power OVS enum */
#define BLEIOT_UART_UART_IRDA_LP_OVS16     (16u)
#define BLEIOT_UART_UART_IRDA_LP_OVS32     (32u)
#define BLEIOT_UART_UART_IRDA_LP_OVS48     (48u)
#define BLEIOT_UART_UART_IRDA_LP_OVS96     (96u)
#define BLEIOT_UART_UART_IRDA_LP_OVS192    (192u)
#define BLEIOT_UART_UART_IRDA_LP_OVS768    (768u)
#define BLEIOT_UART_UART_IRDA_LP_OVS1536   (1536u)

/* Uart MP: mark (address) and space (data) bit definitions */
#define BLEIOT_UART_UART_MP_MARK       (0x100u)
#define BLEIOT_UART_UART_MP_SPACE      (0x000u)

/* UART CTS/RTS polarity settings */
#define BLEIOT_UART_UART_CTS_ACTIVE_LOW    (0u)
#define BLEIOT_UART_UART_CTS_ACTIVE_HIGH   (1u)
#define BLEIOT_UART_UART_RTS_ACTIVE_LOW    (0u)
#define BLEIOT_UART_UART_RTS_ACTIVE_HIGH   (1u)

/* Sources of RX errors */
#define BLEIOT_UART_INTR_RX_ERR        (BLEIOT_UART_INTR_RX_OVERFLOW    | \
                                             BLEIOT_UART_INTR_RX_UNDERFLOW   | \
                                             BLEIOT_UART_INTR_RX_FRAME_ERROR | \
                                             BLEIOT_UART_INTR_RX_PARITY_ERROR)

/* Shifted INTR_RX_ERR defines ONLY for BLEIOT_UART_UartGetByte() */
#define BLEIOT_UART_UART_RX_OVERFLOW       (BLEIOT_UART_INTR_RX_OVERFLOW << 8u)
#define BLEIOT_UART_UART_RX_UNDERFLOW      (BLEIOT_UART_INTR_RX_UNDERFLOW << 8u)
#define BLEIOT_UART_UART_RX_FRAME_ERROR    (BLEIOT_UART_INTR_RX_FRAME_ERROR << 8u)
#define BLEIOT_UART_UART_RX_PARITY_ERROR   (BLEIOT_UART_INTR_RX_PARITY_ERROR << 8u)
#define BLEIOT_UART_UART_RX_ERROR_MASK     (BLEIOT_UART_UART_RX_OVERFLOW    | \
                                                 BLEIOT_UART_UART_RX_UNDERFLOW   | \
                                                 BLEIOT_UART_UART_RX_FRAME_ERROR | \
                                                 BLEIOT_UART_UART_RX_PARITY_ERROR)


/***************************************
*     Vars with External Linkage
***************************************/

#if(BLEIOT_UART_SCB_MODE_UNCONFIG_CONST_CFG)
    extern const BLEIOT_UART_SPI_INIT_STRUCT  BLEIOT_UART_configSpi;
    extern const BLEIOT_UART_UART_INIT_STRUCT BLEIOT_UART_configUart;
#endif /* (BLEIOT_UART_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*    Specific SPI Macro Definitions
***************************************/

#define BLEIOT_UART_GET_SPI_INTR_SLAVE_MASK(sourceMask)  ((sourceMask) & BLEIOT_UART_INTR_SLAVE_SPI_BUS_ERROR)
#define BLEIOT_UART_GET_SPI_INTR_MASTER_MASK(sourceMask) ((sourceMask) & BLEIOT_UART_INTR_MASTER_SPI_DONE)
#define BLEIOT_UART_GET_SPI_INTR_RX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~BLEIOT_UART_INTR_SLAVE_SPI_BUS_ERROR)

#define BLEIOT_UART_GET_SPI_INTR_TX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~BLEIOT_UART_INTR_MASTER_SPI_DONE)


/***************************************
*    Specific UART Macro Definitions
***************************************/

#define BLEIOT_UART_UART_GET_CTRL_OVS_IRDA_LP(oversample) \
        ((BLEIOT_UART_UART_IRDA_LP_OVS16   == (oversample)) ? BLEIOT_UART_CTRL_OVS_IRDA_LP_OVS16 : \
         ((BLEIOT_UART_UART_IRDA_LP_OVS32   == (oversample)) ? BLEIOT_UART_CTRL_OVS_IRDA_LP_OVS32 : \
          ((BLEIOT_UART_UART_IRDA_LP_OVS48   == (oversample)) ? BLEIOT_UART_CTRL_OVS_IRDA_LP_OVS48 : \
           ((BLEIOT_UART_UART_IRDA_LP_OVS96   == (oversample)) ? BLEIOT_UART_CTRL_OVS_IRDA_LP_OVS96 : \
            ((BLEIOT_UART_UART_IRDA_LP_OVS192  == (oversample)) ? BLEIOT_UART_CTRL_OVS_IRDA_LP_OVS192 : \
             ((BLEIOT_UART_UART_IRDA_LP_OVS768  == (oversample)) ? BLEIOT_UART_CTRL_OVS_IRDA_LP_OVS768 : \
              ((BLEIOT_UART_UART_IRDA_LP_OVS1536 == (oversample)) ? BLEIOT_UART_CTRL_OVS_IRDA_LP_OVS1536 : \
                                                                          BLEIOT_UART_CTRL_OVS_IRDA_LP_OVS16)))))))

#define BLEIOT_UART_GET_UART_RX_CTRL_ENABLED(direction) ((0u != (BLEIOT_UART_UART_RX & (direction))) ? \
                                                                     (BLEIOT_UART_RX_CTRL_ENABLED) : (0u))

#define BLEIOT_UART_GET_UART_TX_CTRL_ENABLED(direction) ((0u != (BLEIOT_UART_UART_TX & (direction))) ? \
                                                                     (BLEIOT_UART_TX_CTRL_ENABLED) : (0u))


/***************************************
*        SPI Register Settings
***************************************/

#define BLEIOT_UART_CTRL_SPI      (BLEIOT_UART_CTRL_MODE_SPI)
#define BLEIOT_UART_SPI_RX_CTRL   (BLEIOT_UART_RX_CTRL_ENABLED)
#define BLEIOT_UART_SPI_TX_CTRL   (BLEIOT_UART_TX_CTRL_ENABLED)


/***************************************
*       SPI Init Register Settings
***************************************/

#define BLEIOT_UART_SPI_SS_POLARITY \
             (((uint32) BLEIOT_UART_SPI_SS0_POLARITY << BLEIOT_UART_SPI_SLAVE_SELECT0) | \
              ((uint32) BLEIOT_UART_SPI_SS1_POLARITY << BLEIOT_UART_SPI_SLAVE_SELECT1) | \
              ((uint32) BLEIOT_UART_SPI_SS2_POLARITY << BLEIOT_UART_SPI_SLAVE_SELECT2) | \
              ((uint32) BLEIOT_UART_SPI_SS3_POLARITY << BLEIOT_UART_SPI_SLAVE_SELECT3))

#if(BLEIOT_UART_SCB_MODE_SPI_CONST_CFG)

    /* SPI Configuration */
    #define BLEIOT_UART_SPI_DEFAULT_CTRL \
                    (BLEIOT_UART_GET_CTRL_OVS(BLEIOT_UART_SPI_OVS_FACTOR) | \
                     BLEIOT_UART_GET_CTRL_BYTE_MODE (BLEIOT_UART_SPI_BYTE_MODE_ENABLE) | \
                     BLEIOT_UART_GET_CTRL_EC_AM_MODE(BLEIOT_UART_SPI_WAKE_ENABLE)      | \
                     BLEIOT_UART_CTRL_SPI)

    #define BLEIOT_UART_SPI_DEFAULT_SPI_CTRL \
                    (BLEIOT_UART_GET_SPI_CTRL_CONTINUOUS    (BLEIOT_UART_SPI_TRANSFER_SEPARATION)       | \
                     BLEIOT_UART_GET_SPI_CTRL_SELECT_PRECEDE(BLEIOT_UART_SPI_SUB_MODE &                   \
                                                                  BLEIOT_UART_SPI_MODE_TI_PRECEDES_MASK)     | \
                     BLEIOT_UART_GET_SPI_CTRL_SCLK_MODE     (BLEIOT_UART_SPI_CLOCK_MODE)                | \
                     BLEIOT_UART_GET_SPI_CTRL_LATE_MISO_SAMPLE(BLEIOT_UART_SPI_LATE_MISO_SAMPLE_ENABLE) | \
                     BLEIOT_UART_GET_SPI_CTRL_SCLK_CONTINUOUS(BLEIOT_UART_SPI_FREE_RUN_SCLK_ENABLE)     | \
                     BLEIOT_UART_GET_SPI_CTRL_SSEL_POLARITY (BLEIOT_UART_SPI_SS_POLARITY)               | \
                     BLEIOT_UART_GET_SPI_CTRL_SUB_MODE      (BLEIOT_UART_SPI_SUB_MODE)                  | \
                     BLEIOT_UART_GET_SPI_CTRL_MASTER_MODE   (BLEIOT_UART_SPI_MODE))

    /* RX direction */
    #define BLEIOT_UART_SPI_DEFAULT_RX_CTRL \
                    (BLEIOT_UART_GET_RX_CTRL_DATA_WIDTH(BLEIOT_UART_SPI_RX_DATA_BITS_NUM)     | \
                     BLEIOT_UART_GET_RX_CTRL_BIT_ORDER (BLEIOT_UART_SPI_BITS_ORDER)           | \
                     BLEIOT_UART_GET_RX_CTRL_MEDIAN    (BLEIOT_UART_SPI_MEDIAN_FILTER_ENABLE) | \
                     BLEIOT_UART_SPI_RX_CTRL)

    #define BLEIOT_UART_SPI_DEFAULT_RX_FIFO_CTRL \
                    BLEIOT_UART_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(BLEIOT_UART_SPI_RX_TRIGGER_LEVEL)

    /* TX direction */
    #define BLEIOT_UART_SPI_DEFAULT_TX_CTRL \
                    (BLEIOT_UART_GET_TX_CTRL_DATA_WIDTH(BLEIOT_UART_SPI_TX_DATA_BITS_NUM) | \
                     BLEIOT_UART_GET_TX_CTRL_BIT_ORDER (BLEIOT_UART_SPI_BITS_ORDER)       | \
                     BLEIOT_UART_SPI_TX_CTRL)

    #define BLEIOT_UART_SPI_DEFAULT_TX_FIFO_CTRL \
                    BLEIOT_UART_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(BLEIOT_UART_SPI_TX_TRIGGER_LEVEL)

    /* Interrupt sources */
    #define BLEIOT_UART_SPI_DEFAULT_INTR_SPI_EC_MASK   (BLEIOT_UART_NO_INTR_SOURCES)

    #define BLEIOT_UART_SPI_DEFAULT_INTR_I2C_EC_MASK   (BLEIOT_UART_NO_INTR_SOURCES)
    #define BLEIOT_UART_SPI_DEFAULT_INTR_SLAVE_MASK \
                    (BLEIOT_UART_SPI_INTR_RX_MASK & BLEIOT_UART_INTR_SLAVE_SPI_BUS_ERROR)

    #define BLEIOT_UART_SPI_DEFAULT_INTR_MASTER_MASK \
                    (BLEIOT_UART_SPI_INTR_TX_MASK & BLEIOT_UART_INTR_MASTER_SPI_DONE)

    #define BLEIOT_UART_SPI_DEFAULT_INTR_RX_MASK \
                    (BLEIOT_UART_SPI_INTR_RX_MASK & (uint32) ~BLEIOT_UART_INTR_SLAVE_SPI_BUS_ERROR)

    #define BLEIOT_UART_SPI_DEFAULT_INTR_TX_MASK \
                    (BLEIOT_UART_SPI_INTR_TX_MASK & (uint32) ~BLEIOT_UART_INTR_MASTER_SPI_DONE)

#endif /* (BLEIOT_UART_SCB_MODE_SPI_CONST_CFG) */


/***************************************
*        UART Register Settings
***************************************/

#define BLEIOT_UART_CTRL_UART      (BLEIOT_UART_CTRL_MODE_UART)
#define BLEIOT_UART_UART_RX_CTRL   (BLEIOT_UART_RX_CTRL_LSB_FIRST) /* LSB for UART goes first */
#define BLEIOT_UART_UART_TX_CTRL   (BLEIOT_UART_TX_CTRL_LSB_FIRST) /* LSB for UART goes first */


/***************************************
*      UART Init Register Settings
***************************************/

#if(BLEIOT_UART_SCB_MODE_UART_CONST_CFG)

    /* UART configuration */
    #if(BLEIOT_UART_UART_MODE_IRDA == BLEIOT_UART_UART_SUB_MODE)

        #define BLEIOT_UART_DEFAULT_CTRL_OVS   ((0u != BLEIOT_UART_UART_IRDA_LOW_POWER) ?              \
                                (BLEIOT_UART_UART_GET_CTRL_OVS_IRDA_LP(BLEIOT_UART_UART_OVS_FACTOR)) : \
                                (BLEIOT_UART_CTRL_OVS_IRDA_OVS16))

    #else

        #define BLEIOT_UART_DEFAULT_CTRL_OVS   BLEIOT_UART_GET_CTRL_OVS(BLEIOT_UART_UART_OVS_FACTOR)

    #endif /* (BLEIOT_UART_UART_MODE_IRDA == BLEIOT_UART_UART_SUB_MODE) */

    #define BLEIOT_UART_UART_DEFAULT_CTRL \
                                (BLEIOT_UART_GET_CTRL_BYTE_MODE  (BLEIOT_UART_UART_BYTE_MODE_ENABLE)  | \
                                 BLEIOT_UART_GET_CTRL_ADDR_ACCEPT(BLEIOT_UART_UART_MP_ACCEPT_ADDRESS) | \
                                 BLEIOT_UART_DEFAULT_CTRL_OVS                                              | \
                                 BLEIOT_UART_CTRL_UART)

    #define BLEIOT_UART_UART_DEFAULT_UART_CTRL \
                                    (BLEIOT_UART_GET_UART_CTRL_MODE(BLEIOT_UART_UART_SUB_MODE))

    /* RX direction */
    #define BLEIOT_UART_UART_DEFAULT_RX_CTRL_PARITY \
                                ((BLEIOT_UART_UART_PARITY_NONE != BLEIOT_UART_UART_PARITY_TYPE) ?      \
                                  (BLEIOT_UART_GET_UART_RX_CTRL_PARITY(BLEIOT_UART_UART_PARITY_TYPE) | \
                                   BLEIOT_UART_UART_RX_CTRL_PARITY_ENABLED) : (0u))

    #define BLEIOT_UART_UART_DEFAULT_UART_RX_CTRL \
                    (BLEIOT_UART_GET_UART_RX_CTRL_MODE(BLEIOT_UART_UART_STOP_BITS_NUM)                    | \
                     BLEIOT_UART_GET_UART_RX_CTRL_POLARITY(BLEIOT_UART_UART_IRDA_POLARITY)                | \
                     BLEIOT_UART_GET_UART_RX_CTRL_MP_MODE(BLEIOT_UART_UART_MP_MODE_ENABLE)                | \
                     BLEIOT_UART_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(BLEIOT_UART_UART_DROP_ON_PARITY_ERR) | \
                     BLEIOT_UART_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(BLEIOT_UART_UART_DROP_ON_FRAME_ERR)   | \
                     BLEIOT_UART_UART_DEFAULT_RX_CTRL_PARITY)

    #define BLEIOT_UART_UART_DEFAULT_RX_CTRL \
                                (BLEIOT_UART_GET_RX_CTRL_DATA_WIDTH(BLEIOT_UART_UART_DATA_BITS_NUM)        | \
                                 BLEIOT_UART_GET_RX_CTRL_MEDIAN    (BLEIOT_UART_UART_MEDIAN_FILTER_ENABLE) | \
                                 BLEIOT_UART_GET_UART_RX_CTRL_ENABLED(BLEIOT_UART_UART_DIRECTION))

    #define BLEIOT_UART_UART_DEFAULT_RX_FIFO_CTRL \
                                BLEIOT_UART_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(BLEIOT_UART_UART_RX_TRIGGER_LEVEL)

    #define BLEIOT_UART_UART_DEFAULT_RX_MATCH_REG  ((0u != BLEIOT_UART_UART_MP_MODE_ENABLE) ?          \
                                (BLEIOT_UART_GET_RX_MATCH_ADDR(BLEIOT_UART_UART_MP_RX_ADDRESS) | \
                                 BLEIOT_UART_GET_RX_MATCH_MASK(BLEIOT_UART_UART_MP_RX_ADDRESS_MASK)) : (0u))

    /* TX direction */
    #define BLEIOT_UART_UART_DEFAULT_TX_CTRL_PARITY (BLEIOT_UART_UART_DEFAULT_RX_CTRL_PARITY)

    #define BLEIOT_UART_UART_DEFAULT_UART_TX_CTRL \
                                (BLEIOT_UART_GET_UART_TX_CTRL_MODE(BLEIOT_UART_UART_STOP_BITS_NUM)       | \
                                 BLEIOT_UART_GET_UART_TX_CTRL_RETRY_NACK(BLEIOT_UART_UART_RETRY_ON_NACK) | \
                                 BLEIOT_UART_UART_DEFAULT_TX_CTRL_PARITY)

    #define BLEIOT_UART_UART_DEFAULT_TX_CTRL \
                                (BLEIOT_UART_GET_TX_CTRL_DATA_WIDTH(BLEIOT_UART_UART_DATA_BITS_NUM) | \
                                 BLEIOT_UART_GET_UART_TX_CTRL_ENABLED(BLEIOT_UART_UART_DIRECTION))

    #define BLEIOT_UART_UART_DEFAULT_TX_FIFO_CTRL \
                                BLEIOT_UART_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(BLEIOT_UART_UART_TX_TRIGGER_LEVEL)

    #define BLEIOT_UART_UART_DEFAULT_FLOW_CTRL \
                        (BLEIOT_UART_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(BLEIOT_UART_UART_RTS_FIFO_LEVEL) | \
                         BLEIOT_UART_GET_UART_FLOW_CTRL_RTS_POLARITY (BLEIOT_UART_UART_RTS_POLARITY)   | \
                         BLEIOT_UART_GET_UART_FLOW_CTRL_CTS_POLARITY (BLEIOT_UART_UART_CTS_POLARITY)   | \
                         BLEIOT_UART_GET_UART_FLOW_CTRL_CTS_ENABLE   (BLEIOT_UART_UART_CTS_ENABLE))

    /* Interrupt sources */
    #define BLEIOT_UART_UART_DEFAULT_INTR_I2C_EC_MASK  (BLEIOT_UART_NO_INTR_SOURCES)
    #define BLEIOT_UART_UART_DEFAULT_INTR_SPI_EC_MASK  (BLEIOT_UART_NO_INTR_SOURCES)
    #define BLEIOT_UART_UART_DEFAULT_INTR_SLAVE_MASK   (BLEIOT_UART_NO_INTR_SOURCES)
    #define BLEIOT_UART_UART_DEFAULT_INTR_MASTER_MASK  (BLEIOT_UART_NO_INTR_SOURCES)
    #define BLEIOT_UART_UART_DEFAULT_INTR_RX_MASK      (BLEIOT_UART_UART_INTR_RX_MASK)
    #define BLEIOT_UART_UART_DEFAULT_INTR_TX_MASK      (BLEIOT_UART_UART_INTR_TX_MASK)

#endif /* (BLEIOT_UART_SCB_MODE_UART_CONST_CFG) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

#define BLEIOT_UART_SPIM_ACTIVE_SS0    (BLEIOT_UART_SPI_SLAVE_SELECT0)
#define BLEIOT_UART_SPIM_ACTIVE_SS1    (BLEIOT_UART_SPI_SLAVE_SELECT1)
#define BLEIOT_UART_SPIM_ACTIVE_SS2    (BLEIOT_UART_SPI_SLAVE_SELECT2)
#define BLEIOT_UART_SPIM_ACTIVE_SS3    (BLEIOT_UART_SPI_SLAVE_SELECT3)

#endif /* CY_SCB_SPI_UART_BLEIOT_UART_H */


/* [] END OF FILE */
