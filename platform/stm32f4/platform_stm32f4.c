/*
 * platform_stm32f4.c
 *
 *  Created on: 24 Nov 2017
 *      Author: mati
 */


#include "platform_stm32f4.h"
#include "../../shell_platform_conf.h"
#include "../../shell.h"


#ifdef PLATFORM_STM32F4_DISC
/*#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_uart.h"






static UART_HandleTypeDef uart_handle;*/


char  platform_shell_BS = '\b';
char* platform_shell_NEWLINE = "\n";
char* platform_shell_ARROW_LEFT = "D";
char* platform_shell_ARROW_RIGHT = "C";
char* platform_shell_ARROW_UP = "A";
char* platform_shell_ARROW_DOWN = "B";
char* platform_shell_start_of_escape_seq = "\e";
char* platform_shell_CLEAR_LINE ="2K";


static void platform_uart_init(uint32_t baudrate);



void platform_init()
{
	platform_uart_init(230400);
}

static void platform_uart_init(uint32_t baudrate)
{

/*	 RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

	 RCC->APB2ENR |=RCC_APB2ENR_USART6EN;

	 GPIO_InitTypeDef Rx_pin,TX_pin;

	 Rx_pin.Pin = GPIO_PIN_7;
	 Rx_pin.Mode = GPIO_MODE_AF_OD;
	 Rx_pin.Pull = GPIO_NOPULL;
	 Rx_pin.Alternate = GPIO_AF8_USART6;

	 TX_pin.Pin = GPIO_PIN_6;
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

	 HAL_UART_Init(&uart_handle);*/


}

uint8_t platform_write(const char* str, size_t len,void* param)
{
	//HAL_UART_Transmit(&uart_handle,str,len,1024);
}

uint8_t platform_read(char* str,uint32_t* len, void* param)
{
	*len = 1;
	//HAL_UART_Receive(&uart_handle,str,*len,0xffffffff);
}

#endif
