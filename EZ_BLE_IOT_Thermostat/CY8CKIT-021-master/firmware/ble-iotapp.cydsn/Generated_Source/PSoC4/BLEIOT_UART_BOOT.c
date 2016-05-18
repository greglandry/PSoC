/*******************************************************************************
* File Name: BLEIOT_UART_BOOT.c
* Version 3.10
*
* Description:
*  This file provides the source code of the bootloader communication APIs
*  for the SCB Component Unconfigured mode.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "BLEIOT_UART_BOOT.h"

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (BLEIOT_UART_BTLDR_COMM_ENABLED) && \
                                (BLEIOT_UART_SCB_MODE_UNCONFIG_CONST_CFG)

/*******************************************************************************
* Function Name: BLEIOT_UART_CyBtldrCommStart
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommStart function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void BLEIOT_UART_CyBtldrCommStart(void)
{
    if (BLEIOT_UART_SCB_MODE_I2C_RUNTM_CFG)
    {
        BLEIOT_UART_I2CCyBtldrCommStart();
    }
    else if (BLEIOT_UART_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        BLEIOT_UART_EzI2CCyBtldrCommStart();
    }
#if (!BLEIOT_UART_CY_SCBIP_V1)
    else if (BLEIOT_UART_SCB_MODE_SPI_RUNTM_CFG)
    {
        BLEIOT_UART_SpiCyBtldrCommStart();
    }
    else if (BLEIOT_UART_SCB_MODE_UART_RUNTM_CFG)
    {
        BLEIOT_UART_UartCyBtldrCommStart();
    }
#endif /* (!BLEIOT_UART_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
}


/*******************************************************************************
* Function Name: BLEIOT_UART_CyBtldrCommStop
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommStop function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void BLEIOT_UART_CyBtldrCommStop(void)
{
    if (BLEIOT_UART_SCB_MODE_I2C_RUNTM_CFG)
    {
        BLEIOT_UART_I2CCyBtldrCommStop();
    }
    else if (BLEIOT_UART_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        BLEIOT_UART_EzI2CCyBtldrCommStop();
    }
#if (!BLEIOT_UART_CY_SCBIP_V1)
    else if (BLEIOT_UART_SCB_MODE_SPI_RUNTM_CFG)
    {
        BLEIOT_UART_SpiCyBtldrCommStop();
    }
    else if (BLEIOT_UART_SCB_MODE_UART_RUNTM_CFG)
    {
        BLEIOT_UART_UartCyBtldrCommStop();
    }
#endif /* (!BLEIOT_UART_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
}


/*******************************************************************************
* Function Name: BLEIOT_UART_CyBtldrCommReset
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommReset function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void BLEIOT_UART_CyBtldrCommReset(void)
{
    if(BLEIOT_UART_SCB_MODE_I2C_RUNTM_CFG)
    {
        BLEIOT_UART_I2CCyBtldrCommReset();
    }
    else if(BLEIOT_UART_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        BLEIOT_UART_EzI2CCyBtldrCommReset();
    }
#if (!BLEIOT_UART_CY_SCBIP_V1)
    else if(BLEIOT_UART_SCB_MODE_SPI_RUNTM_CFG)
    {
        BLEIOT_UART_SpiCyBtldrCommReset();
    }
    else if(BLEIOT_UART_SCB_MODE_UART_RUNTM_CFG)
    {
        BLEIOT_UART_UartCyBtldrCommReset();
    }
#endif /* (!BLEIOT_UART_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
}


/*******************************************************************************
* Function Name: BLEIOT_UART_CyBtldrCommRead
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommRead function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  pData:    Pointer to storage for the block of data to be read from the
*            bootloader host
*  size:     Number of bytes to be read.
*  count:    Pointer to the variable to write the number of bytes actually
*            read.
*  timeOut:  Number of units in 10 ms to wait before returning because of a
*            timeout.
*
* Return:
*  Returns CYRET_SUCCESS if no problem was encountered or returns the value
*  that best describes the problem.
*
*******************************************************************************/
cystatus BLEIOT_UART_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    if(BLEIOT_UART_SCB_MODE_I2C_RUNTM_CFG)
    {
        status = BLEIOT_UART_I2CCyBtldrCommRead(pData, size, count, timeOut);
    }
    else if(BLEIOT_UART_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        status = BLEIOT_UART_EzI2CCyBtldrCommRead(pData, size, count, timeOut);
    }
#if (!BLEIOT_UART_CY_SCBIP_V1)
    else if(BLEIOT_UART_SCB_MODE_SPI_RUNTM_CFG)
    {
        status = BLEIOT_UART_SpiCyBtldrCommRead(pData, size, count, timeOut);
    }
    else if(BLEIOT_UART_SCB_MODE_UART_RUNTM_CFG)
    {
        status = BLEIOT_UART_UartCyBtldrCommRead(pData, size, count, timeOut);
    }
#endif /* (!BLEIOT_UART_CY_SCBIP_V1) */
    else
    {
        status = CYRET_INVALID_STATE; /* Unknown mode: return invalid status */
    }

    return(status);
}


/*******************************************************************************
* Function Name: BLEIOT_UART_CyBtldrCommWrite
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommWrite  function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  pData:    Pointer to the block of data to be written to the bootloader host.
*  size:     Number of bytes to be written.
*  count:    Pointer to the variable to write the number of bytes actually
*            written.
*  timeOut:  Number of units in 10 ms to wait before returning because of a
*            timeout.
*
* Return:
*  Returns CYRET_SUCCESS if no problem was encountered or returns the value
*  that best describes the problem.
*
*******************************************************************************/
cystatus BLEIOT_UART_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    if(BLEIOT_UART_SCB_MODE_I2C_RUNTM_CFG)
    {
        status = BLEIOT_UART_I2CCyBtldrCommWrite(pData, size, count, timeOut);
    }
    else if(BLEIOT_UART_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        status = BLEIOT_UART_EzI2CCyBtldrCommWrite(pData, size, count, timeOut);
    }
#if (!BLEIOT_UART_CY_SCBIP_V1)
    else if(BLEIOT_UART_SCB_MODE_SPI_RUNTM_CFG)
    {
        status = BLEIOT_UART_SpiCyBtldrCommWrite(pData, size, count, timeOut);
    }
    else if(BLEIOT_UART_SCB_MODE_UART_RUNTM_CFG)
    {
        status = BLEIOT_UART_UartCyBtldrCommWrite(pData, size, count, timeOut);
    }
#endif /* (!BLEIOT_UART_CY_SCBIP_V1) */
    else
    {
        status = CYRET_INVALID_STATE; /* Unknown mode: return invalid status */
    }

    return(status);
}

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (BLEIOT_UART_BTLDR_COMM_MODE_ENABLED) */


/* [] END OF FILE */
