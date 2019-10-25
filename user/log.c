#include "main.h"



S16 coin_log (char *fmt, ...)
{
//	FATFS fs;
//	FIL file;
//	FRESULT Res;	
	va_list ap;
	char string[64];
	char log_str[64];

	va_start(ap, fmt);
	vsprintf(string, fmt, ap);
		
//	Res = f_mount(&fs, "0:" , 1);	

//	Res =  f_open(&file, "log.txt", FA_WRITE);
//	if (Res != FR_OK)
//	{
//		Res =  f_open(&file, "log.txt", FA_WRITE | FA_CREATE_ALWAYS);
//		if (Res != FR_OK) {
//			my_print("Open file log.txt failed, ");	
//			my_println("Res = %d\n", Res);
//			return -1;
//		}
//	}
	
	sprintf((char *)log_str, "LOG: %4d-%02d-%02d %02d:%02d:%02d %s\n", 
						calendar.w_year, calendar.w_month, calendar.w_date, calendar.hour, calendar.min, calendar.sec,
						string);
	
	my_print ("%s", log_str);	
//	
//	f_lseek(&file, file.fsize);
//	f_printf (&file, "%s", log_str);	
//	
//	f_close(&file);
	
	va_end(ap);
	return 0;
}

