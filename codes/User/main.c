/**
  ******************************************************************************
  * @file    main.c
  * @author  chzh
  * @version V1.0
  * @date    2018-10-12
  * @brief   ���ܱ����۾�
  ******************************************************************************
  */ 
 
 
#include "stm32f10x.h"
#include "bsp_usart1.h"
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
#include "mpu6050.h"

extern key_four key4;
extern int time;

//key4.current_mode=0;	//�����ṹ��ʼ��
//key4.key_rank[MODE_VOLUME]=0,key4.key_rank[MODE_FREQUENCY]=0,key4.key_rank[MODE_DISTANCE]=0;
//key4.max_mode=3;
//key4.max_rank=4;
//key4.min_mode=0;
//key4.min_rank=0;


/**
  * @brief  ��ʼ������
  * @param  ��  
  * @retval ��
  */
static void PeriphInit()
{
	//�δ�ʱ�ӳ�ʼ��
	SysTick_Init();
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;    //ʹ�ܵδ�ʱ��
	//MPU6050�ж�����
	EXTI_Pxy_Config();
	//I2C��ʼ��
	I2C_Bus_Init();
	//MPU6050��ʼ��
	MPU6050Config();
	//������ʼ��
#if BREAK_EXTI_OPEN
	EXTI_Key_Config();	//�ж�
#else
	EXTI_Key_Config();
	Key_GPIO_Config();	//��ѯ
#endif
}

int main(void)
{	
	float Angle[4];             //����3�����ݵĴ���

	USART_Config();	     			   //��ʼ������,����1��������ͨѶ������2���ڵ��ԡ���ʼ������3��������ģ��

	NVIC_Configuration();				//���ô������ȼ������ȼ�����ʹ��NVIC_PriorityGroup_2
	
	TIM6_Config();              //��ʼ����ʱ��6,���ȼ�����ʹ��NVIC_PriorityGroup_2

// 	UltrasonicWave_Configuration();
//	GENERAL_TIM_Init();
//	TIM2_Init();
	
	PeriphInit();              	//����ģ���Լ���ť�ĳ�ʼ��
	printf("\nϵͳ��ʼ�����......\n");

	for(;;)
	{	

		
//		MPU6050Triaxial(Angle);		//������
		
		blind_falled();						//ä���Ƿ�ˤ��		
//		Filter(Angle);
//		SendHelp();
//#if BREAK_EXTI_OPEN
//#else
		KeyPolling();

//#endif

	}
}

/*********************************************END OF FILE**********************/
