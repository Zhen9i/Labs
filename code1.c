#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<locale.h>

struct students{
	char FSTName[80];
	char adress[80];
	int databirth[3];
};

/*
Clear
*/
void clean_stdin()
{
	int c;
	do {
		c = getchar();
	} while (c != '\n' && c != EOF);
}

/*
Получаем данные о студентах
*/

int addInf(struct students *st, int n){
	int i;
	for (i = 0; i < n; i++){
		printf("Получение информации о %d-ом студенте\nВведите инициалы студента(Фамилия Имя Отчество):", i + 1);
		clean_stdin();
		fgets(st[i].FSTName, 80, stdin);
		printf("Введите адресс студента:");
		clean_stdin();
		fgets(st[i].adress, 80, stdin);
		printf("Введите дату рождения студента в виде(День Месяц Год):");
		do{
			clean_stdin();
			scanf("%d %d %d", &st[i].databirth[0], &st[i].databirth[1], &st[i].databirth[2]);
			if (!st[i].databirth[0] || !st[i].databirth[1] || !st[i].databirth[2]){
				printf("Ошибка ввода, введите дату рождения ещё раз: ");
				continue;
			}
			else
				break;
		} while (1);
	}
	return 0;
};

/*
Выводим все студентов
*/

int printfInf(struct students *st, int n){
	int i;
	printf("Вывод информации\n");
	for (i = 0; i < n; i++){
		printf("ФИО:%sДата рождения:%d.%d.%d\nАдрес:%s", st[i].FSTName, st[i].databirth[0], st[i].databirth[1], st[i].databirth[2], st[i].adress);
	}
	return 0;
}

/*
Поиск кол-ва студентов, которые старше fage лет
*/

int findstudents(struct students *st, int n, int fage, int data[3]){
	int k = 0, i;
	for (i = 0; i<n; i++){
		if (data[2] - st[i].databirth[2] > fage){
			k++;
		}
		else if (data[2] - st[i].databirth[2] == fage){
			if (data[1] > st[i].databirth[1]){
				k++;
			}
			else if (data[1] == st[i].databirth[1]){
				if (data[0] >= st[i].databirth[0]){
					k++;
				}
			}
		}
	}
	return k;
}

/*
Вывод в массив имена студентов, которые старше fage лет и сортировка по алфавиту
*/

int findInf(struct students *st, int n, int fage, int data[3], char **str){
	int k = 0, i, j, t, f;
	char exch[80];
	for (i = 0; i<n; i++){
		if (data[2] - st[i].databirth[2] > fage){
			str[k++] = st[i].FSTName;
			continue;
		}
		else if (data[2] - st[i].databirth[2] == fage){
			if (data[1] > st[i].databirth[1]){
				str[k++] = st[i].FSTName;
				continue;
			}
			else if (data[1] == st[i].databirth[1]){
				if (data[0] >= st[i].databirth[0]){
					str[k++] = st[i].FSTName;
					continue;
				}
			}
		}
	}
	for (i = 0; i<k; i++){
		for (j = i + 1; j<k; j++){
			for (f = 0; f<80; f++){
				if (str[i][f] >= str[j][f]){
					for (t = 0; t<80; t++){
						exch[t] = str[i][t];
						str[i][t] = str[j][t];
						str[j][t] = exch[t];
					}
				}
				else
					break;
			}
		}
	}
	return 0;
}

/*
Вывод студентов старших fage лет
*/
int printfst(char** str, int n, int fage){
	int i;
	printf("Имена студентов, которые старше %d лет\n", fage);
	for (i = 0; i<n; i++){
		puts(str[i]);
	}
	return 0;
}

/*
Main
*/

int main(){

	setlocale(LC_ALL, "Russian");

	int N, needstd = 0, age, currentday[3], i;
	struct students *newSt;
	char **ms;

	printf("Введите количество студентов:");
	do{
		clean_stdin();
		scanf("%d", &N);
		if (!N || N < 1 || N>10000){
			printf("Ошибка ввода, введите ещё раз: ");
			continue;
		}
		else{
			break;
		}
	} while (1);

	newSt = (struct students*)malloc(sizeof(struct students)*N);
	if (!newSt)
		return 0;

	addInf(newSt, N);

	printf("Введите возраст студентов для поиска:");
	do{
		clean_stdin();
		scanf("%d", &age);
		if (!age || age < 1 || age > 100){
			printf("Ошибочный ввод, введите снова:");
			continue;
		}
		else
			break;
	} while (1);

	printf("Введите текущую дату, для проверки возраста( День Месяц Год):");
	do{
		clean_stdin();
		scanf("%d %d %d", &currentday[0], &currentday[1], &currentday[2]);
		if (!currentday[0] || !currentday[1] || !currentday[2]){
			printf("Ошибочный ввод, введите снова:");
			continue;
		}
		else
			break;
	} while (1);

	needstd = findstudents(newSt, N, age, currentday);

	ms = (char**)malloc(sizeof(char*)*needstd);
	if (!ms){
		free(newSt);
		return 0;
	}
	for (i = 0; i<needstd; i++){
		ms[i] = (char*)malloc(sizeof(char)* 80);
		if (!ms[i]){
			for (; i >= 0; --i)
				free(ms[i]);
			free(ms);
			free(newSt);
		}
	}

	printfInf(newSt, N);
	findInf(newSt, N, age, currentday, ms);
	if (needstd > 0)
		printfst(ms, needstd, age);
	else
		printf("Нет студентов старше %d лет\n", age);
	free(newSt);
	for(i=0;i<needstd;i++){
	free(ms[i]);
	}
	free(ms);
	return 0;
}
