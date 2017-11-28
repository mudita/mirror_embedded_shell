/*
 * platform_stm32f4.h
 *
 *  Created on: 24 Nov 2017
 *      Author: mati
 */

#ifndef PLATFORM_STM32F4_PLATFORM_STM32F4_H_
#define PLATFORM_STM32F4_PLATFORM_STM32F4_H_

#include <unistd.h>
#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>

/* Codes below are platform/device specific.*/
char  platform_shell_BS;
char* platform_shell_NEWLINE;
char* platform_shell_ARROW_LEFT;
char* platform_shell_ARROW_RIGHT;
char* platform_shell_ARROW_UP;
char* platform_shell_ARROW_DOWN;
char* platform_shell_start_of_escape_seq;
char* platform_shell_CLEAR_LINE;

struct dirent {
    ino_t          d_ino;      //  inode number
    off_t          d_off;       // offset to the next dirent
    unsigned short d_reclen;    // length of this record
    unsigned char  d_type;      // type of file; not supported
                                //   by all file system types
    char           d_name[256]; // filename
};

typedef uint32_t DIR;

inline unsigned char chdir_dummy(char* path){
	return 0;
}

inline unsigned char mkdir_dummy(char* path,uint32_t mode){
	return 0;
}

inline DIR *opendir_dummy(const char *name)
{
	return NULL;
}

inline struct dirent *readdir_dummy(DIR *dirp)
{
	return NULL;
}

inline int closedir_dummy(DIR *dirp)
{
	return 0;
}

/**
 * Warning, please avoid polluting standard namespace. This header is meant to use only in fs_portable layer.
 * If you want to use embedded FS lib, FatFS for example you have to create wrapper around fatfs api and use those functions in
 * macros below.
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


#endif /* PLATFORM_STM32F4_PLATFORM_STM32F4_H_ */
