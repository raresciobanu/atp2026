#include<stdio.h>
#include<stdlib.h>

#pragma warning(disable:4996)

//caz fis binar secvential
//120bytes - 3 bytes in plus padding pt acel char
typedef struct {
	char nume[100];
	int anInfiintare;
	double venituri;
	int nrAngajati;
	char etaje;//'4'/'5'/'8'...
} muzeu;

typedef struct {
	int zi;
	int luna;
	int an;
}data;

typedef struct {
	int cod; //0/1
	int key;

	char nume[100];
	data dataPrimire;
	float valoare;
} echipament;


void citire(muzeu* m) {
	printf("nume = "); gets(m->nume);
	printf("an infiintare = "); scanf("%d", &m->anInfiintare);
	printf("venituri = "); scanf("%lf", &m->venituri);
	printf("nr angajati = "); scanf("%d", &m->nrAngajati);

	getchar();//elibereaza buffer \n de la citirea de mai sus
	printf("etaje = "); scanf("%c", &m->etaje);
}

void afisare(muzeu m) {
	printf("nume = %s\n", m.nume);
	printf("an infiintare = %d\n", m.anInfiintare);
	printf("venituri = %.2lf\n", m.venituri);
	printf("nr angajati = %d\n", m.nrAngajati);
	printf("etaje = %c\n", m.etaje);
}

void scriereFisText(muzeu m) {
	FILE* f = fopen("muzeu.txt", "w");
	if (f == NULL) {
		printf("muzeu.txt nu a putut fi deschis pt scriere\n");
	}

	fprintf(f, "%s\n", m.nume);
	fprintf(f, "%d\n", m.anInfiintare);
	fprintf(f, "%.2lf\n", m.venituri);
	fprintf(f, "%d\n", m.nrAngajati);
	fprintf(f, "%c\n", m.etaje);

	fclose(f);
}

void citireFisText(muzeu* m) {
	FILE* f = fopen("muzeu.txt", "r");
	if (f == NULL) {
		printf("muzeu.txt nu a putut fi deschis pt citire\n");
	}

	fgets(m->nume, 100, f);
	fscanf(f, "%d", &m->anInfiintare);
	fscanf(f, "%lf", &m->venituri);
	fscanf(f, "%d", &m->nrAngajati);

	fgetc(f);//elibereaza buffer \n de la citirea de mai sus
	fscanf(f, "%c", &m->etaje);

	fclose(f);
}

void scriereFisBinar(muzeu m) {
	FILE* f = fopen("muzeu.bin", "wb");
	if (f == NULL) {
		printf("muzeu.bin nu a putut fi deschis pt scriere binara\n");
	}

	fwrite(&m, sizeof(m), 1, f); //putem sa scriem asa pt ca nu avem pointeri

	fclose(f);
}

void citireFisBinar(muzeu* m) {
	FILE* f = fopen("muzeu.bin", "rb");
	if (f == NULL) {
		printf("muzeu.bin nu a putut fi deschis pt citire binara\n");
	}

	fread(m, sizeof(muzeu), 1, f); //putem sa citim asa pt ca nu avem pointeri

	fclose(f);
}

void afisareData(data d) {
	printf("data = %d/%d/%d\n", d.zi, d.luna, d.an);
}

void afisareEchipament(echipament e) {

	printf("cod = %d\n", e.cod);
	printf("key = %d\n", e.key);
	printf("key = %s\n", e.nume);
	printf("key = %.2f\n", e.valoare);
	afisareData(e.dataPrimire);
}

int nrEchipamenteInFisBinar(FILE* f) {
	int pozCurenta = ftell(f);

	fseek(f, 0, SEEK_END);

	int nrEchipamente = ftell(f) / sizeof(echipament);

	fseek(f, pozCurenta, SEEK_SET);

	return nrEchipamente;
}

void populareFisBinarRelativ(echipament e) {
	FILE* f = fopen("echipament.bin", "rb");
	if (f == NULL) {
		f = fopen("echipament.bin", "wb");
	}
	else {
		fclose(f);

		f = fopen("echipament.bin", "ab");
		if (f == NULL) {
			printf("echipament.bin nu a putut fi deschis pt scriere binara relativa\n");
		}
	}

	if (e.key >= 0) {

		int nrEchipamente = nrEchipamenteInFisBinar(f);
		if (e.key >= nrEchipamente) {
			//alocam memorie noua daca cheia introdusa >= nr de echipamente din fisier

			fseek(f, 0, SEEK_END);//cand fis e gol si te pozitionezi la sf => te pozitionezi la inceputul fisierului.

			echipament temp;
			temp.cod = 0;

			for (int i = 0; i < (e.key + 1) - nrEchipamente; i++) {
				fwrite(&temp, sizeof(echipament), 1, f);
			}

			//sau in loc de for(le scrii pe toate odata): 
			// fwrite(&x, sizeof( echipament), (key + 1) - nrEchipamente, f);
		}

		//se pozitioneaza cursorul la adresa key * sizeof(echipament)
		fseek(f, e.key * sizeof(echipament), SEEK_SET);

		echipament temp;
		//se citeste echipamentul de la adreasa: key * sizeof(echipament)
		fread(&temp, sizeof(echipament), 1, f);

		if (temp.cod == 1) {
			printf("La cheia introdusa exista deja un echipament salvat. Nu se mai poate adauga unul.\n");
		}
		else {
			//se pozitioneaza cursorul la adresa key * sizeof(echipament)
			fseek(f, e.key * sizeof(echipament), SEEK_SET);

			//se scrie echipamentul in fisier la adresa key * sizeof(echipament)
			fwrite(&e, sizeof(echipament), 1, f);
		}
	}
	else {
		printf("key trebuie sa fie >= 0\n");
	}

	fclose(f);
}


int main() {
	muzeu m1;
	//citire(&m1);

	printf("\n\n===afisare m1 ===\n\n");

	m1.anInfiintare = 2000;
	m1.etaje = '8';
	m1.nrAngajati = 55;
	m1.venituri = 6755.67645;

	strcpy(m1.nume, "muzeul nr 1");

	afisare(m1);



	printf("\n\n===afisare si citire fis txt -  m2 ===\n\n");
	scriereFisText(m1);

	muzeu m2;
	citireFisText(&m2);
	afisare(m2);


	printf("\n\n===afisare si citire fis bin -  m3 ===\n\n");
	muzeu m3;
	scriereFisBinar(m1);
	citireFisBinar(&m3);

	afisare(m3);

	printf("\n\n===afisare echipament e1 ===\n\n");
	echipament e1;
	e1.cod = 1;
	e1.key = 202;
	e1.dataPrimire.zi = 20;
	e1.dataPrimire.luna = 6;
	e1.dataPrimire.an = 2022;
	e1.valoare = 2999.99;
	strcpy(e1.nume, "masina de spalat");

	afisareEchipament(e1);

	populareFisBinarRelativ(e1);
}