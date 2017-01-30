#include <stdio.h>
#include <stdlib.h>

#include <time.h>


//#include "conio21\conio.c"

#include "Structure.h"

#include "GestionTouches.h"
#include "ManipTranche.h"


#if defined(__WIN32__)

#include "conio21\conio.c"

void affiche(Lettre* l){
    l = (*l).suiv;
    while((*l).suiv != NULL){
        printf("%c",(*l).c);
        l = (*l).suiv;
    }
}

void afficheLettre(Lettre* l){
    while((*l).suiv != NULL){
        if((*l).c != '\n'){
            printf("%c",(*l).c);
        }else{
            printf("#");
        }
        l = (*l).suiv;
    }
}

void afficheMot(Mot* m){
    int ID = 0;
    while((*m).suiv != NULL){
        int i;
        for(i=0;i<(*m).taille;i++){
            printf("%d", ID);
        }
        ID += 1;
        m = (*m).suiv;
    }
}

void afficheLigne(Ligne* l){
    int ID = 0;
    while((*l).suiv != NULL){
        int i;
        for(i=0;i<(*l).taille;i++){
            printf("%d", ID);
        }
        ID += 1;
        l = (*l).suiv;
    }
}
/*
void afficheCurseur(Curseur c){
    printf("On est en Le/Mo/Li : %d/%d/%d\n", c.lettre, c.mot, c.ligne);
    printf("Les tailles sont Mo/Li : %d/%d\n", *(c.tailleMot), *(c.tailleLigne));
    printf("Emplacement : %d/%d\n\n\n", c.placeMot, c.placeLigne);
}
*/


char randomChar(){
    int temp = rand()%15;

    switch(temp) {
        case 0 :
            return 72;
            break;
        case 1 :
            return 80;
            break;
        case 2 :
            return 77;
            break;
        case 3 :
            return 75;
            break;
        case 4 :
            return 13;
            break;
        case 5 :
            return 8;
            break;
        case 6 :
            return 83;
            break;
        case 7 :
            return 8;
            break;
        case 8 :
            return 8;
            break;
        case 9 :
            return 75;
            break;
        case 10 :
            return ' ';
            break;
        default :
            return (48 + rand()%74);
    }
}

void ouvrirFichier(char* chemin, Curseur* curseur){
    FILE* fichier = NULL;
    int c = 0;

    fichier = fopen(chemin, "r");

    if (fichier != NULL)
    {
        c = fgetc(fichier);
        while (c != EOF)
        {
            inserer(curseur, c);
            c = fgetc(fichier);
        }

        fclose(fichier);
    }
}

int main()
{
    srand(time(NULL));

    Ligne* ligne = newChaineLigne();
    Mot* mot = (*ligne).debut;
    Lettre* lettre = (*mot).debut;

    Curseur* curseur = initialise(lettre, mot, ligne, 1, 1);

    printf("Bienvenue dans l'editeur MrWrite\n\n\n");
    printf("Appuyez sur '²'(cube) pour quiter.\n\nAppyez sur 'o' pour ouvrir un fichier ou 'entree' pour continuer.");

    char c = -3;

    c = getch();

    if(c==-3){
        return 0;
    }else if(c==111 || c==79){
        clrscr();
        printf("Bienvenue dans l'editeur MrWrite\n\n\n");
        printf("Entrez le chemin vers le fichier :\n");
        char temp[100];
        scanf("%s", temp);
        ouvrirFichier(temp, curseur);
    }

    clrscr();

    do{
        printf("Bienvenue dans l'editeur MrWrite\n\n\n");

        inserer(curseur, '|');
        affiche(lettre);
        toucheDel(curseur);
/*
        printf("\n\n\n\n");
        printf("%d", c);
        printf("\n\n\n\n");
        afficheLettre(lettre);
        printf("\n");
        afficheMot(mot);
        printf("\n");
        afficheLigne(ligne);
        printf("\n");
        printf("(%d, %d)", (*curseur).placeMot, (*curseur).placeLigne);
        printf("\n");
*/
        c = getch();
        //c = randomChar();

        clrscr();

        switch(c) {
            case -3 :
                break;
            case -32 :
                break;
            case 72 :
                haut(curseur);
                break;
            case 80 :
                bas(curseur);
                break;
            case 77 :
                droite(curseur);
                break;
            case 75 :
                gauche(curseur);
                break;
            case 13 :
                inserer(curseur, '\n');
                break;
            case 8 :
                toucheDel(curseur);
                break;
            case 83 :
                toucheSuppr(curseur);
                break;
            default :
                inserer(curseur, c);
        }

    }while(c != -3);


    return 0;
}

#endif

#if defined(__LINUX__)
void affiche(Lettre* l){
    l = (*l).suiv;
    while((*l).suiv != NULL){
        printf("%c",(*l).c);
        l = (*l).suiv;
    }
}

void afficheLettre(Lettre* l){
    while((*l).suiv != NULL){
        if((*l).c != '\n'){
            printf("%c",(*l).c);
        }else{
            printf("#");
        }
        l = (*l).suiv;
    }
}

void afficheMot(Mot* m){
    int ID = 0;
    printf("|");
    while((*m).suiv != NULL){
        int i;
        for(i=1;i<(*m).taille;i++){
            printf("-");
            //printf("%d", ID);
        }
        printf("|");
        ID += 1;
        m = (*m).suiv;
    }
}

void afficheLigne(Ligne* l){
    int ID = 0;
    printf("|");
    while((*l).suiv != NULL){
        int i;
        for(i=1;i<(*l).taille;i++){
            printf("-");
            //printf("%d", ID);
        }
        printf("|");
        ID += 1;
        l = (*l).suiv;
    }
}
/*
void afficheCurseur(Curseur c){
    printf("On est en Le/Mo/Li : %d/%d/%d\n", c.lettre, c.mot, c.ligne);
    printf("Les tailles sont Mo/Li : %d/%d\n", *(c.tailleMot), *(c.tailleLigne));
    printf("Emplacement : %d/%d\n\n\n", c.placeMot, c.placeLigne);
}
*/


char randomChar(){
    int temp = rand()%15;

    switch(temp) {
        case 0 :
            return 72;
            break;
        case 1 :
            return 80;
            break;
        case 2 :
            return 77;
            break;
        case 3 :
            return 75;
            break;
        case 4 :
            return 13;
            break;
        case 5 :
            return 8;
            break;
        case 6 :
            return 83;
            break;
        case 7 :
            return 8;
            break;
        case 8 :
            return 8;
            break;
        case 9 :
            return 75;
            break;
        case 10 :
            return ' ';
            break;
        default :
            return (48 + rand()%74);
    }
}

void ouvrirFichier(char* chemin, Curseur* curseur){
    FILE* fichier = NULL;
    int c = 0;

    fichier = fopen(chemin, "r");

    if (fichier != NULL)
    {
        c = fgetc(fichier);
        while (c != EOF)
        {
            inserer(curseur, c);
            c = fgetc(fichier);
        }

        fclose(fichier);
    }
}

char getch(){
    system("/bin/stty raw");
    char c = getchar();
    system("/bin/stty cooked");

    return c;
}

void boucleBest(){
    srand(time(NULL));

    Ligne* ligne = newChaineLigne();
    Mot* mot = (*ligne).debut;
    Lettre* lettre = (*mot).debut;

    Curseur* curseur = initialise(lettre, mot, ligne, 1, 1);

    printf("Bienvenue dans l'editeur MrWrite\n\n\n");
    printf("Appuyez sur '²'(cube) pour quiter.\n\nAppyez sur 'o' pour ouvrir un fichier ou 'entree' pour continuer.");

    char c = getch();

    if(c==-59){
        return ;
    }else if(c==111 || c==79){
        system("clear");
        printf("Bienvenue dans l'editeur MrWrite\n\n\n");
        printf("Entrez le chemin vers le fichier :\n");
        char temp[100];
        scanf("%s", temp);
        ouvrirFichier(temp, curseur);
    }

    system("clear");

    do{
        printf("Bienvenue dans l'editeur MrWrite\n\n\n");

        inserer(curseur, '|');
        affiche(lettre);
        toucheDel(curseur);

        printf("\n\n\n\n");






        printf("%d", c);
        printf("\n\n\n\n");
        printf("\nLettres: ");
        afficheLettre(lettre);
        printf("\nMots   : ");
        afficheMot(mot);
        printf("\nLignes : ");
        afficheLigne(ligne);
        printf("\n");
        printf("Curseur en position (%d, %d)", (*curseur).placeMot, (*curseur).placeLigne);
        printf("\n");







        c = getch();
        //c = randomChar();

        system("clear");

        switch(c) {
            case -59 :
                c = getchar();
                break;
            case 91 :
                break;
            case 51 :
                break;
            case 27 :
                if(getchar()==91){
                    c = getchar();
                    switch(c){
                        case 51 :
                            if(getchar()==126){
                                toucheSuppr(curseur);
                            }
                            break;
                        case 65 :
                            haut(curseur);
                            break;
                        case 66 :
                            bas(curseur);
                            break;
                        case 67 :
                            droite(curseur);
                            break;
                        case 68 :
                            gauche(curseur);
                            break;
                    }
                }
                break;
            case 13 :
                inserer(curseur, '\n');
                break;
            case 127 :
                toucheDel(curseur);
                break;
            default :
                inserer(curseur, c);
        }

    }while(c != -109);
}

int main()
{
    boucleBest();

    /*
    char c;
    while(1==1){
        c = getch();
        printf("\n%d\n", c);

    }
    */

    return 0;
}
#endif 