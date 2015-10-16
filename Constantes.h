#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <string>

//Taille de la grille de jeu
const int MAP_SIZE = 7;

//Taille nombre de Frame Par seconde (pour facilité la gestion des déplacements)
const int FPS = 30;

//Dimensions de l'écran
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = MAP_SIZE*60;

//Différentes valeurs prises par les pièces (p doit etre la plus graden valeur)
const int P1 = 100;
const int P2 = 10;
const int P3 = 20;
const int P4 = 30;
const int P5 = 50;

//Nombre pièces selon leur valeur
const int P1_NB = 1;
const int P2_NB = 14;
const int P3_NB = 14;
const int P4_NB = 14;
const int P5_NB = 5;

//Nom du fichier de sauvegarde
const std::string SAVE_FILE = "highscore.dat";

//Nombre d'entrées maximum dans le fichier de sauvegarde
const int MAX_SAVES = 5;




#endif // CONSTANTES
