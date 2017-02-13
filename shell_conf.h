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
#define SHELL_CMD_HISTORY_DEPTH	10

#define SHELL_CMD_MAX_PARAM_NR	10
#define SHELL_CMD_MAX_PARAM_LEN	10

#define SHELL_MAX_PASSWORD_LEN	128

#define SHELL_ASSERT(X)	assert(X)

/* Only for standalone version of shell. Otherwise comment define below ! */
#define SHELL_NO_FREERTOS
#define SHELL_MAX_OUTPUT_BUFFER_SIZE	128


#if (SHELL_MAX_PASSWORD_LEN > SHELL_MAX_OUTPUT_BUFFER_SIZE)
#error "Shell password musn't be longer than SHELL_MAX_OUTPUT_BUFFER_SIZE"
#endif
#endif /* MODULES_SHELL_SHELL_CONF_H_ */
