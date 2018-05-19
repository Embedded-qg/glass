#ifndef __MP3_H
#define	__MP3_H


#include "stm32f10x.h"


/* ������Ƶģ�����ӵ�GPIO�˿�, �û�ֻ��Ҫ�޸�����Ĵ��뼴�ɸı���Ƶ�MP3���� */

#define MP31_GPIO_PORT    	GPIOB			              /* GPIO�˿� */
#define MP31_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */
#define MP31_GPIO_PIN		GPIO_Pin_8			        /* ���ӵ�SCLʱ���ߵ�GPIO */


#define MP32_GPIO_PORT    	GPIOB			              /* GPIO�˿� */
#define MP32_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */
#define MP32_GPIO_PIN		GPIO_Pin_5			        /* ���ӵ�SCLʱ���ߵ�GPIO */


#define MP33_GPIO_PORT    	GPIOB			              /* GPIO�˿� */
#define MP33_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */
#define MP33_GPIO_PIN		GPIO_Pin_6			        /* ���ӵ�SCLʱ���ߵ�GPIO */

#define MP34_GPIO_PORT    	GPIOB			              /* GPIO�˿� */
#define MP34_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */
#define MP34_GPIO_PIN			GPIO_Pin_7			        /* ���ӵ�SCLʱ���ߵ�GPIO */


/** the macro definition to trigger the MP3 on or off 
  * 1 - off
  *0 - on
  */
#define ON  0
#define OFF 1


/* ֱ�Ӳ����Ĵ����ķ�������IO */
#define	digitalHi(p,i)		 {p->BSRR=i;}	 //���Ϊ�ߵ�ƽ		
#define digitalLo(p,i)		 {p->BRR=i;}	 //����͵�ƽ
#define digitalToggle(p,i) {p->ODR ^=i;} //�����ת״̬


/* �������IO�ĺ� */
#define MP31_TOGGLE		 digitalToggle(MP31_GPIO_PORT,MP31_GPIO_PIN)
#define MP31_OFF		   digitalHi(MP31_GPIO_PORT,MP31_GPIO_PIN)
#define MP31_ON			   digitalLo(MP31_GPIO_PORT,MP31_GPIO_PIN)

#define MP32_TOGGLE		 digitalToggle(MP32_GPIO_PORT,MP32_GPIO_PIN)
#define MP32_OFF		   digitalHi(MP32_GPIO_PORT,MP32_GPIO_PIN)
#define MP32_ON			   digitalLo(MP32_GPIO_PORT,MP32_GPIO_PIN)

#define MP33_TOGGLE		 digitalToggle(MP33_GPIO_PORT,MP33_GPIO_PIN)
#define MP33_OFF		   digitalHi(MP33_GPIO_PORT,MP33_GPIO_PIN)
#define MP33_ON			   digitalLo(MP33_GPIO_PORT,MP33_GPIO_PIN)

#define MP34_OFF		   digitalHi(MP34_GPIO_PORT,MP34_GPIO_PIN)
#define MP34_ON			   digitalLo(MP34_GPIO_PORT,MP34_GPIO_PIN)


void MP3_GPIO_Config(void);
int MP3Run(int num);
#endif /* __MP3_H */
