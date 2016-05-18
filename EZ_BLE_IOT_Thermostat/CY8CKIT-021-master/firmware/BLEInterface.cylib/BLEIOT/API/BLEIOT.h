#ifndef BLEIOT_H
#define BLEIOT_H
#include "cytypes.h"

typedef enum BLEIOT_BlueStates {
    BLEIOT_OFF=0,
    BLEIOT_ON=1,
    BLEIOT_BLINK=2,
    BLEIOT_BLECONTROL=3
} BLEIOT_BlueStates;

typedef enum BLEIOT_BleStates {
    BLEIOT_BLEOFF,
    BLEIOT_BLEON,
    BLEIOT_BLESTART,
    BLEIOT_BLEADVERTISING,
    BLEIOT_BLECONNECTED
} BLEIOT_BleStates;

void BLEIOT_Start();
uint32 BLEIOT_getDirtyFlags();



void BLEIOT_updateBootload(uint8);
void BLEIOT_updateBlue(BLEIOT_BlueStates);
void BLEIOT_updateLed0(uint8);
void BLEIOT_updateLed1(uint8);
void BLEIOT_updateButton0(uint8);
void BLEIOT_updateButton1(uint8);
void BLEIOT_updateTrim(int16);
void BLEIOT_updateContrast(uint8);
void BLEIOT_updateDisplay(uint16);
void BLEIOT_updateTone(uint16);
void BLEIOT_updateBleState(BLEIOT_BleStates);
void BLEIOT_updateTemperature(int16);
void BLEIOT_updatePot(int16);


#define BLEIOT_FLAG_BOOTLOAD (1<<0)
#define BLEIOT_FLAG_BLUE (1<<1)
#define BLEIOT_FLAG_LED0 (1<<2)
#define BLEIOT_FLAG_LED1 (1<<3)
#define BLEIOT_FLAG_BUTTON0 (1<<4)
#define BLEIOT_FLAG_BUTTON1 (1<<5)
#define BLEIOT_FLAG_TRIM (1<<6)
#define BLEIOT_FLAG_CONTRAST (1<<7)
#define BLEIOT_FLAG_DISPLAY (1<<8)
#define BLEIOT_FLAG_TONE (1<<9)
#define BLEIOT_FLAG_BLESTATE (1<<10)
#define BLEIOT_FLAG_TEMPERATURE (1<<11)
#define BLEIOT_FLAG_POT (1<<12)


typedef struct BLEIOT_SystemStatus {
    uint8 bootload;
    uint32 updatedFlags;
    BLEIOT_BlueStates blue;
    uint8 led0;
    uint8 led1;
    uint8 button0;
    uint8 button1;
    int16 trim;
    uint8 contrast;
    uint16 display;
    uint16 tone;
    BLEIOT_BleStates bleState;
    int16 temperature;
    int16 pot;
} __attribute__((packed)) BLEIOT_SystemStatus;

extern BLEIOT_SystemStatus BLEIOT_local;
extern BLEIOT_SystemStatus BLEIOT_remote;
extern uint32 BLEIOT_dirtyFlags;
#define BLEIOT_getDirtyFlags() (BLEIOT_dirtyFlags)


#endif