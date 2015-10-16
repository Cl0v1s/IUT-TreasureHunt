#include "Interface.h"

using namespace std;


/* *********************** Nom de la fonction ************************
* createInterface
*************************** Auteur, Dates ****************************
* T.Bouzans, 21/11/14
*************************** Description ******************************
* créer une nouvelle interface contenant les informations sur le jeu
*************************** Entrées **********************************
* x, position x de l'interface
* y, position y de l'interface
* jauge1, jauge contenant les informations des bonus du joueur 1
* jauge, idem pour le joueur 2
*************************** Sorties **********************************
* L'interface initialisée
**********************************************************************/
Interface createInterface(int x, int y, Jauge *jauge1, Jauge *jauge2)
{
    Interface i;
    i.x = x;
    i.y = y;
    //Mise à jour des positions relatives aux jauges pour les faire correspondre à l'emplacement de l'interface
    jauge2->x = x+jauge2->x;
    jauge2->y = y+jauge2->y;
    jauge1->x = x+jauge1->x;
    jauge1->y = y+jauge1->y;
    Rectangle r;
    r.x = jauge1->x+21;
    r.y = jauge1->y+98;
    r.width = 8;
    r.height = 0;
    jauge1->level = r;
    Rectangle t;
    t.x = jauge2->x+21;
    t.y = jauge2->y+98;
    t.width = 8;
    t.height = 0;
    jauge2->level = t;
    i.jauge1 = jauge1;
    i.jauge2 = jauge2;
    i.frame = 0;
    return i;
}

/* *********************** Nom de la fonction ************************
* loadResourceInterface
*************************** Auteur, Dates ****************************
* T.Bouzans, 21/11/14
* C.portron, 22/11/14
*************************** Description ******************************
* Charge les ressources graphiques utilisées par l'interface
*************************** Entrées **********************************
* interface, interface pour laquelle les ressources doivent etre chargées
* player1, feuille de sprite du joueur 1
* player2, feuille de sprite du joueur 2
* coins, feuille de sprite contenant l'ensemble des pièces
* bubble, image de la bulle
* background, image de fond de l'interface (inutilisé pour le moment)
*************************** Sorties **********************************
* void
**********************************************************************/
void loadRessourcesInterface(Interface &interface, SDL_Surface *player1, SDL_Surface *player2, SDL_Surface *coins, SDL_Surface *bubble, SDL_Surface *background)
{
    //On charge ici les ressources nécessaires à l'affichage de l'inertace (pour éviter de faire une fonction de création de l'intreface trop longue)
    interface.background = background;
    interface.player_1 = player1;
    interface.player_2 = player2;
    interface.coins = coins;
    interface.bubble = bubble;
}

/* *********************** Nom de la fonction ************************
* updateInterface
*************************** Auteur, Dates ****************************
* C. Portron, 21/11/14
*************************** Description ******************************
* Met à jour les données de l'interface
*************************** Entrées **********************************
* interface, interface dont les fonnées doivent etre mises à jour
*************************** Sorties **********************************
* void
**********************************************************************/
void updateInterface(Interface &interface)
{
    //On met à jour les jauges
    updateJauge(*interface.jauge1);
    updateJauge(*interface.jauge2);
    //On met à jour l'index de frame
    interface.frame += 0.05;
    if(interface.frame>3)
        interface.frame = 0;
}

/* *********************** Nom de la fonction ************************
* drawInterface
*************************** Auteur, Dates ****************************
* C. Portron, 22/11/14
*************************** Description ******************************
* Affiche l'interface
*************************** Entrées **********************************
* interface, interface devant etre affichée
* font, police utilisée pour l'interface
* screen, surface sur laquelle doit etre dessinée l'interface
* currentlyPlaying, index du joueur jouant actuellement
*************************** Sorties **********************************
* void
**********************************************************************/
void drawInterface(Interface interface,TTF_Font *font,  SDL_Surface *screen, int currentlyPlaying)
{
    //Affichage des jauges
    drawJauge(*interface.jauge1, font, screen);
    drawJauge(*interface.jauge2, font, screen);

    //Affichage des "miniatures" des joueurs pour permettre de les différencier
    SDL_Rect clip;
    clip.x= 0;clip.y = 4*60;clip.h = 60;clip.w=60;
    if(currentlyPlaying == 1)
    {
        clip.x= ((int)interface.frame)*60;
    }
    applySurface(interface.jauge1->x+24-30, interface.jauge1->y-60, interface.player_1, screen, &clip);
    clip.x= 0;
    if(currentlyPlaying == 2)
    {
        clip.x= ((int)interface.frame)*60;
    }
    applySurface(interface.jauge2->x+24-30, interface.jauge2->y-60, interface.player_2, screen, &clip);

    //Affichage des scores des deux joueurs associés aux jauges
    RGBA color;
    color.r = 150;
    color.g = 150;
    color.b = 150;
    color.a = 255;
    //Affichage des points du premier joueur
    string m = convertToString(interface.jauge1->player->points);
    Vector2 v = getTextSize(m, font);
    drawText(m, interface.jauge1->x+24-v.x/2, interface.jauge1->y+110,font, 32, color, screen);
    //Affichage des points du deuxième joueur
    m = convertToString(interface.jauge2->player->points);
    v = getTextSize(m, font);
    drawText(m, interface.jauge2->x+24-v.x/2, interface.jauge2->y+110,font, 32, color, screen);
    //Affichage des dernières pièces ramassées par les deux joueurs
    int index = getIndexInSpriteSheet(interface.jauge1->player->lastCoin);
    if(index>-1)
    {
        clip.x = index; clip.y = 0, clip.w = 60; clip.h = 60;
        applySurface(interface.jauge1->x+24-35,interface.jauge1->y-135, interface.bubble,screen,NULL);
        applySurface(interface.jauge1->x+24-28, interface.jauge1->y-134, interface.coins, screen, &clip);
    }
    index = getIndexInSpriteSheet(interface.jauge2->player->lastCoin);
    if(index>-1)
    {
        clip.x = index; clip.y = 0, clip.w = 60; clip.h = 60;
        applySurface(interface.jauge2->x+24-35,interface.jauge2->y-135, interface.bubble,screen,NULL);
        applySurface(interface.jauge2->x+24-28, interface.jauge2->y-134, interface.coins, screen, &clip);
    }


    //TODO: Dessiner ici le fond de l'interface
}

