// HitachiDecoder.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <io.h>
#include <fcntl.h>
int _tmain(int argc, _TCHAR* argv[])
{
	FILE *in, *out;
	if (argc < 2)
	{
		_setmode(0, _O_BINARY);
		in=stdin;
		out = stdout;
	}
	else
	{
		in = fopen(argv[1], "rb");
		if (!in)
		{
			fprintf(stderr, "Failed to open file: %s for reading.\n", argv[1]);
			return 2;
		}
		char buf[65536];
		strcpy(buf, argv[1]);
		char *t=strrchr(buf, '.');
		strcpy(t, ".csv");
		out = fopen(buf, "wt");
		if (!out)
		{
			fprintf(stderr, "Failed to open file: %s for reading.\n", buf);
			return 3;
		}
	}
	unsigned char buf[1365692+100];
	memset(buf, 0, sizeof(buf));
	fread(buf, 1, sizeof(buf),in);
	for (size_t i = 0xFC5; buf[i]; i+=0x80)
	{
		fprintf(out, "%d/%02d/%02d %02d:%02d:%02d\n",
			256*buf[i] + buf[i+1], (int)buf[i+2], (int)buf[i+3],
			(int)buf[i+4], (int)buf[i+5], (int)buf[i+6]);
	}
	return 0;
}

