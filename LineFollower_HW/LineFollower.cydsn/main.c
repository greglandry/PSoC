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
	PWM_MOT1_Start();
	PWM_MOT2_Start();
	PWM_MOT3_Start();
	Comp1_Start();
	Comp2_Start();
	Comp3_Start();
	VDAC1_Start();
	VDAC2_Start();
	VDAC3_Start();
		
	CyPmAltAct(PM_ALT_ACT_TIME_NONE,PM_ALT_ACT_SRC_NONE);
	
	/* The firmware never gets to here due to the CyPmAltAct call */
	for(;;)
    {
	}
}
	/* [] END OF FILE */
