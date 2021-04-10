#include <stdio.h>
#include <stdlib.h>
#include "Header.h"
int main()
{
    int arraySize = 0;
    int newArraySize = 0;
    struct TheGame* games = NULL;
    while (1)
    {
        switch (menu())
        {
        case 1:
            printf("Number of games you want to add: \n");
            newArraySize = inputValidationInt();
            arraySize += newArraySize;
            games = add(games, arraySize, newArraySize);
            break;
        case 2:
            show(games, arraySize);
            break;
        case 3:
            change(games, arraySize);
            break;
        case 4:
            search(games, arraySize);
            break;
        case 5:
            sort(games, arraySize);
             break;
        case 6:
            del(games, arraySize);
            arraySize = sizeof(games)/sizeof(struct TheGame*);
            break;
        case 7:
            free(games);
            return 0;
        default:
            printf("Error. Incorrect value!\n");
        }
    }
}