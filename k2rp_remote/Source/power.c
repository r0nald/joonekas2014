/**
  ******************************************************************************
  * @file    power.c
  * @author  TUT Robotics Club NPO
  * @version V1.0
  * @date    08-July-2013
  * @brief   This file contains Power control functions.
  ******************************************************************************  
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "typedefs.h"
#include "power.h"
#include "powercfg.h"
#include "util.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static GPIO_InitTypeDef GPIO_InitStructure;
static DMA_InitTypeDef DMA_InitStructure;
static ADC_InitTypeDef  ADC_InitStructure;
static ADC_CommonInitTypeDef ADC_CommonInitStructure;
static __IO uint16_t ADC_ConvertedValue[2];
static uint16_t Voltage;
static uint16_t Temperature;
static uint32_t PowerOnDelay;
static uint32_t PowerOffDelay;

/* Private functions ---------------------------------------------------------*/
static void ConfigureGPIO(void);
static void ConfigureADC(void);

/**
  * @brief  Configure GPIO pins
  * @retval None
  */
static void ConfigureGPIO(void)
{
   /* PWR_CTRL and CHG_STAT clock enable */
  RCC_AHB1PeriphClockCmd(PWR_CTRL_GPIO_CLK | USB_PWR_DET_GPIO_CLK |
                         CHG_STAT_GPIO_CLK | UBAT_GPIO_CLK, ENABLE);
  
  /* PWR_CTRL output pin configuration */
  GPIO_InitStructure.GPIO_Pin = PWR_CTRL_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
  GPIO_Init(PWR_CTRL_GPIO_PORT, &GPIO_InitStructure);
  
  /* USB POWER detect input pin configuration */	
	GPIO_InitStructure.GPIO_Pin = USB_PWR_DET_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
  GPIO_Init(USB_PWR_DET_GPIO_PORT, &GPIO_InitStructure);
	       
  /* CHG_STAT input pin configuration */
  GPIO_InitStructure.GPIO_Pin = CHG_STAT_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(CHG_STAT_GPIO_PORT, &GPIO_InitStructure);  
  
  /* UBAT input pin configuration */
  GPIO_InitStructure.GPIO_Pin = UBAT_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(UBAT_GPIO_PORT, &GPIO_InitStructure);  
}


/**
  * @brief  Configure ADC
  * @retval None
  */
static void ConfigureADC(void)
{
  /*------------------------ DMA1 configuration ------------------------------*/
  
  /* Enable DMA1 clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
  
  /* DMA1 channel1 configuration */
  DMA_DeInit(DMA2_Stream0);	
	DMA_InitStructure.DMA_Channel = DMA_Channel_0;  
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC1_DR_ADDRESS;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&ADC_ConvertedValue[0];
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_BufferSize = 2;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;	
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA2_Stream0, &DMA_InitStructure);
  DMA_Cmd(DMA2_Stream0, ENABLE);
  
	
  /*----------------- ADC1 configuration with DMA enabled --------------------*/
  
 
  
  /* Enable ADC1 clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  
	/* ADC Common Init **********************************************************/
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_7Cycles;
  ADC_CommonInit(&ADC_CommonInitStructure);
	
	/* ADC3 Init ****************************************************************/
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_ExternalTrigConv = 0;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfConversion = 2;
  ADC_Init(ADC1, &ADC_InitStructure);
	
  
  /* Enable temperature sensor and Vref */
  ADC_TempSensorVrefintCmd(ENABLE);
  
  /* ADC1 regular channel configuration */
	ADC_RegularChannelConfig(ADC1, UBAT_ADC_CHANNEL, 1, ADC_SampleTime_112Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_TempSensor, 2, ADC_SampleTime_112Cycles);
	
  /* Enable DMA request after last transfer (Single-ADC mode) */
  ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);
    
  /* Enable ADC1 DMA */
  ADC_DMACmd(ADC1, ENABLE);

  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);
  
  /* Start ADC1 Software Conversion */
  ADC_SoftwareStartConv(ADC1);
}


/* Public functions ----------------------------------------------------------*/

/**
  * @brief  Power control initialization.  
  * @retval None
  */
void Power_Init(void)
{
  ConfigureGPIO();
  ConfigureADC();
  
  /* Reset variables */
  PowerOnDelay = 200;
  PowerOffDelay = 0;
}


/**
  * @brief  Power periodic task
  * @param  Period: Task execution period in milliseconds  
  */
void Power_Task(uint32_t Period)
{  
  /* ADC conversion done ? */
  if (DMA_GetFlagStatus(DMA2_Stream0, DMA_FLAG_TCIF0))  
  {        
    Voltage     = POWER_VOLTAGE_FORMULA(ADC_ConvertedValue[0]);
    Temperature = ADC_ConvertedValue[1];   
    
    /* Start next ADC1 Software Conversion */
    ADC_SoftwareStartConv(ADC1);
  }  
  
  /* Power on delay reached zero (when wasn't zero before) ? */
  if (Util_Countdown(&PowerOnDelay, Period, true))
  {
    GPIO_WriteBit(PWR_CTRL_GPIO_PORT, PWR_CTRL_PIN, Bit_SET);
  }
  
  /* Power off delay reached zero (when wasn't zero before) ? */
  if (Util_Countdown(&PowerOffDelay, Period, true))
  {
    //PowerOff();
    GPIO_WriteBit(PWR_CTRL_GPIO_PORT, PWR_CTRL_PIN, Bit_RESET);
  }
}


/**
  * @brief  Setting power status
  * @param  Delay: Delay until power off
  */
void Power_TurnOff(uint32_t Delay)
{  
  /* Take power on delay also into account to ensure off isn't faster than power up */
  PowerOffDelay = Delay + PowerOnDelay;    
}


/**
  * @brief  Getting supply voltage
  * @retval Millivolts
  */
uint16_t Power_GetSupplyVoltage(void)
{
  return Voltage;
}


/**
  * @brief  Is battery being charged
  * @retval true or false
  */
bool Power_IsBatteryCharging(void)
{
  bool status = false;
  
  if (!GPIO_ReadInputDataBit(CHG_STAT_GPIO_PORT, CHG_STAT_PIN))
  {
    status = true;
  }
  
  return status;
}


/**
  * @brief  Is usb voltage present
  * @retval true or false
  */
bool Power_Is_USB_Connected(void)
{
  bool status = false;
  
  if (GPIO_ReadInputDataBit(USB_PWR_DET_GPIO_PORT, USB_PWR_DET_PIN))
  {
    status = true;
  }
  
  return status;
}

/**
  * @brief  Getting battery charge level
  * @retval Level from 0% to 100%
  */
uint8_t Power_GetBatteryLevel(void)
{
  uint16_t level = Voltage - 3400;
	if(level == 0) { return level;}
	if(level > 800) { level = 800; }

  level = level / 8;  
  
  return level;
}


/**
  * @brief  Getting temperatur voltage
  * @retval Millidegrees in Celcius
  */
uint16_t Power_GetTemperature(void)
{
	unsigned int temp, volt;
	
	 volt = (Temperature *3300)/4095;
   temp = (uint16_t)((volt - 760)/2)+25;
	
  return temp;
}



