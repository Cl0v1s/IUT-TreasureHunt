#include "Scene_Win.h"


using namespace std;


/* *********************** Nom de la fonction ************************
* win
*************************** Auteur, Dates ****************************
* T. Bouzans, 24/11/14
* C. Portron, 24/11/14
* C. Portron, 14/12/14
*************************** Description ******************************
* Affiche l'écran de fin de partie
*************************** Entrées **********************************
* screen, écran
* winner, joueur ayant gagné la partie
*************************** Sorties **********************************
* int gamestate, etat du jeu après l'exécution de win
**********************************************************************/
int win(SDL_Surface *screen, Player *winner)
{

    //Chargement des ressources necessaires
    SDL_Surface *button_sprite;
    TTF_Font *h1, *normal;

    //Chargement des ressources de la scene
    h1 = TTF_OpenFont("assets/font.ttf", 50);
    normal = TTF_OpenFont("assets/font.ttf", 20);
    button_sprite = LoadImageTransparent("assets/button.png",0,255,255);

    bool done = false;
    int gamestate = 2;

    //Création des boutons
    Button replay = createButton(button_sprite,"Rejouer", 640/2-100,SCREEN_HEIGHT-130,normal);
    Button quit = createButton(button_sprite,"Quitter", 640/2-100,SCREEN_HEIGHT-70,normal);

    //Affecation de la valeur spéciale à la vélocité X du joueur pour afficher l'animation de saut
    winner->velocity.x = INT_MIN;
    winner->position.x = SCREEN_WIDTH/2-30;
    winner->position.y = 150;

    //Lecture des scores précedents
    bool high = false;
    int highscore = readBestScore();
    if(highscore > winner->turn)
    {
        high = true;
    }
    saveScore(winner->turn);

    while(!done)
    {
        int startTicks = SDL_GetTicks();
        //Actualisation des boutons
        gamestate = manageInputWin(&replay, &quit);
        if(gamestate != 2)
        {
            done=true;
        }
        //Actualisation de l'index de frame pour le joueur
        winner->frame+=0.025;
        if(winner->frame>3)
            winner->frame = 0;

        //Nettoyage de l'écran
        SDL_Rect  rect;
        rect.x = 0;
        rect.y = 0;
        rect.w = SCREEN_WIDTH;
        rect.h = SCREEN_HEIGHT;
        SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 40, 45, 68));

        //Affichage des boutons
        drawButton(&replay, screen);
        drawButton(&quit, screen);


        //Affichage du texte
        RGBA white;
        white.r = 255; white.g = 255; white.b = 255; white.a = 255;
        string msg = "Le joueur " + convertToString(winner->id) + " a gagne !";
        Vector2 siz = getTextSize(msg, normal);
        drawText(msg, SCREEN_WIDTH/2 - siz.x /2-25, 100, normal, 20, white, screen);

        msg = "Victoire !";
        siz = getTextSize(msg, h1);
        drawText(msg, SCREEN_WIDTH/2 - siz.x /2, 20, h1, 20, white, screen);


        //Affichage de l'animation
        drawPlayer(*winner, screen);

        //Affichage des scores (score/highscore)
        if(!high)
            msg = "Vous avez gagne en " + convertToString(winner->turn) + " tours";
        else
            msg = "Record battu ! Gagne en "+convertToString(winner->turn)+" tours !";
        siz = getTextSize(msg, normal);
        drawText(msg, SCREEN_WIDTH/2 - siz.x/2 -25, 230, normal, 20, white, screen);

        if(highscore != INT_MAX)
        {
            msg="";
            if(high)
                msg = "(ex)";
            msg += "Meilleur score: "+ convertToString(highscore) + " tours";
            siz = getTextSize(msg, normal);
            drawText(msg, SCREEN_WIDTH/2 - siz.x/2 -25, 255, normal, 20, white, screen);
        }



        SDL_Flip(screen);
        manageFrames(startTicks);

    }
    //Déchargement des ressources utilisées
    TTF_CloseFont(h1);
    TTF_CloseFont(normal);
    SDL_FreeSurface(button_sprite);
    return gamestate;

}

/* *********************** Nom de la fonction ************************
* manageInputWin
*************************** Auteur, Dates ****************************
* T. Bouzans 24/11/14
* C. Portron 24/11/14
*************************** Description ******************************
* Gère les entrées du joueur
*************************** Entrées **********************************
* replay, bouton rejouer
* quit, bouton quitter
*************************** Sorties **********************************
* int gamestate, etat du jeu après action du joueur, 2 si aucune action
**********************************************************************/
int manageInputWin(Button *replay, Button *quit)
{
    int gamestate = 2;
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        // On teste le clic sur le bouton fermer et sir le bouton quitter
        if(event.type == SDL_QUIT || buttonOnClick(&event, quit))
        {
            gamestate = 3;
            break;
        }

        //On teste le clic sur le bouton rejouer
        if(buttonOnClick(&event, replay))
        {
            gamestate = 1;
            break;
        }
    }
    return gamestate;
}

/* *********************** Nom de la fonction ************************
* readBestScore
*************************** Auteur, Dates ****************************
* C. Portron, 24/11/14
* T. Bouzans, 24/11/14
*************************** Description ******************************
* On récupère le meilleur score
*************************** Entrées **********************************
* void
*************************** Sorties **********************************
* int, meilleur score
**********************************************************************/
int readBestScore()
{

    string l;
    fstream f;
    f.open(SAVE_FILE.c_str());
    if(f.is_open())
    {
        getline(f, l);
        return atoi(l.c_str());
    }
    return INT_MAX;
}

/* *********************** Nom de la fonction ************************
* saveScore
*************************** Auteur, Dates ****************************
* C. Portron, 24/11/14
* T. Bouzans, 24/11/14
* C. Portron, 14/12/14
*************************** Description ******************************
* Sauvegarde le score du gagnant de la partie si meilleur que l'un des MAX_SAVES meilleurs scores précedents
*************************** Entrées **********************************
* score, score du gagnant
*************************** Sorties **********************************
* void
**********************************************************************/
void saveScore(int score)
{
    // On récupère les meilleurs scores
    int tab[MAX_SAVES];
    int nb_score = 0;
    readAllScores(tab, nb_score);
    // Si le ficher de score existe
    if(nb_score != -1)
    {
        bool placed = false;
        int i = 0;
        // On insère le score du gagnant à la place qui lui revient dans le tableau trié
        while(!placed && i < nb_score)
        {
            if(score < tab[i])
            {
                moveIntArrayRight(tab, i, nb_score, MAX_SAVES);
                tab[i] = score;
                placed = true;
            }
            i++;
        }
        //Si le score du gagnant est meulleur que l'un des MAX_SAVES meilleurs scores précedents alors on enregsitre le nouveau classement
        if(placed)
        {
            fstream f;
            f.open(SAVE_FILE.c_str(),ios_base::out);
            for(int u = 0; u < nb_score; u++)
            {
                f << tab[u] << endl;
            }
            f.close();
            return;
        }
    }
    else //Si le fichier de sauvegarde n'existait pas, alors on le céer un y insérant le score du gagnant
    {
        fstream f;
        f.open(SAVE_FILE.c_str(),ios_base::out);
        f << score << endl;
        f.close();
    }
}

/* *********************** Nom de la fonction ************************
* readAllScores
*************************** Auteur, Dates ****************************
* C. Portron, 14/12/14
*************************** Description ******************************
* Récupère l'ensemble des n à MAX_SAVES meilleurs scores
*************************** Entrées **********************************
* score, tableau contenant les scores
* nb_score, nombre de score
*************************** Sorties **********************************
* void
**********************************************************************/
void readAllScores(int score[], int &nb_score)
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
