/**
  ******************************************************************************
  * @file    mp3.c
  * @author  chzh
  * @version V1.0
  * @date    2018-05-19
  * @brief   mp3ģ�麯��
  ******************************************************************************
  */ 
#include "mp3.h"
#include <stdio.h>
int Rate=0;
int time=0;
int flag_volume=0;


u8 Call[5]={0x7E,0x03,0x0E,0x0D,0xEF};//ָֹͣ��

u8 Next[5]={0x7E,0x03,0x03,0x00,0xEF};//��һ��ָ��
u8 Last[5]={0x7E,0x03,0x04,0x07,0xEF};//��һ��ָ��

u8 Add[5] ={0x7E,0x03,0x05,0x06,0xEF};					//����+ָ��	
u8 Sub[5] ={0x7E,0x03,0x06,0x05,0xEF};         //������ָ��

u8 rate_1[5]=      {0x7E,0x03,0x01,0x02,0xEF};                //����ָ��,ѭ��������һ������
u8 rate_2[7]=      {0x7E,0x05,0x41,0x00,0x0F,0x4B,0xEF};      //����
u8 rate_3[7]=      {0x7E,0x05,0x41,0x00,0x01,0x45,0xEF};      //��Ƶ��
u8 rate_4[7]=      {0x7E,0x05,0x41,0x00,0x02,0x46,0xEF};      //��Ƶ��
u8 rate_5[7]=      {0x7E,0x05,0x41,0x00,0x03,0x47,0xEF};      //��Ƶ��

u8 CareFootLeft[7]=    {0x7E,0x05,0x41,0x00,0x04,0x40,0xEF};      //����
u8 CareHandLeft[7]=    {0x7E,0x05,0x41,0x00,0x05,0x41,0xEF};      //���� 
u8 CareHeadLeft[7]=    {0x7E,0x05,0x41,0x00,0x06,0x42,0xEF};      //ͷ��
u8 CareFootRight[7]=    {0x7E,0x05,0x41,0x00,0x18,0x5C,0xEF};      //����
u8 CareHandRight[7]=    {0x7E,0x05,0x41,0x00,0x19,0x5D,0xEF};      //���� 
u8 CareHeadRight[7]=    {0x7E,0x05,0x41,0x00,0x1A,0x5E,0xEF};      //ͷ��

u8 East[7]=        {0x7E,0x05,0x41,0x00,0x07,0x43,0xEF};      //��
u8 South[7]=       {0x7E,0x05,0x41,0x00,0x08,0x4C,0xEF};      //��
u8 West[7]=        {0x7E,0x05,0x41,0x00,0x09,0x4D,0xEF};      //��
u8 North[7]=       {0x7E,0x05,0x41,0x00,0x0A,0x4E,0xEF};      //��
u8 SouthEast[7]=   {0x7E,0x05,0x41,0x00,0x0B,0x4F,0xEF};      //����
u8 SouthWest[7]=   {0x7E,0x05,0x41,0x00,0x0C,0x48,0xEF};      //����
u8 NorthWest[7]=   {0x7E,0x05,0x41,0x00,0x0D,0x49,0xEF};      //����
u8 NorthEast[7]=   {0x7E,0x05,0x41,0x00,0x0E,0x4A,0xEF};      //����

u8 ModeVolume[7]=  {0x7E,0x05,0x41,0x00,0x15,0x51,0xEF};      //������ʾģʽ
u8 ModeRate[7]=    {0x7E,0x05,0x41,0x00,0x16,0x52,0xEF};      //Ƶ����ʾģʽ
u8 AdjustVolume[7]={0x7E,0x05,0x41,0x00,0x10,0x54,0xEF};      //��������ģʽ
u8 AdjustRate[7]=  {0x7E,0x05,0x41,0x00,0x11,0x55,0xEF};      //Ƶ�ʵ���ģʽ
u8 ModeDistance[7]={0x7E,0x05,0x41,0x00,0x12,0x56,0xEF};      //�������
u8 ModeExit[7]=    {0x7E,0x05,0x41,0x00,0x17,0x53,0xEF};      //�˳�����

u8 Alarm[7]=       {0x7E,0x05,0x41,0x00,0x13,0x57,0xEF};      //����ź��ѷ���
u8 AutoAlarm[7]=   {0x7E,0x05,0x41,0x00,0x14,0x50,0xEF};      //�Ƿ���Ҫ�Զ�����
u8 SendSucceed[7]= {0x7E,0x05,0x41,0x00,0x1B,0x5F,0xEF};      //������Ϣ�ѷ���
u8 QuitAlarm[7]=   {0x7E,0x05,0x41,0x00,0x1C,0x58,0xEF};      //�˳��Զ�����


/*
 * ��������USART3_Send_String
 * ����  ��������������ָ��
 * ����  ����
 * ���  ����	
 */
void USART3_Send_String(u8 *p,u8 cnt)
{   
		if(flag_volume==1)                           //flag_volume==1˵��Ŀǰ���ڲ�������
			return;
		else
		{
			 while(cnt>0)
			 {	 
					 USART_ClearFlag(USART3, USART_FLAG_TC);
					 USART_SendData(USART3,*p++);			 
					 while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
					 {
							 ;
					 }
					 cnt--;
			 }
	 }
}

void USART3_Send_String_Key(u8 *p,u8 cnt)
{   
			 while(cnt>0)
			 {	 
					 USART_ClearFlag(USART3, USART_FLAG_TC);
					 USART_SendData(USART3,*p++);			 
					 while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
					 {
							 ;
					 }
					 cnt--;
			 }
}

/*
 * ��������AddRate
 * ����  ������Ƶ��
 * ����  ����
 * ���  ����	
 */
void AddRate()
{
	if(Rate<2)
		Rate++;
}

/*
 * ��������SubRate
 * ����  ������Ƶ��
 * ����  ����
 * ���  ����	
 */
void SubRate()
{
	if(Rate>0)
		Rate--;
}


/*
 * ��������AddVolume
 * ����  ����������
 * ����  ����
 * ���  ����	
 */
void AddVolume()
{
	USART3_Send_String_Key(Add,sizeof(Add));  //��������
}

/*
 * ��������SubVolume
 * ����  ����������
 * ����  ����
 * ���  ����	
 */
void SubVolume()
{
		USART3_Send_String_Key(Sub,sizeof(Sub));  //��������
}
	
/*
 * ��������Weighting
 * ����  ���Եȼ����м�Ȩ
 * ����  ����
 * ���  ����	
 */
int Weighting(int degree)
{
	if(degree==1)
		return Rate;
	else
		return degree+2;
}

/*
 * ��������PlayVoice
 * ����  ������������
 * ����  �����뼴����ײ�Ĳ�λ
 * ���  ����	
 */
void PlayVoice(int position,int left_right)
{
			if(left_right)
			{
				switch(position)
				{
					case head:
						USART3_Send_String(CareHeadRight,sizeof(CareHeadRight));
						break;
					case hand:
						USART3_Send_String(CareHandRight,sizeof(CareHandRight));
						break;
					case foot:
						USART3_Send_String(CareFootRight,sizeof(CareFootRight));
						break;
				}
			}
			else
			{
				switch(position)
				{
					case head:
						USART3_Send_String(CareHeadLeft,sizeof(CareHeadLeft));
						break;
					case hand:
						USART3_Send_String(CareHandLeft,sizeof(CareHandLeft));
						break;
					case foot:
						USART3_Send_String(CareFootLeft,sizeof(CareFootLeft));
						break;
				}
			}
}


/*
 * ��������PlayRate
 * ����  ������Ƶ�ʡ�
 * ����  ������Ƶ�ʵĵȼ�
 * ���  ����	
 */
void PlayRate(int degree)
{
	degree = degree + Rate;
	printf("Rate = %d \r\n",Rate);
//	static int last_degree = 0 ;
//	if(last_degree == degree)
//		return;	
//	last_degree = degree;
//			degree=Rate+degree;
			switch(degree)
			{
				case 0:
					                                      				    //Ƶ��1
					break;
				case 1:
					USART3_Send_String(rate_2,sizeof(rate_2));				//Ƶ��2
					break;
				case 2:
					USART3_Send_String(rate_3,sizeof(rate_3));				//Ƶ��3
					break;
				case 3:
					USART3_Send_String(rate_4,sizeof(rate_4));				//Ƶ��4
					break;
				case 4:
					USART3_Send_String(rate_5,sizeof(rate_5));				//Ƶ��5
					break;
			}

}

/*
 * ��������PlayDirection
 * ����  �����ŷ�λ����Ϣ��
 * ����  �����뷽λ��Ϣ
 * ���  ����	
 */
void PlayDirection(char direction)
{
		flag_volume=0;
		printf("��  �յ��ķ�λΪ��%c\r\n",direction);
		switch(direction)
		{
				case InEast:
					USART3_Send_String(East,sizeof(East));
					break;
				case InSouth:
						USART3_Send_String(South,sizeof(South));
						break;
				case InWest:
						USART3_Send_String(West,sizeof(West));
						break;
				case InNorth:
						USART3_Send_String(North,sizeof(North));
						break;
				case InSouthEast:
						USART3_Send_String(SouthEast,sizeof(SouthEast));
						break;
				case InSouthWest:
						USART3_Send_String(SouthWest,sizeof(SouthWest));
						break;
				case InNorthWest:
						USART3_Send_String(NorthWest,sizeof(NorthWest));
						break;
				case InNorthEast:
						USART3_Send_String(NorthEast,sizeof(NorthEast));
						break;					
		}
}

/*
 * ��������TIM6_TIM_NVIC_Config
 * ����  �����ö�ʱ��6�����ȼ������ȼ�����ʹ��NVIC_PriorityGroup_2
 * ����  ����
 * ���  ����	
 */
void TIM6_TIM_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    // �����ж���Ϊ0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		
		// �����ж���Դ
    NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn ;	
		// ���������ȼ�Ϊ 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
	  // ������ռ���ȼ�Ϊ3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/*
 * ע�⣺TIM_TimeBaseInitTypeDef�ṹ��������5����Ա��TIM6��TIM7�ļĴ�������ֻ��
 * TIM_Prescaler��TIM_Period������ʹ��TIM6��TIM7��ʱ��ֻ���ʼ����������Ա���ɣ�
 * ����������Ա��ͨ�ö�ʱ���͸߼���ʱ������.
 *-----------------------------------------------------------------------------
 *typedef struct
 *{ TIM_Prescaler            ����
 *	TIM_CounterMode			     TIMx,x[6,7]û�У���������
 *  TIM_Period               ����
 *  TIM_ClockDivision        TIMx,x[6,7]û�У���������
 *  TIM_RepetitionCounter    TIMx,x[1,8,15,16,17]����
 *}TIM_TimeBaseInitTypeDef; 
 *-----------------------------------------------------------------------------
 */

/*
 * ��������TIM6_TIM_Mode_Config
 * ����  ����ʼ����ʱ��6
 * ����  ����
 * ���  ����	
 */
void TIM6_TIM_Mode_Config(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		
		// ������ʱ��ʱ��,���ڲ�ʱ��CK_INT=72M
    TIM6_TIM_APBxClock_FUN(TIM6_TIM_CLK, ENABLE);
	
		// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
    TIM_TimeBaseStructure.TIM_Period = TIM6_TIM_Period;	

	  // ʱ��Ԥ��Ƶ��Ϊ
    TIM_TimeBaseStructure.TIM_Prescaler= TIM6_TIM_Prescaler;
	
	  // ��ʼ����ʱ��
    TIM_TimeBaseInit(TIM6_TIM, &TIM_TimeBaseStructure);
		
		// ����������жϱ�־λ
    TIM_ClearFlag(TIM6_TIM, TIM_FLAG_Update);
	  
		// �����������ж�
    TIM_ITConfig(TIM6_TIM,TIM_IT_Update,ENABLE);
		
		// ʹ�ܼ�����
    TIM_Cmd(TIM6_TIM, ENABLE);	
}
/*
 * ��������TIM6_Config
 * ����  ����ʼ����ʱ��6,�����������ŵļ�ʱ
 * ����  ����
 * ���  ����	
 */
void TIM6_Config(void)
{
	TIM6_TIM_NVIC_Config();
	TIM6_TIM_Mode_Config();
}
