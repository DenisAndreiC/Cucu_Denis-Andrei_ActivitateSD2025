#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

struct Heap {
	int lungime;   //lungimea vectorului
	Masina* vector;  //vectorul de masini
	int nrMasini;//este deiferit de lungimea vectorului
};
typedef struct Heap Heap;


Masina citireMasinaDinFisier(FILE* file)
{
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina)
{
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

Heap initializareHeap(int lungime)  //initializam heap ul cu 0 masini dar cu o lungime primita ca parametru
{
	Heap heap;
	heap.lungime = lungime; //initializam lungimea heap ului cu parametru primit
	heap.nrMasini = 0;  // numarul de masini din heap este momentan 0
	heap.vector = (Masina*)malloc(sizeof(Masina) * lungime);  //atribuim vectorul prin cast
	return heap;
}

void filtreazaHeap(Heap heap, int pozitieNod)
{
	int pozFiuSt = 2 * pozitieNod + 1;
	int pozFiuDr = 2 * pozitieNod + 2;
	int pozMax = pozitieNod;
	if (heap.vector[pozMax].id < heap.vector[pozFiuSt].id) {
		pozMax = pozFiuSt;
	}
	if (pozFiuDr < heap.nrMasini && heap.vector[pozMax].id < heap.vector[pozFiuDr].id)
	{
		pozMax = pozFiuDr;
	}
	if (pozMax != pozitieNod)
	{
		Masina aux = heap.vector[pozMax];
		heap.vector[pozMax] = heap.vector[pozitieNod];
		heap.vector[pozitieNod] = aux;
		if (2 * pozMax + 1 <= heap.nrMasini - 1)// sau if(pozMax <= (heap.nrMasini-2)/2
		{
			filtreazaHeap(heap, pozMax);
		}
	}
}

Heap citireHeapDeMasiniDinFisier(const char* numeFisier)
{
	FILE* file = fopen(numeFisier, "r");
	Heap heap = initializareHeap(10);

	while (!feof(file)) {
		heap.vector[heap.nrMasini++] = citireMasinaDinFisier(file);
	}

	fclose(file);
	for (int i = (heap.nrMasini - 2) / 2;i >= 0;i--)
	{
		filtreazaHeap(heap, i);
	}
	return heap;

}

void afisareHeap(Heap heap)
{
	for (int i = 0;i < heap.nrMasini;i++)
	{
		afisareMasina(heap.vector[i]);
	}
}

int main() {
	Heap heap = citireHeapDeMasiniDinFisier("masini.txt");
	afisareHeap(heap);
	return 0; 
}