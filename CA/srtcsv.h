/*------------------------------------------------------------------------------
 * File    : srtcodes.h
 * Time    : 2023-8-25 16:38:8
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

#include "srttable.h"
#include "srtcodes.h"
#include "srtprintf.h"

typedef struct SRTCSV
{
	size_t n_rows;
	int* n_columns;
	char*** data;

	struct SRTCSV* (*read)(struct SRTCSV* self, char _filename[_MAX_PATH], const char sep);
}SRTCSV_t;

SRTCSV_t* SRTCSV_read(SRTCSV_t* self, char _filename[_MAX_PATH], const char sep);
SRTTable_t* SRTCSVReadToTable(char _filename[_MAX_PATH], char sep, SRTTable_t* table);
void SRTCSV_print(SRTCSV_t* csv);
void SRTCSV_free(SRTCSV_t* csv);

