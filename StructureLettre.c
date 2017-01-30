#include <stdio.h>
#include <stdlib.h>
#include "Structure.h"

/**
 *  Initialise un nouveau caractère
 */
Lettre* initLettre(char c){
    Lettre* l = malloc(sizeof(Lettre));

    (*l).c = c;
    (*l).prev = NULL;
    (*l).suiv = NULL;

    return l;
}

/**
 *  Crée une nouvelle chaine vide (un caractère de début
 *  et un de fin) et renvoie le caractère de début.
 */
Lettre* newChaineLettre(){
    Lettre* d = initLettre(DEBUT);
    Lettre* f = initLettre(FIN);

    (*d).suiv = f;
    (*f).prev = d;

    return d;
}

/**
 *  Ajoute une lettre juste après celle donnée
 */
Lettre* insertLettre(char c, Lettre* prev){
    Lettre* l = initLettre(c);

    insertChaineLettre(l, l, prev);

    return l;
}

/**
 *  insert une chaine de caractère après
 *  prev
 */
void insertChaineLettre(Lettre* debut, Lettre* fin, Lettre* prev){
    Lettre* suiv = (*prev).suiv;

    (*prev).suiv = debut;
    (*debut).prev = prev;
    (*suiv).prev = fin;
    (*fin).suiv = suiv;
}

/**
 *  Enlève un caractère (désalocation)
 */
Lettre* supprLettre(Lettre* l){
    Lettre* prev = (*l).prev;
    Lettre* suiv = (*l).suiv;

    (*prev).suiv = suiv;
    (*suiv).prev = prev;

    free(l);

    return suiv;
}

/**
 *  Enlève une chaine de caractères (désalocation)
 */
Lettre* supprChaineLettre(Lettre* debut, Lettre* fin){
    while(debut != fin){
        debut = supprLettre(debut);
    }

    return supprLettre(debut);
}
