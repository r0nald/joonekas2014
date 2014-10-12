#include "joonekas.h"

#include "Comm.h"
#include "pwm_out.h"
#include "adc.h"
#include "dma_uart.h"
#include "controller1.h"
#include "line_sens.h"

#include "stm32f4xx_gpio.h"

static uint32_t time = 0;

static int32_t 	btnUpTimer 	= -1;
static uint8_t 	btnDown 		= 0;
static uint8_t 	sDelay 			= 0;
static uint8_t 	store 			= 0;
static uint32_t Address 		= 0;

static uint8_t 	manLeft 		= 0;
static uint8_t 	manRight 		= 0;
static uint8_t 	manKill 		= 0;


#define startTime 50



uint8_t ADCTreshold;

OutputMsg_t     OutputMsg;
InputMsg_t 			InputMsg;

__IO uint32_t FlashData32 = 0;



int writeFlash(void);



void Joonekas_SysTick(void)
{



	
	LineSenseOut		lineSense;
	Controller1Out 	controllerOut;
	
	

	
	if(sDelay == 0) {
		OutputMsg.OutPacket.CMD_STAT &= ~SetParam; // clear parameters flags
	}
	
	
	/**
		* START BUTTON
		*/
	if(!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2)) {
		if(btnDown) {
			btnUpTimer = 0;
		}
		else if(btnUpTimer > 0 // Falling edge has been detected
			&& btnUpTimer == startTime) {
				
			InputMsg.InPacket.rcvCMD |= Run; // Set RUN bit to 1
			time = 0; // Reset runtime
			Controller1_Reset();
			Driver_Enable(1, 1);
			manKill = 0;
			btnUpTimer = -1;
		}
		else if(btnUpTimer >= 0) {
			btnUpTimer++;
		}
	}
	btnDown = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2);
	/**
		*/

		
	/**
		* Good reflection gives ADC value ~16, bad reflection 40-60.
		*/
	OutputMsg.OutPacket.lineSensors = ADC_GetLineSensing(ADCTreshold);
	
	lineSense = LS_Feedback(OutputMsg.OutPacket.lineSensors);
	OutputMsg.OutPacket.pidFeedback = lineSense.feedback;
	OutputMsg.OutPacket.usedSensors = lineSense.usedLinePatt;

	
// New message received	
	if(Comm_NewMsg()) {
		
	// UI asks setting parameters 
		if(InputMsg.InPacket.rcvCMD & GetParam) {
			OutputMsg.OutPacket.CMD_STAT |= SetParam; // Set get parameters flag
		}	
	// UI sent new setting parameters 		
		else if(InputMsg.InPacket.rcvCMD & SetParam) {
			OutputMsg.OutPacket.CMD_STAT |= SetParam; // Set set parameters flag
				
			ADCTreshold = InputMsg.InPacket.SetADCTresh;
			controllerObj.settings.maxPWM = InputMsg.InPacket.SetPWMLim;
			controllerObj.settings.maxISUM = InputMsg.InPacket.SetISumLim;  
			controllerObj.settings.P = InputMsg.InPacket.SetP;  
			controllerObj.settings.I = InputMsg.InPacket.SetI;  
			controllerObj.settings.D = InputMsg.InPacket.SetD; 
			controllerObj.settings.basePwm = InputMsg.InPacket.SetBasePWM; 
			store = 1; // set store flag
		}			
	// Running	
		else if(InputMsg.InPacket.rcvCMD & Run) { // &0x01, If RUN bit is set
			time = 0;	// Reset runtime
			Controller1_Reset();
			Driver_Enable(1, 1);
			manKill = 0; 
		} 
	// Stopped or manual drive
		else { 
		// Manual Drive
			if(InputMsg.InPacket.rcvCMD & ManDrive) {
				
				PWM_Set(0.12, 0.12);
				if(InputMsg.InPacket.rcvCMD & ManLeft) {
					manLeft = 1;
				}
				else {
					manLeft = 0;
				}
				
				if(InputMsg.InPacket.rcvCMD & ManRight) {
					manRight = 1;
				}
				else{
					manRight = 0;
				}
					
				manKill = 10; // set drive time 50ms
				
				Driver_Enable(manLeft, manRight);
				
				
			}
		// Stopped
			else {
			
				Driver_Enable(0, 0);
				PWM_Set(0, 0);
				Controller1_Reset();
			}
		}
	}
	

// K2RP running ?	
	if(InputMsg.InPacket.rcvCMD & Run) // &0x01, If RUN bit is set
	{
		// PID calc
			controllerOut = Controller1_Run(OutputMsg.OutPacket.pidFeedback);
			
		// set parameters to outmessage struct
			OutputMsg.OutPacket.pwmLeft = controllerOut.pwmLeft; 
			OutputMsg.OutPacket.pwmRight = controllerOut.pwmRight;
			OutputMsg.OutPacket.pidK = controllerOut.uk; 
			OutputMsg.OutPacket.pidI = controllerOut.ui; 
			OutputMsg.OutPacket.pidD = controllerOut.ud;
			OutputMsg.OutPacket.pidU = controllerOut.u;
		
		// Set New PWM values
			PWM_Set(OutputMsg.OutPacket.pwmLeft, OutputMsg.OutPacket.pwmRight);
		  
			OutputMsg.OutPacket.time = time;
		// Increment time only when K2RP is running
			time++;	
			
			OutputMsg.OutPacket.CMD_STAT |= Run;
	}
	else {
		OutputMsg.OutPacket.CMD_STAT &= ~Run;
	
		if(manKill > 0) {
			manKill--;
			if(manKill == 0) { // disable drivers when delay is over
				Driver_Enable(0, 0);
			}
		}
		
	// We need to store new values to flash 
		else if(store) {
			if(writeFlash()) {
				GPIOA->BSRRL = GPIO_Pin_8; // RED LED LD4 ON
			}
			GPIOA->BSRRH = GPIO_Pin_10; // GREEN LED LD5 OFF
			store = 0; // clear flag		
		} 	
	}
	
	
// set parameters to outmessage struct
	if(OutputMsg.OutPacket.CMD_STAT & SetParam) {
		OutputMsg.OutPacket.adc1 = ADCTreshold;
		
		OutputMsg.OutPacket.pwmLeft = controllerObj.settings.maxPWM; 
		OutputMsg.OutPacket.pwmRight = controllerObj.settings.maxISUM;
		OutputMsg.OutPacket.pidK = controllerObj.settings.P; 
		OutputMsg.OutPacket.pidI = controllerObj.settings.I; 
		OutputMsg.OutPacket.pidD = controllerObj.settings.D;
		OutputMsg.OutPacket.pidU = controllerObj.settings.basePwm;
	}
	else{
		OutputMsg.OutPacket.adc1 = ADC_GetAdcReading(0);
	}
	OutputMsg.OutPacket.adc2 = ADC_GetAdcReading(1);
	OutputMsg.OutPacket.adc3 = ADC_GetAdcReading(2);
	OutputMsg.OutPacket.adc4 = ADC_GetAdcReading(3);
	OutputMsg.OutPacket.adc5 = ADC_GetAdcReading(4);
	OutputMsg.OutPacket.adc6 = ADC_GetAdcReading(5);
	OutputMsg.OutPacket.adc7 = ADC_GetAdcReading(6);
	OutputMsg.OutPacket.adc8 = ADC_GetAdcReading(7);
	OutputMsg.OutPacket.adc9 = ADC_GetAdcReading(8);
	OutputMsg.OutPacket.adc10 = ADC_GetAdcReading(9);
	OutputMsg.OutPacket.battVoltage = ADC_GetAdcReading(10);

// Start  outPacket TX
	if(sDelay > 3) {			// Slow down packet rate to 25Hz to avoid xbee buf overflow
		DmaUart_StartTx();
		sDelay = 0;
	}
	else {
		sDelay++;
	}

}


// Write Flash Function ****************************************************** //
int writeFlash(void) {
	

	GPIOA->BSRRL = GPIO_Pin_10; // GREEN LED LD5 ON
	// flash operation
		FLASH_Unlock(); // Unlock flash memory
	// clear flags
		FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
										FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR); 
			
		if (FLASH_EraseSector(FLASH_Sector_3, VoltageRange_3) != FLASH_COMPLETE) { 
			return 1;
		}
		Address = ADDR_FLASH_SECTOR_3; // set flash address
			
	// Store ADC treshold
		if (FLASH_ProgramWord(Address, ADCTreshold) == FLASH_COMPLETE) {
      Address += 4; // increment by 4
    }
    else { return 2; }
		
	// Store MAX PWM
		if (FLASH_ProgramWord(Address, *((const uint32_t*)(&controllerObj.settings.maxPWM))) == FLASH_COMPLETE) {
      Address += 4; // increment by 4
    }
    else { return 2; }

	// Store MAX I SUM
		if (FLASH_ProgramWord(Address, *((const uint32_t*)(&controllerObj.settings.maxISUM))) == FLASH_COMPLETE) {
      Address += 4; // increment by 4
    } else { return 2; }

	// Store P
		if (FLASH_ProgramWord(Address, *((const uint32_t*)(&controllerObj.settings.P))) == FLASH_COMPLETE) {
      Address += 4; // increment by 4
    } else { return 2; }

	// Store I
		if (FLASH_ProgramWord(Address, *((const uint32_t*)(&controllerObj.settings.I))) == FLASH_COMPLETE) {
      Address += 4; // increment by 4
    } else { return 2; }

	// Store D
		if (FLASH_ProgramWord(Address, *((const uint32_t*)(&controllerObj.settings.D))) == FLASH_COMPLETE) {
      Address += 4; // increment by 4
    } else { return 2; }

	// Store Base PWM
		if (FLASH_ProgramWord(Address, *((const uint32_t*)(&controllerObj.settings.basePwm))) == FLASH_COMPLETE) {
      Address += 4; // increment by 4
    } else { return 2; }		
	
		FLASH_Lock(); // lock flash memory
		
		return 0; // return success
}

