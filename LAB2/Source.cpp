#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"
#include <windows.h>
union Info
{
	char date[9];
	int seasons;
};
struct Series
{
	char title[20];
	int episodes;
	Info info;
	int isType;
	int size;
};
int check(int numberOfSeries)
{
	if (numberOfSeries == 0)
	{
		printf("Ooops...No notes found.\n");
		return -1;
	}
	else return 1;
}
int menu()
{
	int choice;
	printf("Choose an operation:\n");
	printf("1) Add series\n2) Show series\n3) Delete series\n4) Search series\n5) Sort series\n6) Change series\n7) Search series by part of option\n8) Exit\n");
	while (!scanf_s("%d", &choice))
	{
		printf("Incorrect value! Try again...\n");
		rewind(stdin);
	}
	system("CLS");
	return choice;
}
struct Series* add(struct Series* serial, int numberOfSeries)
{
	system("CLS");
	printf("Enter number of series you want to add: ");
	int numberToAdd = 0;
	while (!scanf_s("%d", &numberToAdd) || (numberToAdd < 1))
	{
		rewind(stdin);
		system("CLS");
		printf("Incorrect value! try again...\n");
	}
	int startToAdd = numberOfSeries;
	numberOfSeries += numberToAdd;
	if(startToAdd!=0)	serial = (Series*)realloc(serial, numberOfSeries * sizeof(Series));
	else serial = (Series*)calloc(numberOfSeries, sizeof(Series));
	system("CLS");
	for (int i = 0; i < numberOfSeries; i++)
	{
		serial[i].size = numberOfSeries;
	}
	for (int i = startToAdd; i < numberOfSeries; i++)
	{
		printf("Series number: %d\n", i + 1);
		printf("Enter series title: "); 
		rewind(stdin);
		fgets(serial[i].title, 20, stdin);
		rewind(stdin);
		deleteEnter(serial, numberOfSeries, i, 1);
		rightRegister(serial, numberOfSeries, i);
		printf("Enter number of episodes: ");
		while (!scanf_s("%d", &serial[i].episodes) || (serial[i].episodes < 1))
		{
			rewind(stdin);
			system("CLS");
			printf("Incorrect value! try again...\n");
		}
		printf("Enter '1' to enter releae date or '2' to enter number of seasons: ");
		while (!scanf_s("%d", &serial[i].isType) || (serial[i].isType < 1) || (serial[i].isType > 2))
		{
			rewind(stdin);
			system("CLS");
			printf("Incorrect value! try again...\n");
		}
		if (serial[i].isType == 1)
		{
			printf("Enter release date(YYYYMMDD): ");
			rewind(stdin);
			fgets(serial[i].info.date, 9, stdin);
			rewind(stdin);
			deleteEnter(serial, numberOfSeries, i, 2);
		}
		else
		{
			printf("Enter number of seasons: ");
			while (!scanf_s("%d", &serial[i].info.seasons) || (serial[i].info.seasons < 1))
			{
				rewind(stdin);
				system("CLS");
				printf("Incorrect value! try again...\n");
			}
		}
		system("CLS");
	}
	return serial;
}
void show(struct Series* serial, int numberOfSeries)
{
	if (check(numberOfSeries) == -1) return;
	int choice;
	system("CLS");
	printf("1)Show all notes\n2)Show 1 note\n3)Exit\n");
	while (!scanf_s("%d", &choice) || (choice < 1) || (choice > 3))
	{
		printf("Incorrect value. Try again.\n");
		rewind(stdin);
	}
	printf("\n");
	switch (choice)
	{
	case 1:
		system("CLS");
		print(serial, numberOfSeries, -1);
		break;
	case 2:
		printf("Enter number of series you want to see: ");
		while (!scanf_s("%d", &choice) || (choice < 1) || (choice > numberOfSeries))
		{
			printf("Incorrect value. Try again.\n");
			rewind(stdin);
		}
		choice--;
		system("CLS");
		print(serial, numberOfSeries, choice);
		break;
	case 3:
		return;
		break;
	}
}
void print(struct Series* serial, int numberOfSeries, int serialToPrint)
{
	char table[] = "S E R I E S";
	printLine();
	printf("|\t\t\t\t\t %-43s|\n", table);
	printLine();
	printf("|\t%-5s|\t%-19s|\t%-5s|\t%-5s|\t%-8s|\n", "Note", "Title", "Episodes", "Seasons", "Release Date");
	printLine();
	if (serialToPrint != -1)
	{
		if (serial[serialToPrint].isType == 1)
		{
			printf("|\t%-5d|\t%-19s|\t%-8d|\t%-7s|\t%-12s|\n",
				serialToPrint + 1, (serial + serialToPrint)->title,
				serial[serialToPrint].episodes, "-",
				(serial + serialToPrint)->info.date);
			printLine();
		}
		else
		{
			printf("|\t%-5d|\t%-19s|\t%-8d|\t%-7d|\t%-12s|\n",
				serialToPrint + 1, (serial + serialToPrint)->title,
				serial[serialToPrint].episodes, serial[serialToPrint].info.seasons,
				"-");
			printLine();
		}
	}
	else
	{
		for (int i = 0; i < numberOfSeries; i++)
		{
			if (serial[i].isType == 1)
			{
				printf("|\t%-5d|\t%-19s|\t%-8d|\t%-7s|\t%-12s|\n",
					i + 1, (serial + i)->title,
					serial[i].episodes, "-",
					(serial + i)->info.date);
				printLine();
			}
			else
			{
				printf("|\t%-5d|\t%-19s|\t%-8d|\t%-7d|\t%-12s|\n",
					i + 1, (serial + i)->title,
					serial[i].episodes, serial[i].info.seasons,
					"-");
				printLine();
			}
		}
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
int size(struct Series* serial, int numberOfSeries)
{
	numberOfSeries = serial[0].size;
	return numberOfSeries;
}
void deleteEnter(struct Series* serial, int numberOfSeries, int numberOfStructure, int choice)
{
	if (choice == 1)
	{
		for (int i = 0; i < 20; i++)
		{
			if (serial[numberOfStructure].title[i] == '\n')
				for (i; i < 20; i++)
					serial[numberOfStructure].title[i] = serial[numberOfStructure].title[i + 1];
		}
	}
	else
	{
		for (int i = 0; i < 8; i++)
		{
			if (serial[numberOfStructure].info.date[i] == '\n')
				for (i; i < 8; i++)
					serial[numberOfStructure].info.date[i] = serial[numberOfStructure].info.date[i + 1];
		}
	}
}
void search(struct Series* serial, int numberOfSeries)
{
	if (check(numberOfSeries) == -1) return;
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
		for (int i = 0; i < 20; i++)
		{
			if (str[i] == '\n')		str[i] ='\0';
		}
		for (int i = 0; i < numberOfSeries; ++i)
		{
			int temp = 0;
			if (strlen(serial[i].title) == strlen(str))
			{
				for (int j = 0; j < strlen(str); j++)
				{
					if (serial[i].title[j] != str[j])
						break;
					else
						temp++;
					if (temp == strlen(str))
						print(serial, numberOfSeries, i);
					flag = 1;
				}
			}
		}
		break;
	case 2:
		printf("Enter number of episodes: ");
		while (!scanf_s("%d", &intToSearch) || (intToSearch < 1))
		{
			printf("Incorrect value\n");
			rewind(stdin);
		}
		for (int i = 0; i < numberOfSeries; i++)
		{
			if (serial[i].episodes == intToSearch)
			{
				print(serial, numberOfSeries, i);
				flag = 1;
				break;
			}
		}
		break;
	case 3:
		printf("Enter date of release(YYYYMMDD): ");
		rewind(stdin);
		fgets(str, 9, stdin);
		rewind(stdin);
		for (int i = 0; i < 9; i++)
		{
			if (str[i] == '\n')		str[i] = '\0';
		}
		for (int i = 0; i < numberOfSeries; ++i)
		{
			if (serial[i].isType != 1) continue;
			int temp = 0;
			if (strlen(serial[i].info.date) == strlen(str))
			{
				for (int j = 0; j < strlen(str); j++)
				{
					if (serial[i].info.date[j] != str[j])
						break;
					else
						temp++;
					if (temp == strlen(str))
						print(serial, numberOfSeries, i);
					flag = 1;
				}
			}
		}
		break;
	case 4:
		printf("Enter number of seasons: ");
		while (!scanf_s("%d", &intToSearch) || (intToSearch < 1))
		{
			printf("Incorrect value\n");
			rewind(stdin);
		}
		for (int i = 0; i < numberOfSeries; i++)
		{
			if (serial[i].isType != 2) continue;
			if (serial[i].info.seasons == intToSearch)
			{
				print(serial, numberOfSeries, i);
				flag = 1;
				break;
			}
		}
		break;
	case 5:
		system("CLS");
		return;
		break;
	}
	if (flag == 0) printf("Nothing found...Try again.\n");
}
struct Series* del(struct Series* serial, int numberOfSeries)
{
	if (check(numberOfSeries) == -1) return serial;
	int choice = 0;
	system("CLS");
	printf("1)Delete all notes\n2)Delete 1 note\n3)Delete by option\n4)Exit\n");
	while (!scanf_s("%d", &choice) || (choice < 1) || (choice > 3))
	{
		printf("Incorrect value. Try again.\n");
		rewind(stdin);
	}
	printf("\n");
	switch (choice)
	{
	case 1:
		system("CLS");
		printf("All notes were successfully deleted!\n");
		numberOfSeries = 1;
		serial = (Series*)realloc(serial, numberOfSeries * sizeof(Series));
		serial[0].size = 0;
		break;
	case 2:
		printf("Enter number of note you want to delete: ");
		while (!scanf_s("%d", &choice) || (choice < 1) || (choice > numberOfSeries))
		{
			printf("Incorrect value. Try again.\n");
			rewind(stdin);
		}
		choice--;
		serial=delExact(serial, numberOfSeries, choice);
		return serial;
		break;
	case 3:
		serial=deleteByTheOption(serial, numberOfSeries);
		return serial;
		break;
	case 4:
		return serial;
		break;
	}
	return serial;
}
struct Series* delExact(struct Series* serial, int numberOfSeries, int serialNumber)
{
	for (int i = serialNumber; i < numberOfSeries; i++)
	{
		serial[i] = serial[i + 1];
	}
	numberOfSeries--;
	for (int i = 0; i < numberOfSeries; i++)
	{
		serial[i].size = numberOfSeries;
	}
	serial = (Series*)realloc(serial, numberOfSeries * sizeof(Series));
	system("CLS");
	printf("Note was successfully deleted!\n");
	return serial;
}
struct Series* deleteByTheOption(struct Series* serial, int numberOfSeries)
{
	if (check(numberOfSeries) == -1) return serial;
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
		for (int i = 0; i < 20; i++)
		{
			if (str[i] == '\n')		str[i] = '\0';
		}
		for (int i = 0; i < numberOfSeries; ++i)
		{
			int temp = 0;
			if (strlen(serial[i].title) == strlen(str))
			{
				for (int j = 0; j < strlen(str); j++)
				{
					if (serial[i].title[j] != str[j])
						break;
					else
						temp++;
					if (temp == strlen(str))
					{
						serial = delExact(serial, numberOfSeries, i);
						numberOfSeries--;
						for (int i = 0; i < numberOfSeries; i++)
						{
							serial[i].size = numberOfSeries;
						}
						serial = (Series*)realloc(serial, numberOfSeries * sizeof(Series));
					}
					flag = 1;
				}
			}
		}
		break;
	case 2:
		printf("Enter number of episodes: ");
		while (!scanf_s("%d", &intToSearch) || (intToSearch < 1))
		{
			printf("Incorrect value\n");
			rewind(stdin);
		}
		for (int i = 0; i < numberOfSeries; i++)
		{
			if (serial[i].episodes == intToSearch)
			{
				serial = delExact(serial, numberOfSeries, i);
				numberOfSeries--;
				for (int i = 0; i < numberOfSeries; i++)
				{
					serial[i].size = numberOfSeries;
				}
				serial = (Series*)realloc(serial, numberOfSeries * sizeof(Series));
				flag = 1;
				break;
			}
		}
		break;
	case 3:
		printf("Enter date of release(YYYYMMDD): ");
		rewind(stdin);
		fgets(str, 9, stdin);
		rewind(stdin);
		for (int i = 0; i < 9; i++)
		{
			if (str[i] == '\n')		str[i] = '\0';
		}
		for (int i = 0; i < numberOfSeries; ++i)
		{
			if (serial[i].isType != 1) continue;
			int temp = 0;
			if (strlen(serial[i].info.date) == strlen(str))
			{
				for (int j = 0; j < strlen(str); j++)
				{
					if (serial[i].info.date[j] != str[j])
						break;
					else
						temp++;
					if (temp == strlen(str))
					{
						serial = delExact(serial, numberOfSeries, i);
						numberOfSeries--;
						for (int i = 0; i < numberOfSeries; i++)
						{
							serial[i].size = numberOfSeries;
						}
						serial = (Series*)realloc(serial, numberOfSeries * sizeof(Series));
					}
					flag = 1;
				}
			}
		}
		break;
	case 4:
		printf("Enter number of seasons: ");
		while (!scanf_s("%d", &intToSearch) || (intToSearch < 1))
		{
			printf("Incorrect value\n");
			rewind(stdin);
		}
		for (int i = 0; i < numberOfSeries; i++)
		{
			if (serial[i].isType != 2) continue;
			if (serial[i].info.seasons == intToSearch)
			{
				serial = delExact(serial, numberOfSeries, i);
				numberOfSeries--;
				for (int i = 0; i < numberOfSeries; i++)
				{
					serial[i].size = numberOfSeries;
				}
				serial = (Series*)realloc(serial, numberOfSeries * sizeof(Series));
				flag = 1;
				break;
			}
		}
		break;
	case 5:
		system("CLS");
		return serial;
		break;
	}
	if (flag == 0) printf("Nothing found...Try again.\n");
	return serial;
}
void sort(struct Series* serial, int numberOfSeries)
{
	if (check(numberOfSeries) == -1) return;
	system("CLS");
	printf("How to sort:\n");
	printf("1)From Min to Max\n");
	printf("2)From Max to Min\n");
	printf("3)Exit\n");
	int choice;
	while (!scanf_s("%d", &choice) || (choice < 1) || (choice > 3))
	{
		printf("Incorrect value. Try again.\n");
		rewind(stdin);
	}
	printf("\n");
	switch (choice)
	{
	case 1:
		system("CLS");
		sortFromMin(serial, numberOfSeries);
		return;
		break;
	case 2:
		system("CLS");
		sortFromMax(serial, numberOfSeries);
		return;
		break;
	case 3:
		system("CLS");
		return;
		break;
	}
}
void sortFromMin(struct Series* serial, int numberOfSeries)
{
	struct Series temp;
	int choice;
	system("CLS");
	print(serial, numberOfSeries, -1);
	printf("1)Title\n");
	printf("2)Number of episodes\n");
	printf("3)Date of release\n");
	printf("4)Number of seasons\n");
	printf("5)Exit\n");
	while (!scanf_s("%d", &choice) || (choice < 1) || (choice > 5))
	{
		printf("Incorrect value. Try again.\n");
		rewind(stdin);
	}
	switch (choice)
	{
	case 1:
		for (int i = 0; i < numberOfSeries; i++)
		{
			for (int j = 0; j < numberOfSeries - 1; j++)
			{
				if (strcmp(serial[j].title, serial[j+1].title) > 0)
				{
					temp = serial[j];
					serial[j] = serial[j + 1];
					serial[j + 1] = temp;
					break;
				}
			}
		}
		break;
	case 2:
		for (int i = 0; i < numberOfSeries; i++)
		{
			for (int j = 0; j < numberOfSeries - 1; j++)
			{
				if (serial[j].episodes > serial[j + 1].episodes)
				{
					temp = serial[j];
					serial[j] = serial[j + 1];
					serial[j + 1] = temp;
				}
			}
		}
		break;
	case 3:
		for (int i = 0; i < numberOfSeries; i++)
		{
			for (int j = 0; j < numberOfSeries - 1; j++)
			{
				if (serial[j].isType != 1) continue;
				if (strcmp(serial[j].info.date, serial[j + 1].info.date) > 0)
				{
					temp = serial[j];
					serial[j] = serial[j + 1];
					serial[j + 1] = temp;
					break;
				}
			}
		}
	case 4:
		for (int i = 0; i < numberOfSeries; i++)
		{
			for (int j = 0; j < numberOfSeries - 1; j++)
			{
				if (serial[j].isType == 1) continue;
				if (serial[j].info.seasons > serial[j + 1].info.seasons)
				{
					temp = serial[j];
					serial[j] = serial[j + 1];
					serial[j + 1] = temp;
				}
			}
		}
		break;
	case 5:
		system("CLS");
		print(serial, numberOfSeries, -1);
		return;
	}
	system("CLS");
}
void sortFromMax(struct Series* serial, int numberOfSeries)
{
	struct Series temp;
	int choice;
	system("CLS");
	print(serial, numberOfSeries, -1);
	printf("1)Title\n");
	printf("2)Number of episodes\n");
	printf("3)Date of release\n");
	printf("4)Number of seasons\n");
	printf("5)Exit\n");
	while (!scanf_s("%d", &choice) || (choice < 1) || (choice > 5))
	{
		printf("Incorrect value. Try again.\n");
		rewind(stdin);
	}
	switch (choice)
	{
	case 1:
		for (int i = 0; i < numberOfSeries; i++)
		{
			for (int j = 0; j < numberOfSeries - 1; j++)
			{
				if (strcmp(serial[j].title, serial[j + 1].title) < 0)
				{
					temp = serial[j];
					serial[j] = serial[j + 1];
					serial[j + 1] = temp;
					break;
				}
			}
		}
		break;
	case 2:
		for (int i = 0; i < numberOfSeries; i++)
		{
			for (int j = 0; j < numberOfSeries - 1; j++)
			{
				if (serial[j].episodes < serial[j + 1].episodes)
				{
					temp = serial[j];
					serial[j] = serial[j + 1];
					serial[j + 1] = temp;
				}
			}
		}
		break;
	case 3:
		for (int i = 0; i < numberOfSeries; i++)
		{
			for (int j = 0; j < numberOfSeries - 1; j++)
			{
				if (serial[j].isType != 1) continue;
				if (strcmp(serial[j].info.date, serial[j + 1].info.date) < 0)
				{
					temp = serial[j];
					serial[j] = serial[j + 1];
					serial[j + 1] = temp;
					break;
				}
			}
		}
	case 4:
		for (int i = 0; i < numberOfSeries; i++)
		{
			for (int j = 0; j < numberOfSeries - 1; j++)
			{
				if (serial[j].isType == 1) continue;
				if (serial[j].info.seasons < serial[j + 1].info.seasons)
				{
					temp = serial[j];
					serial[j] = serial[j + 1];
					serial[j + 1] = temp;
				}
			}
		}
		break;
	case 5:
		system("CLS");
		print(serial, numberOfSeries, -1);
		return;
	}
	system("CLS");
}
struct Series* change(struct Series* serial, int numberOfSeries)
{
	int numberToChange = 0, choice;
	if (check(numberOfSeries) == -1) return serial;
	system("CLS");
	print(serial, numberOfSeries, -1);
	printf("Enter number of note you want to change: ");
	while (!scanf_s("%d", &numberToChange) || (numberToChange < 1) || (numberToChange > numberOfSeries))
	{
		printf("Incorrect value. Try again.\n");
		rewind(stdin);
	}
	numberToChange--;
	int exit = 0;
	do
	{
		printf("1)Change title\n");
		printf("2)Change number of episodes\n");
		printf("3)Change date\n");
		printf("4)Change number of seasons\n");
		printf("5)Exit\n");
		while (!scanf_s("%d", &choice) || (choice < 1) || (choice > 5))
		{
			printf("Incorrect value. Try again.\n");
			rewind(stdin);
		}
		switch (choice)
		{
		case 1:
			printf("Enter new title: ");
			rewind(stdin);
			fgets(serial[numberToChange].title, 20, stdin);
			rewind(stdin);
			deleteEnter(serial, numberOfSeries, numberToChange, 1);
			rightRegister(serial, numberOfSeries, numberToChange);
			break;
		case 2:
			printf("Enter new number of episodes: ");
			while (!scanf_s("%d", &serial[numberToChange].episodes) || (serial[numberToChange].episodes < 1))
			{
				printf("Incorrect value. Try again.\n");
				rewind(stdin);
			}
			break;
		case 3:
			serial[numberToChange].isType = 1;
			printf("Enter new date: ");
			rewind(stdin);
			fgets(serial[numberToChange].info.date, 9, stdin);
			rewind(stdin);
			deleteEnter(serial, numberOfSeries, numberToChange, 2);
			break;
		case 4:
			serial[numberToChange].isType = 2;
			printf("Enter new number of seasons: ");
			while (!scanf_s("%d", &serial[numberToChange].info.seasons) || (serial[numberToChange].info.seasons < 1))
			{
				printf("Incorrect value. Try again.\n");
				rewind(stdin);
			}
			break;
		case 5:
			exit = 1;
			break;
		}
	} while (exit != 1);
	system("CLS");
	return serial;
}
void partSearch(struct Series* serial, int numberOfSeries)
{
	if (check(numberOfSeries) == -1) return;
	system("CLS");
	printf("Select option to search:\n");
	printf("1)Title\n");
	printf("2)Number of episodes\n");
	printf("3)Date of release\n");
	printf("4)Number of seasons\n");
	printf("5)Exit\n");
	int choice;
	while (!scanf_s("%d", &choice) || (choice < 1) || (choice > 5))
	{
		printf("Incorrect value. Try again.\n");
		rewind(stdin);
	}
	printf("\n");
	switch (choice)
	{
	case 1:
		system("CLS");
		printf("Enter symbols of title (*a*b*): ");
		findCharNumber(serial, numberOfSeries, 1);
		break;
	case 2:
		system("CLS");
		printf("Enter symbols of numer of episodes (*a*b*): ");
		findCharNumber(serial, numberOfSeries, 2);
		break;
	case 3:
		system("CLS");
		printf("Enter symbols of date (*a*b*): ");
		findCharNumber(serial, numberOfSeries, 3);
		break;
	case 4:
		system("CLS");
		printf("Enter symbols of number of seasons (*a*b*): ");
		findCharNumber(serial, numberOfSeries, 4);
		break;
	case 5:
		system("CLS");
		return;
		break;
	}
}
void findCharNumber(struct Series* serial, int numberOfSeries, int choice)
{
	char str[20], str2[20];
	char compareChar;
	int flag = 0, flag1 = 0;
	rewind(stdin);
	fgets(str, 20, stdin);
	rewind(stdin);
	for (int l = 0; l < numberOfSeries; l++)
	{
		switch (choice)
		{
		case 1:
			for (int i = 0; i < 20; i++)
				str2[i] = serial[l].title[i];
			break;
		case 2:
			sprintf_s(str2, "%d", serial[l].episodes);
			break;
		case 3:
			if (serial[l].isType != 1) continue;
			for (int i = 0; i < 20; i++)
				str2[i] = serial[l].info.date[i];
			break;
		case 4:
			if (serial[l].isType == 1) continue;
			sprintf_s(str2, "%d", serial[l].info.seasons);
			break;
		}
		int j = 0, i = 0, j1 = 0;
		for (i; i < strlen(str); i++)
		{
			while ((str[i] != '*') && (str[i] != '\n') && (str[i] != '\0'))
			{
				compareChar = str[i];
				flag1++;
				for (j = j1; j < strlen(str2); j++)
				{
					if (str2[j] == compareChar)
					{
						flag++;
						j1 = j;
						j = strlen(str2);
					}
				}
				break;
			}
		}
		if ((flag == flag1) && (flag1 != 0))	print(serial, numberOfSeries, l);
		flag = 0;
		flag1 = 0;
	}
}
void rightRegister(struct Series* serial, int numberOfSeries, int numberOfStructure)
{
	if ((serial[numberOfStructure].title[0] >= 'a') && (serial[numberOfStructure].title[0] <= 'z'))
		serial[numberOfStructure].title[0] -= 32;
	for (int i = 1; i < 20; i++)
	{
		if ((serial[numberOfStructure].title[i] >= 'A') && (serial[numberOfStructure].title[i] <= 'Z'))
			serial[numberOfStructure].title[i] += 32;
	}
	for (int i = 1; i < 20; i++)
	{
		if ((serial[numberOfStructure].title[i] >= 'a') && (serial[numberOfStructure].title[i] <= 'z') &&
			(((serial[numberOfStructure].title[i - 1]) == '-') || ((serial[numberOfStructure].title[i - 1]) == ' ')))
			serial[numberOfStructure].title[i] -= 32;
	}
}