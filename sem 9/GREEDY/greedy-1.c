#include<stdio.h>
#include<stdlib.h>

typedef struct {
	float valoare; float cost;
} Obiect;

//Problema rucsacului in varianta continua
//=>Se ocupa intreaga capacitate a rucsacului
//obiectele adaugate in rucsac pot fi fractionate
//Pentru un algoritm eficient obiectele sunt deja sortate descrescator
//dupa castigul adus de fiecare obiect.
//q - capacitatea totala a rucsacului
//n - nr. obiecte
//ob - lista de obiecte
//sol - vector care marcheaza obiectele introduse in rucsac
void rucsacContinuu(float q, int n, Obiect* ob, float* sol) {
	int i;

	//parcurgem pana trecem prin toate obiectele din lista sau pana
	//cand capacitatea rucsacului este 0
	for (i = 0; i < n && q > 0; i++) {
		if (q >= ob[i].cost) {
			sol[i] = 1; //marcam obiectul ca introdus in rucsac
			q -= ob[i].cost;
		}
		else {
			//daca capacitatea este mai mica decat costul obiectului,
			//acesta se fractioneaza (doar pentru varianta continua)
			sol[i] = q / ob[i].cost;
			q = 0;

			//pentru eventualele obiecte neprelucrate in for se da valoarea 0
			//in vectorul solutie, deoarece acestea nu au fost puse in rucsac 
			for (int j = i + 1; j < n; j++)
				sol[j] = 0;
		}
	}
}


int main() {
	int n = 10;

	Obiect* obiecte = malloc(n * sizeof(Obiect));
	obiecte[0].cost = 1; obiecte[0].valoare = 3;
	obiecte[1].cost = 2; obiecte[1].valoare = 2;
	obiecte[2].cost = 3; obiecte[2].valoare = 1;
	obiecte[3].cost = 4; obiecte[3].valoare = 4;
	obiecte[4].cost = 5; obiecte[4].valoare = 5;
	obiecte[5].cost = 6; obiecte[5].valoare = 3;
	obiecte[6].cost = 7; obiecte[6].valoare = 2;
	obiecte[7].cost = 8; obiecte[7].valoare = 7;
	obiecte[8].cost = 9; obiecte[8].valoare = 1;
	obiecte[9].cost = 10; obiecte[9].valoare = 8;

	//prelucrare preliminara
	//sortarea obiectelor in mod descrescator
	Obiect aux;
	float* obiecteAcceptate;
	float q;

	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
			if (obiecte[i].valoare / obiecte[i].cost < obiecte[j].valoare / obiecte[j].cost)	//castig unitar
			{
				aux = obiecte[i];
				obiecte[i] = obiecte[j];
				obiecte[j] = aux;
			}


	printf("Capacitatea rucsacului: "); scanf("%f", &q);

	obiecteAcceptate = malloc(n * sizeof(float));

	rucsacContinuu(q, n, obiecte, obiecteAcceptate); 
	
	double castig = 0;

	for (int i = 0; i < n; i++) {
		castig += obiecte[i].valoare * obiecteAcceptate[i];
		printf("%d: c = %.2f	v = %.2f bucati de obiecte adaugate = %.2f; castig =% .2f\n", i + 1, obiecte[i].cost, obiecte[i].valoare, obiecteAcceptate[i], castig);
	}

	free(obiecte);

	return 0;
}
