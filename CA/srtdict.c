#include "srtdict.h"

SRTKeyDataString_t* SRTKeyDataString_init(SRTKeyDataString_t* self, const char* key, const char* data)
{
	if (self)
	{
		self->key = copyChars(key);
		self->data = copyChars(data);
	}
	else
	{
		self = mkKDStr(key, data);
	}
	return self;
}

void SRTKeyDataString_free(SRTKeyDataString_t* self)
{
	if (self->key)
	{
		free(self->key);
		self->key = NULL;
	}
	if (self->data)
	{
		free(self->data);
		self->key = NULL;
	}
}

SRTKeyDataString_t* mkKDStr(const char* key, const char* data)
{
	SRTKeyDataString_t* kd = (SRTKeyDataString_t*)malloc(sizeof(SRTKeyDataString_t));
	if (kd)
	{
		kd->key = copyChars(key);
		kd->data = copyChars(data);
	}
	return kd;
}

SRTDictString_t* SRTDictString_init(SRTDictString_t* self)
{
	self->init = SRTDictString_init;
	self->set = SRTDictString_set;
	self->get = SRTDictString_get;
	self->free = SRTDictString_free;

	if (!self)
	{
		self = (SRTDictString_t*)malloc(sizeof(SRTDictString_t));
	}
	if (self)
	{
		SRTList_init(&(self->_list), sizeof(SRTKeyDataString_t));
		self->count = self->_list.count;
	}
	return self;
}

SRTKeyDataString_t* SRTDictString_set(SRTDictString_t* self, const char* key, const char* data)
{
	SRTKeyDataString_t* kd = SRTDictString_getKD(self, key);
	if (!kd)
	{
		kd = (SRTKeyDataString_t*)(self->_list.add(&(self->_list), NULL));
		kd->key = copyChars(key);
		kd->data = copyChars(data);
		self->count++;
	}
	else
	{
		if (kd->data)
		{
			free(kd->data);
		}
		kd->data = copyChars(data);
	}
	return kd;
}

char* SRTDictString_get(SRTDictString_t* self, const char* key)
{
	SRTKeyDataString_t* kd = SRTDictString_getKD(self, key);
	if (kd)
	{
		return kd->data;
	}
	else
	{
		return NULL;
	}
}

SRTKeyDataString_t* SRTDictString_getKD(SRTDictString_t* self, const char* key)
{
	SRTKeyDataString_t* kd = NULL;
	for (size_t i = 0; i < self->count; i++)
	{
		kd = (SRTKeyDataString_t*)(self->_list.get(&(self->_list), i));
		if (STR_EQUAL(kd->key, key))
		{
			return kd;
		}
	}
	return NULL;
}

void SRTDictString_free(SRTDictString_t* self)
{
	self->_list.free(&(self->_list));
}



