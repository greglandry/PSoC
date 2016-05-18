#include "project.h"

//
// This structure stores the value of the various system variables
// as known on this end of the link.
//
BLEIOT_SystemStatus BLEIOT_local;

//
// This structure stores the value of the various system variables
// as recevied from the communications link representing their state
// on the remote end of the link.
//
BLEIOT_SystemStatus BLEIOT_remote;

//
// The dirty flag is a set of bits that represents when the local state
// differs from the remote state.  If the dirty bit is set for a given
// value, that value needs to be sent to the remote end of the UART connection.
//
uint32 BLEIOT_dirtyFlags=0;

//
// The number of systick counts in the current cycle.  There is a 20 ms cycle
// in which data is processes.  At the end of this 20 ms cycle, the count is
// reset to zero and if needed the local data is sent to the remote end of
// the connection.
//
static int count;
static int BLEIOT_initVar=0;

//
// Forward declarations.
//
static void BLEIOT_TriggerSystem(void);
static void BLEIOT_Transmit();
static void BLEIOT_Receive();

//
// BLEIOT_update() -
//
// Arguments:
//    mask - the bit in the dirty flag that represents the value being updated
//    local - a pointer to the local copy of a given value
//    remote - a pointer to the remove copy of a given value
//    newVal - a new copy of the given value
//    size - the size of the value in bytes
//
// This function applies a new value to a given entry in the structure representing
// the state of the hardware.  If the new value is different than the remote value
// then the dirty flag is set indicating that the remote values need to be pushed
// to remote connection.  The local value is then updated as well and the update flag
// set to indicate that the value has been changed.
//
void BLEIOT_update(uint32 mask,void *local,void *remote,void *newVal,int size)
{
    if(!memcmp(remote,newVal,size))
    {
        BLEIOT_dirtyFlags &= ~mask;
    }
    BLEIOT_local.updatedFlags |= mask;

    memcpy(local,newVal,size);
}

//
// BLEIOT__updateBootload() -
//
// Arguments:
//    val - flag indicating that ...
//
// Function for updating the boot load state ...
//
inline void BLEIOT_updateBootload(uint8 val)
{
    BLEIOT_update(BLEIOT_FLAG_BOOTLOAD,&BLEIOT_local.bootload,&BLEIOT_remote.bootload,&val,sizeof(BLEIOT_remote.bootload));
}

inline void BLEIOT_updateBlue(BLEIOT_BlueStates val)
{
    BLEIOT_update(BLEIOT_FLAG_BLUE,&BLEIOT_local.blue,&BLEIOT_remote.blue,&val,sizeof(BLEIOT_local.blue));
}

inline void BLEIOT_updateLed0(uint8 val)
{
    BLEIOT_update(BLEIOT_FLAG_LED0,&BLEIOT_local.led0,&BLEIOT_remote.led0,&val,sizeof(BLEIOT_local.led0));
}

inline void BLEIOT_updateLed1(uint8 val)
{
    BLEIOT_update(BLEIOT_FLAG_LED1,&BLEIOT_local.led1,&BLEIOT_remote.led1,&val,sizeof(BLEIOT_local.led1));
}
inline void BLEIOT_updateButton0(uint8 val)
{
    BLEIOT_update(BLEIOT_FLAG_BUTTON0,&BLEIOT_local.button0,&BLEIOT_remote.button0,&val,sizeof(BLEIOT_remote.button0));
}

inline void BLEIOT_updateButton1(uint8 val)
{
    BLEIOT_update(BLEIOT_FLAG_BUTTON1,&BLEIOT_local.button1,&BLEIOT_remote.button1,&val,sizeof(BLEIOT_remote.button1));
}

inline void BLEIOT_updateTrim(int16 val)
{
    BLEIOT_update(BLEIOT_FLAG_TRIM,&BLEIOT_local.trim,&BLEIOT_remote.trim,&val,sizeof(BLEIOT_remote.trim));
}
inline void BLEIOT_updateContrast(uint8 val)
{
    BLEIOT_update(BLEIOT_FLAG_CONTRAST,&BLEIOT_local.contrast,&BLEIOT_remote.contrast,&val,sizeof(BLEIOT_remote.contrast));
}

inline void BLEIOT_updateDisplay(uint16 val)
{
    BLEIOT_update(BLEIOT_FLAG_DISPLAY,&BLEIOT_local.display,&BLEIOT_remote.display,&val,sizeof(BLEIOT_remote.display));
}

inline void BLEIOT_updateTone(uint16 val)
{
    BLEIOT_update(BLEIOT_FLAG_TONE,&BLEIOT_local.tone,&BLEIOT_remote.tone,&val,sizeof(BLEIOT_remote.tone));
}

inline void BLEIOT_updateBleState(BLEIOT_BleStates val)
{
    BLEIOT_update(BLEIOT_FLAG_BLESTATE,&BLEIOT_local.bleState,&BLEIOT_remote.bleState,&val,sizeof(BLEIOT_remote.bleState));
}

inline void BLEIOT_updateTemperature(int16 val)
{
    BLEIOT_update(BLEIOT_FLAG_TEMPERATURE,&BLEIOT_local.temperature,&BLEIOT_remote.temperature,&val,sizeof(BLEIOT_remote.temperature));
}

inline void BLEIOT_updatePot(int16 val)
{
    BLEIOT_update(BLEIOT_FLAG_POT,&BLEIOT_local.pot,&BLEIOT_remote.pot,&val,sizeof(BLEIOT_remote.pot));
}

//
// BLEIOT_TriggerSystem() -
//
// This function is called from the SysTick callback.  The systick is generally
// configured to interrupt to CPU once every millisecond.  This function assumes
// that it is called each millisecond.
//
void BLEIOT_TriggerSystem()
{
    //
    // If there is enough data in the uart buffer to be a complete system status
    // read and process this data from the remote connection.  Note this can happen
    // at any time in the 20 ms cycle.  We have data, we reset the count to ensure
    // that we wait another 10 ms before we transmit any data.
    //
    if(BLEIOT_UART_SpiUartGetRxBufferSize() == sizeof(BLEIOT_SystemStatus))
    {
        BLEIOT_Receive();
        
        //
        // When we receive data, we reset the count to ensure that we follow
        // the receive operation with a transmit operation in 10 ms.
        //
        count = 10;
     }

    //
    // Every 20 ms perform the transmit operation
    //
    if(count++ > 20)
    {
        BLEIOT_Transmit();
        count = 0;
    }    
}

//
// BLEIOT_Start() -
//
// Called to start the component.  Initializes the component variables, starts the UART, starts the
// systick timer, and sets up a callback to process systick interrupts.
//
void BLEIOT_Start()
{
    int i;
    BLEIOT_UART_Start();
    
    //
    // The SysTick is a shared resource, you probably should not start it here.  You should probaby
    // make clear in the documentation that this component relies on the shared systick capability to
    // be started and have at least a single callback slot available.
    //
    CySysTickStart();
    
    //
    // Initialize the count that is incremented in each systick callback.  This is used to time when
    // specific operations are performed in the systick interrupt.
    //
    count = 0;
    
    //
    // I would probably pass in the systick slot.  Doing this automatically works and may seem more user
    // friendly, but there are five slots and if the user is using more than one, they can layout out at
    // the top level of their application which systick slot is allocated to which function.  Even if you
    // are doing this automatically, I would use the cylib defined constant.
    //
    for(i=CY_SYS_SYST_NUM_OF_CALLBACKS ; i>-1 ; i--)
    {
        if( CySysTickGetCallback(i) == NULL)
        {
            CySysTickSetCallback(i,&BLEIOT_TriggerSystem);
            BLEIOT_initVar = 0;
        }
    }
    //
    // Did not find a slot, can we not have the start function return
    // a true/false status.  I hate it when code presumes I cannot process an initilaization
    // failure.  If the initialization fails, I might want to go into a loop and blink a GPIO 
    // to light and LED to indiate some kind of status information.
    //
    if(BLEIOT_initVar == 0) // this can only happen if all of the systick vectors are taken
            CYASSERT(1);

    BLEIOT_local.blue = BLEIOT_BLECONTROL;
    BLEIOT_remote.blue = BLEIOT_BLECONTROL;
    BLEIOT_local.bleState = BLEIOT_BLEOFF;
    BLEIOT_remote.bleState = BLEIOT_BLEOFF;
}

//
// BLEIOT_Transmit() -
//
// If the UART TX buffer is empty, and the local data has been updated with respect
// to the remote data, send the local data to the remote end.
//
void BLEIOT_Transmit()
{
    //
    // If nothing has been updated in the local structure, or if we are still
    // transmitting existing data, just return.  We will check again in another
    // 20 ms
    //
    if(!BLEIOT_local.updatedFlags || BLEIOT_UART_SpiUartGetTxBufferSize())
        return;

    //
    // Send the local data structure to the remote end. We do this because we have 
    // locally changed the data and want to let the remote end know.
    //
    BLEIOT_UART_SpiUartPutArray((uint8 *)&BLEIOT_local,sizeof(BLEIOT_SystemStatus));
    
    //
    // Ok, the data is sent, (well its in the buffer), so mark the local data in sync
    // with the remote data.
    //
    BLEIOT_local.updatedFlags = 0;
    
    //
    // ???
    //
    BLEIOT_local.bootload=0; 
}

//
// BLEIOT_updateDirtyFlags() -
//
// Arguments:
//   local - pointer to local data value
//   remote - pointer to remote data value
//   mask - the bit in the updated flags that represents the given value
//   size - the size of the value in bytes
//
// This method looks at data received in the remote data structure and
// determines if it is different than in the local data structure.  If the data
// is different, the dirty flag is set and the data is marked to be sent to the
// remote connection.

//
void BLEIOT_updateDirtyFlags(void *local,void *remote,uint32 mask,int size)
{
    if(BLEIOT_remote.updatedFlags & mask)
    {
        if(memcmp(local,remote,size))
            BLEIOT_dirtyFlags |= mask;
        else
            BLEIOT_dirtyFlags &= ~mask;
    }
}

void BLEIOT_Receive()
{
    uint32 i;
    uint8 *buff;
    buff = (uint8 *)&BLEIOT_remote;

    //
    // Copy the data from the UART recieve data into the remote data structure.  This
    // data structure now represents the state at the remote end of the connection.
    //
    for(i=0;i<sizeof(BLEIOT_SystemStatus);i++)
    {
        *buff++ = BLEIOT_UART_SpiUartReadRxData();
    }
    
    //
    // Now, for each value in the struture, check to see if it is different.  If it is different
    // set the dirty flag for that entry.  if it is the same clear the dirty flag.
    //
    BLEIOT_updateDirtyFlags(&BLEIOT_local.bootload,&BLEIOT_remote.bootload,BLEIOT_FLAG_BOOTLOAD,sizeof(BLEIOT_remote.bootload));  
    BLEIOT_updateDirtyFlags(&BLEIOT_local.blue,&BLEIOT_remote.blue,BLEIOT_FLAG_BLUE,sizeof(BLEIOT_remote.blue));
    BLEIOT_updateDirtyFlags(&BLEIOT_local.led0,&BLEIOT_remote.led0,BLEIOT_FLAG_LED0,sizeof(BLEIOT_remote.led0));
    BLEIOT_updateDirtyFlags(&BLEIOT_local.led1,&BLEIOT_remote.led1,BLEIOT_FLAG_LED1,sizeof(BLEIOT_remote.led1));
    BLEIOT_updateDirtyFlags(&BLEIOT_local.button0,&BLEIOT_remote.button0,BLEIOT_FLAG_BUTTON0,sizeof(BLEIOT_remote.button0));
    BLEIOT_updateDirtyFlags(&BLEIOT_local.button1,&BLEIOT_remote.button1,BLEIOT_FLAG_BUTTON1,sizeof(BLEIOT_remote.button1));
    BLEIOT_updateDirtyFlags(&BLEIOT_local.trim,&BLEIOT_remote.trim,BLEIOT_FLAG_TRIM,sizeof(BLEIOT_remote.trim));
    BLEIOT_updateDirtyFlags(&BLEIOT_local.contrast,&BLEIOT_remote.contrast,BLEIOT_FLAG_CONTRAST,sizeof(BLEIOT_remote.contrast));
    BLEIOT_updateDirtyFlags(&BLEIOT_local.display,&BLEIOT_remote.display,BLEIOT_FLAG_DISPLAY,sizeof(BLEIOT_remote.display));
    BLEIOT_updateDirtyFlags(&BLEIOT_local.tone,&BLEIOT_remote.tone,BLEIOT_FLAG_TONE,sizeof(BLEIOT_remote.tone));
    BLEIOT_updateDirtyFlags(&BLEIOT_local.bleState,&BLEIOT_remote.bleState,BLEIOT_FLAG_BLESTATE,sizeof(BLEIOT_remote.bleState));
    BLEIOT_updateDirtyFlags(&BLEIOT_local.temperature,&BLEIOT_remote.temperature,BLEIOT_FLAG_TEMPERATURE,sizeof(BLEIOT_remote.temperature));
    BLEIOT_updateDirtyFlags(&BLEIOT_local.pot,&BLEIOT_remote.pot,BLEIOT_FLAG_POT,sizeof(BLEIOT_remote.pot));
}