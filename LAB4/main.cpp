#include <stdio.h>
#include <Windows.h>
#include "Header.h"
int main()
{
	struct Series* serial = NULL;
	while (1)
	{
		switch (menu())
		{
		case 1:
			add(&serial);
			reverse(&serial);
			break;
		case 2:
			print(serial, 0);
			break;
		case 3:
			del(&serial);
			break;
		case 4:
			search(serial);
			break;
		case 5:
			write(serial);
			break;
		case 6:
			read(&serial);
			reverse(&serial);
			break;
		case 7:
			clear(&serial);
			return 0;
		default:
			printf("Incorrect value! Try again...\n");
			system("CLS");
		}
	}
}