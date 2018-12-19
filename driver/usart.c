#include "main.h"

//U16 RS485_FrameEndFlag;

void uart1_send_data (int ch)
{
    //USART1->SR;  //USART_GetFlagStatus(USART1, USART_FLAG_TC) 解决第一个字符发送失败的问题
	
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
	if(ch == '\n'){
		USART_SendData(USART1, '\r');
		my_env.roll_count++;
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
	}
    //一个一个发送字符
    USART_SendData(USART1, (unsigned char) ch);
    //等待发送完成
    while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
}

void uart1_puts(const char *s)
{
	while (*s) {
		uart1_send_data(*s++);
	}
}

void uart1_dma_config (void)
{
}
//串口1 DMA方式发送中断  
void DMA1_Channel4_IRQHandler(void)  
{
	if(DMA_GetITStatus(DMA1_IT_TC4)){
		//清除标志位  
		DMA_ClearFlag(DMA1_FLAG_TC4);//清除通道4传输完成标志
		DMA_ClearITPendingBit(DMA1_IT_GL4); //清除全部中断标志 
		USART_DMACmd(USART1,USART_DMAReq_Tx, DISABLE); //DISABLE串口1的DMA发送  
		DMA_Cmd(DMA1_Channel4, DISABLE);  
	}
} 

void start_uart1_dma (u32 _memBaseAddr, U16 _size)
{
	/*--------------------------- DMAy Channelx CMAR Configuration ----------------*/
	/* Write to DMA1 Channel4 CMAR */
	DMA1_Channel4->CMAR = _memBaseAddr;
	DMA_SetCurrDataCounter (DMA1_Channel4, _size);
	DMA_Cmd(DMA1_Channel4, ENABLE);  
	USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE); //使能串口1的DMA发送   
}

void start_uart3_dma (u32 _memBaseAddr, U16 _size)
{
	/*--------------------------- DMAy Channelx CMAR Configuration ----------------*/
	/* Write to DMA1 Channel2 CMAR */
	DMA1_Channel2->CMAR = _memBaseAddr;
	DMA_SetCurrDataCounter (DMA1_Channel2, _size);
	DMA_Cmd(DMA1_Channel2, ENABLE);  
	USART_DMACmd(USART3,USART_DMAReq_Tx,ENABLE); //使能串口1的DMA发送   
}
void uart1_init (void)
{
	//GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
  
	//USART1_TX   GPIOA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
	//USART1_RX	  GPIOA.10初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

	//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = UART1_RX_INT_PREEM;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = UART1_RX_INT_SUB;		//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
	//USART 初始化设置

	USART_InitStructure.USART_BaudRate = UART1_BOUND_RATE;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

	USART_Init(USART1, &USART_InitStructure); //初始化串口1
	//USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断 
	USART_ITConfig(USART1,USART_IT_IDLE,ENABLE); //开启串口空闲中断 
	USART_Cmd(USART1, ENABLE);                    //使能串口1 
	
	uart1_dma_config ();

}


void stop_uart1_receive (void)
{
    DMA_Cmd(DMA1_Channel5,DISABLE);
	USART_ITConfig(USART1,USART_IT_IDLE, DISABLE); //开启串口空闲中断 
}
void start_uart1_receive (void)
{        
	//设置传输数据长度  
	memset (cmd_analyze.rec_buf, 0, CMD_BUF_LEN);
    DMA_Cmd(DMA1_Channel5,DISABLE);
    DMA_SetCurrDataCounter(DMA1_Channel5, CMD_BUF_LEN);  
    DMA_Cmd(DMA1_Channel5,ENABLE);
	USART_ITConfig(USART1,USART_IT_IDLE, ENABLE); //开启串口空闲中断 
}


#if EN_USART1_RX   //如果使能了接收
//串口1接收中断     
void USART1_IRQHandler(void)                                 
{     
    uint32_t temp = 0;    
    if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)  
    {  
      temp = USART1->SR;  
      temp = USART1->DR; //清USART_IT_IDLE标志  
			if (my_env.tty){
				fill_rec_buf(temp);
			}else if (temp == ' '){
				my_env.tty_ctr++;
				if (my_env.tty_ctr > 5){
					my_env.tty = 1;
				}
			}else{
				my_env.tty_ctr = 0;
			}
    }else{
        temp = USART1->SR;  
        temp = USART1->DR; //清USART_IT_IDLE标志  
	}
} 

#endif

//串口3 DMA方式发送中断  
void DMA1_Channel2_IRQHandler(void)  
{  
	if(DMA_GetITStatus(DMA1_IT_TC2)){
		//清除标志位  
		DMA_ClearFlag(DMA1_FLAG_TC2);//清除通道4传输完成标志
		DMA_ClearITPendingBit(DMA1_IT_GL2); //清除全部中断标志 
		USART_DMACmd(USART3,USART_DMAReq_Tx, DISABLE); //DISABLE串口1的DMA发送  
		DMA_Cmd(DMA1_Channel2, DISABLE);  
	}
} 
void uart3_dma_config (void)
{
}

void uart3_init (void)
{
	//GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//使能GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//使能USART1时钟
  
	//USART3_TX   GPIOB10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB10
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB10
   
	//USART3_RX	  GPIOB11初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PB11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB11

	//Usart3 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = UART3_RX_INT_PREEM;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = UART3_RX_INT_SUB;		//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
	//USART 初始化设置

	USART_InitStructure.USART_BaudRate = UART3_BOUND_RATE;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

	USART_Init(USART3, &USART_InitStructure); //初始化串口3
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启串口接受中断
	USART_Cmd(USART3, ENABLE);                    //使能串口3 
	
	uart3_dma_config ();
}

#if EN_USART3_RX   //如果使能了接收
unsigned char uart3_rec_buf[UART3_BUF_LEN];
U16 uart3_rec_count = 0;
void USART3_IRQHandler(void)                	//串口3中断服务程序
{
	__IO u8 Res;
	//Res = USART1->SR;
	
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
	#if (MODBUS_RTU_USE_UART == 3)
		TIM_SetCounter(TIM7,0);//当接收到一个新的字节，将定时器7复位为0，重新计时（相当于喂狗）
		TIM_Cmd(TIM7,ENABLE);//开始计时
	#endif
		uart3_rec_buf[uart3_rec_count++] = USART_ReceiveData(USART3);	//读取接收到的数据
	}else{
		Res = USART_ReceiveData(USART3);	//读取接收到的数据
	}
} 
#endif











