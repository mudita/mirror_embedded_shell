/*
 * history_list.c
 *
 *  Created on: 21 lip 2016
 *      Author: Mateusz
 */

#include "history_list.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "shell_conf.h"

/* This flag is used for announcing to traverse functions that new entry has been added. */
static bool new_entryflag = false;
static bool doubled_entryflag = false;

void history_list_Init(hlist_t *const inst, uint32_t max_items_nr)
{
	inst->items_nr = 0;
	inst->max_items_nr = max_items_nr;

	inst->llist_current = inst->llist_end = inst->llist_beg = NULL;
}

void history_list_AddBeg(hlist_t *const inst,const char* dptr)
{
	/* If new string is the same as the current position of history list omit it. */
	if(inst->llist_current != NULL && strcmp(dptr,inst->llist_beg->dptr) == 0){
		inst->llist_current = inst->llist_beg;
		//doubled_entryflag = true;
		return;
	}

	if(inst->items_nr == inst->max_items_nr){// we've reached maximum capacity of history list

		//remove last position from list
		struct llist_t* temp_prev = inst->llist_end->prev;

		free(inst->llist_end->dptr);
		free(inst->llist_end);

		temp_prev->next = NULL;
		inst->llist_end = temp_prev;

	}
	else{
		inst->items_nr++;
	}

	struct llist_t* new_beg = NULL;

	new_beg = malloc(sizeof (struct llist_t));

	new_beg->prev = NULL;
	new_beg->next = inst->llist_beg;
	new_beg->dptr = malloc(strlen(dptr)+1);
	strcpy(new_beg->dptr,dptr);

	if(inst->llist_beg != NULL){ // check if its first element in list
		inst->llist_beg->prev = new_beg;
	}
	else{//first element simultaneously is last one
		inst->llist_end = new_beg;
	}
	inst->llist_beg = new_beg;
	inst->llist_current = inst->llist_beg;

	new_entryflag = true;
}

const char* history_list_TraverseUp(hlist_t *const inst)
{
	if(inst->llist_current == NULL)
		return NULL;

	/* Is this the oldest element from the list ? */
	if(inst->llist_current->next != NULL){

		/* Is this beginning of the list ? */
		if( new_entryflag == true && inst->llist_current->prev == NULL ){
			char* temp = inst->llist_current->dptr;
			inst->llist_current = inst->llist_current->next;
			return temp;
		}
		else if(doubled_entryflag == true){
			doubled_entryflag = false;
		}
		else{
			/* We are in the middle of the list so traverse one element up(older) then print it.
			 * In case of reaching the oldest element(end of the list) just print it without moving node pointer.*/
			 if(new_entryflag == false) inst->llist_current = inst->llist_current->next;
			 else new_entryflag = false;
		}

	}
	return inst->llist_current->dptr;

}

const char* history_list_TraverseDown(hlist_t *const inst)
{
	if(inst->llist_current == NULL){
		return NULL;
	}

	/* We are not at the beginning of history list.
	 * First traverse one element down(newer) then print it */
	if(inst->llist_current->prev != NULL)
	{
		inst->llist_current = inst->llist_current->prev;

		return inst->llist_current->dptr;
	}
	/* We are at the beginning of the history list.
	 * The only we can(and have to !) do is print this entry onto console */
	else
	{
		new_entryflag = false;
		return inst->llist_current->dptr;
	}
}
