/*******************************************************************************
* File Name: BLEIOT_UART_PINS.h
* Version 3.10
*
* Description:
*  This file provides constants and parameter values for the pin components
*  buried into SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PINS_BLEIOT_UART_H)
#define CY_SCB_PINS_BLEIOT_UART_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define BLEIOT_UART_REMOVE_RX_WAKE_SDA_MOSI_PIN  (1u)
#define BLEIOT_UART_REMOVE_RX_SDA_MOSI_PIN      (1u)
#define BLEIOT_UART_REMOVE_TX_SCL_MISO_PIN      (1u)
#define BLEIOT_UART_REMOVE_CTS_SCLK_PIN      (1u)
#define BLEIOT_UART_REMOVE_RTS_SS0_PIN      (1u)
#define BLEIOT_UART_REMOVE_SS1_PIN                 (1u)
#define BLEIOT_UART_REMOVE_SS2_PIN                 (1u)
#define BLEIOT_UART_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define BLEIOT_UART_REMOVE_I2C_PINS                (1u)
#define BLEIOT_UART_REMOVE_SPI_MASTER_PINS         (1u)
#define BLEIOT_UART_REMOVE_SPI_MASTER_SCLK_PIN     (1u)
#define BLEIOT_UART_REMOVE_SPI_MASTER_MOSI_PIN     (1u)
#define BLEIOT_UART_REMOVE_SPI_MASTER_MISO_PIN     (1u)
#define BLEIOT_UART_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define BLEIOT_UART_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define BLEIOT_UART_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define BLEIOT_UART_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define BLEIOT_UART_REMOVE_SPI_SLAVE_PINS          (1u)
#define BLEIOT_UART_REMOVE_SPI_SLAVE_MOSI_PIN      (1u)
#define BLEIOT_UART_REMOVE_SPI_SLAVE_MISO_PIN      (1u)
#define BLEIOT_UART_REMOVE_UART_TX_PIN             (0u)
#define BLEIOT_UART_REMOVE_UART_RX_TX_PIN          (1u)
#define BLEIOT_UART_REMOVE_UART_RX_PIN             (0u)
#define BLEIOT_UART_REMOVE_UART_RX_WAKE_PIN        (1u)
#define BLEIOT_UART_REMOVE_UART_RTS_PIN            (1u)
#define BLEIOT_UART_REMOVE_UART_CTS_PIN            (1u)

/* Unconfigured pins */
#define BLEIOT_UART_RX_WAKE_SDA_MOSI_PIN (0u == BLEIOT_UART_REMOVE_RX_WAKE_SDA_MOSI_PIN)
#define BLEIOT_UART_RX_SDA_MOSI_PIN     (0u == BLEIOT_UART_REMOVE_RX_SDA_MOSI_PIN)
#define BLEIOT_UART_TX_SCL_MISO_PIN     (0u == BLEIOT_UART_REMOVE_TX_SCL_MISO_PIN)
#define BLEIOT_UART_CTS_SCLK_PIN     (0u == BLEIOT_UART_REMOVE_CTS_SCLK_PIN)
#define BLEIOT_UART_RTS_SS0_PIN     (0u == BLEIOT_UART_REMOVE_RTS_SS0_PIN)
#define BLEIOT_UART_SS1_PIN                (0u == BLEIOT_UART_REMOVE_SS1_PIN)
#define BLEIOT_UART_SS2_PIN                (0u == BLEIOT_UART_REMOVE_SS2_PIN)
#define BLEIOT_UART_SS3_PIN                (0u == BLEIOT_UART_REMOVE_SS3_PIN)

/* Mode defined pins */
#define BLEIOT_UART_I2C_PINS               (0u == BLEIOT_UART_REMOVE_I2C_PINS)
#define BLEIOT_UART_SPI_MASTER_PINS        (0u == BLEIOT_UART_REMOVE_SPI_MASTER_PINS)
#define BLEIOT_UART_SPI_MASTER_SCLK_PIN    (0u == BLEIOT_UART_REMOVE_SPI_MASTER_SCLK_PIN)
#define BLEIOT_UART_SPI_MASTER_MOSI_PIN    (0u == BLEIOT_UART_REMOVE_SPI_MASTER_MOSI_PIN)
#define BLEIOT_UART_SPI_MASTER_MISO_PIN    (0u == BLEIOT_UART_REMOVE_SPI_MASTER_MISO_PIN)
#define BLEIOT_UART_SPI_MASTER_SS0_PIN     (0u == BLEIOT_UART_REMOVE_SPI_MASTER_SS0_PIN)
#define BLEIOT_UART_SPI_MASTER_SS1_PIN     (0u == BLEIOT_UART_REMOVE_SPI_MASTER_SS1_PIN)
#define BLEIOT_UART_SPI_MASTER_SS2_PIN     (0u == BLEIOT_UART_REMOVE_SPI_MASTER_SS2_PIN)
#define BLEIOT_UART_SPI_MASTER_SS3_PIN     (0u == BLEIOT_UART_REMOVE_SPI_MASTER_SS3_PIN)
#define BLEIOT_UART_SPI_SLAVE_PINS         (0u == BLEIOT_UART_REMOVE_SPI_SLAVE_PINS)
#define BLEIOT_UART_SPI_SLAVE_MOSI_PIN     (0u == BLEIOT_UART_REMOVE_SPI_SLAVE_MOSI_PIN)
#define BLEIOT_UART_SPI_SLAVE_MISO_PIN     (0u == BLEIOT_UART_REMOVE_SPI_SLAVE_MISO_PIN)
#define BLEIOT_UART_UART_TX_PIN            (0u == BLEIOT_UART_REMOVE_UART_TX_PIN)
#define BLEIOT_UART_UART_RX_TX_PIN         (0u == BLEIOT_UART_REMOVE_UART_RX_TX_PIN)
#define BLEIOT_UART_UART_RX_PIN            (0u == BLEIOT_UART_REMOVE_UART_RX_PIN)
#define BLEIOT_UART_UART_RX_WAKE_PIN       (0u == BLEIOT_UART_REMOVE_UART_RX_WAKE_PIN)
#define BLEIOT_UART_UART_RTS_PIN           (0u == BLEIOT_UART_REMOVE_UART_RTS_PIN)
#define BLEIOT_UART_UART_CTS_PIN           (0u == BLEIOT_UART_REMOVE_UART_CTS_PIN)


/***************************************
*             Includes
****************************************/

#if (BLEIOT_UART_RX_WAKE_SDA_MOSI_PIN)
    #include "BLEIOT_UART_uart_rx_wake_i2c_sda_spi_mosi.h"
#endif /* (BLEIOT_UART_RX_SDA_MOSI) */

#if (BLEIOT_UART_RX_SDA_MOSI_PIN)
    #include "BLEIOT_UART_uart_rx_i2c_sda_spi_mosi.h"
#endif /* (BLEIOT_UART_RX_SDA_MOSI) */

#if (BLEIOT_UART_TX_SCL_MISO_PIN)
    #include "BLEIOT_UART_uart_tx_i2c_scl_spi_miso.h"
#endif /* (BLEIOT_UART_TX_SCL_MISO) */

#if (BLEIOT_UART_CTS_SCLK_PIN)
    #include "BLEIOT_UART_uart_cts_spi_sclk.h"
#endif /* (BLEIOT_UART_CTS_SCLK) */

#if (BLEIOT_UART_RTS_SS0_PIN)
    #include "BLEIOT_UART_uart_rts_spi_ss0.h"
#endif /* (BLEIOT_UART_RTS_SS0_PIN) */

#if (BLEIOT_UART_SS1_PIN)
    #include "BLEIOT_UART_spi_ss1.h"
#endif /* (BLEIOT_UART_SS1_PIN) */

#if (BLEIOT_UART_SS2_PIN)
    #include "BLEIOT_UART_spi_ss2.h"
#endif /* (BLEIOT_UART_SS2_PIN) */

#if (BLEIOT_UART_SS3_PIN)
    #include "BLEIOT_UART_spi_ss3.h"
#endif /* (BLEIOT_UART_SS3_PIN) */

#if (BLEIOT_UART_I2C_PINS)
    #include "BLEIOT_UART_scl.h"
    #include "BLEIOT_UART_sda.h"
#endif /* (BLEIOT_UART_I2C_PINS) */

#if (BLEIOT_UART_SPI_MASTER_PINS)
#if (BLEIOT_UART_SPI_MASTER_SCLK_PIN)
    #include "BLEIOT_UART_sclk_m.h"
#endif /* (BLEIOT_UART_SPI_MASTER_SCLK_PIN) */

#if (BLEIOT_UART_SPI_MASTER_MOSI_PIN)
    #include "BLEIOT_UART_mosi_m.h"
#endif /* (BLEIOT_UART_SPI_MASTER_MOSI_PIN) */

#if (BLEIOT_UART_SPI_MASTER_MISO_PIN)
    #include "BLEIOT_UART_miso_m.h"
#endif /*(BLEIOT_UART_SPI_MASTER_MISO_PIN) */
#endif /* (BLEIOT_UART_SPI_MASTER_PINS) */

#if (BLEIOT_UART_SPI_SLAVE_PINS)
    #include "BLEIOT_UART_sclk_s.h"
    #include "BLEIOT_UART_ss_s.h"

#if (BLEIOT_UART_SPI_SLAVE_MOSI_PIN)
    #include "BLEIOT_UART_mosi_s.h"
#endif /* (BLEIOT_UART_SPI_SLAVE_MOSI_PIN) */

#if (BLEIOT_UART_SPI_SLAVE_MISO_PIN)
    #include "BLEIOT_UART_miso_s.h"
#endif /*(BLEIOT_UART_SPI_SLAVE_MISO_PIN) */
#endif /* (BLEIOT_UART_SPI_SLAVE_PINS) */

#if (BLEIOT_UART_SPI_MASTER_SS0_PIN)
    #include "BLEIOT_UART_ss0_m.h"
#endif /* (BLEIOT_UART_SPI_MASTER_SS0_PIN) */

#if (BLEIOT_UART_SPI_MASTER_SS1_PIN)
    #include "BLEIOT_UART_ss1_m.h"
#endif /* (BLEIOT_UART_SPI_MASTER_SS1_PIN) */

#if (BLEIOT_UART_SPI_MASTER_SS2_PIN)
    #include "BLEIOT_UART_ss2_m.h"
#endif /* (BLEIOT_UART_SPI_MASTER_SS2_PIN) */

#if (BLEIOT_UART_SPI_MASTER_SS3_PIN)
    #include "BLEIOT_UART_ss3_m.h"
#endif /* (BLEIOT_UART_SPI_MASTER_SS3_PIN) */

#if (BLEIOT_UART_UART_TX_PIN)
    #include "BLEIOT_UART_tx.h"
#endif /* (BLEIOT_UART_UART_TX_PIN) */

#if (BLEIOT_UART_UART_RX_TX_PIN)
    #include "BLEIOT_UART_rx_tx.h"
#endif /* (BLEIOT_UART_UART_RX_TX_PIN) */

#if (BLEIOT_UART_UART_RX_PIN)
    #include "BLEIOT_UART_rx.h"
#endif /* (BLEIOT_UART_UART_RX_PIN) */

#if (BLEIOT_UART_UART_RX_WAKE_PIN)
    #include "BLEIOT_UART_rx_wake.h"
#endif /* (BLEIOT_UART_UART_RX_WAKE_PIN) */

#if (BLEIOT_UART_UART_RTS_PIN)
    #include "BLEIOT_UART_rts.h"
#endif /* (BLEIOT_UART_UART_RTS_PIN) */

#if (BLEIOT_UART_UART_CTS_PIN)
    #include "BLEIOT_UART_cts.h"
#endif /* (BLEIOT_UART_UART_CTS_PIN) */


/***************************************
*              Registers
***************************************/

#if (BLEIOT_UART_RX_WAKE_SDA_MOSI_PIN)
    #define BLEIOT_UART_RX_WAKE_SDA_MOSI_HSIOM_REG \
                            (*(reg32 *) BLEIOT_UART_uart_rx_wake_i2c_sda_spi_mosi__0__HSIOM)
    #define BLEIOT_UART_RX_WAKE_SDA_MOSI_HSIOM_PTR \
                            ( (reg32 *) BLEIOT_UART_uart_rx_wake_i2c_sda_spi_mosi__0__HSIOM)
    #define BLEIOT_UART_RX_WAKE_SDA_MOSI_HSIOM_MASK \
                            (BLEIOT_UART_uart_rx_wake_i2c_sda_spi_mosi__0__HSIOM_MASK)
    #define BLEIOT_UART_RX_WAKE_SDA_MOSI_HSIOM_POS \
                            (BLEIOT_UART_uart_rx_wake_i2c_sda_spi_mosi__0__HSIOM_SHIFT)

    #define BLEIOT_UART_RX_WAKE_SDA_MOSI_INTCFG_REG \
                            (*(reg32 *) BLEIOT_UART_uart_rx_wake_i2c_sda_spi_mosi__0__INTCFG)
    #define BLEIOT_UART_RX_WAKE_SDA_MOSI_INTCFG_PTR \
                            ( (reg32 *) BLEIOT_UART_uart_rx_wake_i2c_sda_spi_mosi__0__INTCFG)
    #define BLEIOT_UART_RX_WAKE_SDA_MOSI_INTCFG_TYPE_POS  (BLEIOT_UART_uart_rx_wake_i2c_sda_spi_mosi__SHIFT)
    #define BLEIOT_UART_RX_WAKE_SDA_MOSI_INTCFG_TYPE_MASK \
                            ((uint32) BLEIOT_UART_INTCFG_TYPE_MASK << \
                                      BLEIOT_UART_RX_WAKE_SDA_MOSI_INTCFG_TYPE_POS)
#endif /* (BLEIOT_UART_RX_WAKE_SDA_MOSI_PIN) */

#if (BLEIOT_UART_RX_SDA_MOSI_PIN)
    #define BLEIOT_UART_RX_SDA_MOSI_HSIOM_REG   (*(reg32 *) BLEIOT_UART_uart_rx_i2c_sda_spi_mosi__0__HSIOM)
    #define BLEIOT_UART_RX_SDA_MOSI_HSIOM_PTR   ( (reg32 *) BLEIOT_UART_uart_rx_i2c_sda_spi_mosi__0__HSIOM)
    #define BLEIOT_UART_RX_SDA_MOSI_HSIOM_MASK  (BLEIOT_UART_uart_rx_i2c_sda_spi_mosi__0__HSIOM_MASK)
    #define BLEIOT_UART_RX_SDA_MOSI_HSIOM_POS   (BLEIOT_UART_uart_rx_i2c_sda_spi_mosi__0__HSIOM_SHIFT)
#endif /* (BLEIOT_UART_RX_SDA_MOSI_PIN) */

#if (BLEIOT_UART_TX_SCL_MISO_PIN)
    #define BLEIOT_UART_TX_SCL_MISO_HSIOM_REG   (*(reg32 *) BLEIOT_UART_uart_tx_i2c_scl_spi_miso__0__HSIOM)
    #define BLEIOT_UART_TX_SCL_MISO_HSIOM_PTR   ( (reg32 *) BLEIOT_UART_uart_tx_i2c_scl_spi_miso__0__HSIOM)
    #define BLEIOT_UART_TX_SCL_MISO_HSIOM_MASK  (BLEIOT_UART_uart_tx_i2c_scl_spi_miso__0__HSIOM_MASK)
    #define BLEIOT_UART_TX_SCL_MISO_HSIOM_POS   (BLEIOT_UART_uart_tx_i2c_scl_spi_miso__0__HSIOM_SHIFT)
#endif /* (BLEIOT_UART_TX_SCL_MISO_PIN) */

#if (BLEIOT_UART_CTS_SCLK_PIN)
    #define BLEIOT_UART_CTS_SCLK_HSIOM_REG   (*(reg32 *) BLEIOT_UART_uart_cts_spi_sclk__0__HSIOM)
    #define BLEIOT_UART_CTS_SCLK_HSIOM_PTR   ( (reg32 *) BLEIOT_UART_uart_cts_spi_sclk__0__HSIOM)
    #define BLEIOT_UART_CTS_SCLK_HSIOM_MASK  (BLEIOT_UART_uart_cts_spi_sclk__0__HSIOM_MASK)
    #define BLEIOT_UART_CTS_SCLK_HSIOM_POS   (BLEIOT_UART_uart_cts_spi_sclk__0__HSIOM_SHIFT)
#endif /* (BLEIOT_UART_CTS_SCLK_PIN) */

#if (BLEIOT_UART_RTS_SS0_PIN)
    #define BLEIOT_UART_RTS_SS0_HSIOM_REG   (*(reg32 *) BLEIOT_UART_uart_rts_spi_ss0__0__HSIOM)
    #define BLEIOT_UART_RTS_SS0_HSIOM_PTR   ( (reg32 *) BLEIOT_UART_uart_rts_spi_ss0__0__HSIOM)
    #define BLEIOT_UART_RTS_SS0_HSIOM_MASK  (BLEIOT_UART_uart_rts_spi_ss0__0__HSIOM_MASK)
    #define BLEIOT_UART_RTS_SS0_HSIOM_POS   (BLEIOT_UART_uart_rts_spi_ss0__0__HSIOM_SHIFT)
#endif /* (BLEIOT_UART_RTS_SS0_PIN) */

#if (BLEIOT_UART_SS1_PIN)
    #define BLEIOT_UART_SS1_HSIOM_REG      (*(reg32 *) BLEIOT_UART_spi_ss1__0__HSIOM)
    #define BLEIOT_UART_SS1_HSIOM_PTR      ( (reg32 *) BLEIOT_UART_spi_ss1__0__HSIOM)
    #define BLEIOT_UART_SS1_HSIOM_MASK     (BLEIOT_UART_spi_ss1__0__HSIOM_MASK)
    #define BLEIOT_UART_SS1_HSIOM_POS      (BLEIOT_UART_spi_ss1__0__HSIOM_SHIFT)
#endif /* (BLEIOT_UART_SS1_PIN) */

#if (BLEIOT_UART_SS2_PIN)
    #define BLEIOT_UART_SS2_HSIOM_REG     (*(reg32 *) BLEIOT_UART_spi_ss2__0__HSIOM)
    #define BLEIOT_UART_SS2_HSIOM_PTR     ( (reg32 *) BLEIOT_UART_spi_ss2__0__HSIOM)
    #define BLEIOT_UART_SS2_HSIOM_MASK    (BLEIOT_UART_spi_ss2__0__HSIOM_MASK)
    #define BLEIOT_UART_SS2_HSIOM_POS     (BLEIOT_UART_spi_ss2__0__HSIOM_SHIFT)
#endif /* (BLEIOT_UART_SS2_PIN) */

#if (BLEIOT_UART_SS3_PIN)
    #define BLEIOT_UART_SS3_HSIOM_REG     (*(reg32 *) BLEIOT_UART_spi_ss3__0__HSIOM)
    #define BLEIOT_UART_SS3_HSIOM_PTR     ( (reg32 *) BLEIOT_UART_spi_ss3__0__HSIOM)
    #define BLEIOT_UART_SS3_HSIOM_MASK    (BLEIOT_UART_spi_ss3__0__HSIOM_MASK)
    #define BLEIOT_UART_SS3_HSIOM_POS     (BLEIOT_UART_spi_ss3__0__HSIOM_SHIFT)
#endif /* (BLEIOT_UART_SS3_PIN) */

#if (BLEIOT_UART_I2C_PINS)
    #define BLEIOT_UART_SCL_HSIOM_REG     (*(reg32 *) BLEIOT_UART_scl__0__HSIOM)
    #define BLEIOT_UART_SCL_HSIOM_PTR     ( (reg32 *) BLEIOT_UART_scl__0__HSIOM)
    #define BLEIOT_UART_SCL_HSIOM_MASK    (BLEIOT_UART_scl__0__HSIOM_MASK)
    #define BLEIOT_UART_SCL_HSIOM_POS     (BLEIOT_UART_scl__0__HSIOM_SHIFT)

    #define BLEIOT_UART_SDA_HSIOM_REG     (*(reg32 *) BLEIOT_UART_sda__0__HSIOM)
    #define BLEIOT_UART_SDA_HSIOM_PTR     ( (reg32 *) BLEIOT_UART_sda__0__HSIOM)
    #define BLEIOT_UART_SDA_HSIOM_MASK    (BLEIOT_UART_sda__0__HSIOM_MASK)
    #define BLEIOT_UART_SDA_HSIOM_POS     (BLEIOT_UART_sda__0__HSIOM_SHIFT)
#endif /* (BLEIOT_UART_I2C_PINS) */

#if (BLEIOT_UART_SPI_MASTER_SCLK_PIN)
    #define BLEIOT_UART_SCLK_M_HSIOM_REG   (*(reg32 *) BLEIOT_UART_sclk_m__0__HSIOM)
    #define BLEIOT_UART_SCLK_M_HSIOM_PTR   ( (reg32 *) BLEIOT_UART_sclk_m__0__HSIOM)
    #define BLEIOT_UART_SCLK_M_HSIOM_MASK  (BLEIOT_UART_sclk_m__0__HSIOM_MASK)
    #define BLEIOT_UART_SCLK_M_HSIOM_POS   (BLEIOT_UART_sclk_m__0__HSIOM_SHIFT)
#endif /* (BLEIOT_UART_SPI_MASTER_SCLK_PIN) */

#if (BLEIOT_UART_SPI_MASTER_SS0_PIN)
    #define BLEIOT_UART_SS0_M_HSIOM_REG    (*(reg32 *) BLEIOT_UART_ss0_m__0__HSIOM)
    #define BLEIOT_UART_SS0_M_HSIOM_PTR    ( (reg32 *) BLEIOT_UART_ss0_m__0__HSIOM)
    #define BLEIOT_UART_SS0_M_HSIOM_MASK   (BLEIOT_UART_ss0_m__0__HSIOM_MASK)
    #define BLEIOT_UART_SS0_M_HSIOM_POS    (BLEIOT_UART_ss0_m__0__HSIOM_SHIFT)
#endif /* (BLEIOT_UART_SPI_MASTER_SS0_PIN) */

#if (BLEIOT_UART_SPI_MASTER_SS1_PIN)
    #define BLEIOT_UART_SS1_M_HSIOM_REG    (*(reg32 *) BLEIOT_UART_ss1_m__0__HSIOM)
    #define BLEIOT_UART_SS1_M_HSIOM_PTR    ( (reg32 *) BLEIOT_UART_ss1_m__0__HSIOM)
    #define BLEIOT_UART_SS1_M_HSIOM_MASK   (BLEIOT_UART_ss1_m__0__HSIOM_MASK)
    #define BLEIOT_UART_SS1_M_HSIOM_POS    (BLEIOT_UART_ss1_m__0__HSIOM_SHIFT)
#endif /* (BLEIOT_UART_SPI_MASTER_SS1_PIN) */

#if (BLEIOT_UART_SPI_MASTER_SS2_PIN)
    #define BLEIOT_UART_SS2_M_HSIOM_REG    (*(reg32 *) BLEIOT_UART_ss2_m__0__HSIOM)
    #define BLEIOT_UART_SS2_M_HSIOM_PTR    ( (reg32 *) BLEIOT_UART_ss2_m__0__HSIOM)
    #define BLEIOT_UART_SS2_M_HSIOM_MASK   (BLEIOT_UART_ss2_m__0__HSIOM_MASK)
    #define BLEIOT_UART_SS2_M_HSIOM_POS    (BLEIOT_UART_ss2_m__0__HSIOM_SHIFT)
#endif /* (BLEIOT_UART_SPI_MASTER_SS2_PIN) */

#if (BLEIOT_UART_SPI_MASTER_SS3_PIN)
    #define BLEIOT_UART_SS3_M_HSIOM_REG    (*(reg32 *) BLEIOT_UART_ss3_m__0__HSIOM)
    #define BLEIOT_UART_SS3_M_HSIOM_PTR    ( (reg32 *) BLEIOT_UART_ss3_m__0__HSIOM)
    #define BLEIOT_UART_SS3_M_HSIOM_MASK   (BLEIOT_UART_ss3_m__0__HSIOM_MASK)
    #define BLEIOT_UART_SS3_M_HSIOM_POS    (BLEIOT_UART_ss3_m__0__HSIOM_SHIFT)
#endif /* (BLEIOT_UART_SPI_MASTER_SS3_PIN) */

#if (BLEIOT_UART_UART_TX_PIN)
    #define BLEIOT_UART_TX_HSIOM_REG   (*(reg32 *) BLEIOT_UART_tx__0__HSIOM)
    #define BLEIOT_UART_TX_HSIOM_PTR   ( (reg32 *) BLEIOT_UART_tx_0__HSIOM)
    #define BLEIOT_UART_TX_HSIOM_MASK  (BLEIOT_UART_tx__0__HSIOM_MASK)
    #define BLEIOT_UART_TX_HSIOM_POS   (BLEIOT_UART_tx__0__HSIOM_SHIFT)
#endif /* (BLEIOT_UART_UART_TX_PIN) */

#if (BLEIOT_UART_UART_RTS_PIN)
    #define BLEIOT_UART_RTS_HSIOM_REG  (*(reg32 *) BLEIOT_UART_rts__0__HSIOM)
    #define BLEIOT_UART_RTS_HSIOM_PTR  ( (reg32 *) BLEIOT_UART_rts__0__HSIOM)
    #define BLEIOT_UART_RTS_HSIOM_MASK (BLEIOT_UART_rts__0__HSIOM_MASK)
    #define BLEIOT_UART_RTS_HSIOM_POS  (BLEIOT_UART_rts__0__HSIOM_SHIFT)
#endif /* (BLEIOT_UART_UART_RTS_PIN) */


/***************************************
*        Registers Constants
***************************************/

/* Pins constants */
#define BLEIOT_UART_HSIOM_DEF_SEL      (0x00u)
#define BLEIOT_UART_HSIOM_GPIO_SEL     (0x00u)
#define BLEIOT_UART_HSIOM_UART_SEL     (0x09u)
#define BLEIOT_UART_HSIOM_I2C_SEL      (0x0Eu)
#define BLEIOT_UART_HSIOM_SPI_SEL      (0x0Fu)

#define BLEIOT_UART_RX_WAKE_SDA_MOSI_PIN_INDEX   (0u)
#define BLEIOT_UART_RX_SDA_MOSI_PIN_INDEX       (0u)
#define BLEIOT_UART_TX_SCL_MISO_PIN_INDEX       (1u)
#define BLEIOT_UART_CTS_SCLK_PIN_INDEX       (2u)
#define BLEIOT_UART_RTS_SS0_PIN_INDEX       (3u)
#define BLEIOT_UART_SS1_PIN_INDEX                  (4u)
#define BLEIOT_UART_SS2_PIN_INDEX                  (5u)
#define BLEIOT_UART_SS3_PIN_INDEX                  (6u)

#define BLEIOT_UART_RX_WAKE_SDA_MOSI_PIN_MASK ((uint32) 0x01u << BLEIOT_UART_RX_WAKE_SDA_MOSI_PIN_INDEX)
#define BLEIOT_UART_RX_SDA_MOSI_PIN_MASK     ((uint32) 0x01u << BLEIOT_UART_RX_SDA_MOSI_PIN_INDEX)
#define BLEIOT_UART_TX_SCL_MISO_PIN_MASK     ((uint32) 0x01u << BLEIOT_UART_TX_SCL_MISO_PIN_INDEX)
#define BLEIOT_UART_CTS_SCLK_PIN_MASK     ((uint32) 0x01u << BLEIOT_UART_CTS_SCLK_PIN_INDEX)
#define BLEIOT_UART_RTS_SS0_PIN_MASK     ((uint32) 0x01u << BLEIOT_UART_RTS_SS0_PIN_INDEX)
#define BLEIOT_UART_SS1_PIN_MASK                ((uint32) 0x01u << BLEIOT_UART_SS1_PIN_INDEX)
#define BLEIOT_UART_SS2_PIN_MASK                ((uint32) 0x01u << BLEIOT_UART_SS2_PIN_INDEX)
#define BLEIOT_UART_SS3_PIN_MASK                ((uint32) 0x01u << BLEIOT_UART_SS3_PIN_INDEX)

/* Pin interrupt constants */
#define BLEIOT_UART_INTCFG_TYPE_MASK           (0x03u)
#define BLEIOT_UART_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin Drive Mode constants */
#define BLEIOT_UART_PIN_DM_ALG_HIZ  (0u)
#define BLEIOT_UART_PIN_DM_DIG_HIZ  (1u)
#define BLEIOT_UART_PIN_DM_OD_LO    (4u)
#define BLEIOT_UART_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Return drive mode of the pin */
#define BLEIOT_UART_DM_MASK    (0x7u)
#define BLEIOT_UART_DM_SIZE    (3)
#define BLEIOT_UART_GET_P4_PIN_DM(reg, pos) \
    ( ((reg) & (uint32) ((uint32) BLEIOT_UART_DM_MASK << (BLEIOT_UART_DM_SIZE * (pos)))) >> \
                                                              (BLEIOT_UART_DM_SIZE * (pos)) )

#if (BLEIOT_UART_TX_SCL_MISO_PIN)
    #define BLEIOT_UART_CHECK_TX_SCL_MISO_PIN_USED \
                (BLEIOT_UART_PIN_DM_ALG_HIZ != \
                    BLEIOT_UART_GET_P4_PIN_DM(BLEIOT_UART_uart_tx_i2c_scl_spi_miso_PC, \
                                                   BLEIOT_UART_uart_tx_i2c_scl_spi_miso_SHIFT))
#endif /* (BLEIOT_UART_TX_SCL_MISO_PIN) */

#if (BLEIOT_UART_RTS_SS0_PIN)
    #define BLEIOT_UART_CHECK_RTS_SS0_PIN_USED \
                (BLEIOT_UART_PIN_DM_ALG_HIZ != \
                    BLEIOT_UART_GET_P4_PIN_DM(BLEIOT_UART_uart_rts_spi_ss0_PC, \
                                                   BLEIOT_UART_uart_rts_spi_ss0_SHIFT))
#endif /* (BLEIOT_UART_RTS_SS0_PIN) */

/* Set bits-mask in register */
#define BLEIOT_UART_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit in the register */
#define BLEIOT_UART_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define BLEIOT_UART_SET_HSIOM_SEL(reg, mask, pos, sel) BLEIOT_UART_SET_REGISTER_BITS(reg, mask, pos, sel)
#define BLEIOT_UART_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        BLEIOT_UART_SET_REGISTER_BITS(reg, mask, pos, intType)
#define BLEIOT_UART_SET_INP_DIS(reg, mask, val) BLEIOT_UART_SET_REGISTER_BIT(reg, mask, val)

/* BLEIOT_UART_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  BLEIOT_UART_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if (BLEIOT_UART_CY_SCBIP_V0)
#if (BLEIOT_UART_I2C_PINS)
    #define BLEIOT_UART_SET_I2C_SCL_DR(val) BLEIOT_UART_scl_Write(val)

    #define BLEIOT_UART_SET_I2C_SCL_HSIOM_SEL(sel) \
                          BLEIOT_UART_SET_HSIOM_SEL(BLEIOT_UART_SCL_HSIOM_REG,  \
                                                         BLEIOT_UART_SCL_HSIOM_MASK, \
                                                         BLEIOT_UART_SCL_HSIOM_POS,  \
                                                         (sel))
    #define BLEIOT_UART_WAIT_SCL_SET_HIGH  (0u == BLEIOT_UART_scl_Read())

/* Unconfigured SCB: scl signal */
#elif (BLEIOT_UART_RX_WAKE_SDA_MOSI_PIN)
    #define BLEIOT_UART_SET_I2C_SCL_DR(val) \
                            BLEIOT_UART_uart_rx_wake_i2c_sda_spi_mosi_Write(val)

    #define BLEIOT_UART_SET_I2C_SCL_HSIOM_SEL(sel) \
                    BLEIOT_UART_SET_HSIOM_SEL(BLEIOT_UART_RX_WAKE_SDA_MOSI_HSIOM_REG,  \
                                                   BLEIOT_UART_RX_WAKE_SDA_MOSI_HSIOM_MASK, \
                                                   BLEIOT_UART_RX_WAKE_SDA_MOSI_HSIOM_POS,  \
                                                   (sel))

    #define BLEIOT_UART_WAIT_SCL_SET_HIGH  (0u == BLEIOT_UART_uart_rx_wake_i2c_sda_spi_mosi_Read())

#elif (BLEIOT_UART_RX_SDA_MOSI_PIN)
    #define BLEIOT_UART_SET_I2C_SCL_DR(val) \
                            BLEIOT_UART_uart_rx_i2c_sda_spi_mosi_Write(val)


    #define BLEIOT_UART_SET_I2C_SCL_HSIOM_SEL(sel) \
                            BLEIOT_UART_SET_HSIOM_SEL(BLEIOT_UART_RX_SDA_MOSI_HSIOM_REG,  \
                                                           BLEIOT_UART_RX_SDA_MOSI_HSIOM_MASK, \
                                                           BLEIOT_UART_RX_SDA_MOSI_HSIOM_POS,  \
                                                           (sel))

    #define BLEIOT_UART_WAIT_SCL_SET_HIGH  (0u == BLEIOT_UART_uart_rx_i2c_sda_spi_mosi_Read())

#else
    #define BLEIOT_UART_SET_I2C_SCL_DR(val) \
                                                    do{ /* Does nothing */ }while(0)
    #define BLEIOT_UART_SET_I2C_SCL_HSIOM_SEL(sel) \
                                                    do{ /* Does nothing */ }while(0)

    #define BLEIOT_UART_WAIT_SCL_SET_HIGH  (0u)
#endif /* (BLEIOT_UART_I2C_PINS) */

/* SCB I2C: sda signal */
#if (BLEIOT_UART_I2C_PINS)
    #define BLEIOT_UART_WAIT_SDA_SET_HIGH  (0u == BLEIOT_UART_sda_Read())
/* Unconfigured SCB: sda signal */
#elif (BLEIOT_UART_TX_SCL_MISO_PIN)
    #define BLEIOT_UART_WAIT_SDA_SET_HIGH  (0u == BLEIOT_UART_uart_tx_i2c_scl_spi_miso_Read())
#else
    #define BLEIOT_UART_WAIT_SDA_SET_HIGH  (0u)
#endif /* (BLEIOT_UART_MOSI_SCL_RX_PIN) */
#endif /* (BLEIOT_UART_CY_SCBIP_V0) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Unconfigured pins */
#define BLEIOT_UART_REMOVE_MOSI_SCL_RX_WAKE_PIN    BLEIOT_UART_REMOVE_RX_WAKE_SDA_MOSI_PIN
#define BLEIOT_UART_REMOVE_MOSI_SCL_RX_PIN         BLEIOT_UART_REMOVE_RX_SDA_MOSI_PIN
#define BLEIOT_UART_REMOVE_MISO_SDA_TX_PIN         BLEIOT_UART_REMOVE_TX_SCL_MISO_PIN
#ifndef BLEIOT_UART_REMOVE_SCLK_PIN
#define BLEIOT_UART_REMOVE_SCLK_PIN                BLEIOT_UART_REMOVE_CTS_SCLK_PIN
#endif /* BLEIOT_UART_REMOVE_SCLK_PIN */
#ifndef BLEIOT_UART_REMOVE_SS0_PIN
#define BLEIOT_UART_REMOVE_SS0_PIN                 BLEIOT_UART_REMOVE_RTS_SS0_PIN
#endif /* BLEIOT_UART_REMOVE_SS0_PIN */

/* Unconfigured pins */
#define BLEIOT_UART_MOSI_SCL_RX_WAKE_PIN   BLEIOT_UART_RX_WAKE_SDA_MOSI_PIN
#define BLEIOT_UART_MOSI_SCL_RX_PIN        BLEIOT_UART_RX_SDA_MOSI_PIN
#define BLEIOT_UART_MISO_SDA_TX_PIN        BLEIOT_UART_TX_SCL_MISO_PIN
#ifndef BLEIOT_UART_SCLK_PIN
#define BLEIOT_UART_SCLK_PIN               BLEIOT_UART_CTS_SCLK_PIN
#endif /* BLEIOT_UART_SCLK_PIN */
#ifndef BLEIOT_UART_SS0_PIN
#define BLEIOT_UART_SS0_PIN                BLEIOT_UART_RTS_SS0_PIN
#endif /* BLEIOT_UART_SS0_PIN */

#if (BLEIOT_UART_MOSI_SCL_RX_WAKE_PIN)
    #define BLEIOT_UART_MOSI_SCL_RX_WAKE_HSIOM_REG     BLEIOT_UART_RX_WAKE_SDA_MOSI_HSIOM_REG
    #define BLEIOT_UART_MOSI_SCL_RX_WAKE_HSIOM_PTR     BLEIOT_UART_RX_WAKE_SDA_MOSI_HSIOM_REG
    #define BLEIOT_UART_MOSI_SCL_RX_WAKE_HSIOM_MASK    BLEIOT_UART_RX_WAKE_SDA_MOSI_HSIOM_REG
    #define BLEIOT_UART_MOSI_SCL_RX_WAKE_HSIOM_POS     BLEIOT_UART_RX_WAKE_SDA_MOSI_HSIOM_REG

    #define BLEIOT_UART_MOSI_SCL_RX_WAKE_INTCFG_REG    BLEIOT_UART_RX_WAKE_SDA_MOSI_HSIOM_REG
    #define BLEIOT_UART_MOSI_SCL_RX_WAKE_INTCFG_PTR    BLEIOT_UART_RX_WAKE_SDA_MOSI_HSIOM_REG

    #define BLEIOT_UART_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS   BLEIOT_UART_RX_WAKE_SDA_MOSI_HSIOM_REG
    #define BLEIOT_UART_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK  BLEIOT_UART_RX_WAKE_SDA_MOSI_HSIOM_REG
#endif /* (BLEIOT_UART_RX_WAKE_SDA_MOSI_PIN) */

#if (BLEIOT_UART_MOSI_SCL_RX_PIN)
    #define BLEIOT_UART_MOSI_SCL_RX_HSIOM_REG      BLEIOT_UART_RX_SDA_MOSI_HSIOM_REG
    #define BLEIOT_UART_MOSI_SCL_RX_HSIOM_PTR      BLEIOT_UART_RX_SDA_MOSI_HSIOM_PTR
    #define BLEIOT_UART_MOSI_SCL_RX_HSIOM_MASK     BLEIOT_UART_RX_SDA_MOSI_HSIOM_MASK
    #define BLEIOT_UART_MOSI_SCL_RX_HSIOM_POS      BLEIOT_UART_RX_SDA_MOSI_HSIOM_POS
#endif /* (BLEIOT_UART_MOSI_SCL_RX_PIN) */

#if (BLEIOT_UART_MISO_SDA_TX_PIN)
    #define BLEIOT_UART_MISO_SDA_TX_HSIOM_REG      BLEIOT_UART_TX_SCL_MISO_HSIOM_REG
    #define BLEIOT_UART_MISO_SDA_TX_HSIOM_PTR      BLEIOT_UART_TX_SCL_MISO_HSIOM_REG
    #define BLEIOT_UART_MISO_SDA_TX_HSIOM_MASK     BLEIOT_UART_TX_SCL_MISO_HSIOM_REG
    #define BLEIOT_UART_MISO_SDA_TX_HSIOM_POS      BLEIOT_UART_TX_SCL_MISO_HSIOM_REG
#endif /* (BLEIOT_UART_MISO_SDA_TX_PIN_PIN) */

#if (BLEIOT_UART_SCLK_PIN)
    #ifndef BLEIOT_UART_SCLK_HSIOM_REG
    #define BLEIOT_UART_SCLK_HSIOM_REG     BLEIOT_UART_CTS_SCLK_HSIOM_REG
    #define BLEIOT_UART_SCLK_HSIOM_PTR     BLEIOT_UART_CTS_SCLK_HSIOM_PTR
    #define BLEIOT_UART_SCLK_HSIOM_MASK    BLEIOT_UART_CTS_SCLK_HSIOM_MASK
    #define BLEIOT_UART_SCLK_HSIOM_POS     BLEIOT_UART_CTS_SCLK_HSIOM_POS
    #endif /* BLEIOT_UART_SCLK_HSIOM_REG */
#endif /* (BLEIOT_UART_SCLK_PIN) */

#if (BLEIOT_UART_SS0_PIN)
    #ifndef BLEIOT_UART_SS0_HSIOM_REG
    #define BLEIOT_UART_SS0_HSIOM_REG      BLEIOT_UART_RTS_SS0_HSIOM_REG
    #define BLEIOT_UART_SS0_HSIOM_PTR      BLEIOT_UART_RTS_SS0_HSIOM_PTR
    #define BLEIOT_UART_SS0_HSIOM_MASK     BLEIOT_UART_RTS_SS0_HSIOM_MASK
    #define BLEIOT_UART_SS0_HSIOM_POS      BLEIOT_UART_RTS_SS0_HSIOM_POS
    #endif /* BLEIOT_UART_SS0_HSIOM_REG */
#endif /* (BLEIOT_UART_SS0_PIN) */

#define BLEIOT_UART_MOSI_SCL_RX_WAKE_PIN_INDEX BLEIOT_UART_RX_WAKE_SDA_MOSI_PIN_INDEX
#define BLEIOT_UART_MOSI_SCL_RX_PIN_INDEX      BLEIOT_UART_RX_SDA_MOSI_PIN_INDEX
#define BLEIOT_UART_MISO_SDA_TX_PIN_INDEX      BLEIOT_UART_TX_SCL_MISO_PIN_INDEX
#ifndef BLEIOT_UART_SCLK_PIN_INDEX
#define BLEIOT_UART_SCLK_PIN_INDEX             BLEIOT_UART_CTS_SCLK_PIN_INDEX
#endif /* BLEIOT_UART_SCLK_PIN_INDEX */
#ifndef BLEIOT_UART_SS0_PIN_INDEX
#define BLEIOT_UART_SS0_PIN_INDEX              BLEIOT_UART_RTS_SS0_PIN_INDEX
#endif /* BLEIOT_UART_SS0_PIN_INDEX */

#define BLEIOT_UART_MOSI_SCL_RX_WAKE_PIN_MASK BLEIOT_UART_RX_WAKE_SDA_MOSI_PIN_MASK
#define BLEIOT_UART_MOSI_SCL_RX_PIN_MASK      BLEIOT_UART_RX_SDA_MOSI_PIN_MASK
#define BLEIOT_UART_MISO_SDA_TX_PIN_MASK      BLEIOT_UART_TX_SCL_MISO_PIN_MASK
#ifndef BLEIOT_UART_SCLK_PIN_MASK
#define BLEIOT_UART_SCLK_PIN_MASK             BLEIOT_UART_CTS_SCLK_PIN_MASK
#endif /* BLEIOT_UART_SCLK_PIN_MASK */
#ifndef BLEIOT_UART_SS0_PIN_MASK
#define BLEIOT_UART_SS0_PIN_MASK              BLEIOT_UART_RTS_SS0_PIN_MASK
#endif /* BLEIOT_UART_SS0_PIN_MASK */

#endif /* (CY_SCB_PINS_BLEIOT_UART_H) */


/* [] END OF FILE */
