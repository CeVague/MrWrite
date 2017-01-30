#include <stdio.h>
#include <stdlib.h>
#include "GestionTouches.h"

void toucheEntree(Curseur* curseur){
    Lettre* lettre = insertLettre('\n', (*curseur).lettre);

    Mot* mot = diviseMot(lettre, (*curseur).mot, (*curseur).placeMot);

    diviseLigne(mot, (*curseur).ligne, (*curseur).placeLigne);
}

void toucheEspace(Curseur* curseur){
    Lettre* lettre = insertLettre(' ', (*curseur).lettre);

    diviseMot(lettre, (*curseur).mot, (*curseur).placeMot);

    changeTailleLigne((*curseur).ligne, 1);
}

void toucheLettre(Curseur* curseur, char c){
    insertLettre(c, (*curseur).lettre);
    changeTailleMot((*curseur).mot, 1);
    changeTailleLigne((*curseur).ligne, 1);
}

void toucheSuppr(Curseur* curseur){
    if((*(*(*curseur).lettre).suiv).c != FIN){
        droite(curseur);
        suppr(curseur);
        gauche(curseur);
    }
}

void toucheDel(Curseur* curseur){
    if((*(*curseur).lettre).c != DEBUT){
        suppr(curseur);
        gauche(curseur);
    }
}

void inserer(Curseur* curseur, char c){
    if(c=='\n'){
        toucheEntree(curseur);
    }else if(c==' '){
        toucheEspace(curseur);
    }else{
        toucheLettre(curseur, c);
    }
    droite(curseur);
}

void droite(Curseur* curseur){
    Lettre* lettre = (*(*curseur).lettre).suiv;

    // Si on arrive pas en fin de chaine
    if((*lettre).c != FIN){
        // On avance d'une lettre
        changeLettre(curseur, lettre);
        (*curseur).placeMot += 1;
        (*curseur).placeLigne += 1;

        // Si ça nous fait changer de mot
        // on avance d'un mot
        Mot* mot = (*curseur).mot;
        if((*curseur).placeMot > (*mot).taille){
            changeMot(curseur, (*mot).suiv, 1);
        }

        // Si ça nous fait changer de ligne
        // on change de ligne
        Ligne* ligne = (*curseur).ligne;
        if((*curseur).placeLigne > (*ligne).taille){
            changeLigne(curseur, (*ligne).suiv, 1);
        }
    }
}

void gauche(Curseur* curseur){
    Lettre* lettre = (*(*curseur).lettre).prev;

    if((*(*curseur).lettre).c != DEBUT){
        changeLettre(curseur, lettre);
        (*curseur).placeMot -= 1;
        (*curseur).placeLigne -= 1;

        Mot* mot = (*curseur).mot;
        if((*curseur).placeMot < 1){
            changeMot(curseur, (*mot).prev, (*(*mot).prev).taille);
        }

        Ligne* ligne = (*curseur).ligne;
        if((*curseur).placeLigne < 1){
            changeLigne(curseur, (*ligne).prev, (*(*ligne).prev).taille);
        }
    }
}

/**
 *  Place le curseur à une position donnée dans
 *  un mot de manière optimal (maximum O(n/2) )
 */
void viseDansMot(Curseur* curseur, Mot* mot, int cible){
    Lettre* lettre;
    int position;

    if(cible<=(((*mot).taille + 1)/2)){
        position = 0;

        lettre = (*mot).debut;

        while( cible > position ){
            position += 1;
            lettre = (*lettre).suiv;
        }
    }else{
        position = (*mot).taille - 1;

        lettre = (*(*(*mot).suiv).debut).prev;

        while(cible < position){
            position -= 1;
            lettre = (*lettre).prev;
        }
    }

    changeLettre(curseur, lettre);
    changeMot(curseur, mot, position + 1);
}

void viseDansLigne(Curseur* curseur, int cible, Ligne* ligne){
    if((*ligne).taille<=cible){
        Ligne* ligneSuiv = (*ligne).suiv;

        Lettre* lettre = (*(*(*ligneSuiv).debut).debut).prev;
        Mot* mot = (*(*ligneSuiv).debut).prev;

        changeLigne(curseur, ligne, (*ligne).taille);
        changeMot(curseur, mot, (*mot).taille);
        changeLettre(curseur, lettre);
    }else{
        Mot* mot;
        int cibleMot;

        if(cible < (((*ligne).taille + 1)/2)){
            mot = (*ligne).debut;

            int debutMot = 1;
            int finMot = (*mot).taille;
            while(cible>finMot){
                mot = (*mot).suiv;
                debutMot = finMot + 1;
                finMot += (*mot).taille;
            }

            cibleMot = cible - debutMot;
        }else{
            mot = (*(*(*ligne).suiv).debut).prev;

            int debutMot = (*ligne).taille - (*mot).taille + 1;
            //int finMot = (*ligne).taille;
            while(cible<debutMot){
                mot = (*mot).prev;
                //finMot = debutMot - 1;
                debutMot -= (*mot).taille;
            }

            cibleMot = cible - debutMot;
        }

        viseDansMot(curseur, mot, cibleMot);

        changeLigne(curseur, ligne, cible);
    }
}

void bas(Curseur* curseur){
    Ligne* ligne = (*(*curseur).ligne).suiv;

    int cible = (*curseur).placeLigne;

    if((*ligne).taille != 0){
        viseDansLigne(curseur, cible, ligne);
    }else{
        finDeLigne(curseur);
    }
}

void haut(Curseur* curseur){
    Ligne* ligne = (*(*curseur).ligne).prev;

    int cible = (*curseur).placeLigne;

    if(ligne != NULL){
        viseDansLigne(curseur, cible, ligne);
    }else{
        debutDeLigne(curseur);
    }
}
