#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
struct Flights
{
	int number;
	char destination[20];
	int time;
	int date;
	double price;
};
int menu(struct Flights* flight, int numberOfFlights)
{
	int choice;
	printf("Choose an operation (1-8):\n");
	printf("1) Add flight\n2) Show entered flights\n3) Change flight\n4) Search by the option\n5) Sort flights\n6) Delete flight\n7) Search by part of option\n8)Exit\n");
	while (!scanf_s("%d", &choice) || (choice < 1) || (choice > 8))
	{
		printf("Incorrect value\n");
		rewind(stdin);
	}
	switch (choice)
	{
	case 1:
		add(flight, numberOfFlights);
		break;
	case 2:
		show(flight, numberOfFlights);
		break;
	case 3:
		change(flight, numberOfFlights);
		break;
	case 4:
		search(flight, numberOfFlights);
		break;
	case 5:
		sort(flight, numberOfFlights);
		break;
	case 6:
		del(flight, numberOfFlights);
		break;
	case 7:
		partSearch(flight, numberOfFlights);
		break;
	case 8:
		break;
	}
	return choice;
}
void add(struct Flights* flight, int numberOfFlights)
{
	int numberToAdd = 0, startToAdd = 0;
	system("CLS");
	printf("Enter number of flights you want to add: ");
	if (numberOfFlights != 0)
	{
		startToAdd = numberOfFlights;
		while (!scanf_s("%d", &numberToAdd) || (numberToAdd < 1))
		{
			printf("Incorrect value. Try again...\n");
			rewind(stdin);
		}
		printf("\n");
		flight = (Flights*)realloc(flight, (numberToAdd + numberOfFlights) * sizeof(Flights));
	}
	else
	{
		while (!scanf_s("%d", &numberOfFlights) || (numberOfFlights < 1))
		{
			printf("Incorrect value. Try again...\n");
			rewind(stdin);
		}
		printf("\n");
		flight = (Flights*)calloc(numberOfFlights, sizeof(Flights));
	}
	numberOfFlights += numberToAdd;
	for (int i = startToAdd; i < numberOfFlights; i++)
	{
		printf("Note number: %d\n", i + 1);
		printf("Enter number of flight: ");
		while (!scanf_s("%d", &flight[i].number) || (flight[i].number < 1))
		{
			rewind(stdin);
			printf("Incorrect value\n");
		}
		printf("Enter destination: ");
		rewind(stdin);
		fgets(flight[i].destination, 20, stdin);
		deleteEnter(flight, numberOfFlights, i);
		rightRegister(flight, numberOfFlights, i);
		rewind(stdin);
		printf("Enter date:\n");
		int year = 0, month = 0, day = 0;
		printf("Enter year: ");
		while (!scanf_s("%d", &year) || (year < 2000) || (year > 2050))
		{
			rewind(stdin);
			printf("Incorrect value\n");
		}
		printf("Enter month: ");
		while (!scanf_s("%d", &month) || (month < 1) || (month > 12))
		{
			rewind(stdin);
			printf("Incorrect value\n");
		}
		printf("Enter day: ");
		while (!scanf_s("%d", &day) || (day < 1) || (day > 31))
		{
			rewind(stdin);
			printf("Incorrect value\n");
		}
		flight[i].date = year * 10000 + month * 100 + day;
		printf("Enter time:\n");
		int hour = 0, minute = 0, second = 0;
		printf("Enter hours: ");
		while (!scanf_s("%d", &hour) || (hour > 23) || (hour < 0))
		{
			rewind(stdin);
			printf("Incorrect value\n");
		}
		printf("Enter minutes: ");
		while (!scanf_s("%d", &minute) || (minute > 59) || (minute < 0))
		{
			rewind(stdin);
			printf("Incorrect value\n");
		}
		printf("Enter seconds: ");
		while (!scanf_s("%d", &second) || (second > 59) || (second < 0))
		{
			rewind(stdin);
			printf("Incorrect value\n");
		}
		flight[i].time = hour * 10000 + minute * 100 + second;
		printf("Enter price: ");
		while (!scanf_s("%lf", &flight[i].price) || (flight[i].price <= 0))
		{
			rewind(stdin);
			printf("Incorrect value\n");
		}
		printf("\n");
	}
	system("CLS");
	menu(flight, numberOfFlights);
}
void show(struct Flights* flight, int numberOfFlights)
{
	int choice = 0;
	if (check(flight, numberOfFlights) == -1)
	{
		menu(flight, numberOfFlights);
		return;
	}
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
		print(flight, numberOfFlights, -1);
		menu(flight, numberOfFlights);
		return;
		break;
	case 2:
		printf("Enter number of note you want to see: ");
		while (!scanf_s("%d", &choice) || (choice < 1) || (choice > numberOfFlights))
		{
			printf("Incorrect value. Try again.\n");
			rewind(stdin);
		}
		choice--;
		system("CLS");
		print(flight, numberOfFlights, choice);
		menu(flight, numberOfFlights);
		return;
		break;
	case 3:
		menu(flight, numberOfFlights);
		return;
		break;
	}
	menu(flight, numberOfFlights);
	return;
}
void change(struct Flights* flight, int numberOfFlights)
{
	int numberToChange = 0, choice;
	if (check(flight, numberOfFlights) == -1)
	{
		menu(flight, numberOfFlights);
		return;
	}
	system("CLS");
	print(flight, numberOfFlights, -1);
	printf("Enter number of note you want to change: ");
	while (!scanf_s("%d", &numberToChange) || (numberToChange < 1) || (numberToChange > numberOfFlights))
	{
		printf("Incorrect value. Try again.\n");
		rewind(stdin);
	}
	numberToChange--;
	int exit = 0;
	do
	{
		int year = 0, month = 0, day = 0;
		int hour = 0, minute = 0, second = 0;
		printf("1)Change number of flight\n");
		printf("2)Change destination\n");
		printf("3)Change date of flight\n");
		printf("4)Change time of flight\n");
		printf("5)Change price of flight\n");
		printf("6)Exit\n");
		while (!scanf_s("%d", &choice) || (choice < 1) || (choice > 6))
		{
			printf("Incorrect value. Try again.\n");
			rewind(stdin);
		}
		switch (choice)
		{
		case 1:
			printf("Enter new number of flight: ");
			while (!scanf_s("%d", &flight[numberToChange].number) || (flight[numberToChange].number < 1))
			{
				rewind(stdin);
				printf("Incorrect value\n");
			}
			break;
		case 2:
			printf("Enter new destination: ");
			rewind(stdin);
			fgets(flight[numberToChange].destination, 20, stdin);
			deleteEnter(flight, numberOfFlights, numberToChange);
			break;
		case 3:
			printf("Enter date:\n");
			printf("Enter year: ");
			while (!scanf_s("%d", &year) || (year < 2000) || (year > 2050))
			{
				rewind(stdin);
				printf("Incorrect value\n");
			}
			printf("Enter month: ");
			while (!scanf_s("%d", &month) || (month < 1) || (month > 12))
			{
				rewind(stdin);
				printf("Incorrect value\n");
			}
			printf("Enter day: ");
			while (!scanf_s("%d", &day) || (day < 1) || (day > 31))
			{
				rewind(stdin);
				printf("Incorrect value\n");
			}
			flight[numberToChange].date = year * 10000 + month * 100 + day;
			break;
		case 4:
			printf("Enter time:\n");
			printf("Enter hours: ");
			while (!scanf_s("%d", &hour) || (hour > 23) || (hour < 0))
			{
				rewind(stdin);
				printf("Incorrect value\n");
			}
			printf("Enter minutes: ");
			while (!scanf_s("%d", &minute) || (minute > 59) || (minute < 0))
			{
				rewind(stdin);
				printf("Incorrect value\n");
			}
			printf("Enter seconds: ");
			while (!scanf_s("%d", &second) || (second > 59) || (second < 0))
			{
				rewind(stdin);
				printf("Incorrect value\n");
			}
			flight[numberToChange].time = hour * 10000 + minute * 100 + second;
			break;
		case 5:
			printf("\nEnter price: ");
			while (!scanf_s("%lf", &flight[numberToChange].price) || (flight[numberToChange].price <= 0))
			{
				rewind(stdin);
				printf("Incorrect value\n");
			}
			break;
		case 6:
			exit = 1;
			break;
		}
	} while (exit != 1);
	system("CLS");
	menu(flight, numberOfFlights);
}
void del(struct Flights* flight, int numberOfFlights)
{
	int choice = 0;
	if (check(flight, numberOfFlights) == -1)
	{
		menu(flight, numberOfFlights);
		return;
	}
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
		free(flight);
		system("CLS");
		printf("All notes were successfully deleted!\n");
		numberOfFlights = 0;
		break;
	case 2:
		printf("Enter number of note you want to delete: ");
		while (!scanf_s("%d", &choice) || (choice < 1) || (choice > numberOfFlights))
		{
			printf("Incorrect value. Try again.\n");
			rewind(stdin);
		}
		choice--;
		delExact(flight, numberOfFlights, choice);
		break;
	case 3:
		deleteByTheOption(flight, numberOfFlights);
		return;
		break;
	case 4:
		menu(flight, numberOfFlights);
		return;
		break;
	}
	menu(flight, numberOfFlights);
}
void search(struct Flights* flight, int numberOfFlights)
{
	if (check(flight, numberOfFlights) == -1)
	{
		menu(flight, numberOfFlights);
		return;
	}
	system("CLS");
	printf("Select option to search:\n");
	printf("1)Number of flight\n");
	printf("2)Destination\n");
	printf("3)Date\n");
	printf("4)Time\n");
	printf("5)Price\n");
	printf("6)Exit\n");
	int choice, intToSearch = 0, flag = 0;
	double doubleToSearch;
	char str[20];
	while (!scanf_s("%d", &choice) || (choice < 1) || (choice > 6))
	{
		printf("Incorrect value\n");
		rewind(stdin);
	}
	switch (choice)
	{
	case 1:
		printf("Enter number of flight: ");
		while (!scanf_s("%d", &intToSearch) || (intToSearch < 1))
		{
			printf("Incorrect value\n");
			rewind(stdin);
		}
		for (int i = 0; i < numberOfFlights; i++)
		{
			while (flight[i].number == intToSearch)
			{
				print(flight, numberOfFlights, i);
				flag = 1;
				break;
			}
		}
		break;
	case 2:
		printf("Enter destination: ");
		rewind(stdin);
		fgets(str, 20, stdin);
		for (int i = 0; i < 20; i++)
		{
			if (str[i] == '\n')
				for (i; i < 20; i++)
					str[i] = str[i + 1];
		}
		for (int i = 0; i < numberOfFlights; ++i)
		{
			int temp = 0;
			if (strlen(flight[i].destination) == strlen(str))
			{
				for (int j = 0; j < strlen(str); j++)
				{
					if (flight[i].destination[j] != str[j])
						break;
					else
						temp++;
					if (temp == strlen(str))
						print(flight, numberOfFlights, i);
					flag = 1;
				}
			}
		}
		break;
	case 3:
		printf("Enter date of flight: ");
		while (!scanf_s("%d", &intToSearch) || (intToSearch < 1))
		{
			printf("Incorrect value\n");
			rewind(stdin);
		}
		for (int i = 0; i < numberOfFlights; i++)
		{
			while (flight[i].date == intToSearch)
			{
				print(flight, numberOfFlights, i);
				flag = 1;
				break;
			}
		}
		break;
	case 4:
		printf("Enter time of flight: ");
		while (!scanf_s("%d", &intToSearch) || (intToSearch < 1))
		{
			printf("Incorrect value\n");
			rewind(stdin);
		}
		for (int i = 0; i < numberOfFlights; i++)
		{
			while (flight[i].time == intToSearch)
			{
				print(flight, numberOfFlights, i);
				flag = 1;
				break;
			}
		}
		break;
	case 5:
		printf("Enter price of flight: ");
		while (!scanf_s("%lf", &doubleToSearch) || (doubleToSearch <= 0))
		{
			printf("Incorrect value\n");
			rewind(stdin);
		}
		for (int i = 0; i < numberOfFlights; i++)
		{
			while (flight[i].price == doubleToSearch)
			{
				print(flight, numberOfFlights, i);
				flag = 1;
				break;
			}
		}
		break;
	case 6:
		system("CLS");
		menu(flight, numberOfFlights);
		return;
		break;
	}
	if (flag == 0) printf("Nothing found...Try again.\n");
	menu(flight, numberOfFlights);
}
void sort(struct Flights* flight, int numberOfFlights)
{
	if (check(flight, numberOfFlights) == -1)
	{
		menu(flight, numberOfFlights);
		return;
	}
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
		sortFromMin(flight, numberOfFlights);
		return;
		break;
	case 2:
		system("CLS");
		sortFromMax(flight, numberOfFlights);
		return;
		break;
	case 3:
		system("CLS");
		menu(flight, numberOfFlights);
		return;
		break;
	}
}
void sortFromMin(struct Flights* flight, int numberOfFlights)
{
	if (check(flight, numberOfFlights) == -1)
	{
		menu(flight, numberOfFlights);
		return;
	}
	struct Flights temp;
	int choice;
	system("CLS");
	print(flight, numberOfFlights, -1);
	printf("1)Sort by number of flight\n");
	printf("2)Sort by destination\n");
	printf("3)Sort by date of flight\n");
	printf("4)Sort by time of flight\n");
	printf("5)Sort by price of flight\n");
	printf("6)Exit\n");
	while (!scanf_s("%d", &choice) || (choice < 1) || (choice > 6))
	{
		printf("Incorrect value. Try again.\n");
		rewind(stdin);
	}
	switch (choice)
	{
	case 1:
		for (int i = 0; i < numberOfFlights; i++)
		{
			for (int j = 0; j < numberOfFlights - 1; j++)
			{
				if (flight[j].number > flight[j + 1].number)
				{
					temp = flight[j];
					flight[j] = flight[j + 1];
					flight[j + 1] = temp;
				}
			}
		}
		break;
	case 2:
			for (int i = 0; i < numberOfFlights; i++)
			{
				for (int j = 0; j < numberOfFlights-1; j++)
				{
					if (strcmp(flight[j].destination , flight[j + 1].destination)>0)
					{
						temp = flight[j];
						flight[j] = flight[j + 1];
						flight[j + 1] = temp;
						break;
					}
				}
			}
		break;
	case 3:
		for (int i = 0; i < numberOfFlights; i++)
		{
			for (int j = 0; j < numberOfFlights - 1; j++)
			{
				if (flight[j].date > flight[j + 1].date)
				{
					temp = flight[j];
					flight[j] = flight[j + 1];
					flight[j + 1] = temp;
				}
			}
		}
		break;
	case 4:
		for (int i = 0; i < numberOfFlights; i++)
		{
			for (int j = 0; j < numberOfFlights - 1; j++)
			{
				if (flight[j].time > flight[j + 1].time)
				{
					temp = flight[j];
					flight[j] = flight[j + 1];
					flight[j + 1] = temp;
				}
			}
		}
		break;
	case 5:
		for (int i = 0; i < numberOfFlights; i++)
		{
			for (int j = 0; j < numberOfFlights - 1; j++)
			{
				if (flight[j].price > flight[j + 1].price)
				{
					temp = flight[j];
					flight[j] = flight[j + 1];
					flight[j + 1] = temp;
				}
			}
		}
		break;
	case 6:
		system("CLS");
		print(flight, numberOfFlights, -1);
		menu(flight, numberOfFlights);
		return;
	}
	system("CLS");
	print(flight, numberOfFlights, -1);
	menu(flight, numberOfFlights);
}
void sortFromMax(struct Flights* flight, int numberOfFlights)
{
	if (check(flight, numberOfFlights) == -1)
	{
		menu(flight, numberOfFlights);
		return;
	}
	struct Flights temp;
	int choice;
	system("CLS");
	print(flight, numberOfFlights, -1);
	printf("1)Sort by number of flight\n");
	printf("2)Sort by destination\n");
	printf("3)Sort by date of flight\n");
	printf("4)Sort by time of flight\n");
	printf("5)Sort by price of flight\n");
	printf("6)Exit\n");
	while (!scanf_s("%d", &choice) || (choice < 1) || (choice > 6))
	{
		printf("Incorrect value. Try again.\n");
		rewind(stdin);
	}
	switch (choice)
	{
	case 1:
		for (int i = 0; i < numberOfFlights; i++)
		{
			for (int j = 0; j < numberOfFlights - 1; j++)
			{
				if (flight[j].number < flight[j + 1].number)
				{
					temp = flight[j];
					flight[j] = flight[j + 1];
					flight[j + 1] = temp;
				}
			}
		}
		break;
	case 2:
			for (int i = 0; i < numberOfFlights; i++)
			{
				for (int j = 0; j < numberOfFlights - 1; j++)
				{
					if (strcmp(flight[j].destination, flight[j + 1].destination)<0)
					{
						temp = flight[j];
						flight[j] = flight[j + 1];
						flight[j + 1] = temp;
						break;
					}
				}
			}
		break;
	case 3:
		for (int i = 0; i < numberOfFlights; i++)
		{
			for (int j = 0; j < numberOfFlights - 1; j++)
			{
				if (flight[j].date < flight[j + 1].date)
				{
					temp = flight[j];
					flight[j] = flight[j + 1];
					flight[j + 1] = temp;
				}
			}
		}
		break;
	case 4:
		for (int i = 0; i < numberOfFlights; i++)
		{
			for (int j = 0; j < numberOfFlights - 1; j++)
			{
				if (flight[j].time < flight[j + 1].time)
				{
					temp = flight[j];
					flight[j] = flight[j + 1];
					flight[j + 1] = temp;
				}
			}
		}
		break;
	case 5:
		for (int i = 0; i < numberOfFlights; i++)
		{
			for (int j = 0; j < numberOfFlights - 1; j++)
			{
				if (flight[j].price < flight[j + 1].price)
				{
					temp = flight[j];
					flight[j] = flight[j + 1];
					flight[j + 1] = temp;
				}
			}
		}
		break;
	case 6:
		system("CLS");
		print(flight, numberOfFlights, -1);
		menu(flight, numberOfFlights);
		return;
	}
	system("CLS");
	print(flight, numberOfFlights, -1);
	menu(flight, numberOfFlights);
}
int check(struct Flights* flight, int numberOfFlights)
{
	if (numberOfFlights == 0)
	{
		printf("Ooops...No notes found.\n");
		return -1;
	}
}
void print(struct Flights* flight, int numberOfFlights, int flightToPrint)
{
	char table[] = "F L I G H T S";
	printLine();
	printf("|\t\t\t\t\t %-58s|\n", table);
	printLine();
	printf("|\t%-5s|\t%-10s|\t%-19s|\t%-10s|\t%-10s|\t%-11s|\n", "Note", "Number", "Destination", "Date", "Time", "Price");
	printLine();
	if (flightToPrint != -1)
	{
		printf("|\t%-5d|\t%-10d|\t%-19s|\t%-10d|\t%-10d|\t%-11.2lf|\n",
			flightToPrint + 1, flight[flightToPrint].number, (flight + flightToPrint)->destination,
			flight[flightToPrint].date, flight[flightToPrint].time,
			flight[flightToPrint].price);
		printLine();
	}
	else
	{
		for (int i = 0; i < numberOfFlights; i++)
		{
			printf("|\t%-5d|\t%-10d|\t%-19s|\t%-10d|\t%-10d|\t%-11.2lf|\n",
				i + 1, flight[i].number, (flight + i)->destination,
				flight[i].date, flight[i].time,
				flight[i].price);
			printLine();
		}
	}
}
void printLine()
{
	for (int i = 0; i < 100; i++)
	{
		printf("%c", '_');
	}
	printf("\n");
}
void deleteEnter(struct Flights* flight, int numberOfFlights, int numberOfStructure)
{
	for (int i = 0; i < 20; i++)
	{
		if (flight[numberOfStructure].destination[i] == '\n')
			for (i; i < 20; i++)
				flight[numberOfStructure].destination[i] = flight[numberOfStructure].destination[i + 1];
	}
}
void partSearch(struct Flights* flight, int numberOfFlights)
{
	if (check(flight, numberOfFlights) == -1)
	{
		menu(flight, numberOfFlights);
		return;
	}
	system("CLS");
	printf("Select option to search:\n");
	printf("1)Number of flight\n");
	printf("2)Destination\n");
	printf("3)Date\n");
	printf("4)Time\n");
	printf("5)Price\n");
	printf("6)Exit\n");
	int choice;
	while (!scanf_s("%d", &choice) || (choice < 1) || (choice > 6))
	{
		printf("Incorrect value. Try again.\n");
		rewind(stdin);
	}
	printf("\n");
	switch (choice)
	{
	case 1:
		system("CLS");
		printf("Enter symbols of number (*a*b*): ");
		findCharNumber(flight, numberOfFlights, 1);
		break;
	case 2:
		system("CLS");
		printf("Enter symbols of destination (*a*b*): ");
		findCharNumber(flight, numberOfFlights, 2);
		break;
	case 3:
		system("CLS");
		printf("Enter symbols of date (*a*b*): ");
		findCharNumber(flight, numberOfFlights, 3);
		break;
	case 4:
		system("CLS");
		printf("Enter symbols of time (*a*b*): ");
		findCharNumber(flight, numberOfFlights, 4);
		break;
	case 5:
		system("CLS");
		printf("Enter symbols of price (*a*b*): ");
		findCharNumber(flight, numberOfFlights, 5);
		break;
	case 6:
		system("CLS");
		menu(flight, numberOfFlights);
		return;
		break;
	}
	menu(flight, numberOfFlights);
}
void findCharNumber(struct Flights* flight, int numberOfFlights, int choice)
{
	char str[20], str2[20];
	char compareChar;
	int flag = 0, flag1 = 0;
	rewind(stdin);
	fgets(str, 20, stdin);
	rewind(stdin);
	for (int l = 0; l < numberOfFlights; l++)
	{
		switch (choice)
		{
		case 1:
			sprintf_s(str2, "%d", flight[l].number);
			break;
		case 2:
			for (int i = 0; i < 20; i++)
				str2[i] = flight[l].destination[i];
			break;
		case 3:
			sprintf_s(str2, "%d", flight[l].date);
			break;
		case 4:
			sprintf_s(str2, "%d", flight[l].time);
			break;
		case 5:
			sprintf_s(str2, "%lf", flight[l].price);
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
		if ((flag == flag1) && (flag1 != 0))	print(flight, numberOfFlights, l);
		flag = 0;
		flag1 = 0;
	}
}
void deleteByTheOption(struct Flights* flight, int numberOfFlights)
{
	if (check(flight, numberOfFlights) == -1)
	{
		menu(flight, numberOfFlights);
		return;
	}
	system("CLS");
	printf("Select option to search:\n");
	printf("1)Number of flight\n");
	printf("2)Destination\n");
	printf("3)Date\n");
	printf("4)Time\n");
	printf("5)Price\n");
	printf("6)Exit\n");
	int choice, intToSearch = 0, flag = 0;
	double doubleToSearch;
	char str[20];
	while (!scanf_s("%d", &choice) || (choice < 1) || (choice > 6))
	{
		printf("Incorrect value\n");
		rewind(stdin);
	}
	switch (choice)
	{
	case 1:
		printf("Enter number of flight: ");
		while (!scanf_s("%d", &intToSearch) || (intToSearch < 1))
		{
			printf("Incorrect value\n");
			rewind(stdin);
		}
		for (int i = 0; i < numberOfFlights; i++)
		{
			while (flight[i].number == intToSearch)
			{
				delExact(flight, numberOfFlights, i);
				flag = 1;
				break;
			}
		}
		break;
	case 2:
		printf("Enter destination: ");
		rewind(stdin);
		fgets(str, 20, stdin);
		for (int i = 0; i < 20; i++)
		{
			if (str[i] == '\n')
				for (i; i < 20; i++)
					str[i] = str[i + 1];
		}
		for (int i = 0; i < numberOfFlights; ++i)
		{
			int temp = 0;
			if (strlen(flight[i].destination) == strlen(str))
			{
				for (int j = 0; j < strlen(str); j++)
				{
					if (flight[i].destination[j] != str[j])
						break;
					else
						temp++;
					if (temp == strlen(str))
						print(flight, numberOfFlights, i);
					delExact(flight, numberOfFlights, i);
					flag = 1;
					break;
				}
			}
		}
		break;
	case 3:
		printf("Enter date of flight: ");
		while (!scanf_s("%d", &intToSearch) || (intToSearch < 1))
		{
			printf("Incorrect value\n");
			rewind(stdin);
		}
		for (int i = 0; i < numberOfFlights; i++)
		{
			while (flight[i].date == intToSearch)
			{
				delExact(flight, numberOfFlights, i);
				flag = 1;
				break;
			}
		}
		break;
	case 4:
		printf("Enter time of flight: ");
		while (!scanf_s("%d", &intToSearch) || (intToSearch < 1))
		{
			printf("Incorrect value\n");
			rewind(stdin);
		}
		for (int i = 0; i < numberOfFlights; i++)
		{
			while (flight[i].time == intToSearch)
			{
				delExact(flight, numberOfFlights, i);
				flag = 1;
				break;
			}
		}
		break;
	case 5:
		printf("Enter price of flight: ");
		while (!scanf_s("%lf", &doubleToSearch) || (doubleToSearch <= 0))
		{
			printf("Incorrect value\n");
			rewind(stdin);
		}
		for (int i = 0; i < numberOfFlights; i++)
		{
			while (flight[i].price == doubleToSearch)
			{
				delExact(flight, numberOfFlights, i);
				flag = 1;
				break;
			}
		}
		break;
	case 6:
		system("CLS");
		menu(flight, numberOfFlights);
		return;
		break;
	}
	if (flag == 0) printf("Nothing found...Try again.\n");
	menu(flight, numberOfFlights);
}
void delExact(struct Flights* flight, int numberOfFlights, int flightNumber)
{
	for (int i = flightNumber; i < numberOfFlights; i++)
	{
		flight[i] = flight[i + 1];
	}
	numberOfFlights--;
	flight = (Flights*)realloc(flight, numberOfFlights * sizeof(Flights));
	system("CLS");
	printf("Note was successfully deleted!\n");
	menu(flight, numberOfFlights);
}
void rightRegister(struct Flights* flight, int numberOfFlights, int numberOfStructure)
{
	if ((flight[numberOfStructure].destination[0] >= 'a') && (flight[numberOfStructure].destination[0] <= 'z'))
		flight[numberOfStructure].destination[0] -= 32;
	for (int i = 1; i < 20; i++)
	{
		if ((flight[numberOfStructure].destination[i] >= 'A') && (flight[numberOfStructure].destination[i] <= 'Z'))
			flight[numberOfStructure].destination[i] += 32;
	}
	for (int i = 1; i < 20; i++)
	{
		if ((flight[numberOfStructure].destination[i] >= 'a') && (flight[numberOfStructure].destination[i] <= 'z') &&
			(((flight[numberOfStructure].destination[i - 1]) == '-') || ((flight[numberOfStructure].destination[i - 1]) == ' ')))
			flight[numberOfStructure].destination[i] -= 32;
	}
}