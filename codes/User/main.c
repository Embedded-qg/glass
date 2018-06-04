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
#include "bsp_GeneralTim.h"
#include "UltrasonicWave.h"
#include "debug.h"

LinkQueue q;
/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	USART1_Config();	     						//��ʼ������1��������ͨѶ
	NVIC_Configuration();							//�������ȼ�
	USART2_Initialise( 38400 );				//����2���ڵ���
	USART3_Config();									//��ʼ������3��������ģ��
	
	UltrasonicWave_Configuration();
	GENERAL_TIM_Init();
	TIM2_Init();
	init_Queue(&q); 						
	printf("start\r\n");
//	USART3_Send_String(NorthEast,sizeof(NorthEast));
	for(;;)
	{
		Deal_Data();
	}
}
/*********************************************END OF FILE**********************/
