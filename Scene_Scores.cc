#include "Scene_Scores.h"

using namespace std;


/* *********************** Nom de la fonction ************************
* scores
*************************** Auteur, Dates ****************************
* C. Portron, 14/12/14
*************************** Description ******************************
* Affiche  et gère l'écran des scores
*************************** Entrées **********************************
* screen, écran
*************************** Sorties **********************************
* int gamestate, etat du jeu après exécution de l'écran des scores
**********************************************************************/
int scores(SDL_Surface *screen)
{

    //Chargement des resources néecssaire à l'écran
    TTF_Font *h1 = TTF_OpenFont("assets/font.ttf", 50);
    TTF_Font *normal = TTF_OpenFont("assets/font.ttf", 20);
    SDL_Surface *button_sprite = LoadImageTransparent("assets/button.png",0,255,255);

    //créatoin du bouton retour
    Button ret = createButton(button_sprite, "Retour", SCREEN_WIDTH/2 - 215/2, SCREEN_HEIGHT-70, normal);

    bool done = false;
    int gamestate = 2;

    //Récupération des scores
    int score[MAX_SAVES];
    int nb_score = 0;
    readScores(score, nb_score);


    while(!done)
    {
        int startms = SDL_GetTicks();

        //Gère les actions du joueur
        gamestate = manageInputScores(&ret);
        if(gamestate != 2)
        {
            done = true;
        }

        //On nettoie l'écran
        SDL_Rect  rect;
        rect.x = 0;
        rect.y = 0;
        rect.w = SCREEN_WIDTH;
        rect.h = SCREEN_HEIGHT;
        SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 40, 45, 68));

        RGBA white;
        white.a = 255; white.r = 255; white.g = 255; white.b = 255;

        //On affiche le titre de l'écran
        string msg = "Scores:";
        Vector2 siz = getTextSize(msg, h1);
        drawText("Scores:", SCREEN_WIDTH/2 - siz.x/2, 30, h1, 50, white, screen);

        //Affiche les scores
        drawScores(score, nb_score, normal, screen);

        //Dessine le bouton retour
        drawButton(&ret, screen);

        SDL_Flip(screen);
        manageFrames(startms);
    }
    //On libère les resources utilisées par l'écran
    SDL_FreeSurface(button_sprite);
    TTF_CloseFont(h1);
    TTF_CloseFont(normal);
    return gamestate;
}

/* *********************** Nom de la fonction ************************
* manageInputScores
*************************** Auteur, Dates ****************************
* C. Portron, 14/12/14
*************************** Description ******************************
* Gère les actions du joueur
*************************** Entrées **********************************
* ret, bouton retour
*************************** Sorties **********************************
* int , gamestate, etat du jeu après action du joueur, 2 sinon aucune action
**********************************************************************/
int manageInputScores(Button *ret)
{

    int gamestate = 2;
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(buttonOnClick(&event, ret))
        {
            gamestate = 0;
        }
        if(event.type == SDL_QUIT)
        {
            gamestate = 3;
        }
    }
    return gamestate;
}

/* *********************** Nom de la fonction ************************
* readScores
*************************** Auteur, Dates ****************************
* C. Portron, 14/12/14
*************************** Description ******************************
* Lit les 5 meilleurs scores
*************************** Entrées **********************************
* score, tableau contenant les 5 meilleurs scores
* nb_score, nombre de meilleurs scores
*************************** Sorties **********************************
* void
**********************************************************************/
void readScores(int score[], int &nb_score)
{
    string line;
    nb_score = -1;
    fstream file;
    file.open(SAVE_FILE.c_str(), ios_base::in);
    if(file.is_open())
    {
        nb_score = 0;
        while(getline(file, line) && nb_score < MAX_SAVES)
        {
            score[nb_score] = atoi(line.c_str());
            nb_score +=1;
        }
    }
}

/* *********************** Nom de la fonction ************************
* drawScores
*************************** Auteur, Dates ****************************
* C. Portron, 14/12/14
*************************** Description ******************************
* Affiche l'écran des scores
*************************** Entrées **********************************
* score, tableau contenant les 5 meilleurs scores
* nb_score, nombre de score
* font, police à utiliser pour afficher les scores
* screen, surface sur laquelle dessiner les scores
*************************** Sorties **********************************
* void
**********************************************************************/
void drawScores(int score[], int nb_score, TTF_Font *font, SDL_Surface *screen)
{
    string msg;
    Vector2 siz;
    RGBA white;
    white.a = 255; white.r = 255; white.g =255;white.b = 255;
    //Si aucun score n'a été trouvé
    if(nb_score == -1)
    {
        msg = "Aucune Sauvegarde";
        siz = getTextSize(msg, font);
        drawText(msg, SCREEN_WIDTH/2 - siz.x/2, SCREEN_HEIGHT/2, font, 20, white, screen);
        return;
    }
    //Sinon on affiche chacun des scores
    for(int i = 0; i < nb_score; i++)
    {
        msg = convertToString(score[i]) + "  Tours";
        siz  = getTextSize(msg, font);
        drawText(msg, SCREEN_WIDTH/2 - siz.x /2, 100+30*i, font, 02, white, screen);
    }
}
