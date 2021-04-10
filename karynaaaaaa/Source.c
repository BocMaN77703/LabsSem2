#include <stdio.h>
#include <stdlib.h>
#include "Header.h"
#include <string.h>
union Rules
{
    int maxPlayers;
    char gameGenre[20];
};
struct TheGame
{
    float price;
    char name[20];
    union Rules rules;
    int flag;
};
int menu()
{
    int choice;
    printf("Choose an operation:\n");
    printf("1) Add game\n2) Show games\n3) Change games\n4) Search games\n5) Sort games\n6) Delete games\n7) Exit\n");
    choice = correctChoice(7);
    return choice;
}
struct TheGame* add(struct TheGame* games, int arraySize, int newArraySize)
{
    if (arraySize - newArraySize == 0) games = (struct TheGame*)calloc(arraySize, sizeof(struct TheGame));
    else games = (struct TheGame*)realloc(games, arraySize * sizeof(struct TheGame));
    for (int i = arraySize - newArraySize; i < arraySize; i++)
    {
        printf("Number of game: %d\n", i + 1);
        printf("Enter price: ");
        /*while (!scanf_s("%f", &games[i].price) || (games[i].price < 0))
        {
            rewind(stdin);
            printf("Incorrect value!\n");
        }*/
        games[i].price = inputValidationFloat();
        printf("Enter name: ");
        rewind(stdin);
        fgets(games[i].name, 20, stdin);
        rewind(stdin);
        games[i].name[strlen(games[i].name) - 1] = '\0';
        printf("Enter '1' to enter game genre or '2' to enter max number of players: ");
        /*while (!scanf_s("%d", &games[i].flag) || (games[i].flag < 1) || (games[i].flag > 2))
        {
            rewind(stdin);
            printf("Incorrect value! try again...\n");
        }*/
        games[i].flag = correctChoice(2);
        if (games[i].flag == 1)
        {
            printf("Enter game genre: ");
            rewind(stdin);
            fgets(games[i].rules.gameGenre, 20, stdin);
            rewind(stdin);
            games[i].rules.gameGenre[strlen(games[i].rules.gameGenre) - 1] = '\0';
        }
        else
        {
            printf("Enter max number of players: ");
            /*while (!scanf_s("%d", &games[i].rules.maxPlayers) || (games[i].rules.maxPlayers < 1))
            {
                rewind(stdin);
                printf("Incorrect value! try again...\n");
            }*/
            games[i].rules.maxPlayers = inputValidationInt();
        }
    }
    return games;
}
void show(struct TheGame* games, int arraySize) {
    hat();
    for (int i = 0; i < arraySize; i++) {
        printGames(games, i);
        line();
    }
}
void hat() {
    char title[] = "G A M E S";
    line();
    printf("|%-40s%-79s|\n", " ", title);
    line();
    printf("|\t%-2s\t|\t%-15s\t|\t%-8s\t|\t%-9s\t|\t%-s\t\t\t|\n", "#", "Name", "Price", "Genre", "Max Players");
    line();
}
void printGames(struct TheGame* games, int i) {
    if (games[i].flag == 1)
        printf("|\t%-2d\t|\t%-20s\t|\t%-.2f\t|\t%-20s\t|\t%-s\t\t|\n", i + 1,
            games[i].name, games[i].price, games[i].rules.gameGenre, "-");
    else printf("|\t%-2d\t|\t%-20s\t|\t%-.2f\t|\t%-s\t|\t%-5d\t\t\t|\n", i + 1,
        games[i].name, games[i].price, "-", games[i].rules.maxPlayers);
    line();
}
void line()
{
    for (int i = 0; i < 115; i++)
    {
        printf("%c", '-');
    }
    printf("\n");
}
void change(struct TheGame* games, int arraySize)
{
    printf("Choose an operation:\n");
    printf("1)  Edit the entire post\n");
    printf("2)  Edit part of note\n");
    printf("3)  Exit\n");
    int choice = correctChoice(3);
    switch (choice)
    {
    case 1:
        changeOneGame(games, arraySize);
        break;
    case 2:
        partChange(games, arraySize);
        break;
    case 3:
        break;
    }

}
void changeOneGame(struct TheGame* games, int arraySize)
{
    printf("Enter game number\n");
    int gameNumber = correctChoice(arraySize);
    gameNumber--;
    printf("Enter new game name\n");
    rewind(stdin);
    fgets(games[gameNumber].name,20, stdin);
    rewind(stdin);
    games[gameNumber].name[strlen(games[gameNumber].name) - 1] = '\0';
    printf("Enter new price size\n");
    games[gameNumber].price = inputValidationFloat();

    if (games[gameNumber].flag == 1)
    {
        printf("Make a choice\n");
        printf("1)  Change game genre\n");
        printf("2)  Change the field with the game genre to the maximum number of players\n");
        int choice = correctChoice(2);
        switch (choice)
        {
        case 1:
            printf("Enter a new genre\n");
            rewind(stdin);
            fgets(games[gameNumber].rules.gameGenre, 20, stdin);
            rewind(stdin);
            games[gameNumber].rules.gameGenre[strlen(games[gameNumber].rules.gameGenre) - 1] = '\0';
            return;
        case 2:
            printf("Enter the maximum number of players\n");
            games[gameNumber].rules.maxPlayers = inputValidationInt();
            games[gameNumber].flag = 2;
            return;
        }
    }
    if (games[gameNumber].flag == 2)
    {
        printf("Make choice\n");
        printf("1)  Change the maximum number of players\n");
        printf("2)  Change the maximum number of players to the game genre\n");
        int choice = correctChoice(2);
        switch (choice)
        {
        case 1:
            printf("Enter the maximum number of players\n");
            games[gameNumber].rules.maxPlayers = inputValidationInt();
            return;
        case 2:
            printf("Enter new genre\n");
            rewind(stdin);
            fgets(games[gameNumber].rules.gameGenre, 20, stdin);
            rewind(stdin);
            games[gameNumber].rules.gameGenre[strlen(games[gameNumber].rules.gameGenre) - 1] = '\0';
            games[gameNumber].flag = 1;
            return;
        }
    }
}
void partChange(struct TheGame* games, int arraySize)
{
    printf("Enter game number\n");
    int gameNumber = correctChoice(arraySize);
    gameNumber--;
    printf("Make a choice\n");
    printf("1)  Change game name\n");
    printf("2)  Change price size\n");
    printf("3)  Change game genre\n");
    printf("4)  Change the maximum number of players\n");
    int choice = correctChoice(4);
    switch (choice)
    {
    case 1:
        printf("Enter new game name\n");
        rewind(stdin);
        fgets(games[gameNumber].name, 20, stdin);
        rewind(stdin);
        games[gameNumber].name[strlen(games[gameNumber].name) - 1] = '\0';

        break;
    case 2:
        printf("Enter new price size\n");
        games[gameNumber].price = inputValidationFloat();
        break;
    case 3:
        if (games[gameNumber].flag == 1)
        {
            printf("Enter the new genre\n");
            rewind(stdin);
            fgets(games[gameNumber].rules.gameGenre,20,stdin);
            rewind(stdin);
            games[gameNumber].rules.gameGenre[strlen(games[gameNumber].rules.gameGenre) - 1] = '\0';

        }
        if (games[gameNumber].flag == 2)
        {
            printf("If you change this field,"
                "you will no longer be able to store information about the maximum number of players\n");
            printf("Do you want to make changes?\n");
            printf("1)No\n2)Yes\n");
            int editChoice = correctChoice(2);
            switch (editChoice)
            {
            case 1:
                break;
            case 2:
                printf("Enter the genre\n");
                rewind(stdin);
                gets(games[gameNumber].rules.gameGenre);
                games[gameNumber].flag = 1;
            }
        }
        break;
    case 4:
        if (games[gameNumber].flag == 2)
        {
            printf("Enter the maximum number of players\n");
            games[gameNumber].rules.maxPlayers = inputValidationInt();
        }
        if (games[gameNumber].flag == 1)
        {
            printf("If you change this field,"
                "you will no longer be able to store information about the genre of the game\n");
            printf("Do you want to make changes?\n");
            printf("1)No\n2)Yes\n");
            int editChoice = correctChoice(2);
            switch (editChoice)
            {
            case 1:
                break;
            case 2:
                printf("Enter the maximum number of players\n");
                games[gameNumber].rules.maxPlayers = inputValidationInt();
                games[gameNumber].flag = 2;
            }
        }
        break;
    }
}
void search(struct TheGame* games, int arraySize)
{
    printf("Choose an operation:\n1)    By the given parameter\n2)    Partical search\n");
    int choice = correctChoice(2);
    switch (choice)
    {
    case 1:
        searchByGivenParam(games, arraySize);
        break;
    case 2:
        particalSearch(games, arraySize);
        break;
    }
}
void searchByGivenParam(struct TheGame* games, int arraySize)
{
    printf("Choose an operation:\n");
    printf("1)Name\n2)Price\n3)Genre of the game\n4)Maximum number of players\n");
    int choice = correctChoice(4);
    int gameNumber = 0;
    switch (choice)
    {
    case 1:
        printf("Enter game name: ");
        rewind(stdin);
        char authorName[20];
        fgets(authorName, 20, stdin);
        rewind(stdin);
        authorName[strlen(authorName) - 1] = '\0';
        gameNumber = 0;
        hat();
        for (int i = 0; i < arraySize; ++i)
        {
            if (strcmp(authorName, games[i].name) == 0)
            {
                //Вывод
                printGames(games, i);
                gameNumber++;
            }
        }
        rewind(stdin);
        break;
    case 2:
        printf("Enter the number of pages\n");
        float price = inputValidationFloat();
        gameNumber = 0;
        hat();
        for (int i = 0; i < arraySize; ++i)
        {
            if (price == games[i].price)
            {
                /*headline();
                searchOutput(pointer, gameNumber);
                Вывод*/
                printGames(games, i);
                gameNumber++;
            }
        }
        break;
    case 3:
        printf("Enter genre\n");
        rewind(stdin);
        char genreName[20];
        fgets(genreName,20, stdin);
        rewind(stdin);
        genreName[strlen(genreName) - 1] = '\0';
        gameNumber = 0;
        hat();
        for (int i = 0; i < arraySize; ++i)
        {
            if (strcmp(genreName, games[i].rules.gameGenre) == 0)
            {
                //Вывод
                printGames(games, i);
                gameNumber++;
            }
        }
        rewind(stdin);
        break;
    case 4:
        printf("Enter the max number of players\n");
        int maxPlayers = inputValidationInt();
        gameNumber = 0;
        hat();
        for (int i = 0; i < arraySize; ++i)
        {
            if (maxPlayers == games[i].rules.maxPlayers)
            {
                printGames(games, i);
                gameNumber++;
            }
        }
        break;
    }
}
void particalSearch(struct TheGame* games, int arraySize)
{
    printf("Select option to search:\n");
    printf("1)Name\n");
    printf("2)Price\n");
    printf("3)Game genre\n");
    printf("4)Max number of players\n");
    printf("5)Exit\n");
    int choice;
    choice = correctChoice(5);
    printf("\n");
    switch (choice)
    {
    case 1:
        printf("Enter Name: ");
        //findCharNumber(games, arraySize, 1);
        break;
    case 2:
        printf("Enter Price: ");
        //findCharNumber(games, arraySize, 2);
        break;
    case 3:
        printf("Enter game genre: ");
        //findCharNumber(games, arraySize, 3);
        break;
    case 4:
        printf("Enter number of players: ");
        //findCharNumber(games, arraySize, 4);
        break;
    case 5:
        return;
        break;
    }
    char str[20], str2[20];
    char compareChar;
    int flag = 0, flag1 = 0;
    rewind(stdin);
    fgets(str, 20, stdin);
    rewind(stdin);
    for (int l = 0; l < arraySize; l++)
    {
        switch (choice)
        {
        case 1:
            for (int i = 0; i < 20; i++)
                str2[i] = games[l].name[i];
            break;
        case 2:
            sprintf(str2, "%f", games[l].price);
            break;
        case 3:
            if (games[l].flag != 1) continue;
            for (int i = 0; i < 20; i++)
                str2[i] = games[l].rules.gameGenre[i];
            break;
        case 4:
            if (games[l].flag == 1) continue;
            sprintf_s(str2, "%d", games[l].rules.maxPlayers);
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
        if ((flag == flag1) && (flag1 != 0))
        {
            hat();
            printGames(games, l);
        }
        flag = 0;
        flag1 = 0;
    }
}
struct TheGame* del(struct TheGame* games, int arraySize)
{
    printf("1)Delete by number\n2)Delete by parameter\n3)Exit\n");
    int choice = correctChoice(3);
    switch (choice)
    {
    case 1:
        printf("Choose game to delete:\n");
        choice = inputValidationInt();
        delExact(games, arraySize, choice);
        break;
    case 2:
        printf("Choose an operation:\n");
        printf("1)Name\n2)Price\n3)Maximum number of players\n4)Genre of the game\n");
        choice = correctChoice(4);
        int gameNumber = 0;
        switch (choice)
        {
        case 1:
            printf("Enter game name: ");
            rewind(stdin);
            char authorName[20];
            gets(authorName);
            gameNumber = 0;
            for (int i = 0; i < arraySize; ++i)
            {
                if (strcmp(authorName, games[i].name) == 0)
                {
                    //Вывод
                    delExact(games, arraySize, i);
                    gameNumber++;
                }
            }
            rewind(stdin);
            break;
        case 2:
            printf("Enter the number of pages\n");
            float price = inputValidationFloat();
            gameNumber = 0;
            for (int i = 0; i < arraySize; ++i)
            {
                if (price == games[i].price)
                {
                    /*headline();
                    searchOutput(pointer, gameNumber);
                    Вывод*/
                    delExact(games, arraySize, i);
                    gameNumber++;
                }
            }
            break;
        case 3:
            printf("Enter genre\n");
            rewind(stdin);
            char genreName[20];
            gets(genreName);
            gameNumber = 0;
            for (int i = 0; i < arraySize; ++i)
            {
                if (strcmp(genreName, games[i].rules.gameGenre) == 0)
                {
                    //Вывод
                    delExact(games, arraySize, i);
                    gameNumber++;
                }
            }
            rewind(stdin);
            break;
        case 4:
            printf("Enter the max number of players\n");
            int maxPlayers = inputValidationInt();
            gameNumber = 0;
            for (int i = 0; i < arraySize; ++i)
            {
                if (maxPlayers == games[i].rules.maxPlayers)
                {
                    delExact(games, arraySize, i);
                    gameNumber++;
                }
            }
            break;
        }
        break;
    case 3:
        break;
    }
    return games;
}
struct TheGame* delExact(struct TheGame* games, int arraySize, int num)
{
    for (int i = num; i < arraySize; i++)
    {
        games[i] = games[i + 1];
    }
    arraySize--;
    games = (struct TheGame*)realloc(games, arraySize * sizeof(struct TheGame));
    printf("Note was successfully deleted!\n");
    return games;
}
void sort(struct TheGame* games, int arraySize)
{
    printf("How to sort:\n");
    printf("1)From Min to Max\n");
    printf("2)From Max to Min\n");
    printf("3)Exit\n");
    int choice=correctChoice(3);
    printf("\n");
    switch (choice)
    {
    case 1:
        sortFromMin(games, arraySize);
        return;
        break;
    case 2:
        sortFromMax(games, arraySize);
        return;
        break;
    case 3:
        return;
        break;
    }
}
void sortFromMin(struct TheGame* games, int arraySize)
{
    struct TheGame temp;
    int choice;
    hat();
    for (int i = 0; i < arraySize; i++)
        printGames(games, i);
    printf("1)Title\n");
    printf("2)Number of episodes\n");
    printf("3)Date of release\n");
    printf("4)Number of seasons\n");
    printf("5)Exit\n");
    choice = correctChoice(5);
    switch (choice)
    {
    case 1:
        for (int i = 0; i < arraySize; i++)
        {
            for (int j = 0; j < arraySize - 1; j++)
            {
                if (strcmp(games[j].name, games[j + 1].name) > 0)
                {
                    temp = games[j];
                    games[j] = games[j + 1];
                    games[j + 1] = temp;
                    break;
                }
            }
        }
        break;
    case 2:
        for (int i = 0; i < arraySize; i++)
        {
            for (int j = 0; j < arraySize - 1; j++)
            {
                if (games[j].price > games[j + 1].price)
                {
                    temp = games[j];
                    games[j] = games[j + 1];
                    games[j + 1] = temp;
                }
            }
        }
        break;
    case 3:
        for (int i = 0; i < arraySize; i++)
        {
            for (int j = 0; j < arraySize - 1; j++)
            {
                if (games[j].flag != 1) continue;
                if (strcmp(games[j].rules.gameGenre, games[j + 1].rules.gameGenre) > 0)
                {
                    temp = games[j];
                    games[j] = games[j + 1];
                    games[j + 1] = temp;
                    break;
                }
            }
        }
    case 4:
        for (int i = 0; i < arraySize; i++)
        {
            for (int j = 0; j < arraySize - 1; j++)
            {
                if (games[j].flag == 1) continue;
                if (games[j].rules.maxPlayers > games[j + 1].rules.maxPlayers)
                {
                    temp = games[j];
                    games[j] = games[j + 1];
                    games[j + 1] = temp;
                }
            }
        }
        break;
    case 5:
        return;
    }
}
void sortFromMax(struct TheGame* games, int arraySize)
{
    struct TheGame temp;
    int choice;
    hat();
    for (int i = 0; i < arraySize; i++)
        printGames(games, i);
    printf("1)Title\n");
    printf("2)Number of episodes\n");
    printf("3)Date of release\n");
    printf("4)Number of seasons\n");
    printf("5)Exit\n");
    choice = correctChoice(5);
    switch (choice)
    {
    case 1:
        for (int i = 0; i < arraySize; i++)
        {
            for (int j = 0; j < arraySize - 1; j++)
            {
                if (strcmp(games[j].name, games[j + 1].name) < 0)
                {
                    temp = games[j];
                    games[j] = games[j + 1];
                    games[j + 1] = temp;
                    break;
                }
            }
        }
        break;
    case 2:
        for (int i = 0; i < arraySize; i++)
        {
            for (int j = 0; j < arraySize - 1; j++)
            {
                if (games[j].price < games[j + 1].price)
                {
                    temp = games[j];
                    games[j] = games[j + 1];
                    games[j + 1] = temp;
                }
            }
        }
        break;
    case 3:
        for (int i = 0; i < arraySize; i++)
        {
            for (int j = 0; j < arraySize - 1; j++)
            {
                if (games[j].flag != 1) continue;
                if (strcmp(games[j].rules.gameGenre, games[j + 1].rules.gameGenre) < 0)
                {
                    temp = games[j];
                    games[j] = games[j + 1];
                    games[j + 1] = temp;
                    break;
                }
            }
        }
    case 4:
        for (int i = 0; i < arraySize; i++)
        {
            for (int j = 0; j < arraySize - 1; j++)
            {
                if (games[j].flag == 1) continue;
                if (games[j].rules.maxPlayers < games[j + 1].rules.maxPlayers)
                {
                    temp = games[j];
                    games[j] = games[j + 1];
                    games[j + 1] = temp;
                }
            }
        }
        break;
    case 5:
        return;
    }
}

//------------Проверки на ввод------------//
int inputValidationInt()
{
    int n;
    while (scanf("%d", &n) != 1 || n <= 0)
    {
        rewind(stdin);
        printf("Try again\n");
    }
    return n;
}
float inputValidationFloat()
{
    float n;
    while (scanf("%f", &n) != 1 || n <= 0)
    {
        rewind(stdin);
        printf("Try again\n");
    }
    return n;
}
int correctChoice(int k)
{
    int n;
    while (scanf("%d", &n) != 1 || n <= 0 || n > k)
    {
        rewind(stdin);
        printf("Try again\n");
    }
    return n;
}