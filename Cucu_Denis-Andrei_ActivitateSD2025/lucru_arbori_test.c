#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct Masina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct Masina Masina;

struct Nod {

	Masina info;
	struct Nod* st;
	struct Nod* dr;
	
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


void adaugaMasiniInArbore(Nod** arbore, Masina masinaNoua) {
	
	if (!(*arbore)) {

		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = masinaNoua;
		nou->dr = NULL;
		nou->st = NULL;
		*arbore = nou;
	}
	else {
		if ((*arbore)->info.id > masinaNoua.id)
		{
			adaugaMasiniInArbore(&((*arbore)->st), masinaNoua);

		}
		else if ((*arbore)->info.id < masinaNoua.id)
		{
			adaugaMasiniInArbore(&((*arbore)->dr), masinaNoua);
		}
	}
}




void* citireArboreDeMasiniDinFisier(const char* numeFisier) {
	FILE* file = fopen(numeFisier, "r");
	Nod* radacina = NULL;

	while (!feof(file))
	{
		adaugaMasiniInArbore(&radacina, citireMasinaDinFisier(file));
	}
	fclose(file);
	return radacina;
}

void afisareArboreInPostOrdine(Nod* arbore)
{
	if (arbore)
	{
		afisareArboreInPostOrdine(arbore->st);
		afisareArboreInPostOrdine(arbore->dr);
		afisareMasina(arbore->info);
	}
}

void afisareArboreInOrdineBuna(Nod* arbore)
{
	if (arbore)
	{
		afisareArboreInOrdineBuna(arbore->st);
		afisareMasina(arbore->info);
		afisareArboreInOrdineBuna(arbore->dr);
	
	}
}

void afisareArboreInPreOrdine(Nod* arbore)
{
	if (arbore)
	{
		afisareMasina(arbore->info);
		afisareArboreInPreOrdine(arbore->st);
		afisareArboreInPreOrdine(arbore->dr);
	}
}




void dezalocareArboreDeMasini(Nod** arbore) {

	if (*arbore)
	{
		dezalocareArboreDeMasini(&((*arbore)->st));
		dezalocareArboreDeMasini(&((*arbore)->dr));
		free((*arbore)->info.numeSofer);
		free((*arbore)->info.model);
		free((*arbore));
		(*arbore) = NULL;
	}
	
}



int main() {


	return 0;
}