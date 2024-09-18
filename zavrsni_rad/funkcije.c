#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

// Globalne varijable
Mjesec mjeseci[12] = {
    {31, "Sijecanj"}, {28, "Veljaca"}, {31, "Ozujak"},
    {30, "Travanj"}, {31, "Svibanj"}, {30, "Lipanj"},
    {31, "Srpanj"}, {31, "Kolovoz"}, {30, "Rujan"},
    {31, "Listopad"}, {30, "Studeni"}, {31, "Prosinac"}
};

char* daniUTjednu[7]; // Globalna varijabla za dane u tjednu

// Funkcija za provjeru prestupne godine
inline int jePrestupnaGodina(int godina)
{
    return (godina % 4 == 0 && godina % 100 != 0) || (godina % 400 == 0);
}

// Funkcija za izraèunavanje dana u tjednu
inline int izracunajDanUTjednu(int dan, int mjesec, int godina)
{
    if (mjesec < 3)
    {
        mjesec += 12;
        godina -= 1;
    }
    return (dan + 2 * mjesec + (3 * (mjesec + 1) / 5) + godina + (godina / 4) - (godina / 100) + (godina / 400) + 2) % 7;
}

// Funkcija za uèitavanje dana u tjednu iz datoteke
void ucitajDaneUTjednu(const char* imeDatoteke, char** dani)
{
    FILE* file = fopen(imeDatoteke, "r");
    if (file == NULL)
    {
        perror("Greska pri otvaranju datoteke");
        return;
    }
    for (int i = 0; i < 7; i++)
    {
        dani[i] = (char*)malloc(10 * sizeof(char));
        if (dani[i] == NULL)
        {
            perror("Greska pri zauzimanju memorije");
            fclose(file);
            return;
        }
        fscanf(file, "%9s", dani[i]);
    }
    fclose(file);
}

// Funkcija za oslobaðanje memorije
void oslobodiDaneUTjednu(char** dani)
{
    for (int i = 0; i < 7; i++)
    {
        free(dani[i]);
    }
}

// Funkcija za ispis kalendara za mjesec
void ispisiKalendarZaMjesec(int godina, int mjesecIndex)
{
    // Ažuriraj broj dana u veljaèi ako je prestupna godina
    if (jePrestupnaGodina(godina))
    {
        mjeseci[1].brojDana = 29;  // Veljaca ima 29 dana u prestupnoj godini
    }
    else
    {
        mjeseci[1].brojDana = 28;  // Vratiti na 28 dana ako nije prestupna godina
    }

    // Uèitaj dane u tjednu iz datoteke
    ucitajDaneUTjednu("dani.txt", daniUTjednu);

    // Ispisi naziv mjeseca i godine
    printf("\n---------- %s %d ----------\n", mjeseci[mjesecIndex].imeMjeseca, godina);

    // Ispisi dane u tjednu
    for (int j = 0; j < 7; j++)
    {
        printf("%s ", daniUTjednu[j]);
    }
    printf("\n");

    // Izraèunaj prvi dan mjeseca
    int prviDan = izracunajDanUTjednu(1, mjesecIndex + 1, godina);

    // Ispiši prazna mjesta prije prvog dana
    for (int j = 0; j < prviDan; j++)
    {
        printf("    ");
    }

    // Ispisi dane u mjesecu
    for (int dan = 1; dan <= mjeseci[mjesecIndex].brojDana; dan++)
    {
        printf("%3d ", dan);
        if ((dan + prviDan) % 7 == 0)
        {
            printf("\n");
        }
    }
    printf("\n\n");

    // Oslobodi memoriju za dane u tjednu
    oslobodiDaneUTjednu(daniUTjednu);
}

// Funkcija za ispis izbornika
void ispisiIzbornik()
{
    printf("Odaberite mjesec:\n");
    for (int i = 0; i < 12; i++)
    {
        printf("%d. %s\n", i + 1, mjeseci[i].imeMjeseca);
    }
    printf("\n");
}

// Funkcija za usporedbu mjesece prema broju dana
int usporediMjesecePoBrojuDana(const void* a, const void* b)
{
    Mjesec* mjesecA = (Mjesec*)a;
    Mjesec* mjesecB = (Mjesec*)b;
    return mjesecA->brojDana - mjesecB->brojDana;
}

// Funkcija za sortiranje i ispis mjesece prema broju dana
void sortirajMjesecePoBrojuDana()
{
    // Kopiraj mjeseci u lokalni niz za sortiranje
    Mjesec mjeseciSortirani[12];
    memcpy(mjeseciSortirani, mjeseci, sizeof(mjeseciSortirani));

    qsort(mjeseciSortirani, 12, sizeof(Mjesec), usporediMjesecePoBrojuDana);

    printf("\nMjeseci sortirani po broju dana:\n");
    for (int i = 0; i < 12; i++)
    {
        printf("%s: %d dana\n", mjeseciSortirani[i].imeMjeseca, mjeseciSortirani[i].brojDana);
    }
    printf("\n");
}

// Funkcija za prikaz velièine datoteke koristeæi ftell
void prikaziVelicinuDatoteke(const char* imeDatoteke)
{
    FILE* file = fopen(imeDatoteke, "r");
    if (file == NULL)
    {
        perror("Greska pri otvaranju datoteke");
        return;
    }

    fseek(file, 0, SEEK_END);  // Pomakni se na kraj datoteke
    long velicina = ftell(file);  // ftell vraæa trenutnu poziciju pokazivaèa u datoteci
    if (velicina == -1L)
    {
        perror("Greska prilikom citanja velicine datoteke");
    }
    else
    {
        printf("Velicina datoteke '%s' je %ld bajta.\n", imeDatoteke, velicina);
    }
    printf("\n");

    fclose(file);
}

// Funkcija za pretragu mjeseca po broju dana
void pretraziMjesecPoBrojuDana(int brojDana)
{
    // Pretraži kroz globalni niz mjeseci
    int found = 0;
    for (int i = 0; i < 12; i++)
    {
        if (mjeseci[i].brojDana == brojDana)
        {
            printf("Mjesec sa %d dana je: %s\n", brojDana, mjeseci[i].imeMjeseca);
            found = 1;
        }
    }
    printf("\n");

    if (!found)
    {
        printf("Nema mjeseca sa %d dana.\n", brojDana);
    }
    printf("\n");
}

// Funkcija za spremanje mjeseca u datoteku
void spremiMjesecUDatoteku(int godina, int mjesecIndex)
{
    const char* imeDatoteke = "mjesec.txt"; // Staticki naziv datoteke

    FILE* file = fopen(imeDatoteke, "w");
    if (file == NULL)
    {
        perror("Greska pri otvaranju datoteke za pisanje");
        return;
    }

    // Ispiši naziv mjeseca i godine
    fprintf(file, "Kalendar za %s %d\n", mjeseci[mjesecIndex].imeMjeseca, godina);

    // Ispiši dane u tjednu
    for (int j = 0; j < 7; j++)
    {
        fprintf(file, "%s ", daniUTjednu[j]);
    }
    fprintf(file, "\n");

    // Izraèunaj prvi dan mjeseca
    int prviDan = izracunajDanUTjednu(1, mjesecIndex + 1, godina);

    // Ispiši prazna mjesta prije prvog dana
    for (int j = 0; j < prviDan; j++)
    {
        fprintf(file, "    ");
    }

    // Ispiši dane u mjesecu
    for (int dan = 1; dan <= mjeseci[mjesecIndex].brojDana; dan++)
    {
        fprintf(file, "%3d ", dan);
        if ((dan + prviDan) % 7 == 0)
        {
            fprintf(file, "\n");
        }
    }
    fprintf(file, "\n");

    fclose(file);
}

// Funkcija za brisanje datoteke
void obrisiDatoteku()
{
    const char* imeDatoteke = "mjesec.txt"; // Staticki naziv datoteke

    if (remove(imeDatoteke) == 0)
    {
        printf("Datoteka '%s' je uspjesno obrisana.\n", imeDatoteke);
    }
    else
    {
        perror("Greska pri brisanju datoteke");
    }
    printf("\n");
}








