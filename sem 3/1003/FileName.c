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

void citireMasinaConsola(struct Masina *m) {
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
	printf("Nume:"); scanf("%s", p->nume);
	printf("Varsta"), scanf("%d", &p->nume);

	citireMasinaConsola(&p->masina);
}

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
	m1.pMarca = (char*) malloc(strlen("BMW") + 1);
	strcpy(m1.pMarca, "BMW");
	afisareMasinaConsola(m1);


	struct Masina m2;
	m2.pMarca = NULL; // initializati tot timpul pointerii cu NULL!

	printf("\n\n====citire m2====\n\n");
	citireMasinaConsola(&m2);

	printf("\n\n====afisare m2====\n\n");
	afisareMasinaConsola(m2);



	printf("\n\n====sizeOf====\n\n");
	struct Persoana p1;
	
	printf("size Animal = %d\n", sizeof(a));
	printf("size Masina = %d\n", sizeof(m1));
	printf("size Persoana = %d\n", sizeof(p1));


	free(m1.pMarca);

	return 11;
}