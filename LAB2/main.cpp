#include <stdio.h>
#include <stdlib.h>
#include "Header.h"
int main()
{
	int numberOfSeries = 0;
	struct Series* serial=NULL;
	while (1)
	{
		switch (menu())
		{
		case 1: 
			serial=add(serial, numberOfSeries); 
			numberOfSeries = size(serial, numberOfSeries); 
			break;
		case 2: show(serial, numberOfSeries); break;
		case 3:
			serial=del(serial, numberOfSeries);
			numberOfSeries = size(serial, numberOfSeries);
			break;
		case 4:	search(serial, numberOfSeries); break;
		case 5: sort(serial, numberOfSeries); break;
		case 6: serial=change(serial, numberOfSeries); break;
		case 7: partSearch(serial, numberOfSeries); break;
		case 8: 
			free(serial);
			return 0;
		default:
			printf("Incorrect value! Try again...\n");
			system("CLS");
		}
	}
}