#include <stdio.h>
#include<malloc.h>
void init(int* n, int* k, int** x)
{
	printf("n="); scanf("%d", n);
	printf("k="); scanf("%d", k);

	*x = malloc(*k * sizeof(int));
	for (int i = 0; i < *k; i++)
		*(*x + i) = 0;
}

//afiseaza solutia
void afiseaza(int k, int* x)
{
	for (int i = 0; i < k; i++)
		printf("%d ", x[i]);
	printf("\n");
}

//verifica daca poate fi adaugat numarul la solutie
int posibil(int p, int* x)
{
	if (p > 0 && x[p] <= x[p - 1])
		return 0;
	return 1;
}

//subprogramul recursiv de generare combinari de n luate cite k
void combinari(int p, int n, int k, int* x)
{
	int pval;
	for (pval = 1; pval <= n; pval++)
	{
		x[p] = pval;
		if (posibil(p, x))
		{
			if (p == k - 1)
				afiseaza(k, x);
			else
				combinari(p + 1, n, k, x);
		}
	}
}

int main()
{
	int n, k, *x;

	init(&n, &k, &x);

	if (k > 0 && k <= n) 
		combinari(0, n, k, x);
	else printf("Nu exista solutii");

	free(x);

	return 0;
}
