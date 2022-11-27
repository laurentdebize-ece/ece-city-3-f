#include "../includes/menu_accueil.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "../includes/menu_UI.h"
#include "../includes/test.h"
#include "../includes/map/map.h"
#include "../includes/map/save_map.h"

void resize_Menu(int width_Window, int height_Window) {
     if(!IsWindowFullscreen()) {
         int ecran = GetCurrentMonitor(); //sur quel écran est l'image/nbr d'écran connectés
         SetWindowSize(GetMonitorWidth(ecran),GetMonitorHeight(ecran));
     }

     else {
         ToggleFullscreen(); //bascule l'état de la fenêtre
         SetWindowSize(WIDTH,HEIGHT);
     }

}

void ini_Menu(Vector2 position_souris, int screensizeWidth, int screensizeHeight,const char* title) {
    InitWindow(screensizeWidth,screensizeHeight,title);
    resize_Menu(WIDTH,HEIGHT);
}

void menu() {




    /// Initialisation des variables utiles à l'affichage des bitmaps

    int etat=0;
    int* pointeurEtat= &etat;
    bool pause = false;
    bool mode2jeu= NULL;
    bool type2map = false;


    Texture2D image,image2,image_ecran_accueil,image_mode2jeu,image_option,image_coeur,image_thinking;
    Music music;

    const char* sprite_Capitaliste = "../assets/bitmaps/Menu/PIGGYBANKMODIF.png";
    const char* sprite_Communiste = "../assets/bitmaps/Menu/CommunisteMODIF.png";
    const char* ecran_accueil = "../assets/bitmaps/Menu/campagne.png";
    const char* USA_URSS = "../assets/bitmaps/Menu/COLDWAR2.png";
    const char* ecran_option = "../assets/bitmaps/Menu/Gear_Modif.png";
    const char* coeur = "../assets/bitmaps/Menu/Heart.png";
    const char* think = "../assets/bitmaps/Menu/reflexion.png";

    InitWindow(WIDTH,HEIGHT,TITLE);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    resize_Menu(WIDTH,HEIGHT);

    SetTargetFPS(FPS);

    Vector2 screen_size = {GetScreenWidth(), GetScreenHeight()};

    Game_t* game = NULL;


    InitAudioDevice();

    /// Téléchargement des bitmaps et de la musique

    image = LoadTexture(sprite_Capitaliste);
    image2 = LoadTexture(sprite_Communiste);
    image_ecran_accueil = LoadTexture(ecran_accueil);
    image_mode2jeu = LoadTexture(USA_URSS);
    image_option = LoadTexture(ecran_option);
    image_coeur = LoadTexture(coeur);
    image_thinking = LoadTexture(think);

    music = LoadMusicStream("../assets/Sound/Music/MUSIC.mp3");

    PlayMusicStream(music);

    while(!WindowShouldClose()&& *pointeurEtat!=-1) { /// case -1 correspond au bouton quitter

        UpdateMusicStream(music);

        if (IsWindowResized()){    /// Ca pue la merde
            screen_size = get_screen_size();
            if(game) {
                resize_hud(&game->hud, screen_size);
            }
        }

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

            case 1:
                DrawTexture(image_mode2jeu,0,0,WHITE);
                afficher_modes_jeu(pointeurEtat,image,image2,&mode2jeu);
                break;

            case 2: {
                game = malloc(sizeof(Game_t ));
                load_saved_map(&game->map,&game->houses,&game->water_towers,&game->power_plants,&game->time,&game->money,&game->population,&game->capitaliste,SAVE_1_PATH);
                *pointeurEtat = 200;
                break;
            }

            case 3:
                DrawTexture(image_option,0,0,WHITE);
                afficher_options_jeu(pointeurEtat);
                break;

            case 4 :afficher_regles(pointeurEtat,image_thinking);
                break;

            case 5:
                afficher_credits(pointeurEtat,image_coeur);
                break;

            case 100:
            case 200:
                if(!game) game = create_game(screen_size,mode2jeu,type2map);
                StopMusicStream(music);
                loop_jeu(game,mode2jeu);
                break;

            default:
                break;

        }
    }
    if(game) destroy_game(&game);
    UnloadTexture(image_coeur);
    UnloadTexture(image_option);
    UnloadTexture(image_mode2jeu);
    UnloadTexture(image);
    UnloadTexture(image2);
    UnloadTexture(image_ecran_accueil);
    StopMusicStream(music);
    UnloadMusicStream(music);
    CloseAudioDevice();
    CloseWindow();
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


