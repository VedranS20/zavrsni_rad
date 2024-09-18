#pragma once
#ifndef HEADER_H
#define HEADER_H

// Definicija enum tipa za dane u tjednu
typedef enum
{
    NEDJELJA,
    PONEDJELJAK,
    UTORAK,
    SRIJEDA,
    CETVRTAK,
    PETAK,
    SUBOTA
} DanUTjednu;

// Definicija strukture za datum
typedef struct
{
    int dan;
    int mjesec;
    int godina;
} Datum;

// Definicija strukture za mjesec s kalendarom
typedef struct
{
    int brojDana;
    const char* imeMjeseca;
} Mjesec;

// Deklaracija globalnih varijabli s extern
extern Mjesec mjeseci[12];
extern char* daniUTjednu[7];

// Deklaracija funkcija
int jePrestupnaGodina(int godina);
int izracunajDanUTjednu(int dan, int mjesec, int godina);
void ispisiKalendarZaMjesec(int godina, int mjesecIndex);
void ucitajDaneUTjednu(const char* imeDatoteke, char** dani);
void oslobodiDaneUTjednu(char** dani);
void ispisiIzbornik();
void prikaziVelicinuDatoteke(const char* imeDatoteke);
void sortirajMjesecePoBrojuDana();
void pretraziMjesecPoBrojuDana(int brojDana);  // Dodano za pretragu mjeseca
void spremiMjesecUDatoteku(int godina, int mjesecIndex); // Dodano za spremanje mjeseca u datoteku
void obrisiDatoteku(int mjesecIndex, int godina); // Dodano za brisanje datoteke

#endif // HEADER_H
















