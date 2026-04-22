#include<stdio.h>

//Sortare prin metoda selectiei
//Metoda selectiei presupune parcurgerea vectorului de la primul element pana la penultimul element.
//Pentru fiecare pozitie i din cadrul parcurgerii se cauta elementul minim din cadrul pozitiilor ramase(de la i + 1 pana la n).
//Se face interschimbarea intre pozitia curenta i si elementul minim gasit in pozitiile ramase din vector.

void sortareSelectie(int a[], int n) {
	int aux;
	int poz; //utilizat pentru salvarea pozitiei elementului minim gasit
	for (int i = 0; i < n - 1; i++) { //parcurgem vectorul de la primul element pana la penultimul
		poz = i;
		//parcurgem restul vectorului de la i + 1 pana la final pentru a gasi pozitie elementului de valoare minima
		for (int j = i + 1; j < n; j++)
			if (a[j] < a[poz])
				poz = j;

		//facem interschimbarea intre pozitia curenta i si pozitia elementului de valoare minima
		aux = a[poz];
		a[poz] = a[i];
		a[i] = aux;
	}
}
int main() {
	int arr[] = { 10, 7, 8, 9, 1, 5 };

	int n = sizeof(arr) / sizeof(arr[0]);

	sortareSelectie(arr, n);

	printf("Array-ul sortat: ");

	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);

	return 0;
}
