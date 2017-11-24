/*
 * platform.h
 *
 *  Created on: 24 Nov 2017
 *      Author: mati
 */

#ifndef PLATFORM_PLATFORM_H_
#define PLATFORM_PLATFORM_H_

#include <stdint.h>
#include "../shell_platform_conf.h"

#ifdef PLATFORM_STM32F4_DISC
#include "stm32f4/platform_stm32f4.h"
#elif defined(PLATFORM_LINUX)
#include "linux/platform_linux.h"
#elif defined(PLATFORM_WINDOWS)
#include "linux/platform_win.h"
#elif defined(PLATFORM_EXT_IMPLEMENTATION)
#pragma message "Remember to invoke shell_RegisterIOFunctions() in order to register read/write functions"
#else
#warning "No platform specified. Create new one in /platform or use PLATFORM_EXT_IMPLEMENTATION and invoke shell_RegisterIOFunctions to register read/write functions."
#endif


extern void platform_init() __attribute__ ((weak));

extern uint8_t platform_write(const char* str, size_t len,void* param) __attribute__ ((weak));

extern uint8_t platform_read(char* str,uint32_t* len, void* param) __attribute__ ((weak));

#endif /* PLATFORM_PLATFORM_H_ */
