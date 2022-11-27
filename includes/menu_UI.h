#ifndef PROJET_MENU_UI_H
#define PROJET_MENU_UI_H

#include "src/raylib.h"




void bouton_rectangle(Rectangle rec,const char* txt,Color couleur_Base, Color couleur_clique,float font_police_txt,Color couleur_txt);
void importer_image();

void menu_audio(const char* musique_selec, Music music);
void menu_sprite(Texture2D image, const char* sprite_a_dessiner);
void menu();
void ini_Menu(Vector2 position_souris,  int screensizeWidth , int screensizeHeight,const char* title);
void resize_Menu(int width_Window, int Height_Window);


#endif //PROJET_MENU_UI_H
