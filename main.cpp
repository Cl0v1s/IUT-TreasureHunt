//////////////////////////////////////////////////////
// TREASURE HUNT                                    //
//////////////////////////////////////////////////////
// Par T. Bouzans et c. Portron                     //
// -------------------------------------------------//
// L'ensemble des fichiers sources de ce projet     //
// (excepté les fichiers Lib.h et Lib.cc)           //
// sont protégés par la LICENSE APACHE 2.0.         //
//////////////////////////////////////////////////////



#include <SDL/SDL.h>
#include "Constantes.h"
#include "Lib.h"
#include "Scene.h"
#include "Scene_Game.h"
#include "Scene_Menu.h"
#include "Scene_Win.h"
#include "Scene_Scores.h"
#include <cstdlib>

/* *********************** Nom de la fonction ************************
* MAIN
*************************** Auteur, Dates ****************************
* C.portron, 12/11/14
* T.Bouzans, 14/11/14
*************************** Description ******************************
* Initialise le jeu et contrôle son déroulement global
*************************** Entrées **********************************
*
*************************** Sorties **********************************
* Code d'execution du programe
**********************************************************************/
int main()
{

    //initialisation de la SDL
    SDL_Surface *screen;
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    screen=SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);
    //initialisation de l'aléatoire
    srand(time(NULL));


    //variables de jeu globales
    int gamestate = 0;
    bool quit=false;

    //boucle principale permettant de passer d'un écran à l'autre
    //0: menu, 1: jeu, 2: scores, 3: quitter
    while(!quit)
    {

        switch(gamestate)
        {
        case 0:
            gamestate = menu(screen);
            break;
        case 1:
            gamestate = game(screen);
            break;
        case 2:
            gamestate = scores(screen);
            break;
        case 3:
            quit=true;
            break;
        }
    }
    //Déchargement des données des libraries
    TTF_Quit();
    SDL_Quit();
    return 0;
}


