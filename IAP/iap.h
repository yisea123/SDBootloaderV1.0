#ifndef	_IAP_H
#define _IAP_H

#define HEX_DATA_START 9

#define FLASH_APP1_ADDR		0x08010000  	//第一个应用程序起始地址(存放在FLASH)
#define FLASH_REG_INFO_ADDR		(0x0800D000)  	//
#define FLASH_DATA_ADDR		(FLASH_REG_INFO_ADDR + 1000)  	//第一个应用程序起始地址(存放在SPI FLASH)


#define DEFAULT_APP_FILE_NAME "0:/Counter.hex"

typedef  void (*iapfun)(void);				//定义一个函数类型的参数.
typedef struct{
	U8 start;
	U8 len;
	u16 addr;
	U8 type;
	char data[16];
	U8 sum_check;
}s_hex_file;

#define REG_SIZE 16
typedef struct{
	char reg_info[REG_SIZE];
	uint32_t time_limit;
	uint32_t time_use;
}s_reg_file;



void iap_load_app(u32 appxaddr);			//执行flash里面的app程序
int iap_func (char *app_name, int opt);
void start_app (void);
int load_spi_app (u32 app_addr);



#endif

 
