/*
	
*/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>


#define COLUMNS 3

struct damoye
{
	int dmy[COLUMNS];
};

int mainMenu();
int printfInf();
int clean_stdin();
int addInf();
int readInf();
int find1();
int find2();
int find3();


int main()
{
	if (!mainMenu())
	{
#ifdef _MSC_VER
		system("pause");
#endif
		return 0;
	}
	else
		return 1;
}

int mainMenu()
{
	do
	{
		char choice;
		printfInf();
		scanf("%c", &choice);
		clean_stdin();
		switch (choice)
		{
		case 'a': case 'A':
			if (addInf())
				return 1;
			break;
		case 'b': case 'B':
			if (readInf())
				return 1;
			break;
		case 'c': case 'C':
			find1();
			break;
		case 'd': case 'D':
			find2();
			break;
		case 'e': case 'E':
			find3();
			break;
		case 'q': case 'Q':
			return 0;
		default :
			printf("Unknown command. Try again\n");
		} 
	} while (1);
}

int printfInf()
{
	printf("\tMain menu\n");
	printf("Press 'A' to add information to binary file\n");
	printf("Press 'B' to read binary file\n");
	printf("Press 'C' to find smallest year\n");
	printf("Press 'D' to find spring's date\n");
	printf("Press 'E' to find latest date\n");
	printf("Press 'Q' to quit\n");
	return 0;
}

int clean_stdin()
{
#ifdef __GNUC__
	__fpurge(stdin);
#elif _MSC_VER
	fflush(stdin);
#else
	int c;
	do
	{
		c = getchar();
	} while (c != '\n' && c != EOF);
#endif
	return 0;
}

int addInf()
{
	FILE *data;
	int dmy[COLUMNS];
	if (!(data = fopen("data.bin", "w+b")))
		return 1;
	do
	{
		int ctr;
		printf("Input information(Day Month Year) or (-1 -1 -1) to finish: ");
		ctr = scanf("%d %d %d", &dmy[0], &dmy[1], &dmy[2]);
		clean_stdin();
		if (dmy[0] == -1 && dmy[1] == -1 && dmy[2] == -1)
		{
			fwrite(&dmy, sizeof(int), COLUMNS, data);
			break;
		}
		else if (dmy[0] < 0 || dmy[0] > 31 || dmy[1] < 0 || dmy[1] > 12
			|| dmy[2] < 0 || dmy[2] > 2015)
		{
			printf("You input wrong date(this date is %d:%d:%d)\n", dmy[0], dmy[1], dmy[2]);
			continue;
		}
		else if (ctr == 3)
		{
			fwrite(&dmy, sizeof(int), COLUMNS, data);
			continue;
		}
		else
		{
			printf("Wrong parameters\n");
			continue;
		}
	} while (1);
	fclose(data);
	return 0;
}

int readInf()
{
	FILE *data;
	int  sizeInf, tmpInf[COLUMNS], i;
	struct damoye * inf;
	sizeInf = 0;
	inf = (struct damoye *)malloc(sizeof(struct damoye));
	if (!inf)
		return 1;
	if (!(data = fopen("data.bin", "r+b")))
	{
		free(inf);
		return 1;
	}
	while (!feof(data))
	{
		inf = (struct damoye *)realloc(inf, sizeof(struct damoye) * (++sizeInf));
		if (!inf)
		{
			printf("Memory error\n");
			fclose(data);
			return 1;
		}
		fread(&tmpInf, sizeof(int), COLUMNS, data);
		inf[sizeInf - 1].dmy[0] = tmpInf[0];
		inf[sizeInf - 1].dmy[1] = tmpInf[1];
		inf[sizeInf - 1].dmy[2] = tmpInf[2];
	}
	for (i = 0; (inf[i].dmy[0] != -1 && inf[i].dmy[1] != -1 && inf[i].dmy[2] != -1); i++)
	{
		printf("%2d:%2d:%4d\n", inf[i].dmy[0], inf[i].dmy[1], inf[i].dmy[2]);
	}
	fclose(data);
	free(inf);
	return 0;
}

int find1()
{
	FILE *data;
	int  sizeInf, tmpInf[COLUMNS], i,j;
	struct damoye * inf;
	sizeInf = 0;
	inf = (struct damoye *)malloc(sizeof(struct damoye));
	if (!inf)
		return 1;
	if (!(data = fopen("data.bin", "r+b")))
	{
		free(inf);
		return 1;
	}
	while (!feof(data))
	{
		inf = (struct damoye *)realloc(inf, sizeof(struct damoye) * (++sizeInf));
		if (!inf)
		{
			printf("Memory error\n");
			fclose(data);
			return 1;
		}
		fread(&tmpInf, sizeof(int), COLUMNS, data);
		inf[sizeInf - 1].dmy[0] = tmpInf[0];
		inf[sizeInf - 1].dmy[1] = tmpInf[1];
		inf[sizeInf - 1].dmy[2] = tmpInf[2];
	}
	for (i = 0,j = 0; (inf[i].dmy[0] != -1 && inf[i].dmy[1] != -1 && inf[i].dmy[2] != -1); i++)
	{
		if (inf[i].dmy[2] < inf[j].dmy[2])
			j = i;
	}
	printf("Date with smallest year is %2d:%2d:%4d\n", inf[j].dmy[0], inf[j].dmy[1], inf[j].dmy[2]);
	fclose(data);
	free(inf);
	return 0;
}

int find2()
{
	FILE *data;
	int  sizeInf, tmpInf[COLUMNS], i;
	struct damoye * inf;
	sizeInf = 0;
	inf = (struct damoye *)malloc(sizeof(struct damoye));
	if (!inf)
		return 1;
	if (!(data = fopen("data.bin", "r+b")))
	{
		free(inf);
		return 1;
	}
	while (!feof(data))
	{
		inf = (struct damoye *)realloc(inf, sizeof(struct damoye) * (++sizeInf));
		if (!inf)
		{
			printf("Memory error\n");
			fclose(data);
			return 1;
		}
		fread(&tmpInf, sizeof(int), COLUMNS, data);
		inf[sizeInf - 1].dmy[0] = tmpInf[0];
		inf[sizeInf - 1].dmy[1] = tmpInf[1];
		inf[sizeInf - 1].dmy[2] = tmpInf[2];
	}
	for (i = 0; (inf[i].dmy[0] != -1 && inf[i].dmy[1] != -1 && inf[i].dmy[2] != -1); i++)
	{
		if (inf[i].dmy[1] == 3 || inf[i].dmy[1] == 4 || inf[i].dmy[1] == 5)
			printf("Springs date is %2d:%2d:%4d\n", inf[i].dmy[0], inf[i].dmy[1], inf[i].dmy[2]);
	}
	fclose(data);
	free(inf);
	return 0;
}

int find3()
{
	FILE *data;
	int  sizeInf, tmpInf[COLUMNS], i,j;
	struct damoye * inf;
	sizeInf = 0;
	inf = (struct damoye *)malloc(sizeof(struct damoye));
	if (!inf)
		return 1;
	if (!(data = fopen("data.bin", "r+b")))
	{
		free(inf);
		return 1;
	}
	while (!feof(data))
	{
		inf = (struct damoye *)realloc(inf, sizeof(struct damoye) * (++sizeInf));
		if (!inf)
		{
			printf("Memory error\n");
			fclose(data);
			return 1;
		}
		fread(&tmpInf, sizeof(int), COLUMNS, data);
		inf[sizeInf - 1].dmy[0] = tmpInf[0];
		inf[sizeInf - 1].dmy[1] = tmpInf[1];
		inf[sizeInf - 1].dmy[2] = tmpInf[2];
	}
	for (i = 0, j = 0; (inf[i].dmy[0] != -1 && inf[i].dmy[1] != -1 && inf[i].dmy[2] != -1); i++)
	{
		if (inf[i].dmy[2] > inf[j].dmy[2])
			j = i;
		else if (inf[i].dmy[2] == inf[j].dmy[2])
		{
			if (inf[i].dmy[1] > inf[j].dmy[1])
			{
				j = i;
			}
			else if (inf[i].dmy[1] == inf[j].dmy[1])
			{
				if (inf[i].dmy[0] > inf[j].dmy[0])
				{
					j = i;
				}
			}
		}
	}
	printf("Latest date is %2d:%2d:%4d\n", inf[j].dmy[0], inf[j].dmy[1], inf[j].dmy[2]);
	fclose(data);
	free(inf);
	return 0;
}