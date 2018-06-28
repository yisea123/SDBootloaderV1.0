#include "main.h"

/**
  * @brief  初始化控制LED的IO
  * @param  无
  * @retval 无
  */
void led_init (void)
{		
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;
	/*开启GPIOB和GPIOF的外设时钟*/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE); 
	/*设置引脚模式为通用推挽输出*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	/*设置引脚速率为50MHz */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	/*选择要控制的GPIOB引脚*/															   
	GPIO_InitStructure.GPIO_Pin = LED1_MAP | LED2_MAP | LED3_MAP;	
	/*调用库函数，初始化GPIOB*/
	GPIO_Init(GPIOB, &GPIO_InitStructure);		
	/* 关闭所有led灯	*/
	GPIO_SetBits(GPIOB, LED1_MAP | LED2_MAP | LED3_MAP);	 		
}
/*********************************************END OF FILE**********************/

