/*
 * fs_cmds.c
 *
 *  Created on: 27 Nov 2017
 *      Author: mati
 */


#include <stdio.h>
#include "../platform/platform.h"
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


static char path_buff[512] = {0};

static BaseType_t ls_callback(char *pcWriteBuffer, size_t xWriteBufferLen, argv arg, size_t argc  )
{
    DIR *dp;
    struct dirent *dirp;

    getcwd_fs(path_buff,sizeof(path_buff));

    if ((dp = opendir_fs(path_buff)) == NULL)
        return pdFALSE;

    while ((dirp = readdir_fs(dp)) != NULL){
    	pcWriteBuffer += sprintf(pcWriteBuffer,"%s\n",dirp->d_name);
    }
    closedir_fs(dp);
	return pdFALSE;
}

static BaseType_t cat_callback(char *pcWriteBuffer, size_t xWriteBufferLen, argv arg, size_t argc  )
{
	FILE* fd = NULL;

	fd = open_fs(arg[1],"r");

	if(fd != NULL){
		//read no more than xWriteBufferLen
		size_t len=read_fs(pcWriteBuffer,sizeof(char),xWriteBufferLen,fd);

		if(len == 0){
			//error
		}else {
		}
	}

	close_fs(fd);

	return pdFALSE;
}

static BaseType_t cd_callback(char *pcWriteBuffer, size_t xWriteBufferLen, argv arg, size_t argc  )
{

	if(arg[1][0] == '/'){
		strcpy(path_buff,arg[1]);
	}else{
		getcwd_fs(path_buff,sizeof(path_buff));

		sprintf(path_buff,"%s/%s",path_buff,arg[1]);
	}

	if(!chdir_fs(path_buff)){
		//success
	}else{
		//error
	}
	return pdFALSE;
}

static BaseType_t mkdir_callback(char *pcWriteBuffer, size_t xWriteBufferLen, argv arg, size_t argc  )
{

	if(!mkdir_fs(arg[1],0)){
		//success
	}else{
		//error
	}

	return pdFALSE;
}

static BaseType_t cwd_callback(char *pcWriteBuffer, size_t xWriteBufferLen, argv arg, size_t argc  )
{

	getcwd_fs(pcWriteBuffer,xWriteBufferLen);
	return pdFALSE;
}

