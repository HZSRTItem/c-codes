#include "srtprintf.h"

SRTCharList_t* fmtN(SRTCharList_t* str_list, size_t width)
{
	if (width < 0)
	{
		SRTCharList_addString(str_list, "-");
	}
	size_t width_tmp = width;
	size_t n_width = 1;
	while (1)
	{
		width = width / 10;
		if (width == 0)
		{
			break;
		}
		n_width *= 10;
	}
	width = width_tmp;
	while (1)
	{
		char n = (char)(width / n_width);
		SRTCharList_add(str_list, '0' + n);
		width %= n_width;
		n_width /= 10;
		if (width == 0)
		{
			break;
		}
	}
	return str_list;
}

char* fmtOne(size_t width, size_t n_end, const char* end_str, char* dst_chars)
{
	SRTCharList_t str_list;
	SRTCharList_init(&str_list, NULL);
	SRTCharList_addString(&str_list, "%");
	if (width)
	{
		fmtN(&str_list, width);
	}
	if (n_end)
	{
		SRTCharList_addString(&str_list, ".");
		fmtN(&str_list, n_end);
	}
	if (end_str)
	{
		SRTCharList_addString(&str_list, end_str);
	}
	dst_chars = fmtCopyString(dst_chars, &str_list);
	SRTCharList_free(&str_list);
	return dst_chars;
}

char* fmtInt(size_t width, char* dst_chars)
{
	return fmtOne(width, 0, "d", dst_chars);
}

char* fmtDouble(size_t width, size_t n_end, char* dst_chars)
{
	return fmtOne(width, n_end, "f", dst_chars);
}

char* fmtString(size_t width, char* dst_chars)
{
	return fmtOne(width, 0, "s", dst_chars);
}

char* fmtCopyString(char* dst_chars, SRTCharList_t* str_list)
{
	if (!dst_chars)
	{
		dst_chars = (char*)malloc(sizeof(char) * (str_list->count + 2));
	}

	if (dst_chars)
	{
		strcpy_s(dst_chars, str_list->count + 2, str_list->data);
	}

	return dst_chars;
}

