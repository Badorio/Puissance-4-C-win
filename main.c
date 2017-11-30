#include <stdio.h>
#include <stdlib.h>
#include "affichageWin.h" //Fonctions uniques à windows
#include "affichage.h"//Fonctions d'affichage
#include "IA.h" //Les fonctions relatives à l'IA
#include "jeu.h" //Fonctions relatives au jeu en tant que tel


/*
BENJAMIN BELLUZ
HEPL INPRES, Informatique de gestion 1 2105
Dernière modification : 24/11/2017 14:05
Version en cours : 1.04 -> Version interne

1.0
-Version complète initiale
1.01
-ajout d'une possibilité de quitter en milieu de partie (1 joueur uniquement pour l'instant)
1.02
-ajout de la possibilité de quitter en partie en mode 2 joueurs
-correction flickering quand l'ordinateur joue
1.03
-ajout d'un visuel du dernier coup joué par l'adversaire
1.04
-ajout de commentaires et préparation en vue d'élagage alpha-beta

1.1
-élagage alpha-beta -> modes de difficulté modifiés
-ajout de commentaires
-simplification de la fonction d'évaluation -> l'ordinateur va essayer de gagner, et plus de faire des séries de 2 et 3. Juste gagner
-supprimer les fonctions min et max initiales -> plus que alphaBeta min et max
-ajout d'un message quand l'ordinateur réfléchit
*/


/*
ELAGAGE APLHA BETA!!
*/

/*
EZ DRAW POUR UNE INTERFACE UN PEU PLUS JOLIE
*/

/*
Attente avant affichage grille IA
*/

int main()
{
    int i, max, col, cpt, joueur;
    int grille[6][7];
    int *p1;
    int choixMenu;
    char reponse, chCol;
    int dif;

    p1=&max;

    printf("\nPuissance 4 en C pour Windows !\n\n");
    do
    {
        menu();
        fflush(stdin);
        scanf("%d", &choixMenu);
        effacerAff();
        initGrille(grille);

        switch(choixMenu)
        {
        //1 JOUEUR
        case 1:
            //DIFFICULTE DE LA PARTIE
            do
            {
                difMenu();
                fflush(stdin);
                scanf("%d", &dif);
                if(dif<1 || dif>4)
                    printf("\nCHOIX INCORRECT");
            }
            while(dif<1 || dif>4);

            //SAVOIR QUI COMMENCE
            do
            {
                printf("\nVoulez-vous jouer en premier ? (o/n)\n");
                fflush(stdin);
                scanf("%c", &reponse);
            }
            while(reponse != 'o' && reponse!='O' && reponse!= 'n' && reponse!='N');
            switch(reponse)
            {
            case 'o':
            case 'O':
                cpt=1;
                break;
            case 'n':
            case 'N':
                cpt=0;
                break;
            }

            //LE JEU A PROPREMENT PARLER COMMENCE ICI
            do
            {
                joueur=cpt%2+1;

                //Eviter de ne pas pouvoir recommencer une partie après en avoir quitté une et joueur en deuxieme
                chCol='0';

                switch(joueur)
                {
                //IA
                case 1:
                    effacerAff();
                    afficherGrille(grille);

                    printf("\n\nL'ordinateur reflechit...\n\n");

                    col=IAjouer(grille, p1, dif);
                    i=ligne(col, grille);
                    grille[i][col]=joueur;
                    break;
                //JOUEUR
                case 2:
                    //AFFICHAGES
                    effacerAff();
                    afficherGrille(grille);
                    if(cpt>1)
                        affDernierCoup(grille, col, (cpt-1)%2+1);

                    printf("\nA vous de jouer !\n");
                    //SAISIE COLONNE
                    printf("Colonne [1...7] :\nQ: quitter\n");
                    do
                    {
                        fflush(stdin);
                        scanf("%c", &chCol);

                        if(chCol!='q' && chCol!='Q')
                        {
                            col=chCol-49;
                            if(col<0||col>6)
                                printf("\nCHOIX INCORRECT !!\n");
                            else
                            {
                                if(ligne(col, grille)==-1)
                                    printf("\nColonne pleine !\n");
                            }
                        }
                        //ON AFFECTE UNE VALEUR DE COLONNE MEME SI ON QUITTE POUR EVITER LES ENNUIS DANS LE RESTE DU PROGRAMME
                        else
                            col=0;

                    }
                    while(col<0 || col>6 || ligne(col, grille)==-1);
                    //ON JOUE LE COUP DESIRÉ
                    i=ligne(col, grille);
                    grille[i][col]=joueur;

                    break;
                }
                //effacerAff();
                //afficherGrille(grille);
                //il faudrait la possibilité de faire attendre un peu avant l'affichage ici, pour eviter le flickering de quand l'ia joue

                cpt++;
            }
            while(victoire(grille)==-1 && verifPlein(grille)==0 && chCol!= 'Q' && chCol != 'q');
            //AFFICHER LA GRILLE A LA FIN
            afficherGrille(grille);
            affDernierCoup(grille, col, (cpt+1)%2+1);
            finJeu(victoire(grille), choixMenu);

            break;
        //2 JOUEURS
        case 2:
            afficherGrille(grille);

            do
            {
                joueur=cpt%2+1;

                switch(joueur)
                {
                case 1:
                    printf("\nLes bleus peuvent jouer !\n");
                    break;
                case 2:
                    printf("\nLes rouges peuvent jouer !\n");
                    break;
                }


                printf("Colonne [1...7] : \nQ: quitter\n");
                do
                {
                    fflush(stdin);
                    scanf("%c", &chCol);
                    if(chCol!='q' && chCol!='Q')
                    {
                        col=chCol-49;
                        if(col<0 || col>6)
                            printf("\nCHOIX INCORRECT !!\n");
                        else
                        {
                            if(ligne(col, grille)==-1)
                                printf("\nColonne pleine !\n");
                        }
                    }
                    else
                        col=0;
                }
                while(col<0 || col>6 || ligne(col, grille)==-1);

                //ON JOUE LE COUP DESIRÉ
                i=ligne(col, grille);
                grille[i][col]=joueur;

                effacerAff();
                afficherGrille(grille);
                affDernierCoup(grille, col, joueur);

                cpt++;
            }
            while(victoire(grille)==-1 && verifPlein(grille)==0 && chCol!='Q' && chCol!='q');
            finJeu(victoire(grille), choixMenu);

            break;
        case 3:
            printf("\n\nAu revoir !");
            break;
        default:
            printf("\n\nCHOIX INVALIDE !\n");
        }
    }
    while(choixMenu!=3);

    //Permet d'attendre une pression sur enter pour que l'utilisateur voit le message d'au revoir
    fflush(stdin);
    scanf("%c", &reponse);

    return 0;
}


