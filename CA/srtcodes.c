#include "srtcodes.h"

/* c++ get exe directory */
void h_getexedir(char exe_dir[_MAX_PATH])
{
	char* efile = NULL;
	_get_pgmptr(&efile);
	strcpy_s(exe_dir, _MAX_PATH, efile);
	size_t n = strlen(exe_dir);
	if (n > 0)
	{
		for (size_t i = n - 1; i >= 0; i--)
		{
			if (exe_dir[i] == '\\')
			{
				exe_dir[i + 1] = '\0';
				break;
			}
		}
	}

}

/* c add a path in the end*/
void h_addpath(char h_dst[_MAX_PATH], char h_add[_MAX_PATH])
{
	size_t n_dst = strlen(h_dst);
	if (h_dst[n_dst - 1] != '\\')
	{
		h_dst[n_dst] = '\\';
		h_dst[n_dst++] = '\0';
	}
	strcat_s(h_dst, _MAX_PATH, h_add);
}

void getexefilename(char _dst_filename[_MAX_PATH], char* _src_filename)
{
	h_getexedir(_dst_filename);
	h_addpath(_dst_filename, _src_filename);
}

void getfullfilename(char _dst_filename[_MAX_PATH], char* _src_filename)
{
	//char fn[_MAX_PATH] = { '\0' };

	if (strrchr(_src_filename, ':') == NULL)
	{
		h_getcwd(_dst_filename);
		h_addpath(_dst_filename, _src_filename);
	}
	else
	{
		strcpy_s(_dst_filename, _MAX_PATH, _src_filename);
	}

}

void printLine_(int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("-");
	}
	printf("\n");
}


int copyFile(char _dst_filename[_MAX_PATH], char _src_filename[_MAX_PATH])
{
	FILE* fr = NULL;
	fopen_s(&fr, _src_filename, "r");
	if (!fr)
	{
		return 0;
	}
	FILE* fw = NULL;
	fopen_s(&fw, _dst_filename, "w");
	if (!fw)
	{
		return 0;
	}

	char ch = '\0';
	ch = fgetc(fr);

	while (!feof(fr))
	{
		fputc(ch, fw);
		ch = fgetc(fr);
	}

	fclose(fr);
	fclose(fw);
	return 1;
}

void getfilename(char _dst_filename[_MAX_PATH], char _src_filename[_MAX_PATH])
{
	size_t n = strlen(_src_filename);
	size_t n_start = 0;
	for (size_t i = n - 1; i >= 0; i--)
	{
		if (_src_filename[i] == '\\')
		{
			n_start = i;
			break;
		}
	}
	if (n_start)
	{
		n_start += 1;
	}
	strcpy_s(_dst_filename, _MAX_PATH, _src_filename + n_start);
}


char* strtrim(char* _str_strim)
{
	if (!_str_strim)
	{
		return NULL;
	}

	size_t len = strlen(_str_strim);

	if (len == 0)
	{
		return NULL;
	}

	char* s0 = _str_strim;
	char* s1 = NULL;

	for (; *s0; s0++)
	{

		if (!isspaceChar(*s0))
		{
			break;
		}
	}

	for (size_t i = len - 1; i >= 0; i--)
	{
		if (!isspaceChar(_str_strim[i]))
		{
			s1 = _str_strim + i;
			break;
		}
	}

	if (s0 > s1)
	{
		return NULL;
	}

	for (size_t i = 0; i < len; i++)
	{
		_str_strim[i] = *s0;
		if (s0 == s1)
		{
			_str_strim[i + 1] = '\0';
			break;
		}
		s0++;
	}

	return _str_strim;
}

int isspaceString(char* _str)
{
	int is_space = 1;
	char* _str_0 = _str;
	while (*_str_0)
	{
		if (!isspaceChar(*_str_0))
		{
			is_space = 0;
			break;
		}
		++_str_0;
	}
	return is_space;
}

/* c get current time*/
void h_getcurrenttime(struct tm* ct)
{
	time_t timep;
	struct tm ct_tmp;
	time(&timep);
	gmtime_s(&ct_tmp, &timep);
	ct->tm_sec = ct_tmp.tm_sec;
	ct->tm_min = ct_tmp.tm_min;
	ct->tm_hour = ct_tmp.tm_hour;
	ct->tm_mday = ct_tmp.tm_mday;
	ct->tm_mon = ct_tmp.tm_mon;
	ct->tm_year = ct_tmp.tm_year;
	ct->tm_wday = ct_tmp.tm_wday;
	ct->tm_yday = ct_tmp.tm_yday;
	ct->tm_isdst = ct_tmp.tm_isdst;
}

char* getchars_file(FILE* fr, int (*endread)(char* _str))
{
	if (!fr)
	{
		return NULL;
	}

	char ch = '\0';
	SRTCharList_t charlist;
	SRTCharList_init(&charlist, NULL);

	while (!feof(fr))
	{
		ch = fgetc(fr);
		SRTCharList_add(&charlist, ch);
		if (endread)
		{
			if (endread(charlist.data))
			{
				break;
			}
		}
	}

	size_t n = strlen(charlist.data);
	char* ret_str = (char*)malloc(sizeof(char) * (n + 6));
	char* ret_str_tmp = charlist.data;
	if (ret_str)
	{
		if (n >= 3)
		{
			if (charlist.data[0] == 0xEF && charlist.data[1] == 0xBB
				&& charlist.data[2] == 0xBF)
			{
				ret_str_tmp = charlist.data + 3;
			}
		}
		strcpy_s(ret_str, n + 6, ret_str_tmp);
	}

	SRTCharList_free(&charlist);

	return ret_str;
}

size_t string_replace(char* _str, char _src_ch, char _dst_ch)
{
	size_t n = strlen(_str);
	for (int i = 0; i < n; i++)
	{
		if (_str[i] == _src_ch)
		{
			_str[i] = _dst_ch;
		}
	}
	return n;
}

int isspaceChar(char ch)
{
	if (ch < 0 || ch>255)
	{
		return 0;
	}
	return isspace(ch);
}

int getFileSize(char _filename[_MAX_PATH])
{
	int n = 0;
	char ch = '\0';
	FILE* fr = NULL;
	if (fopen_s(&fr, _filename, "r"))
	{
		return 0;
	}

	while (!feof(fr))
	{
		ch = fgetc(fr);
		++n;
	}
	fclose(fr);

	return n - 1;
}

char* readTextAll(char _filename[_MAX_PATH])
{
	FILE* fr = NULL;
	if (fopen_s(&fr, _filename, "r"))
	{
		printf("Can not open file %s\n", _filename);
		return NULL;
	}

	char* _data = getchars_file(fr, NULL);

	fclose(fr);

	return _data;
}

SRTReadLine_t* SRTReadLine_init(SRTReadLine_t* self)
{
	self->fr = NULL;
	self->line = NULL;
	self->max_line_len = 1024;

	self->init = SRTReadLine_init;
	self->open = SRTReadLine_open;
	self->next = SRTReadLine_next;
	self->close = SRTReadLine_close;

	return self;
}

SRTReadLine_t* SRTReadLine_open(SRTReadLine_t* self, char _filename[_MAX_PATH])
{
	if (_filename)
	{
		if (fopen_s(&(self->fr), _filename, "r"))
		{
			self->fr = NULL;
			return NULL;
		}

		self->line = malloc(sizeof(char) * self->max_line_len);
		return self;
	}
	else
	{
		return NULL;
	}
}

void SRTReadLine_close(SRTReadLine_t* self)
{
	if (self->fr)
	{
		fclose(self->fr);
	}
	if (self->line)
	{
		free(self->line);
	}
}

char* SRTReadLine_next(SRTReadLine_t* self)
{
	if (!(self->fr))
	{
		return NULL;
	}

	int len;

	if (fgets(self->line, self->max_line_len, self->fr) == NULL)
		return NULL;

	while (strrchr(self->line, '\n') == NULL)
	{
		self->max_line_len *= 2;
		char* line_temp = (char*)realloc(self->line, self->max_line_len);
		if (line_temp)

		{
			self->line = line_temp;
		}
		else
		{
			return NULL;
		}
		len = (int)strlen(self->line);
		if (fgets(self->line + len, self->max_line_len - len, self->fr) == NULL)
			break;
	}

	char* line_end = strrchr(self->line, '\n');
	if (line_end)
	{
		*line_end = '\0';
	}

	//len = strlen(self->line);
	//printf("len:%d max_line_len:%d %s\n", len, self->max_line_len, self->line);

	return self->line;
}

/* get current path into dst */
int h_getcwd(char dst[_MAX_PATH])
{
	char* buffer;
	// Get the current working directory:
	if ((buffer = _getcwd(NULL, 0)) == NULL)
		return 0;
	else
	{
		strcpy_s(dst, _MAX_PATH, buffer);
		free(buffer);
		return 1;
	}
}

//SRTStringList_t* SRTStringList_init(SRTStringList_t* self)
//{
//    self->N = 6;
//    self->n = 0;
//    self->d = (char**)malloc(sizeof(char*) * self->N);
//
//    self->add = SRTStringList_add;
//    self->free = SRTStringList_free;
//    self->init = SRTStringList_init;
//
//    return self;
//}
//
//char* SRTStringList_add(SRTStringList_t* self, char* _element)
//{
//    if (self->n == self->N)
//    {
//        self->N *= 2;
//        char** tmp = (char**)realloc(self->d, sizeof(char*) * self->N);
//        if (tmp)
//        {
//            self->d = tmp;
//        }
//        else
//        {
//            return NULL;
//        }
//    }
//
//    size_t n = strlen(_element);
//    self->d[self->n] = (char*)malloc(sizeof(char) * (n + 6));
//    if (self->d[self->n])
//    {
//        strcpy_s(self->d[self->n], n + 6, _element);
//    }
//    else
//    {
//        self->d[self->n] = NULL;
//
//    }
//    self->n++;
//
//    return self->d[self->n - 1];
//}
//
//void SRTStringList_free(SRTStringList_t* self)
//{
//    printf("n:%d, N:%d\n", self->n, self->N);
//    for (int i = 0; i < self->n; i++)
//    {
//        free(self->d[i]);
//    }
//    free(self->d);
//
//}

SRTIntList_t* SRTIntList_init(SRTIntList_t* self)
{
	self->length = 6;
	self->count = 0;
	self->data = (int*)malloc(sizeof(int) * self->length);

	self->add = SRTIntList_add;
	self->free = SRTIntList_free;
	self->init = SRTIntList_init;

	return self;
}

int SRTIntList_add(SRTIntList_t* self, int _element)
{
	if (self->count == self->length)
	{
		self->length *= 2;
		int* tmp = (int*)realloc(self->data, sizeof(int) * self->length);
		if (tmp)
		{
			self->data = tmp;
		}
		else
		{
			return 0;
		}
	}

	self->data[self->count++] = _element;

	return self->data[self->count - 1];
}

int* SRTIntList_copy(SRTIntList_t* self, int* _elements)
{
	if (!_elements)
	{
		_elements = (int*)malloc(sizeof(int) * self->count);
	}
	if (_elements)
	{
		memcpy_s(_elements, sizeof(int) * self->count, self->data, sizeof(int) * self->count);
	}
	return _elements;
}

void SRTIntList_free(SRTIntList_t* self)
{
	//printf("n:%d, N:%d\n", self->n, self->N);
	if (self->data)
	{
		free(self->data);
	}
}

SRTDoubleList_t* SRTDoubleList_init(SRTDoubleList_t* self)
{
	self->N = 6;
	self->n = 0;
	self->d = (double*)malloc(sizeof(double) * self->N);

	self->add = SRTDoubleList_add;
	self->free = SRTDoubleList_free;
	self->init = SRTDoubleList_init;

	return self;
}

double SRTDoubleList_add(SRTDoubleList_t* self, double _element)
{
	if (self->n == self->N)
	{
		self->N *= 2;
		double* tmp = (double*)realloc(self->d, sizeof(double) * self->N);
		if (tmp)
		{
			self->d = tmp;
		}
		else
		{
			return 0.0;
		}
	}

	self->d[self->n++] = _element;

	return self->d[self->n - 1];
}

void SRTDoubleList_free(SRTDoubleList_t* self)
{
	//printf("n:%d, N:%d\n", self->n, self->N);
	if (self->d)
	{
		free(self->d);
	}
}

//SRTCharList_t* SRTCharList_init(SRTCharList_t* self)
//{
//    self->N = 6;
//    self->n = 0;
//    self->d = (char*)malloc(sizeof(char) * self->N);
//    if (self->d)
//    {
//        for (int i = 0; i < self->N; i++)
//        {
//            self->d[i] = '\0';
//        }
//    }
//
//    self->add = SRTCharList_add;
//    self->free = SRTCharList_free;
//    self->init = SRTCharList_init;
//    self->adds1 = SRTCharList_adds1;
//    self->adds2 = SRTCharList_adds2;
//    self->adds3 = SRTCharList_adds3;
//    return self;
//}
//
//char* SRTCharList_add(SRTCharList_t* self, char _element)
//{
//    if (self->n == self->N - 1)
//    {
//        self->N *= 2;
//        char* tmp = (char*)realloc(self->d, sizeof(char) * self->N);
//        if (tmp)
//        {
//            self->d = tmp;
//            for (int i = self->n; i < self->N; i++)
//            {
//                self->d[i] = '\0';
//            }
//        }
//        else
//        {
//            return NULL;
//        }
//    }
//
//    self->d[self->n++] = _element;
//
//    return self->d;
//}
//
//char* SRTCharList_adds1(SRTCharList_t* self, const char* _element)
//{
//    size_t n = strlen(_element);
//    for (size_t i = 0; i < n; i++)
//    {
//        self->add(self, _element[i]);
//    }
//    return self->d;
//}
//
//char* SRTCharList_adds2(SRTCharList_t* self, char _element[])
//{
//    size_t n = strlen(_element);
//    for (size_t i = 0; i < n; i++)
//    {
//        self->add(self, _element[i]);
//    }
//    return self->d;
//}
//
//char* SRTCharList_adds3(SRTCharList_t* self, char* _element)
//{
//    size_t n = strlen(_element);
//    for (size_t i = 0; i < n; i++)
//    {
//        self->add(self, _element[i]);
//    }
//    return self->d;
//}
//
//void SRTCharList_free(SRTCharList_t* self)
//{
//    if (self->d)
//    {
//        free(self->d);
//    }
//}

/* a string start contain other string */
int h_striscontain_start(char* find_str, char* src_str)
{
	for (int i = 0; find_str[i] && src_str[i]; i++)
	{
		if (find_str[i] != src_str[i])
		{
			return 0;
		}
	}
	return 1;
}

char* copyString(char* _str)
{
	size_t n = strlen(_str);
	char* o_str = (char*)malloc(sizeof(char) * (n + 2));
	if (o_str)
	{
		strcpy_s(o_str, n + 6, _str);
	}
	return o_str;
}
