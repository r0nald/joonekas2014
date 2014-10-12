/**
  ******************************************************************************
  * @file    logic.c
  * @author  TUT Robotics Club NPO
  * @version V1.0
  * @date    18-August-2013
  * @brief   This file contains Buttons control functions.
  ******************************************************************************  
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include <stdio.h>
#include <stdlib.h>
#include "typedefs.h"
#include "power.h"
#include "led.h"
#include "ledcfg.h"
#include "button.h"
#include "speaker.h"
#include "xbee.h"
#include "xbeecfg.h"
#include "math.h"
#include "logic.h"
#include "drawing.h"
#include "util.h"
#include "fonts/verdana9.h"
#include "fonts/verdana14.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint32_t Uptime = 0;
static uint32_t ShutDownDelay;
static bool USB_CON_STAT = false;



/* Private functions ---------------------------------------------------------*/

void DrawNeedle(uint32_t Angle)
{
  //uint32_t r = 35;
  //uint32_t x1, y1, x2, y2;
  //static uint32_t oldX, oldY;
  //uint32_t a;

  //a = DEGREES_TO_FIX32(Angle);
  
  //x1 = 80 << 16;
  //y1 = 64 << 16;
  
  //x2 = x1 + ((r * (cosine(a))));
  //y2 = y1 + ((r * (sine(a))));
    
  //x2 = 120 << 16;
  //y2 = ((20 + Angle) << 16);
  
  /*
  LCD_SetColor(0, 0, 0);
  LCD_DrawLine(x1 >> 16, y1 >> 16, oldX >> 16, oldY >> 16);
  LCD_SetColor(255, 0, 0);
  LCD_DrawLine(x1 >> 16, y1 >> 16, x2 >> 16, y2 >> 16);
  */
  //oldX = x2;
  //oldY = y2;
}

/**
  * @brief  Logic initialization.  
  * @retval None
  */
void Logic_Init(void)
{    
  drawFill(COLOR_BLACK);
  drawRectangle(0, 0, 159, 127, COLOR_GREEN);
  drawLine(0, 16, 159, 16, COLOR_GREEN);  
  drawString(3, 3, COLOR_WHITE, &verdana9ptFontInfo, "K2RP remote");
  
}


/**
  * @brief  Display clock in the screen corner  
  */
void DisplayClock(uint32_t Period)
{
  const uint16_t ClockLocationX = 100;
  const uint16_t ClockLocationY = 3;
  const uint16_t ClockWidth     = 48;
  const uint16_t ClockHeight    = 10;  
  char text[10];
  uint32_t Seconds = Uptime / 1000;
  static uint32_t PrevSeconds = 0xFFFFFF;
  
  if (Seconds >= 216000) Seconds = 216000 - 1;
  
	
  if (Seconds != PrevSeconds)
  {        
    sprintf(text, "%02d:%02d:%02d",(Seconds / 3600) % 60, (Seconds / 60) % 60, Seconds % 60);      
    drawRectangleFilled(ClockLocationX, ClockLocationY, ClockLocationX + ClockWidth, ClockLocationY + ClockHeight, COLOR_BLACK);
    drawString(ClockLocationX, ClockLocationY, COLOR_GRAY_225, &verdana9ptFontInfo, text);
    PrevSeconds = Seconds;
  }
}

/**
  * @brief  Display battery indicator on the screen corner  
  */
void DisplayBattery(uint32_t Period)
{
  const uint16_t BatteryLocationX = 150;
  const uint16_t BatteryLocationY = 3;
  const uint16_t BatteryWidth     = 6;
  const uint16_t BatteryHeight    = 10;  
  static uint8_t charging_level;
  static uint32_t charging_timer;  
  uint8_t battery_level;
  bool charging;
  uint16_t y;
    
	
	const uint16_t RobotBatLocationX = 3;
  const uint16_t RobotBatLocationY = 20;
  const uint16_t RobotBatWidth     = 30;
  const uint16_t RobotBatHeight    = 10;  
  char RobotBatText[10];
	float vBatt;
	uint8_t lowBatt;
	
	// display Robot's battery
	if(NewMsg) {
		
		
		vBatt = (float)(InputMsg.InPacket.battVoltage / 3.6);
		if(vBatt < 10.80) {
			lowBatt = 1;
			Speaker_Beep(2000, 50, 50); // beep when Robot's battery is low
		}
		else {
			lowBatt = 0;
		}
		snprintf( RobotBatText,10, "%2.2f", vBatt);		
    drawRectangleFilled(RobotBatLocationX, RobotBatLocationY, RobotBatLocationX + RobotBatWidth, RobotBatLocationY + RobotBatHeight, COLOR_BLACK);
    drawString(RobotBatLocationX, RobotBatLocationY, ((lowBatt) ? COLOR_RED : COLOR_GREEN) , &verdana9ptFontInfo, RobotBatText);
		
		
			NewMsg = 0;	//clear new message flag
	}
	
	
	
  /* Get battery status */
  charging = Power_IsBatteryCharging();
	
  battery_level = Power_GetBatteryLevel();
	if(battery_level > 0) {
		battery_level = battery_level / BatteryHeight;
	}	
  
  /* Display charging or display status */
	// USB power
	if(USB_CON_STAT) {
		// Battery is charging
		if (charging) {
			for (y = 0; y <= BatteryHeight; y++) {
				drawLine(BatteryLocationX, BatteryLocationY + BatteryHeight - y,
								 BatteryLocationX + BatteryWidth, BatteryLocationY + BatteryHeight - y,
								 ((y > charging_level) ? COLOR_BLACK : COLOR_BLUE));
			}
    
			/* Move charging indicator every 200ms */
			charging_timer += Period;
			if (charging_timer > 200) {
				charging_timer -= 200;    
				charging_level++;
				if (charging_level > BatteryHeight) {
					charging_level = 0;
				}
			}
		} // end charging
		// Battery fully charged
		else {
			for (y = 0; y <= BatteryHeight; y++) {
				drawLine(BatteryLocationX, 
								 BatteryLocationY + BatteryHeight - y,
								 BatteryLocationX + BatteryWidth, 
								 BatteryLocationY + BatteryHeight - y,
								 COLOR_BLUE);
			} // end for
		} // end full charge
  } // end USB power 
	// Battery power
  else {
		// Battery empty, shut down
		if(battery_level == 0) {
			Power_TurnOff(100);
		} // end shut down
		
		// Display battery
    for (y = 0; y <= BatteryHeight; y++)
    {
      drawLine(BatteryLocationX, BatteryLocationY + BatteryHeight - y,
        BatteryLocationX + BatteryWidth, BatteryLocationY + BatteryHeight - y,
        ((y < battery_level) ? ((battery_level > 2) ? COLOR_GREEN : COLOR_RED) : COLOR_BLACK ));
    }
  } // end Battery power
}



void DisplayStuff(void)
{
  char text[10];
  uint16_t ubat = Power_GetSupplyVoltage();
  uint16_t temp = Power_GetTemperature();
  
  sprintf(text, "%d mV", ubat);
  drawRectangleFilled(126, 21, 158, 35, COLOR_BLACK);
  drawString(126, 23, COLOR_GRAY_225, &verdana9ptFontInfo, text);  
  
  sprintf(text, "%d deg", temp);
  drawRectangleFilled(26, 21, 58, 35, COLOR_BLACK);
  drawString(26, 23, COLOR_GRAY_225, &verdana9ptFontInfo, text);
}

void DrawBar(uint16_t LocationX, uint16_t LocationY, uint16_t Width, uint16_t Range, int16_t Value, uint16_t Color)
{
  Value = MIN(Value,  Range);
  Value = MAX(Value, -Range);
  
  if (Value >= 0)
  {
    drawRectangleFilled(LocationX, LocationY - Range, LocationX + Width, LocationY - Value - 1, COLOR_BLACK);
    drawRectangleFilled(LocationX, LocationY + 1, LocationX + Width, LocationY + Range, COLOR_BLACK);
  }
  else
  {
    drawRectangleFilled(LocationX, LocationY - Range, LocationX + Width, LocationY - 1, COLOR_BLACK);
    drawRectangleFilled(LocationX, LocationY - Value + 1, LocationX + Width, LocationY + Range, COLOR_BLACK);
  }
  
  drawRectangleFilled(LocationX, LocationY, LocationX + Width, LocationY - Value, Color);
}



/**
  * @brief  Logic periodic task
  * @param  Period: Task execution period in milliseconds  
  */
#define ManDrive			0x08
#define ManLeft	  		0x10
#define ManRight			0x20


void Logic_Task(uint32_t Period)
{  
	bool USB_CON_prev_STAT = false;
	
 // int i;
 // static int dirScroll = 0;
 // char text[32];
  
  Uptime += Period;
  
	USB_CON_prev_STAT = Power_Is_USB_Connected();
	if(USB_CON_prev_STAT != USB_CON_STAT) {
		if(USB_CON_prev_STAT == false) {
			// USB DEINIT
			LED_Clear();
		}
		else {
			// USB INIT
			LED_Set();
		}
		USB_CON_STAT = USB_CON_prev_STAT;
	}
	
	
  DisplayClock(Period);
  DisplayBattery(Period);
  //DisplayStuff();
  
	
	if (Button_IsPressed(Button_Stop))
  {
		// send stop cmd
		OutputMsg.OutPacket.rcvCMD = 0x00;			// No CMD
		// set uart transmit packet flag
		if(SendUART == 0) {
			SendUART = 1;
		}
  }
	
	if (Button_IsPressed(Button_Start))
  {
		// send start cmd
		OutputMsg.OutPacket.rcvCMD = 0x01;			// Start CMD
		// set uart transmit packet flag
		if(SendUART == 0) {
			SendUART = 1;
		}
  }
	

  
  if (Button_IsDown(Button_Left) && Button_IsDown(Button_Right))
  {
		// send drive forward cmd
		OutputMsg.OutPacket.rcvCMD = (ManDrive | ManLeft | ManRight);			
		// set uart transmit packet flag
		if(SendUART == 0) {
			SendUART = 1;
		}
  }
  else if (Button_IsDown(Button_Left))
  {    
		// send drive left cmd
		OutputMsg.OutPacket.rcvCMD = (ManDrive | ManRight);			
		// set uart transmit packet flag
		if(SendUART == 0) {
			SendUART = 1;
		}     
  }
  else if (Button_IsDown(Button_Right))
  {
		
		// send drive right cmd
		OutputMsg.OutPacket.rcvCMD = (ManDrive | ManLeft);			
		// set uart transmit packet flag
		if(SendUART == 0) {
			SendUART = 1;
		}
  }

	
 

  
  if (Button_IsDown(Button_Stop))
  {
		ShutDownDelay += Period;
    if (ShutDownDelay >= 5000)
    {
      Speaker_Beep(1000, 30, 50); // beep when power off active
			Power_TurnOff(100);
    }
  }
  else
  {
    ShutDownDelay = 0;
  }

  

  // TODO: Send start, stop or manual drive cmd packet to uart if needed. make 40ms delay between packets.

  
}


