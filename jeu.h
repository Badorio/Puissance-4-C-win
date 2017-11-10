#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED


//Fonction qui verifie si il y a victoire et qui a gagné
int victoire(int grille[6][7]);


//NE PAS TOUCHER
int ligne(int colonne, int grille[6][7]); //Fonction principale du jeu  ARG: Qui joue; OU il joue
/*
Codes de retour :
0: tout s'est bien passé
-1: colonne pleine

*/

//INITIALISE LA GRILLE A 0
void initGrille(int grille[6][7]);

//VERIFIE SI LES COLONNES SONT PLEINES OU PAS
int verifPlein(int grille[6][7]);

//COMPTE LE NOMBRE DE SERIES DE n PIONS ALIGNES DANS LA GRILLE
void nb_series(int tab[6][7], int* s_j1, int* s_j2, int n);

#endif // JEU_H_INCLUDED
