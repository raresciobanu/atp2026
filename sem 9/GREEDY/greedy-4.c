#include<stdio.h>

//Se face plata unei sume cu bancnotele furnizate intr-o lista.
//Printre acestea se afla si bancnota unitate.
//Se doreste sa se faca plata cu un numar cat mai mic de bancnote.
//Lista de bancnote contine valorile acestora in ordine descrescatoare.
//suma - suma de platit
//tipuriBancnote - bancnotele disponibile pentru plata
//n - nr de tipuri de bancnote
//sol - vector care retine cate bancnote s-au folosit din fiecare tip 
void plataSumei(int suma, int* tipuriBancnote, int n, int* sol) {
	//parcurgem bancnotele de la cea mai mare valoare la cea mai mica 
	for (int i = 0; i < n; i++) {
		sol[i] = suma / tipuriBancnote[i];
		suma = suma % tipuriBancnote[i]; //suma ramasa reprezinta restul
	}
}
int main() {
	int n = 7;
	int valoriBancnote[] = { 500, 200, 100, 50, 10, 5, 1 };
	int bancnoteUtilizate[] = { 0, 0, 0, 0, 0, 0, 0 };

	int sumaDePlata;
	printf("Suma de plata: "); scanf("%d", &sumaDePlata);

	plataSumei(sumaDePlata, valoriBancnote, n, bancnoteUtilizate);

	printf("\nBanconte utilizate:\n");

	for (int i = 0; i < n; i++)
		printf("%d - %d Subtotal: %d\n", valoriBancnote[i], bancnoteUtilizate[i], valoriBancnote[i] * bancnoteUtilizate[i]);

	return 0;
}
