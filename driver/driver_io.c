#include "main.h"


void drive_io_init (void)
{
	
	
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

























