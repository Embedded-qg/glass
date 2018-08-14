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
extern int flag_volume; 
/**
  * @brief  �ж��Ƿ���Ҫͨ����������Σ����Ϣ
  * @param  ��  
  * @retval ��
  */
void blind_falled(float Angle[4])
{
	int i;
	if(1==flag_FALLING)	//ä��ˤ��
	{ 
		flag_volume=0;
			for(i=9;i>0;i--)   //��ʱ10��
			{
				mdelay(1000);	
				USART3_Send_String(AutoAlarm,sizeof(AutoAlarm));
				printf("���ţ��Ƿ���Ҫ���������Ϣ,i == %d\r\n",i);
				if(flag_FALLING == 0)
				{
						Filter(Angle);
						return ;
				}
					
			}	
	}
}

void SendHelp(void)
{
			if(1==flag_FALLING){		//�����ȫ������û�б����£���ôflag_FALLING��־λ����Ϊ1�����Է���������Ϣ
				
			USART_SendData(USART1, '2');		//����Σ����Ϣ
			while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
				continue;	
			flag_volume=0;
			USART3_Send_String(Alarm,sizeof(Alarm));
			printf("�������Զ���������\r\n");
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
