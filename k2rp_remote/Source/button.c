/**
  ******************************************************************************
  * @file    button.c
  * @author  TUT Robotics Club NPO
  * @version V1.0
  * @date    28-June-2013
  * @brief   This file contains Buttons control functions.
  ******************************************************************************  
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "typedefs.h"
#include "button.h"
#include "buttoncfg.h"

/* Private typedef -----------------------------------------------------------*/
typedef struct
{
  uint32_t Clock;
  GPIO_TypeDef * Port;
  uint16_t Pin;
  
} Button_Defition;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private constant ----------------------------------------------------------*/
static const Button_Defition BUTTONS[BUTTON_COUNT] =
{
  /* Button_Start  */ { BUTTON_START_GPIO_CLK, BUTTON_START_GPIO_PORT, BUTTON_START_PIN },
  /* Button_Stop   */ { BUTTON_STOP_GPIO_CLK,  BUTTON_STOP_GPIO_PORT,  BUTTON_STOP_PIN  },
  /* Button_Left   */ { BUTTON_LEFT_GPIO_CLK,  BUTTON_LEFT_GPIO_PORT,  BUTTON_LEFT_PIN  },
  /* Button_Right  */ { BUTTON_RIGHt_GPIO_CLK, BUTTON_RIGHT_GPIO_PORT, BUTTON_RIGHT_PIN }
};

/* Private variables ---------------------------------------------------------*/
static GPIO_InitTypeDef GPIO_InitStructure;
static uint8_t Samples[BUTTON_COUNT];
static uint8_t Statuses[BUTTON_COUNT];
static bool PressedEvents[BUTTON_COUNT];
static bool ReleasedEvents[BUTTON_COUNT];

/**
  * @brief  Buttons initialization.  
  * @retval None
  */
void Button_Init(void)
{  
  uint32_t i;
  
  /* GPIO configuration */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  /* Configure buttons, reset samples and statuses */
  for (i = 0; i < BUTTON_COUNT; i++)
  {
    /* Enable clock */
    RCC_AHB1PeriphClockCmd(BUTTONS[i].Clock, ENABLE);
    
    /* GPIO configuration */
    GPIO_InitStructure.GPIO_Pin = BUTTONS[i].Pin;
    GPIO_Init(BUTTONS[i].Port, &GPIO_InitStructure);
    
    /* Reset variables */
    Samples[i] = 0x55;
    Statuses[i] = 0xFF;
    PressedEvents[i] = false;
    ReleasedEvents[i] = false;
  }
}


/**
  * @brief  Button periodic task
  * @param  Period: Task execution period in milliseconds  
  */
void Button_Task(uint32_t Period)
{
  uint32_t i;

  /* Check each button */
  for (i = 0; i < BUTTON_COUNT; i++)
  {
    /* Takes samples */
    if (GPIO_ReadInputDataBit(BUTTONS[i].Port, BUTTONS[i].Pin) == Bit_RESET)
    {
      Samples[i] = (Samples[i] << 1) | 1;
    }
    else
    {
      Samples[i] <<= 1;
    }
    
    /* All samples show pressing ? */
    if ((Samples[i] & ACTIVE_MASK) == ACTIVE_MASK)
    {
      /* Pressed event? */
      if (Statuses[i] == 0)
      {
        PressedEvents[i] = true;
      }      
      /* Down */
      Statuses[i] = 1;      
    }
    /* All samples show unpressed ? */
    else if ((Samples[i] & ACTIVE_MASK) == 0)
    {
      /* Released event? */
      if (Statuses[i] == 1)
      {
        ReleasedEvents[i] = true;
      }      
      /* Up */
      Statuses[i] = 0;
    }    
  }
}


/**
  * @brief  Getting button down status
  * @param  Button: Button type
  * @retval true if button is down, false if not
  */
bool Button_IsDown(Button_TypeDef Button)
{    
  return ((Statuses[Button] == 1) ? true : false);
}


/**
  * @brief  Getting button press event
  * @param  Button: Button type
  * @retval true if button is pressed, false if not
  */
bool Button_IsPressed(Button_TypeDef Button)
{  
  bool status = PressedEvents[Button];
  PressedEvents[Button] = false;
  return status;
}


/**
  * @brief  Getting button released event
  * @param  Button: Button type
  * @retval true if button is released, false if not
  */
bool Button_IsReleased(Button_TypeDef Button)
{  
  bool status = ReleasedEvents[Button];
  ReleasedEvents[Button] = false;
  return status;
}
