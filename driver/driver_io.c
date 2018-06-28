#include "main.h"


void drive_io_init (void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟
	/*开启GPIO外设时钟*/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOG, ENABLE); 
	
	/*设置引脚模式为通用推挽输出*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	/*设置引脚速率为50MHz */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	
	/*选择要控制的GPIOB引脚*/															   
	GPIO_InitStructure.GPIO_Pin = OUTPUT_PIN_MAP;
	/*调用库函数，初始化GPIOF*/
	GPIO_Init(GPIOF, &GPIO_InitStructure);	
	/* 关闭所有输出	*/	 
	GPIO_SetBits(GPIOF, OUTPUT_PIN_MAP);	
	
	

	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	////////////////////////////////////////////////////
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
	 									   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	//EXT6
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource6);
	EXTI_InitStructure.EXTI_Line = EXTI_Line6;
	EXTI_Init(&EXTI_InitStructure);
	EXTI_ClearITPendingBit(EXTI_Line6); //清除中断挂起标志位
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//外部中断线6
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = EXT6_INT_PREEM;	//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = EXT6_INT_SUB;			//子优先级
	NVIC_Init(&NVIC_InitStructure);
	//EXT7
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource7);
	EXTI_InitStructure.EXTI_Line = EXTI_Line7;
	EXTI_Init(&EXTI_InitStructure);
	EXTI_ClearITPendingBit(EXTI_Line7); //清除中断挂起标志位
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//外部中断线7
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = EXT7_INT_PREEM;	//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = EXT7_INT_SUB;			//子优先级
	NVIC_Init(&NVIC_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	//EXT8
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource8);
	EXTI_InitStructure.EXTI_Line = EXTI_Line8;
	EXTI_Init(&EXTI_InitStructure);
	EXTI_ClearITPendingBit(EXTI_Line8); //清除中断挂起标志位
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//外部中断线8
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = EXT8_INT_PREEM;	//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = EXT8_INT_SUB;			//子优先级
	NVIC_Init(&NVIC_InitStructure);			
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_11;
	GPIO_Init(GPIOG, &GPIO_InitStructure);		
	//EXT0
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOG,GPIO_PinSource0);
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_Init(&EXTI_InitStructure);
	EXTI_ClearITPendingBit(EXTI_Line0); //清除中断挂起标志位
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//外部中断线0
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = EXT0_INT_PREEM;	//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = EXT0_INT_SUB;			//子优先级
	NVIC_Init(&NVIC_InitStructure);
	//EXT1
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOG,GPIO_PinSource1);
	EXTI_InitStructure.EXTI_Line = EXTI_Line1;
	EXTI_Init(&EXTI_InitStructure);
	EXTI_ClearITPendingBit(EXTI_Line1); //清除中断挂起标志位
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//外部中断线1
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = EXT1_INT_PREEM;	//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = EXT1_INT_SUB;			//子优先级
	NVIC_Init(&NVIC_InitStructure);
	//EXT2
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOG,GPIO_PinSource2);
	EXTI_InitStructure.EXTI_Line = EXTI_Line2;
	EXTI_Init(&EXTI_InitStructure);
	EXTI_ClearITPendingBit(EXTI_Line2); //清除中断挂起标志位
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//外部中断线2
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = EXT2_INT_PREEM;	//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = EXT2_INT_SUB;			//子优先级
	NVIC_Init(&NVIC_InitStructure);
	//EXT3
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOG,GPIO_PinSource3);
	EXTI_InitStructure.EXTI_Line = EXTI_Line3;
	EXTI_Init(&EXTI_InitStructure);
	EXTI_ClearITPendingBit(EXTI_Line3); //清除中断挂起标志位
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//外部中断线3
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = EXT3_INT_PREEM;	//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = EXT3_INT_SUB;			//子优先级
	NVIC_Init(&NVIC_InitStructure);		
	//EXT11
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOG,GPIO_PinSource11);
	EXTI_InitStructure.EXTI_Line = EXTI_Line11;
	EXTI_Init(&EXTI_InitStructure);
	EXTI_ClearITPendingBit(EXTI_Line11); //清除中断挂起标志位
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//外部中断线11
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = EXT11_INT_PREEM;	//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = EXT11_INT_SUB;			//子优先级
	NVIC_Init(&NVIC_InitStructure);			
	
}

//外部中断线0的中断服务函数
void EXTI0_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line0); //清除中断线0挂起标志位
}
//外部中断线1的中断服务函数
void EXTI1_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line1); //清除中断线1挂起标志位
}
//外部中断线2的中断服务函数
void EXTI2_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line2); //清除中断线2挂起标志位
}
//外部中断线3的中断服务函数
void EXTI3_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line3); //清除中断线3挂起标志位
}

//外部中断线6 7 8的中断服务函数
void EXTI9_5_IRQHandler(void)
{
	if (PCin(6) == 0){
	}else if (PCin(7) == 0){
	}else if (PAin(8) == 0){
	}
	EXTI_ClearITPendingBit(EXTI_Line6 | EXTI_Line7 | EXTI_Line8); //清除中断线6挂起标志位
}
//外部中断线11的中断服务函数
void EXTI15_10_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line11); //清除中断线11挂起标志位
}

























