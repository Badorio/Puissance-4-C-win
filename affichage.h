#ifndef AFFICHAGE_H_INCLUDED
#define AFFICHAGE_H_INCLUDED

void menu();
void difMenu();
void afficherGrille(int grille[6][7]); //On prend un tableau 6 lignes 7 colonnes car puissance 4 possède ces dimensions
void finJeu(int identiteGagnant, int modeJeu); //Message different en fonction de l'identite du gagnant
/*
Mode 1: 1 joueur
Mode 2: 2 joueurs
*/

void affDernierCoup(int tab[6][7], int colonne, int joueur);

#endif // AFFICHAGE_H_INCLUDED
