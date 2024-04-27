#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <io.h>
#include <direct.h>
#include <ctype.h>
#include <math.h>

/* cl F:\code\cpp\CA\CA\list_csv_fieldnames_main.c  /out:srt_listcsvfns.exe */

int list_csv_fieldnames_main_(int argc, char* argv[])
{
	if (argc <= 1)
	{
		printf("srt_listcsvfns csv_fn\n");
		return 0;
	}

	char _src_filename[_MAX_PATH] = { '\0' };
	strcpy_s(_src_filename, _MAX_PATH, argv[1]);

	FILE* fr = NULL;
	fopen_s(&fr, _src_filename, "r");
	if (!fr)
	{
		printf("Can not open %s\n", _src_filename);
		return 0;
	}

	char ch = '\0';
	ch = fgetc(fr);

	printf("\"");
	while (!feof(fr))
	{
		if (ch == '\n')
		{
			printf("\"\n");
			break;
		}
		if (ch == ',')
		{
			printf("\", \"");
		}
		else
		{
			printf("%c", ch);
		}
		ch = fgetc(fr);
	}

	fclose(fr);
	return 0;
}

int main(int argc, char* argv[])
{
	return list_csv_fieldnames_main_(argc, argv);
}
