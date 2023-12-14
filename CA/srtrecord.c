#include "srtrecord.h"

SRTRecord_t* SRTRecord_init(SRTRecord_t* self, size_t id)
{
	if (!self)
	{
		self = (SRTRecord_t*)malloc(sizeof(SRTRecord_t));
		if (!self)
		{
			return NULL;
		}
	}

	self->id = id;
	self->key = NULL;
	self->text = NULL;
	self->back = NULL;

	return self;
}

SRTRecord_t* SRTRecord_init_v2(SRTRecord_t* self, size_t id, const char* key, const char* text, const char* back)
{
	self = SRTRecord_init(self, id);
	self->key = copyChars(key);
	self->text = copyChars(text);
	self->back = copyChars(back);
	return self;
}

SRTRecord_t* SRTRecord_free(SRTRecord_t* self)
{
	if (!self->key)
	{
		free(self->key);
	}
	if (!self->text)
	{
		free(self->text);
	}
	if (!self->back)
	{
		free(self->back);
	}
	return self;
}

SRTRecordList_t* SRTRecordList_init(SRTRecordList_t* self)
{
	self->init = SRTRecordList_init;
	self->set = SRTRecordList_set;
	self->get = SRTRecordList_get;
	self->free = SRTRecordList_free;

	if (!self)
	{
		self = (SRTRecordList_t*)malloc(sizeof(SRTRecordList_t));
	}
	if (self)
	{
		SRTList_init(&(self->_list), sizeof(SRTRecord_t));
		self->count = self->_list.count;
	}

	return self;
}

SRTRecord_t* SRTRecordList_add(SRTRecordList_t* self, const SRTRecord_t* emement)
{
	self->count++;
	return (SRTRecord_t*)(self->_list.add(&(self->_list), emement));
}

SRTRecord_t* SRTRecordList_set(SRTRecordList_t* self, size_t idx, const SRTRecord_t* emement)
{
	return (SRTRecord_t*)(self->_list.set(&(self->_list), idx, emement));
}

SRTRecord_t* SRTRecordList_get(SRTRecordList_t* self, size_t idx)
{
	return (SRTRecord_t*)(self->_list.get(&(self->_list), idx));
}

void SRTRecordList_free(SRTRecordList_t* self)
{
	for (size_t i = 0; i < self->count; i++)
	{
		
	}
}

