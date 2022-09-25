#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

struct Dict
{
	char*** ar;
	unsigned ec;
};

struct Dict parseDict(const char* dictText);
void teachDict(const struct Dict dict, const unsigned blockSize, const unsigned startBlockIndex);
int min(int x, int y);
unsigned countChars(const char* s, const char c);
char* readFile(const char* filepath);
void genRandOrder(unsigned* a, const unsigned l);
void clearScr(void);

int main(const unsigned char argc, const char** args)
{
	if(argc < 3)
		return 1;

	const char* dictFilepath = args[1];
	const unsigned blockSize = atoi(args[2]);

	unsigned startBlockIndex;

	if(argc == 3)
		startBlockIndex = 0U;
	else
		startBlockIndex = atoi(args[3]) - 1;

	char* dictText = readFile(dictFilepath);

	const struct Dict dict = parseDict(dictText);
	free(dictText);

	teachDict(dict, blockSize, startBlockIndex);

	return 0;
}

struct Dict parseDict(const char* dictText)
{
	struct Dict dict;

	bool isc, isn;
	unsigned di, dsi, ei, wl;

	di = dsi = ei = 0U;

	dict.ec = countChars(dictText, '\n');
	dict.ar = malloc(dict.ec * sizeof(char**));

	while(ei < dict.ec)
		dict.ar[ei++] = malloc(2 * sizeof(char*));

	for(ei = 0U; dictText[di] != '\0'; di++)
	{
		isc = dictText[di] == ':';
		isn = dictText[di] == '\n';

		if(!(isc || isn))
			continue;

		wl = di - dsi;

		dict.ar[ei][isn] = malloc(wl + 1);
		dict.ar[ei][isn][wl] = '\0';
		memcpy(dict.ar[ei][isn], &dictText[dsi], wl);

		dsi = di + isc + 1;
		ei += isn;
	}

	return dict;
}

void teachDict(struct Dict dict, const unsigned blockSize, const unsigned startBlockIndex)
{
	bool iqc, ibc;
	char ic;
	unsigned bsi, cbs, bc, bi, qi, ei, vi;
	unsigned* order;

	bc = (dict.ec + blockSize - 1) / blockSize;
	order = malloc(blockSize * sizeof(unsigned));

	srand(time(NULL));

	for(bi = startBlockIndex; bi < bc; bi++)
	{
		do
		{
			ibc = true;

			bsi = bi * blockSize;
			cbs = min(blockSize, dict.ec - bsi);

			genRandOrder(order, cbs);

			for(qi = 0U; qi < cbs; qi++)
			{
				ei = bsi + order[qi];

				clearScr();
				printf("bi: %u/%u\nqi: %u/%u\nibc: %d\n\n%s: ", bi + 1, bc, qi + 1, cbs, ibc, dict.ar[ei][0]);

				iqc = true;
				vi = 0U;

				do
				{
					ic = getchar();

					if(dict.ar[ei][1][vi] == '\0')
						continue;

					iqc = iqc && ic == dict.ar[ei][1][vi];
					vi++;
				}
				while(ic != '\n');

				ibc = ibc && iqc;

				if(iqc)
					printf("correct");
				else
					printf("incorrect: %s", dict.ar[ei][1]);

				putchar(' ');
				while(getchar() != '\n');
			}
		}
		while(!ibc);
	}

	free(order);
}

int min(int x, int y)
{
	if(x < y)
		return x;
	else
		return y;
}

unsigned countChars(const char* s, const char c)
{
	unsigned n;

	char d;
	unsigned i;

	n = i = 0U;

	while((d = s[i++]) != '\0')
		n += d == c;

	return n;
}

char* readFile(const char* filepath)
{
	char* s;

	unsigned i;
	long l;
	FILE* f;

	i = 0U;

	f = fopen(filepath, "r");

	fseek(f, 0L, SEEK_END);
	l = ftell(f);
	rewind(f);

	s = malloc(l + 1);

	while((s[i++] = getc(f)) != EOF);
	s[l] = '\0';

	return s;
}

void genRandOrder(unsigned* a, const unsigned l)
{
	unsigned r, m, i, j;

	for(i = 0U; i < l; i++)
		a[i] = l;

	for(m = l; m > 0; m--)
	{
		r = rand() % m;

		i = j = 0U;

		while(i++ <= r)
		{
			while(a[j++] < l);
		}

		a[j - 1] = m - 1;
	}
}

void clearScr(void)
{
	printf("\x1B[2J\x1B[1;1H");
}

