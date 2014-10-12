/**
  ******************************************************************************
  * @file    usb_conf.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    22-July-2011
  * @brief   General low level driver configuration
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_CONF__H__
#define __USB_CONF__H__

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
 
#define USB_OTG_FS_CORE

 
/****************** USB OTG FS CONFIGURATION **********************************/
#define RX_FIFO_FS_SIZE                          128
#define TX0_FIFO_FS_SIZE                          32
#define TX1_FIFO_FS_SIZE                         128
#define TX2_FIFO_FS_SIZE                          32 
#define TX3_FIFO_FS_SIZE                           0

//#define USB_OTG_FS_LOW_PWR_MGMT_SUPPORT
//#define USB_OTG_FS_SOF_OUTPUT_ENABLED

/****************** USB OTG MODE CONFIGURATION ********************************/

#define USE_DEVICE_MODE


/****************** C Compilers dependant keywords ****************************/
/* In HS mode and when the DMA is used, all variables and data structures dealing
   with the DMA during the transaction process should be 4-bytes aligned */    

#define __ALIGN_BEGIN
#define __ALIGN_END   


/* __packed keyword used to decrease the data type alignment to 1-byte */
#if defined (__CC_ARM)         /* ARM Compiler */
  #define __packed    __packed
#elif defined (__ICCARM__)     /* IAR Compiler */
  #define __packed    __packed
#elif defined   ( __GNUC__ )   /* GNU Compiler */                        
  #define __packed    __attribute__ ((__packed__))
#elif defined   (__TASKING__)  /* TASKING Compiler */
  #define __packed    __unaligned
#endif /* __CC_ARM */



#endif //__USB_CONF__H__

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

