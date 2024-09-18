#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main()
{
    int godina;
    int mjesec;
    int brojDana;
    char imeDatoteke[50];  // Dodano za pohranu imena datoteke

    // Unos godine od korisnika
    printf("Unesite godinu: ");
    scanf("%d", &godina);

    // Ispis sortirane liste mjeseci po broju dana
    sortirajMjesecePoBrojuDana();

    // Poziv funkcije koja koristi ftell za prikaz velièine datoteke
    prikaziVelicinuDatoteke("dani.txt");

    while (1)
    {
        // Ispis izbornika
        ispisiIzbornik();
        printf("Unesite broj mjeseca (1-12), 0 za izlaz, 13 za pretragu mjeseca po broju dana, ili 14 za brisanje datoteke: ");
        scanf("%d", &mjesec);
        printf("\n");

        if (mjesec == 0)
        {
            break; // Izlaz iz petlje ako je korisnik unio 0
        }
        else if (mjesec == 13)
        {
            printf("Unesite broj dana za pretragu: ");
            scanf("%d", &brojDana);
            pretraziMjesecPoBrojuDana(brojDana);
        }
        else if (mjesec == 14)
        {
            // Obrisi prethodno spremljenu datoteku
            if (strlen(imeDatoteke) > 0)
            {
                obrisiDatoteku(0, godina); // Koristi odgovarajuæi index i godinu
                imeDatoteke[0] = '\0';  // Oèisti ime datoteke
            }
            else
            {
                printf("Nema datoteke za brisanje.\n");
            }
        }
        else if (mjesec < 1 || mjesec > 12)
        {
            printf("Neispravan unos. Pokusajte ponovo.\n");
        }
        else
        {
            int mjesecIndex = mjesec - 1;

            // Ispiši kalendar za odabrani mjesec
            ispisiKalendarZaMjesec(godina, mjesecIndex);

            // Spremi kalendar u novu datoteku
            snprintf(imeDatoteke, sizeof(imeDatoteke), "%s_%d.txt", mjeseci[mjesecIndex].imeMjeseca, godina);
            spremiMjesecUDatoteku(godina, mjesecIndex);
        }
    }

    return 0;
}











