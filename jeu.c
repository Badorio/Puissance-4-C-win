#include <stdio.h>
#include <stdlib.h>
#include "jeu.h"


/*
On va évaluer l'état de la grille à un moment donné. On retournera le nombre de pions consécutifs maximums
d'un joueur
*/
int victoire(int grille[6][7]) //prend la grille
{
    int j1=0, j2=0;
    int *pj1, *pj2;
    pj1=&j1; pj2=&j2;

    nb_series(grille, pj1, pj2, 4);
    //printf("\n\n\tnb series 4 : %d %d", j1, j2);
    //Si le joueur 1 gagne
    if(j1>0)
        return 1;

    //Si le joueur 2 gagne
    else if(j2>0)
        return 2;

    //Si la partie est finie et que personne n'a gagné
    else if(verifPlein(grille)==1)
        return 0;

    //Si la partie n'est pas finie
    else
        return -1;
}

int ligne(int colonne, int grille[6][7]) //prend comme argument QUI joue et OU il joue
{
    int i;

    if(grille[0][colonne] != 0) //Si la colonne est pleine
        return -1; //Colonne pleine

    i=5;

    while(grille[i][colonne] != 0) //Tant qu'on ne trouve pas de case vide dans la colonne (en partant du bas bien sur)
    {
        i--; //On monte dans la grille pour trouver une case vide
    }

    //grille[i][colonne-1] = joueur; //Quand on a une case vide, on l'assigne au joueur en question
    return i;
}

void initGrille(int grille[6][7])
{
    int i, j;
    for(i=0; i<6; i++)
    {
        for(j=0; j<7; j++)
        {
            grille[i][j]=0;
        }
    }
}

int verifPlein(int grille[6][7])
{
    int i=0;
    while(grille[0][i] != 0 && i<7) //Tant qu'on a des pions en haut des colonnes et qu'on n'est pas au bout des colonnes
    {
        i++;
    }
    if(i==7) //si toutes les colonnes sont pleines
        return 1;
    else //sinon
        return 0;
}

void nb_series(int tab[6][7], int* s_j1, int* s_j2, int n)
{
    int cpt1, cpt2, i, j, k, l, cptDiag;

    *s_j1=0;
    *s_j2=0;


    //SERIES HORIZ
    for(i=0; i<6; i++)
    {
        cpt1=0; cpt2=0;
        for(j=0; j<7; j++) //Tant qu'on n'est pas au bout de la ligne
        {
            if(tab[i][j]==1)
            {
                cpt1++;
                cpt2=0;
                if(cpt1==n)
                    *s_j1+=1;
            }
            else if(tab[i][j]==2)
            {
                cpt2++;
                cpt1=0;
                if(cpt2==n)
                    *s_j2+=1;
            }
            else
            {
                cpt1=0; cpt2=0;
            }
        }
    }

    //SERIES VERTICALES
    for(j=0; j<7; j++)
    {
        cpt1=0; cpt2=0;
        for(i=0; i<6; i++)
        {
            if(tab[i][j]==1)
            {
                cpt1++;
                cpt2=0;
                if(cpt1==n){
                    *s_j1+=1;}
            }
            else if(tab[i][j]==2)
            {
                cpt2++;
                cpt1=0;
                if(cpt2==n){
                    *s_j2+=1;}
            }
            else
            {
                cpt1=0; cpt2=0;
            }
        }
    }

    //SERIES DIAGONALES 1
    for(i=0; i<6; i++)
    {
        for(j=0; j<7; j++)
        {
            cpt1=0; cpt2=0; cptDiag=0;
            k=i; l=j;
            do
            {
                if(tab[k][l]==1)
                {
                    cpt1++;
                    cpt2=0;
                    if(cpt1==n)
                        *s_j1+=1;
                }
                else if(tab[k][l]==2)
                {
                    cpt2++;
                    cpt1=0;
                    if(cpt2==n)
                        *s_j2+=1;
                }
                else
                {
                    cpt1=0; cpt2=0;
                }
                k++;
                l++;
                cptDiag++;
            }
            while(k<6 && l<7 && cptDiag<4);
        }
    }

    //SERIES DIAGONALES 2
    for(i=0; i<6; i++)
    {
        for(j=0; j<7; j++)
        {
            cpt1=0; cpt2=0; cptDiag=0;
            k=i; l=j;
            do
            {
                if(tab[k][l]==1)
                {
                    cpt1++;
                    cpt2=0;
                    if(cpt1==n){
                        *s_j1+=1;}
                }
                else if(tab[k][l]==2)
                {
                    cpt2++;
                    cpt1=0;
                    if(cpt2==n)
                        *s_j2+=1;
                }
                else
                {
                    cpt1=0; cpt2=0;
                }
                k++;
                l--;
                cptDiag++;
            }
            while(k<6 && l>=0 && cptDiag<n);
        }
    }
}

