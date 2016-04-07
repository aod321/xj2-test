#ifndef __Lcd_H_
#define __Lcd_H_

#include"config.h"



//void	Initialize_LCD(void);
void	Write_AC(u8 hang,u8 lie);
void	Write_DIS_Data(u8 DIS_Data);
void	ClearLine(u8 hang);
u8		BIN_ASCII(u8 tmp);
void 	PutString(u8 hang,u8 lie,u8 *puts);
void	WriteChar(u8 hang,u8 lie,u8 dat);
void Initialize_LCD(void)	;

sfr		LCD_BUS = 0x90;	//P0--0x80, P1--0x90, P2--0xA0, P3--0xB0
sbit	LCD_ENA	= P3^6;	
sbit	LCD_RW	= P3^5;	
sbit	LCD_RS	= P3^4;



#define LineLenth	16		//16x2
//#define LineLenth 20		//20x2
//#define LineLenth 40		//40x2

#define	LCD_DelayNop()	NOP(20)

#endif
