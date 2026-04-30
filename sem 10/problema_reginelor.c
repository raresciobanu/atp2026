#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<malloc.h>
#include<math.h>

//x[i] -> coloana; i->linia
// Conditia de continuare: reginele i si j nu se ataca daca nu sunt pe aceeasi coloana: x[i] != x[j]
// - distantele pe verticala si orizontala sunt diferite: abs(i - j) != abs(x[i] - x[j]))

// I: solutia partiala (x), numarul de elemente (i)
// E: 1 daca e acceptabila, 0 daca nu e acceptabila

int posibil(int* x, int i)
{
	for (int j = 1; j < i; j++)
		if (x[i] == x[j] || abs(i - j) == abs(x[i] - x[j]))
			return 0;
	return 1;
}

// Retine o configuratie solutie (afisare)
// I: nr. solutie (nr), nr regine (n), vector solutie
// E: -

void retine_solutia(int nr, int n, int* x)
{
	int i, j;
	printf("\n Solutia numarul %d\n", nr);
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
			printf("%c ", j == x[i] ? 'R' : 'x'); //x[i] contine indexul coloanei...i-indexul liniei; j-indexul coloanei
		printf("\n");
	}
}

// I: numar regine/dimensiune tabla (n)
// E: numar solutii
int regine(int n)
{
	int nr;
	int* x;
	int i, ok;

	x = malloc((n + 1) * sizeof(int));       	//vectorul solutie
	nr = 0;                	//numar solutii
	i = 1;
	x[1] = 0;                            //prima valoare minus ratia

	while (i > 0)                     //cit timp nu am ajuns la configuratia finala
	{
		ok = 0;
		while (x[i] < n && ok == 0) //alege urmatoarea valoare acceptabila pentru x[i]
		{
			x[i]++;                         //urmatoarea valoare pentru x[i]
			ok = posibil(x, i);         //este acceptabila?
		}
		if (ok == 0) 
			i--;
		else
			if (i == n)    retine_solutia(++nr, n, x);
			else
				x[++i] = 0;       //prima valoare minus ratia
	}
	free(x);

	return nr;
}

// I: numar dame (n), element curent (i), vector solutie (x),
// numar solutii (nr)
// E: nr. solutii
int regine_r(int n, int i, int* x, int nr)
{
	int j;
	if (i == n + 1)
		retine_solutia(++nr, n, x);
	else
		for (j = 1; j <= n; j++)
		{
			x[i] = j;
			if (posibil(x, i))
				nr = regine_r(n, i + 1, x, nr);
		}
	return nr;
}

int main() {
	int n;
	printf("n="); scanf("%d", &n);

	int* x = malloc((n + 1) * sizeof(int));//este n+1 pt ca vrem sa iteram mai usor prin vector doar de la 1->N (fara poz 0)

	int nr = 0;

	//printf("\n\nNumarul de solutii este %d ", regine_r(n, 1, x, nr));
	printf("\n\nNumarul de solutii este %d ", regine(n));

	free(x);
	return 0;
}
