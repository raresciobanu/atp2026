#include<stdio.h>
#include<stdlib.h>

#pragma warning(disable:4996)

// 12 bytes
struct Data {
	int zi;
	int luna;
	int an;
};

// 128 bytes
struct Produs {
	int key;
	int esteSetat;//valoarea 0/1 - pentru a indica daca o locatie din fisier este ocupata de un Produs

	char nume[100];
	float pret;
	int cantitate;

	struct Data valabilitate;
};

void afisareData(struct Data d) {
	printf("zi: %d\n", d.zi);
	printf("luna: %d\n", d.luna);
	printf("an: %d\n", d.an);
}

void citireData(struct Data* d) {
	printf("zi:"); scanf("%d", &d->zi);
	printf("luna:"); scanf("%d", &d->luna);
	printf("an:"); scanf("%d", &d->an);
}

void afisareProdus(struct Produs p) {
	printf("\n\n===afisare Produs===\n\n");

	printf("key: %d\n", p.key);
	printf("esteSetat: %d\n", p.esteSetat);
	printf("nume: %s\n", p.nume);
	printf("pret: %.2f\n", p.pret);
	printf("cantitate: %d\n", p.cantitate);

	afisareData(p.valabilitate);
}

void citireProdus(struct Produs* p, int key) {
	printf("\n\n===citire Produs===\n\n");

	p->esteSetat = 1;
	p->key = key;
	printf("nume:"); gets(p->nume);
	printf("pret:"); scanf("%f", &p->pret);
	printf("cantitate:"); scanf("%d", &p->cantitate);

	citireData(&p->valabilitate);
}

int aflaCateProduseSuntInFisier(FILE* f) {
	//ftell -> returneaza pozitia curenta a cursorului in fisier
	int pozCurenta = ftell(f);//pastram pozita curenta;

	fseek(f, 0, SEEK_END);//se pozitioneaza la sf fisierului

	int nrProduse = ftell(f) / sizeof(struct Produs); //daca tu ai 10 produse in fisier => ftell va fi 1280  => 1280/128 = 10 produse

	fseek(f, pozCurenta, SEEK_SET);//se pozitioneaza la pozitia initiala

	return nrProduse;
}

struct Produs getProdusEmpty() {
	struct Data d1;
	d1.zi = 0;
	d1.luna = 0;
	d1.an = 0;

	struct Produs p1;
	p1.cantitate = 0;
	p1.esteSetat = 0;
	p1.key = 0;
	strcpy(p1.nume, "");
	p1.pret = 0;
	p1.valabilitate = d1;

	return p1;
}

int main()
{
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

	struct Data d1;
	d1.zi = 20;
	d1.luna = 6;
	d1.an = 2026;

	struct Produs p1;
	p1.cantitate = 10;
	p1.esteSetat = 1;
	p1.key = 1;
	strcpy(p1.nume, "Coca Cola");
	p1.pret = 7.9;
	p1.valabilitate = d1;

	afisareProdus(p1);

	//struct Produs p2;
	//citireProdus(&p2, 2);
	//afisareProdus(p2);


	FILE* fisBinar = fopen("fisBinarProduse.bin", "wb+");
	if (fisBinar == NULL) {
		printf("ERROR: fisBinarProduse.bin nu s-a putut deschide.");
		exit(1);
	}


	while (!feof(stdin)) {//atunci cand se cere ca sfarsitul introducerii sa fie marcat standard
		printf("\n\nAlegeti o optiune din meniu:\n");
		printf("1) Salvati un produs in fisier la o anumita pozitie.\n");
		printf("2) Modificati un produs din fisier de la o anumita pozitie.\n");
		printf("3) Stergeti un produs din fisier de la o anumita pozitie.\n");
		printf("4) Afisati un produs din fisier de la o anumita pozitie.\n");
		printf("5) Exit.\n");

		int optiune;
		printf("Introduceti optiunea dorita: "); scanf("%d", &optiune);

		switch (optiune) {
		case 1: {
			int key;
			printf("Introduceti un produs de la tastatura:\n");
			printf("Key: "); scanf("%d", &key);
			int nrProduse = aflaCateProduseSuntInFisier(fisBinar);

			if (key >= 0) {
				struct Produs p = getProdusEmpty();

				if (key >= nrProduse) {
					//alocam memorie noua daca cheia introdusa >= nr de produse din fisier

					fseek(fisBinar, 0, SEEK_END);//cand fis e gol si te pozitionezi la sf => te pozitionezi la inceputul fisierului.


					for (int i = 0; i < (key + 1) - nrProduse; i++) {
						fwrite(&p, sizeof(struct Produs), 1, fisBinar);
					}

					//sau in loc de for(le scrii pe toate odata): fwrite(&p, sizeof(struct Produs), (key + 1) - nrProduse, fisBinar);
				}

				//se pozitioneaza cursorul la adresa key * sizeof(Produs)
				fseek(fisBinar, key * sizeof(struct Produs), SEEK_SET);

				//se citeste produsul de la adreasa: key * sizeof(Produs)
				fread(&p, sizeof(struct Produs), 1, fisBinar);

				if (p.esteSetat == 1) {
					printf("La cheia introdusa exista deja un produs salvat. Nu se mai poate adauga unul.\n");
				}
				else {
					getchar();//ramane blocat in buffer un \n...de la citirea key ului
					citireProdus(&p, key);

					//se pozitioneaza cursorul la adresa key * sizeof(Produs)
					fseek(fisBinar, key * sizeof(struct Produs), SEEK_SET);

					//se scrie un Produs in fisier la adresa key * sizeof(Produs)
					fwrite(&p, sizeof(struct Produs), 1, fisBinar);
				}
			}
			else {
				printf("Key trebuie sa fie >=0!\n");
			}

			break;
		}
		case 2: {
			struct Produs p;

			int key;
			printf("Key: "); scanf("%d", &key);

			//se pozitioneaza cursorul la adresa key * sizeof(Produs)
			fseek(fisBinar, key * sizeof(struct Produs), SEEK_SET);

			//se citeste produsul de la adreasa: key * sizeof(Produs)
			fread(&p, sizeof(struct Produs), 1, fisBinar);

			if (p.esteSetat == 0) {
				printf("La cheia introdusa nu exista niciun produs. NU se poate modifica nimic.\n");
			}
			else {
				getchar();//ramane blocat in buffer un \n...de la citirea key ului

				citireProdus(&p, key);

				//se pozitioneaza cursorul la adresa key * sizeof(Produs)
				fseek(fisBinar, key * sizeof(struct Produs), SEEK_SET);

				//se scrie Produs in fisier la adresa key * sizeof(Produs)
				fwrite(&p, sizeof(struct Produs), 1, fisBinar);
			}

			break;
		}
		case 3: {
			struct Produs p;

			int key;
			printf("Key: "); scanf("%d", &key);

			//se pozitioneaza cursorul la adresa key * sizeof(Produs)
			fseek(fisBinar, key * sizeof(struct Produs), SEEK_SET);

			//se citeste produsul de la adresa: key * sizeof(Produs)
			fread(&p, sizeof(struct Produs), 1, fisBinar);

			if (p.esteSetat == 0) {
				printf("La cheia introdusa nu exista niciun produs. NU se poate sterge nimic.\n");
			}
			else {
				p.esteSetat = 0;//atat trebuie facut la stergere

				//se pozitioneaza cursorul la adresa key * sizeof(Produs)
				fseek(fisBinar, key * sizeof(struct Produs), SEEK_SET);

				//se scrie Produs in fisier la adresa key * sizeof(Produs)
				fwrite(&p, sizeof(struct Produs), 1, fisBinar);

				printf("S-a sters produsul de la cheia: %d\n", key);
			}

			break;
		}
		case 4: {
			struct Produs p;

			int key;
			printf("Key: "); scanf("%d", &key);

			//se pozitioneaza cursorul la adresa key * sizeof(Produs)
			fseek(fisBinar, key * sizeof(struct Produs), SEEK_SET);

			//se citeste produsul de la adresa: key * sizeof(Produs)
			fread(&p, sizeof(struct Produs), 1, fisBinar);

			if (p.esteSetat == 0) {
				printf("La cheia introdusa nu exista niciun produs. NU se poate afisa nimic.\n");
			}
			else {
				afisareProdus(p);
			}

			break;
		}
		case 5: {
			printf("Aplicatia s-a oprit.\n");
			exit(44);
		}
		default: {
			printf("Optiunea introdusa nu exista.\n");
		}
		}
	}
	return 444;
}



//0 * 128
//1 * 128
//2 * 128
//3 * 128
//...
//10 * 128
//11 * 128
//...
//20 * 128
