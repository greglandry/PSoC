/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>

#define SELECTED        0
#define MAX_WAIT_TIME   100
int main()
{
    uint16 waitTime = 0;
    
    CyGlobalIntEnable;
    PWM_LED_Init();
    
    if(Pin_BL_Select_Read() == SELECTED)
    {
        for(waitTime = 0; waitTime < MAX_WAIT_TIME; waitTime++)
        {
            CyDelay(1);
            if(Pin_BL_Select_Read() != SELECTED)
            {
                break;
            }
        }
        
        if(waitTime == MAX_WAIT_TIME)
        {
            Bootloader_SET_RUN_TYPE (Bootloader_START_BTLDR);
			
			/*Indicate that you have entered the bootloader mode.*/
			PWM_LED_WritePeriod(30000);
			PWM_LED_WriteCompare(15000);
        }
    }
    else
	{
		/* If the application is not valid, the CPU will halt, since application
         * validation is enabled. Blink the LED very fast (ON Time = 0.25s, OFF Time = 0.25s)*/
		PWM_LED_WritePeriod(5000);
		PWM_LED_WriteCompare(2500);
	}
       
    /* Enable the PWM */
	PWM_LED_Enable();
    
    CyBtldr_Start();
    
    for(;;)
    {

    }
}

/* [] END OF FILE */
