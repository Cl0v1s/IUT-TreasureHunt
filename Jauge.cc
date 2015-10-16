#include "Jauge.h"

using namespace std;


/* *********************** Nom de la fonction ************************
* createJauge
*************************** Auteur, Dates ****************************
* C. Portron, 19/11/14
*************************** Description ******************************
* Créer une nouvelle jauge contenant les informations sur les bonus d'un joueur
*************************** Entrées **********************************
* x, position x de la jauge
* y, position y de la jauge
* player, joueur dont la jauge doit afficher les informations
* sprite, spritesheet de la jauge
*************************** Sorties **********************************
* Nouvelle jauge
**********************************************************************/
Jauge createJauge(int x, int y, Player *player, SDL_Surface *sprite)
 {
     Jauge j;
     j.x = x;
     j.y = y;
     j.player = player;
     j.frame = 0;
     Rectangle r;
     r.x = x+21;
     r.y = y+98;
     r.width = 8;
     r.height = 0;
     j.level = r;
     Vector2 v;
     v.x = 0;
     v.y = 0;
     j.progress = v;
     j.lastCombo = 0;
     j.sprite = sprite;
     return j;
 }


/* *********************** Nom de la fonction ************************
* updateJauge
*************************** Auteur, Dates ****************************
* C. Portron, 19/11/14
*************************** Description ******************************
* Met à jour les données de la jauge
*************************** Entrées **********************************
* jauge, jauge devant etre mise à jour
*************************** Sorties **********************************
* void
**********************************************************************/
void updateJauge(Jauge &jauge)
{
    //On met à jour le niveau de la jauge
    jauge.level.height += 0.03*jauge.progress.y;;
    jauge.level.y -= 0.03*jauge.progress.y;
    jauge.progress.y -= 0.03*jauge.progress.y;
    if(abs(jauge.progress.y) < 1)
        jauge.progress.y = 0;
    if(jauge.level.y < jauge.y + 2)
        jauge.level.y = jauge.y +2;

    //On met à jour le niveau de combo indiqué par la jauge
    if(jauge.lastCombo < jauge.player->combo)
    {
        jauge.progress.y += 25;
        jauge.lastCombo = jauge.player->combo;
    }
    if(jauge.player->combo == 0)
    {
        resetJauge(jauge);
        jauge.lastCombo = 0;
    }

    //on manage les frames
    jauge.frame+=0.25;

    if(jauge.frame > 3)
        jauge.frame = 0;

}


/* *********************** Nom de la fonction ************************
* resetJauge
*************************** Auteur, Dates ****************************
* C. Portron, 19/11/14
*************************** Description ******************************
* Remet à zéro le niveau de la jauge
*************************** Entrées **********************************
* jauge, jauge devant etre remise à zéro
*************************** Sorties **********************************
* void
**********************************************************************/
void resetJauge(Jauge &jauge)
{
    jauge.progress.y = jauge.level.y - (jauge.y + 98);
}


/* *********************** Nom de la fonction ************************
* drawJauge
*************************** Auteur, Dates ****************************
* C. Portron, 19/11/14
*************************** Description ******************************
* Affiche la jauge à l'écran
*************************** Entrées **********************************
* jauge, jauge devant etre affichée
* font, police devant etre utilisée pour afficher les données textuelles de la jauge
* screen, surface sur laquelle doit etre dessinée la jauge
*************************** Sorties **********************************
* void
**********************************************************************/
void drawJauge(Jauge jauge, TTF_Font *font, SDL_Surface *screen)
{
    SDL_Rect rect;
    rect.x = 48*(int)jauge.frame;
    rect.y = 0;
    rect.w = 48;
    rect.h = 100;

    //on dessine le niveau de la jauge
    SDL_Rect level;
    level.x  = (int)jauge.level.x;
    level.y = (int)jauge.level.y;
    level.w = (int)jauge.level.width;
    level.h = (int)jauge.level.height;
    SDL_FillRect(screen, &level, SDL_MapRGB(screen->format, 0,255,0));

    //On dessine l'image de la jauge
    applySurface(jauge.x, jauge.y,jauge.sprite, screen, &rect);

    //On afiche les points bonus offerts par les combos
    int d = 10*pow(2, (jauge.player->combo-1));
    if(jauge.player->combo == 0)
        d = 0;
    string m = "+"+convertToString(d);
    RGBA color;
    color.r = 150;
    color.g = 150;
    color.b = 150;
    color.a = 255;
    drawText(m, jauge.x+48, jauge.y+40, font, 32, color, screen);
}
