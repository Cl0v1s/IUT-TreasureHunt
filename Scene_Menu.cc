#include "Scene_Menu.h"


/* *********************** Nom de la fonction ************************
* menu
*************************** Auteur, Dates ****************************
* T.bouzans, 22/11/14
* C. Portron, 24/11/14
* C. Portron 14/12/14
*************************** Description ******************************
* Gère le menu du jeu
*************************** Entrées **********************************
* screen, écran
*************************** Sorties **********************************
* int, etat du jeu après l'exécution du menu
**********************************************************************/
int menu(SDL_Surface *screen)
{
    //Chargement des ressources de la scene
    TTF_Font *h1 = TTF_OpenFont("assets/font.ttf", 50);
    TTF_Font *normal = TTF_OpenFont("assets/font.ttf", 20);
    SDL_Surface *button_sprite = LoadImageTransparent("assets/button.png",0,255,255);
    //création des boutons du menu
    Button play = createButton(button_sprite,"Jouer", SCREEN_WIDTH/2 - 215/2, SCREEN_HEIGHT-200,normal);
    Button quit = createButton(button_sprite,"Quitter", SCREEN_WIDTH/2 - 215/2, SCREEN_HEIGHT-70,normal);
    Button scores = createButton(button_sprite, "Scores", SCREEN_WIDTH/2-215/2, SCREEN_HEIGHT-135, normal);
    bool done=false;
    int gamestate = 0;

    while(!done)
    {
        int startMs = SDL_GetTicks();
        //On gère ls entrées du joueur
        gamestate = manageInputMenu(&play, &scores, &quit);
        if(gamestate != 0)
            done = true;
        //On affiche le menu
        drawMenu(screen, h1, &play, &scores, &quit);
        SDL_Flip(screen);

        manageFrames(startMs);

    }
    //On libère les ressources utilisées par le  jeu
    SDL_FreeSurface(button_sprite);
    TTF_CloseFont(h1);
    TTF_CloseFont(normal);
    return gamestate;
}

/* *********************** Nom de la fonction ************************
* manageInput
*************************** Auteur, Dates ****************************
* T. Bouzans 22/11/14
* C. Portron, 14/12/14
*************************** Description ******************************
* Gère les entrées du joueur dans l'interface
*************************** Entrées **********************************
* play, bouton jouer
* scores, bouton scores
* quit, bouton quitter
*************************** Sorties **********************************
* int, gamestate après clic sur l'in des boutons, 2 si pas de clic
**********************************************************************/
int manageInputMenu(Button *play, Button *scores, Button *quit)
{
        int gamestate = 0;
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            //Action à réaliser lorsque le joueur clique sur le bouton jouer
            if(buttonOnClick(&event, play))
            {
                gamestate = 1;
            }
            //Action à réaliser lorsque le joueur clique le bouton quitter ou ferme la fenetre
            if(buttonOnClick(&event, quit) || event.type == SDL_QUIT)
            {
                gamestate = 3;
            }
            if(buttonOnClick(&event, scores))
                gamestate = 2;
        }
        return gamestate;
}


/* *********************** Nom de la fonction ************************
* drawMenu
*************************** Auteur, Dates ****************************
* T. Bouzans, 22/11/14
*************************** Description ******************************
* On dessine le menu
*************************** Entrées **********************************
* screen, surface sur laquelle dessiner le menu
* h1, police de titre
* play, bouton jouer
* scores, bouton scores
* quit, bouton quitter
*************************** Sorties **********************************
* void
**********************************************************************/
void drawMenu(SDL_Surface *screen, TTF_Font *h1, Button *play,Button *scores, Button *quit)
{
        //Efface l'écran
        SDL_Rect  rect;
        rect.x = 0;
        rect.y = 0;
        rect.w = SCREEN_WIDTH;
        rect.h = SCREEN_HEIGHT;
        SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 40, 45, 68));

        //Affiche le titre du jeu
        RGBA color;color.a = 255;color.r = 255;color.g = 255;color.b = 255;
        int _xtxt = (getTextSize("Treasure Hunt",h1)).x/2;
        drawText("Treasure Hunt", SCREEN_WIDTH /2-_xtxt, 50, h1,50,color, screen);

        //Affiche les boutons à l'écran
        drawButton(play, screen);
        drawButton(scores, screen);
        drawButton(quit, screen);
}
