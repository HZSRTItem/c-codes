/*------------------------------------------------------------------------------
 * File    : srttable.c
 * Time    : 2023-8-21 11:0:34
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
#include "srtprintf.h"

#define STR_EQUAL(a, b) (strcmp(a, b) == 0)
#define SRTTABLE_MAX_COLN_LEN 36

enum SRTTableDataType
{
    INT_T,    // int
    DOUBLE_T, // double
    STRING_T, // string
};

typedef union SRTTableCellData
{
    int dint;
    double ddouble;
    char* dstring;
} SRTTableCellData_t;

typedef struct SRTTableCell
{
    SRTTableCellData_t data;
    enum SRTTableDataType celltype;

} SRTTableCell_t;

typedef struct SRTTableCellCollection
{
    size_t count;
    size_t length;
    SRTTableCell_t** data;

} SRTTableCellCollection_t;

typedef struct SRTTable
{
    size_t n_rows;    // number of rows
    size_t n_columns; // number of rows

    size_t _length_rows;             // number length of rows
    SRTTableCellCollection_t** rows; // rows

    size_t _length_columns;              // number length of rows
    char** column_names;                 // column names of this
    enum SRTTableDataType* column_types; // column names of this
    SRTTableCellCollection_t** columns;  // columns

    struct SRTTable* (*init)(struct SRTTable* self);
    SRTTableCellCollection_t* (*addRow)(struct SRTTable* self);
    SRTTableCellCollection_t* (*addColumn)(struct SRTTable* self, const char* column_name, enum SRTTableDataType data_type);
    SRTTableCell_t* (*get)(struct SRTTable* self,  size_t row, size_t column);
    int (*getInt)(struct SRTTable* self,  size_t row, size_t column);
    double (*getDouble)(struct SRTTable* self,  size_t row, size_t column);
    char* (*getString)(struct SRTTable* self,  size_t row, size_t column);
    void (*setInt)(struct SRTTable* self,  size_t row, size_t column, int d);
    void (*setDouble)(struct SRTTable* self,  size_t row, size_t column, double d);
    void (*setString)(struct SRTTable* self,  size_t row, size_t column, const char* d);
    void (*free)(struct SRTTable* self);
} SRTTable_t;

SRTTableCell_t* SRTTableCell_init(SRTTableCell_t* self);
void SRTTableCell_free(SRTTableCell_t* self);

SRTTableCellCollection_t* SRTTableCellCollection_init(SRTTableCellCollection_t* self);
SRTTableCellCollection_t* SRTTableCellCollection_add(SRTTableCellCollection_t* self, SRTTableCell_t* element);
SRTTableCell_t* SRTTableCellCollection_get(SRTTableCellCollection_t* self, size_t index);
SRTTableCell_t* SRTTableCellCollection_set(SRTTableCellCollection_t* self, size_t index, SRTTableCell_t* element);
void SRTTableCellCollection_free(SRTTableCellCollection_t* self);

SRTTable_t* SRTTable_init(SRTTable_t* self);
SRTTableCellCollection_t* SRTTable_addRow(SRTTable_t* self);
SRTTableCellCollection_t* SRTTable_addColumn(SRTTable_t* self, const char* column_name, enum SRTTableDataType data_type);
SRTTableCell_t* SRTTable_get(SRTTable_t* self,  size_t row, size_t column);
int SRTTable_getInt(SRTTable_t* self,  size_t row, size_t column);
double SRTTable_getDouble(SRTTable_t* self,  size_t row, size_t column);
char* SRTTable_getString(SRTTable_t* self,  size_t row, size_t column);
void SRTTable_setInt(struct SRTTable* self,  size_t row, size_t column, int d);
void SRTTable_setDouble(struct SRTTable* self,  size_t row, size_t column, double d);
void SRTTable_setString(struct SRTTable* self,  size_t row, size_t column, const char* d);
void SRTTable_free(SRTTable_t* self);
void SRTTable_print(SRTTable_t* self);