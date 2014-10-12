/**
  ******************************************************************************
  * @file    usbd_usr.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    22-July-2011
  * @brief   This file includes the user application layer
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "usbd_usr.h"
#include "usbd_ioreq.h"




USBD_Usr_cb_TypeDef USR_cb =
{
  USBD_USR_Init,
  USBD_USR_DeviceReset,
  USBD_USR_DeviceConfigured,
  USBD_USR_DeviceSuspended,
  USBD_USR_DeviceResumed,

};




/**
* @brief  USBD_USR_Init 
* @param  None
* @retval None
*/
void USBD_USR_Init(void)
{  
// DO NOTHING 
// LED INIT
  
}

/**
* @brief  USBD_USR_DeviceReset 
* @param  speed : device speed
* @retval None
*/
void USBD_USR_DeviceReset(uint8_t speed )
{
// DO NOTHING
}


/**
* @brief  USBD_USR_DeviceConfigured
* @param  None
* @retval Staus
*/
void USBD_USR_DeviceConfigured (void)
{
	/* GREEN LED ON - VCP Interface configured */
	GPIOC->BSRRL = GPIO_Pin_8; // LED ON

}

/**
* @brief  USBD_USR_DeviceSuspended 
* @param  None
* @retval None
*/
void USBD_USR_DeviceSuspended(void)
{
	/* GREEN LED OFF-USB Device in Suspend Mode. */
	GPIOC->BSRRH = GPIO_Pin_8; // LED OFF
	
	/* Users can do their application actions here for the USB-Reset */
	
}


/**
* @brief  USBD_USR_DeviceResumed 
* @param  None
* @retval None
*/
void USBD_USR_DeviceResumed(void)
{
    /* GREEN LED ON - USB Device in Idle Mode. */
		GPIOC->BSRRL = GPIO_Pin_8; // LED ON
	
    /* Users can do their application actions here for the USB-Reset */
	
}


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
