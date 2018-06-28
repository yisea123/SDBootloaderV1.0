#ifndef __MODBUSRTU_H
#define __MODBUSRTU_H

#define MODBUS_RTU_USE_UART 1
#define MODBUS_RTU_ADDR 0x02

#define MODBUS_VIRTUAL_INPUT_NUM 8
#define MODBUS_INPUT_NUM 8
#define MODBUS_OUTPUT_NUM 20 + MODBUS_VIRTUAL_INPUT_NUM
#define MODBUS_REG_NUM 128

#define MODBUS_SAVE_DATA_NUM 20
#define MODBUS_SAVE_DATA_SIZE (MODBUS_SAVE_DATA_NUM * 2)
#define MODBUS_SAVE_DATA_START 30

#define RS485_TX_EN PGout(8)


extern U16 Modbus_HoldReg_CPU_Usage;

typedef struct 
{
	U16 data[MODBUS_SAVE_DATA_NUM];
}s_modbus_save_data;


u16 CRC16(u8 *data_buf, u16 len);
void modbus_analyze(u8 * data_buf);
void modbus_init(void);
int save_para (int flag);
int load_para (void);
extern vu32 virtual_input[MODBUS_VIRTUAL_INPUT_NUM];

extern u8 RS485_TX_BUFF[256];//·¢ËÍ»º³åÇø


#endif

 
