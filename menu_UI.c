#include "menu_accueil.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "menu_UI.h"


#define TITLE "ECE City"

void bouton_rectangle(Rectangle rec,const char* txt,Color couleur_Base, Color couleur_clique,float font_police_txt,Color couleur_txt) {

    Vector2 taille_largeur_longueur = MeasureTextEx(GetFontDefault(),txt,font_police_txt,2);

    bool mouse_on_button = CheckCollisionPointRec(GetMousePosition(),rec);

    int X = MeasureText(txt,font_police_txt);

    float point_depart_x = (rec.width-taille_largeur_longueur.x)/2 +rec.x;
    float point_depart_y = (rec.height-taille_largeur_longueur.y)/2 + rec.y;


    if(mouse_on_button) {
        DrawRectangleRec(rec,couleur_clique);
        DrawText(txt,point_depart_x,point_depart_y,(int)font_police_txt,couleur_txt);
    }
    else {
        DrawRectangleRec(rec,couleur_Base);
        DrawText(txt,point_depart_x,point_depart_y,(int)font_police_txt,couleur_txt);
    }
}


void menu_audio(const char* musique_selec, Music music) {

    InitAudioDevice();

    music = LoadMusicStream(musique_selec);

    PlayMusicStream(music);
}

void menu_sprite(Texture2D image,const char* sprite_a_dessiner) {

    image = LoadTexture(sprite_a_dessiner);

    BeginDrawing();

        ClearBackground(WHITE);

        DrawTexture(image,100,100, WHITE);


        EndDrawing();
}


