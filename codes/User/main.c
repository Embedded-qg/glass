/**
  ******************************************************************************
  * @file    main.c
  * @author  chzh
  * @version V1.0
  * @date    2018-05-19
  * @brief   ���ܱ����۾�
  ******************************************************************************
  */ 
 
 
#include "stm32f10x.h"
#include "bsp_usart1.h"
#include "queue.h"
#include "mp3.h"
#include "stm32f10x_it.h"
#include "./systick/bsp_SysTick.h"
#include "./i2c/bsp_i2c.h"
#include "./exti/bsp_exti.h" 
#include "./MPU6050/mpu6050/mpu6050.h"
#include "bsp_key.h"
#include "bsp_GeneralTim.h"
#include "UltrasonicWave.h"
#include "debug.h"

LinkQueue q;
extern int flag_FALLING;	//ä��ˤ����־ =1��ʾˤ���� =0��ʾ����
int flag_SendText=0;	//�ж��Ƿ񷢽�����Ϣ��ͨ����������־ =1��ʾ��������Ϣ�� =0��ʾ����������Ϣ


//#define BLIND_SAFE 1
//#define BLIND_UNSAFE 0
/**
  * @brief  ��ʼ������
  * @param  ��  
  * @retval ��
  */
static void PeriphInit()
{
	//�δ�ʱ�ӳ�ʼ��
	SysTick_Init();
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;
	//MPU6050�ж�����
	EXTI_Pxy_Config();
	//I2C��ʼ��
	I2C_Bus_Init();
	//MPU6050��ʼ��
	MPU6050Config();
	//������ʼ��
//	Key_GPIO_Config();	//��ѯ
	EXTI_Key_Config();	//�ж�
}

/**
  * @brief  �ж��Ƿ���Ҫͨ����������Σ����Ϣ
  * @param  ��  
  * @retval ��
  */
static void blind_falled()
{
	if(1==flag_FALLING)	//ä��ˤ��
	{
			mdelay(1000);
			if(1==flag_FALLING){		//�����ȫ������û�б����£���ôflag_FALLING��־λ����Ϊ1�����Է���������Ϣ
				
				USART_SendData(USART1, '1');		//����Σ����Ϣ
				while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
					continue;		
				
				printf("\nˤ��һ��ʱ���ȫ��δ�����£��ѷ�����Ϣ1����������ģ��");
				flag_FALLING=0;
			}
			
			else	//ä����ˤ��
			{
				printf("ä��ˤ����ȫ���Ѿ�������");		
			}
	}
	else
		return;
}

/**
  * @brief  ��������ģ��
  * @param  ��  
  * @retval ��
  */
static void key_module()
{
	int key_n;
	key_n=KeyPolling();	//����ģ��
	
	switch(key_n)
	{
		case KEY_MODE:	//ģʽѡ��
			
			break;
		case KEY_BACK:	//������һ��ģʽ
			
			break;
		case KEY_ADD:	//�Ӻ�
			
			break;
		case KEY_SUB:	//����

			break;
		case KEY_SAFE:	//��ȫ

			break;
		default:
			break;
	}
	
}


/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	float Angle[4];
	
	USART1_Config();	     			//��ʼ������1��������ͨѶ
	NVIC_Configuration();				//�������ȼ�
	USART2_Initialise( 38400 );	//����2���ڵ���
	USART3_Config();						//��ʼ������3��������ģ��
	
	init_Queue(&q); 		
	
	UltrasonicWave_Configuration();
	GENERAL_TIM_Init();
	TIM2_Init();
	
	PeriphInit();	//�����ʼ��
	printf("\nϵͳ��ʼ�����......\n");

	for(;;)
	{
		MPU6050Triaxial(Angle);	//������
		blind_falled();		//ä���Ƿ�ˤ��
//		key_module();		//����ģ��

		Deal_Data();
		
//		mdelay(50);
	}
}
/*********************************************END OF FILE**********************/
