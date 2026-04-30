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
// I: numarul solutiei (num), dimensiunea permutarii (nr), permutarea (v)
void retine_solutia(int num, int nr, int* v)
{
	int i;
	printf("\nSolutia numarul %d:", num);
	for (i = 0; i < nr; i++)  printf("%2d ", v[i]);
}

// Genereaza permutari de n elemente (1..n)
// I: n
// E: numar permutari
int permutari(int n)
{
	int* p, i, ok, nr;
	
	p = malloc(n * sizeof(int));         //vectorul solutie

	nr = 0;                      //numar solutii
	i = 0;

	p[0] = 0;                  //prima valoare(=1) minus ratia(=1)
	
	while (i >= 0)            //cat timp nu am ajuns la configuratia finala
	{
		ok = 0;
		while (p[i] < n && ok == 0) //alege urmatoarea valoare acceptabila pentru p[i]
		{
			p[i]++;                 //urmatoarea valoare pentru p[i]
			ok = posibil(p, i);    //este acceptabila?
		}
		if (ok == 0)               //impas, revenire
			i--;
		else
			if (i == n - 1)        //configuratie solutie (am ajuns la finalul vectorului p)
				retine_solutia(++nr, n, p);
			else
				p[++i] = 0;       //prima valoare(=1) minus ratia(=1)
	}

	free(p);

	return nr;
}

//Permutari recursiv
//I: dimensiune (n), pas curent (i), sol. partiala curenta (x),  nr. crt. sol. (nr)
//E: numar solutii (nr)
int permutari_r(int n, int i, int* x, int nr)
{
	if (i == n)
		retine_solutia(++nr, n, x);
	else
		for (int j = 1; j <= n; j++)
		{
			x[i] = j;
			if (posibil(x, i))
				nr = permutari_r(n, i + 1, x, nr);
		}
	return nr;
}

int main() {
	int n, nr;

	printf("n="); scanf("%d", &n);

	int* x = malloc(n * sizeof(int));

	//nr = permutari(n); //apel pentru varianta iterativa

	//printf("\n\nNumarul total de permutari este: %d\n\n", nr);

	nr = permutari_r(n, 0, x, 0); //apel pentru varianta recursiva

	printf("\n\nNumarul total de permutari este: %d\n\n", nr);

	free(x);
	return 0;
}
