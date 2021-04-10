#include <stdio.h>
#include <stdlib.h>
#include "Header.h"
int main()
{
	struct Flights* flight=NULL;
	int numberOfFlights=0;
	int n=menu(flight, numberOfFlights);
	while (n == 8)
	{
		free(flight);
		return 0;
	}
	return 0;
}