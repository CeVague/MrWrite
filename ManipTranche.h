#ifndef _TRANCHE_
#define _TRANCHE_

#include "Structure.h"

typedef struct Curseur Curseur;

struct Curseur
{
    // lettre, mot et ligne pointées par le curseur
    Lettre* lettre;
    Mot* mot;
    Ligne* ligne;
    // Lien vers les tailles des lignes et mots pointés
    size_t* tailleMot;
    size_t* tailleLigne;
    // Position du curseur dans le mot actuel et
    // dans la ligne actuelle
    int placeMot;
    int placeLigne;
};

Curseur* initialise(Lettre* lettre, Mot* mot, Ligne* ligne, int placeMot, int placeLigne);

char get(Curseur* curseur);

void changeLigne(Curseur* curseur, Ligne* ligne, int placeLigne);
void changeMot(Curseur* curseur, Mot* mot, int placeMot);
void changeLettre(Curseur* curseur, Lettre* lettre);

void finDeMot(Curseur* curseur);
void debutDeMot(Curseur* curseur);
void finDeLigne(Curseur* curseur);
void debutDeLigne(Curseur* curseur);

Lettre* supprSimple(Lettre* lettre, Mot* mot, Ligne* ligne);
void suppr(Curseur* curseur);

#endif
