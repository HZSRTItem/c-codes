/*------------------------------------------------------------------------------
 * File    : srtstring.c
 * Time    : 2023-8-22 16:38:50
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

typedef struct SRTCharList
{
    size_t count;
    size_t length;
    char* data;

    struct SRTCharList* (*add)(struct SRTCharList* self, const char ch);
    struct SRTCharList* (*addString)(struct SRTCharList* self, const char* string);
} SRTCharList_t;

typedef struct SRTStringList
{
    size_t count;
    size_t length;
    char** data;

    struct SRTStringList* (*add)(struct SRTStringList* self, char* element);
} SRTStringList_t;

SRTCharList_t* SRTCharList_init(SRTCharList_t* self, const char* string);
SRTCharList_t* SRTCharList_add(SRTCharList_t* self, const char ch);
SRTCharList_t* SRTCharList_addString(SRTCharList_t* self, const char* string);
char* SRTCharList_copy(SRTCharList_t* self, char* dst_chars);
void SRTCharList_free(SRTCharList_t* self);

SRTStringList_t* SRTStringList_init(SRTStringList_t* self);
SRTStringList_t* SRTStringList_add(SRTStringList_t* self, const char* element);
char** SRTStringList_copy(SRTStringList_t* self, char** strings);
void SRTStringList_free(SRTStringList_t* self);

char* copyChars(const char* chars);