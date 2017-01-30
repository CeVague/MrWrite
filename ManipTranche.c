#include <stdio.h>
#include <stdlib.h>
#include "ManipTranche.h"

/**
 *  Initialise un pointeur
 */
Curseur* initialise(Lettre* lettre, Mot* mot, Ligne* ligne, int placeMot, int placeLigne){
    Curseur* curseur = malloc(sizeof(Curseur));

    (*curseur).lettre = lettre;
    (*curseur).mot = mot;
    (*curseur).ligne = ligne;
    (*curseur).tailleMot = &((*mot).taille);
    (*curseur).tailleLigne = &((*ligne).taille);
    (*curseur).placeMot = placeMot;
    (*curseur).placeLigne = placeLigne;

    return curseur;
}

/**
 *  R�cup�re le caract�re point� par le curseur
 */
char get(Curseur* curseur){
    return (*(*curseur).lettre).c;
}

/**
 *  Met � jour la ligne point� par le curseur et sa position
 */
void changeLigne(Curseur* curseur, Ligne* ligne, int placeLigne){
    (*curseur).ligne = ligne;
    (*curseur).tailleLigne = &((*ligne).taille);
    (*curseur).placeLigne = placeLigne;
}

/**
 *  Met � jour le mot point� par le curseur et sa position
 */
void changeMot(Curseur* curseur, Mot* mot, int placeMot){
    (*curseur).mot = mot;
    (*curseur).tailleMot = &((*mot).taille);
    (*curseur).placeMot = placeMot;
}

/**
 *  Met � jour la lettre point� par le curseur
 */
void changeLettre(Curseur* curseur, Lettre* lettre){
    (*curseur).lettre = lettre;
}

/**
 *  Saute en fin de mot
 */
void finDeMot(Curseur* curseur){
    (*curseur).lettre = (*(*(*(*curseur).mot).suiv).debut).prev;
    (*curseur).placeMot = (*(*curseur).mot).taille;
}

/**
 *  Saute en d�but de mot
 */
void debutDeMot(Curseur* curseur){
    (*curseur).lettre = (*(*curseur).mot).debut;
    (*curseur).placeMot = 1;
}

/**
 *  Saute en fin de mot
 */
void finDeLigne(Curseur* curseur){
    Ligne* ligne = (*(*curseur).ligne).suiv;

    Lettre* lettre = (*(*(*ligne).debut).debut).prev;
    Mot* mot = (*(*ligne).debut).prev;
    ligne = (*curseur).ligne;

    changeLigne(curseur, ligne, (*ligne).taille);
    changeMot(curseur, mot, (*mot).taille);
    changeLettre(curseur, lettre);
}

/**
 *  Saute en d�but de mot
 */
void debutDeLigne(Curseur* curseur){
    changeLigne(curseur, (*curseur).ligne, 1);
    changeMot(curseur, (*(*curseur).ligne).debut, 1);
    changeLettre(curseur, (*(*curseur).mot).debut);
}

/**
 *  Enl�ve une lettre et diminue la taille du mot et
 *  de la ligne concern�e
 */
Lettre* supprSimple(Lettre* lettre, Mot* mot, Ligne* ligne){
    lettre = supprLettre(lettre);
    (*mot).taille -= 1;
    (*ligne).taille -= 1;

    return lettre;
}

/**
 *  Supprime proprement le caract�re point� par le curseur
 */
void suppr(Curseur* curseur){
    Lettre* lettre = (*curseur).lettre;
    Mot* mot = (*curseur).mot;
    Ligne* ligne = (*curseur).ligne;

    // On m�morise la lettre point�e
    char c = get(curseur);

    // On la supprime et r�cup�re la suivante
    lettre = supprSimple(lettre, mot, ligne);

    // On place le curseur sur cette rempla�ante
    changeLettre(curseur, lettre);

    // Si on vient de supprimer un espace ou un retour � la ligne
    if(c == ' ' || c == '\n'){

        /* mani�re plus naturelle de voir
        ce qu'on fait

        gauche(curseur);
        fusioneMot(mot);
        droite(curseur);*/

        // On fusionne notre mot et le pr�c�dent
        Mot* prevMot = (*mot).prev;
        changeMot(curseur, prevMot, (*prevMot).taille + 1);
        fusioneMot(mot);

        // Si on a supprim� un retour chariot
        if(c == '\n'){
            // On fusionne notre ligne et la pr�c�dente
            Ligne* prevLigne = (*ligne).prev;
            changeLigne(curseur, prevLigne, (*prevLigne).taille + 1);
            fusioneLigne(ligne);
        }
    }
}
