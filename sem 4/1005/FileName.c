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

void scrieCameraInFisierTxt(struct Camera c, FILE* fisOut) {
	fprintf(fisOut, "%d\n", c.nrPaturi);
	fprintf(fisOut, "%d\n", c.tip);
	fprintf(fisOut, "%.2f\n", c.pret);
	fprintf(fisOut, "%s\n", c.vedere);
	fprintf(fisOut, "%d\n", c.areAC);
}

void citireCameraDinFisierTxt(struct Camera* c, FILE* fisIn) {
	fscanf(fisIn, "%d", &c->nrPaturi);

	fscanf(fisIn, "%d", &c->tip);

	fscanf(fisIn, "%f", &c->pret);

	fgetc(fisIn);//pt a elibera bufferul de \n -ul de mai sus

	fgets(c->vedere, 100, fisIn);

	int temp;
	fscanf(fisIn, "%d", &temp);
	c->areAC = temp;
}


void scrieHotelInFisierTxt(struct Hotel h, FILE* fisOut) {
	fprintf(fisOut, "%s\n", h.nume);
	fprintf(fisOut, "%.2f\n", h.rating);
	fprintf(fisOut, "%d\n", h.nrCamere);

	for (int i = 0; i < h.nrCamere; i++) {
		scrieCameraInFisierTxt(h.camere[i], fisOut);
	}
}

void citireHotelDinFisierTxt(struct Hotel* h, FILE* fisIn) {
	if (h->nume != NULL) {
		free(h->nume); //evitare memory leaks
	}

	char aux[100];
	fgets(aux, 100, fisIn);
	h->nume = (char*)malloc(strlen(aux) + 1);
	strcpy(h->nume, aux);

	fscanf(fisIn, "%f", &h->rating);
	fscanf(fisIn, "%d", &h->nrCamere);

	for (int i = 0; i < h->nrCamere; i++) {
		citireCameraDinFisierTxt(&h->camere[i], fisIn);
	}
}

void scrieCameraInFisierBinar(struct Camera c, FILE* fisBinOut) {
	//functia fwrite - primeste ca input ===> fwrite(addressData, sizeData, numbersData, pointerToFile);
	//addressData - adresa variabilei citite (cu "&" in fata)
	//sizeData - dimensiunea variabilei salvate (sizeof)
	//numbersData - numarul de variabile salvate
			//int arr[3] = {101, 203, 303};
			//
			//fwrite(arr, sizeof(int), 2, fp); //va scrie primele 2 elemente din vector
	//pointerToFile - fisierul unde se salveaza variabila

	//DACA scrierea are erori atunci fwrite va retuna un numar mai mic decat variabila numbersData;


	//fwrite(&c, sizeof(c), 1, fisBinOut); //can nu ai pointeri poti si asa
	//sau scrii membru cu membru

	fwrite(&c.nrPaturi, sizeof(c.nrPaturi), 1, fisBinOut);
	fwrite(&c.tip, sizeof(c.tip), 1, fisBinOut);
	fwrite(&c.pret, sizeof(c.pret), 1, fisBinOut);
	fwrite(&c.vedere, sizeof(c.vedere), 1, fisBinOut);
	fwrite(&c.areAC, sizeof(c.areAC), 1, fisBinOut);
}

void citireCameraDinFisierBinar(struct Camera* c, FILE* fisBinIn) {
	//alternativ putem face ca mai jos daca structura noastra nu ar contine pointeri
	//fread(&m, sizeof(c), 1, fisBinIn);

	//sau:
	fread(&c->nrPaturi, sizeof(c->nrPaturi), 1, fisBinIn);
	fread(&c->tip, sizeof(c->tip), 1, fisBinIn);
	fread(&c->pret, sizeof(c->pret), 1, fisBinIn);
	fread(&c->vedere, sizeof(c->vedere), 1, fisBinIn);
	fread(&c->areAC, sizeof(c->areAC), 1, fisBinIn);
}

void scrieHotelInFisierBinar(struct Hotel h, const char* numeFisier) {
	FILE* fisierHoteluriOutBinar = fopen(numeFisier, "wb");
	if (fisierHoteluriOutBinar == NULL) {
		printf("EROARE: Nu s-a putut deschide pentru scriere fisierul %s", *numeFisier);
		exit(300);
	}

	//la siruri de caractere e putin diferit
	int dim = strlen(h.nume) + 1;
	fwrite(&dim, sizeof(dim), 1, fisierHoteluriOutBinar);
	fwrite(h.nume, dim, 1, fisierHoteluriOutBinar);


	fwrite(&h.rating, sizeof(h.rating), 1, fisierHoteluriOutBinar);
	fwrite(&h.nrCamere, sizeof(h.nrCamere), 1, fisierHoteluriOutBinar);

	for (int i = 0; i < h.nrCamere; i++) {
		scrieCameraInFisierBinar(h.camere[i], fisierHoteluriOutBinar);
	}

	fclose(fisierHoteluriOutBinar);
}

void citireHotelDinFisierBinar(struct Hotel* h, const char* numeFisier) {
	FILE* fisierHoteluriInBinar = fopen(numeFisier, "rb");
	if (fisierHoteluriInBinar == NULL) {
		printf("EROARE: Nu s-a putut deschide pentru citire fisierul %s", *numeFisier);
		exit(300);
	}

	if (h->nume != NULL) {
		free(h->nume); //evitare memory leaks
	}

	//la siruri de caractere e putin diferit
	char aux[100];
	int dim = 0;
	fread(&dim, sizeof(dim), 1, fisierHoteluriInBinar);
	fread(aux, dim, 1, fisierHoteluriInBinar);

	h->nume = (char*)malloc(strlen(aux) + 1);
	strcpy(h->nume, aux);

	fread(&h->rating, sizeof(h->rating), 1, fisierHoteluriInBinar);
	fread(&h->nrCamere, sizeof(h->nrCamere), 1, fisierHoteluriInBinar);

	for (int i = 0; i < h->nrCamere; i++) {
		citireCameraDinFisierBinar(&h->camere[i], fisierHoteluriInBinar);
	}

	fclose(fisierHoteluriInBinar);
}

// const int * --> ce se afla la zona de memorie catre care pointeaza pointerul este constanta.
// int * const --> var pointer este constanta (nu poti altera adresa catre care pointeaza pointerul).
// const int * const -> un pointer constant ce pointeaza catre o zona de memorie constanta

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


	//struct Hotel h2;
	//h2.nume = NULL;// initializati pointerii tot timpul;

	//citireHotelConsola(&h2);

	//printf("\n\n======Afisare Hotel h2======\n\n");

	//afisareHotelConsola(h2);


	printf("\n\n---scriere in fisiere---\n\n");
	printf("\n\n---scriere HOTELURI in fisier text---\n\n");

	// scriere in fisiere
	//w-creare fisier si scriere in el, daca exista fisierul exista se sterg toate informatiile din el
	//wb-este "w" in mod binar
	//r-citire din fisier, daca fisierul nu exista se intoarce NULL la fopen()
	//rb-este "r" in mod binar, daca fisierul nu exista se intoarce NULL la fopen()
	//a-adaugare informatii la sf fisierului, daca NU exista fisierul se face unul nou
	//ab- este "a" in mod binar
	//r+ sau rb+ - fisier deschis pentru citire si scriere/ citire si scriere in mod binar, daca fisierul nu exista se intoarce NULL la fopen()
	//w+ sau wb+ - fisier deschis pentru citire si scriere in mod binar.
	//a+ si ab+ - fisier deschis pentru citire si adaugare la final

	FILE* fisierHotelOut = fopen("hoteluri.txt", "w");
	if (fisierHotelOut == NULL) {
		printf("EROARE: Nu s-a putut deschide pentru scriere fisierul hoteluri.txt");
		exit(300);
	}

	scrieHotelInFisierTxt(h1, fisierHotelOut);

	//important! inchideti fisierul dupa ce terminati de lucrat in el
	fclose(fisierHotelOut);

	FILE* fisierHotelIn = fopen("hoteluri.txt", "r");
	if (fisierHotelIn == NULL) {
		printf("EROARE: Nu s-a putut deschide pentru citire fisierul hoteluri.txt");
		exit(404);
	}

	struct Hotel h3;
	h3.nume = NULL;

	citireHotelDinFisierTxt(&h3, fisierHotelIn);

	printf("\n\n======Afisare Hotel h3======\n\n");
	afisareHotelConsola(h3);



	//fisire BINARE
	printf("\n\n---scriere HOTELURI in fisier binar---\n\n");

	scrieHotelInFisierBinar(h1, "hoteluri.bin");
	
	struct Hotel h4;
	h4.nume = NULL;
	citireHotelDinFisierBinar(&h4, "hoteluri.bin");


	printf("\n\n======Afisare Hotel h4======\n\n");
	afisareHotelConsola(h4);




	printf("\n\n======SizeOf======\n\n");
	printf("size Animal = %d\n", sizeof(a));
	printf("size Camera = %d\n", sizeof(c1));
	printf("size Hotel = %d\n", sizeof(h1));

	return 0;
}