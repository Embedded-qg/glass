
#include "./key/bsp_key.h"  
#include "./usart/bsp_usart1.h"
#include "./systick/bsp_SysTick.h"
#include "mp3.h"
#include "UltrasonicWave.h"

extern int flag_FALLING;
key_four key4 = {0, {0, 0, 0}, 3, 4, 0, 0};

static void delay(int i)
{
	for(;i>0;i--);
}



#if BREAK_EXTI_OPEN

 /**
  * @brief  ����Ƕ�������жϿ�����NVIC
  * @param  ��
  * @retval ��
  */
static void NVIC_Configuration2(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* ����NVICΪ���ȼ���1 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  /* �����ж�Դ������1 */
  NVIC_InitStructure.NVIC_IRQChannel = KEY1_INT_EXTI_IRQ;
  /* ������ռ���ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* ���������ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* ʹ���ж�ͨ�� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

	  /* �����ж�Դ������2������ʹ������������� */  
  NVIC_InitStructure.NVIC_IRQChannel = KEY2_INT_EXTI_IRQ;
  NVIC_Init(&NVIC_InitStructure);

	  /* �����ж�Դ������3������ʹ������������� */  
  NVIC_InitStructure.NVIC_IRQChannel = KEY3_INT_EXTI_IRQ;
  NVIC_Init(&NVIC_InitStructure);

  /* �����ж�Դ������4������ʹ������������� */  
  NVIC_InitStructure.NVIC_IRQChannel = KEY4_INT_EXTI_IRQ;
  NVIC_Init(&NVIC_InitStructure);

  /* �����ж�Դ������5������ʹ������������� */  
  NVIC_InitStructure.NVIC_IRQChannel = KEY5_INT_EXTI_IRQ;
  NVIC_Init(&NVIC_InitStructure);

}

 /**
  * @brief  ���� IOΪEXTI�жϿڣ��������ж����ȼ�
  * @param  ��
  * @retval ��
  */
void EXTI_Key_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	EXTI_InitTypeDef EXTI_InitStructure;

	/*��������GPIO�ڵ�ʱ��*/
	RCC_APB2PeriphClockCmd(KEY1_INT_GPIO_CLK|KEY2_INT_GPIO_CLK|KEY3_INT_GPIO_CLK|KEY4_INT_GPIO_CLK|KEY5_INT_GPIO_CLK,ENABLE);
												
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
	/* �������ж� */
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  /* ʹ���ж� */	
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	
  /*--------------------------KEY2����-----------------------------*/
	/* ѡ�񰴼��õ���GPIO */	
  GPIO_InitStructure.GPIO_Pin = KEY2_INT_GPIO_PIN;
  /* ����Ϊ�������� */	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(KEY2_INT_GPIO_PORT, &GPIO_InitStructure);

	/* ѡ��EXTI���ź�Դ */
  GPIO_EXTILineConfig(KEY2_INT_EXTI_PORTSOURCE, KEY2_INT_EXTI_PINSOURCE); 
  EXTI_InitStructure.EXTI_Line = KEY2_INT_EXTI_LINE;
	
	/* EXTIΪ�ж�ģʽ */
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	/* �������ж� */
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  /* ʹ���ж� */	
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	
	  /*--------------------------KEY3����-----------------------------*/
	/* ѡ�񰴼��õ���GPIO */	
  GPIO_InitStructure.GPIO_Pin = KEY3_INT_GPIO_PIN;
  /* ����Ϊ�������� */	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(KEY2_INT_GPIO_PORT, &GPIO_InitStructure);

	/* ѡ��EXTI���ź�Դ */
  GPIO_EXTILineConfig(KEY3_INT_EXTI_PORTSOURCE, KEY3_INT_EXTI_PINSOURCE); 
  EXTI_InitStructure.EXTI_Line = KEY3_INT_EXTI_LINE;
	
	/* EXTIΪ�ж�ģʽ */
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	/* �������ж� */
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  /* ʹ���ж� */	
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	
	  /*--------------------------KEY4����-----------------------------*/
	/* ѡ�񰴼��õ���GPIO */	
  GPIO_InitStructure.GPIO_Pin = KEY4_INT_GPIO_PIN;
  /* ����Ϊ�������� */	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(KEY4_INT_GPIO_PORT, &GPIO_InitStructure);

	/* ѡ��EXTI���ź�Դ */
  GPIO_EXTILineConfig(KEY4_INT_EXTI_PORTSOURCE, KEY4_INT_EXTI_PINSOURCE); 
  EXTI_InitStructure.EXTI_Line = KEY4_INT_EXTI_LINE;
	
	/* EXTIΪ�ж�ģʽ */
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	/* �������ж� */
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  /* ʹ���ж� */	
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	
	  /*--------------------------KEY5����-----------------------------*/
	/* ѡ�񰴼��õ���GPIO */	
  GPIO_InitStructure.GPIO_Pin = KEY5_INT_GPIO_PIN;
  /* ����Ϊ�������� */	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(KEY5_INT_GPIO_PORT, &GPIO_InitStructure);

	/* ѡ��EXTI���ź�Դ */
  GPIO_EXTILineConfig(KEY5_INT_EXTI_PORTSOURCE, KEY5_INT_EXTI_PINSOURCE); 
  EXTI_InitStructure.EXTI_Line = KEY5_INT_EXTI_LINE;
	
	/* EXTIΪ�ж�ģʽ */
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	/* �������ж� */
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  /* ʹ���ж� */	
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}


/*
	�ĸ��жϵ�printf()���������ģ�ע����������䣬����Ҫ���������ʾ
*/


void KEY1_IRQHandler(void)
{
  //ȷ���Ƿ������EXTI Line�ж�
	if(EXTI_GetITStatus(KEY1_INT_EXTI_LINE) != RESET) 
	{
//		EXTI_n(KEY1);
		printf("\n���°�ȫ��!");
		if(0 == flag_FALLING)
		{
				USART_SendData(USART1, '2');		//����һ��������Ϣ
				while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
					continue;		
				
				printf("\tä�˲���ˤ��״̬��ֻ�Ƿ���һ���Ե�������Ϣ");
		}
		else
			flag_FALLING=0;	//ä�˰�ȫ
    //����жϱ�־λ
		delay(iCOUNT);
//		EXTI_n_Open(KEY1);
		EXTI_ClearITPendingBit(KEY1_INT_EXTI_LINE); 
	}  
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void KEY2_IRQHandler(void)	//��ѯ��ǰ״̬
{
  //ȷ���Ƿ������EXTI Line�ж�
	if(EXTI_GetITStatus(KEY2_INT_EXTI_LINE) != RESET) 
	{
//    EXTI_n(KEY2);
		printf("\n���¹���ѡ���");
		if(MODE_VOLUME == key4.current_mode)	//��ǰ������������ģʽ
		{
			printf("\t��ǰ��������������,��ǰ�����ȼ�Ϊ��%d", key4.key_rank[MODE_VOLUME]);
			//���ţ���ǰ������������ģʽ
		}
		else if(MODE_FREQUENCY == key4.current_mode)	//��ǰ����Ƶ�ʵ���ģʽ
		{
			printf("\t��ǰ����Ƶ�ʵ����У���ǰƵ�ʵȼ�Ϊ��%d", key4.key_rank[MODE_FREQUENCY]);			
			//���ţ���ǰ����Ƶ�ʵ���ģʽ
		}
		else if(MODE_DISTANCE == key4.current_mode)	//��ǰ���ھ������ģʽ
		{
			printf("\t��ǰ���ھ�������У���ǰ����ȼ�Ϊ��%d", key4.key_rank[MODE_DISTANCE]);
			//���ţ���ǰ���ھ������ģʽ
		}
		else
		{
			printf("\nKEY2_IRQHandler error!");
		}
		
		//����жϱ�־λ
		delay(iCOUNT);
//		EXTI_n_Open(KEY2);
		EXTI_ClearITPendingBit(KEY2_INT_EXTI_LINE);     
	}  
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
#define MODE_VOLUME     0
#define MODE_FREQUENCY 	1
#define MODE_DISTANCE   2
*/


void KEY3_IRQHandler(void)	//��һ��ģʽ
{
  //ȷ���Ƿ������EXTI Line�ж�
	if(EXTI_GetITStatus(KEY3_INT_EXTI_LINE) != RESET) 
	{
//		EXTI_n(KEY3);
		printf("\n���½�����һ��ģʽ��!");
		key4.current_mode=(++key4.current_mode)%key4.max_mode;
		if(MODE_VOLUME == key4.current_mode)
		{
			printf("\t��ǰģʽ����Ϊ��%s", "����ģʽ");
		}
		if(MODE_FREQUENCY == key4.current_mode)
		{
			printf("\t��ǰģʽ����Ϊ��%s", "Ƶ��ģʽ");
		}
		if(MODE_DISTANCE == key4.current_mode)
		{
			printf("\t��ǰģʽ����Ϊ��%s", "����ģʽ");
		}
		//����жϱ�־λ
		delay(iCOUNT);
		EXTI_ClearITPendingBit(KEY3_INT_EXTI_LINE);     
//		EXTI_n_Open(KEY3);
	}  
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void KEY4_IRQHandler(void)	//�Ӻż�
{
  //ȷ���Ƿ������EXTI Line�ж�
	if(EXTI_GetITStatus(KEY4_INT_EXTI_LINE) != RESET) 
	{
//    EXTI_n(KEY4);
		printf("\n���¼Ӻż�");
		
		if(MODE_VOLUME == key4.current_mode)	//��ǰ������������ģʽ
		{
			if(key4.max_rank == key4.key_rank[MODE_VOLUME]+1)
			{
				printf("\t��ǰ��������Ϊ�ȼ���%d���ﵽ���ȼ������ٵ���", key4.key_rank[MODE_VOLUME]);				

			}
			else
			{
				//�������Ӻ�������
				AddVolume();
				key4.key_rank[MODE_VOLUME]=(++key4.key_rank[MODE_VOLUME])%key4.max_rank;					
				printf("\t��ǰ��������Ϊ�ȼ���%d", key4.key_rank[MODE_VOLUME]);
			}

		}
		else if(MODE_FREQUENCY == key4.current_mode)	//��ǰ����Ƶ�ʵ���ģʽ
		{
			if(key4.max_rank == key4.key_rank[MODE_FREQUENCY]+1)
			{
				printf("\t��ǰƵ�ʵ���Ϊ�ȼ���%d���ﵽ���ȼ������ٵ���", key4.key_rank[MODE_FREQUENCY]);			
			}
			else
			{
				//Ƶ�����Ӻ�������
				AddRate();
				key4.key_rank[MODE_FREQUENCY]=(++key4.key_rank[MODE_FREQUENCY])%key4.max_rank;					
				printf("\t��ǰƵ�ʵ���Ϊ�ȼ���%d", key4.key_rank[MODE_FREQUENCY]);
			}

		}
		else if(MODE_DISTANCE == key4.current_mode)	//��ǰ���ھ������ģʽ
		{
			if(key4.max_rank == key4.key_rank[MODE_DISTANCE]+1)
			{			
				printf("\t��ǰ�������Ϊ�ȼ���%d���ﵽ���ȼ������ٵ���", key4.key_rank[MODE_DISTANCE]);
			}
			else
			{
				//�������Ӻ�������
				addDistance();
				key4.key_rank[MODE_DISTANCE]=(++key4.key_rank[MODE_DISTANCE])%key4.max_rank;					
				printf("\t��ǰ�������Ϊ�ȼ���%d", key4.key_rank[MODE_DISTANCE]);
			}
		}
		else
		{
			printf("KEY4_IRQHandler error!");
		}
		
		//����жϱ�־λ
		delay(iCOUNT);
		EXTI_ClearITPendingBit(KEY4_INT_EXTI_LINE);     
//		EXTI_n_Open(KEY4);
	}  
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void KEY5_IRQHandler(void)	//���ż�
{
  //ȷ���Ƿ������EXTI Line�ж�
	if(EXTI_GetITStatus(KEY5_INT_EXTI_LINE) != RESET) 
	{
//    EXTI_n(KEY5);
		printf("\n���¼��ż�");
		
		if(MODE_VOLUME == key4.current_mode)	//��ǰ������������ģʽ
		{
			if(key4.min_rank == key4.key_rank[MODE_VOLUME])
			{
				printf("\t��ǰ��������Ϊ�ȼ���%d���ﵽ��С�ȼ������ٵ�С", key4.key_rank[MODE_VOLUME]);
			}
			else
			{
				//�������ٺ�������
				SubVolume();
				key4.key_rank[MODE_VOLUME]=(--key4.key_rank[MODE_VOLUME])%key4.max_rank;					
				printf("\t��ǰ��������Ϊ�ȼ���%d", key4.key_rank[MODE_VOLUME]);
			}				
		}
		else if(MODE_FREQUENCY == key4.current_mode)	//��ǰ����Ƶ�ʵ���ģʽ
		{
			if(key4.min_rank == key4.key_rank[MODE_FREQUENCY])
			{
				printf("\t��ǰƵ�ʵ���Ϊ�ȼ���%d���ﵽ��С�ȼ������ٵ�С", key4.key_rank[MODE_FREQUENCY]);
			}
			else
			{
				//Ƶ�ʼ��ٺ�������
				SubRate();
				key4.key_rank[MODE_FREQUENCY]=(--key4.key_rank[MODE_FREQUENCY])%key4.max_rank;					
				printf("\t��ǰƵ�ʵ���Ϊ�ȼ���%d", key4.key_rank[MODE_FREQUENCY]);
			}
		}
		else if(MODE_DISTANCE == key4.current_mode)	//��ǰ���ھ������ģʽ
		{
			if(key4.min_rank == key4.key_rank[MODE_DISTANCE])
			{
				printf("\t��ǰ�������Ϊ�ȼ���%d���ﵽ��С�ȼ������ٵ�С", key4.key_rank[MODE_DISTANCE]);			
			}
			else
			{
				//������ٺ�������
				minusDistance();
				key4.key_rank[MODE_DISTANCE]=(--key4.key_rank[MODE_DISTANCE])%key4.max_rank;					
				printf("\t��ǰ�������Ϊ�ȼ���%d", key4.key_rank[MODE_DISTANCE]);
			}
		}
		else
		{
			printf("KEY5_IRQHandler error!");
		}
		
		//����жϱ�־λ
		delay(iCOUNT);
		EXTI_ClearITPendingBit(KEY5_INT_EXTI_LINE);     
//		EXTI_n_Open(KEY5);
	}  
}




#else

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
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 

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
					while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_DOWN)	//�ȴ������ſ�
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

		if( Key_Scan_down2(KEY2_GPIO_PORT,KEY2_GPIO_PIN) == TRUE  )
		{
	
				printf("\n���¹���ѡ���!\r\n");
				if(MODE_VOLUME == key4.current_mode)	//��ǰ������������ģʽ
				{
					printf("\t��ǰ��������������,��ǰ�����ȼ�Ϊ��%d\r\n", key4.key_rank[MODE_VOLUME]);
					//���ţ���ǰ������������ģʽ
				}
				if(MODE_FREQUENCY == key4.current_mode)	//��ǰ����Ƶ�ʵ���ģʽ
				{
					printf("\t��ǰ����Ƶ�ʵ����У���ǰƵ�ʵȼ�Ϊ��%d\r\n", key4.key_rank[MODE_FREQUENCY]);			
					//���ţ���ǰ����Ƶ�ʵ���ģʽ
				}
				if(MODE_DISTANCE == key4.current_mode)	//��ǰ���ھ������ģʽ
				{
					printf("\t��ǰ���ھ�������У���ǰ����ȼ�Ϊ��%d\r\n", key4.key_rank[MODE_DISTANCE]);
					//���ţ���ǰ���ھ������ģʽ
				}
				if(key4.current_mode != MODE_VOLUME && key4.current_mode != MODE_FREQUENCY && key4.current_mode != MODE_DISTANCE)
				{
					printf("\nKEY2 error! key4.current_mode = %d", key4.current_mode);
				}

		}		

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	

		if( Key_Scan_down2(KEY3_GPIO_PORT,KEY3_GPIO_PIN) == TRUE  )
		{
				printf("\n���½�����һ��ģʽ��!\r\n");
				key4.current_mode=(++key4.current_mode)%key4.max_mode;
				if(MODE_VOLUME == key4.current_mode)
				{
					printf("\t��ǰģʽ����Ϊ��%s", "����ģʽ\r\n");
				}
				if(MODE_FREQUENCY == key4.current_mode)
				{
					printf("\t��ǰģʽ����Ϊ��%s", "Ƶ��ģʽ\r\n");
				}
				if(MODE_DISTANCE == key4.current_mode)
				{
					printf("\t��ǰģʽ����Ϊ��%s", "����ģʽ\r\n");
				}

		}		

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	

		if( Key_Scan_down2(KEY4_GPIO_PORT,KEY4_GPIO_PIN) == TRUE  )
		{
				printf("\n���¼Ӻż�!\r\n");
				
				if(MODE_VOLUME == key4.current_mode)	//��ǰ������������ģʽ
				{
						if(key4.max_rank == key4.key_rank[MODE_VOLUME]+1)
						{
							printf("\t��ǰ��������Ϊ�ȼ���%d���ﵽ���ȼ������ٵ���\r\n", key4.key_rank[MODE_VOLUME]);				

						}
						else
						{
							//�������Ӻ�������
							key4.key_rank[MODE_VOLUME]=(++key4.key_rank[MODE_VOLUME])%key4.max_rank;					
							printf("\t��ǰ��������Ϊ�ȼ���%d\r\n", key4.key_rank[MODE_VOLUME]);
						}

				}
				else if(MODE_FREQUENCY == key4.current_mode)	//��ǰ����Ƶ�ʵ���ģʽ
				{
						if(key4.max_rank == key4.key_rank[MODE_FREQUENCY]+1)
						{
							printf("\t��ǰƵ�ʵ���Ϊ�ȼ���%d���ﵽ���ȼ������ٵ���\r\n", key4.key_rank[MODE_FREQUENCY]);			
						}
						else
						{
							//Ƶ�����Ӻ�������
							key4.key_rank[MODE_FREQUENCY]=(++key4.key_rank[MODE_FREQUENCY])%key4.max_rank;					
							printf("\t��ǰƵ�ʵ���Ϊ�ȼ���%d\r\n", key4.key_rank[MODE_FREQUENCY]);
						}

				}
				else if(MODE_DISTANCE == key4.current_mode)	//��ǰ���ھ������ģʽ
				{
						if(key4.max_rank == key4.key_rank[MODE_DISTANCE]+1)
						{			
							printf("\t��ǰ�������Ϊ�ȼ���%d���ﵽ���ȼ������ٵ���\r\n", key4.key_rank[MODE_DISTANCE]);
						}
						else
						{
							//�������Ӻ�������
							key4.key_rank[MODE_DISTANCE]=(++key4.key_rank[MODE_DISTANCE])%key4.max_rank;					
							printf("\t��ǰ�������Ϊ�ȼ���%d\r\n", key4.key_rank[MODE_DISTANCE]);
						}
				}
				else
				{
						printf("KEY4 error! key4.current_mode = %d\r\n", key4.current_mode);
				}

		}		

////////////////////////////////////////////////////////////////////////////////////////////////
		
		if( Key_Scan_down2(KEY5_GPIO_PORT,KEY5_GPIO_PIN) == TRUE  )
		{
				printf("\n���¼��ż�!\r\n");
		
				if(MODE_VOLUME == key4.current_mode)	//��ǰ������������ģʽ
				{
						if(key4.min_rank == key4.key_rank[MODE_VOLUME])
						{
							printf("\t��ǰ��������Ϊ�ȼ���%d���ﵽ��С�ȼ������ٵ�С\r\n", key4.key_rank[MODE_VOLUME]);
						}
						else
						{
							//�������ٺ�������
							key4.key_rank[MODE_VOLUME]=(--key4.key_rank[MODE_VOLUME])%key4.max_rank;					
							printf("\t��ǰ��������Ϊ�ȼ���%d\r\n", key4.key_rank[MODE_VOLUME]);
						}				
				}
				else if(MODE_FREQUENCY == key4.current_mode)	//��ǰ����Ƶ�ʵ���ģʽ
				{
						if(key4.min_rank == key4.key_rank[MODE_FREQUENCY])
						{
							printf("\t��ǰƵ�ʵ���Ϊ�ȼ���%d���ﵽ��С�ȼ������ٵ�С\r\n", key4.key_rank[MODE_FREQUENCY]);
						}
						else
						{
							//Ƶ�ʼ��ٺ�������
							key4.key_rank[MODE_FREQUENCY]=(--key4.key_rank[MODE_FREQUENCY])%key4.max_rank;					
							printf("\t��ǰƵ�ʵ���Ϊ�ȼ���%d\r\n", key4.key_rank[MODE_FREQUENCY]);
						}
				}
				else if(MODE_DISTANCE == key4.current_mode)	//��ǰ���ھ������ģʽ
				{
					if(key4.min_rank == key4.key_rank[MODE_DISTANCE])
					{
						printf("\t��ǰ�������Ϊ�ȼ���%d���ﵽ��С�ȼ������ٵ�С\r\n", key4.key_rank[MODE_DISTANCE]);			
					}
					else
					{
						//������ٺ�������
						key4.key_rank[MODE_DISTANCE]=(--key4.key_rank[MODE_DISTANCE])%key4.max_rank;					
						printf("\t��ǰ�������Ϊ�ȼ���%d\r\n", key4.key_rank[MODE_DISTANCE]);
					}
				}
				else
				{
					printf("KEY5 error! key4.current_mode = %d\r\n", key4.current_mode);
				}
		
	}		

}

static void NVIC_Configuration2(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* ����NVICΪ���ȼ���1 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
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
	/* �������ж� */
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
		printf("\n���°�ȫ��! exit\r\n");
		if(0 == flag_FALLING)
		{
				USART_SendData(USART1, '2');		//����һ��������Ϣ
				while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
					continue;		
				
				printf("\tä�˲���ˤ��״̬��ֻ�Ƿ���һ���Ե�������Ϣ");
		}
		else
			flag_FALLING=0;	//ä�˰�ȫ
    //����жϱ�־λ
		delay(iCOUNT);
//		EXTI_n_Open(KEY1);
		EXTI_ClearITPendingBit(KEY1_INT_EXTI_LINE); 
	}  
}


#endif



/*********************************************END OF FILE**********************/


