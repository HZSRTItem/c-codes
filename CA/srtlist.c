#include "srtlist.h"

SRTList_t* SRTList_init(SRTList_t* self, size_t type_size)
{
	self->init = SRTList_init;
	self->add = SRTList_add;
	self->get = SRTList_get;
	self->set = SRTList_set;
	self->free = SRTList_free;

	if (!self)
	{
		self = (SRTList_t*)malloc(sizeof(SRTList_t));
	}

	if (self)
	{
		self->count = 0;
		self->length = 6;
		if (type_size <= 0)
		{
			type_size = 1;
		}
		self->type_size = type_size;
		self->data = malloc(self->length * self->type_size);
	}

	return self;
}

void* SRTList_add(SRTList_t* self, const void* element)
{
	if (self->count >= self->length)
	{
		self->length *= 2;
		void* data_tmp = realloc(self->data, self->length * self->type_size);
		if (data_tmp)
		{
			self->data = data_tmp;
		}
	}

	char* _tmp_data = (char*)(self->data) + (self->count * self->type_size) / sizeof(char);
	if (element)
	{
		memcpy_s(_tmp_data, (self->length - self->count) * self->type_size, element, self->type_size);
	}
	else
	{
		memset(_tmp_data, NULL, self->type_size);
	}
	self->count++;
	return _tmp_data;
}

void* SRTList_get(SRTList_t* self, size_t idx)
{
	idx = idx < 0 ? idx + self->count : idx;
	if (idx < 0 || idx >= self->count)
	{
		return NULL;
	}

	return (char*)(self->data) + (idx * self->type_size) / sizeof(char);
}

void* SRTList_set(SRTList_t* self, size_t idx, const void* element)
{
	idx = idx < 0 ? idx + self->count : idx;
	if (idx < 0 || idx >= self->count)
	{
		return NULL;
	}

	char* _tmp_data = (char*)(self->data) + (idx * self->type_size) / sizeof(char);
	memcpy_s(_tmp_data, (self->length - self->count) * self->type_size, element, self->type_size);
	return _tmp_data;
}

void SRTList_free(SRTList_t* self)
{
	if (self->data)
	{
		free(self->data);
	}
}

/*
 * Allocate a new list_t. NULL on failure.
 */
list_t* list_new(void)
{
	list_t* self;
	if (!(self = (list_t*)(sizeof(list_t))))
		return NULL;
	self->head = NULL;
	self->tail = NULL;
	self->free = NULL;
	self->match = NULL;
	self->len = 0;
	return self;
}

/*
 * Free the list.
 * @self: Pointer to the list
 */
void list_destroy(list_t* self)
{
	unsigned int len = self->len;
	list_node_t* next;
	list_node_t* curr = self->head;

	while (len--) {
		next = curr->next;
		if (self->free) self->free(curr->val);
		free(curr);
		curr = next;
	}

	free(self);
}

/*
 * Append the given node to the list
 * and return the node, NULL on failure.
 * @self: Pointer to the list for popping node
 * @node: the node to push
 */
list_node_t* list_rpush(list_t* self, list_node_t* node) {
	if (!node) return NULL;

	if (self->len) {
		node->prev = self->tail;
		node->next = NULL;
		self->tail->next = node;
		self->tail = node;
	}
	else {
		self->head = self->tail = node;
		node->prev = node->next = NULL;
	}

	++self->len;
	return node;
}

/*
 * Return / detach the last node in the list, or NULL.
 * @self: Pointer to the list for popping node
 */
list_node_t* list_rpop(list_t* self) {
	if (!self->len) return NULL;

	list_node_t* node = self->tail;

	if (--self->len) {
		(self->tail = node->prev)->next = NULL;
	}
	else {
		self->tail = self->head = NULL;
	}

	node->next = node->prev = NULL;
	return node;
}

/*
 * Return / detach the first node in the list, or NULL.
 * @self: Pointer to the list for popping node
 */
list_node_t* list_lpop(list_t* self) {
	if (!self->len) return NULL;

	list_node_t* node = self->head;

	if (--self->len) {
		(self->head = node->next)->prev = NULL;
	}
	else {
		self->head = self->tail = NULL;
	}

	node->next = node->prev = NULL;
	return node;
}

/*
 * Prepend the given node to the list
 * and return the node, NULL on failure.
 * @self: Pointer to the list for pushing node
 * @node: the node to push
 */
list_node_t* list_lpush(list_t* self, list_node_t* node) {
	if (!node) return NULL;

	if (self->len) {
		node->next = self->head;
		node->prev = NULL;
		self->head->prev = node;
		self->head = node;
	}
	else {
		self->head = self->tail = node;
		node->prev = node->next = NULL;
	}

	++self->len;
	return node;
}

/*
 * Return the node associated to val or NULL.
 * @self: Pointer to the list for finding given value
 * @val: Value to find
 */
list_node_t* list_find(list_t* self, void* val) {
	list_iterator_t* it = list_iterator_new(self, LIST_HEAD);
	list_node_t* node;

	while ((node = list_iterator_next(it))) {
		if (self->match) {
			if (self->match(val, node->val)) {
				list_iterator_destroy(it);
				return node;
			}
		}
		else {
			if (val == node->val) {
				list_iterator_destroy(it);
				return node;
			}
		}
	}

	list_iterator_destroy(it);
	return NULL;
}

/*
 * Return the node at the given index or NULL.
 * @self: Pointer to the list for finding given index
 * @index: the index of node in the list
 */
list_node_t* list_at(list_t* self, int index) {
	list_direction_t direction = LIST_HEAD;

	if (index < 0) {
		direction = LIST_TAIL;
		index = ~index;
	}

	if ((unsigned)index < self->len) {
		list_iterator_t* it = list_iterator_new(self, direction);
		list_node_t* node = list_iterator_next(it);
		while (index--) node = list_iterator_next(it);
		list_iterator_destroy(it);
		return node;
	}

	return NULL;
}

/*
 * Remove the given node from the list, freeing it and it's value.
 * @self: Pointer to the list to delete a node
 * @node: Pointer the node to be deleted
 */
void list_remove(list_t* self, list_node_t* node) {
	node->prev
		? (node->prev->next = node->next)
		: (self->head = node->next);

	node->next
		? (node->next->prev = node->prev)
		: (self->tail = node->prev);

	if (self->free) self->free(node->val);

	free(node);
	--self->len;
}

/*
 * Allocate a new list_iterator_t. NULL on failure.
 * Accepts a direction, which may be LIST_HEAD or LIST_TAIL.
 */
list_iterator_t* list_iterator_new(list_t* list, list_direction_t direction) {
	list_node_t* node = direction == LIST_HEAD
		? list->head
		: list->tail;
	return list_iterator_new_from_node(node, direction);
}

/*
 * Allocate a new list_iterator_t with the given start
 * node. NULL on failure.
 */
list_iterator_t* list_iterator_new_from_node(list_node_t* node, list_direction_t direction) {
	list_iterator_t* self;
	if (!(self = malloc(sizeof(list_iterator_t))))
		return NULL;
	self->next = node;
	self->direction = direction;
	return self;
}

/*
 * Return the next list_node_t or NULL when no more
 * nodes remain in the list.
 */
list_node_t* list_iterator_next(list_iterator_t* self) {
	list_node_t* curr = self->next;
	if (curr) {
		self->next = self->direction == LIST_HEAD
			? curr->next
			: curr->prev;
	}
	return curr;
}

/*
 * Free the list iterator.
 */
void list_iterator_destroy(list_iterator_t* self) {
	free(self);
	self = NULL;
}

/*
 * Allocates a new list_node_t. NULL on failure.
 */
list_node_t* list_node_new(void* val) 
{
	list_node_t* self;
	if (!(self = malloc(sizeof(list_node_t))))
		return NULL;
	self->prev = NULL;
	self->next = NULL;
	self->val = val;
	return self;
}