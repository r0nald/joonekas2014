/**
  ******************************************************************************
  * @file    util.h
  * @author  TUT Robotics Club NPO
  * @version V1.0
  * @date    08-July-2013
  * @brief   This file contains definitions for Buttons control functions.
  ******************************************************************************  
  */ 
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TYPEDEFS_H
#define __TYPEDEFS_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"
   
/* Exported types ------------------------------------------------------------*/

#ifndef bool
typedef uint8_t bool;
#endif
  
#ifndef true
#define true 1
#endif
   
#ifndef false
#define false 0
#endif

//#define true  TRUE
//#define false FALSE

#ifndef NULL
#define NULL 0
#endif
   
#ifdef __cplusplus
}
#endif

#endif
