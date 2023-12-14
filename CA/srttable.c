/*------------------------------------------------------------------------------
 * File    : srttable.c
 * Time    : 2023-8-21 11:0:34
 * Author  : Zheng Han
 * Contact : hzsongrentou1580@gmail.com
 * License : (C)Copyright 2023, ZhengHan. All rights reserved.
 * Desc    :
------------------------------------------------------------------------------*/
#include "srttable.h"

SRTTableCell_t* SRTTableCell_init(SRTTableCell_t* self)
{
	if (!self)
	{
		self = (SRTTableCell_t*)malloc(sizeof(SRTTableCell_t));
		if (!self)
		{
			return self;
		}
	}

	self->data.dint = 0;
	self->data.ddouble = 0.0;
	self->data.dstring = (char*)malloc(sizeof(char) * 2);
	if (self->data.dstring)
	{
		self->data.dstring[0] = '\0';
	}
	self->celltype = STRING_T;
	return self;
}

void SRTTableCell_free(SRTTableCell_t* self)
{
	if (!self)
	{
		return;
	}
	if (self->data.dstring)
	{
		if (self->celltype == STRING_T)
		{
			free(self->data.dstring);
		}
	}
}

SRTTableCellCollection_t* SRTTableCellCollection_init(SRTTableCellCollection_t* self)
{
	if (!self)
	{
		self = (SRTTableCellCollection_t*)malloc(sizeof(SRTTableCellCollection_t));
		if (!self)
		{
			return NULL;
		}
	}

	self->count = 0;
	self->length = 6;
	self->data = (SRTTableCell_t**)malloc(sizeof(SRTTableCell_t*) * self->length);
	if (!self->data)
	{
		return NULL;
	}
	for (size_t i = 0; i < self->length; i++)
	{
		self->data[i] = NULL;
	}
	return self;
}

SRTTableCellCollection_t* SRTTableCellCollection_add(SRTTableCellCollection_t* self, SRTTableCell_t* element)
{
	if (self->count >= self->length)
	{
		self->length *= 2;
		SRTTableCell_t** data_tmp = (SRTTableCell_t**)realloc(self->data, sizeof(SRTTableCell_t*) * self->length);
		if (data_tmp)
		{
			self->data = data_tmp;
			for (size_t i = self->count; i < self->length; i++)
			{
				self->data[i] = NULL;
			}
		}
	}

	if (!element)
	{
		element = SRTTableCell_init(element);
	}

	self->data[self->count] = element;
	self->count++;
	return self;
}

SRTTableCell_t* SRTTableCellCollection_get(SRTTableCellCollection_t* self, size_t index)
{
	if (index < 0)
	{
		index += self->count;
	}

	if (index >= self->count || index < 0)
	{
		perror("SRTTableCellCollection get index out of range.");
	}

	return self->data[index];
}

SRTTableCell_t* SRTTableCellCollection_set(SRTTableCellCollection_t* self, size_t index, SRTTableCell_t* element)
{
	if (index < 0)
	{
		index += self->count;
	}

	if (index >= self->count || index < 0)
	{
		perror("SRTTableCellCollection set index out of range.");
	}

	SRTTableCell_t* tmp = self->data[index];
	self->data[index] = element;
	return tmp;
}

void SRTTableCellCollection_free(SRTTableCellCollection_t* self)
{
	if (!self)
	{
		return;
	}

	if (self->data)
	{
		for (size_t i = 0; i < self->count; i++)
		{
			SRTTableCell_free(self->data[i]);
			free(self->data[i]);
			self->data[i] = NULL;
		}
		free(self->data);
		self->data = NULL;
	}
}

SRTTable_t* SRTTable_init(SRTTable_t* self)
{
	self->init = SRTTable_init;
	self->addRow = SRTTable_addRow;
	self->addColumn = SRTTable_addColumn;
	self->free = SRTTable_free;
	self->get = SRTTable_get;
	self->getInt = SRTTable_getInt;
	self->getDouble = SRTTable_getDouble;
	self->getString = SRTTable_getString;
	self->setInt = SRTTable_setInt;
	self->setDouble = SRTTable_setDouble;
	self->setString = SRTTable_setString;

	self->n_rows = 0;    // number of rows
	self->n_columns = 0; // number of rows

	self->_length_rows = 6;
	self->rows = (SRTTableCellCollection_t**)malloc(sizeof(SRTTableCellCollection_t*) * self->_length_rows);
	if (!self->rows)
	{
		return NULL;
	}
	for (size_t i = 0; i < self->_length_rows; i++)
	{
		self->rows[i] = NULL;
	}

	self->_length_columns = 6;
	self->column_names = (char**)malloc(sizeof(char*) * self->_length_columns);
	self->columns = (SRTTableCellCollection_t**)malloc(sizeof(SRTTableCellCollection_t*) * self->_length_columns);
	self->column_types = (enum SRTTableDataType*)malloc(sizeof(enum SRTTableDataType) * self->_length_columns);
	if (!(self->column_names && self->columns && self->column_types))
	{
		return NULL;
	}
	for (size_t i = 0; i < self->_length_columns; i++)
	{
		self->column_names[i] = NULL;
		self->columns[i] = NULL;
		self->column_types[i] = STRING_T;
	}
	return self;
}

SRTTableCellCollection_t* SRTTable_addRow(SRTTable_t* self)
{
	if (self->n_rows >= self->_length_rows)
	{
		self->_length_rows *= 2;
		SRTTableCellCollection_t** rows_tmp = (SRTTableCellCollection_t**)realloc(self->rows, sizeof(SRTTableCellCollection_t*) * self->_length_rows);
		if (rows_tmp)
		{
			self->rows = rows_tmp;
			for (size_t i = self->n_rows; i < self->_length_rows; i++)
			{
				self->rows[i] = NULL;
			}
		}
	}

	SRTTableCellCollection_t* cells = SRTTableCellCollection_init(NULL);
	if (cells)
	{
		for (size_t i = 0; i < self->n_columns; i++)
		{
			SRTTableCell_t* cell = SRTTableCell_init(NULL);
			cell->celltype = self->column_types[i];
			SRTTableCellCollection_add(cells, cell);
			SRTTableCellCollection_add(self->columns[i], cell);
		}
		self->rows[self->n_rows] = cells;
	}
	self->n_rows++;
	return cells;
}

SRTTableCellCollection_t* SRTTable_addColumn(SRTTable_t* self, const char* column_name, enum SRTTableDataType data_type)
{
	if (self->n_columns >= self->_length_columns)
	{
		self->_length_columns *= 2;

		SRTTableCellCollection_t** column_tmp = (SRTTableCellCollection_t**)realloc(self->columns, sizeof(SRTTableCellCollection_t*) * self->_length_columns);
		if (column_tmp)
		{
			self->columns = column_tmp;
			for (size_t i = self->n_columns; i < self->_length_columns; i++)
			{
				self->columns[i] = NULL;
			}
		}
		else
		{
			return NULL;
		}

		char** column_names_tmp = (char**)realloc(self->column_names, sizeof(char*) * self->_length_columns);
		if (column_names_tmp)
		{
			self->column_names = column_names_tmp;
			for (size_t i = self->n_columns; i < self->_length_columns; i++)
			{
				self->column_names[i] = NULL;
			}
		}
		else
		{
			return NULL;
		}

		enum SRTTableDataType* column_types = (enum SRTTableDataType*)realloc(self->column_types, sizeof(enum SRTTableDataType) * self->_length_columns);
		if (column_types)
		{
			self->column_types = column_types;
			for (size_t i = self->n_columns; i < self->_length_columns; i++)
			{
				self->column_types[i] = STRING_T;
			}
		}
		else
		{
			return NULL;
		}
	}

	char* column_name_tmp = (char*)malloc(sizeof(char) * (SRTTABLE_MAX_COLN_LEN + 1));
	if (column_name_tmp)
	{
		for (size_t i = 0; i < SRTTABLE_MAX_COLN_LEN + 1; i++)
		{
			column_name_tmp[i] = '\0';
		}

		if (!column_name)
		{
			strcpy_s(column_name_tmp, SRTTABLE_MAX_COLN_LEN, "COLUMN_");
			sprintf_s(column_name_tmp + 7, SRTTABLE_MAX_COLN_LEN - 8, "%zu", self->n_columns + 1);
		}
		else
		{
			size_t n_string = strlen(column_name);
			if (n_string > SRTTABLE_MAX_COLN_LEN)
			{
				for (int i = 0; i < SRTTABLE_MAX_COLN_LEN; i++)
				{
					column_name_tmp[i] = column_name[i];
				}
				printf("Warning: length of SRT Table column name not more than %d. Substring \"%s\" to \"%s\"",
					SRTTABLE_MAX_COLN_LEN, column_name, column_name_tmp);
			}
			strcpy_s(column_name_tmp, SRTTABLE_MAX_COLN_LEN, column_name);
		}
		self->column_names[self->n_columns] = column_name_tmp;
	}
	else
	{
		return NULL;
	}

	self->column_types[self->n_columns] = data_type;

	SRTTableCellCollection_t* cells = SRTTableCellCollection_init(NULL);
	if (cells)
	{
		for (size_t i = 0; i < self->n_rows; i++)
		{
			SRTTableCell_t* cell = SRTTableCell_init(NULL);
			cell->celltype = data_type;
			SRTTableCellCollection_add(cells, cell);
			SRTTableCellCollection_add(self->rows[i], cell);
		}
		self->columns[self->n_columns] = cells;
	}
	self->n_columns++;
	return cells;
}

SRTTableCell_t* SRTTable_get(SRTTable_t* self, size_t row, size_t column)
{
	row += row < 0 ? self->n_rows : 0;
	column += column < 0 ? self->n_columns : 0;
	if (row < 0 || row >= self->n_rows)
	{
		perror("SRTTableCellCollection row index out of range.");
	}
	if (column < 0 || column >= self->n_columns)
	{
		perror("SRTTableCellCollection column index out of range.");
	}
	return self->rows[row]->data[column];
}

int SRTTable_getInt(SRTTable_t* self, size_t row, size_t column)
{
	return SRTTable_get(self, row, column)->data.dint;
}

double SRTTable_getDouble(SRTTable_t* self, size_t row, size_t column)
{
	return SRTTable_get(self, row, column)->data.ddouble;
}

char* SRTTable_getString(SRTTable_t* self, size_t row, size_t column)
{
	return SRTTable_get(self, row, column)->data.dstring;
}

void SRTTable_setInt(struct SRTTable* self, size_t row, size_t column, int d)
{
	SRTTableCell_t* cell = self->get(self, row, column);
	if (cell->celltype != INT_T)
	{
		perror("SRT Table Cell type is not int.");
	}
	cell->data.dint = d;
}

void SRTTable_setDouble(struct SRTTable* self, size_t row, size_t column, double d)
{
	SRTTableCell_t* cell = self->get(self, row, column);
	if (cell->celltype != DOUBLE_T)
	{
		perror("SRT Table Cell type is not double.");
	}
	cell->data.ddouble = d;
}

void SRTTable_setString(struct SRTTable* self, size_t row, size_t column, const char* d)
{
	SRTTableCell_t* cell = self->get(self, row, column);
	if (cell->celltype != STRING_T)
	{
		perror("SRT Table Cell type is not string.");
	}
	if (d)
	{
		size_t n = strlen(d);
		char* d_tmp = (char*)malloc(sizeof(char) * (n + 2));
		if (d_tmp)
		{
			strcpy_s(d_tmp, n + 1, d);
		}
		free(cell->data.dstring);
		cell->data.dstring = d_tmp;
	}
}

int getIntWidth(int n)
{
	int width = 0;
	if (n < 0)
	{
		n = -n;
		++width;
	}
	while (n != 0)
	{
		++width;
		n /= 10;
	}
	return width;
}

void SRTTable_print(SRTTable_t* self)
{
	int n_end = 2;
	char sep = ' ';

	char** column_fmts = (char**)malloc(sizeof(char*) * self->n_columns);
	if (!column_fmts)
	{
		return;
	}

	for (size_t i = 0; i < self->n_columns; i++)
	{
		size_t width = strlen(self->column_names[i]);
		size_t width_tmp = 0;
		if (self->column_types[i] == INT_T)
		{
			for (size_t j = 0; j < self->n_rows; j++)
			{
				width_tmp = getIntWidth(self->rows[j]->data[i]->data.dint);
				if (width < width_tmp)
				{
					width = width_tmp;
				}
			}
			column_fmts[i] = fmtInt((int)width, NULL);
		}
		else if (self->column_types[i] == DOUBLE_T)
		{
			for (size_t j = 0; j < self->n_rows; j++)
			{
				width_tmp = getIntWidth((int)(self->rows[j]->data[i]->data.ddouble));
				width_tmp += n_end;
				if (width < width_tmp)
				{
					width = width_tmp;
				}
			}
			column_fmts[i] = fmtDouble(width, n_end, NULL);
		}
		else if (self->column_types[i] == STRING_T)
		{
			for (size_t j = 0; j < self->n_rows; j++)
			{
				width_tmp = strlen(self->rows[j]->data[i]->data.dstring);
				if (width < width_tmp)
				{
					width = width_tmp;
				}
			}
			column_fmts[i] = fmtString(width, NULL);
		}
		else
		{
			column_fmts[i] = NULL;
		}
		if (width != 0)
		{
			char* fmt = fmtString(width, NULL);
			printf(fmt, self->column_names[i]);
			if (i == self->n_columns - 1)
			{
				printf("\n");
			}
			else
			{
				printf("%c", sep);
			}
			free(fmt);
		}
	}

	for (size_t i = 0; i < self->n_rows; i++)
	{
		size_t j = 0;
		for (; j < self->n_columns - 1; j++)
		{
			if (column_fmts[j])
			{
				printf(column_fmts[j], self->rows[i]->data[j]->data);
				printf("%c", sep);
			}
		}
		if (column_fmts[self->n_columns - 1])
		{
			printf(column_fmts[self->n_columns - 1], self->rows[i]->data[self->n_columns - 1]->data);
			printf("\n");
		}
	}

	for (size_t i = 0; i < self->n_columns; i++)
	{
		if (column_fmts[i])
		{
			free(column_fmts[i]);
		}
	}
	free(column_fmts);
}

void SRTTable_free(SRTTable_t* self)
{
	if (!self)
	{
		return;
	}

	if (self->rows)
	{
		for (size_t i = 0; i < self->n_rows; i++)
		{

			for (size_t j = 0; j < self->n_columns; j++)
			{
				SRTTableCell_free(self->rows[i]->data[i]);
				free(self->rows[i]->data[i]);
			}
			free(self->rows[i]->data);
			free(self->rows[i]);

		}
		free(self->rows);
		for (size_t j = 0; j < self->n_columns; j++)
		{
			free(self->columns[j]->data);
			free(self->columns[j]);
			free(self->column_names[j]);
		}
		free(self->columns);
		free(self->column_names);
	}
}

