/**
  ******************************************************************************
  * @file    powercfg.h
  * @author  TUT Robotics Club NPO
  * @version V1.0
  * @date    08-July-2013
  * @brief   This file contains definitions for Power configuration.
  ******************************************************************************  
  */ 
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __POWERCFG_H
#define __POWERCFG_H

#ifdef __cplusplus
 extern "C" {
#endif
   
/* Includes ------------------------------------------------------------------*/
#include "typedefs.h"

/* Public define -------------------------------------------------------------*/
#define ADC1_DR_ADDRESS       ((uint32_t)0x4001204C)

/* Public macro --------------------------------------------------------------*/
#define PWR_CTRL_PIN          GPIO_Pin_11
#define PWR_CTRL_GPIO_PORT    GPIOB
#define PWR_CTRL_GPIO_CLK     RCC_AHB1Periph_GPIOB
	 
#define USB_PWR_DET_PIN       GPIO_Pin_10
#define USB_PWR_DET_GPIO_PORT GPIOA
#define USB_PWR_DET_GPIO_CLK  RCC_AHB1Periph_GPIOA

#define CHG_STAT_PIN          GPIO_Pin_9
#define CHG_STAT_GPIO_PORT    GPIOC
#define CHG_STAT_GPIO_CLK     RCC_AHB1Periph_GPIOC

#define UBAT_PIN              GPIO_Pin_1
#define UBAT_GPIO_PORT        GPIOB
#define UBAT_GPIO_CLK         RCC_AHB1Periph_GPIOB
#define UBAT_ADC_CHANNEL      ADC_Channel_9

#define POWER_VOLTAGE_FORMULA(adc) ((adc * 3300 * 2) / 4095)

#ifdef __cplusplus
}
#endif

#endif
