/*
 * main.c
 *
 *  Created on: 21 lip 2016
 *      Author: Mateusz
 */


#include "shell.h"
#include "history_list.h"
#include <stdio.h>
#include <string.h>

BaseType_t test_callback(char *pcWriteBuffer, size_t xWriteBufferLen, argv arg, size_t argc){

	uint8_t i =0;

	for(i=0;i<argc;i++){
		printf(&arg[i][0]);
	}
	fflush(stdout);

	strcpy(pcWriteBuffer,"testowy command dziala !");

	return pdFALSE;
}

BaseType_t test1_callback( char *pcWriteBuffer, size_t xWriteBufferLen, argv arg, size_t argc){
	strcpy(pcWriteBuffer,"testowy1 command dziala !");

	return pdFALSE;
}

shell_cmd_t test_cmd = {"test","	test -> testowy cmd",test_callback,SHELL_CMD_VARIABLE_PARAM_NR};
shell_cmd_t test1_cmd = {"test1","	test1 -> testowy cmd1",test1_callback,4};

static FILE* input;
static FILE* output;

uint8_t write_std(const char* str, size_t len,void* param)
{
	(void)len;
	(void)param;
	size_t cnt =0;
	fwrite(str,1,len,output);
	return 0;
}

uint8_t read_std(char* str,uint32_t* len, void* param)
{
	(void) param;
	char byte  = 0;

	byte = fgetc(input);

	if(byte == EOF)// end of file
	{
		fflush(output);
		fclose(input);
		fclose(output);
		exit(1);
	}else{
		*str =byte;
		*len = 1;
	}

	return 0;
}



int main(void)
{

	input = fopen("input.txt","r");

	if(input == NULL){
		return -1;
	}

	output = fopen("output.txt","w");

	if(output == NULL){
		return -1;
	}

	fflush(stdout);

	shell_t shell;
	shell_Init(&shell,128);

	shell_RegisterIOFunctions(&shell,write_std,read_std);

	shell_RegisterCmd(&test_cmd);
	shell_RegisterCmd(&test1_cmd);


	for(;;)
	{
		shell_RunPeriodic(&shell);
	}




	return 0;
}
