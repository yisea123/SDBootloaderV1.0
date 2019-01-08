#include "main.h"


//const char fill_data[1024 * 493] = {0x55};
 
//通过串口打印SD卡相关信息
void show_sdcard_info(void)
{
	switch(SDCardInfo.CardType)
	{
		case SDIO_STD_CAPACITY_SD_CARD_V1_1:printf("Card Type:SDSC V1.1\r\n");break;
		case SDIO_STD_CAPACITY_SD_CARD_V2_0:printf("Card Type:SDSC V2.0\r\n");break;
		case SDIO_HIGH_CAPACITY_SD_CARD:printf("Card Type:SDHC V2.0\r\n");break;
		case SDIO_MULTIMEDIA_CARD:printf("Card Type:MMC Card\r\n");break;
	}	
  	printf("Card ManufacturerID:%d\r\n",SDCardInfo.SD_cid.ManufacturerID);	//制造商ID
 	printf("Card RCA:%d\r\n",SDCardInfo.RCA);								//卡相对地址
	printf("Card Capacity:%d MB\r\n",(u32)(SDCardInfo.CardCapacity>>20));	//显示容量
 	printf("Card BlockSize:%d\r\n",SDCardInfo.CardBlockSize);			//显示块大小
} 


#ifdef USE_LUA
int lua_main( int argc, char **argv );
// +================== New task interface ==================+
static void start_lua() {
  char* lua_argv[] = { (char *)"lua", (char *)"-i", NULL };
  my_println("Task task_lua started.\n");
  lua_main( 2, lua_argv );
  my_println("Task task_lua quit.\n");
  // Only enable UART interrupts once we've successfully started up,
  // otherwise the task queue might fill up with input events and prevent
  // the start_lua task from being posted.
  //ETS_UART_INTR_ENABLE();
}
#endif

int main (void)
{
	int wait_time = 3;
	delay_init();	    	 //延时函数初始化	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart1_init ();
	led_init ();
	drive_io_init ();
	system_env_init ();	
	//uart3_init ();

	my_println ();
	my_println ("*****************************************************************");
	my_println ("*                   SDBootloader Start                      *");
	my_println ("*****************************************************************");
	my_println ("my_cmd_Start at 0x%08x", (unsigned int)MY_CMD_RO_SEC_START);
	my_println ("my_cmd_End at   0x%08x", (unsigned int)MY_CMD_RO_SEC_END);
	my_println ("my_cmd_Length   0x%02x", (unsigned int)MY_CMD_RO_SEC_LENGTH);
//	my_println ("****************************RTC Info*****************************");
//	RTC_Init();	  			//RTC初始化
//	my_print ("%04d-%02d-%2d  ", calendar.w_year, calendar.w_month, calendar.w_date); 
//	my_println ("%02d:%02d:%02d", calendar.hour, calendar.min, calendar.sec);
//	my_println ("**************************SPI Flash Info*************************");
//	W25QXX_Init();			//W25QXX初始化
//	if (W25QXX_ReadID()!=W25Q128){
//		my_println ("W25Q128 Check Failed! ");
//	}else{
//		my_println ("W25Q128 Ready! ");
//	}
//	my_println ("***************************SD Card Info**************************");
//	if (SD_Init()){
//		my_println ("SD Card Init Error! Please Check! ");
//	}else{	
//		my_env.SD_exist = 0x55;
//		show_sdcard_info();	//打印SD卡相关信息
//	}
//	my_println ("***************************FatFs Info**************************");
//	my_println ("*****************************************************************");
//	LOG ("System Start");
	my_println ("*****************************************************************");
	/*************************************************************************************/
#ifdef USE_LUA
	my_env.tty = 1;
	start_lua ();
#endif
	/*************************************************************************************/
	
	
	if (my_env.SD_exist == 0x55){
		check_reg ();
	}
	
	my_env.roll_count = 0;
	while (wait_time){
		if (my_env.tty == 1){
			start_uart1_receive ();
			break;
		}
		Rollback ();
		my_println ("Start App after... %d", wait_time--);
		delay_ms (250);
		LED2 = !LED2;
		delay_ms (250);
		LED2 = !LED2;
		delay_ms (250);
		LED2 = !LED2;
		delay_ms (250);
		LED2 = !LED2;
	}
	Rollback ();
	my_println ("Start App after... %d", wait_time);
	if (my_env.tty == 0){
		cmd ();
	}else{
		my_print ("Login:");
	}
	while (my_env.tty){
		if (my_env.uart0_cmd_flag == 1){ 
			my_env.uart0_cmd_flag = 0;			
			vTaskCmdAnalyze ();
		}
		delay_ms (100);
		LED2 = !LED2;	
	}
	my_println ();
	if (iap_func (DEFAULT_APP_FILE_NAME, 1) != 0){
	}
	start_app ();
	while (1);

} 


