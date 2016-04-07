#include "config.h"
#include "pwm.h"
#include "timer.h"
#include "Exti.h"
#define speed 150//正常行驶速度 0-255
#define TLIN P0&0x07//红外信号线（3路）取P0的低3位 P00最右

sbit k =P1^6;//定义红外开关输入端口
unsigned char g;//常数g
 
//电机模块管脚
//将右电机信号线接P25 pwm0
//将左电机信号线接P25 pwm1

sbit led1 = P0^4;  //循迹模块管脚
sbit led2 = P0^5;
sbit led3 = P0^6;
sbit led4 = P0^7;
sbit led5 = P2^4;
sbit led6 = P2^5;
sbit led7 = P2^0;
sbit led8 = P2^3;
u8 time_counter=0;//timer0 计数
u8 line_counter=0;//黑线 计数
u8 time_counter1=0;//timer1 计数

//压线标志位
bit L1=0;//最右侧标志位
bit L2=0;
bit L3=0;
bit L4=0;//最左侧标志位

u8 flag=0;


extern u8	pwm0,pwm1,pwm2;

/***************************向前走*****************************/
void forward() 
{
		pwm_left(speed);
		pwm_right(speed);
}
/**************************停止*****************************/
void stop() {pwm_left(0);	pwm_right(0);}  

/*左转90度，自动恢复*/
void turn_left()
{
	//调试参数修改转弯模式
		pwm_left(0);
		pwm_right(speed);
	//调试参数，1-255
		delay_ms(2000);
		pwm_left(speed);
		pwm_right(speed);
}

/*右转90度，自动恢复*/
void turn_right()
{
	//调试参数修改转弯模式
		pwm_left(speed);
		pwm_right(0);
	//调试参数，0-65536
		delay_ms(2000);
		pwm_left(speed);
		pwm_right(speed);
}

void adjust_left()
{
	u8 temp=TLIN;
		pwm_left(0);
		pwm_right(speed);
	//????????
	//??????
	//??130 delay_ms(100)
	//??170 delay_ms(180) 1?150 too samll
	//
		delay_ms(220);
		//?????
		for(;temp!=0xf0;temp=TLIN)//???????
		{
		}
		//??
		pwm_left(speed);
		pwm_right(0);
		//????
		delay_ms(200);
		//????
		pwm_left(speed);
		pwm_right(speed);
		return;
		
}
void adjust_right()
{
		u8 temp=TLIN;
		pwm_left(speed);
		pwm_right(0);
	//????????
	//??????
	//??130 delay_ms(100)
	//??170 delay_ms(180) 1?150 too samll
	//
		delay_ms(200);
		//?????
		for(;temp!=0xf0;temp=TLIN)//???????
		{
	//		delay_ms(10);
		}
		//??
		pwm_left(0);
		pwm_right(speed);
		//????
		delay_ms(150);
		//????
		pwm_left(speed);
		pwm_right(speed);
		return;

}

/************************
//左转可调，自动恢复
//t1:保持左转状态时间 1-255
//t2:回调时间 1-255
*************************/
void turn_leftn(u16 t1,u16 t2)
{
	//调试参数修改转弯模式
		pwm_left(0);
		pwm_right(speed);
	//:保持左转状态时间
		delay_ms(t1);
		//回调
		//回调时pwm比需要计算、调试
		pwm_left(speed);
		pwm_right(0);
			//回调时间
		delay_ms(t2);
		//恢复前行
		pwm_left(speed);
		pwm_right(speed);
}

/************************
//右转可调，支持转弯后回调
//t1:保持右转状态时间 1-255
//t2:回调时间 1-255
*************************/
void turn_rightn(u16 t1,u16 t2)
{
	
	//调试参数修改转弯模式
		pwm_left(speed);
		pwm_right(0);
	//保持右转状态时间
		delay_ms(t1);
		
		//回调
		//回调时pwm比需要计算、调试
		pwm_left(0);
		pwm_right(speed);
			//回调时间
		delay_ms(t2);
		
		//恢复前行
		pwm_left(speed);
		pwm_right(speed);

}

/*****************************检测前面是否有小车*******************************/

void check()
{
	if(k==1)
		g=1;
	else 
		g=0;
}


void Inline()		//检测黑线信号，检测到黑线时变为高电平，平时低电平
{
	switch(TLIN)
	{
		//没检测到黑线时，直行
		case 0x00:    forward(); 									break;
		
		//仅右边检测到黑线时,左转
		case 0x01:  adjust_left(); 								break;
		
		//仅中间检测到黑线时，正常直行
		case 0x02: 		line_counter++; 														break;
				
		//中间以及右边检测到黑线时
		case 0x03: 								  							break;
		
		//仅左边检测到黑线时,右转
		case 0x04:	adjust_right();							  break;
		//仅中间未检测到黑线,忽略
		case 0x05:  															break;  
		
		//中间以及左边检测到黑线时
		case 0x06: 															 break;	
		
		//全都检测到黑线时
		case 0x07:  		forward();							 break;
		default: break;
		
	}
		
}

/*************************主函数***********************************/
main()
{ 
	PCA_Init();//pwm初始化
	Timer_config();
	EXTI_config();
	EA=1;
	check();//初始化检测前方小车
	forward(); //直行
	//调试用 1-255
	delay_ms(200);
	while(1)
	{ 
		Inline();
	//	pwm_left(speed);
	//	pwm_right(0);

	 }
 }


