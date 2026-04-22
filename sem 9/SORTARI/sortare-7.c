#include<stdio.h>
//Sortare prin metoda interschimbarii
//Aceasta metoda presupune verificarea a cate doua elemente. Daca ordinea nu este cea corecta se produce o interschimbare intre aceste doua elemente.
//Aceasta metoda este similara cu metoda selectiei, doar ca la metoda selectiei se cauta pozitia elementului de valoare minima(pentru sortare crescatoare) si se producea o singura interschimbare. 
//Aici se va produce cate o interschimbare de fiecare data cand valorile nu sunt in ordinea corecta.
void sortareInterschimbare(int a[], int n) {
	int aux;
	for (int i = 0; i < n - 1; i++) //parcurgem pana la penultimul element
		for (int j = i + 1; j < n; j++) //comparam urmatoarele elemente de dupa pozitia i cu elementul de pe pozitia i
			//se face interschimbare de fiecare data cand gasim un element j mai mic decat i

			//astfel aducem elementul minim la finalul iteratiilor 
			if (a[i] > a[j]) {
				aux = a[i];
				a[i] = a[j];
				a[j] = aux;
			}
}
int main() {
	int arr[] = { 10, 7, 8, 9, 1, 5 };

	int n = sizeof(arr) / sizeof(arr[0]);

	sortareInterschimbare(arr, n);

	printf("Array-ul sortat: ");
	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);

	return 0;
}

