#include <stdio.h>

int verificare(int n, int k)
{
	int i, d = 0;
	for (i = 2; i <= n / 2; i++)
		if (n % i == 0)
			d++;
	return (d == k) ? 1 : 0;//daca s a gasit N care sa aiba k div proprii return 1
	//expresie conditionala echivalenta cu if(d==k) return 1; else return 0;
}

int divizori(int k)
{
	int i, n;
	n = k + 2; //dc n=k+2 si nu n=k? pt ca daca ar fi K=2 si am face n=k => variabila n=2 nu are div proprii; nici n=3 nu are; primul element care ar avea ca div comun ar fi n=4 (adica valoarea 2);
	while (verificare(n, k) == 0)n++;
	return n;
}

void main()
{
	int k;
	printf("Introduceti nr. de divizori proprii:");
	scanf("%d", &k);
	printf("Cel mai mic nr. natural cu %d divizori proprii este %d\n", k, divizori(k));
}
