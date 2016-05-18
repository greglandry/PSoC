#include <project.h>
#include "BLEIOT_BLEIOT.h"

typedef struct NotifyFlags {
    uint8 blue;
    uint8 led0;
    uint8 led1;
    uint8 button0;
    uint8 button1;
    uint8 trim;
    uint8 contrast;
    uint8 display;
    uint8 tone;
    uint8 temperature;
    uint8 pot;
    
} NotifyFlags;

typedef union Types {
    uint8 bytes[2];
    int16 integer16;
    uint16 uinteger16;
} __attribute__((packed)) Types;


NotifyFlags notifyFlags;


/***************************************************************
 * Function to update the LED state in the GATT database
 **************************************************************/
void processBlueLed()
{
    switch(BLEIOT_local.blue)
            {
                case BLEIOT_ON:
                    PWM_Stop();
                    blue_Write(1); // in HW mode sw reg is OE.. output enable=on to drive active low
                    break;
                case BLEIOT_OFF:
                    PWM_Stop();
                    blue_Write(0); // in HW mode sw reg is OE.. output enable=off to drive tristate output
                break;
                case BLEIOT_BLECONTROL:
                    if(CyBle_GetState() == CYBLE_STATE_CONNECTED)
                    {
                        PWM_Stop();
                        blue_Write(1); // in HW mode sw reg is OE.. output enable=on to drive active low
                    }
                    else
                    if(CyBle_GetState() == CYBLE_STATE_ADVERTISING)
                    {
                        blue_Write(1); // turn the OE back on
                        PWM_Start();
                    }
                    else
                    {
                        blue_Write(0);
                        PWM_Stop();
                        //blue_Write(0); // in HW mode sw reg is OE.. output enable=off to drive tristate output
                    }
                break;
                case BLEIOT_BLINK:
                    blue_Write(1); // turn the OE back on
                    PWM_Start();
                break;
            }
}

void updateGattDB(uint8 *val,int size,uint8 notify, CYBLE_GATT_DB_ATTR_HANDLE_T handle,uint8 flags)
{
    
    // this little block of code doesnt make me happy... 
   
    switch(CyBle_GetState())
    {
        case CYBLE_STATE_ADVERTISING:
            return;
        case CYBLE_STATE_DISCONNECTED:
            return;
        case CYBLE_STATE_STOPPED:
            return;
        case CYBLE_STATE_CONNECTED:
            break;
        case CYBLE_STATE_INITIALIZING:
            return;
    }
        
    //update the GATT Database
    CYBLE_GATTS_HANDLE_VALUE_NTF_T 	tempHandle;
    tempHandle.attrHandle = handle;
  	tempHandle.value.val = val;
    tempHandle.value.len = size;
    CYBLE_GATT_ERR_CODE_T ret = CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,flags);
    if(ret != CYBLE_GATT_ERR_NONE) // this is really not a good place to be.
    {
        return;
        
        CYASSERT(0);
        while(1);
    }
    // if peer initiated then write response.
    if(flags == CYBLE_GATT_DB_PEER_INITIATED)
        CyBle_GattsWriteRsp(cyBle_connHandle);
    else if(notify) // If notify & local initiated 
    {
        CyBle_GattsNotification(cyBle_connHandle,&tempHandle);
    }    
}


/***************************************************************
 * Function to handle the BLE stack
 **************************************************************/
void BleCallBack(uint32 event, void* eventParam)
{
    CYBLE_GATTS_WRITE_REQ_PARAM_T *wrReqParam;

    switch(event)
    {
        /* if there is a disconnect or the stack just turned on from a reset then start the advertising and turn on the LED blinking */
        case CYBLE_EVT_STACK_ON:
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
            BLEIOT_updateBleState(BLEIOT_BLEADVERTISING);
            processBlueLed();
            memset(&notifyFlags,0,sizeof(notifyFlags));
        break;
            
        case CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP:
            processBlueLed();
        break;
        
            
        case CYBLE_EVT_GAP_DEVICE_CONNECTED:           
            
            BLEIOT_updateBleState(BLEIOT_BLECONNECTED);
            processBlueLed();
		   
            updateGattDB((uint8 *)&BLEIOT_local.blue,sizeof(BLEIOT_local.blue),notifyFlags.blue,CYBLE_CY8CKIT021_BLUE_CHAR_HANDLE,CYBLE_GATT_DB_LOCALLY_INITIATED);
            updateGattDB(&BLEIOT_local.led0,sizeof(BLEIOT_local.led0),notifyFlags.led0,CYBLE_CY8CKIT021_LED0_CHAR_HANDLE,CYBLE_GATT_DB_LOCALLY_INITIATED);
            updateGattDB(&BLEIOT_local.led1,sizeof(BLEIOT_local.led1),notifyFlags.led1,CYBLE_CY8CKIT021_LED1_CHAR_HANDLE,CYBLE_GATT_DB_LOCALLY_INITIATED);
            updateGattDB(&BLEIOT_local.button0,sizeof(BLEIOT_local.button0),notifyFlags.button0,CYBLE_CY8CKIT021_BUTTON0_CHAR_HANDLE,CYBLE_GATT_DB_LOCALLY_INITIATED);
            updateGattDB(&BLEIOT_local.button1,sizeof(BLEIOT_local.button1),notifyFlags.button1,CYBLE_CY8CKIT021_BUTTON1_CHAR_HANDLE,CYBLE_GATT_DB_LOCALLY_INITIATED);
            updateGattDB((uint8 *)&BLEIOT_local.trim,sizeof(BLEIOT_local.trim),notifyFlags.trim,CYBLE_CY8CKIT021_TRIM_CHAR_HANDLE,CYBLE_GATT_DB_LOCALLY_INITIATED);
            updateGattDB(&BLEIOT_local.contrast,sizeof(BLEIOT_local.contrast),notifyFlags.contrast,CYBLE_CY8CKIT021_CONTRAST_CHAR_HANDLE,CYBLE_GATT_DB_LOCALLY_INITIATED);            
            updateGattDB((uint8 *)&BLEIOT_local.display,sizeof(BLEIOT_local.display),notifyFlags.trim,CYBLE_CY8CKIT021_DISPLAY_CHAR_HANDLE,CYBLE_GATT_DB_LOCALLY_INITIATED);
            updateGattDB((uint8 *)&BLEIOT_local.tone,sizeof(BLEIOT_local.tone),notifyFlags.tone,CYBLE_CY8CKIT021_TONE_CHAR_HANDLE,CYBLE_GATT_DB_LOCALLY_INITIATED);
            updateGattDB((uint8 *)&BLEIOT_local.temperature,(BLEIOT_local.temperature),notifyFlags.temperature,CYBLE_CY8CKIT021_TEMPERATURE_CHAR_HANDLE,CYBLE_GATT_DB_LOCALLY_INITIATED);
            updateGattDB((uint8 *)&BLEIOT_local.pot,(BLEIOT_local.pot),notifyFlags.pot,CYBLE_CY8CKIT021_POT_CHAR_HANDLE,CYBLE_GATT_DB_LOCALLY_INITIATED);
        break;
            

        case CYBLE_EVT_GATTS_WRITE_REQ:
            wrReqParam = (CYBLE_GATTS_WRITE_REQ_PARAM_T *) eventParam;
			
            // Bootload
            #ifndef BootLoadable__DISABLED
      
            if(wrReqParam->handleValPair.attrHandle == CYBLE_CY8CKIT021_BOOTLOAD_CHAR_HANDLE)
            {
                if(wrReqParam->handleValPair.value.val[0])
                    Bootloadable_Load();
              
            }
            #endif
         
            
            /// BLUE
            if(wrReqParam->handleValPair.attrHandle == CYBLE_CY8CKIT021_BLUE_CHAR_HANDLE)
            {
                BLEIOT_updateBlue(wrReqParam->handleValPair.value.val[0]);
                processBlueLed();
                updateGattDB(wrReqParam->handleValPair.value.val,1,notifyFlags.blue,CYBLE_CY8CKIT021_BLUE_CHAR_HANDLE,CYBLE_GATT_DB_PEER_INITIATED);
            }
            
            if(wrReqParam->handleValPair.attrHandle == CYBLE_CY8CKIT021_BLUE_CCCD_DESC_HANDLE)
            {
                notifyFlags.blue = wrReqParam->handleValPair.value.val[0];
                CyBle_GattsWriteRsp(cyBle_connHandle);
            }
            
            // LED0
            
            if(wrReqParam->handleValPair.attrHandle == CYBLE_CY8CKIT021_LED0_CHAR_HANDLE)
            {
                BLEIOT_updateLed0(wrReqParam->handleValPair.value.val[0]);
                updateGattDB(wrReqParam->handleValPair.value.val,1,notifyFlags.led0,CYBLE_CY8CKIT021_LED0_CHAR_HANDLE,CYBLE_GATT_DB_PEER_INITIATED);
            }
            
            if(wrReqParam->handleValPair.attrHandle == CYBLE_CY8CKIT021_LED0_CCCD_DESC_HANDLE)
            {
                notifyFlags.led0 = wrReqParam->handleValPair.value.val[0];
                CyBle_GattsWriteRsp(cyBle_connHandle);
            }

            // LED1
            if(wrReqParam->handleValPair.attrHandle == CYBLE_CY8CKIT021_LED1_CHAR_HANDLE)
            {
                BLEIOT_updateLed1(wrReqParam->handleValPair.value.val[0]);
                updateGattDB(wrReqParam->handleValPair.value.val,1,notifyFlags.led0,CYBLE_CY8CKIT021_LED1_CHAR_HANDLE,CYBLE_GATT_DB_PEER_INITIATED);
            }
            
            if(wrReqParam->handleValPair.attrHandle == CYBLE_CY8CKIT021_LED1_CCCD_DESC_HANDLE)
            {
                notifyFlags.led1 = wrReqParam->handleValPair.value.val[0];
                CyBle_GattsWriteRsp(cyBle_connHandle);
            }
            
            // BUTTON 0
            if(wrReqParam->handleValPair.attrHandle == CYBLE_CY8CKIT021_BUTTON0_CCCD_DESC_HANDLE)
            {
                notifyFlags.button0 = wrReqParam->handleValPair.value.val[0];
                CyBle_GattsWriteRsp(cyBle_connHandle);
            }
           
            // BUTTON 1
            if(wrReqParam->handleValPair.attrHandle == CYBLE_CY8CKIT021_BUTTON1_CCCD_DESC_HANDLE)
            {
                notifyFlags.button1 = wrReqParam->handleValPair.value.val[0];
                CyBle_GattsWriteRsp(cyBle_connHandle);
            }

            // TRIM
            if(wrReqParam->handleValPair.attrHandle == CYBLE_CY8CKIT021_TRIM_CHAR_HANDLE)
            {
                Types *tu = (Types *)wrReqParam->handleValPair.value.val;
                BLEIOT_updateTrim(tu->integer16);
                updateGattDB(wrReqParam->handleValPair.value.val,2,notifyFlags.trim,CYBLE_CY8CKIT021_TRIM_CHAR_HANDLE,CYBLE_GATT_DB_PEER_INITIATED);
            }
            
            if(wrReqParam->handleValPair.attrHandle == CYBLE_CY8CKIT021_TRIM_CCCD_DESC_HANDLE)
            {
                notifyFlags.trim = wrReqParam->handleValPair.value.val[0];
                CyBle_GattsWriteRsp(cyBle_connHandle);
            }
            
            
            // Contrast
            if(wrReqParam->handleValPair.attrHandle == CYBLE_CY8CKIT021_CONTRAST_CHAR_HANDLE)
            {
                BLEIOT_updateContrast(wrReqParam->handleValPair.value.val[0]);
                updateGattDB(wrReqParam->handleValPair.value.val,1,notifyFlags.contrast,CYBLE_CY8CKIT021_CONTRAST_CHAR_HANDLE,CYBLE_GATT_DB_PEER_INITIATED);
            }
            
            if(wrReqParam->handleValPair.attrHandle == CYBLE_CY8CKIT021_CONTRAST_CCCD_DESC_HANDLE)
            {
                notifyFlags.contrast = wrReqParam->handleValPair.value.val[0];
                CyBle_GattsWriteRsp(cyBle_connHandle);
            }
            
            
            // DISPLAY
    
            if(wrReqParam->handleValPair.attrHandle == CYBLE_CY8CKIT021_DISPLAY_CHAR_HANDLE)
            {
                Types *tu = (Types *)wrReqParam->handleValPair.value.val;
                BLEIOT_updateDisplay(tu->uinteger16);
                updateGattDB(wrReqParam->handleValPair.value.val,2,notifyFlags.display,CYBLE_CY8CKIT021_DISPLAY_CHAR_HANDLE,CYBLE_GATT_DB_PEER_INITIATED);
            }
            if(wrReqParam->handleValPair.attrHandle == CYBLE_CY8CKIT021_DISPLAY_CCCD_DESC_HANDLE)
            {
                notifyFlags.display = wrReqParam->handleValPair.value.val[0];
                CyBle_GattsWriteRsp(cyBle_connHandle);
            }
    
            // TONE
            if(wrReqParam->handleValPair.attrHandle == CYBLE_CY8CKIT021_TONE_CHAR_HANDLE)
            {
                Types *tu = (Types *)wrReqParam->handleValPair.value.val;
                BLEIOT_updateTone(tu->uinteger16);
                updateGattDB(wrReqParam->handleValPair.value.val,2,notifyFlags.tone,CYBLE_CY8CKIT021_TONE_CHAR_HANDLE,CYBLE_GATT_DB_PEER_INITIATED);
            }
            
            if(wrReqParam->handleValPair.attrHandle == CYBLE_CY8CKIT021_TONE_CCCD_DESC_HANDLE)
            {
                notifyFlags.tone = wrReqParam->handleValPair.value.val[0];
                CyBle_GattsWriteRsp(cyBle_connHandle);
            }
            
           
             // TEMPERTATURE
            if(wrReqParam->handleValPair.attrHandle == CYBLE_CY8CKIT021_TEMPERATURE_CCCD_DESC_HANDLE)
            {
                notifyFlags.temperature = wrReqParam->handleValPair.value.val[0];
                CyBle_GattsWriteRsp(cyBle_connHandle);
            }
            
            
            // POT
            if(wrReqParam->handleValPair.attrHandle == CYBLE_CY8CKIT021_POT_CCCD_DESC_HANDLE)
            {
                notifyFlags.pot = wrReqParam->handleValPair.value.val[0];
                CyBle_GattsWriteRsp(cyBle_connHandle);
            }
            
  	    break;  
        
        default:
            break;
    }
} 

#define LED_ON 0
#define LED_OFF 1
int main()
{

    
    CyGlobalIntEnable;
    BLEIOT_Start();
    processBlueLed();
    
    EZI2C_Start();
    EZI2C_EzI2CSetBuffer1(sizeof(BLEIOT_local),1,(uint8 *)&BLEIOT_local);
    
    for(;;)
    {

        #ifndef BootLoadable__DISABLED
        // if they write into the BLEIOT_local.bootload (from EzI2C)
        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_BOOTLOAD || BLEIOT_local.bootload)
        {
            // enter the bootloader
            Bootloadable_Load();
        }
        #endif
       
        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_BLUE)
        {
            BLEIOT_updateBlue(BLEIOT_remote.blue);
            processBlueLed();
            updateGattDB((uint8 *)&BLEIOT_local.blue,sizeof(BLEIOT_local.blue),notifyFlags.blue,CYBLE_CY8CKIT021_BLUE_CHAR_HANDLE,CYBLE_GATT_DB_LOCALLY_INITIATED);
        }
        
        
        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_LED0)
        {
            BLEIOT_updateLed0(BLEIOT_remote.led0);
            updateGattDB(&BLEIOT_local.led0,sizeof(BLEIOT_local.led0),notifyFlags.led0,CYBLE_CY8CKIT021_LED0_CHAR_HANDLE,CYBLE_GATT_DB_LOCALLY_INITIATED);
        }
        
        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_LED1)
        {
            BLEIOT_updateLed1(BLEIOT_remote.led1);
            updateGattDB(&BLEIOT_local.led1,sizeof(BLEIOT_local.led1),notifyFlags.led1,CYBLE_CY8CKIT021_LED1_CHAR_HANDLE,CYBLE_GATT_DB_LOCALLY_INITIATED);
        }
        

        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_BUTTON0)
        {
            BLEIOT_updateButton0(BLEIOT_remote.button0);
            updateGattDB(&BLEIOT_local.button0,sizeof(BLEIOT_local.button0),notifyFlags.button0,CYBLE_CY8CKIT021_BUTTON0_CHAR_HANDLE,CYBLE_GATT_DB_LOCALLY_INITIATED);
            

        }

        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_BUTTON1)
        {
            BLEIOT_updateButton1(BLEIOT_remote.button1);
            updateGattDB(&BLEIOT_local.button1,sizeof(BLEIOT_local.button1),notifyFlags.button1,CYBLE_CY8CKIT021_BUTTON1_CHAR_HANDLE,CYBLE_GATT_DB_LOCALLY_INITIATED);
        }
  
        
        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_TRIM)
        {
            BLEIOT_updateTrim(BLEIOT_remote.trim);
            updateGattDB((uint8 *)&BLEIOT_local.trim,sizeof(BLEIOT_local.trim),notifyFlags.trim,CYBLE_CY8CKIT021_TRIM_CHAR_HANDLE,CYBLE_GATT_DB_LOCALLY_INITIATED);
        }
        
        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_CONTRAST)
        {
            BLEIOT_updateContrast(BLEIOT_remote.contrast);
            updateGattDB(&BLEIOT_local.contrast,sizeof(BLEIOT_local.contrast),notifyFlags.contrast,CYBLE_CY8CKIT021_CONTRAST_CHAR_HANDLE,CYBLE_GATT_DB_LOCALLY_INITIATED);
        }
       
        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_DISPLAY)
        {
            BLEIOT_updateDisplay(BLEIOT_remote.display);
            updateGattDB((uint8 *)&BLEIOT_local.display,sizeof(BLEIOT_local.display),notifyFlags.display,CYBLE_CY8CKIT021_DISPLAY_CHAR_HANDLE,CYBLE_GATT_DB_LOCALLY_INITIATED);
        }

        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_TONE)
        {
            BLEIOT_updateTone(BLEIOT_remote.tone);
            updateGattDB((uint8 *)&BLEIOT_local.tone,sizeof(BLEIOT_local.tone),notifyFlags.tone,CYBLE_CY8CKIT021_TONE_CHAR_HANDLE,CYBLE_GATT_DB_LOCALLY_INITIATED);
        }
   
        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_BLESTATE)
        {
            if(BLEIOT_remote.bleState == BLEIOT_BLEOFF)
            {
                CyBle_Stop();
                BLEIOT_updateBleState(BLEIOT_BLEOFF);
                processBlueLed();
            }
            if(BLEIOT_remote.bleState == BLEIOT_BLEON && BLEIOT_local.bleState == BLEIOT_BLEOFF)
            {
                CyBle_Start(BleCallBack);
                BLEIOT_updateBleState(BLEIOT_BLESTART);
            }
        }
        
        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_TEMPERATURE)
        {
            BLEIOT_updateTemperature(BLEIOT_remote.temperature);
            updateGattDB((uint8 *)&BLEIOT_local.temperature,sizeof(BLEIOT_local.temperature),notifyFlags.temperature,CYBLE_CY8CKIT021_TEMPERATURE_CHAR_HANDLE,CYBLE_GATT_DB_LOCALLY_INITIATED);

        }
        
        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_POT)
        {
            BLEIOT_updatePot(BLEIOT_remote.pot);
            updateGattDB((uint8 *)&BLEIOT_local.pot,sizeof(BLEIOT_local.pot),notifyFlags.pot,CYBLE_CY8CKIT021_POT_CHAR_HANDLE,CYBLE_GATT_DB_LOCALLY_INITIATED);
        }
        
        if(BLEIOT_local.bleState != BLEIOT_BLEOFF)
        {
            CyBle_ProcessEvents();
            CyBle_EnterLPM(CYBLE_BLESS_DEEPSLEEP);
        }
    }
}
