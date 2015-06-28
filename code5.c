#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <getopt.h>

#define string_length 100
#define number_common_functions 3
#define columns 2

char common_functions[number_common_functions][string_length] = {
	"--help",
	"--show",
	"--change"
};


typedef int(*function_p)();

int main_menu(char **,int *);
int help();
int show();
int change();
int general_changing(char *,char *,char **,char **,int);
char * memory_allocating(int);
char ** memory_allocating_p(int);
int define_changing(FILE *,char **,char **,int);
int space_insert(char *);
int main(int * argc,char * argv[])
{
	main_menu(argv,argc);
	return 0;
}

int main_menu(char ** argv,int * argc)
{
	int counter_1,counter_2;
	int opt;
	function_p function_pointer[number_common_functions] = {help,show,change};
   	static const char *optString = "hsc";
   	int long longIndex;
	static const struct option longOpts[] = {
    	{ "help", no_argument, NULL, 'h' },
    	{ "show", no_argument, NULL, 's' },
    	{ "change", no_argument, NULL, 'c' },
   		{ NULL, no_argument, NULL, 0 }
	};
    opt = getopt_long( argc, argv, optString,longOpts,&longIndex);
    while( opt != -1 ) {
    	printf("%c\n",opt);
        switch( opt ) {
            case 'h':
                function_pointer[0]();
                break;    
            case 's':
                function_pointer[1]();
                break;  
            case 'c':
                function_pointer[2]();
                break;            
            default:
                printf("Command not found!\n");
                return 1;
        }
        opt = getopt_long( argc, argv, optString, longOpts,&longIndex );
    }
	/*for(counter_1 = 1;argv[counter_1] != NULL;counter_1++)
	{
		for(counter_2 = 0;counter_2 < number_common_functions;counter_2++)
		{
			if(strcmp(argv[counter_1],common_functions[counter_2]) == 0)
			{
				function_pointer[counter_2]();
				continue;
			}
		}
	}*/
	return 0;
}

int help()
{
	printf("\n\t--help          show all commands\n");
	printf("\t--show          show text from files on the console\n");
	printf("\t--change        make change in text files(change some word in first file from second file)\n\n");
	return 0;
}

int show()
{
	FILE *first_input,*second_input;
	char files_string[string_length];
	if((first_input = fopen("first_input.txt","a+")) == 0)
		printf("Text file with main text not found.\n");
	while (fgets(files_string,string_length,first_input))
	{
		puts(files_string);
	}
	fclose(first_input);
	if((second_input = fopen("second_input.txt","a+")) == 0)
		printf("Text file with word for change not found.\n");
	while (fgets(files_string,string_length,second_input))
	{
		puts(files_string);
	}
	fclose(second_input);
	return 0;
}

int change()
{
	FILE *first,*second,*third;
	char *string_1,*string_2,**change_1,**change_2;
	int counter_1,counter_2,counter_3;
	counter_1 = 0;
	if((first = fopen("first_input.txt","r+")) == 0)
	{
		printf("First file not found.\n");
		return 0;
	}
	if((second = fopen("second_input.txt","r+")) == 0)
	{
		printf("Second file not found.\n");
		return 0;
	}
	if((third = fopen("third.txt","w+")) == 0)
	{
		printf("Third file not found.\n");
		return 0;
	}
	string_1 = memory_allocating(string_length);
	while(fgets(string_1,string_length,second))
		counter_1++;
	string_2 = memory_allocating(string_length);
	change_1 = memory_allocating_p(counter_1);
	change_2 = memory_allocating_p(counter_1);
	for(counter_2 = 0;counter_2 < counter_1;counter_2++)
	{
		change_1[counter_2] = memory_allocating(string_length);
		change_2[counter_2] = memory_allocating(string_length);
	}
	define_changing(second,change_1,change_2,counter_1);
	while(fgets(string_1,string_length,first))
	{
		general_changing(string_1,string_2,change_1,change_2,counter_1);
	}
	fprintf(third,"%s",string_2);
	free(string_1);
	free(string_2);
	for(counter_2 = 0;counter_2 < counter_1;counter_2++)
	{
		free(change_1[counter_2]);
		free(change_2[counter_2]);
	}
	free(change_1);
	free(change_2);
	fclose(first);
	fclose(second);
	fclose(third);
	return 0;
}

char * memory_allocating(int size)
{
	char *new_string;
	new_string = (char *)malloc(sizeof(char)*size);
	if(!new_string)
	{
		printf("Memmory isn't allocated.\n");
		return 0;
	}
	return new_string;
}

char ** memory_allocating_p(int size)
{
	char **new_string;
	new_string = (char **)malloc(sizeof(char *)*size);
	if(!new_string)
	{
		printf("Memmory isn't allocated.\n");
		return 0;
	}
	return new_string;
}

int define_changing(FILE *reading_file,char **string_1,char **string_2,int size)
{
	int counter;
	char symbol;
	rewind(reading_file);
	for(counter = 0;counter < size;counter++)
	{
		fscanf(reading_file,"%s",string_1[counter]);
		do
		{
			fscanf(reading_file,"%c",&symbol);
		} while (symbol != '-');
		fscanf(reading_file,"%c",&symbol);
		fscanf(reading_file,"%s",string_2[counter]);
	}
	return 0;
}

int general_changing(char * string_1,char * string_2,char **change_1,char ** change_2,int rows)
{
	char signs[] = {' '};
	char *cut_str;
	bool res = false;
	int counter;
	space_insert(string_1);
	cut_str  = strtok(string_1,signs);
	do
	{
		for(counter = 0;counter < rows;counter++)
		{
			if(strcmp(cut_str,change_1[counter]) == 0)
			{
				strcat(string_2,change_2[counter]);
				strcat(string_2," ");
				res = true;
			}
		}
		if(!res)
		{
			strcat(string_2,cut_str);
			strcat(string_2," ");
			res = false;
		}
		res = false;
		cut_str = strtok (NULL,signs);
	} while (cut_str != NULL);
}

int space_insert(char * string)
{
	int counter_1,counter_2;
	char symbol_1,symbol_2;
	counter_1 = 0;
	do
	{
		if(string[counter_1] == '!' || string[counter_1] == '?' || string[counter_1] == '.'
			|| string[counter_1] == ',' || string[counter_1] == ':' || string[counter_1] == ';'
			|| string[counter_1] == '-')
		{
			if(string[counter_1 - 1] != ' ')
			{
				symbol_1 = string[counter_1];
				for(counter_2 = counter_1 + 1;counter_2 < (string_length - 1);counter_2++)
				{
					symbol_2 = string[counter_2];
					string[counter_2] = symbol_1;
					symbol_1 = symbol_2;
				}
				string[counter_1] = ' ';
			}
			if(string[counter_1 + 1] != ' ')
			{
				symbol_1 = string[counter_1 + 1];
				for(counter_2 = counter_1 + 2;counter_2 < (string_length - 1);counter_2++)
				{
					symbol_2 = string[counter_2];
					string[counter_2] = symbol_1;
					symbol_1 = symbol_2;
				}
				string[counter_1 + 1] = ' ';
			}
		}
		counter_1++;
	} while(counter_1 < string_length);
	return 0;
}
