#include <stdint.h>



#define Stop 			0x00
#define Run 			0x01
#define GetParam 	0x02
#define SetParam 	0x04
#define ManDrive	0x08
#define ManLeft	  0x10
#define ManRight	0x20

// Input Packet struct
typedef union {
			volatile uint8_t RxBytes[1];
			struct {
				//uint16_t 	StartSTR;						// "K2"	// No need to store it 
				float			SetBasePWM;						// Base PWM value
				float			SetP; 								// P VAL: error * P
				float			SetI;									// I VAL: SUM (error * I)
				float			SetD;									// D VAL: (error - last error) * D
				float			SetISumLim;						// PID OUT: (P + I + D) limited with MAX PID value
				float			SetPWMLim;						// BASE PWM - PID OUT
			  uint8_t		rcvCMD;								// Command Byte
				uint8_t		SetADCTresh;					// ADCTreshold
				uint16_t	EndByte;							// 0x0D0A
			} InPacket;  
}	InputMsg_t;

extern InputMsg_t InputMsg;


// Output Packet struct
typedef union {
			volatile uint8_t TxBytes[1];
			struct {
				uint16_t 	StartSTR;							// "K2"	
				uint8_t		adc1;									// Most right linesensor value
				uint8_t		adc2;
				uint8_t		adc3;
				uint8_t		adc4;
				uint8_t		adc5;									// Center Right linesensor value
				uint8_t		adc6;									// Center Left linesensor value
				uint8_t		adc7;
				uint8_t		adc8;
				uint8_t		adc9;
				uint8_t		adc10;								// Most left linesensor value		
				uint16_t	lineSensors;	
				uint16_t	usedSensors;	
				
				float			pidFeedback;					// PID error
				float			pidK; 								// P VAL: error * P
				float			pidI;									// I VAL: SUM (error * I)
				float			pidD;									// D VAL: (error - last error) * D
				float			pidU;									// PID OUT: (P + I + D) limited with MAX PID value
				float			pwmLeft;							// BASE PWM - PID OUT
				float			pwmRight;							// BASE PWM + PID OUT
				uint32_t 	time;									// runtime
				uint8_t		CMD_STAT;							// Command Echo & status bits
				uint8_t	  battVoltage;					// Battery voltage
				uint16_t	EndByte;							// 0x0D0A
			} OutPacket;  
}	OutputMsg_t;

extern OutputMsg_t OutputMsg;





/*
 * Call this to initialize internal states of Comm
 */
void Comm_Init(void);

/*
 * This function should be called if data is received from serial port
 */
void Comm_Process(uint8_t InByte);

/*
 * This command will return non-zero, if a new command has been received.
 * Returns non-zero only once.
 */
uint8_t Comm_NewMsg(void);






