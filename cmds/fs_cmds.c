/*
 * fs_cmds.c
 *
 *  Created on: 27 Nov 2017
 *      Author: mati
 */

#include <stdio.h>
#include <string.h>
#include "fs_cmds.h"

static BaseType_t cwd_callback(char *pcWriteBuffer, size_t xWriteBufferLen, argv arg, size_t argc  );
static BaseType_t ls_callback(char *pcWriteBuffer, size_t xWriteBufferLen, argv arg, size_t argc  );
static BaseType_t cat_callback(char *pcWriteBuffer, size_t xWriteBufferLen, argv arg, size_t argc  );
static BaseType_t cd_callback(char *pcWriteBuffer, size_t xWriteBufferLen, argv arg, size_t argc  );
static BaseType_t mkdir_callback(char *pcWriteBuffer, size_t xWriteBufferLen, argv arg, size_t argc  );

shell_cmd_t fs_cmds_tab[] ={
		 {"cwd","	cwd -> Print current working directory",cwd_callback,0},
		 {"ls","	ls -> List directory contents",ls_callback,0},
		 {"cat","	cat -> Print file content",cat_callback,1},
		 {"cd","	cd -> Change current directory",cd_callback,1},
		 {"mkdir","	mkdir -> Create new directory",mkdir_callback,1}
};

size_t fs_cmds_tab_size = sizeof(fs_cmds_tab)/sizeof(fs_cmds_tab[0]);

static BaseType_t ls_callback(char *pcWriteBuffer, size_t xWriteBufferLen, argv arg, size_t argc  )
{
	return pdFALSE;
}

static BaseType_t cat_callback(char *pcWriteBuffer, size_t xWriteBufferLen, argv arg, size_t argc  )
{
	FILE* fd = NULL;

	fd = fopen(arg[1],"r");

	if(fd != NULL){
		size_t len=fread(pcWriteBuffer,sizeof(char),SHELL_MAX_OUTPUT_BUFFER_SIZE,fd);

		if(len == 0){
			//error
		}else {
			xWriteBufferLen = len;
		}
	}

	return pdFALSE;
}

static BaseType_t cd_callback(char *pcWriteBuffer, size_t xWriteBufferLen, argv arg, size_t argc  )
{

	/*if(!chdir(arg[1])){
		//success
	}else{
		//error
	}*/
	return pdFALSE;
}

static BaseType_t mkdir_callback(char *pcWriteBuffer, size_t xWriteBufferLen, argv arg, size_t argc  )
{

	if(!mkdir(arg[1],0)){
		//success
	}else{
		//error
	}

	return pdFALSE;
}


static char *
getcwd (char *buf, size_t size){
	return NULL;
}

static BaseType_t cwd_callback(char *pcWriteBuffer, size_t xWriteBufferLen, argv arg, size_t argc  )
{

	getcwd(pcWriteBuffer,SHELL_MAX_OUTPUT_BUFFER_SIZE);
	return pdFALSE;
}
