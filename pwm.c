#include "pwm.h"
extern u8	pwm0,pwm1,pwm2;

//========================================================================
// 函数: void	PCA_Init(void)
// 描述: PCA初始化程序.
//========================================================================
void	PCA_Init(void)
{
	CR = 0;
	AUXR1 = (AUXR1 & ~(3<<4)) | PCA_P24_P25_P26_P27;	//切换IO口
	//将PCA/PWM切换到P24(ECI) P25(CCP0) P26(CCP1) P27(CCP2)
	CCON = 0; //初始化PCA控制寄存器
	
	PCA_PWM0 = (PCA_Mode_Capture | ENABLE);	//8位模式
	PCA_PWM1 = (PCA_Mode_Capture | ENABLE);
	PCA_PWM2 = (PCA_Mode_Capture | DISABLE);
	
	CCAPM0 = 0x42; //PCA模块0为8位PWM模式
	CCAPM1 = 0x42; //PCA模块1为8位PWM模式
	CCAPM2 = 0x42; //PCA模块2为8位PWM模式

	CH = 0;
	CL = 0;
	//选择时钟源
	CMOD = 0x02; //设置PCA时钟源 1T

	pwm0 = 0;	//给PWM一个初值
	pwm1 = 0;
	pwm2 = 0;

	PWMn_Update(PCA0,pwm0);
	PWMn_Update(PCA1,pwm1);
	//PWMn_Update(PCA2,pwm2);

	CR    = 1;	// 运行PCA定时器
	//	EA = 1;
	P2M1 &= ~(0xe0);	//P2.7 P2.6 P2.5 设置为推挽输出
	P2M0 |=  (0xe0);
}
//========================================================================
// 函数: void  delay_ms(u8 ms)
// 描述: 延时函数。
// 参数: ms,要延时的ms数, 这里只支持1~255ms. 自动适应主时钟.
//========================================================================
void  delay_ms(u16 ms)
{
     unsigned int i;
	 do{
	      i = MAIN_Fosc / 13000;
		  while(--i)	;
     }while(--ms);
}


//========================================================================
// 函数: void PWMn_SetHighReg(unsigned int high)
// 描述: 更新占空比数据。
// 参数: high:高电位周期 0-255
//========================================================================
void PWMn_Update(u8 PCA_id, u16 pwm)
{
	if(PCA_id == PCA0)
	{
		CR = 0;						//停止PCA一会， 一般不会影响PWM。
		CCAP0H = CCAP0L=0xff-pwm;
		CR = 1;						//启动PCA。
	}
	else if(PCA_id == PCA1)
	{
		CR = 0;						//停止PCA。
		CCAP1H = CCAP1L=0xff-pwm;
		CR = 1;						//启动PCA。
	}
	else if(PCA_id == PCA2)
	{
		CR = 0;						//停止PCA。
		CCAP2H = CCAP2L=0xff-pwm;
		CR = 1;						//启动PCA。
	}
}



/*
#define		PWM_DUTY		6000		//定义PWM的周期，数值为PCA所选择的时钟脉冲个数。
#define		PWM_HIGH_MIN	80		//限制PWM输出的最小占空比, 避免中断里重装参数时间不够。
#define		PWM_HIGH_MAX	(PWM_DUTY - PWM_HIGH_MIN)	//限制PWM输出的最大占空比。
*/
void	pwm_left(u8 highpwm)//最小值PWM_HIGH_MIN  最大值PWM_HIGH_MAX
{
	PWMn_Update(PCA1,highpwm);
}
void	pwm_right(u8 highpwm)
{
	PWMn_Update(PCA0,highpwm);
}



