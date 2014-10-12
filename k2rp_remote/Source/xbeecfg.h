/**
  ******************************************************************************
  * @file    xbeecfg.h
  * @author  Mikk Leini
  * @version V1.0
  * @date    10-June-2013
  * @brief   This file contains definitions for XBee configuration.
  ******************************************************************************  
  */ 
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __XBEECFG_H
#define __XBEECFG_H

#ifdef __cplusplus
 extern "C" {
#endif
   
/* Includes ------------------------------------------------------------------*/
#include "typedefs.h"
   
/* Public macros -------------------------------------------------------------*/
#define XBEE_COM                        USART2
#define XBEE_COM_APBPERIPHCLOCK         RCC_APB1PeriphClockCmd
#define XBEE_COM_CLK                    RCC_APB1Periph_USART2
#define XBEE_COM_IRQn                   USART2_IRQn
#define XBEE_COM_IRQHandler             USART2_IRQHandler

#define XBEE_COM_TX_PIN                 GPIO_Pin_2
#define XBEE_COM_TX_GPIO_PORT           GPIOA
#define XBEE_COM_TX_GPIO_CLK            RCC_AHB1Periph_GPIOA
#define XBEE_COM_TX_SOURCE              GPIO_PinSource2
#define XBEE_COM_TX_AF                  GPIO_AF_USART2

#define XBEE_COM_RX_PIN                 GPIO_Pin_3
#define XBEE_COM_RX_GPIO_PORT           GPIOA
#define XBEE_COM_RX_GPIO_CLK            RCC_AHB1Periph_GPIOA
#define XBEE_COM_RX_SOURCE              GPIO_PinSource3
#define XBEE_COM_RX_AF                  GPIO_AF_USART2

#define XBEE_RST_PIN                    GPIO_Pin_13
#define XBEE_RST_GPIO_PORT              GPIOC
#define XBEE_RST_GPIO_CLK               RCC_AHB1Periph_GPIOC

#define XBEE_BAUDRATE                   115200
#define XBEE_API_ESCAPED

#ifdef __cplusplus
}
#endif

#endif
