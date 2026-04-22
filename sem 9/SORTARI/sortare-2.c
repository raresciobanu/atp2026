//MERGE SORT = DIVIDE ET IMPERA + interclasare
//x-tabloul ; p - poz de inceput a tabloului X; u - poz de sf. a tabloului X;
//aici tabloul nu mai este ordonat....e un tablou oarecare


//se imparte vectorul in secvente din ce in ce mai mici, astfel incat
//fiecare secventa sa fie ordonata la un moment dat si interclasata
//cu o alta secventa din vector corespunzatoare. 

#include<stdio.h>
void interclasare(int x[], int p, int m, int u)
{
	int i, j, k, l;

	int z[100];

	i = p; j = m + 1; k = 0;
	while ((i <= m) && (j <= u))
	{
		if (x[i] < x[j])
		{
			z[k] = x[i];
			i++;
			k++;
		}
		else
		{
			z[k] = x[j];
			j++;
			k++;
		}
	}

	if (i <= m)
		for (l = i; l <= m; l++)
		{
			z[k] = x[l];
			k++;
		}

	if (j <= u)
		for (l = j; l <= u; l++)
		{
			z[k] = x[l];
			k++;
		}

	int t = p;
	for (k = 0; k < (u - p) + 1; k++)
		x[t++] = z[k];
}


void mergeSort(int x[], int p, int u)
{
	if (p < u)
	{
		int m = (p + u) / 2;//mijlocul tabloului X
		mergeSort(x, p, m); // se tot imparte tabloul X / 2 recursiv 
		mergeSort(x, m + 1, u);
		interclasare(x, p, m, u);
	}
}

int main() {
	int N = 3, M = 4;
	int T = N + M;
	int x[] = { 1,31,17,2,5,18,9 };

	mergeSort(x, 0, T - 1);//pana la N-1 aici !! pe pozitia x[7] o sa gasiti valori gunoi (-8932932932)

	//afisare vector dupa sortare 

	for (int i = 0; i < T; i++) {
		printf("%d ", x[i]);
	}
	printf("\n");
	return 0;
}
