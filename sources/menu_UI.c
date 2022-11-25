#include "../includes/menu_accueil.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "../includes/menu_UI.h"
#include "../includes/test.h"


#define TITLE "ECE City"
#define WIDTH 1920
#define HEIGHT 1080


void menu() {

    /// Initialisation des variables utiles à l'affichage des bitmaps

    int etat=0;
    int* pointeurEtat= &etat;
    bool pause = false;

    Menu_Bouttons etatA = Accueil;
    Menu_Bouttons* pointeurEtatA = &etatA; //remplacer les valeurs de etat par les enum de etatA

    Texture2D image,image2,image_ecran_accueil;
    Music music;
    const char* sprite_Capitaliste = "../assets/bitmaps/Menu/PIGGYBANKMODIF.png";
    const char* sprite_Communiste = "../assets/bitmaps/Menu/CommunisteMODIF.png";
    const char* ecran_accueil = "../assets/bitmaps/Menu/FONDECRAN.png";


    InitWindow(WIDTH,HEIGHT,TITLE);

    SetTargetFPS(60);


    Game_t* game = create_game();

    InitAudioDevice();

    /// Téléchargement des bitmaps et de la musique

    image = LoadTexture(sprite_Capitaliste);
    image2 = LoadTexture(sprite_Communiste);
    image_ecran_accueil = LoadTexture(ecran_accueil);
    music = LoadMusicStream("../assets/Sound/Music/MUSIC.mp3");

    PlayMusicStream(music);

    while(!WindowShouldClose()) {

        UpdateMusicStream(music);

        if(IsKeyPressed(KEY_P)) {
            pause = !pause;
            if(pause==true) {
                PauseMusicStream(music);
            } else ResumeMusicStream(music);
        }

        switch(*pointeurEtat) {

            /// Différents cas en fonction du bouton sur lequel on clique

            case 0:
                DrawTexture(image_ecran_accueil,0,0,WHITE);
                afficher_menu_accueil(pointeurEtat);
                break;

            case 1: afficher_modes_jeu(pointeurEtat,image,image2);
                break;

            case 2:
                //load_saved_map();
                break;

            case 3: afficher_options_jeu(pointeurEtat);
                break;

            case 4 :afficher_regles(pointeurEtat);
                break;

            case 5: afficher_credits(pointeurEtat);
                break;

            case 100:
            case 200:
                StopMusicStream(music);
                loop_jeu(game);
                break;

            default:
                break;

        }
    }

    destroy_game(game);

    StopMusicStream(music);
    UnloadMusicStream(music);
    CloseAudioDevice();
}



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


