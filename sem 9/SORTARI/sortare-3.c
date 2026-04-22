#include<stdio.h>

void interschimbaValori(int* a, int* b) {
	int aux = *a;
	*a = *b;
	*b = aux;
}

/*
1)	aceasta functie alege ca pivot ultimul element din tablou;
2)	se rearanjează elementele în aşa fel încât, toate elementele care sunt mai mari
decât pivotul merg în partea dreaptă a tabloului. Valorile egale cu pivotul pot sta în orice parte a tabloului. În plus, tabloul poate fi împărţit în părţi care nu au aceeaşi dimensiune (nu sunt egale).
Functia returneaza indexul unde se va imparti tabloul(se va imparti de la indexul pivotului);
*/
int impartire(int tablou[], int stanga, int dreapta)
{
	// pivot (elementul care va fi mutat la pozitia sa corecta in tabloul sortat)
	// practic ultimul element din tablou va fi mutat undeva.... 
	int pivot = tablou[dreapta];

	int i = (stanga - 1); // se pastreaza indexul ultimului element mai mic decât pivotul nostru
	for (int j = stanga; j <= dreapta - 1; j++)
	{
		// daca elementul curent este mai mic decat pivotul 
		if (tablou[j] < pivot)
		{
			i++;	// se mareste indexul celui mai mic element 
			interschimbaValori(&tablou[i], &tablou[j]);
		}
	}
	//se muta pivotul pe pozitia lui corespunzatoare in tablou;
	interschimbaValori(&tablou[i + 1], &tablou[dreapta]);

	return i + 1;
}

/*
tablou --> tabloul care trebuie sortat;
stanga --> Indexul de start;
dreapta --> Indexul de final;
Algoritmul imparte tabloul in bucati(nu neaparat egale) din ce in ce mai mici si dupa care il sorteaza.
*/
void quickSort(int tablou[], int stanga, int dreapta)
{
	if (stanga < dreapta)
	{
		/* pi este indexul de impartire
		practic se calculeaza unde se imparte tabloul(divide et impera)
		*/
		int pi = impartire(tablou, stanga, dreapta);

		quickSort(tablou, stanga, pi - 1); // sorteaza elementele pana la indexul de impartire PI; pentru ca știi deja ca pivotul folosit mai sus e deja pus pe poziția corespunzătoare in tablou…nu mai trebuie sortat încă o dată și el
		quickSort(tablou, pi + 1, dreapta); // sorteaza elementele dupa indexul de impartire PI;
	}
}

void afisareTablou(int tablou[], int N)
{
	int i;
	for (i = 0; i < N; i++) printf("%d ", tablou[i]);
	printf("\n");
}

int main() {
	int tablou[] = { 10, 7, 8, 9, 1, 5 };

	int n = sizeof(tablou) / sizeof(tablou[0]);//asa se poate afla cate elemente are un vector

	quickSort(tablou, 0, n - 1);//n-1 pt elementele sunt stocate in vector de la pozitia 0;

	printf("Vector sortat:\n");

	afisareTablou(tablou, n);

	return 0;
}
