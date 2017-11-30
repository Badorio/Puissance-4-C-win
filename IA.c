#include <stdio.h>
#include <stdlib.h>
#include "IA.h"
#include <time.h> //pour le srand()
#include "jeu.h"

//#define PROF 2
#define VALS2 1
#define VALS3 100
#define VALS4 1000
#define MAXINIT 100000


//SIMULE UNE SERIE DE MOUVEMENTS CONSECUTIFS DANS LA GRILLE
//SORT LA COLONNE POUR LAQUELLE LE CHEMIN EST LE PLUS FAVORABLE
//ON EVALUE A LA FIN ET POUR DETERMINER QUEL MOUVEMENT LE JOUEUR VA SUREMENT FAIRE

/*
Pour résumer, on avait 2 problèmes dans les fonctions alpha beta min et alpha beta max:
1 : on ne supprimait le pion qu'après les vérif, du coup lors de coupures alpha ou beta, on ne supprimait pas !
2 : dans la fonction min, on faisait jouer l'ia au lieu du joueur..
Du coup l'ia pensait pouvoir jouer seule :haha:
*/


int IAjouer(int grille[6][7], int *maxAdd, int dif)
{
    int i, j, max[2], val;
    int tab[6][7];
    int profondeur;
    int colonne;

    profondeur=profondeurMod(dif, grille);


    printf("\nprof %d\n", profondeur);

    max[0]=-MAXINIT;
    //Moyen de récupérer la valeur du maximum
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
            val=alphaBetaMin(tab, max[0], MAXINIT, profondeur-1);

            //if(val>max[0] || ((val == max[0]) && (rand()%2 == 0)))
            if(val>max[0])
            {
                max[0] = val;
                max[1] = j;
            }
            suppPion(tab, j);
        }
    }
    return max[1];
}


int alphaBetaMax(int tab[6][7], int alpha, int beta, int profondeur) //VERIFIER L'ALGORITHME !!!
{
    //printf("\nprof max: %d", profondeur);
    if(profondeur == 0 || victoire(tab)!=-1)
    {
        return IAeval(tab);
    }

    int i, j, tmp;
    //Pour chaque coup possible
    for(j=0; j<7; j++)
    {
        if(tab[0][j] == 0)
        {
            i=ligne(j, tab);
            tab[i][j] = 1;

            tmp = alphaBetaMin(tab, alpha, beta, profondeur-1);
//Condition pour ne pas toujours jouer au même endroit
//Avec alpha ici au lieu de max
//            if(tmp > max || ((tmp == max) && (rand()%2 == 0)))


            //Si c'est parce qu'on supprimait pas le pion avant de retourner beta que ca merdait, je vais rager
            //Supprimer le pion
            //Ca a déjà résolu une bonne partie des problèmes.. l'ordinateur ne rempli déjà plus bêtement la grille !
            //Sauf qu'il n'a pas vraiment envie de me contrer on dirait -> Trouver d'où ce problème vient !
            tab[i][j] = 0;

            //Coupure beta
            if(tmp >= beta)
                return beta;

            if(tmp > alpha)
                alpha = tmp;
        }
    }
    return alpha;
}

int alphaBetaMin(int tab[6][7], int alpha, int beta, int profondeur)
{
    //printf("\nprof min: %d", profondeur);
    if(profondeur == 0 || victoire(tab)!=-1)
    {
        return IAeval(tab);
    }

    int i, j, tmp;
    //Pour chaque coup possible
    for(j=0; j<7; j++)
    {
        if(tab[0][j] == 0)
        {
            i=ligne(j, tab);

            //IL Y AVAIT UN 1 ICI !! JE CROIS QUE C'EST POUR CA QU'IL NE CONTRAIT RIEN !
            //DANS LA SIMULATION IL N'Y A QUE L'IA QUI JOUAIT !
            tab[i][j] = 2;

            tmp = alphaBetaMax(tab, alpha, beta, profondeur-1);

//            if(tmp > max || ((tmp == max) && (rand()%2 == 0)))

            //Supprimer le pion
            tab[i][j] = 0;

            //Coupure alpha
            if(tmp <= alpha)
                return alpha;

            if(tmp < beta)
                beta = tmp;
        }
    }
    return beta;
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

    //pour gagner le plus vite possible
    if(vainqueur==1)
        val = VALS4 - nb_pions;
    //pour perdre le moins vite possible
    else if(vainqueur==2)
        val = -VALS4 + nb_pions;

    //Si il y égalité ou que la partie n'est pas finie, on renvoit 0

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

//SUPPRIME LE PREMIER PION D'UNE COLONNE
void suppPion(int tab[6][7], int col)
{
    int i=0;
    while(tab[i][col]==0)
    {
        i++;
    }
    tab[i][col] = 0;
}

int profondeurMod(int difficulte, int tab[6][7])
{
    int nb_pions=0;
    int i, j, profondeur;
    float coef, new_prof;

    switch(difficulte)
    {
    case 1:
        profondeur=4;
        break;
    case 2:
        profondeur=8;
        break;
    case 3:
        profondeur=12;
        break;
    case 4:
        profondeur=18;
        break;
    default:
        profondeur=8;
    }

    //Nombre de pions
    for(i=0; i<6; i++)
    {
        for(j=0; j<7; j++)
        {
            if(tab[i][j] != 0)
                nb_pions++;
        }
    }
    const pions = 27;

    if(nb_pions <= pions)
        coef = (float)nb_pions/pions;

    if(coef<0.5)
        coef=0.5;

    new_prof=profondeur*coef;
    profondeur=(int)new_prof;

    return profondeur;
}
