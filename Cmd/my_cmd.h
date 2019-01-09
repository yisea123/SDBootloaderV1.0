#ifndef _MY_CMD_
#define _MY_CMD_


#define CTRL_C 0X03


#define HEX_TO_DEC(X) (X >> 4) * 10 + (X & 0xf)

enum 
{
	TTY_IDLE = 0,
	TTY_CONSOLE,
	TTY_UPDATE,
	TTY_MODBUS
};

/*
 * Monitor Command Table
 */
 
#define CFG_CBSIZE	64		/* Console I/O Buffer Size	*/
 #define CFG_MAXARGS		16	/* max number of command args   */
#define CONFIG_CBSIZE					64		/* Console I/O Buffer Size	*/
#define CONFIG_SYS_CBSIZE				64		/* Console I/O Buffer Size	*/
#define CONFIG_MAXARGS					16		/* max number of command args	*/
#define CONFIG_SYS_MAXARGS				16		/* max number of command args	*/
#define CFG_LONGHELP				/* undef to save memory		*/
#define CONFIG_SYS_LONGHELP
//#define CONFIG_AUTO_COMPLETE	1       /* add autocompletion support   */

struct cmd_tbl_s {
	char		*name;		/* Command Name			*/
	int		maxargs;	/* maximum number of arguments	*/
	int		repeatable;	/* autorepeat allowed?		*/
					/* Implementation function	*/
	int		(*cmdhandle)(struct cmd_tbl_s *, int, int, char *[]);
	char		*usage;		/* Usage message	(short)	*/
#ifdef	CFG_LONGHELP
	char		*help;		/* Help  message	(long)	*/
#endif
#ifdef CONFIG_AUTO_COMPLETE
	/* do auto completion on the arguments */
	int		(*complete)(int argc, char *argv[], char last_char, int maxv, char *cmdv[]);
#endif
};

typedef struct cmd_tbl_s	cmd_tbl_t;


extern cmd_tbl_t  __u_boot_cmd_start;
extern cmd_tbl_t  __u_boot_cmd_end;

#define Struct_Section __attribute__ ((unused, section("my_cmd_sec")))


#define MY_CMD(name,maxargs,rep,cmd,usage,help) \
 __align(4) cmd_tbl_t __my_cmd_##name Struct_Section = {#name, maxargs, rep, cmd, usage, help}
 
extern cmd_tbl_t __my_cmd_task_manager;


typedef struct 
{  
	char const *cmd_name;                        //命令字符串  
	int32_t max_args;                            //最大参数数目  
	void (*handle)(int argc, void * cmd_arg);     //命令回调函数  
	char  *help;                                 //帮助信息  
}cmd_list_struct; 

#define _CMD_BUF_LEN 2048
#define  CMD_BUF_LEN _CMD_BUF_LEN*2         //命令缓存的最大长度  
       
typedef struct 
{  
	char rec_buf0[_CMD_BUF_LEN];            //接收命令缓冲区  
	char rec_buf1[_CMD_BUF_LEN];            //接收命令缓冲区  
//	char processed_buf[CMD_BUF_LEN];      //存储加工后的命令(去除控制字符)  
//	int32_t cmd_arg[ARG_NUM];             //保存命令的参数  
}s_cmd_analyze_struct;  

typedef union
{
	char rec_buf[CMD_BUF_LEN];
	s_cmd_analyze_struct data;
}cmd_analyze_struct;

enum
{
	LOGIN_USERNAME = 0x55,
	LOGIN_PASSWORD = 0x5a,
	LOGIN_IN = 0xa5,
};


typedef struct
{
	S16 sys_break;
	U16 roll_count;
	U16 watch_ch;
	U16 dma_state;
	U16 print;
	U16 tty;
	U16 tty_ctr;
	S16 uart0_cmd_flag;
	U16 system_runing;
	U16 modbus_rtu_addr;
	U16 login_state;
	char username[33];
	char password[33];
	U16 SD_exist;
}s_system_env;

typedef struct
{
	cmd_tbl_t * cmdtp;     //命令回调函数  
	int argc;
	void * cmd_arg;
}s_task_parameter;

extern s_system_env my_env;
extern cmd_analyze_struct cmd_analyze; 
extern uint32_t rec_count;

void system_env_init (void);
void print_ng_data (S16 index);
void print_system_env_info (void);
void fill_rec_buf(char data);
void vTaskCmdAnalyze( void );

int run_command (const char *cmd, int flag);
int cmd_usage(cmd_tbl_t *cmdtp);
cmd_tbl_t *find_cmd (const char *cmd);
unsigned long simple_strtoul(const char *cp,char **endp,unsigned int base);
u32 GetLockCode(char *id);
int mk_reg (int flag);
S16 check_reg (void);

void update_finished (void);

void Rollback(void);





extern unsigned int Image$$MY_CMD_RO_SEC$$Base;
extern unsigned int Image$$MY_CMD_RO_SEC$$Length;

#define MY_CMD_RO_SEC_LENGTH 		(&Image$$MY_CMD_RO_SEC$$Length)
#define MY_CMD_RO_SEC_START 		(&Image$$MY_CMD_RO_SEC$$Base)
#define MY_CMD_RO_SEC_END 			((unsigned int)(&Image$$MY_CMD_RO_SEC$$Base) + (unsigned int)MY_CMD_RO_SEC_LENGTH)

#endif
