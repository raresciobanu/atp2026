#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<malloc.h>

//I: solutia (x), pasul curent (i), numarul de tipuri (n), suma de plata (s)
//   suma curenta (c)
//E: 1 daca valoarea este acceptabila, 0 daca nu e acceptabila
int posibil(int* x, int i, int n, int s, int c)
{
	int rez;
	if (i == n - 1)
		rez = (s == c) ? 1 : 0;
	else
		rez = (s >= c) ? 1 : 0;
	return rez;
}

//I: tipuri (t), solutia (x), numarul de tipuri (n), numarul de solutii (ns)
void retine(int* t, int* x, int n, int ns)
{
	int i, s;   s = 0;
	printf("\n\nSolutia numarul %d", ns);
	for (i = 0; i < n; i++)  printf("\n %3d * %2d = %4d, suma=%4d", t[i], x[i], t[i] * x[i], s += t[i] * x[i]);
}

//Plata unei sume
//I: suma, suma curenta (crt), tipuri (t), cantitati (nr), numar de tipuri (n)
//   numarul de solutii gasite (ns), pasul curent (i), solutia (x)
//E: numarul de solutii
int plata(int suma, int crt, int* t, int* nr, int n, int ns, int i, int* x)
{
	int j;
	if (i == n)
		retine(t, x, n, ++ns);
	else
	{
		for (j = 0; j <= nr[i]; j++)
		{
			x[i] = j;
			crt += t[i] * j;
			if (posibil(x, i, n, suma, crt))
				ns = plata(suma, crt, t, nr, n, ns, i + 1, x);
			crt -= t[i] * j;
		}
	}
	return ns;
}

int main() {
	int i, n, x[20], suma;
	int t[20] = { 500, 200, 100, 50, 10, 5, 1 };
	int nr[20] = { 3, 6, 2, 5, 4, 3, 7 };
	n = 7;
	//int t[20], nr[20];
	//printf("introduceti numarul de bacnote disponibile:"); scanf("%d", &n);
	//printf("Introduceti tipurile de bacnote si numarul de bacnote din fiecare tip\n");
	//for (i = 0; i < n; i++)
	//{
	//	printf("t[%d]=", i + 1); scanf("%d", &t[i]);
	//	printf("nr[%d]=", i + 1); scanf("%d", &nr[i]);
	//}
	printf("Introduceti suma de plata:"); scanf("%d", &suma);
	printf("\nNumarul de solutii este %d:", plata(suma, 0, t, nr, n, 0, 0, x));
	return 0;
}
