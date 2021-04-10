#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"
union Info
{
	char date[10];
	int seasons;
};
struct Series
{
	char title[20];
	int episodes;
	union Info info;
	int isType;
	struct Series* adress;
};
int menu()
{
	int choice;
	printf("Choose an operation:\n");
	printf("1) Add series\n2) Show series\n3) Delete series\n4) Search series\n5) Write to the file\n6) Read from file\n7) Exit\n");
	while (!scanf_s("%d", &choice) || choice<1 || choice>7)
	{
		printf("Incorrect value! Try again...\n");
		rewind(stdin);
	}
	system("CLS");
	return choice;
}
void add(struct Series** serial)
{
	system("CLS");
	struct Series* temp = *serial;
	do
	{
		if (!(*serial = (struct Series*)calloc(1, sizeof(struct Series))))
		{
			puts("Not enough memory!\n");
			return;
		}
		printf("Enter series title: ");
		rewind(stdin);
		fgets((*serial)->title, 20, stdin);
		rewind(stdin);
		printf("Enter number of episodes: ");
		while (!scanf_s("%d", &(*serial)->episodes) || ((*serial)->episodes < 1))
		{
			rewind(stdin);
			system("CLS");
			printf("Incorrect value! try again...\n");
		}
		printf("Enter '1' to enter releae date or '2' to enter number of seasons: ");
		while (!scanf_s("%d", &(*serial)->isType) || ((*serial)->isType < 1) || ((*serial)->isType > 2))
		{
			rewind(stdin);
			system("CLS");
			printf("Incorrect value! try again...\n");
		}
		if ((*serial)->isType == 1)
		{
			printf("Enter release date(YYYYMMDD): ");
			rewind(stdin);
			fgets((*serial)->info.date, 10, stdin);
			rewind(stdin);
		}
		else
		{
			printf("Enter number of seasons: ");
			while (!scanf_s("%d", &(*serial)->info.seasons) || ((*serial)->info.seasons < 1))
			{
				rewind(stdin);
				system("CLS");
				printf("Incorrect value! try again...\n");
			}

		}
		deleteEnter(*serial);
		rightRegister(*serial);
		(*serial)->adress = temp;
		temp = *serial;
		system("CLS");
		printf("Do you want to enter more series??? (y/n): ");
		rewind(stdin);
	} while (getchar() == 'y');
	system("CLS");
}
void print(struct Series* serial, int flag)
{
	if (!serial)
	{
		printf("Stack is empty...\n");
		return;
	}
	char table[] = "S E R I E S";
	printLine();
	printf("|\t\t\t\t\t %-43s|\n", table);
	printLine();
	printf("|\t%-5s|\t%-19s|\t%-5s|\t%-5s|\t%-8s|\n", "Note", "Title", "Episodes", "Seasons", "Release Date");
	printLine();
	int i = 1;
	if (flag == 1)
	{
		if (serial->isType == 1)
		{
			printf("|\t%-5d|\t%-19s|\t%-8d|\t%-7s|\t%-12s|\n",
				i, serial->title,
				serial->episodes, "-",
				serial->info.date);
			printLine();
		}
		else
		{
			printf("|\t%-5d|\t%-19s|\t%-8d|\t%-7d|\t%-12s|\n",
				i, serial->title,
				serial->episodes, serial->info.seasons,
				"-");
			printLine();
		}
		serial = serial->adress;
		i++;
	}
	else
	{
		do
		{
			if (serial->isType == 1)
			{
				printf("|\t%-5d|\t%-19s|\t%-8d|\t%-7s|\t%-12s|\n",
					i, serial->title,
					serial->episodes, "-",
					serial->info.date);
				printLine();
			}
			else
			{
				printf("|\t%-5d|\t%-19s|\t%-8d|\t%-7d|\t%-12s|\n",
					i, serial->title,
					serial->episodes, serial->info.seasons,
					"-");
				printLine();
			}
			serial = serial->adress;
			i++;
		} while (serial);
	}
}
void printLine()
{
	for (int i = 0; i < 85; i++)
	{
		printf("%c", '_');
	}
	printf("\n");
}
void deleteEnter(struct Series* serial)
{
		serial->title[strlen(serial->title) - 1] = '\0';
		if (serial->isType == 1) serial->info.date[strlen(serial->info.date) - 1] = '\0';
		serial = serial->adress;
}
void rightRegister(struct Series* serial)
{
	if ((serial->title[0] >= 'a') && (serial->title[0] <= 'z'))
		serial->title[0] -= 32;
	for (int i = 1; i < 20; i++)
	{
		if ((serial->title[i] >= 'A') && (serial->title[i] <= 'Z'))
			serial->title[i] += 32;
	}
	for (int i = 1; i < 20; i++)
	{
		if ((serial->title[i] >= 'a') && (serial->title[i] <= 'z') &&
			(((serial->title[i - 1]) == '-') || ((serial->title[i - 1]) == ' ')))
			serial->title[i] -= 32;
	}
}
void del(struct Series** serial)
{
	if (!serial)
	{
		printf("Stack is empty...\n");
		return;
	}
	int choice = 0;
	system("CLS");
	print(*serial,0);
	printf("Enter number of note you want to delete (0-Exit): ");
	while (!scanf_s("%d", &choice) || (choice < 0))
	{
		printf("Incorrect value. Try again.\n");
		rewind(stdin);
	}
	if (choice == 0) return;
	choice--;
	struct Series* temp, *temp2, *temp3;
	for(int i=0;i<choice-1;i++)  *serial = (*serial)->adress;
	temp = *serial;
	*serial = (*serial)->adress;
	temp2 = *serial;
	temp3 = (*serial)->adress;
	*serial = temp;
	(*serial)->adress = temp3;
	free(temp2);
	system("CLS");
}
void search(struct Series* serial)
{
	if (!serial)
	{
		printf("Stack is empty...\n");
		return;
	}
	system("CLS");
	printf("Select option to search:\n");
	printf("1)Title\n");
	printf("2)Number of episodes\n");
	printf("3)Date of release\n");
	printf("4)Number of seasons\n");
	printf("5)Exit\n");
	int choice, intToSearch = 0, flag = 0;
	char str[20];
	while (!scanf_s("%d", &choice) || (choice < 1) || (choice > 5))
	{
		system("CLS");
		printf("Incorrect value\n");
		rewind(stdin);
	}
	switch (choice)
	{
	case 1:
		printf("Enter title: ");
		rewind(stdin);
		fgets(str, 20, stdin);
		str[strlen(str) - 1] = '\0';
		do
		{
			int temp = 0;
			if (strlen(serial->title) == strlen(str))
			{
				for (int j = 0; j < strlen(str); j++)
				{
					if (serial->title[j] != str[j])
						break;
					else
						temp++;
					if (temp == strlen(str))
						print(serial, 1);
					flag = 1;
				}
			}
			serial = serial->adress;
		}while (serial);
		break;
	case 2:
		printf("Enter number of episodes: ");
		while (!scanf_s("%d", &intToSearch) || (intToSearch < 1))
		{
			printf("Incorrect value\n");
			rewind(stdin);
		}
		do
		{
			if (serial->episodes == intToSearch)
			{
				print(serial,1);
				flag = 1;
				break;
			}
			serial = serial->adress;
		} while (serial);
		break;
	case 3:
		printf("Enter date of release(YYYYMMDD): ");
		rewind(stdin);
		fgets(str, 10, stdin);
		rewind(stdin);
		str[strlen(str) - 1] = '\0';
		do
		{
			if (serial->isType != 1)	serial = serial->adress;
			int temp = 0;
			if (strlen(serial->info.date) == strlen(str))
			{
				for (int j = 0; j < strlen(str); j++)
				{
					if (serial->info.date[j] != str[j])
						break;
					else
						temp++;
					if (temp == strlen(str))
						print(serial,1);
					flag = 1;
				}
			}
			serial = serial->adress;
		} while (serial);
		break;
	case 4:
		printf("Enter number of seasons: ");
		while (!scanf_s("%d", &intToSearch) || (intToSearch < 1))
		{
			printf("Incorrect value\n");
			rewind(stdin);
		}
		do
		{
			if (serial->isType != 2) continue;
			if (serial->info.seasons == intToSearch)
			{
				print(serial,1);
				flag = 1;
				break;
			}
			serial = serial->adress;
		} while (serial);
		break;
	case 5:
		system("CLS");
		return;
		break;
	}
	if (flag == 0) printf("Nothing found...Try again.\n");
}
void fprintLine(FILE* f)
{
	for (int i = 0; i < 85; i++)
	{
		fprintf(f,"%c", '_');
	}
	fprintf(f,"\n");
}
void clear(struct Series** serial)
{
	while (*serial != NULL)
	{
		struct Series* temp;
		temp = *serial;
		*serial = (*serial)->adress;
		free(temp);
	}
}
void write(struct Series* serial)
{
	if (!serial)
	{
		printf("Stack is empty...\n");
		return;
	}
	printf("Choose type of file:\n1)Text file(.txt)\n2)Binary file(.bin)\n3)Exit\n");
	int choice;
	while (!scanf_s("%d", &choice) || (choice < 1) || (choice > 2))
	{
		printf("Incorrect value. Try again.\n");
		rewind(stdin);
	}
	switch (choice)
	{
	case 1:
		printf("Choose:\n1)Write as a table\n2)Write as normal text\n");
		while (!scanf_s("%d", &choice) || (choice < 1) || (choice > 2))
		{
			printf("Incorrect value. Try again.\n");
			rewind(stdin);
		}
		switch (choice)
		{
		case 1:
			writeTextFileTable(serial);
			break;
		case 2:
			writeTextFile(serial);
			break;
		}
		printf("Successfully written to the file!!!\n");
		break;
	case 2:
		writeBinFile(serial);
		break;
	case 3: break;
	}
}
void writeTextFileTable(struct Series* serial)
{
	FILE* f;
	f = fopen("Series table.txt", "w+");
	char table[] = "S E R I E S";
	fprintLine(f);
	fprintf(f, "|\t\t\t\t\t %-43s|\n", table);
	fprintLine(f);
	fprintf(f, "|\t%-5s|\t%-19s|\t%-5s|\t%-5s|\t%-8s|\n", "Note", "Title", "Episodes", "Seasons", "Release Date");
	fprintLine(f);
	int i = 1;
	do
	{
		if (serial->isType == 1)
		{
			fprintf(f, "|\t%-5d|\t%-19s|\t%-8d|\t%-7s|\t%-12s|\n",
				i, serial->title,
				serial->episodes, "-",
				serial->info.date);
			fprintLine(f);
		}
		else
		{
			fprintf(f, "|\t%-5d|\t%-19s|\t%-8d|\t%-7d|\t%-12s|\n",
				i, serial->title,
				serial->episodes, serial->info.seasons,
				"-");
			fprintLine(f);
		}
		serial = serial->adress;
		i++;
	} while (serial);
	fclose(f);
	system("CLS");
}
void writeTextFile(struct Series* serial)
{
	FILE* f;
	f = fopen("Series.txt", "w+");
	do
	{
		if (serial->isType == 1)
		{
			fprintf(f, "%s\n%d\n%s\n%s\n", serial->title, serial->episodes, "-", serial->info.date);
		}
		else
		{
			fprintf(f, "%s\n%d\n%d\n%s\n", serial->title,	serial->episodes, serial->info.seasons, "-");
		}
		serial = serial->adress;
	} while (serial);
	fclose(f);
	system("CLS");
}
void writeBinFile(struct Series* serial)
{
	FILE* f;
	f = fopen("Series.bin", "w+");
	char s = '-';
	do
	{
		if (serial->isType == 1)
		{
			fwrite(serial->title,strlen(serial->title),1, f);
			fwrite(&(serial->episodes), sizeof(int), 1, f);
			fwrite(&s, 1, 1, f);
			fwrite(serial->info.date, strlen(serial->info.date), 1, f);
		}
		else
		{
			fwrite(serial->title, strlen(serial->title), 1, f);
			fwrite(&(serial->episodes), sizeof(int), 1, f);
			fwrite(&(serial->info.seasons), sizeof(int),1 , f);
			fwrite(&s, 1, 1, f);
		}
		serial = serial->adress;
	} while (serial);
	fclose(f);
	system("CLS");
	printf("Successfully written to the file!!!\n");
}
void read(struct Series** serial)
{
	printf("Choose type of file:\n1)Text file(.txt)\n2)Binary file(.bin)\n3)Exit\n");
	int choice;
	while (!scanf_s("%d", &choice) || (choice < 1) || (choice > 3))
	{
		printf("Incorrect value. Try again.\n");
		rewind(stdin);
	}
	switch (choice)
	{
	case 1:
		readTextFile(serial);
		break;
	case 2:
		readBinFile(serial);
		break;
	case 3: break;
	}
}
void readTextFile(struct Series** serial)
{
	system("CLS");
	FILE* f = fopen("Series.txt", "r");
	struct Series* temp = *serial;
	char c; int flg=0;
	do
	{
		if (feof(f)) break;
		if (!(*serial = (struct Series*)calloc(1, sizeof(struct Series))))
		{
			printf("Not enough memory!\n");
			return;
		}
		fgets((*serial)->title, 20, f);
		fscanf(f, "%d", &(*serial)->episodes);
		fpos_t check;
		fgetpos(f, &check);
		fseek(f, 2, SEEK_CUR);
		if (fgetc(f) == '-') (*serial)->isType = 1;
		else (*serial)->isType = 2;
		if ((*serial)->isType == 1)
		{
			fseek(f, 2, SEEK_CUR);
			fgets((*serial)->info.date, 10, f);
			flg = 1;
		}
		else
		{
			fsetpos(f, &check);
			fscanf(f, "%d", &(*serial)->info.seasons);
			flg = 0;
			c = fgetc(f); c = fgetc(f); c = fgetc(f);
		}
		deleteEnter(*serial);
		rightRegister(*serial);
		(*serial)->adress = temp;
		temp = *serial;
	} while (1);
	 if(flg==0)		*serial = (*serial)->adress;
	fclose(f);
	printf("Info from file is successfully read!\n");
}
void readBinFile(struct Series** serial)
{
	system("CLS");
	FILE* f = fopen("Series.bin", "rb");
	struct Series* temp = *serial;
	int flg = 0;
	do
	{
		fpos_t check, check1;
		if (feof(f)) break;
		if (!(*serial = (struct Series*)calloc(1, sizeof(struct Series))))
		{
			printf("Not enough memory!\n");
			return;
		}
		fgetpos(f, &check1);
		fgets((*serial)->title, 20, f);
		fsetpos(f, &check1);
		fseek(f, strlen((*serial)->title)-1, SEEK_CUR);
		fgetpos(f, &check);
		fread(&(*serial)->episodes, sizeof(int), 1, f);
		fgetpos(f, &check);
		char c;
		if (c = fgetc(f) == '-') (*serial)->isType = 1;
		else (*serial)->isType = 2;
		if ((*serial)->isType == 1)
		{
			fgets((*serial)->info.date, 9, f);
			flg = 1;
			//fseek(f, -1, SEEK_CUR);
		}
		else
		{
			fsetpos(f, &check);
			fread(&(*serial)->info.seasons, sizeof(int), 1, f);
			fgetc(f); //fgetc(f); //fgetc(f);
			//fseek(f, 1, SEEK_CUR);
			flg = 0;
		}
		deleteEnter(*serial);
		rightRegister(*serial);
		(*serial)->adress = temp;
		temp = *serial;
	} while (1);
	if (flg == 0)		*serial = (*serial)->adress;
	fclose(f);
	printf("Info from file is successfully read!\n");
}