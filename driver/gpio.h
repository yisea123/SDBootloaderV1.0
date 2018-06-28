#ifndef __GPIO_H__
#define __GPIO_H__


#define LED1_MAP GPIO_Pin_9
#define LED2_MAP GPIO_Pin_8
#define LED3_MAP GPIO_Pin_5

////////////////////////////////////////////////// 
#define LED1 PBout(9)// PB9
#define LED2 PBout(8)// PB8
#define LED3 PBout(5)// PB5	


void led_init (void);


#endif


