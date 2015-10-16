#include "Lib.h"

using namespace std;





/* *********************** Nom de la fonction ************************
* loadImage
*************************** Auteur, Dates ****************************
* N. journet
*************************** Description ******************************
* charge une image
*************************** Entr�es **********************************
* filename, nom du fichier contenant l'image � charger
*************************** Sorties **********************************
* SDL_Surface contenant l'image charg�e
**********************************************************************/
SDL_Surface *load_image( std::string filename )
{

    //Temporary storage for the image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;
     //Load the image

    loadedImage = IMG_Load( filename.c_str() );
    //If nothing went wrong in loading the image
    if( loadedImage != NULL )
    {
        //Create an optimized image
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old image
        SDL_FreeSurface( loadedImage );
    }

      //Return the optimized image
    return optimizedImage;
}


/* *********************** Nom de la fonction ************************
* loadImageTransparent
*************************** Auteur, Dates ****************************
* N. Journet
*************************** Description ******************************
* charge une image en g�rant la transparence
*************************** Entr�es **********************************
* filenane, fichier � charger
* r, inex de rouge du maque de transparence
* g, index de vert du masque de transparence
* b, index de bleu du masque de transparence
*************************** Sorties **********************************
* SDL_Surface contenant l'image charg�e
**********************************************************************/
SDL_Surface * LoadImageTransparent(string filename, int r, int g, int b)
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( filename.c_str() );

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized image
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old image
        SDL_FreeSurface( loadedImage );

        //If the image was optimized just fine
        if( optimizedImage != NULL )
        {
            //Map the color key
            Uint32 colorkey = SDL_MapRGB( optimizedImage->format, r, g, b );

             //Set all pixels of color R 0, G 0xFF, B 0xFF to be transparent
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
        }


     }
   //Return the optimized image
   return optimizedImage;

}

/* *********************** Nom de la fonction ************************
* applySurface
*************************** Auteur, Dates ****************************
* N.Journet
*************************** Description ******************************
* Affiche une SDL_Surface � l'�cran
*************************** Entr�es **********************************
* x, posiotn x � laquelle doit etre affich�e l'image
* y, position y � laquelle doit etre affich�e l'image
* source, Surface � afficher
* destination, surface sur laquelle dessiner la source
* clip, rectangle de la source devant etre affich�
*************************** Sorties **********************************
* void
**********************************************************************/
void applySurface(int x, int y, SDL_Surface* source,
         SDL_Surface* destination, SDL_Rect* clip)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, clip, destination, &offset );
}


/* *********************** Nom de la fonction ************************
* drawText
*************************** Auteur, Dates ****************************
* N. Journet
* C. Portron, 10/11/14
*************************** Description ******************************
* Affiche du texte (g�rant la transparence) � l'�cran
*************************** Entr�es **********************************
* message, texte � afficher
* x, position x du texte
* y, position y du texte
* fontSize, taille du texte devant etre affich�
* textColor, couleur g�rant la transparence � utiliser pour afficher le texte
* screen, surface sur laquelle dessiner le texte
*************************** Sorties **********************************
* void
**********************************************************************/
void
drawText(std::string message,int x,int y,
          TTF_Font *font,int fontSize,RGBA textColor,SDL_Surface* &screen)
{
  string mot="";
  string space=" ";
  int i=0,j;
  SDL_Surface *mes=NULL;

  j = message.find(space);
      SDL_Color texColor;
      texColor.r = textColor.r;
      texColor.g = textColor.g;
      texColor.b = textColor.b;
  while( j != string::npos )
    {
      mot=message.substr(i,j-i);
      if(mot != "")
    {

      mes=TTF_RenderText_Solid(font,mot.c_str(),texColor);
      SDL_SetAlpha(mes,SDL_SRCALPHA,textColor.a);
      applySurface(x,y,mes,screen,NULL);
      x+=mes->w;
      SDL_FreeSurface(mes);
    }
      x+=fontSize;
      i=j+1;
      j = message.find(space,i);
    }

  mot=message.substr(i);
  mes=TTF_RenderText_Solid(font,mot.c_str(),texColor);
  SDL_SetAlpha(mes,SDL_SRCALPHA,textColor.a);
  applySurface(x,y,mes,screen,NULL);
  SDL_FreeSurface(mes);
}


/* *********************** Nom de la fonction ************************
* updateInterface
*************************** Auteur, Dates ****************************
* C. Portron, 10/11/14
*************************** Description ******************************
* Retourne un vecteur contenant la surface utilis�e par le texte pass� en param�tre, une fois affich�
*************************** Entr�es **********************************
* text, texte � tester
* font, TTF_Font utilis�e pour afficher le texte
*************************** Sorties **********************************
* void
**********************************************************************/
Vector2 getTextSize(std::string text, TTF_Font *font)
{
    Vector2 p;
    SDL_Color c;
    c.r = 0;
    c.b = 0;
    c.g = 0;
    SDL_Surface *mes=TTF_RenderText_Solid(font,text.c_str(),c);
    p.x = mes->w;
    p.y = mes->h;
    return p;
}

/* *********************** Nom de la fonction ************************
* randInt
*************************** Auteur, Dates ****************************
* C. Portron, 10/11/14
*************************** Description ******************************
* MRetourne un nombre entier al�atoire compris entre les bornes mi et ma
*************************** Entr�es **********************************
* mi, valeur minimale de l'interval
* ma, valeur maximale de l'interval
*************************** Sorties **********************************
* entier al�atoire
**********************************************************************/
int randInt(int mi, int ma)
{
    return mi + rand() % ((ma) - (mi) +1);
}

/* *********************** Nom de la fonction ************************
* manageFrame
*************************** Auteur, Dates ****************************
* C. Portron, 21/11/14
*************************** Description ******************************
* Permet de conserver un framerate constant
*************************** Entr�es **********************************
* startMs, nombre de tick auquel � commenc� la fonction appelante
*************************** Sorties **********************************
* void
**********************************************************************/
void manageFrames(int startMs)
{
    //On r�cup�re le nombre de tick courant depuis le d�but du fonctionnement du jeu
    int endMs = SDL_GetTicks();
    int delayMs = FPS - (endMs - startMs);
    //Correction du bug suivant:  suite � microfreeze amenant le delai � etre sup�rieur aux fps.
    if(delayMs<=0)
        delayMs = 20;
    SDL_Delay(delayMs);
}


/* *********************** Nom de la fonction ************************
* coonvertToString
*************************** Auteur, Dates ****************************
* C. Portron, 21/11/14
*************************** Description ******************************
* COnvertit en entier en chaine de caract�re
*************************** Entr�es **********************************
* e, entier � convertir
*************************** Sorties **********************************
* chaine de caract�res corresspondant � l'entier pass� en param�tre
**********************************************************************/
string convertToString(int e)
{
    string s;
    stringstream t;
    t << e;
    s = t.str();
    return s;
}

/* *********************** Nom de la fonction ************************
* moveIntArrayRight
*************************** Auteur, Dates ****************************
* C. Portron, 14/12/14
*************************** Description ******************************
* d�cale un tableau d'entier vers la droite depuis l'index
*************************** Entr�es **********************************
* tab, tableau d'entier � d�caler
* index, index de la permi�re case � d�caler
* length, longueur actuelle du tableau
* max_length, longueur maximale du tableau
*************************** Sorties **********************************
* void
**********************************************************************/
void moveIntArrayRight(int tab[], int index, int &length, int max_length)
{
    for(int i = length; i>index; i--)
    {
        if(i<max_length)
        {
            tab[i] = tab[i-1];
        }
    }
    if(length < max_length)
        length += 1;
}
