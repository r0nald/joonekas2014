/**
  ******************************************************************************
  * @file    usbd_cdc_vcp.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    22-July-2011
  * @brief   Generic media access Layer.
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
#include "usbd_cdc_vcp.h"
#include "xbee.h"
#include "xbeecfg.h"

#include "usb_core.h"       // to refer USB_SETUP_REQ structure           

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

#define CDC_DTR_MASK   0x01
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
LINE_CODING linecoding =
  {
    9600, /* baud rate*/
    0x00,   /* stop bits-1*/
    0x00,   /* parity - none*/
    0x08    /* nb. of bits 8*/
  };




/* These are external variables imported from CDC core to be used for IN 
   transfer management. */
extern uint8_t  APP_Rx_Buffer []; /* Write CDC received data in this buffer.
                                     These data will be sent over USB IN endpoint
                                     in the CDC core functions. */
extern uint32_t APP_Rx_ptr_in;    /* Increment this pointer or roll it back to
                                     start address when writing received data
                                     in the buffer APP_Rx_Buffer. */

/* Private function prototypes -----------------------------------------------*/
static uint16_t VCP_Init     (void);
static uint16_t VCP_DeInit   (void);
static uint16_t VCP_Ctrl     (uint32_t Cmd, uint8_t* Buf, uint32_t Len);
uint16_t VCP_DataTx   (uint8_t* Buf, uint32_t Len);
static uint16_t VCP_DataRx   (uint8_t* Buf, uint32_t Len);

//static uint16_t VCP_COMConfig(uint8_t Conf);


CDC_IF_Prop_TypeDef VCP_fops = 
{
  VCP_Init,
  VCP_DeInit,
  VCP_Ctrl,
  VCP_DataTx,
  VCP_DataRx
};

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  VCP_Init
  *         Initializes the Media on the STM32
  * @param  None
  * @retval Result of the opeartion (USBD_OK in all cases)
  */
static uint16_t VCP_Init(void)
{
// Insert uart init code if needed
  
  return USBD_OK;
}

/**
  * @brief  VCP_DeInit
  *         DeInitializes the Media on the STM32
  * @param  None
  * @retval Result of the opeartion (USBD_OK in all cases)
  */
static uint16_t VCP_DeInit(void)
{

  return USBD_OK;
}


/**
  * @brief  VCP_Ctrl
  *         Manage the CDC class requests
  * @param  Cmd: Command code            
  * @param  Buf: Buffer containing command data (request parameters)
  * @param  Len: Number of data to be sent (in bytes)
  * @retval Result of the opeartion (USBD_OK in all cases)
  */

uint8_t host_port_open = 0; // we need to detect Is VCP open or not, othewise USB halt 

static uint16_t VCP_Ctrl (uint32_t Cmd, uint8_t* Buf, uint32_t Len)
{ 
	USB_SETUP_REQ * req = (USB_SETUP_REQ *)Buf;   // for No Data request
	
  switch (Cmd)
  {
  case SEND_ENCAPSULATED_COMMAND:
    /* Not  needed for this driver */
    break;

  case GET_ENCAPSULATED_RESPONSE:
    /* Not  needed for this driver */
    break;

  case SET_COMM_FEATURE:
    /* Not  needed for this driver */
    break;

  case GET_COMM_FEATURE:
    /* Not  needed for this driver */
    break;

  case CLEAR_COMM_FEATURE:
    /* Not  needed for this driver */
    break;

  case SET_LINE_CODING:
    linecoding.bitrate = (uint32_t)(Buf[0] | (Buf[1] << 8) | (Buf[2] << 16) | (Buf[3] << 24));
    linecoding.format = Buf[4];
    linecoding.paritytype = Buf[5];
    linecoding.datatype = Buf[6];
    /* Set the new configuration */
		// Insert function to change UART parameters
    //VCP_COMConfig(OTHER_CONFIG);
    break;

  case GET_LINE_CODING:
    Buf[0] = (uint8_t)(linecoding.bitrate);
    Buf[1] = (uint8_t)(linecoding.bitrate >> 8);
    Buf[2] = (uint8_t)(linecoding.bitrate >> 16);
    Buf[3] = (uint8_t)(linecoding.bitrate >> 24);
    Buf[4] = linecoding.format;
    Buf[5] = linecoding.paritytype;
    Buf[6] = linecoding.datatype; 
    break;

  case SET_CONTROL_LINE_STATE:
    /* Not  needed for this driver */
	//host_port_open = (pInformation->USBwValues.bw.bb0 & 0x01) != 0 ;
	
	if (req->wValue & CDC_DTR_MASK) {
        //
        // host set DTR to '1'
		host_port_open = 1;
        //
    } else {
        //
        // host reset DTR to '0'
			host_port_open = 0;
        //
    }
	
	//TODO!
    break;

  case SEND_BREAK:
    /* Not  needed for this driver */
    break;    
    
  default:
    break;
  }

  return USBD_OK;
}




/**
  * @brief  putchar
  *         Sends one char over the USB serial link.
  * @param  buf: char to be sent
  * @retval none
  */

void VCP_put_char(uint8_t buf)
{
	VCP_DataTx(&buf,1);
}

void VCP_send_str(uint8_t* buf)
{
	uint32_t i=0;
	while(*(buf + i))
	{
		i++;
	}
	VCP_DataTx(buf, i);
}


/**
  * @brief  VCP_DataTx
  *         CDC received data to be send over USB IN endpoint are managed in 
  *         this function.
  * @param  Buf: Buffer of data to be sent
  * @param  Len: Number of data to be sent (in bytes)
  * @retval Result of the opeartion: USBD_OK if all operations are OK else VCP_FAIL
  */
uint16_t VCP_DataTx (uint8_t* Buf, uint32_t Len)
{
	uint32_t i=0;
	while(i < Len)
	{
		APP_Rx_Buffer[APP_Rx_ptr_in] = *(Buf + i);
		APP_Rx_ptr_in++;
  		i++;
		/* To avoid buffer overflow */
		if(APP_Rx_ptr_in == APP_RX_DATA_SIZE)
		{
			APP_Rx_ptr_in = 0;
		}  
	}
	
  return USBD_OK;
}

/**
  * @brief  VCP_DataRx
  *         Data received over USB OUT endpoint are sent over CDC interface 
  *         through this function.
  *           
  *         @note
  *         This function will block any OUT packet reception on USB endpoint 
  *         untill exiting this function. If you exit this function before transfer
  *         is complete on CDC interface (ie. using DMA controller) it will result 
  *         in receiving more data while previous ones are still not sent.
  *                 
  * @param  Buf: Buffer of data to be received
  * @param  Len: Number of data received (in bytes)
  * @retval Result of the opeartion: USBD_OK if all operations are OK else VCP_FAIL
  */

uint32_t VCP_byteCount = 2; // It is 2 because we need uint16 dummy in union to get correct alignment

static uint16_t VCP_DataRx (uint8_t* Buf, uint32_t Len)
{
	uint32_t i;
	
	

	for (i = 0; i < Len; i++)
	{
		// trash all data while previous packet is still sending
		if(VCP_byteCount == 2) {
			if(*(Buf + i) == 0x4B) { // K
				OutputMsg.TxBytes[VCP_byteCount] = *(Buf + i);
				VCP_byteCount++;
			}
		}	
		else if(VCP_byteCount == 3) {
			if(*(Buf + i) == 0x32) { // 2
				OutputMsg.TxBytes[VCP_byteCount] = *(Buf + i);
				VCP_byteCount++;
			}	
			else {
				VCP_byteCount = 2;// go to search start byte
			}
		}
		else if(VCP_byteCount < sizeof(OutputMsg_t)) {
			OutputMsg.TxBytes[VCP_byteCount] = *(Buf + i);
			if(VCP_byteCount == (sizeof(OutputMsg_t) - 1) ) {	// last byte copied to packet
				if(OutputMsg.OutPacket.EndByte == 0x0A0D){ // check packet end
					// set uart transmit packet flag
					SendUART = 1;
					
					//USART_SendData(XBEE_COM, OutputMsg.TxBytes[2]); // transmit first byte ("K")
				}
				else {
					VCP_byteCount = 1; // 1 + 1 = 2 we got bad data, go to search packet again 
				}
			}
			VCP_byteCount++;		
		}
		
		// DATA ECHO
		//VCP_DataTx(Buf,Len);
		
		//USART_SendData(USART2, *(Buf + i));
		// while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
	    //{}
	}
	
	Len = 0;
	return USBD_OK;
}


/**
  * @brief  VCP_COMConfig
  *         Configure the COM Port with default values or values received from host.
  * @param  Conf: can be DEFAULT_CONFIG to set the default configuration or OTHER_CONFIG
  *         to set a configuration received from the host.
  * @retval None.
  */
/*
static uint16_t VCP_COMConfig(uint8_t Conf)
{
 // Add code if needed
	
	
  return USBD_OK;
}
*/






/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
