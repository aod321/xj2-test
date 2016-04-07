#include "config.h"
#include "pwm.h"
#include "timer.h"
#include "Exti.h"
#define speed 150//������ʻ�ٶ� 0-255
#define TLIN P0&0x07//�����ź��ߣ�3·��ȡP0�ĵ�3λ P00����

sbit k =P1^6;//������⿪������˿�
unsigned char g;//����g
 
//���ģ��ܽ�
//���ҵ���ź��߽�P25 pwm0
//�������ź��߽�P25 pwm1

sbit led1 = P0^4;  //ѭ��ģ��ܽ�
sbit led2 = P0^5;
sbit led3 = P0^6;
sbit led4 = P0^7;
sbit led5 = P2^4;
sbit led6 = P2^5;
sbit led7 = P2^0;
sbit led8 = P2^3;
u8 time_counter=0;//timer0 ����
u8 line_counter=0;//���� ����
u8 time_counter1=0;//timer1 ����

//ѹ�߱�־λ
bit L1=0;//���Ҳ��־λ
bit L2=0;
bit L3=0;
bit L4=0;//������־λ

u8 flag=0;


extern u8	pwm0,pwm1,pwm2;

/***************************��ǰ��*****************************/
void forward() 
{
		pwm_left(speed);
		pwm_right(speed);
}
/**************************ֹͣ*****************************/
void stop() {pwm_left(0);	pwm_right(0);}  

/*��ת90�ȣ��Զ��ָ�*/
void turn_left()
{
	//���Բ����޸�ת��ģʽ
		pwm_left(0);
		pwm_right(speed);
	//���Բ�����1-255
		delay_ms(2000);
		pwm_left(speed);
		pwm_right(speed);
}

/*��ת90�ȣ��Զ��ָ�*/
void turn_right()
{
	//���Բ����޸�ת��ģʽ
		pwm_left(speed);
		pwm_right(0);
	//���Բ�����0-65536
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
//��ת�ɵ����Զ��ָ�
//t1:������ת״̬ʱ�� 1-255
//t2:�ص�ʱ�� 1-255
*************************/
void turn_leftn(u16 t1,u16 t2)
{
	//���Բ����޸�ת��ģʽ
		pwm_left(0);
		pwm_right(speed);
	//:������ת״̬ʱ��
		delay_ms(t1);
		//�ص�
		//�ص�ʱpwm����Ҫ���㡢����
		pwm_left(speed);
		pwm_right(0);
			//�ص�ʱ��
		delay_ms(t2);
		//�ָ�ǰ��
		pwm_left(speed);
		pwm_right(speed);
}

/************************
//��ת�ɵ���֧��ת���ص�
//t1:������ת״̬ʱ�� 1-255
//t2:�ص�ʱ�� 1-255
*************************/
void turn_rightn(u16 t1,u16 t2)
{
	
	//���Բ����޸�ת��ģʽ
		pwm_left(speed);
		pwm_right(0);
	//������ת״̬ʱ��
		delay_ms(t1);
		
		//�ص�
		//�ص�ʱpwm����Ҫ���㡢����
		pwm_left(0);
		pwm_right(speed);
			//�ص�ʱ��
		delay_ms(t2);
		
		//�ָ�ǰ��
		pwm_left(speed);
		pwm_right(speed);

}

/*****************************���ǰ���Ƿ���С��*******************************/

void check()
{
	if(k==1)
		g=1;
	else 
		g=0;
}


void Inline()		//�������źţ���⵽����ʱ��Ϊ�ߵ�ƽ��ƽʱ�͵�ƽ
{
	switch(TLIN)
	{
		//û��⵽����ʱ��ֱ��
		case 0x00:    forward(); 									break;
		
		//���ұ߼�⵽����ʱ,��ת
		case 0x01:  adjust_left(); 								break;
		
		//���м��⵽����ʱ������ֱ��
		case 0x02: 		line_counter++; 														break;
				
		//�м��Լ��ұ߼�⵽����ʱ
		case 0x03: 								  							break;
		
		//����߼�⵽����ʱ,��ת
		case 0x04:	adjust_right();							  break;
		//���м�δ��⵽����,����
		case 0x05:  															break;  
		
		//�м��Լ���߼�⵽����ʱ
		case 0x06: 															 break;	
		
		//ȫ����⵽����ʱ
		case 0x07:  		forward();							 break;
		default: break;
		
	}
		
}

/*************************������***********************************/
main()
{ 
	PCA_Init();//pwm��ʼ��
	Timer_config();
	EXTI_config();
	EA=1;
	check();//��ʼ�����ǰ��С��
	forward(); //ֱ��
	//������ 1-255
	delay_ms(200);
	while(1)
	{ 
		Inline();
	//	pwm_left(speed);
	//	pwm_right(0);

	 }
 }


