#include "srtcsv.h"

SRTCSV_t* SRTCSV_read(SRTCSV_t* self, char _filename[_MAX_PATH], const char sep)
{
	FILE* fr = NULL;
	fopen_s(&fr, _filename, "r");
	if (!fr) { return NULL; }

	if (!self)
	{
		self = (SRTCSV_t*)malloc(sizeof(SRTCSV_t));
		if (!self)
		{
			fclose(fr);
			return self;
		}
	}

	self->n_rows = 0;
	self->n_columns = NULL;
	self->data = NULL;

	char ch = '\0';
	size_t nrow = 0;
	size_t ncolumn = 0;
	int is_open = 1;
	int is_two = 0;
	int is_read = 1;
	SRTCharList_t cl;
	SRTCharList_init(&cl, NULL);
	SRTIntList_t intlist;
	SRTIntList_init(&intlist);
	SRTStringList_t sl;
	SRTStringList_init(&sl);

	while (!feof(fr))
	{
		if (is_read)
		{
			ch = fgetc(fr);
		}
		is_read = 1;
		if (is_open)
		{
			if ('"' == ch)
			{
				is_open = 0;
				is_two = 0;
			}
			else if (sep == ch)
			{
				sl.add(&sl, cl.data);
				cl.count = 0;
				cl.data[0] = '\0';
				++ncolumn;
			}
			else if ('\n' == ch)
			{
				sl.add(&sl, cl.data);
				cl.count = 0;
				cl.data[0] = '\0';
				++ncolumn;
				intlist.add(&intlist, (int)ncolumn);
				++nrow;
				ncolumn = 0;
			}
			else
			{
				cl.add(&cl, ch);
			}
		}
		else
		{
			if (is_two)
			{
				if (ch != '"')
				{
					is_open = 1;
					is_read = 0;
				}
				else
				{
					cl.add(&cl, ch);
				}
				is_two = 0;
			}
			else
			{
				if (ch == '"')
				{
					is_two = 1;
				}
				else
				{
					is_two = 0;
					cl.add(&cl, ch);
				}
			}
		}
	}

	self->data = (char***)malloc(sizeof(char**) * nrow);
	self->n_rows = nrow;
	self->n_columns = SRTIntList_copy(&intlist, NULL);

	size_t n_sl = 0;
	if (self->data)
	{
		for (size_t i = 0; i < nrow; i++)
		{
			self->data[i] = (char**)malloc(sizeof(char*) * intlist.data[i]);
			if (self->data[i])
			{
				for (size_t j = 0; j < intlist.data[j]; j++)
				{
					char* str = sl.data[n_sl++];
					size_t nstr = strlen(str);
					self->data[i][j] = (char*)malloc(sizeof(char) * (nstr + 2));
					if (self->data[i][j])
					{
						strcpy_s(self->data[i][j], nstr + 2, str);
					}
				}
			}
		}
	}

	SRTStringList_free(&sl);
	SRTIntList_free(&intlist);
	SRTCharList_free(&cl);
	fclose(fr);
	return self;
}
//
//SRTTable_t* SRTCSVReadToTable(char _filename[_MAX_PATH], const char sep, SRTTable_t* table, int is_1_colname)
//{
//	SRTCSV_t csv;
//	SRTCSV_read(&csv, _filename, sep);
//	SRTCSV_print(&csv);
//
//	if (csv.n_rows <= 0)
//	{
//		return NULL;
//	}
//	for (size_t i = 0; i < csv.n_rows; i++)
//	{
//
//	}
//
//	SRTCSV_free(&csv);
//	return table;
//}

void SRTCSV_print(SRTCSV_t* csv)
{
	char sep = '|';
	SRTIntList_t intlist;
	SRTIntList_init(&intlist);
	int width = 0;

	for (size_t i = 0; i < csv->n_rows; i++)
	{
		for (size_t j = 0; j < (size_t)(csv->n_columns[i]); j++)
		{
			width = (int)strlen(csv->data[i][j]);
			if (intlist.count <= j)
			{
				intlist.add(&intlist, width);
			}
			else
			{
				if (intlist.data[j] < width)
				{
					intlist.data[j] = width;
				}
			}
		}
	}

	char** fmts = (char**)malloc(sizeof(char*) * intlist.count);
	if (fmts)
	{
		for (size_t i = 0; i < intlist.count; i++)
		{
			printf("%d, ", intlist.data[i]);
			fmts[i] = fmtString(intlist.data[i], NULL);
			if (!fmts[i])
			{
				return;
			}
		}
		printf("\n");

		for (size_t i = 0; i < csv->n_rows; i++)
		{
			for (size_t j = 0; j < csv->n_columns[i]; j++)
			{
				printf(fmts[j], csv->data[i][j]);
				printf("%c", sep);
			}
			printf("\n");
		}

		for (size_t i = 0; i < intlist.count; i++)
		{
			free(fmts[i]);
		}
		free(fmts);
	}

	SRTIntList_free(&intlist);
}

void SRTCSV_free(SRTCSV_t* csv)
{
	if (csv->data)
	{
		for (size_t i = 0; i < csv->n_rows; i++)
		{
			if (csv->data[i])
			{
				for (size_t j = 0; j < csv->n_columns[j]; j++)
				{
					if (csv->data[i][j])
					{
						free(csv->data[i][j]);
					}
				}
				free(csv->data[i]);
			}
		}
		free(csv->data);
		free(csv->n_columns);
	}

}

