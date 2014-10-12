#include "Comm.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>


#define StartByte1 0x4B
#define StartByte2 0x32




static int			ByteCount;


static uint8_t 	NewMsg;

void Comm_Init(void)
{
	ByteCount = -2;
	NewMsg = 0;
}



void Comm_Process(uint8_t InByte)
{



// Waiting for start byte
	if(ByteCount == -2)
	{
		if(InByte == StartByte1) {   // Found first start Byte  	
        ByteCount = -1;
		}
		return;	
  }
	else if(ByteCount == -1) {	
		if (InByte == StartByte2) { // Found 2nd start Byte 
			ByteCount = 0;
		}
		else {
			ByteCount = -2;
		}
		return;
	}

	InputMsg.RxBytes[ByteCount] = InByte;
	
	
	if(ByteCount >= (sizeof(InputMsg_t) - 1) ) {
		if(InputMsg.InPacket.EndByte == 0x0A0D){
				NewMsg = 1;
		}
		ByteCount = -2;
		
	} 
	else {
		ByteCount++;	
	}
}

uint8_t Comm_NewMsg(void)
{
	uint8_t hadNewMsg = NewMsg;
	NewMsg = 0;
	return hadNewMsg;
}







