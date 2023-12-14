/*------------------------------------------------------------------------------
 * File    : srtlist
 * Time    : 2023-9-1 18:52:15
 * Author  : Zheng Han
 * Contact : hzsongrentou1580@gmail.com
 * License : (C)Copyright 2023, ZhengHan. All rights reserved.
 * Desc    :
------------------------------------------------------------------------------*/

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <direct.h> 

typedef struct SRTList SRTList_t;

typedef struct SRTList
{
	void* data;
	size_t count;
	size_t length;
	size_t type_size;

	SRTList_t* (*init)(SRTList_t* self, size_t _type_length);
	void* (*add)(SRTList_t* self, const void* element);
	void* (*get)(SRTList_t* self, size_t idx);
	void* (*set)(SRTList_t* self, size_t idx, const void* element);
	void (*free)(SRTList_t* self);

}SRTList_t;

SRTList_t* SRTList_init(SRTList_t* self, size_t _type_length);
void* SRTList_add(SRTList_t* self, const void* element);
void* SRTList_get(SRTList_t* self, size_t idx);
void* SRTList_set(SRTList_t* self, size_t idx, const void* element);
void SRTList_free(SRTList_t* self);


/* list_t iterator direction. */
typedef enum {
	LIST_HEAD
	, LIST_TAIL
} list_direction_t;

/* list_t node struct. */
typedef struct list_node {
	struct list_node* prev;
	struct list_node* next;
	void* val;
} list_node_t;

/* list_t struct. */
typedef struct {
	list_node_t* head;
	list_node_t* tail;
	unsigned int len;
	void (*free)(void* val);
	int (*match)(void* a, void* b);
} list_t;

/* list_t iterator struct. */
typedef struct {
	list_node_t* next;
	list_direction_t direction;
} list_iterator_t;

// Node prototypes.

list_node_t* list_node_new(void* val);

// list_t prototypes.

list_t* list_new(void);
list_node_t* list_rpush(list_t* self, list_node_t* node);
list_node_t* list_lpush(list_t* self, list_node_t* node);
list_node_t* list_find(list_t* self, void* val);
list_node_t* list_at(list_t* self, int index);
list_node_t* list_rpop(list_t* self);
list_node_t* list_lpop(list_t* self);
void list_remove(list_t* self, list_node_t* node);
void list_destroy(list_t* self);

// list_t iterator prototypes.

list_iterator_t* list_iterator_new(list_t* list, list_direction_t direction);
list_iterator_t* list_iterator_new_from_node(list_node_t* node, list_direction_t direction);
list_node_t* list_iterator_next(list_iterator_t* self);
void list_iterator_destroy(list_iterator_t* self);


