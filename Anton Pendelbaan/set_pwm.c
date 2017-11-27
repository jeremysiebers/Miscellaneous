#include "Main.h"
#include "io.h"
#include <xc.h>
#include "api.h"

/******************************************************************************
 * Function:        void SETxPWM(unsigned int value, unsigned char direction)
 *                  Calculates speed to PWM value depending on direction
 *
 * PreCondition:    None
 *
 * Input:           Speed value and direction (left or right)
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *****************************************************************************/
void SETxPWM(unsigned int speed, unsigned char direction){
    
    unsigned int pwm_speed = 511;
    
	if (GETxAPIxVAL(PWM_DIRECTION) != direction){
		SETxAPIxVAL(PWM_DIRECTION, direction);
	}
	
    if (direction == Left){
        pwm_speed = 511 - (speed * 2);		
        SETxAPIxVAL(HW_PWM_SPEED, pwm_speed);
    }
    else if (direction == Right){
        pwm_speed = 511 + (speed * 2);
		SETxAPIxVAL(HW_PWM_SPEED, pwm_speed);
    }
}
