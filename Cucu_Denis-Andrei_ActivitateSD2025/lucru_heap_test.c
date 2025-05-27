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
	Masina* vector;
	int lungime;
	int nrMasini;
};
typedef struct Heap Heap;


struct Nod {
	Masina info;
	struct Nod* next;
};
typedef struct Nod Nod;



Masina citireMasinaDinFisier(FILE* file) {
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

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

void afisareLista(Nod* lista)
{
	if (lista)
	{
		Nod* p = lista;
		while (p)
		{
			afisareMasina(p->info);
			p = p->next;
		}
	}
}

Heap initializareHeap(int lungime) {
	Heap h;
	h.lungime = lungime;
	h.nrMasini = 0;
	h.vector = (Masina*)malloc(lungime * sizeof(Masina));
	return h;
}

void filtreazaHeap(Heap heap, int pozitieNod) {
	int pozStanga = 2 * pozitieNod + 1;
	int pozDreapta = 2 * pozitieNod + 2;
	int pozMax = pozitieNod;

	if (pozStanga < heap.nrMasini && heap.vector[pozMax].id < heap.vector[pozStanga].id)
	{
		pozMax = pozStanga;
	}
	if (pozDreapta < heap.nrMasini && heap.vector[pozMax].id < heap.vector[pozDreapta].id)
	{
		pozMax = pozDreapta;
	}
	if (pozMax != pozitieNod)
	{
		Masina aux = heap.vector[pozMax];
		heap.vector[pozMax] = heap.vector[pozitieNod];
		heap.vector[pozitieNod] = aux;
		
	}
}

Heap citireHeapDeMasiniDinFisier(const char* numeFisier) {
	Heap h = initializareHeap(10);
	FILE* f = fopen(numeFisier, "r");

	while (!feof(f))
	{
		Masina m = citireMasinaDinFisier(f);
		h.vector[h.nrMasini] = m;
		h.nrMasini++;
	}
	fclose(f);

	for (int i = (h.nrMasini - 2) / 2; i >= 0; i--)
	{
		filtreazaHeap(h, i);
	}

	return h;
}

void afisareHeap(Heap heap) {
	if (heap.vector)
	{
		for (int i = 0; i < heap.nrMasini; i++)
		{
			afisareMasina(heap.vector[i]);
		}
	}
}



void dezalocareHeap(Heap* heap) {
	for (int i = 0; i < heap->lungime; i++)
	{
		free(heap->vector[i].numeSofer);
		free(heap->vector[i].model);
	}
	free(heap->vector);
	heap->lungime = 0;
	heap->nrMasini = 0;
	heap->vector = NULL;
}


int main() {
	Heap h = citireHeapDeMasiniDinFisier("masini_arbore.txt.txt");

	afisareHeap(h);

	
}