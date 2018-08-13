#include "bsp_mpu6050.h"
#include "stm32f10x.h"
#include "bsp_usart1.h"
#include "stm32f10x_it.h"
#include "./systick/bsp_SysTick.h"
#include "./i2c/bsp_i2c.h"
#include "./exti/bsp_exti.h" 
#include "./MPU6050/mpu6050/mpu6050.h"
#include "bsp_key.h"
#include "mp3.h"


extern int flag_FALLING;	//ä��ˤ����־ =1��ʾˤ���� =0��ʾ����

/**
  * @brief  �ж��Ƿ���Ҫͨ����������Σ����Ϣ
  * @param  ��  
  * @retval ��
  */
void blind_falled()
{
	int i;
	if(1==flag_FALLING)	//ä��ˤ��
	{
			for(i=9;i>0;i--)   //��ʱ10��
			{
				mdelay(1000);	
				USART3_Send_String(AutoAlarm,sizeof(AutoAlarm));
				printf("���ţ��Ƿ���Ҫ���������Ϣ\r\n");
				if(flag_FALLING == 0)
					return ;
			}	
	}
}

void SendHelp(void)
{
			if(1==flag_FALLING){		//�����ȫ������û�б����£���ôflag_FALLING��־λ����Ϊ1�����Է���������Ϣ
				
			USART_SendData(USART1, '1');		//����Σ����Ϣ
			while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
				continue;		
			USART3_Send_String(Alarm,sizeof(Alarm));
			printf("\nˤ��һ��ʱ���ȫ��δ�����£��ѷ�����Ϣ1����������ģ��");
			flag_FALLING=0;
		}
}

/**
  * @brief  �ĸ���������ģ��
  * @param  ��  
  * @retval ��
  */
void key_module()
{
//	int key_n;
//	key_n=KeyPolling();	//����ģ��
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
	
}
