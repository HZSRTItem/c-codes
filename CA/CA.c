// CA.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <io.h>
#include <direct.h>
#include <ctype.h>
#include <math.h>

#include "srtprintf.h"
#include "srttable.h"
#include "srtcsv.h"
#include "srtlist.h"
#include "srtdict.h"
#include "clistcode.h"
#include "srtrun.h"

int main(int argc, char* argv[])
{
	//char* fmt1 = fmtString(16, NULL);
	//printf("%s: ", fmt1);
	//char line[] = "dsafewafds";
	//printf(fmt1, line);
	//free(fmt1);
	// char csv_fn[_MAX_PATH] = "F:\\code\\cpp\\HistCA\\qd_test_t1.csv";
	// CSV_t csv;
	// CSV_init(&csv);
	// csv.read(&csv, csv_fn);
	// csv.print(&csv);
	// getchar();
	// CSV_free(&csv);
	// SRTTable_t table;
	// SRTTableCell_t cell;
	// SRTTableCellData_t data;
	// printf("%d\n", sizeof(table));
	// printf("%d\n", sizeof(cell.celltype));
	// printf("%d\n", sizeof(cell.celltype));
	// printf("%d\n", sizeof(cell.init));
	// printf("%d\n", sizeof(cell.free));
	// printf("%d\n", sizeof(data));
	//char* line = (char*)malloc(sizeof(char) * 100);
	//char* fmt = (char*)malloc(sizeof(char) * 100);
	////strcpy_s(fmt, 100, "%5d\n");
	////sprintf(line, fmt, 5);
	//printf("%s\n", line);
	//free(fmt);
	//free(line);
	//SRTTable_t table;
	//SRTTable_init(&table);
	//table.addColumn(&table, NULL, STRING_T);
	//table.addColumn(&table, "NULL", STRING_T);
	//table.addColumn(&table, "TIME", STRING_T);
	//table.addColumn(&table, "X", STRING_T);
	//table.addColumn(&table, "Y", STRING_T);
	//table.addColumn(&table, NULL, STRING_T);
	//table.addColumn(&table, NULL, STRING_T);
	//table.addColumn(&table, NULL, STRING_T);
	//SRTTableCellCollection_t* cells = table.addRow(&table);
	//for (size_t i = 0; i < cells->count; i++)
	//{
	//	SRTTable_setString(&table, 0, i, "dsageas");
	//}
	//cells = table.addRow(&table);
	//for (size_t i = 0; i < cells->count; i++)
	//{
	//	SRTTable_setString(&table, 1, i, "aefad");
	//}
	//cells = table.addRow(&table);
	//for (size_t i = 0; i < cells->count; i++)
	//{
	//	SRTTable_setString(&table, 2, i, "eafg");
	//}
	//SRTTable_print(&table);
	//SRTTable_free(&table);

	//SRTCSV_t csv;
	//SRTCSV_read(&csv, "F:\\code\\cpp\\CA\\x64\\Debug\\s2_gz_all_2.csv", ',');
	//SRTCSV_print(&csv);
	//SRTCSV_free(&csv);

	//SRTCSVReadToTable("F:\\code\\cpp\\CA\\x64\\Debug\\s2_gz_all_2.csv", ',', &table);
	//table.free(&table);

	//char line[150] = "nihao\tsadfewa asdf d   sdafdasf  sdafads \nasdfasdf \\ fasdf d\n";

	//const char s[10] = "- \t\n";
	//char* token;
	//char* ptr = NULL;

	///* 获取第一个子字符串 */
	//token = strtok_s(line, s, &ptr);

	///* 继续获取其他的子字符串 */
	//while (token != NULL) {
	//	printf("<%s>\n", token);

	//	token = strtok_s(NULL, s, &ptr);
	//}


	//SRTList_t list;
	//SRTList_init(&list, sizeof(char));
	//const char* line = "F:\\code\\cpp\\CA\\x64\\Debug\\s2_gz_all_2.csv";
	//for (size_t i = 0; i < strlen(line); i++)
	//{
	//	list.add(&list, line + i);
	//}
	//list.add(&list, line+ strlen(line));
	//printf("line:%s\n", (char*)list.data);
	//list.free(&list);

	//const char* struct_name = "Test_t";

	//SRTCharList_t charlist;
	//SRTCharList_init(&charlist, NULL);

	//SRTCharList_free(&charlist);

	//SRTDictString_t dictstr;
	//SRTDictString_init(&dictstr);
	//dictstr.set(&dictstr,"test1", "test1-data");
	//dictstr.set(&dictstr,"test2", "test2-data");
	//dictstr.set(&dictstr, "test2", "test2-1-data");
	//dictstr.set(&dictstr,"test3", "test3-data");
	//printf("test1: %s\n", dictstr.get(&dictstr, "test1"));
	//printf("test2: %s\n", dictstr.get(&dictstr, "test2"));
	//printf("test3: %s\n", dictstr.get(&dictstr, "test3"));
	//dictstr.free(&dictstr);

	return main_sample_select(argc, argv);
	//return clistcode_main(argc, argv);
	//return main_calres(argc, argv);
}



// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
