/*
 * common_cmds.c
 *
 *  Created on: 24 Nov 2017
 *      Author: mati
 */

#include "common_cmds.h"
#include <stdio.h>
#include <string.h>
#include "shell.h"
#include "common.h"


/* Password is shared between shell instances for example:
 * If you created one instance of shell for local interface(RS/UART) and one for TELNET
 * the password will be the same for both instances. */
char shell_password[SHELL_MAX_PASSWORD_LEN];

auth_action auth_state;


static const char* shell_logout_succes = "Logout success";


static BaseType_t password_callback(char *pcWriteBuffer, size_t xWriteBufferLen, argv arg, size_t argc  );

/* Cmd to logout from console*/
static BaseType_t logout_callback(char *pcWriteBuffer, size_t xWriteBufferLen, argv arg, size_t argc  );

/**
 Basic common commands
 */

shell_cmd_t common_cmds_tab[] = {
		{"passwd","	passwd -> Changes password",password_callback,1},
		{"logout","	logout -> Logout from console",logout_callback,0}
};

size_t common_cmds_tabsize = sizeof(common_cmds_tab)/sizeof(common_cmds_tab[0]);

/* Cmd to set new password */
static BaseType_t password_callback(char *pcWriteBuffer, size_t xWriteBufferLen, argv arg, size_t argc  ){

	(void) xWriteBufferLen;
	(void) argc;
	uint16_t len = strlen(&arg[1][0]);

	if((len <= SHELL_MAX_PASSWORD_LEN) && (len > 3)){
		encryptDecrypt(&arg[1][0],shell_password);
	}else{
		sprintf(pcWriteBuffer,"Password cannot be longer than %ud and shorter than 3!",SHELL_MAX_PASSWORD_LEN);
	}
	return pdFALSE;
}

/* Cmd to logout from console*/
static BaseType_t logout_callback(char *pcWriteBuffer, size_t xWriteBufferLen, argv arg, size_t argc  ){

	(void) xWriteBufferLen;
	(void) argc;
	(void) arg;
	auth_state = AUTH_IN_PROGRESS;
	strcpy(pcWriteBuffer,shell_logout_succes);

	return pdFALSE;
}
