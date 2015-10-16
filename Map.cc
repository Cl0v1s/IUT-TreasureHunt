#include "Map.h"

using namespace std;

/* *********************** Nom de la fonction ************************
* generatePossibilites
*************************** Auteur, Dates ****************************
* C. Portron, 20/11/14
*************************** Description ******************************
* Génère un ensemble de possibilités utilisé pour générer le tableau de pièces
*************************** Entrées **********************************
* pos, tableau de possibilités
*************************** Sorties **********************************
* void
**********************************************************************/
void generatePossibilities(int pos[])
{
    int index = 0;
    for(int i = 0; i<P1_NB; i++)
        pos[i] = P1;
    index+=P1_NB;
    for(int i = index; i<index+P2_NB; i++)
        pos[i] = P2;
    index+=P2_NB;
    for(int i = index; i<index+P3_NB; i++)
        pos[i] = P3;
    index+=P3_NB;
    for(int i = index; i<index+P4_NB; i++)
        pos[i] = P4;
    index+=P4_NB;
    for(int i = index; i<index+P5_NB; i++)
        pos[i] = P5;
    index+=P5_NB;
}

/* *********************** Nom de la fonction ************************
* removePossibilites
*************************** Auteur, Dates ****************************
* C. Portron, 20/11/14
*************************** Description ******************************
* Supprime une possibilité du tableau de possibilités
*************************** Entrées **********************************
* m, tableau de possibilites
* length, mongueur du tableau
* index, index de la case devant etre supprimée
*************************** Sorties **********************************
* void
**********************************************************************/
void removePossibility(int m[], int &length, int index)
{
    for(int i = index; i < length; i++)
    {
        m[i] = m[i+1];
    }
    length = length -1;
}

/* *********************** Nom de la fonction ************************
* updateInterface
*************************** Auteur, Dates ****************************
* C. Portron, 20/11/14
* T. Bouzans, 20/11/14
*************************** Description ******************************
* Génère le tableau de pièces
*************************** Entrées **********************************
* _map, Tableau de pièces
*************************** Sorties **********************************
* void
**********************************************************************/
void initMap(Map _map)
{
    //Création du tableau de possibilité
    //TODO: améliorer ce truc
    int length = MAP_SIZE*MAP_SIZE-1;
    int pos[length];
    generatePossibilities(pos);

    //placemebnt des pièces dans le tableau
    int cmpt = 0;
    for(int i = 0; i< MAP_SIZE;i++)
    {
        for(int u = 0; u < MAP_SIZE; u++)
        {
            int index= randInt(0,length-1);

            if(!(i == MAP_SIZE/2 && u == MAP_SIZE/2))
            {
                Coin c;
                c.value = pos[index];
                if((i == MAP_SIZE/2 || u == MAP_SIZE/2) && c.value == P1) //On empeche la pièce de 100 d'etre placée sur une ligne ou colone centrale
                    u-=1;
                else
                {
                    _map[i][u] = c;
                    removePossibility(pos, length, index);
                    cmpt +=1;
                }
            }
        }
    }
    //Placement d'une piece nulle au centre de la grille
    Coin c;
    c.value = 0;
    _map[MAP_SIZE/2][MAP_SIZE/2] = c;
}

/* *********************** Nom de la fonction ************************
* getIndexInSpriteSheet
*************************** Auteur, Dates ****************************
* T.Bouzans, 21/11/14
*************************** Description ******************************
* Retourne l'index en pixel dans la feuille de sprite de la pièce possédant la valeur passée en paramètre
*************************** Entrées **********************************
* value, valeur de la pièce
*************************** Sorties **********************************
* index dans feuille de spite de la pièce passée en paramtre , en fonction de sa valeur
**********************************************************************/
int getIndexInSpriteSheet(int value)
{
            int index = 0;
            switch(value)
            {
                case 10:
                    index = 0;
                    break;
                case 20:
                    index = 60;
                    break;
                case 30:
                    index = 120;
                    break;
                case 50:
                    index = 180;
                    break;
                case 100:
                    index = 180+60;
                    break;
                    default:
                    index = -1;
            }
            return index;
}

/* *********************** Nom de la fonction ************************
* drawMap
*************************** Auteur, Dates ****************************
* C. Portron, 20/11/14
* T. Bouzans, 21/11/14
*************************** Description ******************************
* Affiche le tableau de pièces
*************************** Entrées **********************************
* _map, tableau de pièces
* coins, feuille de sprite des pièces
* screen, surface sur laquelle dessiner les pièces
*************************** Sorties **********************************
* void
**********************************************************************/
void drawMap(Map _map, SDL_Surface *coins, SDL_Surface *screen)
{
    for(int i = 0; i< MAP_SIZE; i++)
    {
        for(int u=0; u< MAP_SIZE; u++)
        {
            //on récuère l'index des pièces dans la feuille de sprite
            int index = getIndexInSpriteSheet(_map[i][u].value);


            SDL_Rect rect;
            if(index > -1)
            {
                rect.x = index;
                rect.y = 0;
                rect.w = 60;
                rect.h = 60;
            }
            else
            {
                rect.x = 0;
                rect.y = 184;
                rect.w = 60;
                rect.h = 60;
            }
            //On affiche la pièce aux bonnes coordonnées
            applySurface(i*60,u*60,coins, screen, &rect);

        }
    }
}
