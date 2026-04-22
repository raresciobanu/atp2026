#include<stdio.h>
#include<stdlib.h>

//Se obtine submultimea de elemente din vector care dau suma maxima.
//Se iau doar elementele pozitive.
//v - multimea primita de elemente
//n - nr elemente multime primita
//sol - submultimea elementelor care dau suma maxima
//nrSol - nr elemente din submultimea rezultat
int sumaMaxima(int* v, int n, int* sol, int* nrSol) {
	*nrSol = 0;
	int max = 0;

	//parcurgem toate elementele din multimea primita
	//si selectam doar elementele pozitive care dau suma maxima la final
	for (int i = 0; i < n; i++)
		if (v[i] >= 0) { //se ia si 0 pentru ca nu afecteaza suma 
			sol[(*nrSol)++] = v[i];
			max += v[i];
		}
	return max;
}

int main() {
	int n, nrSol = 0;
	int* multimeInitiala;
	int* submultimeRezultat;

	printf("Numarul de elemente din multime: "); scanf("%d", &n);

	multimeInitiala = malloc(n * sizeof(int));
	submultimeRezultat = malloc(n * sizeof(int));

	printf("Elementele din multime sunt: ");
	for (int i = 0; i < n; i++)
		scanf("%d", &multimeInitiala[i]);

	int sMax = sumaMaxima(multimeInitiala, n, submultimeRezultat, &nrSol);

	printf("\nSuma maxima este: %d", sMax);
	printf("\nSubmultimea de elemente care formeaza suma maxima: ");

	for (int i = 0; i < nrSol; i++)
		printf("%d ", submultimeRezultat[i]);

	free(submultimeRezultat);
	free(multimeInitiala);

	return 0;
}
