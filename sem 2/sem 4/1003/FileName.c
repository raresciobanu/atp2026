#include<stdio.h>
#include<stdlib.h>

//pt a ignora _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

//4bytes
enum CULORI {
	ROSU,
	VERDE,
	MARO = 44,
	NEGRU,
	ALBASTRU
};

//100bytes
union Animal {
	char culoare[100]; //100bytes
	int varsta; //4bytes
	float kg; //4bytes
};

//24bytes
struct Masina {
	int anFabricatie; // 4 bytes
	int caiPutere; //4 bytes
	char* pMarca; // 8 bytes - depinde - CPU x32 -> 4 Bytes - x64 - 8 bytes
	float capCilindrica; // 4 bytes
	enum CULORI culoare; // 4 bytes
};

//128bytes
struct Persoana
{
	char nume[100];
	int varsta;
	struct Masina masina;
};

void afisareMasinaConsola(struct Masina m) {
	printf("An fabricatie: %d\n", m.anFabricatie);
	printf("Cai putere: %d\n", m.caiPutere);
	printf("Marca: %s\n", m.pMarca);
	printf("Capacitate cilindrica: %.2f\n", m.capCilindrica);
	printf("Culoare: %d\n", m.culoare);
}

void citireMasinaConsola(struct Masina* m) {
	printf("An fabricatie:"); scanf("%d", &m->anFabricatie);

	printf("Cai putere:"); scanf("%d", &m->caiPutere);

	/////////////////////////////////
	char aux[100];
	printf("Marca:"); scanf("%s", aux);

	if (m->pMarca != NULL) {
		free(m->pMarca); //evitare memory leaks
	}

	m->pMarca = (char*)malloc(strlen(aux) + 1);
	strcpy(m->pMarca, aux);
	/////////////////////////////////

	printf("Capacitate cilindrica:"); scanf("%f", &m->capCilindrica);

	printf("Culoare:"); scanf("%d", &m->culoare);
}

void afisarePersoanaConsola(struct Persoana p) {
	printf("Nume: %s\n", p.nume);
	printf("Varsta: %d\n", p.varsta);

	afisareMasinaConsola(p.masina);
}

void citirePersoanaConsola(struct Persoana* p) {
	printf("Nume:"); gets(p->nume);

	printf("Varsta:"); scanf("%d", &p->varsta);

	printf("Citire masina:\n");
	citireMasinaConsola(&p->masina);
}

void scrieMasinaInFisierTxt(struct Masina m, FILE* fisOut) {
	fprintf(fisOut, "%d\n", m.anFabricatie);
	fprintf(fisOut, "%d\n", m.caiPutere);
	fprintf(fisOut, "%s\n", m.pMarca);
	fprintf(fisOut, "%.2f\n", m.capCilindrica);
	fprintf(fisOut, "%d\n", m.culoare);
}

void scriePersoanaInFisierTxt(struct Persoana p, FILE* fisOut) {
	fprintf(fisOut, "%s\n", p.nume);
	fprintf(fisOut, "%d\n", p.varsta);

	scrieMasinaInFisierTxt(p.masina, fisOut);
}

void citireMasinaDinFisierTxt(struct Masina* m, FILE* fisIn) {
	fscanf(fisIn, "%d", &m->anFabricatie);

	fscanf(fisIn, "%d", &m->caiPutere);

	/////////////////////////////////
	char aux[100];
	fscanf(fisIn, "%s", aux);

	if (m->pMarca != NULL) {
		free(m->pMarca); //evitare memory leaks
	}

	m->pMarca = (char*)malloc(strlen(aux) + 1);
	strcpy(m->pMarca, aux);
	/////////////////////////////////

	fscanf(fisIn, "%f", &m->capCilindrica);

	fscanf(fisIn, "%d", &m->culoare);
}


void citirePersoanaDinFisierTxt(struct Persoana* p, FILE* fisIn) {
	fgets(p->nume, 100, fisIn);

	fscanf(fisIn, "%d", &p->varsta);

	citireMasinaDinFisierTxt(&p->masina, fisIn);
}

void scrieMasinaInFisierBinar(struct Masina m, FILE* fisOut) {
	//functia fwrite - primeste ca input ===> fwrite(addressData, sizeData, numbersData, pointerToFile);
	//addressData - adresa variabilei citite (cu "&" in fata)
	//sizeData - dimensiunea variabilei salvate (sizeof)
	//numbersData - numarul de variabile salvate
			//int arr[3] = {101, 203, 303};
			//
			//fwrite(arr, sizeof(int), 2, fp); //va scrie primele 2 elemente din vector
	//pointerToFile - fisierul unde se salveaza variabila

	//DACA scrierea are erori atunci fwrite va retuna un numar mai mic decat variabila numbersData;

	//fwrite(&t, sizeof(l), 1, fisier); //Daca Masina nu ar fi avut char* puteam sa scriem direct asa.

	fwrite(&m.anFabricatie, sizeof(m.anFabricatie), 1, fisOut);
	fwrite(&m.caiPutere, sizeof(m.caiPutere), 1, fisOut);

	//la siruri de caractere e putin diferit
	int dim = strlen(m.pMarca) + 1;
	fwrite(&dim, sizeof(dim), 1, fisOut);
	fwrite(m.pMarca, dim, 1, fisOut);

	fwrite(&m.capCilindrica, sizeof(m.capCilindrica), 1, fisOut);
	fwrite(&m.culoare, sizeof(m.culoare), 1, fisOut);

	//alternativ putem face ca mai jos daca structura noastra nu ar contine pointeri
	//fwrite(&m, sizeof(m), 1, fisier);
}

void scriePersoaneInFisierBinar(struct Persoana p, FILE* fisOut) {
	//la siruri de caractere e putin diferit
	int dim = strlen(p.nume) + 1;
	fwrite(&dim, sizeof(dim), 1, fisOut);
	fwrite(p.nume, dim, 1, fisOut);

	fwrite(&p.varsta, sizeof(p.varsta), 1, fisOut);

	scrieMasinaInFisierBinar(p.masina, fisOut);
}

void citireMasinaDinFisierBinar(struct Masina* m, FILE* fisIn) {
	//functia fread - primeste ca input===> fread(addressData, sizeData, numbersData, pointerToFile);
	//descrierea parametrilor este la fel ca la fwrite

	//fread(&l, sizeof(l), 1, fisier); //daca nu aveam char* in structura Masina scriam asa.

	fread(&m->anFabricatie, sizeof(m->anFabricatie), 1, fisIn);
	fread(&m->caiPutere, sizeof(m->caiPutere), 1, fisIn);

	//la siruri de caractere e putin diferit
	char aux[100];

	int dim = 0;
	fread(&dim, sizeof(dim), 1, fisIn);
	fread(aux, dim, 1, fisIn);

	if (m->pMarca != NULL) {
		free(m->pMarca); //evitare memory leaks
	}

	m->pMarca = (char*)malloc(strlen(aux) + 1);
	strcpy(m->pMarca, aux);
	/////////////////////////////////

	fread(&m->capCilindrica, sizeof(m->capCilindrica), 1, fisIn);

	fread(&m->culoare, sizeof(m->culoare), 1, fisIn);
}


void citirePersoanaDinFisierBinar(struct Persoana* p, FILE* fisIn) {
	//la siruri de caractere e putin diferit
	int dim = 0;
	fread(&dim, sizeof(dim), 1, fisIn);
	fread(p->nume, dim, 1, fisIn);

	fread(&p->varsta, sizeof(p->varsta), 1, fisIn);

	citireMasinaDinFisierBinar(&p->masina, fisIn);
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


	struct Masina m1;
	m1.anFabricatie = 2020;
	m1.caiPutere = 100;
	m1.capCilindrica = 1.9;
	m1.culoare = MARO;

	//se creeaza un pointer ce va pointa catre un sir de caractere de pe HEAP memory;
	m1.pMarca = (char*)malloc(strlen("BMW") + 1);
	strcpy(m1.pMarca, "BMW");
	afisareMasinaConsola(m1);


	//struct Masina m2;
	//m2.pMarca = NULL; // initializati tot timpul pointerii cu NULL!

	//printf("\n\n====citire m2====\n\n");
	//citireMasinaConsola(&m2);

	//printf("\n\n====afisare in consola m2====\n\n");
	//afisareMasinaConsola(m2);

	printf("\n\n====afisare p1====\n\n");

	struct Persoana p1;
	p1.masina = m1;
	p1.varsta = 22;
	strcpy(p1.nume, "Andrei Ciobanu");

	afisarePersoanaConsola(p1);

	//printf("\n\n====citire tastatura p2====\n\n");
	//struct Persoana p2;
	//p2.masina.pMarca = NULL;
	//citirePersoanaConsola(&p2);

	//printf("\n\n====afisare in consola p2====\n\n");
	//afisarePersoanaConsola(p2);


	printf("\n\n====sizeOf====\n\n");

	printf("size Animal = %d\n", sizeof(a));
	printf("size Masina = %d\n", sizeof(m1));
	printf("size Persoana = %d\n", sizeof(p1));


	printf("\n\n---scriere in fisiere---\n\n");
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

	FILE* fisierPersoaneOut = fopen("persoane.txt", "w");
	if (fisierPersoaneOut == NULL) {
		printf("EROARE: Nu s-a putut deschide pentru scriere fisierul persoane.txt");
		exit(300);
	}

	scriePersoanaInFisierTxt(p1, fisierPersoaneOut);

	//important! inchideti fisierul dupa ce terminati de lucrat in el
	fclose(fisierPersoaneOut);


	FILE* fisierPersoaneIn = fopen("persoane.txt", "r");
	if (fisierPersoaneIn == NULL) {
		printf("EROARE: Nu s-a putut deschide pentru citire fisierul persoane.txt");
		exit(404);
	}

	struct Persoana p3;
	p3.masina.pMarca = NULL;

	citirePersoanaDinFisierTxt(&p3, fisierPersoaneIn);

	printf("\n\n====afisare p3 din fisier txt====\n\n");
	afisarePersoanaConsola(p3);

	//important! inchideti fisierul dupa ce terminati de lucrat in el
	fclose(fisierPersoaneIn);



	//fisire BINARE
	printf("\n\n---scriere PERSOANE in fisier binar---\n\n");

	FILE* fisierPersoaneOutBinar = fopen("persoane.bin", "wb");
	if (fisierPersoaneOutBinar == NULL) {
		printf("EROARE: Nu s-a putut deschide pentru scriere fisierul persoane.bin");
		exit(300);
	}

	scriePersoaneInFisierBinar(p1, fisierPersoaneOutBinar);

	fclose(fisierPersoaneOutBinar);


	FILE* fisierPersoaneInBinar = fopen("persoane.bin", "rb");
	if (fisierPersoaneInBinar == NULL) {
		printf("EROARE: Nu s-a putut deschide pentru citire fisierul persoane.bin");
		exit(660);
	}

	struct Persoana p4;
	p4.masina.pMarca = NULL;

	citirePersoanaDinFisierBinar(&p4, fisierPersoaneInBinar);

	printf("\n\n====afisare p4 din fisier binar====\n\n");
	afisarePersoanaConsola(p4);

	fclose(fisierPersoaneInBinar);

	//dezalocari heap
	free(m1.pMarca);
	//free(m2.pMarca);
	free(p3.masina.pMarca);
	free(p4.masina.pMarca);

	return 11;
}