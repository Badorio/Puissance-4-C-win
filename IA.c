#include <stdio.h>
#include <stdlib.h>
#include "IA.h"
#include <time.h> //pour le srand()
#include "jeu.h"

//#define PROF 2
#define VALS2 1
#define VALS3 100
#define VALS4 10000
#define MAXINIT 1000000

/*
D'abord simuler mouvement IA une fois. Puis dans une boucle, simuler joueur puis IA.
=> On finit toujours par l'IA.
On garde juste en memoire la premiere colonne dans laquelle on a joué (hors de la boucle)
*/

//SIMULE UNE SERIE DE MOUVEMENTS CONSECUTIFS DANS LA GRILLE
//SORT LA COLONNE POUR LAQUELLE LE CHEMIN EST LE PLUS FAVORABLE
//ON EVALUE A LA FIN ET POUR DETERMINER QUEL MOUVEMENT LE JOUEUR VA SUREMENT FAIRE

int IAjouer(int grille[6][7], int *maxAdd, int dif)
{
    int i, j, max[2], val;
    int tab[6][7];
    int profondeur;
    //CHOIX DIFFICULTE
    switch(dif)
    {
    //FACILE
    case 1:
        profondeur=2;
        break;
    //MOYEN
    case 2:
        profondeur=3;
        break;
    //DIFFICILE
    case 3:
        profondeur=4;
        break;
    //TRES DIFFICILE
    case 4:
        profondeur=5;
        break;
    //PAR DEFAULT
    default:
        profondeur=3;
    }

    max[0]=-MAXINIT;

    maxAdd=&max[0];

    copyTab(grille, tab);

    //POUR TOUS LES COUPS
    for(j=0; j<7; j++)
    {
        i=ligne(j, tab);
        //SI LA COLONNE EST VIDE
        if(i!= -1)
        {
            //ON SIMULE UN COUP DE L'IA
            tab[i][j]=1;
            //IL FAUT DONC QUE MIN SIMULE UN COUP DU JOUEUR!!!
            val=IAmin(tab, profondeur-1);

            if(val>max[0] || ((val == max[0]) && (rand()%2 == 0)))
            {
                max[0] = val;
                max[1] = j;
            }
            suppPion(tab, j);
        }
    }
    //ON RENVOIE LA COLONNE
    return max[1];
}

int IAmin(int tab[6][7], int profondeur)
{
    if(profondeur == 0 || victoire(tab)!=-1)
    {
        return IAeval(tab);
    }

    int min = MAXINIT;
    int i,j,tmp;

    for(j=0; j<7; j++)
    {
        i=ligne(j, tab);
        if(i != -1)
        {
            //ON AVAIT UN 1 ICI
            //DU COUP LE PC JOUAIT 2x DE SUITE DANS LA SIMU
            //DU COUP IL NE CONTRAIT PAS A TEMPS
            //PROBLEME RESOLU
            //BINGO
            tab[i][j] = 2;
            tmp = IAmax(tab,profondeur-1);

            if(tmp < min || ((tmp == min) && (rand()%2 == 0)))
            {
                min = tmp;
            }
            tab[i][j] = 0;
        }
    }

    return min;

}




int IAmax(int tab[6][7], int profondeur)
{
    if(profondeur == 0 || victoire(tab)!=-1)
    {
        return IAeval(tab);
    }

    int max = -MAXINIT;
    int i,j,tmp;
    //MODIFIER LES BOUCLES
    for(j=0; j<7; j++)
    {
        //SI LA COLONNE EST LIBRE
        if(tab[0][j] == 0)
        {
            i=ligne(j, tab);
            //ON AVAIT UN 2 ICI
            //DU COUP CA MERDAIT
            tab[i][j] = 1;
            tmp = IAmin(tab,profondeur-1);

            if(tmp > max || ((tmp == max) && (rand()%2 == 0)))
            {
                max = tmp;
            }
            tab[i][j] = 0;
        }
    }
    return max;
}


//EVALUE UN ETAT DE LA GRILLE
//SERIES DE 2 +
//SERIES DE 3 ++
//SERIES DE 4 ++++
//HORIZ, VERTIC, DIAGO
//IA : 1
//JOUEUR : 2
int IAeval(int grille[6][7])
{
    int vainqueur, nb_pions=0, val=0;
    int i, j;
    int series2_J1=0, series2_J2=0;
    int series3_J1=0, series3_J2=0;
    //On a juste besoin de deux pointeurs à la fois. On peut les modifier au besoin.
    int *p1, *p2;

    //COMPTER NB PIONS
    for(i=0; i<6; i++)
    {
        for(j=0; j<7; j++)
        {
            if(grille[i][j] != 0)
                nb_pions++;
        }
    }

    vainqueur=victoire(grille);
    //Si quelqu'un gagne
    if(vainqueur != -1)
    {
        if(vainqueur==1)
            //pour gagner le plus vite possible
            return MAXINIT - nb_pions;
        //pour perdre le moins vite possible
        else if(vainqueur==2)
            return -MAXINIT + nb_pions;
        //Si partie a egalité
        else if(vainqueur==0)
            return 0;
    }

    p1=&series2_J1;
    p2=&series2_J2;
    nb_series(grille, p1, p2, 2);

    p1=&series3_J1;
    p2=&series3_J2;
    nb_series(grille, p1, p2, 3);

    //printf("\n\t s2 j1: %d \tj2: %d", series2_J1, series2_J2);

    val = VALS2 * (series2_J1-series2_J2) + VALS3 * (series3_J1-series3_J2);
    return val;
}


//COPIE UN TABLEAU DANS UN AUTRE
void copyTab(int entree[6][7], int sortie[6][7])
{
    int i, j;
    for(i=0; i<6; i++)
    {
        for(j=0; j<7; j++)
        {
            sortie[i][j]=entree[i][j];
        }
    }
}


void suppPion(int tab[6][7], int col)
{
    int i=0;
    while(tab[i][col]==0)
    {
        i++;
    }
    tab[i][col] = 0;
}
