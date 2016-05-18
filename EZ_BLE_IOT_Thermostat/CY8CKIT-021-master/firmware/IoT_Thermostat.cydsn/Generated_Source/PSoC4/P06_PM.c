/*******************************************************************************
* File Name: P06.c  
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
#include "P06.h"

static P06_BACKUP_STRUCT  P06_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: P06_Sleep
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
*  \snippet P06_SUT.c usage_P06_Sleep_Wakeup
*******************************************************************************/
void P06_Sleep(void)
{
    #if defined(P06__PC)
        P06_backup.pcState = P06_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            P06_backup.usbState = P06_CR1_REG;
            P06_USB_POWER_REG |= P06_USBIO_ENTER_SLEEP;
            P06_CR1_REG &= P06_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(P06__SIO)
        P06_backup.sioState = P06_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        P06_SIO_REG &= (uint32)(~P06_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: P06_Wakeup
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
*  Refer to P06_Sleep() for an example usage.
*******************************************************************************/
void P06_Wakeup(void)
{
    #if defined(P06__PC)
        P06_PC = P06_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            P06_USB_POWER_REG &= P06_USBIO_EXIT_SLEEP_PH1;
            P06_CR1_REG = P06_backup.usbState;
            P06_USB_POWER_REG &= P06_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(P06__SIO)
        P06_SIO_REG = P06_backup.sioState;
    #endif
}


/* [] END OF FILE */
