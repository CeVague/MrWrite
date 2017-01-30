#ifndef _STRUCT_
#define _STRUCT_

#define DEBUT 0
#define FIN 1

typedef struct Lettre Lettre;

struct Lettre
{
    char c;
    Lettre* prev;
    Lettre* suiv;
};

Lettre* initLettre(char c);
Lettre* newChaineLettre();
Lettre* insertLettre(char c, Lettre* prev);
void insertChaineLettre(Lettre* debut, Lettre* fin, Lettre* prev);
Lettre* supprLettre(Lettre* l);
Lettre* supprChaineLettre(Lettre* debut, Lettre* fin);



typedef struct Mot Mot;

struct Mot
{
    size_t taille;
    Lettre* debut;
    Mot* prev;
    Mot* suiv;
};

Mot* initMot(Lettre* l);
Mot* newChaineMot();
void changeTailleMot(Mot* mot, int changement);
Mot* insertMot(Lettre* l, Mot* prev);
void insertChaineMot(Mot* debut, Mot* fin, Mot* prev);
Mot* supprMot(Mot* m);
Mot* supprChaineMot(Mot* debut, Mot* fin);
Mot* diviseMot(Lettre* lettre, Mot* mot, int placeMot);
Mot* fusioneMot(Mot* mot);


typedef struct Ligne Ligne;

struct Ligne
{
    size_t taille;
    Mot* debut;
    Ligne* prev;
    Ligne* suiv;
};


Ligne* initLigne(Mot* m);
Ligne* newChaineLigne();
void changeTailleLigne(Ligne* ligne, int changement);
Ligne* insertLigne(Mot* m, Ligne* prev);
void insertChaineLigne(Ligne* debut, Ligne* fin, Ligne* prev);
Ligne* supprLigne(Ligne* l);
Ligne* supprChaineLigne(Ligne* debut, Ligne* fin);
Ligne* diviseLigne(Mot* mot, Ligne* ligne, int placeLigne);
Ligne* fusioneLigne(Ligne* ligne);


#endif
