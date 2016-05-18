/*******************************************************************************
* File Name: BLEIOT_UART_rx.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "BLEIOT_UART_rx.h"

static BLEIOT_UART_rx_BACKUP_STRUCT  BLEIOT_UART_rx_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: BLEIOT_UART_rx_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function must be called for SIO and USBIO
*  pins. It is not essential if using GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet BLEIOT_UART_rx_SUT.c usage_BLEIOT_UART_rx_Sleep_Wakeup
*******************************************************************************/
void BLEIOT_UART_rx_Sleep(void)
{
    #if defined(BLEIOT_UART_rx__PC)
        BLEIOT_UART_rx_backup.pcState = BLEIOT_UART_rx_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            BLEIOT_UART_rx_backup.usbState = BLEIOT_UART_rx_CR1_REG;
            BLEIOT_UART_rx_USB_POWER_REG |= BLEIOT_UART_rx_USBIO_ENTER_SLEEP;
            BLEIOT_UART_rx_CR1_REG &= BLEIOT_UART_rx_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(BLEIOT_UART_rx__SIO)
        BLEIOT_UART_rx_backup.sioState = BLEIOT_UART_rx_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        BLEIOT_UART_rx_SIO_REG &= (uint32)(~BLEIOT_UART_rx_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: BLEIOT_UART_rx_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep().
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to BLEIOT_UART_rx_Sleep() for an example usage.
*******************************************************************************/
void BLEIOT_UART_rx_Wakeup(void)
{
    #if defined(BLEIOT_UART_rx__PC)
        BLEIOT_UART_rx_PC = BLEIOT_UART_rx_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            BLEIOT_UART_rx_USB_POWER_REG &= BLEIOT_UART_rx_USBIO_EXIT_SLEEP_PH1;
            BLEIOT_UART_rx_CR1_REG = BLEIOT_UART_rx_backup.usbState;
            BLEIOT_UART_rx_USB_POWER_REG &= BLEIOT_UART_rx_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(BLEIOT_UART_rx__SIO)
        BLEIOT_UART_rx_SIO_REG = BLEIOT_UART_rx_backup.sioState;
    #endif
}


/* [] END OF FILE */
