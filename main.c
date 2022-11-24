#include <stdio.h>
#include <raylib.h>
#include "includes/test.h"
#include "includes/menu_accueil.h"
#include "includes/menu_UI.h"


#define TITLE "ECE City"

int main (void){

    int etat=0;
    int* pointeurEtat= &etat;


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

    image = LoadTexture(sprite_Capitaliste);
    image2 = LoadTexture(sprite_Communiste);
    image_ecran_accueil = LoadTexture(ecran_accueil);
    music = LoadMusicStream("../assets/Sound/Music/MUSIC.mp3");
    PlayMusicStream(music);

    while(!WindowShouldClose()) {

        UpdateMusicStream(music);

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

    return 0;
}