#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <direct.h> 

#include "srtstring.h"

#define STR_EQUAL(a, b) (strcmp(a, b) == 0)
#define MAX_LINE_LEN 1024

typedef struct SRTTime
{
    int year;
    int mouth;
    int day;
    int hour;
    int minute;
    int second;
} SRTTime_t;

typedef struct SRTIntList
{
    int length;
    int count;
    int* data;

    struct SRTIntList* (*init)(struct SRTIntList* self);
    void (*free)(struct SRTIntList* self);
    int (*add)(struct SRTIntList* self, int _element);
} SRTIntList_t;

typedef struct SRTDoubleList
{
    int N;
    int n;
    double* d;

    struct SRTDoubleList* (*init)(struct SRTDoubleList* self);
    void (*free)(struct SRTDoubleList* self);
    double (*add)(struct SRTDoubleList* self, double _element);
} SRTDoubleList_t;

//typedef struct SRTCharList
//{
//    int N;
//    int n;
//    char* d;
//
//    struct SRTCharList* (*init)(struct SRTCharList* self);
//    void (*free)(struct SRTCharList* self);
//    char* (*add)(struct SRTCharList* self, char _element);
//    char* (*adds1)(struct SRTCharList* self, const char* _element);
//    char* (*adds2)(struct SRTCharList* self, char _element[]);
//    char* (*adds3)(struct SRTCharList* self, char* _element);
//} SRTCharList_t;

typedef struct SRTReadLine
{
    FILE* fr;
    char* line;
    int max_line_len;

    struct SRTReadLine* (*init)(struct SRTReadLine* self);
    struct SRTReadLine* (*open)(struct SRTReadLine* self, char _filename[_MAX_PATH]);
    char* (*next)(struct SRTReadLine* self);
    void  (*close)(struct SRTReadLine* self);
} SRTReadLine_t;

//typedef struct SRTStringList
//{
//    int N;
//    int n;
//    char** d;
//
//    struct SRTStringList* (*init)(struct SRTStringList* self);
//    void (*free)(struct SRTStringList* self);
//    char* (*add)(struct SRTStringList* self, char* _element);
//} SRTStringList_t;

void h_getexedir(char exe_dir[_MAX_PATH]);
void h_addpath(char h_dst[_MAX_PATH], char h_add[_MAX_PATH]);
void getexefilename(char _dst_filename[_MAX_PATH], char* _src_filename);
void getfullfilename(char _dst_filename[_MAX_PATH], char* _src_filename);
void printLine_(int n);
char* strtrim(char* _str_strim);
int isspaceString(char* _str);
int getFileSize(char _filename[_MAX_PATH]);
char* readTextAll(char _filename[_MAX_PATH]);
void h_getcurrenttime(struct tm* ct);
char* getchars_file(FILE* fr, int (*endread)(char* _str));
size_t string_replace(char* _str, char _src_ch, char _dst_ch);
int isspaceChar(char ch);
int copyFile(char _dst_filename[_MAX_PATH], char _src_filename[_MAX_PATH]);
void getfilename(char _dst_filename[_MAX_PATH], char _src_filename[_MAX_PATH]);
int h_getcwd(char dst[_MAX_PATH]); // get current path into dst


SRTReadLine_t* SRTReadLine_init(SRTReadLine_t* self);
SRTReadLine_t* SRTReadLine_open(SRTReadLine_t* self, char _filename[_MAX_PATH]);
char* SRTReadLine_next(SRTReadLine_t* self);
void SRTReadLine_close(SRTReadLine_t* self);

SRTIntList_t* SRTIntList_init(SRTIntList_t* self);
int SRTIntList_add(SRTIntList_t* self, int _element);
int* SRTIntList_copy(SRTIntList_t* self, int* _elements);
void SRTIntList_free(SRTIntList_t* self);

SRTDoubleList_t* SRTDoubleList_init(SRTDoubleList_t* self);
double SRTDoubleList_add(SRTDoubleList_t* self, double _element);
void SRTDoubleList_free(SRTDoubleList_t* self);

//SRTCharList_t* SRTCharList_init(SRTCharList_t* self);
//char* SRTCharList_add(SRTCharList_t* self, char _element);
//char* SRTCharList_adds1(SRTCharList_t* self, const char* _element);
//char* SRTCharList_adds2(SRTCharList_t* self, char _element[]);
//char* SRTCharList_adds3(SRTCharList_t* self, char* _element);
//void SRTCharList_free(SRTCharList_t* self);

int h_striscontain_start(char* find_str, char* src_str);
char* copyString(char* _str);


