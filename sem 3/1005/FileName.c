#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//pt a ignora _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

//4 bytes
enum TipCamera {
	SINGLE,
	DUBLA,
	DELUXE,
	VIP,
	PENTHOUSE,
};

//100bytes
union Animal {
	char culoare[100]; //100bytes
	int varsta; //4bytes
	float kg; //4bytes
};

//teoretic 113 bytes, dar in realitate 116 bytes, pentru a-l alinia pe bool
struct Camera {
	int nrPaturi; //4 bytes
	enum TipCamera tip; //4 bytes
	float pret; //4 bytes
	bool areAC; //1 bytes
	char vedere[100]; //100 bytes
};

// 11616 bytes
struct Hotel {
	char* nume; // 8 bytes - depinde - CPU x32 -> 4 Bytes - x64 - 8 bytes
	float rating; //4 bytes
	int nrCamere; //4 bytes
	struct Camera camere[100]; //11600  bytes
};

void afisareCameraConsola(struct Camera c) {
	printf("Nr paturi: %d\n", c.nrPaturi);
	printf("Tip Camera: %d\n", c.tip);
	printf("Pret: %.2f\n", c.pret);
	printf("Vedere: %s\n", c.vedere);
	printf("Are AC: %d\n", c.areAC);
}

void citireCameraConsola(struct Camera* c) {
	printf("Nr paturi: "); scanf("%d", &c->nrPaturi);

	printf("Tip Camera: "); scanf("%d", &c->tip);

	printf("Pret: "); scanf("%f", &c->pret);

	getchar(); //pt a elibera bufferul de \n -ul de mai sus
	 
	printf("Vedere: "); gets(c->vedere);

	int temp;
	printf("Are AC: "); scanf("%d", &temp);
	c->areAC = temp;
}

void afisareHotelConsola(struct Hotel h) {
	printf("Nume: %s\n", h.nume);
	printf("Rating: %.2f\n", h.rating);
	printf("Nr camere: %d\n", h.nrCamere);

	printf("\nCamere hotel:\n\n");
	for (int i = 0; i < h.nrCamere; i++) {
		afisareCameraConsola(h.camere[i]);
		printf("\n\n");
	}
}

void citireHotelConsola(struct Hotel* h) {
	if (h->nume != NULL) {
		free(h->nume); //evitare memory leaks
	}

	char aux[100];
	printf("Nume: "); gets(aux);
	h->nume = (char*)malloc(strlen(aux) + 1);
	strcpy(h->nume, aux);

	printf("Rating: "); scanf("%f", &h->rating);
	printf("Nr camere: "); scanf("%d", &h->nrCamere);

	printf("Camere:\n");
	for (int i = 0; i < h->nrCamere; i++) {
		citireCameraConsola(&h->camere[i]);
		printf("\n\n");
	}
}

int main() {
	// dif union vs struct?
	// union foloseste aceeasi zona de memorie pt toti membrii acelui union
	// struct fiecare membru are zona lui specifica de memorie

	union Animal a;

	a.varsta = 97;//97 in ASCII este 'a'
	printf("varsta = %d\n", a.varsta);
	printf("culoare = %s\n", a.culoare);

	printf("\n\n======Camera c1======\n\n");

	struct Camera c1;
	c1.areAC = false;
	c1.nrPaturi = 2;
	c1.pret = 868.99;
	c1.tip = DUBLA;
	strcpy(c1.vedere, "la plaja");

	afisareCameraConsola(c1);


	//printf("\n\n======Citire Camera c2======\n\n");
	//struct Camera c2;
	//citireCameraConsola(&c2);

	//printf("\n\n======Afisare Camera c2======\n\n");
	//afisareCameraConsola(c2);


	printf("\n\n======Hotel======\n\n");
	struct Hotel h1;
	//h1.nrCamere = 2;
	h1.nrCamere = 1;
	h1.camere[0] = c1;
	//h1.camere[1] = c2;
	h1.rating = 9.45;

	h1.nume = (char*)malloc(strlen("Hotel_1") + 1);
	strcpy(h1.nume, "Hotel_1");

	afisareHotelConsola(h1);

	printf("\n\n======Citire Hotel h2======\n\n");


	struct Hotel h2;
	h2.nume = NULL;// initializati pointerii tot timpul;

	citireHotelConsola(&h2);

	printf("\n\n======Afisare Hotel h2======\n\n");

	afisareHotelConsola(h2);

	printf("\n\n======SizeOf======\n\n");
	printf("size Animal = %d\n", sizeof(a));
	printf("size Camera = %d\n", sizeof(c1));
	printf("size Hotel = %d\n", sizeof(h1));

	return 0;
}