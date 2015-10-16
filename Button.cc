#include "Button.h"

using namespace std;

/* *********************** Nom de la fonction ************************
* createButton
*************************** Auteur, Dates ****************************
* T.Bouzans, 20/11/14
*************************** Description ******************************
* Créer un bouton interractif
*************************** Entrées **********************************
* psurface, fond du bouton
* string text, texte du bouton
* px, position x du bouton
* py, position y du bouton
* font, police à utiliser pour afficher le texte
*************************** Sorties **********************************
* Le bouton initialisé
**********************************************************************/
Button createButton(SDL_Surface *psurface, std::string text, int px, int py, TTF_Font *font)
{
    Button b;
    b.sprite = psurface;
    b.x = px;
    b.y = py;
    b.width = 200;
    b.height = 56;
    b.font = font;
    b.text = text;
    return b;

}

/* *********************** Nom de la fonction ************************
* drawButton
*************************** Auteur, Dates ****************************
* T.Bouzans, 20/11/14
*************************** Description ******************************
* Dessine un bouton à l'écran
*************************** Entrées **********************************
* pbutton, bouton à dessiner
* screen, surface sur laquelle dessiner le bouton
*************************** Sorties **********************************
* void
**********************************************************************/
void drawButton(Button *pbutton, SDL_Surface *screen)
{
    //on dessine le fond u bouton
    applySurface(pbutton->x, pbutton->y, pbutton->sprite, screen, NULL);
    // On récup-ère les dimension du texte allant etre dessiné
    Vector2 siz = getTextSize(pbutton->text, pbutton->font);
    //on créer une nouvelle couleur
    RGBA r;
    r.b = 255;r.g=255; r.r=255; r.a = 255;
    //On affiche le texte
    drawText(pbutton->text, pbutton->x + pbutton->width/2 - siz.x/2, pbutton->y + pbutton->height/2 - siz.y/2 +5, pbutton->font, 20,r,screen);
}

/* *********************** Nom de la fonction ************************
* buttonOnClick
*************************** Auteur, Dates ****************************
* T.Bouzans, 20/11/14
*************************** Description ******************************
* Teste si un joueur a cliqué sur le bouton
*************************** Entrées **********************************
* event, SDL_Event produit par le clic
* button, bouton à tester
*************************** Sorties **********************************
* True si clic sur le bouton
* False sinon
**********************************************************************/
bool buttonOnClick(SDL_Event *event, Button *button)
{
    //ON teste si l'evenement est bien un clic de souris
    if(event->type==SDL_MOUSEBUTTONDOWN)
    {
        //on récupère la position du clic
        int x = event->button.x;
        int y = event->button.y;
        //On teste si le clic est bien contenu dans le bouton
        if(x >= button->x && x <= button->x + button->width && y >= button->y && y <=button->y + button->height)
        {
            return true;
        }
    }
    return false;
}
