#ifndef _PWM_H_
#define _PWM_H_
#include"config.h"


/*************	����˵��	**************

���3·9~16λPWM�źš�
Ĭ�����ţ�
pwm0-P25,pwm1-P26,pwm2-P27

//PWMn_init()�����н���ѡ��������

******************************************/

/***************************�û��궨��*******************************************************/
//#define 	MAIN_Fosc		24000000UL	//������ʱ��
//#define MAIN_Fosc		22118400L	//������ʱ��
//#define MAIN_Fosc		12000000L	//������ʱ��
//#define MAIN_Fosc		11059200L	//������ʱ��
//#define MAIN_Fosc		 5529600L	//������ʱ��
//#define MAIN_Fosc		24000000L	//������ʱ��
//config.h�ж���

/********************************************************************************************/

#define	PCA0			0
#define	PCA1			1
#define	PCA2			2
#define	PCA_Counter		3
#define	PCA_P12_P11_P10_P37	(0<<4)
#define	PCA_P34_P35_P36_P37	(1<<4)
#define	PCA_P24_P25_P26_P27	(2<<4)////��PCA/PWM�л���P24(ECI) P25(CCP0) P26(CCP1) P27(CCP2)
#define	PCA_Mode_PWM				0x42
#define	PCA_Mode_Capture			0
#define	PCA_Mode_SoftTimer			0x48
#define	PCA_Mode_HighPulseOutput	0x4c
#define	PCA_Clock_1T	(4<<1)
#define	PCA_Clock_2T	(1<<1)
#define	PCA_Clock_4T	(5<<1)
#define	PCA_Clock_6T	(6<<1)
#define	PCA_Clock_8T	(7<<1)
#define	PCA_Clock_12T	(0<<1)
#define	PCA_Clock_Timer0_OF	(2<<1)
#define	PCA_Clock_ECI	(3<<1)
#define	PCA_Rise_Active	(1<<5)
#define	PCA_Fall_Active	(1<<4)
#define	PCA_PWM_8bit	(0<<6)
#define	PCA_PWM_7bit	(1<<6)
#define	PCA_PWM_6bit	(2<<6)

//#define		ENABLE		1
//#define		DISABLE		0



//================================================================

extern u8	pwm0,pwm1,pwm2;

void	PWMn_Update(u8 PCA_id, u16 pwm);
void	PCA_Init(void);
void	delay_ms(u8 ms);
void	pwm_left(u8 highpwm);
void	pwm_right(u8 highpwm);

#endif