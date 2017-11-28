/*
 * platform_semihost.c
 *
 *  Created on: 24 Nov 2017
 *      Author: mati
 */

#include "platform_semihost.h"
#include "../../shell_platform_conf.h"
#include "../../shell.h"


#ifdef PLATFORM_SEMIHOST
#include <stdio.h>
#include <string.h>



char  platform_shell_BS = '\b';
char* platform_shell_NEWLINE = "\n";
char* platform_shell_ARROW_LEFT = "D";
char* platform_shell_ARROW_RIGHT = "C";
char* platform_shell_ARROW_UP = "A";
char* platform_shell_ARROW_DOWN = "B";
char* platform_shell_start_of_escape_seq = "\e";
char* platform_shell_CLEAR_LINE ="2K";


void platform_init()
{
	return;
}

uint8_t platform_write(const char* str, size_t len,void* param)
{
	fwrite(str,1,len,stdout);
	return 0;
}

uint8_t platform_read(char* str,uint32_t* len, void* param)
{
	if(fgets(str,SHELL_READ_BUFFER_LEN,stdin) == NULL){
		*len =0;
		return 0;
	}
	*len = strlen(str);
	return 0;
}


#endif // PLATFORM_LINUX
