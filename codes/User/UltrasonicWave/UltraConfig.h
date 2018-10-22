#ifndef __ULTRACONFIG_H
#define __ULTRACONFIG_H


#include "stm32f10x.h"
#include "UltrasonicWave.h"

/************ͨ�ö�ʱ��TIM�������壬ֻ��TIM2��3��4��5************/
// ��ʹ�ò�ͬ�Ķ�ʱ����ʱ�򣬶�Ӧ��GPIO�ǲ�һ���ģ����Ҫע��
// ��������Ĭ��ʹ��TIM5

#define            GENERAL_TIM                   TIM4
#define            GENERAL_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM_CLK               RCC_APB1Periph_TIM4
#define            GENERAL_TIM_PERIOD            0XFFFF
#define            GENERAL_TIM_PSC              (72-1)
#define            TIM_PscCLK 					 (72000000/(GENERAL_TIM_PSC+1))
// �ж���غ궨��
#define            GENERAL_TIM_IT_CCx            TIM_IT_CC2
#define            GENERAL_TIM_IRQ               TIM4_IRQn
#define            GENERAL_TIM_INT_FUN           TIM4_IRQHandler

// ��ȡ����Ĵ���ֵ�����궨��
#define            GENERAL_TIM_GetCapturex_FUN                 TIM_GetCapture2
// �����źż��Ժ����궨��
#define            GENERAL_TIM_OCxPolarityConfig_FUN           TIM_OC2PolarityConfig

// ��������ʼ����
#define            GENERAL_TIM_STRAT_ICPolarity                TIM_ICPolarity_Rising
// �����Ľ�������
#define            GENERAL_TIM_END_ICPolarity                  TIM_ICPolarity_Falling



// ��ʱ�����벶���û��Զ�������ṹ������
typedef struct
{   
	uint8_t   Capture_FinishFlag;   // ���������־λ
	uint8_t   Capture_StartFlag;    // ����ʼ��־λ
	uint16_t  Capture_CcrValue;     // ���β���Ĵ�����ֵ֮��
	uint8_t   Capture_CCx;           //ͨ�����
}TIM_ICUserValueTypeDef;

extern TIM_ICUserValueTypeDef TIM_ICUserValueStructure[];
/**************************��������********************************/
void GENERAL_TIM_Init(void);
void TIM2_Init(void);
void UltrasonicWave_Init(void);



/**************************��������********************************/
#define	TRIG_PORT1     			  GPIOA		//TRIG       
#define	TRIG_PIN1      			  GPIO_Pin_4   //TRIG       

#define	TRIG_PORT2     			  GPIOA		//TRIG       
#define	TRIG_PIN2      			  GPIO_Pin_5  //TRIG  

#define RCC_APB2Periph_GPIOx  RCC_APB2Periph_GPIOA










#endif	/* __ULTRACONFIG_H */


