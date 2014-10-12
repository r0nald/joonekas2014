#include "controller1.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
	
Controller1 controllerObj;

extern uint8_t ADCTreshold;

static uint8_t leftZero = 0;
static uint8_t rightZero = 0;


Controller1Out Controller1_Run(float fb)
{
	Controller1Out out;
	
	out.uk 	= fb * controllerObj.settings.P;
	controllerObj.iSum += controllerObj.settings.I * fb; 
	
	if(fb > 2) {
		leftZero = 1;
	}
	else if (fb <= 0) {
		leftZero = 0;
	}
	
	if(fb < -2) {
		rightZero = 1;
	}
	else if (fb >= 0) {
		rightZero = 0;
			
	}
	

// Limit Isum
	if(controllerObj.iSum > controllerObj.settings.maxISUM) {
		controllerObj.iSum = controllerObj.settings.maxISUM;
	}
	if(controllerObj.iSum < (-controllerObj.settings.maxISUM) ) {
		controllerObj.iSum = -controllerObj.settings.maxISUM;
	}
	
	out.ui = controllerObj.iSum;
	out.ud 	= (fb - controllerObj.prevErr) * controllerObj.settings.D;
	controllerObj.prevErr = fb;
	
	out.u 	= out.uk + out.ui + out.ud;
	
// Limit max Left PWM
	out.pwmLeft = controllerObj.settings.basePwm - out.u;
	if(out.pwmLeft > controllerObj.settings.maxPWM) {
		out.pwmLeft = controllerObj.settings.maxPWM;
	}
	if(leftZero == 1) {
		out.pwmLeft = 0;
	}
	
// Limit max Right PWM
	out.pwmRight = controllerObj.settings.basePwm + out.u;
	if(out.pwmRight > controllerObj.settings.maxPWM) {
		out.pwmRight = controllerObj.settings.maxPWM;
	}
	if(rightZero == 1) {
		out.pwmRight = 0;
	}
	
	return out;	
}

void Controller1_Reset(void)
{
	controllerObj.iSum 		= 0;	
	controllerObj.prevErr = 0;
}

void 	Controller1_Init(void)
{
	
	uint32_t Addr = ADDR_FLASH_SECTOR_3;
	uint32_t FlashData32 = *(volatile uint32_t*)Addr;
	
	
// Check if memory is empty	
	if( (FlashData32 == 0) || (FlashData32 == 0xFFFFFFFF) ) {
	// For 3C LiPo
		controllerObj.settings.basePwm = 0.2;
		controllerObj.settings.P = 0.09;
		controllerObj.settings.I = 0.001;
		controllerObj.settings.D = 0.55;
		controllerObj.settings.maxISUM = 0.15;
		controllerObj.settings.maxPWM = 0.48;
		ADCTreshold = 30;
		
		
// For 2C LiPo
	//controllerObj.settings.basePwm = 0.4;
	//controllerObj.settings.P = 0.07;
	//controllerObj.settings.I = 0.00005;
	//controllerObj.settings.D = 0.7;
	}
	else {
		  GPIOA->BSRRL = GPIO_Pin_9; // GREEN LED LD6 ON
		
			ADCTreshold = (uint8_t)FlashData32;
			Addr += 4; // increment by 4
		  controllerObj.settings.maxPWM = (*(volatile float*)Addr);
			Addr += 4; // increment by 4
		  controllerObj.settings.maxISUM = (*(volatile float*)Addr);
			Addr += 4; // increment by 4
		  controllerObj.settings.P = (*(volatile float*)Addr);
			Addr += 4; // increment by 4
		  controllerObj.settings.I = (*(volatile float*)Addr);
			Addr += 4; // increment by 4
		  controllerObj.settings.D = (*(volatile float*)Addr);
			Addr += 4; // increment by 4
		  controllerObj.settings.basePwm = (*(volatile float*)Addr);
		
	}
}


