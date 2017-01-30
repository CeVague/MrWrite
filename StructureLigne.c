#include <stdio.h>
#include <stdlib.h>
#include "Structure.h"

Ligne* initLigne(Mot* m){
    Ligne* l = malloc(sizeof(Ligne));

    (*l).taille = 1;
    (*l).debut = m;
    (*l).prev = NULL;
    (*l).suiv = NULL;

    return l;
}

Ligne* newChaineLigne(){
    Mot* md = newChaineMot();
    Mot* mf = (*md).suiv;

    Ligne* d = initLigne(md);
    Ligne* f = initLigne(mf);

    (*d).suiv = f;
    (*f).prev = d;
    (*f).taille = 0;

    return d;
}
void changeTailleLigne(Ligne* ligne, int changement){
    (*ligne).taille += changement;
}

Ligne* insertLigne(Mot* m, Ligne* prev){
    Ligne* l = initLigne(m);

    insertChaineLigne(l, l, prev);

    return l;
}

void insertChaineLigne(Ligne* debut, Ligne* fin, Ligne* prev){
    Ligne* suiv = (*prev).suiv;

    (*prev).suiv = debut;
    (*debut).prev = prev;
    (*suiv).prev = fin;
    (*fin).suiv = suiv;
}

Ligne* supprLigne(Ligne* l){
    Ligne* prev = (*l).prev;
    Ligne* suiv = (*l).suiv;

    (*prev).suiv = suiv;
    (*suiv).prev = prev;

    free(l);

    return suiv;
}

Ligne* supprChaineLigne(Ligne* debut, Ligne* fin){
    while(debut != fin){
        debut = supprLigne(debut);
    }

    return supprLigne(debut);
}

Ligne* diviseLigne(Mot* mot, Ligne* ligne, int placeLigne){
    Ligne* ligneNew = insertLigne(mot, ligne);
    (*ligneNew).taille = (*ligne).taille - placeLigne + 1;
    (*ligne).taille = placeLigne;

    return ligneNew;
}

Ligne* fusioneLigne(Ligne* ligne){
    Ligne* lignePrev = (*ligne).prev;

    (*lignePrev).taille += (*ligne).taille;

    supprLigne(ligne);

    return lignePrev;
}
