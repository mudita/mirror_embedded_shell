/*
 * platform_linux.c
 *
 *  Created on: 24 Nov 2017
 *      Author: mati
 */


#include "platform_linux.h"
#include "../../shell_platform_conf.h"
#include "../../shell.h"


#ifdef PLATFORM_LINUX

void platform_init()
{

}

uint8_t platform_write(const char* str, size_t len,void* param)
{

}

uint8_t platform_read(char* str,uint32_t* len, void* param)
{

}


#endif // PLATFORM_LINUX
