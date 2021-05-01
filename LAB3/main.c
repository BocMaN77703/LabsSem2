#include <stdio.h>
#include <string.h>
#include "Header.h"
int main()
{
	FILE* f=NULL;
	int isType;
	printf("Name of your file: ");
	rewind(stdin);
	char str[20];
	fgets(str, 15, stdin);
	rewind(stdin);
	str[strlen(str) - 1] = '\0';
	printf("1)Text\n2)Binary\n");
	while (!scanf_s("%d", &isType) || (isType < 1) || (isType > 2))
	{
		rewind(stdin);
		printf("Incorrect value! Try again...\n");
	}
	switch (isType)
	{
	case 1:
		textFile(f, str);
		break;
	case 2:
		binFile(f, str);
		break;
	}
}