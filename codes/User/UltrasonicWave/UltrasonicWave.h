#ifndef __UltrasonicWave_H
#define	__UltrasonicWave_H

#include "stm32f10x.h"
#include "bsp_delay.h"
#include "bsp_usart1.h"
#include "bsp_GeneralTim.h"






#define	TRIG_PORT1     			  GPIOA		//TRIG       
#define	TRIG_PIN1      			  GPIO_Pin_4   //TRIG       

#define	TRIG_PORT2     			  GPIOA		//TRIG       
#define	TRIG_PIN2      			  GPIO_Pin_5  //TRIG     



#define RCC_APB2Periph_GPIOx  RCC_APB2Periph_GPIOA

#define AVER_NUM_GLASS        2              //�۾��ϳ���������
#define AVER_NUM_WALK         5              //�����ϳ���������
#define AVER_NUM_ALL   AVER_NUM +AVER_NUM_WALK    //������������

extern int8_t  IT_TAG;

int getRange(void);
int minusDistance(void);
int addDistance(void);
void UltrasonicWave_Configuration(void);               //�Գ�����ģ���ʼ��
void UltrasonicWave(int* num);

#endif /* __UltrasonicWave_H */

