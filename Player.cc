#include "Player.h"

using namespace std;

/* *********************** Nom de la fonction ************************
* createPlayer
*************************** Auteur, Dates ****************************
* T. Bouzans, 19/11/14
*************************** Description ******************************
* Créer un nouveau joueur
*************************** Entrées **********************************
* id, id du joueur
* coords, position en case du joueur dans le tableau de pièce
* sprite, feuille de sprite du joueur
*************************** Sorties **********************************
* Nouveau joueur initialisé
**********************************************************************/
Player createPlayer(int id, Vector2 coords, SDL_Surface *sprite)
{
    Player p;
    p.id = id;
    p.coords = coords;
    p.position.x = coords.x*60;
    p.position.y = coords.y*60;
    p.points = 0;
    p.combo = 0;
    p.lastCoin = 0;
    p.sprite = sprite;
    p.frame = 0;
    p.target.x = -1;
    p.target.y = -1;
    p.turn = 0;
    Vector2 velocity;
    velocity.x = 0;
    velocity.y = 0;
    p.velocity = velocity;
    return p;
}

/* *********************** Nom de la fonction ************************
* updatePlayer
*************************** Auteur, Dates ****************************
* T. Bouzans, 19/11/14
* C.portron, 19/11/14
*************************** Description ******************************
* Met à jour les données du joueur
*************************** Entrées **********************************
* player, joueur à metre à jour
* tiles, tableau de pièces
*************************** Sorties **********************************
* True, si le joueur à terminer son tour
* False sinon
**********************************************************************/
bool updatePlayer(Player &player, Map tiles)
{
    bool changeTurn = false;

    //On met à jour la position visible du joueur en fonction de sa velocité
    player.position.x += 0.03F*player.velocity.x;
    player.position.y += 0.03F*player.velocity.y;
    //On diminue la velocité
    player.velocity.x -= 0.03F*player.velocity.x;
    player.velocity.y -= 0.03F*player.velocity.y;

    //Si la velocité est inférieur à 6 on la rend nulle
    if(abs(player.velocity.x) <= 6)
        player.velocity.x = 0;
    if(abs(player.velocity.y) <= 6)
        player.velocity.y = 0;

    //OON augmente le compteur de frame si le joueur n'ets apsimmobile
    if(abs(player.velocity.x) > 0 || abs(player.velocity.y) > 0)
        player.frame += 0.25;

    if(player.frame > 3)
        player.frame = 0;


    //On met à jour la position en case du joueur en fonction de sa position visuelle
    player.coords.x = round((player.position.x) / 60);
    player.coords.y = round((player.position.y) / 60);


    //On arretele joueur si il a dépassé son objectif
    if(player.velocity.x > 0 && player.position.x > player.target.x * 60)
        stop(player);
    else if(player.velocity.x < 0 && player.position.x < player.target.x * 60)
        stop(player);

    if(player.velocity.y > 0 && player.position.y > player.target.y * 60)
        stop(player);
    else if(player.velocity.y < 0 && player.position.y < player.target.y * 60)
        stop(player);

    //Si le joueur est arrété sur une case, alors on le repositionne correctemment et on lui fait ramasser l'éventuelle pièce
    if(player.velocity.x == 0 && player.velocity.y == 0)
    {
        player.position.x = player.coords.x * 60;
        player.position.y = player.coords.y * 60;
        changeTurn = getCoinPlayer(player, tiles);
    }
    return changeTurn;
}

/* *********************** Nom de la fonction ************************
* stop
*************************** Auteur, Dates ****************************
* C. Portron, 20/11/14
*************************** Description ******************************
* Arrete le déplacement du joueur
*************************** Entrées **********************************
* player, joueur à arreter
*************************** Sorties **********************************
* void
**********************************************************************/
void stop(Player &player)
{
        //On arrete le joueur
        player.target.x = -1;
        player.target.y = -1;
        player.velocity.x = 0;
        player.velocity.y = 0;
        player.frame = 0;
}

/* *********************** Nom de la fonction ************************
* movePlayer
*************************** Auteur, Dates ****************************
* C. Portron, 20/11/14
*************************** Description ******************************
* Déplace le joueur
*************************** Entrées **********************************
* player, joueur à déplacer
* destination, case à laquelle doit se rendre le joueur
* tiles, tableau de pièces
*************************** Sorties **********************************
* void
**********************************************************************/
void movePlayer(Player &player, Vector2 destination, Map tiles)
{
    if(player.velocity.x == 0 && player.velocity.y == 0)
    {
        //On teste si la case de destination n'est pas "en diagonale"
       if(destination.x !=  player.coords.x && destination.y != player.coords.y)
            return;
        //on verifie que la case de destination contient bien une pièce
        if(tiles[(int)destination.x][(int)destination.y].value == 0)
            return;
        player.target = destination;
        //On détermine la direction du joueur
        int w = player.coords.x - destination.x;
        int h = player.coords.y - destination.y;
        if(abs(w)>abs(h))
            player.velocity.x = -w*60*1.5;
        else
            player.velocity.y = -h*60*1.55;
        player.turn +=1;
    }
}

/* *********************** Nom de la fonction ************************
* getCoinPlayer
*************************** Auteur, Dates ****************************
* C. Portron, 20/11/14
* T. Bouzans, 21/11/14
*************************** Description ******************************
* Permet au joueur de ramasser une pièce
*************************** Entrées **********************************
* player, joueur à mettre à jour
* tiles, tableau de pièce
*************************** Sorties **********************************
* True, si le joueur a ramassé une pièce
* False, sinon
**********************************************************************/
bool getCoinPlayer(Player &player, Map tiles)
{
    // Si le joueur n'est pas dans le tableau de pièce, on arrete
    if(player.coords.x < 0 || player.coords.x > MAP_SIZE-1 || player.coords.y < 0 || player.coords.y > MAP_SIZE-1)
        return false;
    Coin c = tiles[(int)player.coords.x][(int)player.coords.y];

    //Si la pièce courante est une pièce nulle, alors on arrete tout
    if(c.value == 0)
        return false;

    //Si la dernière pièce ramassée par le joueur est la même que la pièce qu'il vient de ramasser
    if(player.lastCoin == c.value)
        player.combo += 1;
    else
        player.combo = 0;
    if(player.combo > 4)
        player.combo = 4;

    //Calcul du bonus de combo
    if(player.combo > 0)
    {
        player.points+= 10*pow(2, (player.combo-1));
    }

    player.points += c.value;
    player.lastCoin = c.value;
    //La pièce courante devient une pièce nulle
    c.value = 0;
    tiles[(int)player.coords.x][(int)player.coords.y] = c;
    return true;
}

/* *********************** Nom de la fonction ************************
* updateInterface
*************************** Auteur, Dates ****************************
* C. Portron, 14/12/2014
*************************** Description ******************************
* replace le joueur au centre de la grille (pour corriger un bug n'arrivant que sur les machines de l'IUT)
*************************** Entrées **********************************
* player, joueur à remettre à sa place
*************************** Sorties **********************************
* void
**********************************************************************/
void replacePlayer(Player *player)
{
    Vector2 coords;
    coords.x = (MAP_SIZE-1)/2;
    coords.y = (MAP_SIZE-1)/2;
    player->coords = coords;
    player->position.x = coords.x*60;
    player->position.y = coords.y*60;
}

/* *********************** Nom de la fonction ************************
* updateInterface
*************************** Auteur, Dates ****************************
* C. Portron, 21/11/14
* T. Bouzans, 22/11/14
*************************** Description ******************************
* Dessine le joueur à l'écran
*************************** Entrées **********************************
* player, joueur à dessiner
* screen, surface sur laquelle déssiner le joueur
*************************** Sorties **********************************
* void
**********************************************************************/
void drawPlayer(Player player, SDL_Surface *screen)
{
    int x = (int)player.position.x;
    int y = (int)player.position.y;
    //On détermine l'index du sprite dans la feuille de sprite en fonction de la direction du joueur
    int yframe = 0;
    if(player.velocity.x < 0)
        yframe = 1;
    if(player.velocity.x > 0)
        yframe = 2;
    if(player.velocity.y > 0)
        yframe = 0;
    if(player.velocity.y < 0)
        yframe = 3;
    //Valeur spéciale pour afficher l'animation de joie en fin de partie
    if(player.velocity.x == INT_MIN)
        yframe = 4;

    SDL_Rect rect;
    rect.x = ((int)player.frame) * 60;
    rect.y = yframe * 60;
    rect.w = 60;
    rect.h = 60;
    applySurface(x,y, player.sprite, screen, &rect );
}
