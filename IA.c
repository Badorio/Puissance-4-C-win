#include <stdio.h>
#include <stdlib.h>
#include "IA.h"
#include <time.h> //pour le srand()
#include "jeu.h"


#define VALS2   1
#define VALS3   100
#define VALS4   10000
#define MAXINIT 1000000

#define PROF_DIF_1  4
#define PROF_DIF_2  8
#define PROF_DIF_3  12
#define PROF_DIF_4  16

/*
On a un problème avec l'heuristique ! Au début du jeu, il est TRES intéressant de récompenser les séries
de 2 et 3 pions. En effet, il est difficilé, même avec une profondeur de 10 coups, de faire un coup gagnant au début du jeu.
Dès lors, il serait intéressant de restaurer la fonction d'évaluation à son algorithme original.
On pourrait, peut-être, utiliser une heuristique plus simple pour la fin de partie. À tester !

En plus, potentiel problème avec la profondeur en fin de jeu pour l'instant...
*/



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
    int tab[7][7]; //Une ligne en plus pour garder en mémoire la première ligne libre de chaque colonne
    int profondeur;
//    int profIterativeDeepening;


    profondeur=profondeurMod(dif, grille);


    printf("\nprof %d\n", profondeur);

    max[0]=-MAXINIT;
    //Moyen de récupérer la valeur du maximum
    maxAdd=&max[0];

    copyTab(grille, tab);

    for(j=0; j<7; j++)
    {
        tab[6][j] = ligne(j, tab);
    }

    //POUR TOUS LES COUPS
    //Ca ne fonctionne pas aussi bêtement que ça...
    //for(profIterativeDeepening=0; profIterativeDeepening<=profondeur; profIterativeDeepening++){
    for(j=0; j<7; j++)
    {
        //i=ligne(j, tab);
        i=tab[6][j];
        //SI LA COLONNE EST VIDE
        if(tab[6][j] != -1)
        {
            //ON SIMULE UN COUP DE L'IA
            tab[i][j]=1;
            tab[6][j]-=1;
            val=alphaBetaMin(tab, max[0], MAXINIT, profondeur-1);

            //if(val>max[0] || ((val == max[0]) && (rand()%2 == 0)))
            if(val>max[0])
            {
                max[0] = val;
                max[1] = j;
            }
            suppPion(tab, j);
            tab[6][j]+=1;
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
            //i=ligne(j, tab);
            i=tab[6][j];
            tab[i][j] = 1;
            tab[6][j]-=1;

            tmp = alphaBetaMin(tab, alpha, beta, profondeur-1);
//Condition pour ne pas toujours jouer au même endroit
//Avec alpha ici au lieu de max
//            if(tmp > max || ((tmp == max) && (rand()%2 == 0)))


            //Si c'est parce qu'on supprimait pas le pion avant de retourner beta que ca merdait, je vais rager
            //Supprimer le pion
            //Ca a déjà résolu une bonne partie des problèmes.. l'ordinateur ne rempli déjà plus bêtement la grille !
            //Sauf qu'il n'a pas vraiment envie de me contrer on dirait -> Trouver d'où ce problème vient !
            tab[i][j] = 0;
            tab[6][j]+=1;

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
            //i=ligne(j, tab);//AMELIORER ICI
            i=tab[6][j];
            //IL Y AVAIT UN 1 ICI !! JE CROIS QUE C'EST POUR CA QU'IL NE CONTRAIT RIEN !
            //DANS LA SIMULATION IL N'Y A QUE L'IA QUI JOUAIT !
            tab[i][j] = 2;
            tab[6][j]-=1;

            tmp = alphaBetaMax(tab, alpha, beta, profondeur-1);

//            if(tmp > max || ((tmp == max) && (rand()%2 == 0)))

            //Supprimer le pion
            tab[i][j] = 0;
            tab[6][j]+=1;
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


    //Si il y égalité, on renvoit 0

    if(vainqueur != -1)
    {

        //pour gagner le plus vite possible
        if(vainqueur==1)
            val = VALS4 - nb_pions;
        //pour perdre le moins vite possible
        else if(vainqueur==2)
            val = -VALS4 + nb_pions;
        //Si partie a egalité
        else if(vainqueur==0)
            val = 0;
    }
    //Si la partie n'est pas finie, on renvoit une valeur calculée en fonction des séries de 2 et 3 pions
    else
    {
        p1=&series2_J1;
        p2=&series2_J2;
        nb_series(grille, p1, p2, 2);

        p1=&series3_J1;
        p2=&series3_J2;
        nb_series(grille, p1, p2, 3);

        //printf("\n\t s2 j1: %d \tj2: %d", series2_J1, series2_J2);

        val = VALS2 * (series2_J1-series2_J2) + VALS3 * (series3_J1-series3_J2); //On peut rajouter -1 dans les parenthèses pour rendre
        //l'IA plus défensive -> pourrait être utile pour des profondeurs faibles, mais pas certain.
    }
    //On renvoit la valeur calculée, quelle qu'elle soit
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
    int nb_pions=0, pionsMax;
    int i, j, profondeur, profModulee;
    float coef, new_prof;

    switch(difficulte)
    {
    case 1:
        profondeur=PROF_DIF_1;
        pionsMax=1;
        break;
    case 2:
        profondeur=PROF_DIF_2;
        pionsMax=8;
        break;
    case 3:
        profondeur=PROF_DIF_3;
        pionsMax=20;
        break;
    case 4:
        profondeur=PROF_DIF_4;
        pionsMax=26;
        break;
    default:
        profondeur=PROF_DIF_2;
        pionsMax=8;
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


    if(nb_pions <= pionsMax)
    {
        coef = (float)nb_pions/pionsMax;
        if(coef<0.5)
            coef=0.5;
    }
    else
        coef=1;

    new_prof=profondeur*coef;
    profModulee=(int)new_prof;

    return profModulee;
}
