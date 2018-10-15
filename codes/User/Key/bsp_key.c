
#include "./key/bsp_key.h"  
#include "./usart/bsp_usart1.h"
#include "./systick/bsp_SysTick.h"
#include "mp3.h"
#include "UltrasonicWave.h"
extern int flag_volume;  
extern int flag_FALLING;
extern  int MODE_FLAG;       //1 ���� 0 Ƶ��
key_four key4 = {0, {1, 1, 1}, MAX_MODE, 4, 0, 0,0};

static void delay(int i)
{
	for(;i>0;i--);
}


/**
  * @brief  ���ð����õ���I/O��
  * @param  ��
  * @retval ��
  */
void Key_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*���������˿ڵ�ʱ��*/
	RCC_APB2PeriphClockCmd(KEY1_GPIO_CLK|KEY2_GPIO_CLK|KEY3_GPIO_CLK|KEY4_GPIO_CLK|KEY5_GPIO_CLK,ENABLE);
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//������������������Ϊ50MHz

	
	//ѡ�񰴼�������
	GPIO_InitStructure.GPIO_Pin = KEY1_GPIO_PIN; 					//K1
	// ���ð���������Ϊ��������
//		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//ʹ�ýṹ���ʼ������
	GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStructure);
	
	//ѡ�񰴼�������
	GPIO_InitStructure.GPIO_Pin = KEY2_GPIO_PIN; 					//K2
	//���ð���������Ϊ��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//ʹ�ýṹ���ʼ������
	GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStructure);	
	
		//ѡ�񰴼�������
	GPIO_InitStructure.GPIO_Pin = KEY3_GPIO_PIN; 					//K3
	//���ð���������Ϊ��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//ʹ�ýṹ���ʼ������
	GPIO_Init(KEY3_GPIO_PORT, &GPIO_InitStructure);	

	//ѡ�񰴼�������
	GPIO_InitStructure.GPIO_Pin = KEY4_GPIO_PIN; 					//K4
	//���ð���������Ϊ��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//ʹ�ýṹ���ʼ������
	GPIO_Init(KEY4_GPIO_PORT, &GPIO_InitStructure);	

	//ѡ�񰴼�������
	GPIO_InitStructure.GPIO_Pin = KEY5_GPIO_PIN; 					//K5
	//���ð���������Ϊ��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//ʹ�ýṹ���ʼ������
	GPIO_Init(KEY5_GPIO_PORT, &GPIO_InitStructure);	
}


#if 1         //����ʱ����ߵ�ƽ���ɿ�ʱ����͵�ƽ
//����ʱ����ߵ�ƽ���ɿ�ʱ����͵�ƽ
 /*
 * ��������Key_Scan
 * ����  ������Ƿ��а�������
 * ����  ��GPIOx��x ������ A��B��C��D���� E
 *		     GPIO_Pin������ȡ�Ķ˿�λ 	
 * ���  ��KEY_OFF(û���°���)��KEY_ON�����°�����
 */
static uint8_t Key_Scan_down(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{			
	/* ����Ƿ��а������� */
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_DOWN )  
	{	 
			delay(10);	
			if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_DOWN )  
			{
					while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_DOWN);	//�ȴ������ſ�
				//			printf("�ȴ������ͷ�\r\n"); 
					
					return TRUE;	 
			}
			else
			{
					return FALSE;
			}
	}
	else
	{
			return FALSE;
	}
}

#else
static uint8_t Key_Scan_down2(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{			
	/* ����Ƿ��а������� */
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_UP )  
	{	 
			delay(iTick);	
			if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_UP )  
			{
					while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_UP)	//�ȴ������ſ�
							continue; 
					
					return TRUE;	 
			}
			else
			{
					return FALSE;
			}
	}
	else
	{
			return FALSE;
	}
}
#endif


void KeyPolling(void)
{
//		if( Key_Scan_down2(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == TRUE  )
//		{
//				printf("\n���°�ȫ��!");
//			printf("LUNXUN\r\n");
//				if(0 == flag_FALLING)
//				{
//						USART_SendData(USART1, '2');		//����һ��������Ϣ
//						while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
//							continue;		
//						
//						printf("\tä�˲���ˤ��״̬��ֻ�Ƿ���һ���Ե�������Ϣ\r\n");
//				}
//				else
//					flag_FALLING=0;	//ä�˰�ȫ

//		}		

//////////////////////////////////////////////////////////////////////////////////////////

		if( Key_Scan_down(KEY2_GPIO_PORT,KEY2_GPIO_PIN) == TRUE  )
		{
									flag_volume=0;
				printf("\n���¹������ü�!\r\n");
			     key4.set_parameter = (key4.set_parameter+1) % SET_MAX;    //ѡ����һ��ģʽ
               if(SET_CLOSE == key4.set_parameter)	//��ǰ���ڲ��ɵ���ģʽ
				{
					printf("\t�˳�����\r\n");
					USART3_Send_String(ModeExit,sizeof(ModeExit));
					//���ţ��˳�����
				}		
				else if(SET_VOLUME == key4.set_parameter)	//��ǰ������������ģʽ
				{
					printf("\t��ǰ��������������,��ǰ�����ȼ�Ϊ��%d\r\n", key4.key_rank[MODE_VOLUME]);
					USART3_Send_String(AdjustVolume,sizeof(AdjustVolume));
					//���ţ���ǰ������������ģʽ
				}				
				else if(SET_FREQUENCY == key4.set_parameter)	//��ǰ����Ƶ�ʵ���ģʽ
				{
					printf("\t��ǰ����Ƶ�ʵ����У���ǰƵ�ʵȼ�Ϊ��%d\r\n", key4.key_rank[MODE_FREQUENCY]);			
					USART3_Send_String(AdjustRate,sizeof(AdjustRate));
					//���ţ���ǰ����Ƶ�ʵ���ģʽ
				}
				else if(SET_DISTANCE == key4.set_parameter)	//��ǰ���ھ������ģʽ
				{
					printf("\t��ǰ���ھ�������У���ǰ����ȼ�Ϊ��%d\r\n", key4.key_rank[MODE_DISTANCE]);
					USART3_Send_String(ModeDistance,sizeof(ModeDistance));
					//���ţ���ǰ���ھ������ģʽ
				}
				else 
				{
					printf("\nKEY2 error! key4.current_mode = %d", key4.current_mode);
				}

		}		

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	

		if( Key_Scan_down(KEY3_GPIO_PORT,KEY3_GPIO_PIN) == TRUE  )
		{
			flag_volume=0;
				printf("\n���½�����һ��ģʽ��!\r\n");
				key4.current_mode=(++key4.current_mode)%key4.max_mode;
				if(MODE_VOLUME == key4.current_mode)
				{
					MODE_FLAG=1;
					printf("\t��ǰģʽ����Ϊ��%s", "����ģʽ\r\n");
					USART3_Send_String(ModeVolume,sizeof(ModeVolume));
					//����
				}
				else if(MODE_FREQUENCY == key4.current_mode)
				{
					MODE_FLAG=0;
					printf("\t��ǰģʽ����Ϊ��%s", "Ƶ��ģʽ\r\n");
					USART3_Send_String(ModeRate,sizeof(ModeRate));
					//����
				}
				else if(MODE_SNAKE == key4.current_mode)
				{
					printf("\t��ǰģʽ����Ϊ��%s", "��ģʽ\r\n");
					MODE_FLAG = 2;
				}
		}		

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	

		if( Key_Scan_down(KEY4_GPIO_PORT,KEY4_GPIO_PIN) == TRUE )
		{
			flag_volume=0;
				printf("\n���¼Ӻż�!\r\n");
				if( SET_CLOSE == key4.set_parameter )
				{
					printf("��ѡ������ģʽ\r\n");
				}
				 else if(SET_VOLUME == key4.set_parameter)	//��ǰ������������ģʽ
				{
						if(MAX_RANK_VOLUME <= key4.key_rank[MODE_VOLUME])
						{
							printf("\t��ǰ��������Ϊ�ȼ���%d���ﵽ���ȼ������ٵ���\r\n", key4.key_rank[MODE_VOLUME]);				
								AddVolume();         //�������Ӻ�������
						}
						else
						{
							AddVolume();         //�������Ӻ�������
							++key4.key_rank[MODE_VOLUME];					
							printf("\t��ǰ��������Ϊ�ȼ���%d\r\n", key4.key_rank[MODE_VOLUME]);
						}

				}
				else if(SET_FREQUENCY == key4.set_parameter)	//��ǰ����Ƶ�ʵ���ģʽ
				{
						if(MAX_RANK_FREQUENCY == key4.key_rank[MODE_FREQUENCY])
						{
							printf("\t��ǰƵ�ʵ���Ϊ�ȼ���%d���ﵽ���ȼ������ٵ���\r\n", key4.key_rank[MODE_FREQUENCY]);			
						}
						else
						{
							AddRate();//Ƶ�����Ӻ�������
							++key4.key_rank[MODE_FREQUENCY];					
							printf("\t��ǰƵ�ʵ���Ϊ�ȼ���%d\r\n", key4.key_rank[MODE_FREQUENCY]);
						}

				}
				else if(SET_DISTANCE == key4.set_parameter)	//��ǰ���ھ������ģʽ
				{
						if(MAX_RANK_DISTANCE == key4.key_rank[MODE_DISTANCE])
						{			
							printf("\t��ǰ�������Ϊ�ȼ���%d���ﵽ���ȼ������ٵ���\r\n", key4.key_rank[MODE_DISTANCE]);
						}
						else
						{
							addDistance();             //�������Ӻ�������
							++key4.key_rank[MODE_DISTANCE];					
							printf("\t��ǰ�������Ϊ�ȼ���%d\r\n", key4.key_rank[MODE_DISTANCE]);
						}
				}
				else
				{
						printf("KEY4 error! key4.set_parameter = %d\r\n", key4.set_parameter);
				}

		}		

////////////////////////////////////////////////////////////////////////////////////////////////
		
		if( Key_Scan_down(KEY5_GPIO_PORT,KEY5_GPIO_PIN) == TRUE )
		{
			flag_volume=0;
				printf("\n���¼��ż�!\r\n");
				if( SET_CLOSE == key4.set_parameter )
				{
					printf("��ѡ������ģʽ\r\n");
				}		
				else if(SET_VOLUME == key4.set_parameter)	//��ǰ������������ģʽ
				{
						if(key4.min_rank == key4.key_rank[MODE_VOLUME])
						{
							printf("\t��ǰ��������Ϊ�ȼ���%d���ﵽ��С�ȼ������ٵ�С\r\n", key4.key_rank[MODE_VOLUME]);
							SubVolume();//�������ٺ�������
						}
						else
						{
							SubVolume();//�������ٺ�������
							--key4.key_rank[MODE_VOLUME];					
							printf("\t��ǰ��������Ϊ�ȼ���%d\r\n", key4.key_rank[MODE_VOLUME]);
						}				
				}
				else if(SET_FREQUENCY == key4.set_parameter)	//��ǰ����Ƶ�ʵ���ģʽ
				{
						if(key4.min_rank == key4.key_rank[MODE_FREQUENCY])
						{
							printf("\t��ǰƵ�ʵ���Ϊ�ȼ���%d���ﵽ��С�ȼ������ٵ�С\r\n", key4.key_rank[MODE_FREQUENCY]);
						}
						else
						{
							SubRate();//Ƶ�ʼ��ٺ�������
							--key4.key_rank[MODE_FREQUENCY];					
							printf("\t��ǰƵ�ʵ���Ϊ�ȼ���%d\r\n", key4.key_rank[MODE_FREQUENCY]);
						}
				}
				else if(SET_DISTANCE == key4.set_parameter)	//��ǰ���ھ������ģʽ
				{
					if(key4.min_rank == key4.key_rank[MODE_DISTANCE])
					{
						printf("\t��ǰ�������Ϊ�ȼ���%d���ﵽ��С�ȼ������ٵ�С\r\n", key4.key_rank[MODE_DISTANCE]);			
					}
					else
					{
						minusDistance();       //������ٺ�������
						--key4.key_rank[MODE_DISTANCE];					
						printf("\t��ǰ�������Ϊ�ȼ���%d\r\n", key4.key_rank[MODE_DISTANCE]);
					}
				}
				else
				{
					printf("KEY5 error! key4.set_parameter = %d\r\n", key4.set_parameter);
				}
		
	}		

}

static void NVIC_Configuration2(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* �����ж�Դ������1 */
  NVIC_InitStructure.NVIC_IRQChannel = KEY1_INT_EXTI_IRQ;
  /* ������ռ���ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* ���������ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* ʹ���ж�ͨ�� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void EXTI_Key_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	EXTI_InitTypeDef EXTI_InitStructure;

	/*��������GPIO�ڵ�ʱ��*/
	RCC_APB2PeriphClockCmd(KEY1_INT_GPIO_CLK,ENABLE);
												
	/* ���� NVIC �ж�*/
	NVIC_Configuration2();
	  
/*--------------------------KEY1����-----------------------------*/
	/* ѡ�񰴼��õ���GPIO */	
  GPIO_InitStructure.GPIO_Pin = KEY1_INT_GPIO_PIN;
  /* ����Ϊ�������� */	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(KEY1_INT_GPIO_PORT, &GPIO_InitStructure);

	/* ѡ��EXTI���ź�Դ */
  GPIO_EXTILineConfig(KEY1_INT_EXTI_PORTSOURCE, KEY1_INT_EXTI_PINSOURCE); 
  EXTI_InitStructure.EXTI_Line = KEY1_INT_EXTI_LINE;
	
	/* EXTIΪ�ж�ģʽ */
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	/* ���ж� */
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  /* ʹ���ж� */	
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}


void KEY1_IRQHandler(void)
{
  //ȷ���Ƿ������EXTI Line�ж�
	if(EXTI_GetITStatus(KEY1_INT_EXTI_LINE) != RESET) 
	{
//		EXTI_n(KEY1);
		delay(10);		
		if(GPIO_ReadInputDataBit(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == KEY_DOWN )  //����
		{
			if(0 == flag_FALLING)
			{
					USART_SendData(USART1, '2');		//����һ��������Ϣ
					while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
						continue;		
					flag_volume=0;
					USART3_Send_String(Alarm,sizeof(Alarm));
					printf("\t ���ţ������Ϣ�ѷ���r\n");
			}
			else
			{
					flag_FALLING=0;	//ä�˰�ȫ
					flag_volume=0;
					USART3_Send_String(QuitAlarm,sizeof(QuitAlarm));
					printf("\t ���˳��Զ�����ģʽ����ע�ⰲȫr\n");
			}

		//����жϱ�־λ
			delay(iCOUNT);			
		}			
//		EXTI_n_Open(KEY1);
		EXTI_ClearITPendingBit(KEY1_INT_EXTI_LINE); 
	}  
}






/*********************************************END OF FILE**********************/


