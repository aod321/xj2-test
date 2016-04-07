#include "pwm.h"
extern u8	pwm0,pwm1,pwm2;

//========================================================================
// ����: void	PCA_Init(void)
// ����: PCA��ʼ������.
//========================================================================
void	PCA_Init(void)
{
	CR = 0;
	AUXR1 = (AUXR1 & ~(3<<4)) | PCA_P24_P25_P26_P27;	//�л�IO��
	//��PCA/PWM�л���P24(ECI) P25(CCP0) P26(CCP1) P27(CCP2)
	CCON = 0; //��ʼ��PCA���ƼĴ���
	
	PCA_PWM0 = (PCA_Mode_Capture | ENABLE);	//8λģʽ
	PCA_PWM1 = (PCA_Mode_Capture | ENABLE);
	PCA_PWM2 = (PCA_Mode_Capture | DISABLE);
	
	CCAPM0 = 0x42; //PCAģ��0Ϊ8λPWMģʽ
	CCAPM1 = 0x42; //PCAģ��1Ϊ8λPWMģʽ
	CCAPM2 = 0x42; //PCAģ��2Ϊ8λPWMģʽ

	CH = 0;
	CL = 0;
	//ѡ��ʱ��Դ
	CMOD = 0x02; //����PCAʱ��Դ 1T

	pwm0 = 0;	//��PWMһ����ֵ
	pwm1 = 0;
	pwm2 = 0;

	PWMn_Update(PCA0,pwm0);
	PWMn_Update(PCA1,pwm1);
	//PWMn_Update(PCA2,pwm2);

	CR    = 1;	// ����PCA��ʱ��
	//	EA = 1;
	P2M1 &= ~(0xe0);	//P2.7 P2.6 P2.5 ����Ϊ�������
	P2M0 |=  (0xe0);
}
//========================================================================
// ����: void  delay_ms(u8 ms)
// ����: ��ʱ������
// ����: ms,Ҫ��ʱ��ms��, ����ֻ֧��1~255ms. �Զ���Ӧ��ʱ��.
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
// ����: void PWMn_SetHighReg(unsigned int high)
// ����: ����ռ�ձ����ݡ�
// ����: high:�ߵ�λ���� 0-255
//========================================================================
void PWMn_Update(u8 PCA_id, u16 pwm)
{
	if(PCA_id == PCA0)
	{
		CR = 0;						//ֹͣPCAһ�ᣬ һ�㲻��Ӱ��PWM��
		CCAP0H = CCAP0L=0xff-pwm;
		CR = 1;						//����PCA��
	}
	else if(PCA_id == PCA1)
	{
		CR = 0;						//ֹͣPCA��
		CCAP1H = CCAP1L=0xff-pwm;
		CR = 1;						//����PCA��
	}
	else if(PCA_id == PCA2)
	{
		CR = 0;						//ֹͣPCA��
		CCAP2H = CCAP2L=0xff-pwm;
		CR = 1;						//����PCA��
	}
}



/*
#define		PWM_DUTY		6000		//����PWM�����ڣ���ֵΪPCA��ѡ���ʱ�����������
#define		PWM_HIGH_MIN	80		//����PWM�������Сռ�ձ�, �����ж�����װ����ʱ�䲻����
#define		PWM_HIGH_MAX	(PWM_DUTY - PWM_HIGH_MIN)	//����PWM��������ռ�ձȡ�
*/
void	pwm_left(u8 highpwm)//��СֵPWM_HIGH_MIN  ���ֵPWM_HIGH_MAX
{
	PWMn_Update(PCA1,highpwm);
}
void	pwm_right(u8 highpwm)
{
	PWMn_Update(PCA0,highpwm);
}



