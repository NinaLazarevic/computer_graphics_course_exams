// Broj.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>


int main()
{
	int broj, i, cifra, pombroj;
	char slova[]="0000";

	printf("Unesite broj od 4 cifre:\n");
	scanf("%d", &broj);

	pombroj = broj;
	i = 0;
	while (pombroj/10 != 0)
	{
		pombroj /= 10;
		i++;
	}
	i++;

	if (i > 4)
	{
		printf("Uneli ste broj koji ima vise od 4 cifre");
		return 0;
	}
	if (i < 4)
	{
		printf("Uneli ste broj koji ima manje od 4 cifre");
		return 0;
	}

	while (broj / 10 != 0)
	{
		cifra = broj % 10;
		broj /= 10;
		i--;
		slova[i] = cifra + '0';

		printf("%d. cifra: %d \n", i, cifra);
	}
	i--;
	slova[i] = broj + '0';

	printf("%d. cifra: %d \n", i, broj);


    return 0;
}

