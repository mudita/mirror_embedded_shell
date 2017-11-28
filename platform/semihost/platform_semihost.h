/*
 * platform_semihost.h
 *
 *  Created on: 24 Nov 2017
 *      Author: mati
 */

#ifndef PLATFORM_SEMIHOST_PLATFORM_SEMIHOST_H_
#define PLATFORM_SEMIHOST_PLATFORM_SEMIHOST_H_

#include "../../shell_platform_conf.h"
#include <stddef.h>
#include "sys/stat.h"
#include <unistd.h>
#ifdef PLATFORM_SEMIHOST
#include "dirent.h"
#endif


/* Codes below are platform/device specific.*/
char  platform_shell_BS;
char* platform_shell_NEWLINE;
char* platform_shell_ARROW_LEFT;
char* platform_shell_ARROW_RIGHT;
char* platform_shell_ARROW_UP;
char* platform_shell_ARROW_DOWN;
char* platform_shell_start_of_escape_seq;
char* platform_shell_CLEAR_LINE;

/**
 * Warning, please avoid polluting standard namespace. This header is meant to use only in fs_portable layer.
 */

#define close_fs(__fd)                   		fclose(__fd)
#define fcntl_fs(__fd, __cmd, __arg)     		fcntl(__fd, __cmd, __arg)
#define fstat_fs(__fdes, __stat)         		fstat(__fdes, __stat)
#define link_fs(__oldpath, __newpath)    		link(__oldpath, __newpath)
#define lseek_fs(__fdes, __off, __w)     		lseek(__fdes, __off, __w)
#define mkdir_fs(__path, __m)		  			mkdir(__path, __m)
#define open_fs(__path,__m)     				fopen(__path,__m)
#define write_fs( __buff,__size, __cnt,__fd) 	fwrite( __buff,__size, __cnt,__fd)
#define read_fs( __buff,__size, __cnt,__fd)     fread( __buff,__size, __cnt,__fd)
#define rename_fs(__old, __new)	  				rename(__old, __new)
#define getcwd_fs(__buff,__size) 				getcwd(__buff,__size)
#define chdir_fs(__path)						chdir(__path)
#define opendir_fs(__path)						opendir(__path)
#define closedir_fs(__path)						closedir(__path)
#define readdir_fs(__dir)						readdir(__dir)

#endif /* PLATFORM_SEMIHOST_PLATFORM_SEMIHOST_H_ */
