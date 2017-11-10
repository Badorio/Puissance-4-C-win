#include <stdio.h>
#include <stdlib.h>
#include "affichage.h"
#include "affichageWin.h"

//TEXTE
#define BLACK   "\x1b[30m"
#define GREY    "\x1b[30;1m"
#define RED     "\x1b[31;1m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34;1m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"
//BACKGROUND
#define BBLACK   "\x1b[40m"
#define BGREY    "\x1b[100m"
#define BRED     "\x1b[101m"
#define BGREEN   "\x1b[42m"
#define BYELLOW  "\x1b[43m"
#define BBLUE    "\x1b[104m"
#define BMAGENTA "\x1b[45m"
#define BCYAN    "\x1b[46m"



void menu()
{
    printf("\n\n\n1) Un joueur (contre l'ordinateur)");
    printf("\n2) Deux joueurs (l'un apres l'autre)");
    printf("\n3) Quitter\n\n");
}

void difMenu()
{
    printf("\nDifficulte : \n");
    printf("1: Facile\n");
    printf("2: Moyen\n");
    printf("3: Difficile\n");
    printf("4: Tres difficile\n");
}

void afficherGrille(int grille[6][7])
{
    int i, j, k;

    for(k=0; k<7; k++)
    {
        color(0,0);
        printf("OO");
        color(15,0);
        printf("%d", k+1);
        color(0,0);
        printf("OOOO");
    }
    printf("\n\n");
    for(i = 0; i <=5; i++) //On parcourt les lignes
    {
        for(k=0; k<7; k++)
        {
            color(8,8);
            printf("OOOOOO");
            color(0,0);
            printf("O");
        }
        printf("\n");
        for(j=0; j<7; j++) //On parcourt les colonnes
        {
            switch(grille[i][j])
            {
            case 0:
                color(8,8);
                printf("OOOOOO");
                break;
            case 1:
                color(8,8);
                printf("OO");
                color(9,9);
                printf("OO");
                color(8,8);
                printf("OO");
                break;
            case 2:
                color(8,8);
                printf("OO");
                color(12,12);
                printf("OO");
                color(8,8);
                printf("OO");
                break;
            }
            color(0,0);
            printf("O");
        }
        printf("\n");
        for(k=0; k<7; k++)
        {
            color(8,8);
            printf("OOOOOO");
            color(0,0);
            printf("O");
        }

        printf("\n\n");
    }
    for(k=0; k<7; k++)
    {
        color(0,0);
        printf("OO");
        color(15,0);
        printf("%d", k+1);
        color(0,0);
        printf("OOOO");
    }
    printf("\n\n");
    color(15,0);
}


void finJeu(int identiteGagnant, int modeJeu)
{
    //1 joueur
    if(modeJeu==1)
    {
        if(identiteGagnant == 2)
        {
            printf("\nVous avez battu l'ordinateur !\n");
        }
        else if(identiteGagnant == 1) //si l'ia gagne
        {
            printf("\nL'ordinateur gagne !\n");
        }
        else if(identiteGagnant==0)
        {
            printf("\n\nEgalite !");
        }
        else
            printf("\n\nVous avez quitte la partie.");

    }
    //deux joueurs
    else if(modeJeu==2)
    {
        if(identiteGagnant == 1) //si le joueur 1 gagne
        {
            printf("\nLes bleus gagnent !\n");
        }
        else if(identiteGagnant == 2) //si le joueur 2 gagne
        {
            printf("\nLes rouges gagnent !\n");
        }
        else if(identiteGagnant==0)
        {
            printf("\n\nEgalite !");
        }
        else
            printf("\n\nVous avez quitte la partie.");
    }
}
