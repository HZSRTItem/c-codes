/*------------------------------------------------------------------------------
 * File    : srtreocrd
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

#include "srtlist.h"
#include "srtstring.h"

typedef struct SRTRecord SRTRecord_t;
typedef struct SRTRecordList SRTRecordList_t;
typedef struct SRTRecordCollection SRTRecordCollection_t;

typedef struct SRTRecord
{
	size_t id;
	char* key;
	char* text;
	char* back;

} SRTRecord_t;

SRTRecord_t* SRTRecord_init(SRTRecord_t* self, size_t id);
SRTRecord_t* SRTRecord_init_v2(SRTRecord_t* self, size_t id, const char* key, const char* text, const char* back);
SRTRecord_t* SRTRecord_free(SRTRecord_t* self);

typedef struct SRTRecordList
{
    SRTList_t _list;
    size_t count;

    SRTRecordList_t* (*init)(SRTRecordList_t* self);
    SRTRecord_t* (*add)(SRTRecordList_t* self, const SRTRecord_t* emement);
    SRTRecord_t* (*set)(SRTRecordList_t* self, size_t idx, const SRTRecord_t* emement);
    SRTRecord_t* (*get)(SRTRecordList_t* self, size_t idx);
    void (*free)(SRTRecordList_t* self);

}SRTRecordList_t;

SRTRecordList_t* SRTRecordList_init(SRTRecordList_t* self);
SRTRecord_t* SRTRecordList_add(SRTRecordList_t* self, const SRTRecord_t* emement);
SRTRecord_t* SRTRecordList_set(SRTRecordList_t* self, size_t idx, const SRTRecord_t* emement);
SRTRecord_t* SRTRecordList_get(SRTRecordList_t* self, size_t idx);
void SRTRecordList_free(SRTRecordList_t* self);

typedef struct SRTRecordCollection
{
	SRTList_t _list;


} SRTRecordCollection_t;

