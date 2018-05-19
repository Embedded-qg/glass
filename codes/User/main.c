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
LinkQueue q;
/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	USART1_Config();	     			//��ʼ������1��������ͨѶ
	NVIC_Configuration();				//�������ȼ�
	USART2_Initialise( 38400 );	//����2���ڵ���
	init_Queue(&q); 						
	MP3_GPIO_Config();
	MP3Run(1);									//�����������
	for(;;)
	{
		Deal_Data();
	}
}
/*********************************************END OF FILE**********************/
