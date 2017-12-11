/*
 * portable_stm32f4_hal.c
 *
 *  Created on: 24 Nov 2017
 *      Author: mati
 */


#include "portable.h"

#include "shell.h"

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_uart.h"


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



static UART_HandleTypeDef uart_handle;


char  portable_shell_BS = '\b';
char* portable_shell_NEWLINE = "\r\n";
char* portable_shell_ARROW_LEFT = "D";
char* portable_shell_ARROW_RIGHT = "C";
char* portable_shell_ARROW_UP = "A";
char* portable_shell_ARROW_DOWN = "B";
char* portable_shell_start_of_escape_seq = "\e";
char* portable_shell_CLEAR_LINE ="2K";


static void portable_uart_init(uint32_t baudrate);



void portable_init()
{
	portable_uart_init(230400);
}

static void portable_uart_init(uint32_t baudrate)
{

	 RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

	 RCC->APB2ENR |=RCC_APB2ENR_USART6EN;

	 GPIO_InitTypeDef Rx_pin,TX_pin;

	 Rx_pin.Pin = GPIO_PIN_7;
	 Rx_pin.Mode = GPIO_MODE_AF_OD;
	 Rx_pin.Pull = GPIO_NOPULL;
	 Rx_pin.Alternate = GPIO_AF8_USART6;
	 Rx_pin.Speed = GPIO_SPEED_FREQ_MEDIUM;

	 TX_pin.Pin = GPIO_PIN_6;
	 TX_pin.Pull = GPIO_NOPULL;
	 TX_pin.Mode = GPIO_MODE_AF_PP;
	 TX_pin.Speed = GPIO_SPEED_FREQ_MEDIUM;
	 TX_pin.Alternate = GPIO_AF8_USART6;

	 HAL_GPIO_Init(GPIOC,&Rx_pin);
	 HAL_GPIO_Init(GPIOC,&TX_pin);


	 uart_handle.Instance = USART6;
	 uart_handle.Init.BaudRate = baudrate;
	 uart_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	 uart_handle.Init.Mode = UART_MODE_TX_RX;
	 uart_handle.Init.OverSampling = UART_OVERSAMPLING_16;
	 uart_handle.Init.Parity = UART_PARITY_NONE;
	 uart_handle.Init.StopBits = UART_STOPBITS_1;
	 uart_handle.Init.WordLength = UART_WORDLENGTH_8B;


	 NVIC_SetPriority(USART6_IRQn,10);
	 NVIC_EnableIRQ(USART6_IRQn);

	 HAL_UART_Init(&uart_handle);


}

uint8_t portable_write(const char* str, size_t len,void* param)
{
	HAL_UART_Transmit(&uart_handle,str,len,1024);
}

uint8_t portable_read(char* str,uint32_t* len, void* param)
{
	*len = 1;
	HAL_UART_Receive(&uart_handle,str,*len,0xffffffff);
}

