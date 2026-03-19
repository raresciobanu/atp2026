#include<stdio.h>
#include<stdlib.h>

#pragma warning(disable:4996)

//104 bytes
struct Patron
{
	char nume[100];
	int varsta;
};

//224bytes
struct Firma
{
	int key;
	int esteSetat;//val 0/1 - pentru a indica daca o locatie din fisier este ocupata de o firma

	int nrAngajati;
	double venit;
	char numeFirma[100];
	struct Patron patron;
};

void afisarePatron(struct Patron p) {
	printf("Patron: %s\n", p.nume);
	printf("Varsta: %d\n", p.varsta);
}

void afisareFirma(struct Firma f) {
	printf("\n===Afisare firma===\n");

	printf("Key: %d\n", f.key);
	printf("Este setat: %d\n", f.esteSetat);
	printf("NrAngajati: %d\n", f.nrAngajati);
	printf("Venit: %.2lf\n", f.venit);
	printf("Nume firma: %s\n", f.numeFirma);

	afisarePatron(f.patron);

	printf("\n\n");
}

void citirePatron(struct Patron* p) {
	printf("Patron:"); gets(p->nume);
	printf("Varsta:"); scanf("%d", &p->varsta);
}

void citireFirma(struct Firma* f) {
	printf("===Citire firma===\n");

	f->esteSetat = 1;

	printf("NrAngajati:"); scanf("%d", &f->nrAngajati);
	printf("Venit:"); scanf("%lf", &f->venit);

	getchar();
	printf("Nume firma:"); gets(f->numeFirma);

	citirePatron(&f->patron);

	printf("\n===Citire firma s-a terminat===\n");
}

int aflaCateFirmeSuntInFisier(FILE* f) {
	//ftell -> returneaza pozitia curenta a cursorului in fisier
	int pozCurenta = ftell(f);//pastram pozita curenta;

	fseek(f, 0, SEEK_END);//se pozitioneaza la sf fisierului

	int nrFirme = ftell(f) / sizeof(struct Firma); //daca tu ai 4 firme in fisier => ftell va fi 896  => 896/224 = 4 firme

	fseek(f, pozCurenta, SEEK_SET);//se pozitioneaza la pozitia initiala

	return nrFirme;
}

struct Firma getFirmaEmpty() {
	struct Patron p1;
	strcpy(p1.nume, "");
	p1.varsta = 0;

	struct Firma f1;
	f1.key = 0;
	f1.esteSetat = 0;
	f1.nrAngajati = 0;
	strcpy(f1.numeFirma, "");
	f1.patron = p1;
	f1.venit = 0.0;

	return f1;
}

int main() {


	//Afisarea informatiilor in format tabel

	//FILE *f = fopen("ceva.txt", "w");
	//fprintf(f, "%4s %-16s %3s %30s", "Crt.", "BBB", "AAAA", "Suma");
	//printf("%4s %-16s %6s %30s", "Crt.", "BBB", "AAAA", "Suma");

	//fclose(f);


	//long int ftell(FILE *fp); - returneaza pozitia curenta;

	//int fseek(FILE *fp, long int offset, int origin);

	//fp - fisierul peste care se aplica operatia fseek;

	//offset - numarul de bytes fata de origin(al 3 lea parametru);
	//poate fi nr. pozitiv(pt mersul inainte prin fisier) sau negativ(pt mersul inapoi prin fisier);

	//origin - originea punctului fata de care se aplica offsetul;
	//Ex: SEEK_SET - inceputul fisierului
	//Ex: SEEK_CUR - pozitia curenta a fisierului
	//Ex: SEEK_END - sfarsitul fisierului

	//fseek - returneaza 0 daca mutarea a fost efectuata cu succes, altfel o alta val !=0

	struct Patron p1;
	strcpy(p1.nume, "Patron 1");
	p1.varsta = 33;

	struct Firma f1;
	f1.key = 1;
	f1.esteSetat = 1;
	f1.nrAngajati = 3;
	strcpy(f1.numeFirma, "Firma 1");
	f1.patron = p1;
	f1.venit = 333354.5543;

	afisareFirma(f1);

	//struct Firma f2;
	//citireFirma(&f2);
	//f2.key = 2;
	//afisareFirma(f2);



	FILE* fisBinar = fopen("fisBinarFirme.bin", "wb+");
	if (fisBinar == NULL) {
		printf("ERROR: fisBinarFirme.bin nu s-a putut deschide.");
		exit(1);
	}


	while (!feof(stdin)) {//atunci cand se cere ca sfarsitul introducerii sa fie marcat standard
		printf("\n\nAlegeti o optiune din meniu:\n");
		printf("1) Salvati o firma in fisier la o anumita pozitie.\n");
		printf("2) Modificati o firma din fisier de la o anumita pozitie.\n");
		printf("3) Stergeti o firma din fisier de la o anumita pozitie.\n");
		printf("4) Afisati o firma din fisier de la o anumita pozitie.\n");
		printf("5) Exit.\n");

		int optiune;
		printf("Introduceti optiunea dorita: "); scanf("%d", &optiune);

		switch (optiune) {
		case 1: {
			int key;
			printf("Introduceti o firma de la tastatura:\n");
			printf("Key: "); scanf("%d", &key);
			int nrFirme = aflaCateFirmeSuntInFisier(fisBinar);

			if (key >= 0) {
				struct Firma x = getFirmaEmpty();

				if (key >= nrFirme) {
					//alocam memorie noua daca cheia introdusa >= nr de firme din fisier

					x.esteSetat = 0;

					fseek(fisBinar, 0, SEEK_END);//cand fis e gol si te pozitionezi la sf => te pozitionezi la inceputul fisierului.


					for (int i = 0; i < (key + 1) - nrFirme; i++) {
						fwrite(&x, sizeof(struct Firma), 1, fisBinar);
					}

					//sau in loc de for(le scrii pe toate odata): fwrite(&x, sizeof(struct Firma), (key + 1) - nrFirme, fisBinar);
				}

				//se pozitioneaza cursorul la adresa key * sizeof(Firma)
				fseek(fisBinar, key * sizeof(struct Firma), SEEK_SET);

				//se citeste firma de la adreasa: key * sizeof(Firma)
				fread(&x, sizeof(struct Firma), 1, fisBinar);

				if (x.esteSetat == 1) {
					printf("La cheia introdusa exista deja firma salvata. Nu se mai poate adauga unul.\n");
				}
				else {
					x.key = key;
					citireFirma(&x);

					//se pozitioneaza cursorul la adresa key * sizeof(Firma)
					fseek(fisBinar, key * sizeof(struct Firma), SEEK_SET);

					//se scrie Firma in fisier la adresa key * sizeof(Firma)
					fwrite(&x, sizeof(struct Firma), 1, fisBinar);

				}
			} 
			else {
				printf("Key trebuie sa fie >=0!\n");
			}

			break;
		}
		case 2: {
			struct Firma x;

			int key;
			printf("Key: "); scanf("%d", &key);

			//se pozitioneaza cursorul la adresa key * sizeof(Firma)
			fseek(fisBinar, key * sizeof(struct Firma), SEEK_SET);

			//se citeste firma de la adreasa: key * sizeof(Firma)
			fread(&x, sizeof(struct Firma), 1, fisBinar);

			if (x.esteSetat == 0) {
				printf("La cheia introdusa nu exista nicio firma. NU se poate modifica nimic.\n");
			}
			else {
				citireFirma(&x);

				//se pozitioneaza cursorul la adresa key * sizeof(Firma)
				fseek(fisBinar, key * sizeof(struct Firma), SEEK_SET);

				//se scrie Firma in fisier la adresa key * sizeof(Firma)
				fwrite(&x, sizeof(struct Firma), 1, fisBinar);

			}

			break;
		}
		case 3: {
			struct Firma f;

			int key;
			printf("Key: "); scanf("%d", &key);

			//se pozitioneaza cursorul la adresa key * sizeof(Firma)
			fseek(fisBinar, key * sizeof(struct Firma), SEEK_SET);

			//se citeste firma de la adresa: key * sizeof(Firma)
			fread(&f, sizeof(struct Firma), 1, fisBinar);

			if (f.esteSetat == 0) {
				printf("La cheia introdusa nu exista nicio firma. NU se poate sterge nimic.\n");
			}
			else {
				f.esteSetat = 0;//atat trebuie facut la stergere

				//se pozitioneaza cursorul la adresa key * sizeof(Firma)
				fseek(fisBinar, key * sizeof(struct Firma), SEEK_SET);

				//se scrie Firma in fisier la adresa key * sizeof(Firma)
				fwrite(&f, sizeof(struct Firma), 1, fisBinar);

				printf("S-a sters firma de la cheia: %d\n", key);
			}

			break;
		}
		case 4: {
			struct Firma f;

			int key;
			printf("Key: "); scanf("%d", &key);

			//se pozitioneaza cursorul la adresa key * sizeof(Firma)
			fseek(fisBinar, key * sizeof(struct Firma), SEEK_SET);
					
			//se citeste firma de la adresa: key * sizeof(Firma)
			fread(&f, sizeof(struct Firma), 1, fisBinar);

			if (f.esteSetat == 0) {
				printf("La cheia introdusa nu exista nicio firma. NU se poate afisa nimic.\n");
			}
			else {
				afisareFirma(f);
			}

			break;
		}
		case 5:
		{
			printf("Aplicatia s-a oprit.\n");
			exit(44);
		}
		default:
			printf("Optiunea introdusa nu exista.\n");
		}
	}

	return 100;
}

//0*224
//1 * 224
//2 * 224
//3 * 224
//...
//10 * 224
//11 * 224
//...
//20 * 224