/*
 * portable.h
 *
 *  Created on: Dec 11, 2017
 *      Author: mati
 */

#ifndef EMBEDDED_SHELL_PORTABLE_PORTABLE_H_
#define EMBEDDED_SHELL_PORTABLE_PORTABLE_H_

#include <stdint.h>
#include <stddef.h>
#include "shell_conf.h"


/* Codes below are platform/device specific.*/
char  portable_shell_BS;
char* portable_shell_NEWLINE;
char* portable_shell_ARROW_LEFT;
char* portable_shell_ARROW_RIGHT;
char* portable_shell_ARROW_UP;
char* portable_shell_ARROW_DOWN;
char* portable_shell_start_of_escape_seq;
char* portable_shell_CLEAR_LINE;


uint8_t portable_write(const char* str, size_t len,void* param);
uint8_t portable_read(char* str,uint32_t* len, void* param);
void portable_init();

#if (SHELL_USE_FS == 1)
/**
 * Please define
 */
#define close_fs(__fd)                   		fclose(__fd)
#define fcntl_fs(__fd, __cmd, __arg)     		fcntl(__fd, __cmd, __arg)
#define fstat_fs(__fdes, __stat)         		fstat(__fdes, __stat)
#define link_fs(__oldpath, __newpath)    		link(__oldpath, __newpath)
#define lseek_fs(__fdes, __off, __w)     		lseek(__fdes, __off, __w)
#define mkdir_fs(__path, __m)		  			mkdir_dummy(__path, __m)
#define open_fs(__path,__m)     				fopen(__path,__m)
#define write_fs( __buff,__size, __cnt,__fd) 	fwrite( __buff,__size, __cnt,__fd)
#define read_fs( __buff,__size, __cnt,__fd)     fread( __buff,__size, __cnt,__fd)
#define rename_fs(__old, __new)	  				rename(__old, __new)
#define getcwd_fs(__buff,__size) 				getcwd(__buff,__size)
#define chdir_fs(__path)						chdir_dummy(__path)
#define opendir_fs(__path)						opendir_dummy(__path)
#define closedir_fs(__path)						closedir_dummy(__path)
#define readdir_fs(__dir)						readdir_dummy(__dir)
#endif

#endif /* EMBEDDED_SHELL_PORTABLE_PORTABLE_H_ */
