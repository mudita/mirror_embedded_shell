/*
 * common_cmds.h
 *
 *  Created on: 24 Nov 2017
 *      Author: mati
 */

#ifndef COMMON_CMDS_H_
#define COMMON_CMDS_H_

#include "shell.h"

BaseType_t logout_callback(char *pcWriteBuffer, size_t xWriteBufferLen, argv arg, size_t argc  );
BaseType_t password_callback(char *pcWriteBuffer, size_t xWriteBufferLen, argv arg, size_t argc  );


shell_cmd_t password_cmd;
shell_cmd_t logout_cmd;

#endif /* COMMON_CMDS_H_ */
