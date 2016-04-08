
#ifndef		__CONFIG_H
#define		__CONFIG_H

/*********************************************************/

#define MAIN_Fosc		22118400L	//定义主时钟
//#define MAIN_Fosc		12000000L	//定义主时钟
//#define MAIN_Fosc		11059200L	//定义主时钟
//#define MAIN_Fosc		 5529600L	//定义主时钟
//#define MAIN_Fosc		24000000L	//定义主时钟

/*********************************************************/
#include	"STC15F2K60S2.H"
#include 		"pwm.h"
#include  "Lcd.h"

#define speed 150//正常行驶速度 0-255

void stop();
void Line_Count();

#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16 unsigned int
#endif
#ifndef u32
#define u32 unsigned long
#endif
#endif
