#ifndef _GTOUCHE_
#define _GTOUCHE_

#include "Structure.h"
#include "ManipTranche.h"

void toucheEntree(Curseur* curseur);
void toucheEspace(Curseur* curseur);
void toucheSuppr(Curseur* curseur);
void toucheDel(Curseur* curseur);
void toucheLettre(Curseur* curseur, char c);
void inserer(Curseur* curseur, char c);

void droite(Curseur* curseur);
void gauche(Curseur* curseur);
void bas(Curseur* curseur);
void haut(Curseur* curseur);

#endif
