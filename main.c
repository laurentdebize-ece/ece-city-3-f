#include <stdio.h>
#include <raylib.h>
#include "includes/test.h"
#include "debutMenu.h"
#include "menu_accueil.h"
#include "menu_UI.h"

#define TITLE "ECE City"

int main (void){

    int etat=0;
    int* pointeurEtat= &etat;

    Menu_Bouttons etatA = Accueil;
    Menu_Bouttons* pointeurEtatA = &etatA; //remplacer les valeurs de etat par les enum de etatA

    Texture2D image,image2,image_ecran_accueil;
    Music music;
    const char* sprite_Capitaliste = "../PIGGYBANKMODIF.png";
    const char* sprite_Communiste = "../CommunisteMODIF.png";
    const char* ecran_accueil = "../FONDECRAN.png";

    InitWindow(WIDTH,HEIGHT,TITLE);

    SetTargetFPS(60);

    InitAudioDevice();

    image = LoadTexture(sprite_Capitaliste);
    image2 = LoadTexture(sprite_Communiste);
    image_ecran_accueil = LoadTexture(ecran_accueil);
    music = LoadMusicStream("../MUSIC.mp3");
    PlayMusicStream(music);

    while(!WindowShouldClose()) {

        UpdateMusicStream(music);

        BeginDrawing();

        switch(*pointeurEtat) {

            case 0:
                DrawTexture(image_ecran_accueil,0,0,WHITE);
                afficher_menu_accueil(pointeurEtat);
            break;

            case 1: afficher_modes_jeu(pointeurEtat,image,image2);
            break;

            case 3: afficher_options_jeu(pointeurEtat);
            break;

            case 4 :afficher_regles(pointeurEtat);
            break;

            case 5: afficher_credits(pointeurEtat);
            break;

            default: CloseWindow();
            break;

        }

    }EndDrawing();

    StopMusicStream(music);
    UnloadMusicStream(music);
    CloseAudioDevice();

    CloseWindow();

    return 0;
}