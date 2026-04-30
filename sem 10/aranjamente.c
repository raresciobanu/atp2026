#include <stdio.h>
#include<malloc.h>

// Verifica daca valoarea elementului i este acceptabila(daca v[i] este diferit de toate elementele din v)
int posibil(int* v, int i)
{
	for (int j = 0; j < i; j++)
		if (v[i] == v[j])  return 0;
	return 1;
}

// Afisare solutie pe ecran
// I: numarul solutiei (num), dimensiunea (k), solutia (v)
void retine_solutia(int num, int k, int* v)
{
	int i;
	printf("\nSolutia numarul %d: ", num);
	for (i = 0; i < k; i++)
		printf("%2d ", v[i]);
}

//I: dimensiune (n), numarul maxim k, pas curent (i),
//sol. partiala curenta (x), nr. crt. sol. (nr)
//E: numar solutii (nr)
int aranjamente(int n, int k, int i, int* x, int nr)
{
	int j;
	if (i == k)
		retine_solutia(++nr, k, x);
	else
		for (j = 1; j <= n; j++)
		{
			x[i] = j;
			if (posibil(x, i))
				nr = aranjamente(n, k, i + 1, x, nr);
		}
	return nr;
}

int main()
{
	int n, k, nr;

	printf("n="); scanf("%d", &n);
	printf("k="); scanf("%d", &k);

	int* x = malloc(n * sizeof(int));

	if (k > 0 && k <= n) {
		nr = aranjamente(n, k, 0, x, 0);
		printf("\nNumarul de aranjamente este: %d\n", nr);
	}
	else printf("Nu exista solutii");

	free(x);

	return 0;
}
