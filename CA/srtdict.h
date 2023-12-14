/*------------------------------------------------------------------------------
 * File    : recorddirectory
 * Time    : 2023-9-1 19:44:1
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
#include "srtcodes.h"

typedef struct SRTKeyDataString SRTKeyDataString_t;
typedef struct SRTDictString SRTDictString_t;

typedef struct SRTKeyDataString
{
	char* key;
	char* data;
} SRTKeyDataString_t;

SRTKeyDataString_t* SRTKeyDataString_init(SRTKeyDataString_t* self, const char* key, const char* data);
void SRTKeyDataString_free(SRTKeyDataString_t* self);
SRTKeyDataString_t* mkKDStr(const char* key, const char* data);

typedef struct SRTDictString
{
	SRTList_t _list;
	int count;

	SRTDictString_t* (*init)(SRTDictString_t* self);
	SRTKeyDataString_t* (*set)(SRTDictString_t* self, const char* key, const char* data);
	char* (*get)(SRTDictString_t* self, const char* key);
	void (*free)(SRTDictString_t* self);

}SRTDictString_t;

SRTDictString_t* SRTDictString_init(SRTDictString_t* self);
SRTKeyDataString_t* SRTDictString_set(SRTDictString_t* self, const char* key, const char* data);
char* SRTDictString_get(SRTDictString_t* self, const char* key);
SRTKeyDataString_t* SRTDictString_getKD(SRTDictString_t* self, const char* key);
void SRTDictString_free(SRTDictString_t* self);

