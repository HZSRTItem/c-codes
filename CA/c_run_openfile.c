#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <io.h>
#include <direct.h>
#include <ctype.h>
#include <math.h>

#include "srtcodes.h"

#define STR_EQUAL(a, b) (strcmp(a, b) == 0)

#define CR_OF_MAX_MARK_LEN 36
//#define CR_OF_INIT_FN "F:\\code\\cpp\\CA\\x64\\Debug\\CROF\\CROF.txt"
#define CR_OF_INIT_FN "F:\\code\\share\\OF\\CROF.txt"
#define CR_OF_MAX_N 256

typedef struct CRUN_OpenFile
{
	char mark[CR_OF_MAX_MARK_LEN];
	char filename[_MAX_PATH];
}CRUN_OpenFile_t;

CRUN_OpenFile_t* stringToCROFLine(CRUN_OpenFile_t* crof, char* text)
{
	text = strtrim(text);
	size_t n = strlen(text);
	char* mark = text;
	char* filename = NULL;
	for (size_t i = 0; i < n - 1; i++)
	{
		if (text[i] == ':')
		{
			text[i] = '\0';
			filename = text + i + 1;
			mark = strtrim(mark);
			filename = strtrim(filename);
			break;
		}
	}

	if (!filename)
	{
		printf("Can not format line: %s\n", text);
		return NULL;
	}

	strcpy_s(crof->mark, CR_OF_MAX_MARK_LEN, mark);
	strcpy_s(crof->filename, _MAX_PATH, filename);
	return crof;
}

CRUN_OpenFile_t* initCROF(CRUN_OpenFile_t* crof, char* mark, char* filename)
{
	char* mark_tmp = copyChars(mark);
	char* filename_tmp = copyChars(filename);
	mark_tmp = strtrim(mark_tmp);
	filename_tmp = strtrim(filename_tmp);
	strcpy_s(crof->mark, CR_OF_MAX_MARK_LEN, mark_tmp);
	strcpy_s(crof->filename, _MAX_PATH, filename_tmp);
	return crof;
}

size_t stringToCROF(CRUN_OpenFile_t** crof, char* text)
{
	text = strtrim(text);
	size_t n = strlen(text);
	if (n == 0)
	{
		return 0;
	}
	char* line = text;
	size_t n_line = strlen(line);
	size_t n_crof = 0;
	for (size_t i = 0; i < n - 1; i++)
	{
		if (text[i] == '\n')
		{
			text[i] = '\0';
			line = strtrim(line);
			n_line = strlen(line);
			if (n_line != 0)
			{
				stringToCROFLine(crof[0] + n_crof, line);
				n_crof++;
			}
			line = text + i + 1;
		}
	}
	n_line = strlen(line);
	if (n_line != 0)
	{
		stringToCROFLine(crof[0] + n_crof, line);
		n_crof++;
	}

	//for (size_t i = 0; i < n_crof; i++)
	//{
	//	printf("%2d %s: %s\n", i + 1, crof[0][i].mark, crof[0][i].filename);
	//}
	return n_crof;
}

char* crofToString(const CRUN_OpenFile_t* crof, size_t n_crof)
{
	SRTCharList_t clist;
	SRTCharList_init(&clist, NULL);
	for (size_t i = 0; i < n_crof; i++)
	{
		clist.addString(&clist, crof[i].mark);
		clist.addString(&clist, ": ");
		clist.addString(&clist, crof[i].filename);
		clist.addString(&clist, "\n");
	}
	char* line = SRTCharList_copy(&clist, NULL);
	SRTCharList_free(&clist);
	return line;
}

int cr_run_openfile_main(int argc, char* argv[])
{
	//char this_dirname[_MAX_PATH] = { '\0' };

	//if (argc == 2)
	//{
	//	strcpy_s(this_dirname, _MAX_PATH, argv + 1);
	//}

	if (!isFile(CR_OF_INIT_FN))
	{
		printf("Warning: Make File: %s\n", CR_OF_INIT_FN);
		if (!makeFile(CR_OF_INIT_FN))
		{
			printf("Error: Can not make File: %s\n", CR_OF_INIT_FN);
			return 0;
		}
	}

	char* text = readTextAll(CR_OF_INIT_FN);
	if (!text)
	{
		//printf("Can not find: %s\n", CR_OF_INIT_FN);
		return 0;
	}

	CRUN_OpenFile_t* cof = NULL;
	cof = (CRUN_OpenFile_t*)calloc(256, sizeof(CRUN_OpenFile_t));
	size_t n_crof = stringToCROF(&cof, text);

	if (argc < 2)
	{
		printf("srt_of [mark] [--add mark cmd] [--del mark]\n");
		for (size_t i = 0; i < n_crof; i++)
		{
			printf("  +%2lld %s: %s\n", i + 1, cof[i].mark, cof[i].filename);
		}
	}
	else
	{
		size_t n_mark = -1;
		for (size_t i = 1; i < argc; i++)
		{
			if (STR_EQUAL("--add", argv[i]) && i < argc - 2)
			{
				initCROF(cof + n_crof, argv[i + 1], argv[i + 2]);
				n_crof++;
				printf("Add: \n");
				printf("  +%2lld %s: %s\n", n_crof, cof[n_crof - 1].mark, cof[n_crof - 1].filename);
				i += 2;
			}
			else if (STR_EQUAL("--del", argv[i]) && i < argc - 1)
			{
				size_t n_crof_tmp = n_crof;
				printf("Del: \n");
				for (size_t j = 0; j < n_crof; j++)
				{
					if (STR_EQUAL(argv[i + 1], cof[j].mark))
					{
						printf("  +%2lld %s: %s\n", j + 1, cof[j].mark, cof[j].filename);
						for (size_t k = j; k < n_crof - 1; k++)
						{
							cof[k] = cof[k + 1];
						}
						n_crof_tmp--;
					}
				}
				n_crof = n_crof_tmp;
				i++;
			}
			else if (n_mark == -1)
			{
				n_mark = i;
			}
		}

		if (n_mark != -1)
		{
			int is_find = 0;
			for (size_t i = 0; i < n_crof; i++)
			{
				if (STR_EQUAL(argv[n_mark], cof[i].mark))
				{
					system(cof[i].filename);
					is_find = 1;
				}
			}

			if (!is_find)
			{
				printf("Can not find mark: %s\n", argv[1]);
			}
		}
	}

	char* to_text = crofToString(cof, n_crof);
	writeTextAll(CR_OF_INIT_FN, to_text);

	free(to_text);
	free(text);
	free(cof);
	return 0;
}