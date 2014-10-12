/******************** (C) COPYRIGHT 2009 STMicroelectronics ********************
* File Name          : main.c
* Author             : MCD Application Team
* Version            : V3.1.0
* Date               : 10/30/2009
* Description        : Virtual Com Port Demo main file
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/
/* Demonstracni program pro 4. dil serialu k STM32F4 Discovery kitu
 * Vyuziti kitu jako USB Virtualniho serioveho portu
 * Upravy ver. 1.0; (C) 2011 Mard, mcu.cz */


/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "usbd_cdc_core.h"
#include "usbd_cdc_vcp.h"
#include "usbd_usr.h"
#include "usbd_desc.h"

#include "main.h"
#include "typedefs.h"
#include "power.h"
#include "led.h"
#include "button.h"
#include "speaker.h"
#include "st7735.h"
#include "xbee.h"
#include "logic.h"
#include "util.h"


/* Private typedef -----------------------------------------------------------*/
typedef struct
{
  void (* InitFunction)(void);
  void (* TaskFunction)(uint32_t);
  
} Task;

/* Private define ------------------------------------------------------------*/
#define RT_TASK_PERIOD 10
#define BG_TASK_PERIOD 100

/* Private constants ---------------------------------------------------------*/
static const Task RT_TASK_LIST[] =
{
  { Power_Init,    Power_Task    },
  { LED_Init,      LED_Task      },
  { Button_Init,   Button_Task   },
  { Speaker_Init,  Speaker_Task  },
  { ST7735_Init,   ST7735_Task   },  
  { XBee_Init,     XBee_Task     },
 
};

static const Task BG_TASK_LIST[] =
{
  { Logic_Init,    Logic_Task    },
  };

/* Private macro -------------------------------------------------------------*/
#define RT_TASK_COUNT COUNT_OF(RT_TASK_LIST)
#define BG_TASK_COUNT COUNT_OF(BG_TASK_LIST)

/* Private variables ---------------------------------------------------------*/
static volatile uint32_t RTPeriodCounter = 0;
static volatile uint32_t BGPeriodCounter = 0;

__ALIGN_BEGIN USB_OTG_CORE_HANDLE    USB_OTG_dev __ALIGN_END ;
 
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

	/* USB INIT */
	/*
  USBD_Init(&USB_OTG_dev,            
  USB_OTG_FS_CORE_ID,  
  &USR_desc, 
  &USBD_CDC_cb,
  &USR_cb);

	GPIOC->BSRRL = GPIO_Pin_8; // LED ON
	GPIOC->BSRRH = GPIO_Pin_8; // LED OFF
	
RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_OTG_FS, ENABLE) ; // enable usb AHB bus clock
RCC_AHB2PeriphResetCmd(RCC_AHB2Periph_OTG_FS, ENABLE); // reset usb ahb peripheral
USB_OTG_DisableGlobalInt(pdev);
*/



/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  uint32_t task;
  uint32_t period;
  
  /* Configure SysTick to trigger interrupt every 1 ms */
	if (SysTick_Config(SystemCoreClock / 1000)) { 
    /* Capture error */ 
    while (1);
  }
  
  /* Enable the PWR clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
  
  /* Enable SYSCFG clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  
  /* Configure the Priority Group to 2 bits */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  
  
  /* Initialize real-time tasks */     
  for (task = 0; task < RT_TASK_COUNT; task++)
  {
    RT_TASK_LIST[task].InitFunction();
  }
  
  /* Initialize background tasks */     
  for (task = 0; task < BG_TASK_COUNT; task++)
  {
    BG_TASK_LIST[task].InitFunction();
  }
  
	USBD_Init(&USB_OTG_dev,            
  USB_OTG_FS_CORE_ID,  
  &USR_desc, 
  &USBD_CDC_cb,
  &USR_cb);
	
  /* Infinite loop */
  while (1)
  {
    /* Store period in temp variable and then reset period */
    DI();
    period = BGPeriodCounter;
    BGPeriodCounter = 0;
    EI();
    
    /* Execute background tasks */
    for (task = 0; task < BG_TASK_COUNT; task++)
    {
      BG_TASK_LIST[task].TaskFunction(period);
    }
    
    /* Wait for background tasks period time if it's not elapsed yet */
    while (BGPeriodCounter < BG_TASK_PERIOD) {}
  }
}


/**
  * @brief  This function handles SysTick Handler and acts as real-time task scheduler.  
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  uint32_t task;
  
  /* Execute RT tasks every RT_TASK_PERIOD */
  if (++RTPeriodCounter >= RT_TASK_PERIOD)
  {  
    RTPeriodCounter = 0;    
    for (task = 0; task < RT_TASK_COUNT; task++)
    {
      RT_TASK_LIST[task].TaskFunction(RT_TASK_PERIOD);
    }
  }
    
  /* Count background tasks period in milliseconds */
  BGPeriodCounter++;
}



#ifdef USE_FULL_ASSERT
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert_param error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
#endif

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
