#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"

int main()
{
	struct Tree* root = NULL;
	char str[20];
	while (1)
	{
		switch (menu())
		{
		case 1:
			add(&root);
			break;
		case 2:
			showMenu(root);
			break;
		case 3:
			rewind(stdin);
			puts("Enter word to delete: ");
			fgets(str, 20, stdin);
			rewind(stdin);
			str[strlen(str) - 1] = '\0';
			root=del(root, str);
			break;
		case 4:
			system("CLS");
			clean(&root);
			return 0;
		}
	}
}