#include <stdio.h>
#include <stdlib.h>
#include "Structure.h"

/**
 *  Initialise un nouveau caract�re
 */
Lettre* initLettre(char c){
    Lettre* l = malloc(sizeof(Lettre));

    (*l).c = c;
    (*l).prev = NULL;
    (*l).suiv = NULL;

    return l;
}

/**
 *  Cr�e une nouvelle chaine vide (un caract�re de d�but
 *  et un de fin) et renvoie le caract�re de d�but.
 */
Lettre* newChaineLettre(){
    Lettre* d = initLettre(DEBUT);
    Lettre* f = initLettre(FIN);

    (*d).suiv = f;
    (*f).prev = d;

    return d;
}

/**
 *  Ajoute une lettre juste apr�s celle donn�e
 */
Lettre* insertLettre(char c, Lettre* prev){
    Lettre* l = initLettre(c);

    insertChaineLettre(l, l, prev);

    return l;
}

/**
 *  insert une chaine de caract�re apr�s
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
 *  Enl�ve un caract�re (d�salocation)
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
 *  Enl�ve une chaine de caract�res (d�salocation)
 */
Lettre* supprChaineLettre(Lettre* debut, Lettre* fin){
    while(debut != fin){
        debut = supprLettre(debut);
    }

    return supprLettre(debut);
}
