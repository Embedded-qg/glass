/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTI
  
  AL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_exti.h"
#include "stm32f10x_it.h"
#include "./exti/bsp_exti.h" 
#include "./i2c/bsp_i2c.h"
#include "bsp_key.h"
#include "./systick/bsp_SysTick.h"
#include <stdio.h>
#include"queue.h"
#include "UltraConfig.h"
#include "UltrasonicWave.h"
#include "debug.h"
#include "bsp_key.h"

extern LinkQueue q;
extern int time;
extern int flag_FALLING;
extern int flag_volume;
//char Receive[10];
//int Num;

unsigned int Task_Delay[NumOfTask]={0};
extern void TimingDelay_Decrement(void);
extern void TimeStamp_Increment(void);
extern void gyro_data_ready_cb(void);


/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	unsigned char i;

	TimingDelay_Decrement();
	TimeStamp_Increment();
	
	for(i=0;i<NumOfTask;i++)
	{
		if(Task_Delay[i])
		{
			Task_Delay[i]--;
		}
	}
}

/// IO ���ж�
void EXTI_INT_FUNCTION (void)
{
//	MPU_DEBUG("intterrupt");
	if(EXTI_GetITStatus(EXTI_LINE) != RESET) //ȷ���Ƿ������EXTI Line�ж�
	{

		  /* Handle new gyro*/
		gyro_data_ready_cb();
		EXTI_ClearITPendingBit(EXTI_LINE);     //����жϱ�־λ
	}  
}


/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
void USART1_IRQHandler(void)
{
	uint8_t ch;
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{ 	
//	    ch = USART1->DR;
//		  printf("sjdfj\r\n");
//			int i;
			ch = USART_ReceiveData(USART1);
		  en_Queue(&q, ch);
//			if(ch=='s'||Receive[0]=='s')
//				Receive[Num]=ch;
//			else
//				return;
//			Num++;
//			if(Receive[Num-1]=='e')
//			{
//				Num=0;
//				printf( " ch = %s\r\n", Receive );    //�����ܵ�������ֱ�ӷ��ش�
//				for(i=0;i<10;i++)
//					Receive[i]=' ';
//			}
	} 
	 
}

void USART2_IRQHandler(void)  
{  
	uint8_t ch;
     if(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == SET)  
        {       
                    //USART_SendData(USART2, USART_ReceiveData(USART2));   
          ch = USART_ReceiveData(USART2);
					printf( "%c", ch );    //�����ܵ�������ֱ�ӷ��ش�ӡ
        }   
} 





void TIM2_IRQHandler(void)
{
	extern int8_t  MEASURE_FLAG;   // 0 �۾��ɼ����ݣ� 1 �ȴ����Ȳɼ�����
	
	static int portNum = 0;      //ѡ����ͨ��
	
	if ( TIM_GetITStatus( TIM2, TIM_IT_Update) != RESET ) 
	{			
		if( MEASURE_FLAG == 0)
		{
			UltrasonicWave(portNum);    //�ɼ�һ��ģ������
			portNum++;
			if( portNum == AVER_NUM_GLASS)   //�۾���ģ�����ݲɼ����
			{
				portNum = 0;
				//$$$$$$$$$$����ȷ��Ͳ������
				//MEASURE_FLAG = 1;           
			}
		}
		
		
		
		TIM_ClearITPendingBit(TIM2 , TIM_FLAG_Update);  		 
	}		
	
}

void TIM3_IRQHandler(void)
{
	// ��Ҫ��������źŵ����ڴ��ڶ�ʱ�������ʱʱ����ʱ���ͻ���������������ж�
	if ( TIM_GetITStatus ( TIM3, TIM_IT_Update) != RESET )               
	{	
//		TIM_ICUserValueStructure.Capture_FinishFlag = 1;	
		TIM_ICUserValueStructure[0].Capture_CcrValue += GENERAL_TIM_PERIOD+1;
		TIM_ICUserValueStructure[1].Capture_CcrValue += GENERAL_TIM_PERIOD+1;
		TIM_ClearITPendingBit ( TIM3, TIM_FLAG_Update ); 		
	}
//printf("tim3\r\n");
//��һ��������ģ�������ز����ж�
	if ( TIM_GetITStatus (TIM3, TIM_IT_CC1 ) != RESET && !TIM_ICUserValueStructure[0].Capture_FinishFlag )
	{  	
         p_debug("cc1\r\n");		
		// ��һ�β���
		if ( TIM_ICUserValueStructure[0].Capture_StartFlag == 0 )
		{
			p_debug("once\r\n");
			// ��������0
		//	TIM_SetCounter ( TIM3, 0 );       
      			
			// �Զ���װ�ؼĴ������±�־��0
//			TIM_ICUserValueStructure[0].Capture_Period = 0;
      // �沶��ȽϼĴ�����ֵ�ı�����ֵ��0			
	//		TIM_ICUserValueStructure[0].Capture_CcrValue = 0;
			//��¼��һ�β���Ĵ�����ֵ 
			TIM_ICUserValueStructure[0].Capture_CcrValue = TIM_GetCapture1(TIM3);
			// ����һ�β���������֮�󣬾ͰѲ����������Ϊ�½���
			TIM_OC1PolarityConfig(TIM3, TIM_ICPolarity_Falling);
      // ��ʼ�����׼��1			
			TIM_ICUserValueStructure[0].Capture_StartFlag = 1;		
			TIM_ICUserValueStructure[0].Capture_CCx = 1;			
		}
		// �½��ز����ж�
		else // �ڶ��β���
		{
			p_debug("second\r\n");
			// ��ȡ����ȽϼĴ�����ֵ���һ�β�׽ֵ�Ĳ�ֵ�����ֵ���ǲ��񵽵ĸߵ�ƽ��ʱ���ֵ
			TIM_ICUserValueStructure[0].Capture_CcrValue = TIM_GetCapture1(TIM3) - TIM_ICUserValueStructure[0].Capture_CcrValue ;

			// ���ڶ��β����½���֮�󣬾ͰѲ����������Ϊ�����أ��ÿ����µ�һ�ֲ���
			TIM_OC1PolarityConfig(TIM3, TIM_ICPolarity_Rising);
      // ��ʼ�����־��0		
			TIM_ICUserValueStructure[0].Capture_StartFlag = 0;
            if( TIM_ICUserValueStructure[0].Capture_CCx == 1)
			{
			      // ������ɱ�־��1			
				TIM_ICUserValueStructure[0].Capture_FinishFlag = 1;
				p_debug("finish\r\n");
			}
			else
			{
				p_err("��׽ͨ����ƥ��\r\n");
			}	
			p_debug("tim3, cc1\r\n");
		}
		TIM_ClearITPendingBit (TIM3,TIM_IT_CC1);	    
	}	
//�ڶ���������ģ�������ز����ж�
	if ( TIM_GetITStatus (TIM3, TIM_IT_CC2 ) != RESET && !TIM_ICUserValueStructure[1].Capture_FinishFlag)
	{	
		p_debug("cc2\r\n");
		// ��һ�β���
		if ( TIM_ICUserValueStructure[1].Capture_StartFlag == 0 )
		{
			p_debug("once\r\n");
			// ��������0
			//TIM_SetCounter ( TIM3, 0 );
			// �Զ���װ�ؼĴ������±�־��0
			//TIM_ICUserValueStructure[1].Capture_Period = 0;
      // �沶��ȽϼĴ�����ֵ�ı�����ֵ��0			
//////			TIM_ICUserValueStructure[1].Capture_CcrValue = 0;
			TIM_ICUserValueStructure[1].Capture_CcrValue = TIM_GetCapture2 (TIM3);

			// ����һ�β���������֮�󣬾ͰѲ����������Ϊ�½���
			TIM_OC2PolarityConfig(TIM3, TIM_ICPolarity_Falling);
      // ��ʼ�����׼��1			
			TIM_ICUserValueStructure[1].Capture_StartFlag = 1;
			TIM_ICUserValueStructure[1].Capture_CCx = 2;
		}
		// �½��ز����ж�
		else // �ڶ��β���
		{
			p_debug("second\r\n");
			// ��ȡ����ȽϼĴ�����ֵ�����ֵ���ǲ��񵽵ĸߵ�ƽ��ʱ���ֵ
			TIM_ICUserValueStructure[1].Capture_CcrValue = TIM_GetCapture2 (TIM3) - TIM_ICUserValueStructure[1].Capture_CcrValue ;
			// ���ڶ��β����½���֮�󣬾ͰѲ����������Ϊ�����أ��ÿ����µ�һ�ֲ���
			TIM_OC2PolarityConfig(TIM3, TIM_ICPolarity_Rising);
      // ��ʼ�����־��0		
			TIM_ICUserValueStructure[1].Capture_StartFlag = 0;
            if( TIM_ICUserValueStructure[1].Capture_CCx == 2)
			{
			      // ������ɱ�־��1			
				TIM_ICUserValueStructure[1].Capture_FinishFlag = 1;
				p_debug("finish\r\n");
			}
			else
			{
				p_err("��׽ͨ����ƥ��\r\n");
			}	
			p_debug("tim3, cc2\r\n");			
		}
		TIM_ClearITPendingBit (TIM3,TIM_IT_CC2);	    
	}		
}

void  TIM6_IRQHandler (void)
{
	if ( TIM_GetITStatus( TIM6, TIM_IT_Update) != RESET ) 
	{	
		time++;
		if(time==2000)
			flag_volume=0;
		if(time==2002)
			time=0;
		TIM_ClearITPendingBit(TIM6 , TIM_FLAG_Update);  		 
	}		 	
}

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

///////////////////////////////////////////////////////////////////////////////////


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
