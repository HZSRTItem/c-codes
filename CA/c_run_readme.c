#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <io.h>
#include <direct.h>
#include <ctype.h>
#include <math.h>

int cr_run_readme_main(int argc, char* argv[])
{
	char this_dirname[_MAX_PATH] = { '\0' };

	if (argc == 2)
	{
		strcpy_s(this_dirname, _MAX_PATH, argv + 1);
	}

	FILE* fw;



	return 0;
}