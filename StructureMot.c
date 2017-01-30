#include <stdio.h>
#include <stdlib.h>
#include "Structure.h"

Mot* initMot(Lettre* l){
    Mot* m = malloc(sizeof(Mot));

    (*m).taille = 1;
    (*m).debut = l;
    (*m).prev = NULL;
    (*m).suiv = NULL;

    return m;
}

Mot* newChaineMot(){
    Lettre* ld = newChaineLettre();
    Lettre* lf = (*ld).suiv;

    Mot* d = initMot(ld);
    Mot* f = initMot(lf);

    (*d).suiv = f;
    (*f).prev = d;
    (*f).taille = 0;

    return d;
}

void changeTailleMot(Mot* mot, int changement){
    (*mot).taille += changement;
}

Mot* insertMot(Lettre* l, Mot* prev){
    Mot* m = initMot(l);

    insertChaineMot(m, m, prev);

    return m;
}

void insertChaineMot(Mot* debut, Mot* fin, Mot* prev){
    Mot* suiv = (*prev).suiv;

    (*prev).suiv = debut;
    (*debut).prev = prev;
    (*suiv).prev = fin;
    (*fin).suiv = suiv;
}

Mot* supprMot(Mot* m){
    Mot* prev = (*m).prev;
    Mot* suiv = (*m).suiv;

    (*prev).suiv = suiv;
    (*suiv).prev = prev;

    free(m);

    return suiv;
}

Mot* supprChaineMot(Mot* debut, Mot* fin){
    while(debut != fin){
        debut = supprMot(debut);
    }

    return supprMot(debut);
}

/**
 *  Coupe un mot sur un lettre donnée
 *  (supposé se trouver à la position
     placeMot dans ce mot)
 */
Mot* diviseMot(Lettre* lettre, Mot* mot, int placeMot){
    Mot* motNew = insertMot(lettre, mot);
    (*motNew).taille = (*mot).taille - placeMot + 1;
    (*mot).taille = placeMot;

    return motNew;
}

/**
 *  Fusionne un mot avec celui qui le précède
 */
Mot* fusioneMot(Mot* mot){
    Mot* motPrev = (*mot).prev;

    (*motPrev).taille += (*mot).taille;

    supprMot(mot);

    return motPrev;
}
