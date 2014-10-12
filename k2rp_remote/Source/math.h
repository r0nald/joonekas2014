/**
  ******************************************************************************
  * @file    math.h
  * @author  TUT Robotics Club NPO
  * @version V1.0
  * @date    28-June-2013
  * @brief   This file contains definitions for Math functions.
  ******************************************************************************  
  */ 
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MATH_H
#define __MATH_H

#ifdef __cplusplus
 extern "C" {
#endif   

/* Public types ------------------------------------------------------------- */
typedef uint32_t fixed;
   
/* Exported functions ------------------------------------------------------- */
extern fixed Sin(fixed Angle);
#define Cos(Angle)         Sin(Angle + 0x4000) /* 90 degrees */

#define DEGREES_TO_FIX32(angle) (((((unsigned long)angle) << 22) / 360) << 10)

#define cosine(ulAngle)         sine((ulAngle + 0x40000000))
extern long sine(unsigned long ulAngle);
   
#ifdef __cplusplus
}
#endif

#endif
