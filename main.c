#include "pwm.h"
#include "timer.h"
#include "Exti.h"
#include "Lcd.h"
#include "config.h"

#define speed 150//������ʻ�ٶ� 0-255
#define TLIN P0&0x03//�����ź��ߣ�3·��ȡP0�ĵ�3λ P00����

sbit k =P1^6;//������⿪������˿�
unsigned char g;//����g
 
//���ģ��ܽ�
//���ҵ���ź��߽�P25 pwm0
//�������ź��߽�P25 pwm1

//sbit led1 = P0^4;  //ѭ��ģ��ܽ�
//sbit led2 = P0^5;
//sbit led3 = P0^6;
//sbit led4 = P0^7;
//sbit led5 = P2^4;
//sbit led6 = P2^5;
//sbit led7 = P2^0;
//sbit led8 = P2^3;
extern u8 time_counter=0;//timer0 ����
extern u8 line_counter=0;//���� ����
extern u8 time_counter1=0;//timer1 ����
extern bit update_flag=0;//timer1 �������

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
		for(;temp!=0x00;temp=TLIN)//???????
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
		for(;temp!=0x00;temp=TLIN)//???????
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
	if(P32==1)		//�м�Ƽ�⵽						
	{
		pwm_right(0);								//��ת
		delay_ms(1500);
		forward();									//�ָ�
	
	}
	switch(TLIN)
	{
		//û��⵽����ʱ��ֱ��
		case 0x00:    forward(); 									break;
		
		//�ұ߼�⵽����ʱ,��ת
		case 0x01:  adjust_left(); 								break;
		
		//��߼�⵽����ʱ����ת
		case 0x02: 		adjust_right(); 						break;
				
		//������
		case 0x03: 		 forward(); 								break;
		
//
		default:  break;
	}
	
					Line_Count();

}

void Line_Count()						//����������
{
		

	if(update_flag==1)						//��ʱ100*10us��
		{
					update_flag=0;						//���λ���

				if(line_counter <=1)				//�����ʱ����û�еڶ�����
				{
					line_counter=0;						//�����������		
					TR0=0;										//�رռ�ʱ��
					
				}
		}

		if(line_counter >=3)						//������־��
		{
			
		}
		
		
}

/*************************������***********************************/
main()
{ 
	char dis_code[10]={"---cm"};
	Initialize_LCD();// init LCD1602
	PCA_Init();//pwm��ʼ��
	Timer_config();
	EXTI_config();
	EA=1;

	check();//��ʼ�����ǰ��С��
	forward(); //ֱ��

	ClearLine(1);									//LCDɾ��
	ClearLine(2);
		
	//������ 1-255
	delay_ms(200);
PutString(1,1,"Line_counter:");				//LCD��ʾ		
		WriteChar(1,7,line_counter);
		PutString(2,1,dis_code);
//		PutString(2,7,"mode:");
	while(1)
	{ 
		Inline();
	//	pwm_left(speed);
	//	pwm_right(0);

	 }
 }


