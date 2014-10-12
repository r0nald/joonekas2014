/**
  ******************************************************************************
  * @file    speaker.c
  * @author  TUT Robotics Club NPO
  * @version V1.0
  * @date    28-June-2013
  * @brief   This file contains definitions for Speaker control functions.
  ******************************************************************************  
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "typedefs.h"
#include "speaker.h"
#include "speakercfg.h"
#include "util.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint32_t                BeepDuration;
static GPIO_InitTypeDef        GPIO_InitStructure;;
static TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
static TIM_OCInitTypeDef       TIM_OCInitStructure;  

/**
  * @brief  Speaker initialization.  
  * @retval None
  */
void Speaker_Init(void)
{
  uint16_t PrescalerValue = 0;

  /* --------------------------- System Clocks Configuration ---------------------*/
  
  /* Timer clock enable */
  RCC_APB1PeriphClockCmd(SPEAKER_TIMER_CLK, ENABLE);
  
  /* Speaker clock enable */
  RCC_AHB1PeriphClockCmd(SPEAKER_GPIO_CLK, ENABLE);  

  /*--------------------------------- GPIO Configuration -------------------------*/
  /* GPIOB Configuration: speaker PWM */
  GPIO_InitStructure.GPIO_Pin = SPEAKER_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(SPEAKER_GPIO_PORT, &GPIO_InitStructure);
  GPIO_PinAFConfig(SPEAKER_GPIO_PORT, SPEAKER_SOURCE, SPEAKER_AF);
  
  /* Compute the prescaler value */
  PrescalerValue = (uint16_t) (SystemCoreClock / SPEAKER_MAIN_FREQUENCY) - 1;
  
  /* Time base configuration */  
  TIM_TimeBaseStructure.TIM_Period = SPEAKER_MAIN_FREQUENCY / 1000;
  TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(SPEAKER_TIMER, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

  /* Output compare counter match value is half the timer period */
  TIM_OC3Init(SPEAKER_TIMER, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(SPEAKER_TIMER, TIM_OCPreload_Enable);    
  TIM_SetCompare3(SPEAKER_TIMER, 0);
    
  /* Timer enable counter */
  TIM_Cmd(SPEAKER_TIMER, ENABLE);
}


/**
  * @brief  Speaker periodic task
  * @param  Period: Task execution period in milliseconds  
  */
void Speaker_Task(uint32_t Period)
{
  if (Util_Countdown(&BeepDuration, Period, true))
  {  
    TIM_SetCompare3(SPEAKER_TIMER, 0);
  }
}


/**
  * @brief  Beep function of speaker
  * @param  Frequency: Frequency in hertz
  * @param  Duration: Duration in milliseconds
  * @param  Volume: 0 to 100%  
  */
void Speaker_Beep(uint32_t Frequency, uint32_t Duration, uint8_t Volume)
{  
  uint32_t Period;
    
  /* Turn on at all ? */
  if (Duration > 0)
  {
    BeepDuration = Duration;  
    
    /* Limit frequency between 20 Hz and 16 kHZ */
    if (Frequency < 20)    Frequency = 20;
    if (Frequency > 16000) Frequency = 16000;      
    Period = SPEAKER_MAIN_FREQUENCY / Frequency;
    
    /* Limit volume between 0 and 100% */
    if (Volume > 100) Volume = 100;  
    
    /* Set new PWM period */
    TIM_SetAutoreload(SPEAKER_TIMER, Period);
    
    /* Max duty cycle 33% */
    /* More doesn't make a difference in real volume */
    TIM_SetCompare3(SPEAKER_TIMER, (Period * Volume) / 333);    
  }
}
