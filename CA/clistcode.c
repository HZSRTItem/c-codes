#include "clistcode.h"

int clistcode_main(int argc, char* argv[])
{
	//if (argc < 2)
	//{
	//	printf("srt_clistcode struct_name");
	//	return 0;
	//}
	//char* struct_name = argv[1];
	char struct_name[100] = "SRTRecord";

	SRTCharList_t charlist;
	SRTCharList_init(&charlist, NULL);
	charlist.addString(&charlist, "typedef struct ");
	charlist.addString(&charlist, struct_name);
	charlist.addString(&charlist, "List ");
	charlist.addString(&charlist, struct_name);
	charlist.addString(&charlist, "List_t;\n\n");

	// struct
	charlist.addString(&charlist, "typedef struct ");
	charlist.addString(&charlist, struct_name);
	charlist.addString(&charlist, "List\n{\n");
	charlist.addString(&charlist, "    SRTList_t _list;\n");
	charlist.addString(&charlist, "    int count;\n\n");
	charlist.addString(&charlist, "    ");
	charlist.addString(&charlist, struct_name);
	charlist.addString(&charlist, "List_t* (*init)(");
	charlist.addString(&charlist, struct_name);
	charlist.addString(&charlist, "List_t* self);\n");
	// add
	charlist.addString(&charlist, "    ");
	charlist.addString(&charlist, struct_name);
	charlist.addString(&charlist, "_t* (*add)(");
	charlist.addString(&charlist, struct_name);
	charlist.addString(&charlist, "List_t* self, const ");
	charlist.addString(&charlist, struct_name);
	charlist.addString(&charlist, "_t* emement);\n");
	// set
	charlist.addString(&charlist, "    ");
	charlist.addString(&charlist, struct_name);
	charlist.addString(&charlist, "_t* (*set)(");
	charlist.addString(&charlist, struct_name);
	charlist.addString(&charlist, "List_t* self, size_t idx,  const ");
	charlist.addString(&charlist, struct_name);
	charlist.addString(&charlist, "_t* emement);\n");
	// get
	charlist.addString(&charlist, "    ");
	charlist.addString(&charlist, struct_name);
	charlist.addString(&charlist, "_t* (*get)(");
	charlist.addString(&charlist, struct_name);
	charlist.addString(&charlist, "List_t* self, size_t idx);\n");
	// free
	charlist.addString(&charlist, "    void (*free)(");
	charlist.addString(&charlist, struct_name);
	charlist.addString(&charlist, "List_t* self);\n");
	// end of struct
	charlist.addString(&charlist, "}");
	charlist.addString(&charlist, struct_name);
	charlist.addString(&charlist, "List_t;\n\n");
	// add static
	charlist.addString(&charlist, struct_name);
	charlist.addString(&charlist, "List_t* ");
	charlist.addString(&charlist, struct_name);
	charlist.addString(&charlist, "List_add(");
	charlist.addString(&charlist, struct_name);
	charlist.addString(&charlist, "List_t* self,  const ");
	charlist.addString(&charlist, struct_name);
	charlist.addString(&charlist, "_t* emement);\n");
	// set static
	charlist.addString(&charlist, struct_name);
	charlist.addString(&charlist, "List_t* ");
	charlist.addString(&charlist, struct_name);
	charlist.addString(&charlist, "List_set(");
	charlist.addString(&charlist, struct_name);
	charlist.addString(&charlist, "List_t* self, size_t idx,  const ");
	charlist.addString(&charlist, struct_name);
	charlist.addString(&charlist, "_t* emement);\n");
	// get static
	charlist.addString(&charlist, struct_name);
	charlist.addString(&charlist, "List_t* ");
	charlist.addString(&charlist, struct_name);
	charlist.addString(&charlist, "List_get(");
	charlist.addString(&charlist, struct_name);
	charlist.addString(&charlist, "List_t* self, size_t idx);\n");
	// free static
	charlist.addString(&charlist, "void ");
	charlist.addString(&charlist, struct_name);
	charlist.addString(&charlist, "List_free(");
	charlist.addString(&charlist, struct_name);
	charlist.addString(&charlist, "List_t* self);\n");

	printf("%s\n", charlist.data);
	SRTCharList_free(&charlist);
	return 0;
}
