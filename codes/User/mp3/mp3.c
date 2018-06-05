/**
  ******************************************************************************
  * @file    mp3.c
  * @author  chzh
  * @version V1.0
  * @date    2018-05-19
  * @brief   mp3ģ�麯��
  ******************************************************************************
  */ 
#include "mp3.h"

 /**
  * @brief  ��ʼ������MP3��IO
  * @param  ��
  * @retval ��
  */
void MP3_GPIO_Config(void)
{		
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*����MP3��ص�GPIO����ʱ��*/
		RCC_APB2PeriphClockCmd( MP31_GPIO_CLK | MP32_GPIO_CLK | MP33_GPIO_CLK| MP34_GPIO_CLK, ENABLE);
		/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure.GPIO_Pin = MP31_GPIO_PIN;	

		/*��������ģʽΪͨ���������*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*������������Ϊ50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*���ÿ⺯������ʼ��GPIO*/
		GPIO_Init(MP31_GPIO_PORT, &GPIO_InitStructure);	
		
		/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure.GPIO_Pin = MP32_GPIO_PIN;

		/*���ÿ⺯������ʼ��GPIO*/
		GPIO_Init(MP32_GPIO_PORT, &GPIO_InitStructure);
		
		/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure.GPIO_Pin = MP33_GPIO_PIN;

		/*���ÿ⺯������ʼ��GPIOF*/
		GPIO_Init(MP33_GPIO_PORT, &GPIO_InitStructure);
		
				/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure.GPIO_Pin = MP34_GPIO_PIN;

		/*���ÿ⺯������ʼ��GPIOF*/
		GPIO_Init(MP34_GPIO_PORT, &GPIO_InitStructure);

		/* �ر�����MP3��	*/
		GPIO_SetBits(MP31_GPIO_PORT, MP31_GPIO_PIN);
		
		/* �ر�����MP3��	*/
		GPIO_SetBits(MP32_GPIO_PORT, MP32_GPIO_PIN);	 
    
    /* �ر�����MP3��	*/
		GPIO_SetBits(MP33_GPIO_PORT, MP33_GPIO_PIN);
		
		    /* �ر�����MP3��	*/
		GPIO_SetBits(MP34_GPIO_PORT, MP34_GPIO_PIN);
}

void delay(int x) //��ʱX����
{
	int y,z;
	for(z=x;z>0;z--)
	for(y=110;y>0;y--);
}

/*
	1��0111
	2��1011
	3��0011
	4��1101
	5��0101
	6��1001
	7��0001
	8��1110
	9��0110
*/



int MP3Run(int num)
{	
	switch(num)
	{
		case 1:  //����
			MP31_ON;
			delay(500);
			MP31_OFF;
		break;
		case 2:  //������
			MP32_ON;
			delay(500);
			MP32_OFF;
		break;
		case 3:	//����
			MP31_ON;
			MP32_ON;
			delay(500);
			MP31_OFF;
			MP32_OFF;
		break;
		case 4:	//���Ϸ�
			MP33_ON;
			delay(500);
			MP33_OFF;
		break;
		case 5:	//�Ϸ�
			MP31_ON;
			MP33_ON;
			delay(500);
			MP31_OFF;
		MP33_OFF;
		break;
		case 6:	//������
			MP33_ON;
			MP32_ON;
			delay(500);
			MP33_OFF;
			MP32_OFF;
		break;
		case 7:	//����
			MP31_ON;
			MP32_ON;
			MP33_ON;
			delay(500);
			MP31_OFF;
			MP32_OFF;
			MP33_OFF
		break;
		case 8:	//���Ϸ�
			MP34_ON;
			delay(500);
			MP34_OFF;	
		break;
		case 9:	//ǰ�����ϰ���
			MP31_ON;
			MP34_ON;
			delay(500);
			MP31_OFF;
			MP34_OFF;
		break;
		
	}
	//1--����
//	MP31_ON;
//	delay(500);
//	MP31_OFF;
	
	//2---������
//	MP32_ON;
//	delay(500);
//	MP32_OFF;
	
	//3--����
//	MP31_ON;
//	MP32_ON;
//	delay(500);
//	MP31_OFF;
//	MP32_OFF;
//	
//	//4----���Ϸ�
//	MP33_ON;
//	delay(500);
//	MP33_OFF;
//	
//	//5--�Ϸ�
//	MP31_ON;
//	MP33_ON;
//	delay(500);
//	MP31_OFF;
//	MP33_OFF;
//	
//	//6--������
//	MP33_ON;
//	MP32_ON;
//	delay(500);
//	MP33_OFF;
//	MP32_OFF;
//	
//	//7---����
//		MP31_ON;
//	MP32_ON;
//	MP33_ON;
//	delay(500);
//	MP31_OFF;
//	MP32_OFF;
//	MP33_OFF
//	
//	//8--���Ϸ�
//	MP34_ON;
//	delay(500);
//	MP34_OFF;	
//	
//	//9--ǰ�����ϰ���
//	MP31_ON;
//	MP34_ON;
//	delay(500);
//	MP31_OFF;
//	MP34_OFF;
	


    
}

