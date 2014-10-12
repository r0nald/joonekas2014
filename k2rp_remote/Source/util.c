/**
  ******************************************************************************
  * @file    util.c
  * @author  TUT Robotics Club NPO
  * @version V1.0
  * @date    18-August-2013
  * @brief   This file contains utility functions.
  ******************************************************************************  
  */ 

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "typedefs.h"
#include "util.h"

/* Private macros ------------------------------------------------------------*/
//#define DEBUG_PRINT(format, ...) printf("Util: " format "\n", ##__VA_ARGS__)
#define DEBUG_PRINT(format, ...)

/* Private constants ---------------------------------------------------------*/
static const uint8_t DecDigits[] =
{
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
};

static const uint8_t HexDigits[] =
{
	'0', '1', '2', '3', '4', '5', '6', '7',
	'8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
};

/* Public functions ----------------------------------------------------------*/


/**
  * @brief  Countdown function
  * @retval true if countdown has reached zero
  */
bool Util_Countdown(uint32_t * Timer, uint32_t Period, bool DetectEdge)
{  
  bool result = false;
  
  /* Timer still running ? */
  if (*Timer > 0)
  {
    if (*Timer > Period)
    {
      *Timer -= Period;
    }
    else
    {
      *Timer = 0;
      result = true;
    }
  }
  else
  {
    if (!DetectEdge)
    {
      result = true;
    }
  }
  
  return result;
}


/**
  * @brief  Integer string parser.
  * @retval true when parsing was successful, false if not.
  */
bool Util_ParseUInt32(const char * str, uint16_t length, bool ishex, uint32_t * value)
{  
  uint16_t i;
  uint32_t digit, sum = 0;
  bool found_digit;
    
  /* Calculate number */    
  for (i = 0; i < length; i++)
  {
    /* Parse digit */
    found_digit = false;
    
    /* Hex ? */
  	if (ishex)
  	{  	  
  		for (digit = 0; (!found_digit) && (digit < 16); digit++)
  		{
  			if (str[i] == HexDigits[digit])
        {
          sum = (sum * 16) + digit;
          found_digit = true;
  			}
  		}
  		if (!found_digit)
      {
        DEBUG_PRINT("%s is not hexadecimal number", str);
        return false;
      }
  	}
  	else
  	{
  	  for (digit = 0; (!found_digit) && (digit < 10); digit++)
  		{
  			if (str[i] == DecDigits[digit])
        {          
          sum = (sum * 10) + digit;
          found_digit = true;
  			}
  		}
  		if (!found_digit)
      {
        DEBUG_PRINT("%s is not decimal number", str);
        return false;
      }
  	}
  }
  
  /* Output value */  
  *value = sum;
  
  if (ishex)
  {
    DEBUG_PRINT("Parsed U32 hexadecimal '%s' to %X", str, *value);
  }
  else
  {
    DEBUG_PRINT("Parsed U32 decimal '%s' to %d", str, *value);
  }  
  
  return true;
}

bool Util_ParseUInt16(const char * str, uint16_t length, bool ishex, uint16_t * value)
{
  uint32_t u32;
  bool result = Util_ParseUInt32(str, length, ishex, &u32);
  
  if (result)
  {
  	*value = (uint16_t)(u32 & 0xFFFF);
  }
  
  return result;
}

bool Util_ParseUInt8(const char * str, uint16_t length, bool ishex, uint8_t * value)
{
  uint32_t u32;
  bool result = Util_ParseUInt32(str, length, ishex, &u32);
  
  if (result)
  {
  	*value = (uint8_t)(u32 & 0xFF);
  }
  
  return result;
}


/**
  * @brief  Double parser
  * @retval true when parsing was successful, false if not.  
  */
bool Util_ParseDouble(const char * str, uint16_t length, double * value)
{
  char buffer[32];
  double dbl;
  
  if (length == 0) return false;
  if (length > 32) return false;
    
  strncpy(buffer, str, length);
  buffer[length] = '\0';
  
  dbl = strtod(buffer, NULL);
  *value = dbl;

  DEBUG_PRINT("Parsed double '%s' to '%f'", buffer, dbl);
  
  return true;
}


/**
  * @brief  Coordinate string parser.
  * @retval true when parsing was successful, false if not.
  * @note   Verified with http://www.csgnetwork.com/gpscoordconv.html
  */
bool Util_ParseGPSCoordinate(const char * str, uint16_t length, double * value)
{  
  uint32_t deg, min;
  uint32_t minfraq1 = 0, minfraq2 = 0; /* Optional */
  
  /* Is coordinate size enough ? */
  if (length >= 5)
  {
    /* Are degrees 1, 2 or 3 digits ? */   
    if (str[3] == '.')
    {
      if (!Util_ParseUInt32(str, 1, false, &deg)) return false;
      if (!Util_ParseUInt32(str + 1, 2, false, &min)) return false;
      if (length >= 6) if (!Util_ParseUInt32(str + 4, 2, false, &minfraq1)) return false;
      if (length >= 8) if (!Util_ParseUInt32(str + 6, 2, false, &minfraq2)) return false;
    }
    else if (str[4] == '.')
    {
      if (!Util_ParseUInt32(str, 2, false, &deg)) return false;
      if (!Util_ParseUInt32(str + 2, 2, false, &min)) return false;
      if (length >= 7) if (!Util_ParseUInt32(str + 5, 2, false, &minfraq1)) return false;
      if (length >= 9) if (!Util_ParseUInt32(str + 7, 2, false, &minfraq2)) return false;
    }
    else if (str[5] == '.')
    {
      if (!Util_ParseUInt32(str, 3, false, &deg)) return false;
      if (!Util_ParseUInt32(str + 3, 2, false, &min)) return false;
      if (length >= 8)  if (!Util_ParseUInt32(str + 6, 2, false, &minfraq1)) return false;
      if (length >= 10) if (!Util_ParseUInt32(str + 8, 2, false, &minfraq2)) return false;
    }
    else
    {
      /* Not possible */
      return false;
    }
  }
  
  /* Display */
  DEBUG_PRINT("Coordinate %d deg, %d min, %d minfraq, %d minfraq1", deg, min, minfraq1, minfraq2);
            
  /* Calculate degrees in decimal */
  *value = (double)deg +
           ((double)min / 60.0) + 
           ((double)minfraq1 / 6000.0) +
           ((double)minfraq2 / 600000.0);

  return true;
}
