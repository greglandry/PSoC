/***************************************************************************//**
* \file CYBLE_custom.h
* \version 3.10
* 
* \brief
*  Contains the function prototypes and constants for the Custom Service.
* 
********************************************************************************
* \copyright
* Copyright 2014-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_BLE_CYBLE_CUSTOM_H)
#define CY_BLE_CYBLE_CUSTOM_H

#include "BLE_gatt.h"


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Maximum supported Custom Services */
#define CYBLE_CUSTOMS_SERVICE_COUNT                  (0x01u)
#define CYBLE_CUSTOMC_SERVICE_COUNT                  (0x00u)
#define CYBLE_CUSTOM_SERVICE_CHAR_COUNT              (0x0Cu)
#define CYBLE_CUSTOM_SERVICE_CHAR_DESCRIPTORS_COUNT  (0x02u)

/* Below are the indexes and handles of the defined Custom Services and their characteristics */
#define CYBLE_CY8CKIT021_SERVICE_INDEX   (0x00u) /* Index of CY8CKIT021 service in the cyBle_customs array */
#define CYBLE_CY8CKIT021_BOOTLOAD_CHAR_INDEX   (0x00u) /* Index of bootload characteristic */
#define CYBLE_CY8CKIT021_BOOTLOAD_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_CY8CKIT021_BLUE_CHAR_INDEX   (0x01u) /* Index of blue characteristic */
#define CYBLE_CY8CKIT021_BLUE_CCCD_DESC_INDEX   (0x00u) /* Index of CCCD descriptor */
#define CYBLE_CY8CKIT021_BLUE_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x01u) /* Index of Characteristic User Description descriptor */
#define CYBLE_CY8CKIT021_LED0_CHAR_INDEX   (0x02u) /* Index of led0 characteristic */
#define CYBLE_CY8CKIT021_LED0_CCCD_DESC_INDEX   (0x00u) /* Index of CCCD descriptor */
#define CYBLE_CY8CKIT021_LED0_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x01u) /* Index of Characteristic User Description descriptor */
#define CYBLE_CY8CKIT021_LED1_CHAR_INDEX   (0x03u) /* Index of led1 characteristic */
#define CYBLE_CY8CKIT021_LED1_CCCD_DESC_INDEX   (0x00u) /* Index of CCCD descriptor */
#define CYBLE_CY8CKIT021_LED1_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x01u) /* Index of Characteristic User Description descriptor */
#define CYBLE_CY8CKIT021_BUTTON0_CHAR_INDEX   (0x04u) /* Index of button0 characteristic */
#define CYBLE_CY8CKIT021_BUTTON0_CCCD_DESC_INDEX   (0x00u) /* Index of CCCD descriptor */
#define CYBLE_CY8CKIT021_BUTTON0_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x01u) /* Index of Characteristic User Description descriptor */
#define CYBLE_CY8CKIT021_BUTTON1_CHAR_INDEX   (0x05u) /* Index of button1 characteristic */
#define CYBLE_CY8CKIT021_BUTTON1_CCCD_DESC_INDEX   (0x00u) /* Index of CCCD descriptor */
#define CYBLE_CY8CKIT021_BUTTON1_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x01u) /* Index of Characteristic User Description descriptor */
#define CYBLE_CY8CKIT021_TRIM_CHAR_INDEX   (0x06u) /* Index of trim characteristic */
#define CYBLE_CY8CKIT021_TRIM_CCCD_DESC_INDEX   (0x00u) /* Index of CCCD descriptor */
#define CYBLE_CY8CKIT021_TRIM_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x01u) /* Index of Characteristic User Description descriptor */
#define CYBLE_CY8CKIT021_CONTRAST_CHAR_INDEX   (0x07u) /* Index of contrast characteristic */
#define CYBLE_CY8CKIT021_CONTRAST_CCCD_DESC_INDEX   (0x00u) /* Index of CCCD descriptor */
#define CYBLE_CY8CKIT021_CONTRAST_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x01u) /* Index of Characteristic User Description descriptor */
#define CYBLE_CY8CKIT021_DISPLAY_CHAR_INDEX   (0x08u) /* Index of display characteristic */
#define CYBLE_CY8CKIT021_DISPLAY_CCCD_DESC_INDEX   (0x00u) /* Index of CCCD descriptor */
#define CYBLE_CY8CKIT021_DISPLAY_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x01u) /* Index of Characteristic User Description descriptor */
#define CYBLE_CY8CKIT021_TONE_CHAR_INDEX   (0x09u) /* Index of tone characteristic */
#define CYBLE_CY8CKIT021_TONE_CCCD_DESC_INDEX   (0x00u) /* Index of CCCD descriptor */
#define CYBLE_CY8CKIT021_TONE_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x01u) /* Index of Characteristic User Description descriptor */
#define CYBLE_CY8CKIT021_TEMPERATURE_CHAR_INDEX   (0x0Au) /* Index of temperature characteristic */
#define CYBLE_CY8CKIT021_TEMPERATURE_CCCD_DESC_INDEX   (0x00u) /* Index of CCCD descriptor */
#define CYBLE_CY8CKIT021_TEMPERATURE_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x01u) /* Index of Characteristic User Description descriptor */
#define CYBLE_CY8CKIT021_POT_CHAR_INDEX   (0x0Bu) /* Index of pot characteristic */
#define CYBLE_CY8CKIT021_POT_CCCD_DESC_INDEX   (0x00u) /* Index of CCCD descriptor */
#define CYBLE_CY8CKIT021_POT_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x01u) /* Index of Characteristic User Description descriptor */


#define CYBLE_CY8CKIT021_SERVICE_HANDLE   (0x000Eu) /* Handle of CY8CKIT021 service */
#define CYBLE_CY8CKIT021_BOOTLOAD_DECL_HANDLE   (0x000Fu) /* Handle of bootload characteristic declaration */
#define CYBLE_CY8CKIT021_BOOTLOAD_CHAR_HANDLE   (0x0010u) /* Handle of bootload characteristic */
#define CYBLE_CY8CKIT021_BOOTLOAD_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x0011u) /* Handle of Characteristic User Description descriptor */
#define CYBLE_CY8CKIT021_BLUE_DECL_HANDLE   (0x0012u) /* Handle of blue characteristic declaration */
#define CYBLE_CY8CKIT021_BLUE_CHAR_HANDLE   (0x0013u) /* Handle of blue characteristic */
#define CYBLE_CY8CKIT021_BLUE_CCCD_DESC_HANDLE   (0x0014u) /* Handle of CCCD descriptor */
#define CYBLE_CY8CKIT021_BLUE_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x0015u) /* Handle of Characteristic User Description descriptor */
#define CYBLE_CY8CKIT021_LED0_DECL_HANDLE   (0x0016u) /* Handle of led0 characteristic declaration */
#define CYBLE_CY8CKIT021_LED0_CHAR_HANDLE   (0x0017u) /* Handle of led0 characteristic */
#define CYBLE_CY8CKIT021_LED0_CCCD_DESC_HANDLE   (0x0018u) /* Handle of CCCD descriptor */
#define CYBLE_CY8CKIT021_LED0_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x0019u) /* Handle of Characteristic User Description descriptor */
#define CYBLE_CY8CKIT021_LED1_DECL_HANDLE   (0x001Au) /* Handle of led1 characteristic declaration */
#define CYBLE_CY8CKIT021_LED1_CHAR_HANDLE   (0x001Bu) /* Handle of led1 characteristic */
#define CYBLE_CY8CKIT021_LED1_CCCD_DESC_HANDLE   (0x001Cu) /* Handle of CCCD descriptor */
#define CYBLE_CY8CKIT021_LED1_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x001Du) /* Handle of Characteristic User Description descriptor */
#define CYBLE_CY8CKIT021_BUTTON0_DECL_HANDLE   (0x001Eu) /* Handle of button0 characteristic declaration */
#define CYBLE_CY8CKIT021_BUTTON0_CHAR_HANDLE   (0x001Fu) /* Handle of button0 characteristic */
#define CYBLE_CY8CKIT021_BUTTON0_CCCD_DESC_HANDLE   (0x0020u) /* Handle of CCCD descriptor */
#define CYBLE_CY8CKIT021_BUTTON0_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x0021u) /* Handle of Characteristic User Description descriptor */
#define CYBLE_CY8CKIT021_BUTTON1_DECL_HANDLE   (0x0022u) /* Handle of button1 characteristic declaration */
#define CYBLE_CY8CKIT021_BUTTON1_CHAR_HANDLE   (0x0023u) /* Handle of button1 characteristic */
#define CYBLE_CY8CKIT021_BUTTON1_CCCD_DESC_HANDLE   (0x0024u) /* Handle of CCCD descriptor */
#define CYBLE_CY8CKIT021_BUTTON1_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x0025u) /* Handle of Characteristic User Description descriptor */
#define CYBLE_CY8CKIT021_TRIM_DECL_HANDLE   (0x0026u) /* Handle of trim characteristic declaration */
#define CYBLE_CY8CKIT021_TRIM_CHAR_HANDLE   (0x0027u) /* Handle of trim characteristic */
#define CYBLE_CY8CKIT021_TRIM_CCCD_DESC_HANDLE   (0x0028u) /* Handle of CCCD descriptor */
#define CYBLE_CY8CKIT021_TRIM_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x0029u) /* Handle of Characteristic User Description descriptor */
#define CYBLE_CY8CKIT021_CONTRAST_DECL_HANDLE   (0x002Au) /* Handle of contrast characteristic declaration */
#define CYBLE_CY8CKIT021_CONTRAST_CHAR_HANDLE   (0x002Bu) /* Handle of contrast characteristic */
#define CYBLE_CY8CKIT021_CONTRAST_CCCD_DESC_HANDLE   (0x002Cu) /* Handle of CCCD descriptor */
#define CYBLE_CY8CKIT021_CONTRAST_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x002Du) /* Handle of Characteristic User Description descriptor */
#define CYBLE_CY8CKIT021_DISPLAY_DECL_HANDLE   (0x002Eu) /* Handle of display characteristic declaration */
#define CYBLE_CY8CKIT021_DISPLAY_CHAR_HANDLE   (0x002Fu) /* Handle of display characteristic */
#define CYBLE_CY8CKIT021_DISPLAY_CCCD_DESC_HANDLE   (0x0030u) /* Handle of CCCD descriptor */
#define CYBLE_CY8CKIT021_DISPLAY_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x0031u) /* Handle of Characteristic User Description descriptor */
#define CYBLE_CY8CKIT021_TONE_DECL_HANDLE   (0x0032u) /* Handle of tone characteristic declaration */
#define CYBLE_CY8CKIT021_TONE_CHAR_HANDLE   (0x0033u) /* Handle of tone characteristic */
#define CYBLE_CY8CKIT021_TONE_CCCD_DESC_HANDLE   (0x0034u) /* Handle of CCCD descriptor */
#define CYBLE_CY8CKIT021_TONE_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x0035u) /* Handle of Characteristic User Description descriptor */
#define CYBLE_CY8CKIT021_TEMPERATURE_DECL_HANDLE   (0x0036u) /* Handle of temperature characteristic declaration */
#define CYBLE_CY8CKIT021_TEMPERATURE_CHAR_HANDLE   (0x0037u) /* Handle of temperature characteristic */
#define CYBLE_CY8CKIT021_TEMPERATURE_CCCD_DESC_HANDLE   (0x0038u) /* Handle of CCCD descriptor */
#define CYBLE_CY8CKIT021_TEMPERATURE_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x0039u) /* Handle of Characteristic User Description descriptor */
#define CYBLE_CY8CKIT021_POT_DECL_HANDLE   (0x003Au) /* Handle of pot characteristic declaration */
#define CYBLE_CY8CKIT021_POT_CHAR_HANDLE   (0x003Bu) /* Handle of pot characteristic */
#define CYBLE_CY8CKIT021_POT_CCCD_DESC_HANDLE   (0x003Cu) /* Handle of CCCD descriptor */
#define CYBLE_CY8CKIT021_POT_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x003Du) /* Handle of Characteristic User Description descriptor */



#if(CYBLE_CUSTOMS_SERVICE_COUNT != 0u)
    #define CYBLE_CUSTOM_SERVER
#endif /* (CYBLE_CUSTOMS_SERVICE_COUNT != 0u) */
    
#if(CYBLE_CUSTOMC_SERVICE_COUNT != 0u)
    #define CYBLE_CUSTOM_CLIENT
#endif /* (CYBLE_CUSTOMC_SERVICE_COUNT != 0u) */

/***************************************
* Data Struct Definition
***************************************/

/**
 \addtogroup group_service_api_custom
 @{
*/

#ifdef CYBLE_CUSTOM_SERVER

/** Contains information about Custom Characteristic structure */
typedef struct
{
    /** Custom Characteristic handle */
    CYBLE_GATT_DB_ATTR_HANDLE_T customServCharHandle;
    /** Custom Characteristic Descriptors handles */
    CYBLE_GATT_DB_ATTR_HANDLE_T customServCharDesc[     /* MDK doesn't allow array with zero length */
        CYBLE_CUSTOM_SERVICE_CHAR_DESCRIPTORS_COUNT == 0u ? 1u : CYBLE_CUSTOM_SERVICE_CHAR_DESCRIPTORS_COUNT];
} CYBLE_CUSTOMS_INFO_T;

/** Structure with Custom Service attribute handles. */
typedef struct
{
    /** Handle of a Custom Service */
    CYBLE_GATT_DB_ATTR_HANDLE_T customServHandle;
    
    /** Information about Custom Characteristics */
    CYBLE_CUSTOMS_INFO_T customServInfo[                /* MDK doesn't allow array with zero length */
        CYBLE_CUSTOM_SERVICE_CHAR_COUNT == 0u ? 1u : CYBLE_CUSTOM_SERVICE_CHAR_COUNT];
} CYBLE_CUSTOMS_T;


#endif /* (CYBLE_CUSTOM_SERVER) */

/** @} */

/** \cond IGNORE */
/* The custom Client functionality is not functional in current version of 
* the component.
*/
#ifdef CYBLE_CUSTOM_CLIENT

typedef struct
{
    /** Custom Descriptor handle */
    CYBLE_GATT_DB_ATTR_HANDLE_T descHandle;
	/** Custom Descriptor 128 bit UUID */
	const void *uuid;           
    /** UUID Format - 16-bit (0x01) or 128-bit (0x02) */
	uint8 uuidFormat;
   
} CYBLE_CUSTOMC_DESC_T;

typedef struct
{
    /** Characteristic handle */
    CYBLE_GATT_DB_ATTR_HANDLE_T customServCharHandle;
	/** Characteristic end handle */
    CYBLE_GATT_DB_ATTR_HANDLE_T customServCharEndHandle;
	/** Custom Characteristic UUID */
	const void *uuid;           
    /** UUID Format - 16-bit (0x01) or 128-bit (0x02) */
	uint8 uuidFormat;
    /** Properties for value field */
    uint8  properties;
	/** Number of descriptors */
    uint8 descCount;
    /** Characteristic Descriptors */
    CYBLE_CUSTOMC_DESC_T * customServCharDesc;
} CYBLE_CUSTOMC_CHAR_T;

/** Structure with discovered attributes information of Custom Service */
typedef struct
{
    /** Custom Service handle */
    CYBLE_GATT_DB_ATTR_HANDLE_T customServHandle;
	/** Custom Service UUID */
	const void *uuid;           
    /** UUID Format - 16-bit (0x01) or 128-bit (0x02) */
	uint8 uuidFormat;
	/** Number of characteristics */
    uint8 charCount;
    /** Custom Service Characteristics */
    CYBLE_CUSTOMC_CHAR_T * customServChar;
} CYBLE_CUSTOMC_T;

#endif /* (CYBLE_CUSTOM_CLIENT) */
/** \endcond */

#ifdef CYBLE_CUSTOM_SERVER

extern const CYBLE_CUSTOMS_T cyBle_customs[CYBLE_CUSTOMS_SERVICE_COUNT];

#endif /* (CYBLE_CUSTOM_SERVER) */

/** \cond IGNORE */
#ifdef CYBLE_CUSTOM_CLIENT

extern CYBLE_CUSTOMC_T cyBle_customc[CYBLE_CUSTOMC_SERVICE_COUNT];

#endif /* (CYBLE_CUSTOM_CLIENT) */
/** \endcond */


/***************************************
* Private Function Prototypes
***************************************/

/** \cond IGNORE */
void CyBle_CustomInit(void);

#ifdef CYBLE_CUSTOM_CLIENT

void CyBle_CustomcDiscoverServiceEventHandler(const CYBLE_DISC_SRVC128_INFO_T *discServInfo);
void CyBle_CustomcDiscoverCharacteristicsEventHandler(uint16 discoveryService, const CYBLE_DISC_CHAR_INFO_T *discCharInfo);
CYBLE_GATT_ATTR_HANDLE_RANGE_T CyBle_CustomcGetCharRange(uint8 incrementIndex);
void CyBle_CustomcDiscoverCharDescriptorsEventHandler(const CYBLE_DISC_DESCR_INFO_T *discDescrInfo);

#endif /* (CYBLE_CUSTOM_CLIENT) */

/** \endcond */

/***************************************
* External data references 
***************************************/

#ifdef CYBLE_CUSTOM_CLIENT

extern CYBLE_CUSTOMC_T cyBle_customCServ[CYBLE_CUSTOMC_SERVICE_COUNT];

#endif /* (CYBLE_CUSTOM_CLIENT) */


/** \cond IGNORE */
/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/
#define customServiceCharHandle         customServCharHandle
#define customServiceCharDescriptors    customServCharDesc
#define customServiceHandle             customServHandle
#define customServiceInfo               customServInfo
/** \endcond */


#endif /* CY_BLE_CYBLE_CUSTOM_H  */

/* [] END OF FILE */
