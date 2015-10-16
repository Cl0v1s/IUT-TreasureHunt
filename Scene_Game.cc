#include "Scene_Game.h"

using namespace std;






/* *********************** Nom de la fonction ************************
* game
*************************** Auteur, Dates ****************************
* C. Portron, 19/11/14
* T.Bouzans, 21/11/14
* C.portron, 13/12/14
*************************** Description ******************************
* Gère le déroulement du jeu
*************************** Entrées **********************************
* screen, écran
*************************** Sorties **********************************
* gamestate, état du jeu après la fin de l'écran de jeu
**********************************************************************/
int game(SDL_Surface *screen)
{

    //Chargement des ressources
    TTF_Font *h1, *normal;
    SDL_Surface *player1_sprite, *player2_sprite, *coins, *jauge_sprite;
    //SDL_Surface *flags = LoadImageTransparent(placeholder,0,255,255);

    h1 = TTF_OpenFont("assets/font.ttf", 50);
    normal = TTF_OpenFont("assets/font.ttf", 25);
    player1_sprite = LoadImageTransparent("assets/player1.png",0,255,255);
    player2_sprite = LoadImageTransparent("assets/player2.png",0,255,255);
    coins = LoadImageTransparent("assets/coins.png",0,255,255);
    jauge_sprite = LoadImageTransparent("assets/jauge.png",0,255,255);

    //Création des variables logiques de la scene de jeu
    bool done = false;
    int gamestate = 1;
    int current_turn = 0;

    //Création de la map
    Map tiles;
    initMap(tiles);

    //Création des joueurs
    Vector2 coords;
    coords.x = (MAP_SIZE-1)/2;
    coords.y = (MAP_SIZE-1)/2;
    Player players[2];
    players[0] = createPlayer(1, coords, player1_sprite);
    players[1] = createPlayer(2, coords, player2_sprite);

    //création de l'interface
    Jauge jauge1 = createJauge(20, 140, &players[0], jauge_sprite);
    Jauge jauge2 = createJauge(120, 140, &players[1], jauge_sprite);
    Interface interface = createInterface(60*MAP_SIZE, 10, &jauge1, &jauge2);
    loadRessourcesInterface(interface, player1_sprite, player2_sprite,coins, LoadImageTransparent("assets/bubble.png", 0,255,255),  NULL);


    //boucle logique de jeu
    while(!done)
    {
        int startMs = SDL_GetTicks();
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {

            //Action à réaliser lorsque le joueur ferme la fenetre
            if(event.type == SDL_QUIT)
            {
                gamestate = 3;
                done = true;
                break;
            }
            //Actions à réaliser lors d'un click
            if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                //On gère les actions à réaliser lors du clic
                manageClick(event, players, current_turn, tiles);
                break;
            }
        }

        //Mise à jour des données des joueurs
        //Si update player renvoie true alors, on change de joueur
        if(updatePlayer(players[current_turn], tiles))
        {
            current_turn+=1;
            //Rectification du tour courant
            if(current_turn>1)
                current_turn = 0;
            players[current_turn].position = getOtherPlayer(players, current_turn).position;
            players[current_turn].coords = getOtherPlayer(players, current_turn).position;
        }

        //Mise à jour de l'interface
        updateInterface(interface);


        //On vérifie qu'il n'y a pas de ganant
        int winner = doesAPlayerWon(players, tiles);
        if(winner != 0)
        {
            done = true;
            gamestate = win(screen, &players[winner-1]);
        }

        //Nettoyage de l'écran
        SDL_Rect  rect;
        rect.x = 0;
        rect.y = 0;
        rect.w = SCREEN_WIDTH;
        rect.h = SCREEN_HEIGHT;
        SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 40, 45, 68));

        //affichage de la Map de pieces
        drawMap(tiles, coins,screen);

        //Affichage des joueurs
        drawPlayer(players[current_turn], screen);

        //affichage de l'interface
        drawInterface(interface,normal,screen, current_turn+1);

        //actualisation de l'écran
        SDL_Flip(screen);
        //On gère le nombre de frames par seconde (pour avoir un nombre de FPS fixe)
        if(!done)
            manageFrames(startMs);
    }
    //on décharge les ressources utilisées par la scene
    TTF_CloseFont (normal);
    TTF_CloseFont (h1);
    SDL_FreeSurface(player1_sprite);
    SDL_FreeSurface(player2_sprite);
    SDL_FreeSurface(coins);
    SDL_FreeSurface(jauge_sprite);

    return gamestate;
}

/* *********************** Nom de la fonction ************************
* manageClick
*************************** Auteur, Dates ****************************
* C. Portron, 20/11/14
* T. Bouzans, 22/11/14
*************************** Description ******************************
* Gère les clics et leurs effets
*************************** Entrées **********************************
* event, SDL_Event produit par le clic
* players, tableau contenant les joueur
* current_turn, index du joueur dont c'est le tour dans le tableau de joueur
* tiles, Tableau de pièces
*************************** Sorties **********************************
* void
**********************************************************************/
void manageClick(SDL_Event &event, Player players[], int &current_turn, Map tiles)
{
    if(event.type == SDL_MOUSEBUTTONDOWN)
    {
        int x = event.button.x;
        int y = event.button.y;

        //on teste si le clic a eu lieu dans la zone de la grille
        if(x>=0 && x<=MAP_SIZE*60 && y>=0 && y<=MAP_SIZE*60)
        {
            Vector2 coords;
            coords.x = (int)(x/60);
            coords.y = (int)(y/60);
            //On envoie le joueur courant se déplacer vers la case
            movePlayer(players[current_turn], coords, tiles);
        }


    }
}

/* *********************** Nom de la fonction ************************
* getOtherPlayer
*************************** Auteur, Dates ****************************
* C. Portron, 21/11/14
*************************** Description ******************************
* Récupère le joueur dont ce n'est pas le tour de jouer actuellement
*************************** Entrées **********************************
* players, tableau de joueur contenant lensemble des joueurs
* currentTurn, index du joueur dont c'est le tour dans players
*************************** Sorties **********************************
* Player, joueur dont ce n'est pas le tour actuellement
**********************************************************************/
Player getOtherPlayer(Player players[], int currentTurn)
{
    currentTurn = currentTurn -1;
    if(currentTurn<0)
        currentTurn = 1;
    return players[currentTurn];
}

/* *********************** Nom de la fonction ************************
* doesAPlayerWon
*************************** Auteur, Dates ****************************
* T.Bouzans, 21/11/14
*************************** Description ******************************
* teste si un joueur a gagné la partie
*************************** Entrées **********************************
* players, tableau contenant l'ensemble des joueurs
* tiles, tableau de pièces
*************************** Sorties **********************************
* int, 0 si aucun des joueurs n'a gagné sinon id du joueur gagnant (1 ou 2)
**********************************************************************/
int doesAPlayerWon(Player players[], Map tiles)
{
    int winner = 0;
    int index = 0;


    while(index < 2 && winner == 0)
    {

        int px =round((players[index].position.x) / 60);
        int py = round((players[index].position.y) / 60);
        //Garde bug: mauvais placement x aléatoire du joueur (uniquement à l'IUT) -> WTF ?
        if(!(px < 0 || px > MAP_SIZE-1 || py < 0 || py > MAP_SIZE-1))
        {
            //On teste sir le joueur index peut se mouvoir
            bool found = false;
            int y = 0;
            //On teste si il reste des pièces sur l'axe y
            while(y<MAP_SIZE-1 && !found)
            {
                if(tiles[px][y].value != 0)
                    found = true;
                y+=1;
            }
            int x = 0;
            //On teste si il reste des pièces sur l'axe x
            while(!found && x < MAP_SIZE-1)
            {
                if(tiles[x][py].value != 0)
                    found = true;
                x+=1;
            }
            //Si aucune pièce n'a été trouvé pour lejoueur à l'index courant alors c'est son adversaire qui a gagné
            if(!found)
                winner = getOtherPlayer(players, index).id;

            //Si les points du joueur à l'index courant sont >= à 500 alors, il a gagné
            if(players[index].points >= 500)
            {
                winner = players[index].id;
            }
        }

        index+=1;
    }
    return winner;
}

