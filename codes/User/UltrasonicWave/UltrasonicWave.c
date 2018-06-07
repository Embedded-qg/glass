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
#define DEBUG_ON_OFF 0       //1�򿪵��ԡ�0�ر�
//////////////////////////////

static void UltrasonicWave_StartMeasure(GPIO_TypeDef *  port, int32_t pin);              

static int UltrasonicWave_Distance[AVER_NUM_GLASS];      //������ľ���    
int UltrasonicWave_Distance_Walk[AVER_NUM_WALK] = { 500, 500, 500, 500, 500};   //���Ȳɼ�����
static int16_t MAX_DISTACE =150;        //������
int8_t  MEASURE_FLAG = 0;   // 0 �۾��ɼ����ݣ� 1 �ȴ����Ȳɼ�����

int8_t GET_WALK_FLAG = 0;       //���չ������ݱ�־

static void Obstacle(int distance_glass[], int distance_walk[], int* distanceVoice, int* distanceRate );




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
	int distanceVoice, distanceRate;
	int i;
	i = TIM_ICUserValueStructurex.Capture_CCx;
	// ����ߵ�ƽʱ��ļ�������ֵ
//	time = TIM_ICUserValueStructurex.Capture_CcrValue+1;
	// ��ӡ�ߵ�ƽ����ʱ��
	ftime = ((double) TIM_ICUserValueStructurex.Capture_CcrValue+1)/TIM_PscCLK;
	UltrasonicWave_Distance[i-1] = ftime * 340 / 2  * 100;
	
	p_debug( "\r\n%d : distance %d\r\n",i, UltrasonicWave_Distance[i-1]);

	
	Obstacle(UltrasonicWave_Distance, UltrasonicWave_Distance_Walk,&distanceVoice, &distanceRate );      //�����ϰ�����Ϣ

//	PlayRate(distanceRate);                    //����Ƶ��ģʽ
	PlayVoice(distanceVoice);                  //�޸�����ģʽ
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
	static int8_t lateobstacle[4] = {0};      //��¼������β���ϰ���״̬����������ϰ���ʱ+1��2δ��⵽�ϰ���ʱ����
	
	*distanceVoice = OBSTACLE_NO;
	*distanceRate = OBSTACLE_NO;
	
	
	for( ; i < AVER_NUM_GLASS; i++ )                  //�۾����������ϰ����ж�
	{
		if( distance_glass[i] < MAX_DISTACE )           //�ж�ͷ���Ƿ����ϰ���
		{
			lateobstacle[0]++;
			if( lateobstacle[0] > LATE_NUM )
			{
				lateobstacle[0] = LATE_NUM;
			}
		} 
		else
		{
			lateobstacle[0] = 0;
		}
		p_debug("              %d\r\n", distance_glass[i]);
	}
	
	if( distance_walk[0]  < MAX_DISTACE || distance_walk[1] < MAX_DISTACE )  
	{
		lateobstacle[1]++;
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
	if( lateobstacle[1] == LATE_NUM || lateobstacle[2] == LATE_NUM  )
	{
		*distanceVoice = OBSTACLE_AHEAD;
	}    	
//�жϽ����Ƿ����ϰ���
	if( lateobstacle[3] == LATE_NUM )
	{
		*distanceVoice = OBSTACLE_FOOT;
	}
//Ƶ��ģʽ���ϰ�����ʾ,ȡ����ϰ������
	for( i = 0; i < AVER_NUM_GLASS; i++ )                
	{
		mindistace = mindistace > distance_glass[i] ? distance_glass[i] : mindistace;
	}	
	for( i = 0; i < AVER_NUM_WALK; i++ )
	{
		mindistace = mindistace > distance_walk[i] ? distance_walk[i] : mindistace;
	}
	*distanceRate = mindistace / 100;
    	
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
  delayUs(11);		                      //��ʱ20US
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
		p_debug("test\r\n");
		TIM_ICUserValueStructure[1].Capture_FinishFlag = 0;
	}	
	switch(portNum)          //��ʼ��࣬����һ��>10us�����壬
	{
		case 0: UltrasonicWave_StartMeasure(TRIG_PORT1,TRIG_PIN1); break;
		case 1: UltrasonicWave_StartMeasure(TRIG_PORT2,TRIG_PIN2); break;
	}	
}




/******************* (C) 1209 Lab *****END OF FILE************/
