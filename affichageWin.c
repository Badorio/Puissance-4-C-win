#include <stdio.h>
#include <stdlib.h>
#include <windows.h> //pour la fonction system(cls) En fait ce sera surement juste necessaire dans la fonction jeu et pas ici...
#include "affichageWin.h"



void effacerAff()
{
    system("cls");
}


/*
La console ne voulant plus afficher les s�quences ESC dans les printfs, j'ai �t� oblig� de refaire une fonction pour changer la couleur...
*/
void color(int txt, int bgrd)
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, bgrd*16+txt);
}
