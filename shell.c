/*
 * shell.c
 *
 *  Created on: 29 mar 2016
 *      Author: MateuszPiesta
 */

#include "shell.h"
#include "shell_conf.h"
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "history_list.h"
#include "FreeRTOS_CLI.h"

/* Codes below are platform/device specific.*/
const char  shell_BS = 0x7F;
const char* shell_NEWLINE = "\n";
const char* shell_ARROW_LEFT = "D";
const char* shell_ARROW_RIGHT = "C";
const char* shell_ARROW_UP = "A";
const char* shell_ARROW_DOWN = "B";
/* Prompt code */
const char* shell_prompt = ">";

typedef enum {
	LINE_BUFF_OK = 0,
	LINE_BUFF_FULL = 1,
	LINE_BUFF_EMPTY = 2,
	LINE_BUFF_REACH_MIN = 3,
	LINE_BUFF_REACH_MAX = 4,
	LINE_BUFF_UNSPECIFIED_CMD = 5
} lbuff_e;

typedef enum {
	LINE_BUFF_ADD_CHAR = 0,
	LINE_BUFF_BS = 1,
	LINE_BUFF_CLEAR_WHOLE = 2,
	LINE_BUFF_POS_LEFT = 3,
	LINE_BUFF_POS_RIGHT = 4
} lbuff_action;

/* Forward declarations */
static void shell_send_escape_sequence(shell_t* shell, const char* byte);
static const char* shell_ReturnLineBuff(shell_t* shell);

static hlist_t history = {0};
static char response_output_buff[SHELL_MAX_OUTPUT_BUFFER_SIZE] = {0};

sherr_t shell_Init(shell_t* shell, size_t linebuf_len) {

	SHELL_ASSERT(shell != NULL);

	memset(shell, 0, sizeof(*shell));

	if ((shell->line_buff = malloc(linebuf_len)) == NULL) {
		return SHELL_ERR_MEM;
	}
	shell->line_buff_size = linebuf_len;
	memset(shell->line_buff, 0, linebuf_len);

	history_list_Init(&history,SHELL_CMD_HISTORY_DEPTH);

	shell->line_prompt = (char*) shell_prompt;
	shell->bs_code = (char*) &shell_BS;
	shell->newline_code = (char*) shell_NEWLINE;
	shell->arrowd_code = (char*) shell_ARROW_DOWN;
	shell->arrowl_code = (char*) shell_ARROW_LEFT;
	shell->arrowr_code = (char*) shell_ARROW_RIGHT;
	shell->arrowu_code = (char*) shell_ARROW_DOWN;

	return SHELL_OK;

}

uint8_t shell_RegisterCmd( const shell_cmd_t * const pxCommandToRegister )
{
	return (uint8_t)FreeRTOS_CLIRegisterCommand(pxCommandToRegister);
}

void shell_RegisterIOFunctions(shell_t* shell,
		shell_write_t write,
		shell_read_t read) {

	SHELL_ASSERT(shell != NULL);
	SHELL_ASSERT(write != NULL);
	SHELL_ASSERT(read != NULL);

	shell->write = write;
	shell->read = read;

}


static const char* shell_ReturnLineBuff(shell_t* shell)
{
	return shell->line_buff;
}

static lbuff_e shell_MngtLineBuff(shell_t* shell, char* byte,
		lbuff_action action) {

	lbuff_e ret = LINE_BUFF_UNSPECIFIED_CMD;

	switch (action) {

	case LINE_BUFF_ADD_CHAR:
		if (shell->line_buff_pos > shell->line_buff_size) {
			shell->line_buff_pos = 0;
			memset(shell->line_buff, 0, shell->line_buff_size);	// clear character buffer
			shell->line_buff[0] = '\0';
			ret = LINE_BUFF_FULL;
		} else {
			shell->line_buff[shell->line_buff_pos] = *byte;
			shell->line_buff_pos++;
			if (shell->line_buff_pos == strlen(shell->line_buff)) {
				shell->line_buff[shell->line_buff_pos] = '\0';
			}
			ret = LINE_BUFF_OK;
		}

		break;

	case LINE_BUFF_BS:
		if (shell->line_buff_pos > 0) {

			shell->line_buff[shell->line_buff_pos - 1] = '\0';
			shell->line_buff_pos--;
			ret = LINE_BUFF_OK;
		} else {
			ret = LINE_BUFF_EMPTY;
		}
		break;

	case LINE_BUFF_CLEAR_WHOLE:

		memset(shell->line_buff, 0, shell->line_buff_size);	// clear character buffer
		shell->line_buff[0] = '\0';
		shell->line_buff_pos = 0;
		ret = LINE_BUFF_OK;

		break;

	case LINE_BUFF_POS_LEFT:

		if (shell->line_buff_pos == 0) {
			return LINE_BUFF_REACH_MIN;
		} else {
			shell->line_buff_pos--;
			shell_send_escape_sequence(shell, shell->arrowl_code);
			ret = LINE_BUFF_OK;
		}
		break;

	case LINE_BUFF_POS_RIGHT:

		if (shell->line_buff_pos == strlen(shell->line_buff)) {
			ret = LINE_BUFF_REACH_MAX;
		} else {
			shell->line_buff_pos++;
			shell_send_escape_sequence(shell, shell->arrowr_code);
			ret = LINE_BUFF_OK;
		}

		break;

	default:
		ret = LINE_BUFF_UNSPECIFIED_CMD;
		break;

	}

	return ret;

}

static void shell_write_newline(shell_t* shell) {
	shell->write(shell->newline_code, strlen(shell->newline_code));
	//shell->write(shell->line_prefix, strlen(shell->line_prefix));

}

static void shell_write_prompt(shell_t* shell) {
	shell->write(shell->line_prompt, strlen(shell->line_prompt));

}

static void shell_send_escape_sequence(shell_t* shell,const char* byte) {

	char buff[3] = { 0x1B, '[', 0 };

	buff[2] = *byte;
	shell->write(buff, sizeof(buff));
}

static void shell_NL_Action(shell_t* shell)
{
	shell_write_newline(shell);

	/* If line buffer is empty it means that user typed only enter without providing command */
	if(strcmp(shell_ReturnLineBuff(shell),"\0") != 0){
		/* Add typed cmd into history list only if it is new element
		 * (we don't want to have several the same commands stored in history list) */
		history_list_AddBeg(&history,shell_ReturnLineBuff(shell));

		BaseType_t ret;
		do
		{
			ret = FreeRTOS_CLIProcessCommand(shell_ReturnLineBuff(shell),response_output_buff,SHELL_MAX_OUTPUT_BUFFER_SIZE);

			/* Output cmd response if any */
			shell->write(response_output_buff, strlen(response_output_buff));

			shell_write_newline(shell);

		}while(ret != pdFALSE );

	}

	shell_write_prompt(shell);
	shell_MngtLineBuff(shell, NULL, LINE_BUFF_CLEAR_WHOLE);
}


void shell_RunPeriodic(shell_t* shell) {

	SHELL_ASSERT(shell != NULL);

	char byte;
	static char escape_sequence_start = 0;

	shell->read(&byte);

	if (byte != 0) {

		/*
		 * Start of escape sequence
		 */
		if (byte == 0x1B){
			escape_sequence_start = 1;
		}
		else if ((escape_sequence_start == 1) && (byte == '[')) {
			// omit this byte
		}
		/*
		 * New Line
		 */
		else if (*shell->newline_code == byte) {

			shell_NL_Action(shell);
		}
		/*
		 * Backspace
		 */
		else if (*shell->bs_code == byte) {

			if (shell_MngtLineBuff(shell, NULL, LINE_BUFF_BS) == LINE_BUFF_OK) {
				shell->write(shell->bs_code, 1);
			} else {
				// do nothing, there is nothing to clear inside line buff
			}
		}
		/*
		 * Arrow UP
		 */
		else if ((*shell->arrowu_code == byte) && (escape_sequence_start == 1)) {
			escape_sequence_start = 0;

			history_list_TraverseUp(&history);

		}
		/*
		 * Arrow DOWN
		 */
		else if ((*shell->arrowd_code == byte) && (escape_sequence_start == 1)) {
			escape_sequence_start = 0;

			history_list_TraverseDown(&history);

		}
		/*
		 * Arrow LEFT
		 */
		else if ((*shell->arrowl_code == byte) && (escape_sequence_start == 1)) {
			escape_sequence_start = 0;

			shell_MngtLineBuff(shell, NULL, LINE_BUFF_POS_LEFT);

		}
		/*
		 * Arrow RIGHT
		 */
		else if ((*shell->arrowr_code == byte) && (escape_sequence_start == 1)) {
			escape_sequence_start = 0;

			shell_MngtLineBuff(shell, NULL, LINE_BUFF_POS_RIGHT);

		}
		/*
		 * All ascii characters available from standard keyboard
		 */
		else if ((byte >= 0x20) && (byte <= 0x7E))
		{
			if (shell_MngtLineBuff(shell, &byte, LINE_BUFF_ADD_CHAR) == LINE_BUFF_OK) {

				/* Authorization procedure */


				shell->write(&byte, sizeof(byte));

			} else {
				// line buffer full, clear it and then proceed to next line
				shell_MngtLineBuff(shell, NULL, LINE_BUFF_CLEAR_WHOLE); // clears line buff
				shell_write_newline(shell);
				shell_write_prompt(shell);
			}

		}

	}

}
