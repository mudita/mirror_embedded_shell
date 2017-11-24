/*
 * shell.h
 *
 *  Created on: 29 mar 2016
 *      Author: MateuszPiesta
 */

#ifndef MODULES_SHELL_SHELL_H_
#define MODULES_SHELL_SHELL_H_

#include "shell_conf.h"
#include <stdint.h>
#include <stddef.h>
#include "FreeRTOS_CLI.h"

#define SHELL_CMD_VARIABLE_PARAM_NR	-1

/**
 *  Prototype for shell_write function.
 *  str - string to be written
 *  len - string length
 *  param - generic pointer to pass/ret user's data to/from function */
typedef uint8_t (*shell_write_t)(const char* str, size_t len, void* param);

/**
 * Prototype for shell_read function
 * str - string read
 * param - generic pointer to pass/ret user's data to/from function
 */
typedef uint8_t (*shell_read_t)(char* str,uint32_t* len, void* param);

typedef CLI_Command_Definition_t shell_cmd_t;

typedef enum {
	AUTH_IN_PROGRESS = 1,
	AUTH_PASSED = 2
}auth_action;

typedef struct _shell {

	void* hist_queue;

	char* line_prompt;
	char* line_buff;
	uint32_t line_buff_pos;
	//uint32_t line_buff_current_size;
	size_t line_buff_size;

	shell_write_t write;
	shell_read_t read;

	const char *bs_code;
	const char *newline_code;
	const char *arrowl_code;
	const char *arrowr_code;
	const char *arrowu_code;
	const char *arrowd_code;

	void* param;

} shell_t;



typedef enum{
	SHELL_OK=0,
	SHELL_ERR_GEN=1,
	SHELL_ERR_TAB_FULL=2,
	SHELL_ERR_SPACE=3,
	SHELL_ERR_MEM=4,

}sherr_t;


sherr_t shell_Init(shell_t* shell, size_t linebuf_len);

void shell_InitPlatform(shell_t* shell);


uint8_t shell_RegisterCmd( const shell_cmd_t * const pxCommandToRegister );

void shell_RegisterIOFunctions(shell_t* shell,
		shell_write_t write,
		shell_read_t read);

void shell_RunPeriodic(shell_t* shell);

void shell_PassParam(shell_t* shell,void* param, size_t param_len);





#endif /* MODULES_SHELL_SHELL_H_ */
