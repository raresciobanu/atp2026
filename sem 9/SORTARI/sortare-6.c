#include<stdio.h> 
#include<stdlib.h>
//Sortare prin metoda numararii
//Prin aceasta metoda se mai construieste un vector (cu aceeasi dimensiune ca si vectorul original)
//care va contine pozitiile sortate ale elementelor din vectorul original.
//Fie „a” vectorul original si „num” vectorul de pozitii, num[i] va contine pozitia finala a elementului a[i].
//Pozitia finala a fiecarui element este data de numarul de elemente mai mici decat el din vector.
//Daca avem doua elemente mai mici decat a[i] atunci acesta se afla pe a 3-a pozitie
//Algoritmul va numara cate numere sunt mai mici decat elementul curent. 
void sortareNumarare(int a[], int n) {
	//vectorul num este vectorul care va contine pozitiile
	//vectorul aux este cel folosit pentru pozitionarea elementelor din „a”
	//acesti vectori sunt alocati dinamic pentru a avea dimensiunea vectorului primit „a” ….sau se putea lucra si fara pointeri declarand vectorii „num” si „aux”:
	//int num[100],aux[100]….
	int* num, * aux;

	num = calloc(n, sizeof(int)); // alocam si initializam cu 0 fiecare element din vector..calloc!=malloc…remember?
	aux = malloc(n * sizeof(int)); //e doar un vector temporar…folosit pentru interschimbarea valorilor
	
	//calculam numarul de elemente mai mici pentru combinatia pozitiilor i si j
	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
			if (a[j] < a[i])
				num[i]++;
			else
				num[j]++;

	//punem in aux elementele din a la pozitiile specificate in num 
	for (int i = 0; i < n; i++)
		aux[num[i]] = a[i];

	//punem in vectorul original elementele pozitionate 
	for (int i = 0; i < n; i++)
		a[i] = aux[i];

	//eliberam din HEAP vectorii num si aux
	free(aux);
	free(num);
}

int main() {
	int arr[] = { 10, 7, 8, 9, 1, 5 };

	int n = sizeof(arr) / sizeof(arr[0]);

	sortareNumarare(arr, n);

	printf("Array-ul sortat: ");
	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);

	return 0;
}
