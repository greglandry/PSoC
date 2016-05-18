#include <project.h>

# define TRUE (1)
# define FALSE (0)
# define POT_CHAN (0)   // This tells your ADC to use channel zero
# define POS (0)        // Makes your LCD data appear on the right
# define MODE (1)       // Print leading zeros
# define LED_ON (0)     // Used to turn on active low LED
# define LED_OFF (1)    // Used to turn off active low LED
# define UP     (1)     // Used for set temperature increase
# define DOWN   (2)     // Used for set temperature decrease
/* Bootload BLE module if button is held down */
CY_ISR(StartBootload_ISR)
{
    BLEIOT_updateBootload(1);
    ResetTimer_ClearInterrupt(ResetTimer_INTR_MASK_TC);
    sendBootload_ClearPending();
}

int main()
{
    
    CyDelay(200);

    uint16 Counts=0;            // ADC value (0 to 4095) right shifted by 6 which gives
                                // us 0 to 63 to be used to simulate actual temperature
    uint16 TempSet = 2400;      // Temperature set default value (left justified) 24 deg
    uint16 DisplayTemp = 0;     // The combined sum of desired temp and actual temp
    
    uint16 bleTemp = 0;         // Temperature sent to BLE module
    uint16 bleTempSet = 0;      // Temperature set value sent to BLE module
    
    uint8 button0 = 0;      // Declare CapSense button name button0
    uint8 button1 = 0;      // Declare CapSense button name button1
    uint8 firstpress0 = 0;  // Detects a transition of button1 from 0 to 1
    uint8 firstpress1 = 0;  // Detects a transition of button1 from 0 to 1
    
    int buttonPrevious = 1;

    CyGlobalIntEnable;
    
    ADC_Start();        // Starts the ADC component
    ADC_StartConvert(); // The ADC conversion process begins
    LCD_Start();        // Start the LCD component 
    
    CapSense_Start();
    CapSense_ScanAllWidgets();
    
    LCD_WritePixel(LCD_COLON, TRUE);
       
    ResetTimer_Start();
    sendBootload_StartEx(StartBootload_ISR);
    
    BLEIOT_Start();
    
    /* Initialize temperuature values out of range so that main loop update is triggered */
    BLEIOT_updateTemperature(10000);
    BLEIOT_updatePot(100);    
       
    for(;;)
    {
        
        /* Turn BLE on/off with button press */
        if(buttonPrevious && (Button_Read() == 0))
        {          
            if(BLEIOT_remote.bleState == BLEIOT_BLEOFF)
            {
                BLEIOT_updateBleState(BLEIOT_BLEON);  
            }
            else
            {
                BLEIOT_updateBleState(BLEIOT_BLEOFF);
            }
            
        }
        buttonPrevious = Button_Read();
           
        /* Local Thermostat Operation */
        /* ADC */
        // Read the ADC, shift right by 6 (i.e. divide by 64)
        // and store result in Counts
        Counts = ADC_GetResult16(POT_CHAN);
        Counts = Counts >> 6;

        /* CapSense */
        if (!CapSense_IsBusy())
        {
            // Check Button states and store
            CapSense_ProcessAllWidgets();
            if(CapSense_IsWidgetActive(CapSense_BUTTON0_WDGT_ID))
            {
                button0 = 1;
            }
            else
            {
                button0 = 0;
            }
            if(CapSense_IsWidgetActive(CapSense_BUTTON1_WDGT_ID))
            {
                button1 = 1;
            }
            else
            {
                button1 = 0;
            }
            
            // Light LEDs Based on Capsense buttons
            LED_CS0_Write(~button0);
            LED_CS1_Write(~button1);
            
            // Check for button touchdown transitions
            if (button0 == 1)
            {
                if(firstpress0 == 0) // Touchdown event
                {
                    firstpress0 = 1; // Remember button0 was pressed
                    TempSet = TempSet + 100; // Increment Temp by 1 deg
                }
            }
            else
            {
                firstpress0 = 0; // Button released
            }
            if (button1 == 1)
            {
                if(firstpress1 == 0) // Touchdown event
                {
                    firstpress1 = 1; // Remember button0 was pressed                   
                    TempSet = TempSet - 100; // Decrement Temp by 1 deg
                }
            }
            else
            {
                firstpress1 = 0; // Button released
            }
                 
            CapSense_ScanAllWidgets();  // Start Next Scan
        }
     
        /* Warning LEDs and Buzzer */
        if((Counts * 100) < TempSet)    // Temperature Cold
        {
            LED_Blue_Write(LED_ON);     // Blue On
            LED_Green_Write(LED_OFF);   // Green Off
            LED_Red_Write(LED_OFF);     // Red Off
            PWM_Stop(); // Buzzer Off
        }
        else if ((Counts * 100) <= (TempSet + 500))  // Temperature OK
        {
            LED_Blue_Write(LED_OFF);    // Blue Off
            LED_Green_Write(LED_ON);    // Green On
            LED_Red_Write(LED_OFF);     // Red Off
            PWM_Stop();// Buzzer Off
        }
        else // Tempearture too high
        {
            LED_Blue_Write(LED_OFF);    // Blue Off
            LED_Green_Write(LED_OFF);   // Green Off
            LED_Red_Write(LED_ON);      // Red On
            PWM_Start(); // Buzzer On
        }
    
        /* LCD Display */
        DisplayTemp = TempSet + Counts;
        LCD_Write7SegNumber_0(DisplayTemp, POS, MODE);        
    
        
        /* BLE operation - do only if BLE is not off */    
        if(BLEIOT_remote.bleState != BLEIOT_BLEOFF)
        {
            /* Send new temperature data to the BLE module */
            if(bleTemp != Counts)
            {
                bleTemp = Counts;
                BLEIOT_updatePot(bleTemp);
            }
            if(bleTempSet != TempSet)
            {
                bleTempSet = TempSet;
                /* Scale set temperature down to whole number of  degrees */
                BLEIOT_updateTemperature(TempSet / 100); 
            }     
                       
            /* Get new data from the BLE module */
            /* LED0 is used for temperature changes */
            if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_LED0)
            {
                /* Update local variable copy and clear dirty flag */
                BLEIOT_updateLed0(BLEIOT_remote.led0); 
                if(BLEIOT_local.led0 == UP)
                {
                    TempSet = TempSet + 100; // Increment Temp by 1 deg
                }
                else if (BLEIOT_local.led0 == DOWN)
                {
                    TempSet = TempSet - 100; // Decrement Temp by 1 deg
                }
            }
        } /* End of !BLEOFF state operations */
    } /* End of superloop */
} /* End of main */
