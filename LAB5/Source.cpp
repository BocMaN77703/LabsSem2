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
	struct Series* next;
};
int menu()
{
	int choice;
	printf("Choose an operation:\n");
	printf("1) Add series\n2) Show series\n3) Delete series\n4) Search series\n5) Write to the file\n6) Read from file\n7) Exit\n");
	while (!scanf_s("%d", &choice) || choice < 1 || choice>7)
	{
		printf("Incorrect value! Try again...\n");
		rewind(stdin);
	}
	system("CLS");
	return choice;
}
void add(struct Series** head, struct Series** tail)
{
	system("CLS");
	struct Series* temp;
	do
	{
		if (!(temp = (struct Series*)calloc(1, sizeof(struct Series))))
		{
			puts("Not enough memory!\n");
			return;
		}
		printf("Enter series title: ");
		rewind(stdin);
		fgets(temp->title, 20, stdin);
		rewind(stdin);
		printf("Enter number of episodes: ");
		while (!scanf_s("%d", &temp->episodes) || (temp->episodes < 1))
		{
			rewind(stdin);
			system("CLS");
			printf("Incorrect value! try again...\n");
		}
		printf("Enter '1' to enter release date or '2' to enter number of seasons: ");
		while (!scanf_s("%d", &temp->isType) || (temp->isType < 1) || (temp->isType > 2))
		{
			rewind(stdin);
			system("CLS");
			printf("Incorrect value! try again...\n");
		}
		if (temp->isType == 1)
		{
			printf("Enter release date(YYYYMMDD): ");
			rewind(stdin);
			fgets(temp->info.date, 10, stdin);
			rewind(stdin);
		}
		else
		{
			printf("Enter number of seasons: ");
			while (!scanf_s("%d", &temp->info.seasons) || (temp->info.seasons < 1))
			{
				rewind(stdin);
				system("CLS");
				printf("Incorrect value! try again...\n");
			}

		}
		deleteEnter(temp);
		rightRegister(temp);
		if (!*head)		*tail = *head = temp;       							
		else
		{
			(*tail)->next = temp;      
			*tail = temp;               
		}
	system("CLS");
		printf("Do you want to enter more series??? (y/n): ");
		rewind(stdin);
	} while (getchar() == 'y');
	system("CLS");
}
void print(struct Series* head, int flag)
{
	if (!head)
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
		if (head->isType == 1)
		{
			printf("|\t%-5d|\t%-19s|\t%-8d|\t%-7s|\t%-12s|\n",
				i, head->title,
				head->episodes, "-",
				head->info.date);
			printLine();
		}
		else
		{
			printf("|\t%-5d|\t%-19s|\t%-8d|\t%-7d|\t%-12s|\n",
				i, head->title,
				head->episodes, head->info.seasons,
				"-");
			printLine();
		}
		head = head->next;
		i++;
	}
	else
	{
		do
		{
			if (head->isType == 1)
			{
				printf("|\t%-5d|\t%-19s|\t%-8d|\t%-7s|\t%-12s|\n",
					i, head->title,
					head->episodes, "-",
					head->info.date);
				printLine();
			}
			else
			{
				printf("|\t%-5d|\t%-19s|\t%-8d|\t%-7d|\t%-12s|\n",
					i, head->title,
					head->episodes, head->info.seasons,
					"-");
				printLine();
			}
			head = head->next;
			i++;
		} while (head);
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
	serial = serial->next;
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
void del(struct Series** head, struct Series** tail)
{
	if (!head)
	{
		printf("Stack is empty...\n");
		return;
	}
	int choice = 0;
	system("CLS");
	print(*head, 0);
	printf("Enter number of note you want to delete (0-Exit): ");
	while (!scanf_s("%d", &choice) || (choice < 0))
	{
		printf("Incorrect value. Try again.\n");
		rewind(stdin);
	}
	if (choice == 0) return;
	choice--;
	if (*head == *tail)
	{
		free(*tail);
		*head = *tail = NULL;
		system("CLS");
		return;
	}
	struct Series* temp, * temp2, * temp3;
	if (choice != 0)
	{
		temp3 = *head;
		for (int i = 0; i < choice - 1; i++)  *head = (*head)->next;
		temp = *head;
		*head = (*head)->next;
		temp2 = *head;
		temp->next = temp2->next;
		*head = temp3;
	}
	else
	{
		temp2 = *head;
		*head = (*head)->next;
	}
	free(temp2);
	temp = *head;
	while(temp->next) temp = temp->next;
	*tail = temp;
	system("CLS");
}
void search(struct Series* head)
{
	if (!head)
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
			if (strlen(head->title) == strlen(str))
			{
				for (int j = 0; j < strlen(str); j++)
				{
					if (head->title[j] != str[j])
						break;
					else
						temp++;
					if (temp == strlen(str))
						print(head, 1);
					flag = 1;
				}
			}
			head = head->next;
		} while (head);
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
			if (head->episodes == intToSearch)
			{
				print(head, 1);
				flag = 1;
				break;
			}
			head = head->next;
		} while (head);
		break;
	case 3:
		printf("Enter date of release(YYYYMMDD): ");
		rewind(stdin);
		fgets(str, 10, stdin);
		rewind(stdin);
		str[strlen(str) - 1] = '\0';
		do
		{
			if (head->isType != 1)
			{
				head = head->next;
				continue;
			}
			int temp = 0;
			if (strlen(head->info.date) == strlen(str))
			{
				for (int j = 0; j < strlen(str); j++)
				{
					if (head->info.date[j] != str[j])
						break;
					else
						temp++;
					if (temp == strlen(str))
						print(head, 1);
					flag = 1;
				}
			}
			head = head->next;
		} while (head);
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
			if (head->isType != 2)
			{
				head = head->next;
				continue;
			}
			if (head->info.seasons == intToSearch)
			{
				print(head, 1);
				flag = 1;
				break;
			}
			head = head->next;
		} while (head);
		break;
	case 5:
		system("CLS");
		return;
		break;
	}
	if (flag == 0) printf("Nothing found...Try again.\n");
}
void clear(struct Series** head, struct Series** tail)
{
	while (*head != NULL)
	{
		struct Series* temp;
		temp = *head;
		*head = (*head)->next;
		free(temp);
	}
	*tail = *head;
}
void write(struct Series* head)
{
	if (!head)
	{
		printf("Stack is empty...\n");
		return;
	}
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
		writeTextFile(head);
		printf("Successfully written to the file!!!\n");
		break;
	case 2:
		writeBinFile(head);
		break;
	case 3: break;
	}
}
void writeTextFile(struct Series* head)
{
	FILE* f = fopen("Series.txt", "w");
	do
	{
		if (head->isType == 1)
		{
			fprintf(f, "%d %d %s %s\n", head->isType, head->episodes, head->info.date, head->title);
		}
		else
		{
			fprintf(f, "%d %d %d %s\n", head->isType, head->episodes, head->info.seasons, head->title);
		}
		head = head->next;
	} while (head);
	fclose(f);
	system("CLS");
}
void writeBinFile(struct Series* head)
{
	FILE* f = fopen("Series.bin", "wb");
	do
	{
		if (head->isType == 1)
		{
			fwrite(head->title, 20, 1, f);
			fwrite(&(head->isType), sizeof(int), 1, f);
			fwrite(&(head->episodes), sizeof(int), 1, f);
			fwrite(head->info.date, strlen(head->info.date), 1, f);
		}
		else
		{
			fwrite(head->title, 20, 1, f);
			fwrite(&(head->isType), sizeof(int), 1, f);
			fwrite(&(head->episodes), sizeof(int), 1, f);
			fwrite(&(head->info.seasons), sizeof(int), 1, f);
		}
		head = head->next;
	} while (head);
	fclose(f);
	system("CLS");
	printf("Successfully written to the file!!!\n");
}
void read(struct Series** head, struct Series** tail)
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
		readTextFile(head, tail);
		break;
	case 2:
		readBinFile(head, tail);
		break;
	case 3: break;
	}
}
void readTextFile(struct Series** head, struct Series** tail)
{
	system("CLS");
	FILE* f = fopen("Series.txt", "r");
	struct Series* temp;
	do
	{
		if (feof(f)) break;
		if (!(temp = (struct Series*)calloc(1, sizeof(struct Series))))
		{
			printf("Not enough memory!\n");
			return;
		}
		fscanf(f, "%d", &temp->isType);
		fseek(f, 1, SEEK_CUR);
		fscanf(f, "%d", &temp->episodes);
		fseek(f, 1, SEEK_CUR);
		if (temp->isType == 1)		fgets(temp->info.date, 10, f);
		else
		{
			fscanf(f, "%d", &temp->info.seasons);
			fseek(f, 1, SEEK_CUR);
		}
		fgets(temp->title, 20, f);
		deleteEnter(temp);
		rightRegister(temp);
		if (!*head)		*tail = *head = temp;
		else
		{
			(*tail)->next = temp;
			*tail = temp;
		}
		if (feof(f)) break;
	} while (1);
	temp = *head;
	while (*tail != temp->next)
		temp = temp->next;
	*tail = temp;
	(*tail)->next = NULL;
	fclose(f);
	printf("Info from file is successfully read!\n");
}
void readBinFile(struct Series** head, struct Series** tail)
{
	system("CLS");
	FILE* f = fopen("Series.bin", "rb");
	struct Series* temp;
	fpos_t end, pos;
	fseek(f, 0, SEEK_END);
	fgetpos(f, &end);
	rewind(f);
	do
	{
		if (!(temp = (struct Series*)calloc(1, sizeof(struct Series))))
		{
			printf("Not enough memory!\n");
			return;
		}
		fgets(temp->title, 20, f);
		fseek(f, 1, SEEK_CUR);
		fread(&temp->isType, sizeof(int), 1, f);
		fread(&temp->episodes, sizeof(int), 1, f);
		if (temp->isType == 1)
		{
			fgets(temp->info.date, 9, f);
		}
		else
		{
			fread(&temp->info.seasons, sizeof(int), 1, f);
		}
		fgetpos(f, &pos);
		rightRegister(temp);
		if (!*head)		*tail = *head = temp;
		else
		{
			(*tail)->next = temp;
			*tail = temp;
		}
		if (pos == end) break;
	} while (1);
	fclose(f);
	printf("Info from file is successfully read!\n");
}