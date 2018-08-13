/******************** (C) 1209 Lab **************************
 * �ļ���  : UltrasonicWave.c
 * ����    �����������ģ�飬UltrasonicWave_Configuration��������
             ��ʼ������ģ�飬UltrasonicWave_StartMeasure��������
			 ������࣬������õ�����ͨ������1��ӡ����         
 * ʵ��ƽ̨��Mini STM32������  STM32F103RBT6
 * Ӳ�����ӣ�------------------
 *          | PC8  - TRIG      |
 *          | PC7  - ECHO      |
 *           ------------------
 * ��汾  ��ST3.5.0
 *
 * ����    ��Lee 
*********************************************************************************/

#include "UltrasonicWave.h"
#include "debug.h"
#include "mp3.h"

////////���Կ���//////////////
#ifdef DEBUG_ON_OFF 
#undef  DEBUG_ON_OFF
#endif
#define DEBUG_ON_OFF 1       //1�򿪵��ԡ�0�ر�
//////////////////////////////

static void UltrasonicWave_StartMeasure(GPIO_TypeDef *  port, int32_t pin);              

static int UltrasonicWave_Distance[AVER_NUM_GLASS];      //������ľ���    

static int16_t MAX_DISTACE =150;        //������
int8_t  MEASURE_FLAG = 1;   // 1 �۾��ɼ����ݣ� 0 �ȴ����Ȳɼ�����

int8_t GET_WALK_FLAG = 0;       //���չ������ݱ�־
int UltrasonicWave_Distance_Walk[AVER_NUM_WALK] = { 500, 500, 500, 500, 500};   //���Ȳɼ�����
	static int8_t lateobstacle[4] = {0,0,0,0};      //��¼������β���ϰ���״̬����������ϰ���ʱ+1��2δ��⵽�ϰ���ʱ����
int MODE_FLAG = 1;       //1 ���� 0 Ƶ��

extern int flag_FALLING;


static void Obstacle(int distance_glass[], int distance_walk[], int* distanceVoice, int* distanceRate );


static void ObstacleDelayUs( uint32_t t )
{

	int i;
    for( i = 0; i < t * 10; i++ )
 	{
		__NOP();
	}	
}

/*
 * ��������dealTIM_ICUserValueStructureData
 * ����  ������׽����ʱ������ת��Ϊ����
 * ����  ��TIM_ICUserValueStructurex ��TIM_ICUserValueStructure1-6
			i����Ӧ���������
 * ���  ����	
 */
static void dealTIM_ICUserValueStructureData(TIM_ICUserValueTypeDef TIM_ICUserValueStructurex)
{

//	uint32_t time;
	double ftime;
//	int distanceVoice, distanceRate;
	int i;
	i = TIM_ICUserValueStructurex.Capture_CCx;
	// ����ߵ�ƽʱ��ļ�������ֵ
//	time = TIM_ICUserValueStructurex.Capture_CcrValue+1;
	// ��ӡ�ߵ�ƽ����ʱ��
	ftime = ((double) TIM_ICUserValueStructurex.Capture_CcrValue+1)/TIM_PscCLK;

	UltrasonicWave_Distance[i-1] = ftime * 340 / 2  * 100;
	
//
//	p_debug( "%d : distance %d\r\n",i, UltrasonicWave_Distance[i-1]);

	
//	Obstacle(UltrasonicWave_Distance, UltrasonicWave_Distance_Walk,&distanceVoice, &distanceRate );      //�����ϰ�����Ϣ

////	PlayRate(distanceRate);                    //����Ƶ��ģʽ
//	PlayVoice(distanceVoice);                  //�޸�����ģʽ
}

/*
 * ��������addDistance
 * ����  �����Ӽ����룬 ����ȡֵΪ300 200 100
 * ����  ��num ��ⷶΧ����num����
 * ���  ���޸ĺ�ļ�ⷶΧ
 */
int addDistance()
{
	MAX_DISTACE += 100;
	if( MAX_DISTACE > 300 )           //����ⷶΧΪ3oocm	
		MAX_DISTACE = 300;
	return MAX_DISTACE;
}


/*
 * ��������addDistance
 * ����  ����С�����룬����ȡֵΪ300 200 100
 * ����  ��distance ��ⷶΧ��Сdistanc����
 * ���  ���޸ĺ�ļ�ⷶΧ
 */
int minusDistance()
{
	MAX_DISTACE -= 100;
	if( MAX_DISTACE < 100  )
		MAX_DISTACE = 100;		
	return MAX_DISTACE;
}

/*
 * ��������getDistance
 * ����  ����õ�ǰ��ⷶΧ
 * ����  ����
 * ���  ����ǰ�ļ�ⷶΧ
 */
int getDistance()
{
	return MAX_DISTACE;
}


//�ϰ����ж�
//distance �ɼ��ľ�������
//distanceVoice ����ģʽ���ϰ�����ʾ�� 0 ���ϰ��� 1 �ϰ����ڽ��� 2 �ϰ�������ǰ�� 3�ϰ�����ͷ��λ��
//distanceRate Ƶ��ģʽ���ϰ�����ʾ�� 0 ���ϰ��� 1 �ϰ�����3~2m�� 2 �ϰ�����2~1m ,3 �ϰ���<1m
static void Obstacle(int distance_glass[], int distance_walk[], int* distanceVoice, int* distanceRate )
{
	
	
	int i = 0; 
	int mindistace = 300 ;    //��¼������ϰ������

	
	*distanceVoice = OBSTACLE_NO;
	*distanceRate = 0;
	
	
	for( ; i < AVER_NUM_GLASS; i++ )                  //�۾����������ϰ����ж�
	{
		if( distance_glass[i] < MAX_DISTACE )           //�ж�ͷ���Ƿ����ϰ���
		{
			lateobstacle[0]++;
			if( lateobstacle[0] > LATE_NUM )
			{
				lateobstacle[0] = LATE_NUM;
			}
			break;
		}
	}
	if( i == AVER_NUM_GLASS )        //�ϰ�������ʧ
	{
		lateobstacle[0] = 0;
	}
	
//	for( i = 0; i < 5; i++ )
//	{
//		printf("walk: %d\r\n", distance_walk[i]);
//	}
//	
//	
	
	
	if( distance_walk[0]  < MAX_DISTACE || distance_walk[1] < MAX_DISTACE )  
	{
		lateobstacle[1]++;
//		p_debug("     lateobstacle: %d\r\n", lateobstacle[1]);
		if( lateobstacle[1] > LATE_NUM )
		{
			lateobstacle[1] = LATE_NUM;
		}		
	}
	else
	{
		lateobstacle[1] = 0;
	}	
	
	if( distance_walk[2]  < MAX_DISTACE || distance_walk[3] < MAX_DISTACE )  
	{
		lateobstacle[2]++;
//		p_debug("     lateobstacle: %d\r\n", lateobstacle[2]);
		if( lateobstacle[2] > LATE_NUM )
		{
			lateobstacle[2] = LATE_NUM;
		}
	}
	else
	{
		lateobstacle[2] = 0;
	}	
	
	if( distance_walk[4]  < MAX_DISTACE  )  
	{
		lateobstacle[3]++;
//   	p_debug("foot:%d\r\n", distance_walk[4]);
		if( lateobstacle[3] > LATE_NUM )
		{
			lateobstacle[3] = LATE_NUM;
		}
	}
	else
	{
		lateobstacle[3] = 0;
	}	

//�ж�ͷ���Ƿ����ϰ���
	if( lateobstacle[0] == LATE_NUM )
	{
		*distanceVoice = OBSTACLE_HEAD;
	}
//�ж�ǰ���Ƿ����ϰ���
	if( lateobstacle[1] == LATE_NUM  )
	{
		*distanceVoice = OBSTACLE_AHEAD;
	}    	
//�жϽ����Ƿ����ϰ���
	else if( lateobstacle[3] == LATE_NUM || lateobstacle[2] == LATE_NUM )
	{
		p_debug("foot\r\n");
		*distanceVoice = OBSTACLE_FOOT;
	}
	
/***************Ƶ��ģʽ***********************/	
//Ƶ��ģʽ���ϰ�����ʾ,ȡ����ϰ������
	for( i = 0; i < AVER_NUM_GLASS; i++ )                
	{
		mindistace = mindistace > distance_glass[i] ? distance_glass[i] : mindistace;
	}	
	for( i = 0; i < AVER_NUM_WALK; i++ )
	{
		mindistace = mindistace > distance_walk[i] ? distance_walk[i] : mindistace;
	}
	*distanceRate = 2 - mindistace / 100 ;
  if( *distanceRate < 0 )
	{
		*distanceRate = 0;
	}  

/**********************�������飬�������*******************************/
	for( i = 0; i < AVER_NUM_GLASS; i++ )
	{
		distance_glass[i] = INT16_MAX;
	}
	for( i = 0; i < AVER_NUM_WALK; i++ )
	{
		distance_walk[i] = INT16_MAX;
	}	
}

//�ж��ϰ���λ�ã���������ʾ
void HasObstacle()
{
//	int i;
	int distanceVoice, distanceRate;

//	for( i = 0; i < 5; i++ )
//	{
//		printf("UltrasonicWave_Distance_Walk: %d\r\n", UltrasonicWave_Distance_Walk[i]);
//	}
	
	Obstacle(UltrasonicWave_Distance, UltrasonicWave_Distance_Walk,&distanceVoice, &distanceRate );      //�����ϰ�����Ϣ

	if(flag_FALLING==1)   //���ä�˴���ˤ��״̬����һֱ�������ѹ��ܣ����ڲ����ϰ�����ʾ����
			return ;
//	p_debug(" $$%d\r\n", distanceVoice);
	if( MODE_FLAG )
	{
//		if(distanceVoice)
//			PlayVoice(distanceVoice);                  //�޸�����ģʽ	
	}
	else
	{
		printf("Ƶ�ʣ�%d\r\n",distanceRate);
		PlayRate(distanceRate);                    //����Ƶ��ģʽ
	}
}

/*
 * ��������UltrasonicWave_StartMeasure
 * ����  ����ʼ��࣬����һ��>10us�����壬Ȼ��������صĸߵ�ƽʱ��
 * ����  ��port = TRIG_PORTX ,pin = TRIG_PINX
 * ���  ����	
 */
static void UltrasonicWave_StartMeasure(GPIO_TypeDef *  port, int32_t pin)
{
  GPIO_SetBits(port,pin); 		  //��>10US�ĸߵ�ƽ�TRIG_PORT,TRIG_PIN��������define����?
  ObstacleDelayUs(11);		                      //��ʱ20US
  GPIO_ResetBits(port,pin);

}


/****************************************************************************
* ��    �ƣ�void UltrasonicWave(void *arg)
* ��    �ܣ�����������߳�
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/
void UltrasonicWave(int portNum)
{
    if( TIM_ICUserValueStructure[0].Capture_FinishFlag == 1 )  
	{
	    dealTIM_ICUserValueStructureData(TIM_ICUserValueStructure[0]);
		TIM_ICUserValueStructure[0].Capture_FinishFlag = 0;
	}
    if( TIM_ICUserValueStructure[1].Capture_FinishFlag == 1 )  
	{
	    dealTIM_ICUserValueStructureData(TIM_ICUserValueStructure[1]);
//		p_debug("test\r\n");
		TIM_ICUserValueStructure[1].Capture_FinishFlag = 0;
	}	
	switch(portNum)          //��ʼ��࣬����һ��>10us�����壬
	{
		case 0: UltrasonicWave_StartMeasure(TRIG_PORT1,TRIG_PIN1); break;
		case 1: UltrasonicWave_StartMeasure(TRIG_PORT2,TRIG_PIN2); break;
	}
//	 ObstacleDelayUs(6000);
//p_debug("ssd\r\n");	
}




/******************* (C) 1209 Lab *****END OF FILE************/
