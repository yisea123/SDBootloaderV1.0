#ifndef __HEX2BIN_h
#define __HEX2BIN_h


#include "stm32flash.h"

typedef unsigned int	UINT;
typedef enum {FALSE = 0, TRUE = !FALSE} bool;


typedef union
{
char U8B[STM_SECTOR_SIZE];
u16 U16B[STM_SECTOR_SIZE/2];
} Buffer;

#define BOOTADD FLASH_APP_ADDR

#define false FALSE

#define BOOL bool

#define true TRUE


bool ReadLineInBuff(char *strLine, char* pBuff, UINT nSize, bool bInit);
BOOL CheckHexFile(char *source,  UINT MaxDataSize ,char *hexLineBuffer);
bool SD2ROM(char *source,  UINT MaxDataSize ,char *hexLineBuffer,char*stringBuff);

#endif

