/**
  ******************************************************************************
  * @file    xbee.c
  * @author  Mikk Leini
  * @version V1.0
  * @date    22-July-2013
  * @brief   This file contains XBee ZB API interface functions.
  ******************************************************************************  
  */
	
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "typedefs.h"
#include "xbee.h"
#include "xbeecfg.h"
#include "ledcfg.h"
#include "util.h"
#include "usbd_cdc_vcp.h"

/* Private defines -----------------------------------------------------------*/

#define StartByte1 0x4B // K
#define StartByte2 0x32 // 2

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function declarations ---------------------------------------------*/
static void ProcessRxByte(uint8_t RxByte);

static int			URXByteCount;
static int			UTXByteCount;
InputMsg_t 			InputMsg;
OutputMsg_t 		OutputMsg;

uint8_t SendUART = 0;
uint8_t NewMsg = 0;

/* Private functions ---------------------------------------------------------*/


/* Public functions ----------------------------------------------------------*/

/**
  * @brief  XBee UART interface initialization.
  * @retval None
  */
void XBee_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
    
  /* RF_TX, RF_RX and RF_RST clock enable */
  RCC_AHB1PeriphClockCmd(XBEE_COM_TX_GPIO_CLK | XBEE_COM_RX_GPIO_CLK | XBEE_RST_GPIO_CLK, ENABLE);

  /* Connect RF_TX to USARTx_Tx and RF_RX to USARTx_Rx */
  GPIO_PinAFConfig(XBEE_COM_TX_GPIO_PORT, XBEE_COM_TX_SOURCE, XBEE_COM_TX_AF);
  GPIO_PinAFConfig(XBEE_COM_RX_GPIO_PORT, XBEE_COM_RX_SOURCE, XBEE_COM_RX_AF);
  
  /* Configure RF_TX as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = XBEE_COM_TX_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(XBEE_COM_TX_GPIO_PORT, &GPIO_InitStructure);
    
  /* Configure RF_RX as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = XBEE_COM_RX_PIN;
  GPIO_Init(XBEE_COM_RX_GPIO_PORT, &GPIO_InitStructure);	
  
  /* Configure RF_RST as push-pull output */
  GPIO_InitStructure.GPIO_Pin =  XBEE_RST_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(XBEE_RST_GPIO_PORT, &GPIO_InitStructure);

	/* ------------------------------------------------------------------------ */
	
	/* Enable UART clock */
  XBEE_COM_APBPERIPHCLOCK(XBEE_COM_CLK, ENABLE);
	
	/* Configure USART */
	USART_InitStructure.USART_BaudRate = XBEE_BAUDRATE;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_2;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  

  /* USART configuration */
  USART_Init(XBEE_COM, &USART_InitStructure);
  
  /* Enable the USART RX interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = XBEE_COM_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	    
  /* Enable USART */
  USART_Cmd(XBEE_COM, ENABLE);
	
	/* Enable the USART Receive and transmit complete interrupt */
  USART_ITConfig(XBEE_COM, USART_IT_RXNE, ENABLE);
	USART_ITConfig(XBEE_COM, USART_IT_TC, ENABLE);
	
	/* ------------------------------------------------------------------------ */
	
	/* Set XBee reset */
	GPIO_WriteBit(XBEE_RST_GPIO_PORT, XBEE_RST_PIN, Bit_RESET);
	
	URXByteCount = 0;
	UTXByteCount = 3; // uint 16 dummy + first byte transmit is some other place than usart interrupt
	
	// Init struct
	OutputMsg.OutPacket.EndByte = 0x0A0D;   // Packet end
	OutputMsg.OutPacket.StartSTR = 0x324B;  // Packet start magic
	OutputMsg.OutPacket.rcvCMD = 0x00;			// No CMD
	
}


/**
  * @brief  XBee periodic task
  * @param  Period: Task execution period in milliseconds  
  */
void XBee_Task(uint32_t Period)
{
  /* Release XBee reset */
	GPIO_WriteBit(XBEE_RST_GPIO_PORT, XBEE_RST_PIN, Bit_SET);
  
}




/* Private functions -----------------------------------------------------------*/

/**
  * @brief  XBee USART interrupt handler.
  * @retval None
  */
void XBEE_COM_IRQHandler(void)
{	

	/* Received byte ? */
	if (USART_GetITStatus(XBEE_COM, USART_IT_RXNE))
  {    
    /* Process received byte */
    ProcessRxByte(USART_ReceiveData(XBEE_COM) & 0xFF);    
	}
	
	/* Sent byte ? */
	if (USART_GetITStatus(XBEE_COM, USART_IT_TC))
	{
    /* Send another byte if there is some in transmit FIFO */
    if ( UTXByteCount < sizeof(OutputMsg_t) ) {
			USART_SendData(XBEE_COM, OutputMsg.TxBytes[UTXByteCount]);
			UTXByteCount++;
		}
    else
    {
			GPIO_ToggleBits(LED_GPIO_PORT, LED_PIN);
			UTXByteCount = 3; // reset TX bytecount
			VCP_byteCount = 2; // Allow to copy new usb data to outpacket
			SendUART = 0; // allow new packet send
    }
		USART_ClearITPendingBit(XBEE_COM, USART_IT_TC);
	}
}

/**
  * @brief  Received byte processing
  * @param  RxByte: Received byte.
  * @retval None
  */
static void ProcessRxByte(uint8_t RxByte)
{
// Waiting for start byte
	if(URXByteCount == 0)
	{
		if(RxByte == StartByte1) {   // Found first start Byte 
				InputMsg.RxBytes[URXByteCount] = RxByte;
        URXByteCount = 1;
		}
		return;	
  }
	else if(URXByteCount == 1) {	
		if (RxByte == StartByte2) { // Found 2nd start Byte 
			InputMsg.RxBytes[URXByteCount] = RxByte;
			URXByteCount = 2;
		}
		else {
			URXByteCount = 0;
		}
		return;
	}

	InputMsg.RxBytes[URXByteCount] = RxByte;
	
	
	if(URXByteCount >= (sizeof(InputMsg_t) - 1) ) {
		if(InputMsg.InPacket.EndByte == 0x0A0D){
			// we received new debug data
			
			// sync packet transmit with receive
			if(SendUART == 1) {
				USART_SendData(XBEE_COM, OutputMsg.TxBytes[2]); // transmit first byte ("K")
				SendUART = 2;
			}
				
			
			// send over USB
			if(host_port_open == 1) {
				VCP_DataTx (&InputMsg.RxBytes[0], sizeof(InputMsg_t));
			}
				NewMsg = 1;
		}
		URXByteCount = 0;
		
	} 
	else {
		URXByteCount++;	
	}
	

	
	
}
