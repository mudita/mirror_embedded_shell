/*
 * history_list.h
 *
 *  Created on: 21 lip 2016
 *      Author: Mateusz
 */

#ifndef HISTORY_LIST_H_
#define HISTORY_LIST_H_

#include "stdint.h"

struct llist_t
{
	struct llist_t* prev;
	struct llist_t* next;
	char* dptr;
};


typedef struct
{
	struct llist_t* llist_beg;
	struct llist_t* llist_end;
	struct llist_t* llist_current;

	uint32_t items_nr;
	uint32_t max_items_nr;

}hlist_t;

void history_list_Init(hlist_t *const inst, uint32_t max_items_nr);
void history_list_AddBeg(hlist_t *const inst,const char* dptr);
const char* history_list_TraverseUp(hlist_t *const inst);
const char* history_list_TraverseDown(hlist_t *const inst);
void history_list_SetBeg(hlist_t *const inst);



#endif /* HISTORY_LIST_H_ */
