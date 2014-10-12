/**
  ******************************************************************************
  * @file    led.c
  * @author  TUT Robotics Club NPO
  * @version V1.0
  * @date    28-June-2013
  * @brief   This file contains LED control functions.
  ******************************************************************************  
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "typedefs.h"
#include "led.h"
#include "ledcfg.h"

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static GPIO_InitTypeDef GPIO_InitStructure;

/**
  * @brief  Status LED initialization.  
  * @retval None
  */
void LED_Init(void)
{  
  /* LED clock enable */
  RCC_AHB1PeriphClockCmd(LED_GPIO_CLK, ENABLE);
  
  /* LED output pin configuration */
  GPIO_InitStructure.GPIO_Pin = LED_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);
}


/**
  * @brief  LED periodic task
  * @param  Period: Task execution period in milliseconds  
  */
void LED_Task(uint32_t Period)
{
  
}


/**
  * @brief  Status LED lighting  
  * @retval None
  */
void LED_Set(void)
{
  GPIO_WriteBit(LED_GPIO_PORT, LED_PIN, Bit_SET);
}

/**
  * @brief  Status LED dimming  
  * @retval None
  */
void LED_Clear(void)
{
  GPIO_WriteBit(LED_GPIO_PORT, LED_PIN, Bit_RESET);  
}
