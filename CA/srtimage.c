#include "srtimage.h"

SRTArrayRead_t* SRTArray_readText(SRTArrayRead_t* self, char filename[_MAX_PATH], char const* sep)
{
	self->n = 0;
	self->nrows = 0;
	self->ncolumns = 0;

	char* token;
	char* ptr = NULL;

	SRTReadLine_t rl;
	SRTReadLine_init(&rl);
	rl.open(&rl, filename);
	while (rl.next(&rl))
	{
		strtrim(rl.line);
		int ncol = 0;
		token = strtok_s(rl.line, sep, &ptr);
		while (token != NULL) {
			strtrim(token);
			size_t token_len = strlen(token);
			if (token > 0)
			{
				
			}
			token = strtok_s(rl.line, sep, &ptr);
		}
	}
	rl.close(&rl);
	return self;
}
