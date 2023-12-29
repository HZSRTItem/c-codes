#include "srtstring.h"

SRTCharList_t* SRTCharList_init(SRTCharList_t* self, const char* string)
{
	if (!self)
	{
		self = (SRTCharList_t*)malloc(sizeof(SRTCharList_t));
		if (!self)
		{
			return self;
		}
	}

	self->add = SRTCharList_add;
	self->addString = SRTCharList_addString;

	self->count = 0;
	self->length = 6;
	self->data = (char*)malloc(sizeof(char) * self->length);
	if (self->data)
	{
		self->data[0] = '\0';
	}

	if (string)
	{
		SRTCharList_addString(self, string);
	}

	return self;
}

SRTCharList_t* SRTCharList_add(SRTCharList_t* self, const char ch)
{
	if (self->count >= self->length - 2)
	{
		self->length *= 2;
		char* tmp = (char*)realloc(self->data, sizeof(char) * self->length);
		if (tmp)
		{
			self->data = tmp;
		}
		else
		{
			return NULL;
		}
	}

	self->data[self->count] = ch;
	self->data[self->count + 1] = '\0';
	self->count++;
	return self;
}

SRTCharList_t* SRTCharList_addString(SRTCharList_t* self, const char* string)
{
	size_t n = strlen(string);
	for (size_t i = 0; i < n; i++)
	{
		SRTCharList_add(self, string[i]);
	}
	return self;
}

char* SRTCharList_copy(SRTCharList_t* self, char* dst_chars)
{
	if (!dst_chars)
	{
		dst_chars = (char*)malloc(sizeof(char) * (self->count + 2));
	}

	if (dst_chars)
	{
		strcpy_s(dst_chars, self->count + 2, self->data);
	}

	return dst_chars;
}

void SRTCharList_free(SRTCharList_t* self)
{
	if (self->data)
	{
		free(self->data);
	}

	self->data = NULL;
}

SRTStringList_t* SRTStringList_init(SRTStringList_t* self)
{
	if (!self)
	{
		self = (SRTStringList_t*)malloc(sizeof(SRTStringList_t));
		if (!self)
		{
			return self;
		}
	}

	self->add = SRTStringList_add;
	self->count = 0;
	self->length = 6;
	self->data = (char**)malloc(sizeof(char*) * self->length);
	return self;
}

SRTStringList_t* SRTStringList_add(SRTStringList_t* self, const char* element)
{
	if (self->count == self->length)
	{
		self->length *= 2;
		char** tmp = (char**)realloc(self->data, sizeof(char*) * self->length);
		if (tmp)
		{
			self->data = tmp;
		}
		else
		{
			return NULL;
		}
	}

	size_t n = strlen(element);
	self->data[self->count] = (char*)malloc(sizeof(char) * (n + 2));
	if (self->data[self->count])
	{
		strcpy_s(self->data[self->count], n + 2, element);
	}
	else
	{
		self->data[self->count] = NULL;
	}
	self->count++;

	return self;
}

char** SRTStringList_copy(SRTStringList_t* self, char** strings)
{
	if (!strings)
	{
		strings = (char**)malloc(sizeof(char*) * self->count);
	}
	if (strings)
	{
		for (size_t i = 0; i < self->count; i++)
		{
			size_t n = strlen(self->data[i]);
			strings[i] = (char*)malloc(sizeof(char) * (n + 2));
			if (strings[i])
			{
				strcpy_s(strings[i], n + 2, self->data[i]);
			}
		}
	}
	return strings;
}

void SRTStringList_free(SRTStringList_t* self)
{
	if (self->data)
	{
		for (int i = 0; i < self->count; i++)
		{
			if (self->data[i])
			{
				free(self->data[i]);
			}
		}
		free(self->data);
	}

}

char* copyChars(const char* chars)
{
	char* tmp = NULL;
	if (chars)
	{
		size_t n = strlen(chars);
		tmp = (char*)malloc(sizeof(char) * (n + 2));
		if (tmp)
		{
			strcpy_s(tmp, sizeof(char) * (n + 2), chars);
		}
	}
	return tmp;
}

