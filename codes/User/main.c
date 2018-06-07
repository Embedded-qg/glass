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
#include "UltraConfig.h"
#include "UltrasonicWave.h"
#include "debug.h"
#include "bsp_mpu6050.h"

LinkQueue q;
extern key_four key4;


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

///**
//<<<<<<< HEAD
//  * @brief  �ж��Ƿ���Ҫͨ����������Σ����Ϣ
//  * @param  ��  
//  * @retval ��
//  */
//static void blind_falled()
//{
//	if(1==flag_FALLING)	//ä��ˤ��
//	{
//		while(1)	//��ȫ�������»��߳�ʱʱ �˳�
//		{
//			mdelay(20);
////			KeyPolling();	//����
//			if(0==flag_FALLING)	//ä����ˤ��
//			{
//				printf("flag_FALLING=0");
//				break;			
//			}
//			else
//			{
//				flag_SendText=1;	//��Ҫ����Σ���ź�
//				printf("flag_SendText=1");
//				break;
//			}
//		}
//	}
//	else
//		return;
//}

///**
//  * @brief  ��������ģ��
//  * @param  ��  
//  * @retval ��
//  */
//static void key_module()
//{
//	int key_n;
////	key_n=KeyPolling();	//����ģ��
//	
//	switch(key_n)
//	{
//		case KEY_MODE:	//ģʽѡ��
//			
//			break;
//		case KEY_BACK:	//������һ��ģʽ
//			
//			break;
//		case KEY_ADD:	//�Ӻ�
//			
//			break;
//		case KEY_SUB:	//����

//			break;
//		case KEY_SAFE:	//��ȫ

//			break;
//		default:
//			break;
//	}
//	
//}


/**
=======
>>>>>>> 4109c278e71f77f348e4a77a8b76cd1275b7e467
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	float Angle[4];
	key4.current_mode=0;	//�����ṹ��ʼ��
	key4.key_rank[0]=0,key4.key_rank[1]=0,key4.key_rank[2]=0;
	key4.max_mode=3;
	key4.max_rank=4;
	key4.min_mode=0;
	key4.min_rank=0;
	
	
	USART1_Config();	     			//��ʼ������1��������ͨѶ
	NVIC_Configuration();				//�������ȼ�
	USART2_Initialise( 38400 );	//����2���ڵ���
	USART3_Config();						//��ʼ������3��������ģ��
	
	init_Queue(&q); 		
	
	UltrasonicWave_Configuration();
	GENERAL_TIM_Init();
	TIM2_Init();
	
//	PeriphInit();	//�����ʼ��
	printf("\nϵͳ��ʼ�����......\n");

	for(;;)
	{

//		MPU6050Triaxial(Angle);	//������
//		blind_falled();		//ä���Ƿ�ˤ��
//		key_module();		//����ģ��

		Deal_Data();
		
//		mdelay(50);
	}
}

/*********************************************END OF FILE**********************/
