#ifndef IA_H_INCLUDED
#define IA_H_INCLUDED

/*
Dans la fonction d'evaluation : series de deux pions, trois pions, deux pions suivi d'un autre avec un espace entre,
deux pions avec un espace entre eux, etc
*/

int IAjouer(int grille[6][7], int *maxAddn, int dif);

int alphaBetaMax(int tab[6][7], int alpha, int beta, int profondeur);
int alphaBetaMin(int tab[6][7], int alpha, int beta, int profondeur);

int IAeval(int grille[6][7]);

void copyTab(int entree[6][7], int sortie[6][7]);
void suppPion(int tab[6][7], int col);

int profondeurMod(int difficulte, int tab[6][7]);

#endif // IA_H_INCLUDED
