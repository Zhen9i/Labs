#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<stdbool.h>
#include<math.h>
#include<malloc.h>

struct stack
{
	double number;
	struct stack *next;
};

void clean_stdin(void){
	int c;
	do
	{
		c = getchar();
	} while (c != '\n' && c != EOF);
}

struct stack *push(struct stack * next, double d)
{
	struct stack * tmp;
	tmp = (struct stack*)malloc(sizeof(struct stack));
	if (!tmp)
	{
		return 0;
	}
	tmp->number = d;
	tmp->next = next;
	return tmp;
}

double pop(struct stack** next)
{
	struct stack *tmp;
	double d;
	if (*next == 0)
		return 0;
	tmp = *next;
	d = tmp->number;
	*next = tmp->next;
	free(tmp);
	return d;
}

void InfToPol(char *str1, char *str2, int length)
{
	int i = 0, j = 0, k = 0;
	char *sign;
	sign = (char*)malloc(sizeof(char)*(length / 4));
	if (!sign)
		return;
	do
	{
		if (str1[i] >= '0' && str1[i] <= '9')
		{
			str2[j++] = str1[i++];
			if (str1[i] == '+' || str1[i] == '-' || str1[i] == '/' || str1[i] == '*' || str1[i] == ':' || str1[i] == '^' || str1[i] == '=')
			{
				str2[j++] = ' ';
				if (sign[k] == '/' || sign[k] == '*' || sign[k] == ':')
				{
					str2[j++] = ' ';
					str2[j++] = sign[k--];
					str2[j++] = ' ';
				}
			}
			continue;
		}
		else if (str1[i] == '.')
		{
			str2[j++] = str1[i++];
			continue;
		}
		else if (str1[i] == '=')
		{
			while (k != 0)
			{
				str2[j++] = ' ';
				str2[j++] = sign[k--];
				str2[j++] = ' ';
			}
			str2[j++] = ' ';
			str2[j++] = str1[i++];
			str2[j++] = ' ';
			break;
		}
		else if (str1[i] == '+' || str1[i] == '-' || str1[i] == '/' || str1[i] == '*' || str1[i] == ':' || str1[i] == '^' || str1[i] == '(')
		{
			if (str1[i] == '^')
			{
				str2[j++] = ' ';
				str2[j++] = str1[i++];
				str2[j++] = str1[i++];
				str2[j++] = ' ';
				continue;
			}
			else if (str1[i] == '+' || str1[i] == '-')
			{
				if (k != 0 && sign[k] != '(')
				{
					str2[j++] = ' ';
					str2[j++] = sign[k--];
					str2[j++] = ' ';
					continue;
				}
			}
			sign[++k] = str1[i++];
			continue;
		}
		else if (str1[i] == ')')
		{
			while (sign[k] != '(')
			{
				str2[j++] = ' ';
				str2[j++] = sign[k--];
				str2[j++] = ' ';
			}
			str2[j++] = ' ';
			k--;
			i++;
		}
	} while (1);
}

int scan()
{
	int i = 0, c;
	do
	{
		if (i != 0)
			clean_stdin();
		i++;
		scanf("%d", &c);
		if (!c)
		{
			printf("\033[1;4;32mIncorrect symbol.\n\033[0m");
			continue;
		}
		else
			return c;
		break;
	} while (1);
}

int protection(char *str, int length)
{
	int i;
	for (i = 0; i <= length; i++)
	{
		if (str[i] == ' ')
		{
			int j = i;
			do
			{
				str[j] = str[j + 1];
				j++;
			} while (str[j] != '\n');
		}
	}
	for (i = 0; str[i] != '\0' || str[i] != '\n'; i++)
	{
		if (str[i] <= '9' && str[i] >= '0')
			continue;
		else if (str[i] == '+' || str[i] == '-' || str[i] == '*'
			|| str[i] == '/' || str[i] == ':' || str[i] == '^'
			|| str[i] == '#' || str[i] == '(' || str[i] == ')'
			|| str[i] == '\0' || str[i] == '\n' || str[i] == '=')
			continue;
		else
			return 1;
	}
	return 0;
}

int find_res(char *task, int len, struct stack* newStack)
{
	int i = 0, numst = 0, j, k, ppoint;
	double tempnum = 0, temp1, temp2;
	bool num = false, point = false;
	for (; i < len; i++)
	{
		if (task[i] == '=')
		{
			tempnum = pop(&newStack);
			printf("\033[1;34mCalculation result is : \033[1;36m%.2f\n\033[0m", tempnum);
			return 0;
		}
		if (task[i] == '.' || task[i] == ',')
		{
			point = true;
			ppoint = i;
			continue;
		}
		if (num == false && task[i] == ' ')
			continue;
		if (task[i] >= '0' && task[i] <= '9')
		{
			if (num == false)
			{
				numst = i;
				num = true;
				continue;
			}
			continue;
		}
		if (task[i] == ' ' && num == true)
		{
			num = false;
			if (!point)
			{
				for (j = i - 1, k = 1; j >= numst; j--, k *= 10)
				{
					tempnum += (task[j] - 48) * k;
					if ((j - 1) >= 0 && task[j - 1] == '-')
						tempnum *= -1;
				}
			}
			else
			{
				for (j = ppoint + 1, k = 10; j < i; j++, k *= 10)
				{
					tempnum += (double)(task[j] - 48) / k;
				}
				for (j = ppoint - 1, k = 1; j >= numst; j--, k *= 10)
				{
					tempnum += (task[j] - 48) * k;
					if ((j - 1) >= 0 && task[j - 1] == '-')
						tempnum *= -1;
				}
				point = false;
			}
			newStack = push(newStack, tempnum);
			tempnum = 0;
			continue;
		}
		switch (task[i])
		{
		case '+':
		{
					temp1 = pop(&newStack);
					temp2 = pop(&newStack);
					newStack = push(newStack, temp1 + temp2);
					break;
		}
		case '/': case ':':
		{
					  temp1 = pop(&newStack);
					  temp2 = pop(&newStack);
					  newStack = push(newStack, temp2 / temp1);
					  break;
		}
		case '*':
		{
					temp1 = pop(&newStack);
					temp2 = pop(&newStack);
					newStack = push(newStack, temp1 * temp2);
					break;
		}
		case '-':
		{
					temp1 = pop(&newStack);
					temp2 = pop(&newStack);
					newStack = push(newStack, temp2 - temp1);
					break;
		}
		case '^':
		{
					temp1 = pop(&newStack);
					temp2 = (task[++i] - 48);
					newStack = push(newStack, pow(temp1, temp2));
					break;
		}
		default:
		{
				   printf("\033[1;31m\t\tВыражение введено неверно\n\033[0m");
				   return 1;
		}
		}
		if (task[i] == '\0' || task[i] == '\n')
		{
			printf("\033[1;31m\t\tВыражение введено неверно\n\033[0m");
			do
			{
				if (newStack->next != 0)
					pop(&newStack);
			} while (newStack->next != 0);
			return 1;
		}
	}
	return 0;
}

int start()
{
	do
	{
		struct stack * newStack = NULL;
		char *string, *stringnew;
		int length;
		char res;
		do
		{
			printf("\033[1;32mInput length of string:");
			length = scan();
			printf("\033[0m");
			if (length < 3 || length > 1000)
			{
				printf("\033[1;5;31m\t\tIncorrect number\n\033[0m");
				clean_stdin();
				continue;
			}
			else
				break;
		} while (1);
		string = (char*)malloc(sizeof(char)*length);
		if (!string)
		{
			return 0;
		}
		stringnew = (char*)malloc(sizeof(char)*(2 * length));
		if (!stringnew)
		{
			free(string);
			return 0;
		}
		printf("\033[1;33mInput string for calculation:");
		clean_stdin();
		fgets(string, length, stdin);
		protection(string, length);
		printf("\033[0m");
		InfToPol(string, stringnew, length);
		find_res(stringnew, 2 * length, newStack);
		free(string);
		free(stringnew);
		do
		{
			printf("\033[1;33mDo you want to start again(y-yes,n-no)\n\033[0m");
			scanf("%c",&res);
			if (res != 'Y' && res != 'y' && res != 'N' && res != 'n')
			{
				printf("\033[1;4;32mIncorrect symbol\n\033[0m");
				clean_stdin();
				continue;
			}
			else
			{
				clean_stdin();
				break;
			}
		} while (1);
		if (res == 'y' || res == 'Y')
			continue;
		else
			break;
		return 0;
	} while (1);
}



int main()
{
	setlocale(LC_ALL, "");
	start();
	return 0;
}
