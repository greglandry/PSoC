/*******************************************************************************
* File Name: BLEIOT_UART_tx.c  
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
#include "BLEIOT_UART_tx.h"

static BLEIOT_UART_tx_BACKUP_STRUCT  BLEIOT_UART_tx_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: BLEIOT_UART_tx_Sleep
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
*  \snippet BLEIOT_UART_tx_SUT.c usage_BLEIOT_UART_tx_Sleep_Wakeup
*******************************************************************************/
void BLEIOT_UART_tx_Sleep(void)
{
    #if defined(BLEIOT_UART_tx__PC)
        BLEIOT_UART_tx_backup.pcState = BLEIOT_UART_tx_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            BLEIOT_UART_tx_backup.usbState = BLEIOT_UART_tx_CR1_REG;
            BLEIOT_UART_tx_USB_POWER_REG |= BLEIOT_UART_tx_USBIO_ENTER_SLEEP;
            BLEIOT_UART_tx_CR1_REG &= BLEIOT_UART_tx_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(BLEIOT_UART_tx__SIO)
        BLEIOT_UART_tx_backup.sioState = BLEIOT_UART_tx_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        BLEIOT_UART_tx_SIO_REG &= (uint32)(~BLEIOT_UART_tx_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: BLEIOT_UART_tx_Wakeup
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
*  Refer to BLEIOT_UART_tx_Sleep() for an example usage.
*******************************************************************************/
void BLEIOT_UART_tx_Wakeup(void)
{
    #if defined(BLEIOT_UART_tx__PC)
        BLEIOT_UART_tx_PC = BLEIOT_UART_tx_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            BLEIOT_UART_tx_USB_POWER_REG &= BLEIOT_UART_tx_USBIO_EXIT_SLEEP_PH1;
            BLEIOT_UART_tx_CR1_REG = BLEIOT_UART_tx_backup.usbState;
            BLEIOT_UART_tx_USB_POWER_REG &= BLEIOT_UART_tx_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(BLEIOT_UART_tx__SIO)
        BLEIOT_UART_tx_SIO_REG = BLEIOT_UART_tx_backup.sioState;
    #endif
}


/* [] END OF FILE */
