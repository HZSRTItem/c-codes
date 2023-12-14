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

SRTCharList_t* fmtN(SRTCharList_t* char_list, size_t width);
char* fmtOne(size_t width, size_t size_t, const char* end_str, char* dst_chars);
char* fmtInt(size_t width, char* dst_chars);
char* fmtDouble(size_t width, size_t size_t, char* dst_chars);
char* fmtString(size_t width, char* dst_chars);
char* fmtCopyString(char* dst_chars, SRTCharList_t* str_list);