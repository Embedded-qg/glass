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



static void UltrasonicWave_StartMeasure(GPIO_TypeDef *  port, int32_t pin);              

int UltrasonicWave_Distance[AVER_NUM_GLASS];      //������ľ���    
static int16_t MAX_DISTACE = 300;        //������
int8_t  IT_TAG = 0;          //��ȡ��־��Ϊ1ʱ��ʾ�Զ�ȡ������

/*
 * ��������UltrasonicWave_Configuration
 * ����  ��������ģ��ĳ�ʼ��
 * ����  ����
 * ���  ����	
 */
void UltrasonicWave_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOx, ENABLE);
    
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		     //��Ϊ�������ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_InitStructure.GPIO_Pin = TRIG_PIN1;					
	GPIO_Init(TRIG_PORT1, &GPIO_InitStructure);	
	GPIO_InitStructure.GPIO_Pin = TRIG_PIN2;					
	GPIO_Init(TRIG_PORT2, &GPIO_InitStructure);		
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
	int i;
	i = TIM_ICUserValueStructurex.Capture_CCx;
	// ����ߵ�ƽʱ��ļ�������ֵ
//	time = TIM_ICUserValueStructurex.Capture_CcrValue+1;
	// ��ӡ�ߵ�ƽ����ʱ��
	ftime = ((double) TIM_ICUserValueStructurex.Capture_CcrValue+1)/TIM_PscCLK;
	UltrasonicWave_Distance[i] = ftime * 340 / 2  * 100;
//	printf( "\r\n time %d\r\n",time );	
//	printf( "\r\n ftime %lf\r\n",ftime );
	printf( "\r\n%d : distance %d\r\n",i, UltrasonicWave_Distance[i]);
//	printf( "\r\n��%d.%d s\r\n",time/TIM_PscCLK,time%TIM_PscCLK );	
}



/*
 * ��������UltrasonicWave_StartMeasure
 * ����  ����ʼ��࣬����һ��>10us�����壬Ȼ��������صĸߵ�ƽʱ��
 * ����  ��port = TRIG_PORTX ,pin = TRIG_PINX
 * ���  ����	
 */
void UltrasonicWave_StartMeasure(GPIO_TypeDef *  port, int32_t pin)
{
  GPIO_SetBits(port,pin); 		  //��>10US�ĸߵ�ƽ�TRIG_PORT,TRIG_PIN��������define����?
  delayUs(11);		                      //��ʱ20US
  GPIO_ResetBits(port,pin);

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
	*distanceVoice = 0;
	*distanceRate = 0;
	for( ; i < AVER_NUM_GLASS; i++ )                  //�۾����������ϰ����ж�
	{
		if( distance_glass[i] < MAX_DISTACE )           //�ж�ͷ���Ƿ����ϰ���
		{
			*distanceVoice = 3; 
		} 
	}
	//�ж������Ƿ����ϰ���
	if( distance_walk[4]  < MAX_DISTACE || distance_walk[3] < MAX_DISTACE || distance_walk[2] < MAX_DISTACE  )  
	{
		if( *distanceVoice != 0 )                   //��ͷ��Ҳ�����ϰ�����ֱ����ʾǰ�������ϰ���
		{
			*distanceVoice = 2; 
		}
		else
		{
			*distanceVoice = 1; 			
		}
	}
	 //�ж���ǰ���Ƿ����ϰ���
	if( distance_walk[0]  < MAX_DISTACE || distance_walk[1] < MAX_DISTACE )  
	{
		*distanceVoice = 2; 
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

////////���Կ���//////////////
#ifdef DEBUG_ON_OFF 
#undef  DEBUG_ON_OFF
#endif
#define DEBUG_ON_OFF 0      //1�򿪵��ԡ�0�ر�
//////////////////////////////


/****************************************************************************
* ��    �ƣ�void UltrasonicWave(void *arg)
* ��    �ܣ�����������߳�
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/
void UltrasonicWave(int* num)
{
	static int i = 0;            //ɾ��������
	static int8_t tag;	
	
//	p_debug("&tag %d\r\n", tag);
//	p_debug("&i %d\r\n", i);
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
	switch(tag)          //��ʼ��࣬����һ��>10us�����壬
	{
		case 0: UltrasonicWave_StartMeasure(TRIG_PORT1,TRIG_PIN1); break;
		case 1: UltrasonicWave_StartMeasure(TRIG_PORT2,TRIG_PIN2); break;
	}
	p_debug("#tag %d\r\n", tag);	
	tag = (tag +1) % AVER_NUM_GLASS;
	p_debug("@tag %d\r\n", tag);	

	
}


/******************* (C) 1209 Lab *****END OF FILE************/
