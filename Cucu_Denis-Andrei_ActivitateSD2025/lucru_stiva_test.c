#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//STIVE

struct StructuraMasina {
    int id;
    int nrUsi;
    float pret;
    char* model;
    char* numeSofer;
    unsigned char serie;

};
typedef struct StructuraMasina Masina;

Masina citireMasinaDinFisier(FILE* file)
{
    char buffer[100];
    char sep[3] = ",\n";
    fgets(buffer, 100, file);
    Masina m1;
    char* aux;

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

    m1.serie = strtok(NULL, sep);
    return m1;
}

void AfisareOMasina(Masina masina)
{
    printf("Id: %d\n", masina.id);
    printf("Nr. usi : %d\n", masina.nrUsi);
    printf("Pret: %.2f\n", masina.pret);
    printf("Model: %s\n", masina.model);
    printf("Nume sofer: %s\n", masina.numeSofer);
    printf("Serie: %c\n\n", masina.serie);
}

//declararea la stiva 
struct Nod {
    struct Nod* next;
    Masina info;
};
typedef struct Nod Nod;

void pushStack(Nod** stiva, Masina masinaNoua)
{
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = masinaNoua;
    nou->next = (stiva);
    (*stiva) = nou;

}
Masina popStack(Nod** stiva)
{
    if ((*stiva) != NULL)
    {
        Masina m = (*stiva)->info;
        Nod* temp = *stiva;
        (*stiva) = temp->next;
        free(temp);
        return m;
    }
    return (Masina) { -1, 0, 0, NULL, NULL, '-' };
}

Nod* citireaStackMasiniDinFisier(const char* numeFisier) {
    FILE* file = fopen(numeFisier, "r");
    Nod* stiva = NULL;
    while (!feof(file))
    {
        pushStack(&stiva, citireMasinaDinFisier(file));
    }
    fclose(file);
    return stiva;
}

void afisareStiva(Nod* stiva)
{
    Nod* p = stiva;
    while (p != NULL)
    {
        afisareOMasina(p->info);
        p = p->next;
    }
}

void dezalocareStivaDeMasini(Nod** stiva)
{
    while (*stiva)
    {
        Masina m = popStack(stiva);
        free(m.model);
        free(m.numeSofer);

    }
}