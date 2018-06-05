#ifndef __KEY_H
#define	__KEY_H


#include "stm32f10x.h"

//  ���Ŷ���
#define    KEY1_GPIO_CLK     RCC_APB2Periph_GPIOA
#define    KEY1_GPIO_PORT    GPIOA			   
#define    KEY1_GPIO_PIN		 GPIO_Pin_0

#define    KEY2_GPIO_CLK     RCC_APB2Periph_GPIOC
#define    KEY2_GPIO_PORT    GPIOA		   
#define    KEY2_GPIO_PIN		  GPIO_Pin_4

#define    KEY3_GPIO_CLK     RCC_APB2Periph_GPIOA
#define    KEY3_GPIO_PORT    GPIOA			   
#define    KEY3_GPIO_PIN		 GPIO_Pin_5

#define    KEY4_GPIO_CLK     RCC_APB2Periph_GPIOA
#define    KEY4_GPIO_PORT    GPIOA			   
#define    KEY4_GPIO_PIN		 GPIO_Pin_6

#define    KEY5_GPIO_CLK     RCC_APB2Periph_GPIOA
#define    KEY5_GPIO_PORT    GPIOA			   
#define    KEY5_GPIO_PIN		 GPIO_Pin_7


//���Ŷ���
#define KEY1_INT_GPIO_PORT         GPIOA
#define KEY1_INT_GPIO_CLK          (RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO)
#define KEY1_INT_GPIO_PIN          GPIO_Pin_0
#define KEY1_INT_EXTI_PORTSOURCE   GPIO_PortSourceGPIOA
#define KEY1_INT_EXTI_PINSOURCE    GPIO_PinSource0
#define KEY1_INT_EXTI_LINE         EXTI_Line0
#define KEY1_INT_EXTI_IRQ          EXTI0_IRQn

#define KEY1_IRQHandler            EXTI0_IRQHandler

#define KEY_NO 			0		//û�а���
#define KEY_MODE		1		//���ܼ�
#define KEY_BACK		2		//���ؼ�
#define KEY_ADD			3		//�Ӻż�
#define KEY_SUB			4		//���ż�
#define KEY_SAFE		5		//��ȫ��




 /** �������±��ú�
	*  ��������Ϊ�ߵ�ƽ������ KEY_ON=1�� KEY_OFF=0
	*  ����������Ϊ�͵�ƽ���Ѻ����ó�KEY_ON=0 ��KEY_OFF=1 ����
	*/
#define KEY_ON	1
#define KEY_OFF	0

//#define KEY_ON	0
//#define KEY_OFF	1

void EXTI_Key_Config(void);
void Key_GPIO_Config(void);
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);
int KeyPolling(void);


#endif /* __KEY_H */

