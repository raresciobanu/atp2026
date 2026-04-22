#include<stdio.h>
//Sortare prin metoda bulelor
//Primim ca parametrii vectorul si numarul de elemente din vector
//Se compara pe rand fiecare doua elemente consecutive, de la prima pana la ultima pereche din vector.
//Daca ordinea a doua elemente consecutive nu este cea corecta se face interschimbarea.
//Daca la parcurgerea vectorului s-a produs cel putin o interschimbare se repeta procesul.

void sortareBule(int a[], int n) {
	bool gata = false; //variabila cu care verificam daca mai parcurgem inca o data vectorul sau nu

	int aux;

	while (!gata) {
		gata = true;
		for (int i = 0; i < n - 1; i++)
			if (a[i] > a[i + 1]) {
				aux = a[i];
				a[i] = a[i + 1];
				a[i + 1] = aux;
				gata = false; //s-a produs cel putin o interschimbare, deci marcam faptul ca algoritmul nu este gata si trebuie sa se mai faca cel putin o parcurgere a vectorului
			}
	}
}
int main() {
	int arr[] = { 10, 7, 8, 9, 1, 5 };

	int n = sizeof(arr) / sizeof(arr[0]);

	sortareBule(arr, n);

	printf("Array-ul sortat: ");

	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);

	return 0;
}
