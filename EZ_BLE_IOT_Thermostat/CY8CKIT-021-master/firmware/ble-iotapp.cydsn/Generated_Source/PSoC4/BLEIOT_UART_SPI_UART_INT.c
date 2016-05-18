/*******************************************************************************
* File Name: BLEIOT_UART_SPI_UART_INT.c
* Version 3.10
*
* Description:
*  This file provides the source code to the Interrupt Service Routine for
*  the SCB Component in SPI and UART modes.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "BLEIOT_UART_PVT.h"
#include "BLEIOT_UART_SPI_UART_PVT.h"
#include "cyapicallbacks.h"

#if (BLEIOT_UART_SCB_IRQ_INTERNAL)
/*******************************************************************************
* Function Name: BLEIOT_UART_SPI_UART_ISR
********************************************************************************
*
* Summary:
*  Handles the Interrupt Service Routine for the SCB SPI or UART modes.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
CY_ISR(BLEIOT_UART_SPI_UART_ISR)
{
#if (BLEIOT_UART_INTERNAL_RX_SW_BUFFER_CONST)
    uint32 locHead;
#endif /* (BLEIOT_UART_INTERNAL_RX_SW_BUFFER_CONST) */

#if (BLEIOT_UART_INTERNAL_TX_SW_BUFFER_CONST)
    uint32 locTail;
#endif /* (BLEIOT_UART_INTERNAL_TX_SW_BUFFER_CONST) */

#ifdef BLEIOT_UART_SPI_UART_ISR_ENTRY_CALLBACK
    BLEIOT_UART_SPI_UART_ISR_EntryCallback();
#endif /* BLEIOT_UART_SPI_UART_ISR_ENTRY_CALLBACK */

    if (NULL != BLEIOT_UART_customIntrHandler)
    {
        BLEIOT_UART_customIntrHandler();
    }

    #if (BLEIOT_UART_CHECK_SPI_WAKE_ENABLE)
    {
        /* Clear SPI wakeup source */
        BLEIOT_UART_ClearSpiExtClkInterruptSource(BLEIOT_UART_INTR_SPI_EC_WAKE_UP);
    }
    #endif

    #if (BLEIOT_UART_CHECK_RX_SW_BUFFER)
    {
        if (BLEIOT_UART_CHECK_INTR_RX_MASKED(BLEIOT_UART_INTR_RX_NOT_EMPTY))
        {
            do
            {
                /* Move local head index */
                locHead = (BLEIOT_UART_rxBufferHead + 1u);

                /* Adjust local head index */
                if (BLEIOT_UART_INTERNAL_RX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                if (locHead == BLEIOT_UART_rxBufferTail)
                {
                    #if (BLEIOT_UART_CHECK_UART_RTS_CONTROL_FLOW)
                    {
                        /* There is no space in the software buffer - disable the
                        * RX Not Empty interrupt source. The data elements are
                        * still being received into the RX FIFO until the RTS signal
                        * stops the transmitter. After the data element is read from the
                        * buffer, the RX Not Empty interrupt source is enabled to
                        * move the next data element in the software buffer.
                        */
                        BLEIOT_UART_INTR_RX_MASK_REG &= ~BLEIOT_UART_INTR_RX_NOT_EMPTY;
                        break;
                    }
                    #else
                    {
                        /* Overflow: through away received data element */
                        (void) BLEIOT_UART_RX_FIFO_RD_REG;
                        BLEIOT_UART_rxBufferOverflow = (uint8) BLEIOT_UART_INTR_RX_OVERFLOW;
                    }
                    #endif
                }
                else
                {
                    /* Store received data */
                    BLEIOT_UART_PutWordInRxBuffer(locHead, BLEIOT_UART_RX_FIFO_RD_REG);

                    /* Move head index */
                    BLEIOT_UART_rxBufferHead = locHead;
                }
            }
            while(0u != BLEIOT_UART_GET_RX_FIFO_ENTRIES);

            BLEIOT_UART_ClearRxInterruptSource(BLEIOT_UART_INTR_RX_NOT_EMPTY);
        }
    }
    #endif


    #if (BLEIOT_UART_CHECK_TX_SW_BUFFER)
    {
        if (BLEIOT_UART_CHECK_INTR_TX_MASKED(BLEIOT_UART_INTR_TX_NOT_FULL))
        {
            do
            {
                /* Check for room in TX software buffer */
                if (BLEIOT_UART_txBufferHead != BLEIOT_UART_txBufferTail)
                {
                    /* Move local tail index */
                    locTail = (BLEIOT_UART_txBufferTail + 1u);

                    /* Adjust local tail index */
                    if (BLEIOT_UART_TX_BUFFER_SIZE == locTail)
                    {
                        locTail = 0u;
                    }

                    /* Put data into TX FIFO */
                    BLEIOT_UART_TX_FIFO_WR_REG = BLEIOT_UART_GetWordFromTxBuffer(locTail);

                    /* Move tail index */
                    BLEIOT_UART_txBufferTail = locTail;
                }
                else
                {
                    /* TX software buffer is empty: complete transfer */
                    BLEIOT_UART_DISABLE_INTR_TX(BLEIOT_UART_INTR_TX_NOT_FULL);
                    break;
                }
            }
            while (BLEIOT_UART_SPI_UART_FIFO_SIZE != BLEIOT_UART_GET_TX_FIFO_ENTRIES);

            BLEIOT_UART_ClearTxInterruptSource(BLEIOT_UART_INTR_TX_NOT_FULL);
        }
    }
    #endif
    
#ifdef BLEIOT_UART_SPI_UART_ISR_EXIT_CALLBACK
    BLEIOT_UART_SPI_UART_ISR_ExitCallback();
#endif /* BLEIOT_UART_SPI_UART_ISR_EXIT_CALLBACK */
    
}

#endif /* (BLEIOT_UART_SCB_IRQ_INTERNAL) */


/* [] END OF FILE */
