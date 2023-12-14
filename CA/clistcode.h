#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <direct.h> 
#include "srtstring.h"
#include "srtlist.h"

typedef struct Test Test_t;
//typedef struct TestList TestList_t;
//
//typedef struct TestList
//{
//    SRTList_t _list;
//    int count;
//
//    TestList_t* (*init)(TestList_t* self);
//    Test_t* (*add)(TestList_t* self, Test_t* emement);
//    Test_t* (*set)(TestList_t* self, size_t idx, Test_t* emement);
//    Test_t* (*get)(TestList_t* self, size_t idx);
//    void (*free)(TestList_t* self);
//}TestList_t;
//
//TestList_t* TestList_add(TestList_t* self, Test_t* emement);
//TestList_t* TestList_set(TestList_t* self, size_t idx, Test_t* emement);
//TestList_t* TestList_get(TestList_t* self, size_t idx);
//void TestList_free(TestList_t* self);
//

typedef struct TestList TestList_t;

typedef struct TestList
{
    SRTList_t _list;
    int count;

    TestList_t* (*init)(TestList_t* self);
    Test_t* (*add)(TestList_t* self, Test_t* emement);
    Test_t* (*set)(TestList_t* self, size_t idx, Test_t* emement);
    Test_t* (*get)(TestList_t* self, size_t idx);
    void (*free)(TestList_t* self);
}TestList_t;

TestList_t* TestList_add(TestList_t* self, Test_t* emement);
TestList_t* TestList_set(TestList_t* self, size_t idx, Test_t* emement);
TestList_t* TestList_get(TestList_t* self, size_t idx);
void TestList_free(TestList_t* self);

int clistcode_main(int argc, char* argv[]);