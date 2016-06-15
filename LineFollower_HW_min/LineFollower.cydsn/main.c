/* ========================================
 *
 * Copyright Cypress Semiconductor, 2014
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF Cypress Semiconductor.
 *
 * ========================================
*/
#include <project.h>

int main()
{	
	Timer_Start();
	PWM_IR_Start();
	PWM_MOT_Start();
		
	CyPmAltAct(PM_ALT_ACT_TIME_NONE,PM_ALT_ACT_SRC_NONE);
	
	/* The firmware never gets to here due to the CyPmAltAct call */
	for(;;)
    {
	}
}
	/* [] END OF FILE */
