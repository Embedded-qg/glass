/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   �����жϽ��ղ���
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� iSO STM32 ������ 
  * ��̳    :http://www.chuxue123.com
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */ 
 
 
#include "stm32f10x.h"
#include "bsp_usart1.h"
#include"queue.h"
LinkQueue q;
/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
// int i;
	USART1_Config();	
	NVIC_Configuration();

	USART2_Initialise( 38400 );

	init_Queue(&q); 
	
	for(;;)
	{
		Deal_Data();
	}
}
/*********************************************END OF FILE**********************/
