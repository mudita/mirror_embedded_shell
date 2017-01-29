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

#define SHELL_DEFAULT_CODE	0xff


typedef uint8_t (*cmd_t)(char **arg_tab, uint8_t arg_cnt);
typedef uint8_t (*shell_write_t)(const char* str, size_t len);
typedef uint8_t (*shell_read_t)(char* str);

typedef CLI_Command_Definition_t shell_cmd_t;

typedef struct _cmd_entry
{
	cmd_t cmd;
	char* help_str;
	char* desc;
	char* name;

}cmd_entry_t;

typedef struct _shell {

	void* hist_queue;

	char* line_prompt;
	char* line_buff;
	uint32_t line_buff_pos;
	size_t line_buff_size;

	cmd_entry_t *cmd_etab[SHELL_MAX_NR_REGISTERED_COMMANDS];

	shell_write_t write;
	shell_read_t read;

	const char *bs_code;
	const char *newline_code;
	const char *arrowl_code;
	const char *arrowr_code;
	const char *arrowu_code;
	const char *arrowd_code;

} shell_t;



typedef enum{
	SHELL_OK=0,
	SHELL_ERR_GEN=1,
	SHELL_ERR_TAB_FULL=2,
	SHELL_ERR_SPACE=3,
	SHELL_ERR_MEM=4,

}sherr_t;


sherr_t shell_Init(shell_t* shell, size_t linebuf_len);


uint8_t shell_RegisterCmd( const shell_cmd_t * const pxCommandToRegister );

void shell_RegisterIOFunctions(shell_t* shell,
		uint8_t (*shell_write)(const char* str, size_t len),
		uint8_t (*shell_read)(char* str_out));

void shell_RegisterCmdTab(shell_t* shell, cmd_entry_t* cmd_tab, size_t ele);

/* Max number of elements is 255(TODO: consider using bigger variable for it !) */
sherr_t shell_AddCmdTab(shell_t* shell, cmd_entry_t* cmd_tab, size_t ele);


void shell_RunPeriodic(shell_t* shell);





#endif /* MODULES_SHELL_SHELL_H_ */
