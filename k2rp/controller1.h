


#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) /* Base @ of Sector 3, 16 Kbytes */





typedef struct
{
	float basePwm; 					// This is PWM for both motors when going straight. In turns, will subtract from this.
	float P, I, D;
	float maxISUM;					// I sum limit
	float maxPWM;						// PWM limit
} Controller1Settings;


typedef struct
{
	Controller1Settings settings;
	
	float iSum;
	float prevErr;
} Controller1;

extern Controller1 controllerObj;


typedef struct
{
	float uk, ui, ud;
	float u;
	float pwmLeft, pwmRight;
} Controller1Out;


void 						Controller1_Reset(void);
Controller1Out 	Controller1_Run(float fb);
void 						Controller1_Init(void);
