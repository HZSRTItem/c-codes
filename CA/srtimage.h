/*------------------------------------------------------------------------------
 * File    : srtimage.h
 * Time    : 2023-8-30 14:35:29
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
#include <io.h>
#include <direct.h>
#include <ctype.h>
#include <math.h>

#include "srtstring.h"
#include "srtcodes.h"

#define SRT_MAX_LEN_SHAPE 32

typedef struct SRTArrayInt
{
	size_t shape[SRT_MAX_LEN_SHAPE];
	size_t length_shape;
	int* data;

	int (*get1)(struct SRTArrayInt self, int loc1);
	int (*get2)(struct SRTArrayInt self, int loc1, int loc2);
	int (*get3)(struct SRTArrayInt self, int loc1, int loc2, int loc3);

	int (*set1)(struct SRTArrayInt self, int loc1);
	int (*set2)(struct SRTArrayInt self, int loc1, int loc2);
	int (*set3)(struct SRTArrayInt self, int loc1, int loc2, int loc3);
}SRTArrayInt_t;

typedef struct SRTArrayRead
{
	char** data;
	size_t n;
	size_t nrows;
	size_t ncolumns;
}SRTArrayRead_t;

SRTArrayRead_t* SRTArray_readText(SRTArrayRead_t* self, char filename[_MAX_PATH], char const* sep);
