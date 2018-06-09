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
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;
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
	Key_GPIO_Config();	//��ѯ
#endif
}



int main(void)
{	
	float Angle[4];
	
	USART1_Config();	     			//��ʼ������1��������ͨѶ
	NVIC_Configuration();				//�������ȼ�
	USART2_Initialise( 38400 );	//����2���ڵ���
	USART3_Config();						//��ʼ������3��������ģ��
	
	init_Queue(&q); 		
	
	TIM6_TIM_NVIC_Config();			//��ʼ����ʱ��6
	TIM6_TIM_Mode_Config();			//��������ģ��
	
	UltrasonicWave_Configuration();
	GENERAL_TIM_Init();
	TIM2_Init();
	
	PeriphInit();	//�����ʼ��
	printf("\nϵͳ��ʼ�����......\n");

	for(;;)
	{
p_err_cym("key4.current_mode = %d\nkey4.key_rank[MODE_VOLUME] = %d\nkey4.key_rank[MODE_FREQUENCY] = %d\nkey4.key_rank[MODE_DISTANCE] = %d",
			key4.current_mode, key4.key_rank[MODE_VOLUME], key4.key_rank[MODE_FREQUENCY], key4.key_rank[MODE_DISTANCE]);

		MPU6050Triaxial(Angle);	//������
		blind_falled();		//ä���Ƿ�ˤ��		
		
#if BREAK_EXTI_OPEN
#else
		KeyPolling();
#endif
		
		Deal_Data();
		
//		mdelay(50);
	}
}

/*********************************************END OF FILE**********************/
