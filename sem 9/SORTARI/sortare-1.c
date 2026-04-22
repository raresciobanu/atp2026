#include<stdio.h>
//tablou = vector....folosesc ambii termeni in speranta ca vor fi mai clare explicatiile.

//x-tabloul care va fi sortat
//p-pozitia de inceput a primului "vector" din tabloul X
//m-pozitia de final a primului "vector" din tabloul X
//m+1-pozitia de inceput a celui de-al doilea "vector" din tabloul X
//u-pozitia de final a celui de-al doilea "vector" din tabloul X 
void interclasare(int x[], int p, int m, int u)
{
	int i, j, k, l; //indecsi de parcurgere a tabloului X
	// i - va fi fol. pt primul "vector";
	// j - va fi fol. pt al 2 lea "vector" ;
	// k - index folosit la popularea vectorului temporar Z
	// l - un simplu index de parcurgere...folosit la adaugarea elementelor ramase din x in z

	int z[100];//vector temporar

	i = p; j = m + 1; k = 0;//aveti explicatii mai sus.
	//in acest while se parcurg in acelasi timp acei 2 "vectori" din X
	while ((i <= m) && (j <= u))
	{
		//Se compara "vectorii" din tabloul X intre ei si se creeaza un nou tablou Z sortat.
		if (x[i] < x[j])
		{
			z[k] = x[i];
			i++; 
			k++;
		}
		else
		{
			z[k] = x[j];
			j++;
			k++;
		}
	}

	//daca raman elemente in plus in "vectori" se adauga in Z....primul vector poate avea 3 elem. si al 2 lea poate avea 7 elem.=> 4 elemente trebuie completate
	if (i <= m)
		for (l = i; l <= m; l++)
		{
			z[k] = x[l];
			k++;
		}

	if (j <= u)
		for (l = j; l <= u; l++)
		{
			z[k] = x[l];
			k++;
		}
	//se suprascrie X cu valorile ordonate din Z..astfel X va fi modificat si in main....
	//la vectori nu trebuie sa puneti "&" in fata ca sa se vada modificarile si in main....doar la variabilele simple trebuie "&"
	int t = p;//adica t=0;
	for (k = 0; k < (u - p) + 1; k++)// pe exemplul nostru din main:	cat timp t<(6-0)+1
		x[t++] = z[k];
}

int main() {
	int N = 3, M = 4;
	int x[] = { 1,3,7,2,5,8,9 };//sa presupunem ca vectorul x a fost format din 2 vectori initiali {1,3,7} si {2,5,8,9}
	
	interclasare(x, 0, N - 1, N + M - 1); //observati cu atentie aceasta apelare....
	
	//afisare vector dupa sortare
	for (int i = 0; i < N + M; i++) {
		printf("%d ", x[i]);
	}

	printf("\n");
	return 0;
}