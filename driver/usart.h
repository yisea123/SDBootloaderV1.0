#ifndef __USART_H__
#define __USART_H__

#define UART1_BOUND_RATE 115200
#define EN_USART1_RX 1

#define UART3_BOUND_RATE 19200
#define UART3_BUF_LEN 64
#define EN_USART3_RX 1

void uart1_send_data (int ch);
void uart1_init (void);
void uart1_puts(const char *s);
void stop_uart1_receive (void);
void start_uart1_receive (void);
void start_uart1_dma (u32 _memBaseAddr, U16 _size);

void uart3_init (void);
void start_uart3_dma (u32 _memBaseAddr, U16 _size);


#define my_putc uart1_send_data
#define my_puts uart1_puts

extern unsigned char uart3_rec_buf[UART3_BUF_LEN];
extern U16 uart3_rec_count;

//extern U16 RS485_FrameEndFlag;


#endif
