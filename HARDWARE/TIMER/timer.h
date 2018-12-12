#ifndef __TIMER_H
#define __TIMER_H

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//ALIENTEKս��STM32������
//��ʱ�� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/4
//�汾��V1.1
//��Ȩ���У�����ؾ���
//Copyright(C) �������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//********************************************************************************
#define PMW_WIDTH  100
 

#define SYS_CLK 72
#define TIM2_ARR  499
#define TIM2_PSC  71

#define TIM3_ARR  999
#define TIM3_PSC  71

#define TIM4_ARR  999
#define TIM4_PSC  71

#define TIM5_ARR  65535
#define TIM5_PSC  71

//#define TIM6_ARR  31250
#define TIM6_ARR  (((8 * 1000) / 32) - 1) // (((N * 1000) / 32) - 1) N ms ����һ��DAC����
#define TIM6_PSC  71

#define TIM7_ARR  3999
#define TIM7_PSC  71

#define TIM2_INT_CYCLE (((TIM2_ARR + 1) * (TIM2_PSC + 1)) / SYS_CLK) //us
#define TIM3_INT_CYCLE (((TIM3_ARR + 1) * (TIM3_PSC + 1)) / SYS_CLK) //us
#define TIM4_INT_CYCLE (((TIM4_ARR + 1) * (TIM4_PSC + 1)) / SYS_CLK) //us
#define TIM5_INT_CYCLE (((TIM5_ARR + 1) * (TIM5_PSC + 1)) / SYS_CLK) //us
#define TIM6_INT_CYCLE (((TIM6_ARR + 1) * (TIM6_PSC + 1)) / SYS_CLK) //us
#define TIM7_INT_CYCLE (((TIM7_ARR + 1) * (TIM7_PSC + 1)) / SYS_CLK) //us

void TIM2_Int_Init(u16 arr,u16 psc);
void TIM3_PWM_Init(u16 arr,u16 psc);
void TIM4_PWM_Init(u16 arr,u16 psc);
void TIM5_PWM_Init(u16 arr,u16 psc);
void TIM6_PWM_Init(u16 arr,u16 psc);
void TIM7_PWM_Init(u16 arr,u16 psc);

unsigned long long get_tim5_ticks (void);
void refresh_dma1_cycle (void);
void refresh_adc1_cycle (void);

extern u16 tim2_irq_cycle;

extern unsigned long long tim5_cur_cnt;
extern unsigned long long tim5_pre_cnt;

#endif