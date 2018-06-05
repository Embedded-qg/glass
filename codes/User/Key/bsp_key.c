/**
  ******************************************************************************
  * @file    bsp_key.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   按键应用bsp（扫描模式）
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火 F103-霸道 STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
  
#include "./key/bsp_key.h"  
#include "./usart/bsp_usart1.h"

extern int flag_FALLING;

/**
  * @brief  配置按键用到的I/O口
  * @param  无
  * @retval 无
  */
void Key_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*开启按键端口的时钟*/
	RCC_APB2PeriphClockCmd(KEY1_GPIO_CLK|KEY2_GPIO_CLK,ENABLE);
	
	//选择按键的引脚
	GPIO_InitStructure.GPIO_Pin = KEY1_GPIO_PIN; 
	// 设置按键的引脚为浮空输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//使用结构体初始化按键
	GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStructure);
	
	//选择按键的引脚
	GPIO_InitStructure.GPIO_Pin = KEY2_GPIO_PIN; 
	//设置按键的引脚为浮空输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//使用结构体初始化按键
	GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStructure);	
	
		//选择按键的引脚
	GPIO_InitStructure.GPIO_Pin = KEY3_GPIO_PIN; 
	//设置按键的引脚为浮空输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//使用结构体初始化按键
	GPIO_Init(KEY3_GPIO_PORT, &GPIO_InitStructure);	

	//选择按键的引脚
	GPIO_InitStructure.GPIO_Pin = KEY4_GPIO_PIN; 
	//设置按键的引脚为浮空输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//使用结构体初始化按键
	GPIO_Init(KEY4_GPIO_PORT, &GPIO_InitStructure);	

	//选择按键的引脚
	GPIO_InitStructure.GPIO_Pin = KEY5_GPIO_PIN; 
	//设置按键的引脚为浮空输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//使用结构体初始化按键
	GPIO_Init(KEY5_GPIO_PORT, &GPIO_InitStructure);	

}


 /**
  * @brief  配置嵌套向量中断控制器NVIC
  * @param  无
  * @retval 无
  */
static void NVIC_Configuration2(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* 配置NVIC为优先级组1 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  /* 配置中断源：按键1 */
  NVIC_InitStructure.NVIC_IRQChannel = KEY1_INT_EXTI_IRQ;
  /* 配置抢占优先级 */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* 配置子优先级 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* 使能中断通道 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

}

 /**
  * @brief  配置 IO为EXTI中断口，并设置中断优先级
  * @param  无
  * @retval 无
  */
void EXTI_Key_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	EXTI_InitTypeDef EXTI_InitStructure;

	/*开启按键GPIO口的时钟*/
	RCC_APB2PeriphClockCmd(KEY1_INT_GPIO_CLK,ENABLE);
												
	/* 配置 NVIC 中断*/
	NVIC_Configuration2();
	
/*--------------------------KEY1配置-----------------------------*/
	/* 选择按键用到的GPIO */	
  GPIO_InitStructure.GPIO_Pin = KEY1_INT_GPIO_PIN;
  /* 配置为浮空输入 */	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(KEY1_INT_GPIO_PORT, &GPIO_InitStructure);

	/* 选择EXTI的信号源 */
  GPIO_EXTILineConfig(KEY1_INT_EXTI_PORTSOURCE, KEY1_INT_EXTI_PINSOURCE); 
  EXTI_InitStructure.EXTI_Line = KEY1_INT_EXTI_LINE;
	
	/* EXTI为中断模式 */
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	/* 上升沿中断 */
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  /* 使能中断 */	
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	
}



//static void delay()
//{
//	int i;
//	for(i=10000;i>0;i--);
//}

//按下时输出高电平，松开时输出低电平
 /*
 * 函数名：Key_Scan
 * 描述  ：检测是否有按键按下
 * 输入  ：GPIOx：x 可以是 A，B，C，D或者 E
 *		     GPIO_Pin：待读取的端口位 	
 * 输出  ：KEY_OFF(没按下按键)、KEY_ON（按下按键）
 */
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{			
	/*检测是否有按键按下 */
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON )  
	{	 
		/*等待按键释放 */
		while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON); 
//			delay();
//		if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON )  
			return 	KEY_ON;	 
	}
	else
		return KEY_OFF;
}

int KeyPolling(void)
{
//	if( Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == KEY_ON  )
//	{
//		printf("\nKEY_MODE\n");
//		return KEY_MODE;
//	} 

//	if( Key_Scan(KEY2_GPIO_PORT,KEY2_GPIO_PIN) == KEY_ON  )
//	{
//		printf("\nKEY_BACK\n");
//				return KEY_BACK;
//	}		
//	
//	if( Key_Scan(KEY3_GPIO_PORT,KEY3_GPIO_PIN) == KEY_ON  )
//	{
//		printf("\nKEY_ADD\n");
//				return KEY_ADD;
//	}		

//	if( Key_Scan(KEY4_GPIO_PORT,KEY4_GPIO_PIN) == KEY_ON  )
//	{
//		printf("\nKEY_SUB\n");
//				return KEY_SUB;
//	}		

//	if( Key_Scan(KEY5_GPIO_PORT,KEY5_GPIO_PIN) == KEY_ON  )
//	{
//		printf("\nKEY_SAFE\n");
//		flag_FALLING=0;
//				return KEY_SAFE;
//	}		

//	else
//		return KEY_NO;
}

/*********************************************END OF FILE**********************/


