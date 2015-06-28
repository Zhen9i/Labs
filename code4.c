
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdio_ext.h>
#include <malloc.h>

#define string_length 100
#define min_tree_size 0
#define max_tree_size 1000

struct node
{
char * infomation;
int key;
struct node * left_node, *right_node;
};
int scani()
{
int c;
do
{
__fpurge(stdin);
/*fflush(stdin);*/
scanf("%d", &c);
if (!c || c <= min_tree_size || c >= max_tree_size)
{
printf("Input error : ");
continue;
}
else
{
return c;
}
} while (1);
}
int insert_node(char * insert_string, struct node **main_node)
{
if ((*main_node) == NULL)
{
(*main_node) = (struct node*)malloc(sizeof(struct node));
if (!(*main_node))
return 1;
(*main_node)->infomation = (char *)malloc(sizeof(char)* string_length);
if (!(*main_node)->infomation)
return 1;
strcpy((*main_node)->infomation, insert_string);
(*main_node)->left_node = (*main_node)->right_node = NULL;
return 0;
}
if (strlen((*main_node)->infomation) > strlen(insert_string))
insert_node(insert_string, &(*main_node)->right_node);
else
insert_node(insert_string, &(*main_node)->left_node);
return 0;
}
int delete_tree(struct node *main_node)
{
if (main_node == NULL)
{
return 0;
}
delete_tree(main_node->left_node);
delete_tree(main_node->right_node);
free(main_node->infomation);
free(main_node);
return 0;
}
int print_tree(struct node *main_node, int start)
{
int i;
if (main_node == NULL)
{
return 0;
}
else
{
print_tree(main_node->left_node, ++start);
for (i = 0; i<start; ++i)
printf("|");
printf("%s\n", main_node->infomation);
start--;
}
print_tree(main_node->right_node, ++start);
return 0;
}
struct node * add_node(struct node *main_node)
{
int number_to_add, counter;
char *s;
s = (char*)malloc(sizeof(char)*string_length);
if (!s)
return 0;
printf("Input a number of node to add: :");
do
{
number_to_add = scani();
} while (number_to_add < min_tree_size || number_to_add > max_tree_size);
for (counter = 0; counter < number_to_add; counter++)
{
printf("Input a word to add to tree: ");
__fpurge(stdin);
/*fflush(stdin);*/
fgets(s, string_length, stdin);
insert_node(s, &main_node);
}
free(s);
return main_node;
}
int printf_information()
{
printf("\t\tInformation for command!\n");
printf("'A' - add a number of node to tree.\n");
printf("'B' - see full tree.\n");
printf("'D' - create tree from file.\n");
printf("'S' - save tree to file.\n");
printf("'F' - find max length subtree and min word in subtree.\n");
printf("'E' - exit.\n");
return 0;
}
int save_tree_to_file(struct node *main_node)
{
if (main_node == NULL)
{
return 0;
}
else
{
static FILE * f;
f = fopen("output.txt", "a+");
fprintf(f, "%s\n", main_node->infomation);
fclose(f);
save_tree_to_file(main_node->left_node);
save_tree_to_file(main_node->right_node);
}
return 0;
}
struct node * add_node_from_file(struct node *main_node)
{
FILE * f;
char * s;
s = (char*)malloc(sizeof(char)*string_length);
if (!s)
return 0;
f = fopen("input.txt", "a+");
do
{
fscanf(f, "%s", s);
insert_node(s, &main_node);
} while(feof(f) == 0);
fclose(f);
free(s);
return main_node;
}
int set_tree_key(struct node * main_node, int current_node)
{
if (main_node == NULL)
{
return 0;
}
else
{
main_node->key = current_node++;
set_tree_key(main_node->left_node, current_node);
set_tree_key(main_node->right_node, current_node);
return current_node;
}
}
int find_max_length_subtree(struct node * main_node)
{
static int max_key = 1;
if (main_node == NULL)
{
return 0;
}
else
{
if (main_node->key > max_key)
{
max_key = main_node->key;
}
find_max_length_subtree(main_node->left_node);
find_max_length_subtree(main_node->right_node);
return max_key;
}
}
struct node * find_max_length(struct node * main_node)
{
static int max_node;
static struct node * temp_node;
max_node = find_max_length_subtree(main_node);
if (main_node == NULL)
return 0;
if (max_node != main_node->key)
{
find_max_length(main_node->left_node);
find_max_length(main_node->right_node);
}
else
{
temp_node = main_node;
}
return temp_node;
}
int define_final_result(struct node * main_node)
{
struct node * temp_node;
set_tree_key(main_node, 1);
temp_node = find_max_length(main_node);
printf("Max length subtree - %d\n", temp_node->key);
if (strlen(main_node->infomation) >= strlen(temp_node->infomation))
{
printf("Word with min length is %s", temp_node->infomation);
}
else
{
printf("Word with min length is %s", main_node->infomation);
}
return 0;
}
int menu()
{
int choice;
struct node * tree = NULL;
do
{
printf_information();
printf("Input a letter to choose a function: ");
__fpurge(stdin);
/*fflush(stdin);*/
choice = getchar();
switch (choice)
{
case 'A': case 'a':
{
tree = add_node(tree);
break;
};
case 'B': case 'b':
{
print_tree(tree, 0);
break;
};
case 'E': case 'e':
{
delete_tree(tree);
return 0;
}
case 'S': case 's':
{
save_tree_to_file(tree);
break;
}
case 'D': case 'd':
{
tree = add_node_from_file(tree);
break;
}
case 'F': case 'f':
{
define_final_result(tree);
break;
}
default:
{
printf("Unknown comand!\n");
break;
}
}
} while (1);
free(tree->infomation);
free(tree);
return 0;
}
int main()
{
menu();
return 0;
}
