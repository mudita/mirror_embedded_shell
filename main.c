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

BaseType_t test_callback( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString ){
	strcpy(pcWriteBuffer,"testowy command dziala !");

	return pdFALSE;
}

shell_cmd_t test_cmd = {"test","testowy cmd",test_callback,1};

static FILE* input;
static FILE* output;

uint8_t write_std(const char* str, size_t len)
{
	(void)len;
	size_t cnt =0;
	fwrite(str,1,len,output);
	return 0;
}

uint8_t read_std(char* str)
{
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


	for(;;)
	{
		shell_RunPeriodic(&shell);
	}




	return 0;
}
