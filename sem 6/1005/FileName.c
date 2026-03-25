#include<stdio.h>
#include<stdlib.h>

#pragma warning(disable:4996)

//216 bytes....213 are el + 3 padding
typedef struct {
	char marca[100];
	float capCilindrica;
	int anFabricatie;
	char culoare[100];
	char clasa;
	float pret;
}masina;


typedef struct {
	int cod;//0 / 1 daca exista firma in fis bin relativ
	int key;

	char nume[100];
	masina masina;
}firma;


void afisare(masina m) {
	printf("marca = %s\n", m.marca);
	printf("capCilindrica = %.2f\n", m.capCilindrica);
	printf("anFabricatie = %d\n", m.anFabricatie);
	printf("culoare = %s\n", m.culoare);
	printf("clasa = %c\n", m.clasa);
	printf("pret = %.2f\n", m.pret);
}

void afisareFirma(firma f) {
	printf("cod = %d\n", f.cod);
	printf("key = %d\n", f.key);
	printf("nume = %s\n\n", f.nume);

	afisare(f.masina);
}

void citire(masina* m) {
	printf("marca = "); gets(m->marca);
	printf("capCilindrica = "); scanf("%f", &m->capCilindrica);
	printf("anFabricatie = "); scanf("%d", &m->anFabricatie);
	printf("culoare = "); scanf("%s", &m->culoare);

	getchar();//eliberare buffer \n introdus mai sus
	printf("clasa = "); scanf("%c", &m->clasa);
	printf("pret = "); scanf("%f", &m->pret);
}

void scriereInFisTxt(masina m) {
	FILE* f = fopen("masina.txt", "w");
	if (f == NULL) {
		printf("Fisierul masina.txt nu s a deschis pt scriere.\n");
	}

	fprintf(f, "%s\n", m.marca);
	fprintf(f, "%.2f\n", m.capCilindrica);
	fprintf(f, "%d\n", m.anFabricatie);
	fprintf(f, "%s\n", m.culoare);
	fprintf(f, "%c\n", m.clasa);
	fprintf(f, "%.2f\n", m.pret);

	fclose(f);
}

void citireDinFisTxt(masina* m) {
	FILE* f = fopen("masina.txt", "r");
	if (f == NULL) {
		printf("Fisierul masina.txt nu s a deschis pt citire.\n");
	}

	fgets(m->marca, 100, f);
	fscanf(f, "%f\n", &m->capCilindrica);
	fscanf(f, "%d\n", &m->anFabricatie);
	fscanf(f, "%s\n", &m->culoare);
	fscanf(f, "%c\n", &m->clasa);
	fscanf(f, "%f\n", &m->pret);

	fclose(f);
}

void scriereInFisBinar(masina m) {
	FILE* f = fopen("masina.bin", "wb");
	if (f == NULL) {
		printf("Fisierul masina.bin nu s a deschis pt scriere binara.\n");
	}

	fwrite(&m, sizeof(m), 1, f);

	fclose(f);
}


void citireDinFisBinar(masina* m) {
	FILE* f = fopen("masina.bin", "rb");
	if (f == NULL) {
		printf("Fisierul masina.bin nu s a deschis pt citire binara.\n");
	}

	fread(m, sizeof(masina), 1, f);

	fclose(f);
}

int nrFirmeDinFisBinar(FILE* f) {
	int pozCurenta = ftell(f);

	fseek(f, 0, SEEK_END);

	int nrFirme = ftell(f) / sizeof(firma);

	fseek(f, pozCurenta, SEEK_SET);

	return nrFirme;
}

void populareFisRelativFirma(firma f) {
	FILE* file = fopen("firma.bin", "rb");
	if (file == NULL) {
		file = fopen("firma.bin", "wb");
	}
	else {
		fclose(file);

		file = fopen("firma.bin", "ab");
		if (file == NULL) {
			printf("firma.bin nu a putut fi deschis pt scriere binara relativa\n");
		}
	}

	if (f.key >= 0) {
		int nrFirme = nrFirmeDinFisBinar(file);
		if (f.key >= nrFirme) {
			//alocam memorie noua daca cheia introdusa >= nr de firme din fisier

			fseek(file, 0, SEEK_END);//cand fis e gol si te pozitionezi la sf => te pozitionezi la inceputul fisierului.

			firma temp1;
			temp1.cod = 0;
			for (int i = 0; i < (f.key + 1) - nrFirme; i++) {
				fwrite(&temp1, sizeof(firma), 1, file);
			}

			//sau in loc de for(le scrii pe toate odata): fwrite(&p, sizeof(firma), (key + 1) - nrFirme, file);
		}

		//se pozitioneaza cursorul la adresa key * sizeof(firma)
		fseek(file, f.key * sizeof(firma), SEEK_SET);

		firma temp2;
		//se citeste firma de la adreasa: key * sizeof(firma)
		fread(&temp2, sizeof(firma), 1, file);

		if (temp2.cod == 1) {
			printf("La cheia introdusa exista deja o firma salvata. Nu se mai poate adauga unul.\n");
		}
		else {
			//se pozitioneaza cursorul la adresa key * sizeof(firma)
			fseek(file, f.key * sizeof(firma), SEEK_SET);

			//se scrie o firma in fisier la adresa key * sizeof(firma)
			fwrite(&f, sizeof(firma), 1, file);
		}
	}
	else {
		printf("Key trebuie sa fie >=0!\n");
	}

	fclose(file);
}

firma citireDinFisRelativ(int key) {
	FILE* file = fopen("firma.bin", "rb");
	if (file == NULL) {
		printf("Fisierul firma.bin nu s a deschis.\n\n");
	}

	firma f;

	//se pozitioneaza cursorul la adresa key * sizeof(firma)
	fseek(file, key * sizeof(firma), SEEK_SET);

	//se citeste firma de la adresa: key * sizeof(firma)
	fread(&f, sizeof(firma), 1, file);

	fclose(file);

	if (f.cod == 0) {
		printf("La cheia introdusa nu exista nicio firma. NU se poate afisa nimic.\n");
	}
	else {
		return f;
	}
}

int main() {
	masina m1;
	strcpy(m1.marca, "Audi");
	m1.capCilindrica = 1.9;
	m1.anFabricatie = 2012;
	strcpy(m1.culoare, "verde");
	m1.clasa = 'A';
	m1.pret = 9890.323;

	printf("\n\n===masina m1 afisare===\n\n");
	afisare(m1);

	//printf("\n\n===masina m2 citire&afisare===\n\n");
	//masina m2;
	//citire(&m2);
	//printf("\n\n");
	//afisare(m2);


	printf("\n\n===masina m3 afisare&citire fis text===\n\n");
	masina m3;
	scriereInFisTxt(m1);
	citireDinFisTxt(&m3);
	afisare(m3);


	printf("\n\n===masina m4 afisare&citire fis binar===\n\n");
	masina m4;
	scriereInFisBinar(m1);
	citireDinFisBinar(&m4);
	afisare(m4);


	printf("\n\n===firma 1 afisare===\n\n");
	firma f1;
	f1.masina = m1;
	f1.cod = 1;
	printf("cheie firma = "); scanf("%d", &f1.key);

	strcpy(f1.nume, "Firma 1");
	afisareFirma(f1);


	printf("\n\n===firma 1 populare===\n\n");
	populareFisRelativFirma(f1);

	printf("\n\n===firma 2 afisare din fis relativ===\n\n");

	firma f2;
	f2 = citireDinFisRelativ(f1.key);
	afisareFirma(f2);

	return 0;
}