#include "sample_select.h"

int generateRandomNumber(int x_min, int x_max)
{
	srand((unsigned int)time(NULL));
	int randomNumber = (rand() % (x_max - x_min + 1)) + x_min;
	return randomNumber;
}

int main_sample_select(int argc, char* argv[])
{
	// have input
	int select_number = 100;
	int select_cate = 0;
	char c_name[_MAX_PATH] = "CATEGORY";
	char is_select_name[_MAX_PATH] = "_IS_SELECT_";
	char csv_fn[_MAX_PATH] = "F:\\ProjectSet\\Shadow\\BeiJing\\Samples\\Summary\\sh_bj_spl_summary1.csv";
	char to_csv_fn[_MAX_PATH] = "F:\\ProjectSet\\Shadow\\BeiJing\\Samples\\Summary\\sh_bj_spl_summary1_1.csv";
	char to_select_fn[_MAX_PATH] = { '\0' };
	strcat_s(to_select_fn, _MAX_PATH, csv_fn);
	strcat_s(to_select_fn, _MAX_PATH, "-select");

	SRTCSV_t csv;
	SRTCSV_read(&csv, csv_fn, ',');

	size_t n_rows = csv.n_rows;
	size_t n_columns = csv.n_columns[0];
	char** csv_names = (char**)malloc(sizeof(char*) * (n_columns + 3));
	if (!csv_names)
	{
		return 0;
	}
	for (size_t i = 0; i < n_columns; i++)
	{
		csv_names[i] = csv.data[0][i];
	}

	size_t* cates = (size_t*)malloc(sizeof(size_t) * n_rows);
	if (!cates)
	{
		return 0;
	}
	size_t* is_selects = (size_t*)malloc(sizeof(size_t) * n_rows);
	if (!is_selects)
	{
		return 0;
	}

	int is_have_select_name = -1;
	for (size_t i = 0; i < n_columns; i++)
	{
		if (STR_EQUAL(is_select_name, csv_names[i]))
		{
			is_have_select_name = i;
			break;
		}
	}

	int is_have_c_name = -1;
	for (size_t i = 0; i < n_columns; i++)
	{
		if (STR_EQUAL(c_name, csv_names[i]))
		{
			is_have_select_name = i;
			break;
		}
	}

	for (size_t i = 0; i < n_rows; i++)
	{
		if (is_have_select_name >= 0)
		{
			is_selects[i] = atoi(csv.data[i][is_have_select_name]);
		}
		else
		{
			is_selects[i] = 0;
		}

		if (is_have_c_name >= 0)
		{
			cates[i] = atoi(csv.data[i][is_have_c_name]);
		}
		else
		{
			cates[i] = 0;
		}
	}


	if (select_number < n_rows - 1)
	{
		select_number = n_rows - 1;
	}

	size_t n_find = 0;
	int* n_find_rows = (int*)malloc(sizeof(int) * select_number);
	if (!n_find_rows)
	{
		return 0;
	}
	for (size_t i = 1; i < n_rows; i++)
	{
		int rand_row = generateRandomNumber(1, n_rows);
		if ((cates[rand_row] == select_cate) && (is_selects[rand_row] == 0))
		{
			is_selects[rand_row] = 1;
			n_find_rows[n_find++] = rand_row;
			if (n_find == select_number)
			{
				break;
			}
		}
	}

	FILE* fw = NULL;
	fopen_s(&fw, to_csv_fn, "w");
	if (!fw)
	{
		SRTCSV_free(&csv);
		return 0;
	}
	size_t n_save = n_columns;
	if (is_have_select_name < 0)
	{
		csv_names[n_columns + 1] = is_select_name;
		n_save = n_columns + 1;
	}

	for (size_t i = 0; i < n_save - 1; i++)
	{
		fprintf_s(fw, "%s,", csv_names[i]);
	}
	fprintf_s(fw, "%s\n", csv_names[n_save - 1]);



	for (size_t i = 0; i < n_find; i++)
	{
		int select_row = n_find_rows[i];

		if (is_have_select_name<0)
		{
			for (size_t j = 0; j < n_columns; j++)
			{
				fprintf_s(fw, "%s,", csv.data[select_row][j]);
			}
			fprintf_s(fw, "1\n");
		}
	}

	SRTCSV_free(&csv);
	free(cates);
	free(is_selects);
	free(csv_names);
	return 0;
}
