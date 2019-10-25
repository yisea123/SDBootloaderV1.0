#include "main.h"

iapfun jump2app; 
u16 iapbuf[1024];   
void iap_write_appbin(u32 appxaddr,u8 *appbuf,u32 appsize)
{
	u16 t;
	u16 i=0;
	u16 temp;
	u32 fwaddr=appxaddr;//当前写入的地址
	u8 *dfu=appbuf;
	for(t=0;t<appsize;t+=2){						    
		temp=(u16)dfu[1]<<8;
		temp+=(u16)dfu[0];	  
		dfu+=2;//偏移2个字节
		iapbuf[i++]=temp;	    
		if(i==1024){
			i=0;
			STMFLASH_Write(fwaddr,iapbuf,1024);	
			fwaddr+=2048;//偏移2048  16=2*8.所以要乘以2.
		}
	}
	if(i)
		STMFLASH_Write(fwaddr,iapbuf,i);//将最后的一些内容字节写进去.  
}
int AnalyseHEX(char hex[],int len)
{
	char i=1;
	char data;
	int cc=0;
	char temp[3];
	do{
		temp[0] = hex[i++];
		temp[1] = hex[i++];
		temp[2] = '\0';
		data = simple_strtoul(temp, NULL, 16);
		cc += data;
	} while (i<(len-2));
	cc%=256;
	cc=0x100-cc;
	cc &= 0xFF;
	temp[0] = hex[i++];
	temp[1] = hex[i++];
	data = simple_strtoul(temp, NULL, 16);
	return (cc==data)?0:1;
}

int get_hex_struct (s_hex_file *p_hex, char *_data_buf)
{
	char temp[16];
	int i = 0, j;
	p_hex->start = _data_buf[i++];
	temp[0] = _data_buf[i++];
	temp[1] = _data_buf[i++];
	temp[2] = '\0';
	p_hex->len = simple_strtoul(temp, NULL, 16);
	temp[0] = _data_buf[i++];
	temp[1] = _data_buf[i++];
	temp[2] = _data_buf[i++];
	temp[3] = _data_buf[i++];
	temp[4] = '\0';
	p_hex->addr = simple_strtoul(temp, NULL, 16);
	temp[0] = _data_buf[i++];
	temp[1] = _data_buf[i++];
	temp[2] = '\0';
	p_hex->type = simple_strtoul(temp, NULL, 16);
	if (p_hex->len > 0){
		for (j = 0; j < p_hex->len; j++){
			temp[0] = _data_buf[i++];
			temp[1] = _data_buf[i++];
			temp[2] = '\0';
			p_hex->data[j] = simple_strtoul(temp, NULL, 16);
		}
	}
	temp[0] = _data_buf[i++];
	temp[1] = _data_buf[i++];
	temp[2] = '\0';
	p_hex->sum_check = simple_strtoul(temp, NULL, 16);
	return AnalyseHEX(_data_buf, p_hex->len * 2 + 11);
}

#define BUFF_SIZE 64
int iap_func (char *app_name, int opt)
{
//	u32 flash_addr = 0;
//	
//	u32 app_size = 0;
//	U16 hex_data_len = 0;
//	U16 len_temp = 492;
//	int i = 0, index = 0;
//	FATFS fs;
//	FIL file;
//	FRESULT Res;	
//  FILINFO fno;
//	char buf[BUFF_SIZE];
//	s_hex_file p_hex;
//	
//	memset (&fno, 0, sizeof (FILINFO));
//	
////	W25QXX_Read ((U8*)&p_reg_file, SPI_FLASH_INFO_ADDR, sizeof(s_reg_file));
//	my_println ("Start Update App");
//	Res = f_mount(&fs, "0:" , 1);	
//	
//	Res =  f_open(&file, app_name, FA_READ);
//	if (Res != FR_OK){
//		my_print("Open file %s failed, ", app_name);	
//		my_println("Res = %d", Res);
//		return -1;
//	}else{
//		if (opt == 1){
//			Res = f_stat(app_name, &fno);
//			if(fno.fattrib & AM_RDO){
//				my_println ("No Need to Update!");
//				return FR_OK;
//			}
//		}
//		/*
//		
//        my_println("Size: %lu", fno.fsize);
//        my_println("Timestamp: %u/%02u/%02u, %02u:%02u",
//               (fno.fdate >> 9) + 1980, fno.fdate >> 5 & 15, fno.fdate & 31,
//               fno.ftime >> 11, fno.ftime >> 5 & 63);
//        my_println("Attributes: %c%c%c%c%c",
//               (fno.fattrib & AM_DIR) ? 'D' : '-',
//               (fno.fattrib & AM_RDO) ? 'R' : '-',
//               (fno.fattrib & AM_HID) ? 'H' : '-',
//               (fno.fattrib & AM_SYS) ? 'S' : '-',
//               (fno.fattrib & AM_ARC) ? 'A' : '-');
//		strcpy(buf, "/");
//		Res = f_opendir(&dir, buf);              
//		Res = scan_files(buf);
//		get_fileinfo (&dir, &fno);*/
//	}
//	Res = FR_INVALID_OBJECT;
//	for (;;){
//		if (f_eof(&file))
//			break;
//		f_gets (buf, 64, &file);
//		hex_data_len++;
//		if (hex_data_len == len_temp)
//		{
//			len_temp = 0;
//		}
//		if (get_hex_struct (&p_hex, buf)){//文件错误
//			my_println ("Load App failed!");
//			return Res;
//		}
//		switch (p_hex.type){
//			case 0x00://data
//				for (i = 0; i < p_hex.len; i += 2){
//					iapbuf[index++] = p_hex.data[i] | p_hex.data[i+1] << 8;
//					app_size += 2;
//				}
//				if (index == 1024){
//					index = 0;
//					STMFLASH_Write(flash_addr,iapbuf,1024);	
//					flash_addr += 2048;
//					LED1 = !LED1;
//				}
//				break;
//			case 0x01://end
//				Res = FR_OK;
//				break;
//			case 0x04://ex addr
//				flash_addr = (p_hex.data[0]<< 8 | p_hex.data[1]) << 16;
//				if (flash_addr < FLASH_APP1_ADDR){//否则会覆盖bootloader
//					my_println ("App Runtime Addr Error!");
//					return Res;
//				}
//				break;
//			default:break;
//		}
//	}
//	if (index != 0){
//		STMFLASH_Write(flash_addr,iapbuf,index);//将最后的一些内容字节写进去.  
//	}
//	if (opt == 1){
//		f_chmod(app_name, AM_RDO, AM_RDO | AM_ARC);
//	}
//	f_close(&file);
//	return Res;
return 0;
}

//appxaddr:用户代码起始地址.
void iap_load_app(u32 appxaddr)
{
	if(((*(vu32*)appxaddr)&0x2FFE0000)==0x20000000)	//检查栈顶地址是否合法.
	{ 
		jump2app=(iapfun)*(vu32*)(appxaddr+4);		//用户代码区第二个字为程序开始地址(复位地址)		
		MSR_MSP(*(vu32*)appxaddr);					//初始化APP堆栈指针(用户代码区的第一个字用于存放栈顶地址)
		jump2app();									//跳转到APP.
	}
}	

void start_app (void)
{
	if(((*(vu32*)(FLASH_APP1_ADDR+4))&0xFFFF0000)==FLASH_APP1_ADDR)//判断是否为0X08XXXXXX.
	{	 
		my_println("Start App...");
		iap_load_app(FLASH_APP1_ADDR);//执行FLASH APP代码
	}else{
		my_println("FLASH APP Invalid, stop!");
		cmd ();
		my_env.tty = TTY_CONSOLE;
		GPIO_SetBits(GPIOB, LED1_MAP | LED2_MAP | LED3_MAP);	 
		while (1){
			if (my_env.uart0_cmd_flag == 1){
				my_env.uart0_cmd_flag = 0;		
				if (my_env.tty == TTY_CONSOLE){
					vTaskCmdAnalyze ();
				}else if (my_env.tty == TTY_UPDATE){
					update_finished ();
				}
			}
			delay_ms (200);
			LED1 = !LED1;	
			LED2 = !LED2;	
			LED3 = !LED3;	
		}
	}
}

int load_spi_app (u32 app_addr)
{
	return 0;
}
























