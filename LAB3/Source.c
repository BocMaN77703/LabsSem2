#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include "Header.h"
int textMenu()
{
	int choice;
	printf("Choose:\n");
	printf("1)Add numbers\n2)Read file\n3)Average value\n4)Swap first and last number\n5)Exit\n");
	while (!scanf_s("%d", &choice) || (choice < 1) || (choice > 5))
	{
		rewind(stdin);
		printf("Incorrect value! Try again...\n");
	}
	return choice;
}
int binMenu()
{
	int choice;
	printf("Choose:\n");
	printf("1)Add numbers\n2)Read file\n3)Multiplicity\n4)Shift to the right\n5)Exit\n");
	while (!scanf_s("%d", &choice) || (choice < 1) || (choice > 5))
	{
		rewind(stdin);
		printf("Incorrect value! Try again...\n");
	}
	return choice;
}
void add(FILE* f, char* str)
{
	system("CLS");
	f=fopen(str, "w+");
	int num, add=0;
	printf("How many numbers you want to add: ");
	while(!scanf_s("%d", &add))
	{
		rewind(stdin);
		printf("Incorrect value. Try again... ");
	}
	printf("Enter numbers you want to write to the file:\n");
	for (int i = 0; i < add; i++)
	{
		while (!scanf_s("%d", &num))
		{
			rewind(stdin);
			printf("Incorrect value. Try again... ");
		}
		fprintf(f, "%d ", num);
	}
	fclose(f);
	system("CLS");
}
void show(FILE* f, char* str)
{
	system("CLS");
	f=fopen(str, "r");
	int num;
	printf("Your numbers:\n");
	do
	{
		fscanf(f, "%d", &num);
		if (feof(f)) break;
		printf("%d ", num);
	} while (1);
	printf("\n\n");
	fclose(f);
}
void average(FILE* f, char* str)
{
	system("CLS");
	f=fopen(str, "r");
	int num;
	double sum = 0;
	double counter = 0;
	int size = 0;
	do
	{
		fscanf(f, "%d", &num);
		if (feof(f)) break;
		sum += num;
		size++;
	}while (1);
	float av = sum / size;
	system("CLS");
	printf("Average value: %.2f\n\n", av);
	fclose(f);
}
void swap(FILE* f, char* str)
{
	system("CLS");
	f=fopen(str, "r+");
	int tmp, tmp1;
	fpos_t end1;
	fscanf(f, "%d", &tmp);
	char s, i=-1;
	int k1=0, k2=0;
	int flg=0, flg1=0;
	//Длина чисел и нахождение конца
	while (flg1 !=1)
	{
		fseek(f, i, SEEK_END);
		i--;
		fscanf(f, "%c", &s);
		if (s != ' ')
		{
			k2++;
		}
		else
			if(k2>0)
			{
				fgetpos(f, &end1);
				flg1++;
			}
	}
	fseek(f, end1, SEEK_SET);
	fscanf(f, "%d", &tmp1);
	rewind(f);
	flg1 = 0, i = 0;
	while (flg1 != 1)
	{
		fseek(f, i, SEEK_SET);
		fscanf(f, "%c", &s);
		i++;
		k1++;
		if (s == ' ')
		{
			flg1++;
			k1--;
		}
	}
	//Сдвиг
	int k3=0;
	if (k2 > k1)
	{
		k3 = k2 - k1;
		fpos_t start, end;
		for (int i = 0; i < k3; i++)
		{
			rewind(f);
			fgetpos(f, &start);
			fseek(f, -1, SEEK_END);
			do
			{
				fgetpos(f, &end);
				s =getc(f);
				rewind(f);
				end += 1;
				fsetpos(f, &end);
				putc(s,f);
				fseek(f, end - 2, SEEK_SET);
			} while (start < end - 1);
		}
	}
	if (k2 < k1)
	{
		k3 = k2 - k1;
		fpos_t start;
		for (int i = 0; i < k1-k2; i++)
		{
			rewind(f);
			fgetpos(f, &start);
			do
			{
				fseek(f, start+1, SEEK_SET);
				s = getc(f);
				if (feof(f)) break;
				fseek(f, start, SEEK_SET);
				putc(s, f);
				start++;
			} while (1);
		}
	}
	// Собственно свап
	end1 +=k3;
	rewind(f);
	fprintf(f, "%d ", tmp1);
	fseek(f, end1, SEEK_SET);
	fprintf(f, "%d " , tmp);
	//Убираем лишние символы
	if (k3 > 0)
	{
		fpos_t start, start1;
		fgetpos(f, &start1);
		start1--;
		for (int i = 0; i < k3; i++)
		{
			start = start1;
			do
			{
				fseek(f, start + 1, SEEK_SET);
				s = getc(f);
				if (feof(f)) break;
				fseek(f, start, SEEK_SET);
				putc(s, f);
				start++;
			} while (1);
		}
	}
	fclose(f);
	system("CLS");
	show(f, str);
}
void multiplicity(FILE* f, char* str)
{
	system("CLS");
	int kr;
	int counter=0;
	printf("Enter number to check multiplicity: ");
	while (!scanf_s("%d", &kr))
	{
		rewind(stdin);
		printf("Incorrect value. Try again... ");
	}
	f=fopen(str, "rb");
	do
	{
		int temp;
		fread(&temp, sizeof(int), 1, f);
		if (feof(f))  break;
		if ((kr % temp) == 0) counter++;
	} while (1);
	system("CLS");
	printf("Multiple of %d: %d\n",kr, counter);
	fclose(f);
}
void shift(FILE* f, char* str)
{
	int k = 0, num;
	printf("Number of positions: ");
	while (!scanf_s("%d", &k))
	{
		rewind(stdin);
		printf("Incorrect value. Try again... ");
	}
	f = fopen(str, "r+b");
	fpos_t start, end;
	for (int i = 0; i < k; i++)
	{
		fgetpos(f, &start);
		fseek(f, -sizeof(int), SEEK_END);
		do
		{
			fgetpos(f, &end);
			fread(&num, sizeof(int), 1, f);
			rewind(f);
			end += sizeof(int);
			fsetpos(f, &end);
			fwrite(&num, sizeof(int), 1, f);
			fseek(f, end - 2 * sizeof(int), SEEK_SET);
		} while (start < end - sizeof(int));
		/*fseek(f, end - sizeof(int)+1, SEEK_SET);
		char s;
		fread(&s, 1, 1, f);*/
		int s = NULL;
		fseek(f, end - sizeof(int), SEEK_SET);
		fwrite(&s, sizeof(int), 1, f);
	}
	fclose(f);
	showBin(f, str);
}
void textFile(FILE* f, char* str)
{
	int size = 0;
	strcat(str, ".txt");
	while (1)
	{
		switch (textMenu())
		{
		case 1:
			add(f, str);
			break;
		case 2:
			show(f, str);
			break;
		case 3:
			average(f, str);
			break;
		case 4:
			swap(f, str);
			break;
		case 5:
			return 0;
		}
	}
}
int binFile(FILE* f, char* str)
{
	strcat(str, ".bin");
	while (1)
	{
		switch (binMenu())
		{
		case 1:
			addBin(f, str);
			break;
		case 2:
			showBin(f, str);
			break;
		case 3:
			multiplicity(f, str);
			break;
		case 4:
			shift(f, str);
			break;
		case 5:
			return 0;
		}
	}
}
void addBin(FILE* f, char* str)
{
	system("CLS");
	f = fopen(str, "w+b");
	int num, add = 0;
	printf("How many numbers you want to add: ");
	while (!scanf_s("%d", &add))
	{
		rewind(stdin);
		printf("Incorrect value. Try again... ");
	}
	printf("Enter numbers you want to write to the file:\n");
	for (int i = 0; i <add; i++)
	{
		while (!scanf_s("%d", &num))
		{
			rewind(stdin);
			printf("Incorrect value. Try again... ");
		}
		fwrite(&num, sizeof(int), 1, f);
	}
	fclose(f);
	system("CLS");
}
void showBin(FILE* f, char* str)
{
	system("CLS");
	f = fopen(str, "rb");
	int num;
	printf("Your numbers:\n");
	do
	{
		fread(&num, sizeof(int), 1, f);
		if (feof(f))  break;
		printf("%d ", num);
	}while (1);
	printf("\n\n");
	fclose(f);
}