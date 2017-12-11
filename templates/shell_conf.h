/*
 * shell_conf.h
 *
 *  Created on: 29 mar 2016
 *      Author: MateuszPiesta
 */

#ifndef MODULES_SHELL_SHELL_CONF_H_
#define MODULES_SHELL_SHELL_CONF_H_

#include <assert.h>

#define SHELL_MAX_NR_REGISTERED_COMMANDS	50
#define SHELL_CMD_HISTORY_DEPTH	5

#define SHELL_CMD_MAX_PARAM_NR	10
#define SHELL_CMD_MAX_PARAM_LEN	10

#define SHELL_MAX_PASSWORD_LEN	32

#define SHELL_ASSERT(X)	assert(X)

/* Only for standalone version of shell. Otherwise comment define below ! */
#define SHELL_NO_FREERTOS

/**
 * Buffer used for printing command responses etc
 */
#define SHELL_MAX_OUTPUT_BUFFER_SIZE	1024


/**
 * Buffer used for handling data received in packs. For example someone could paste command into terminal instead typing it.
 */
#define SHELL_READ_BUFFER_LEN	32

/**
 * Set to 1 if you want to use file system commands
 */
#define SHELL_USE_FS	1

#ifndef SHELL_NO_FREERTOS
#include "FreeRTOS.h"
#include "task.h"
#endif

#if (SHELL_MAX_PASSWORD_LEN > SHELL_READ_BUFFER_LEN)
#error "Shell password musn't be longer than SHELL_READ_BUFFER_LEN"
#endif
#endif /* MODULES_SHELL_SHELL_CONF_H_ */
