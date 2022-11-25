#include "../includes/menu_accueil.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "../includes/menu_UI.h"


#define TITLE "ECE City"


void bouton_Retour(int* pointeurEtat) {

    Rectangle Retour = {WIDTH-200,HEIGHT-100,150,50 };

    bool mouse_on_Retour = false;
    mouse_on_Retour = CheckCollisionPointRec(GetMousePosition(), Retour);


    DrawRectangleRec(Retour, DARKGRAY);

    if(mouse_on_Retour) {
        DrawRectangleRec(Retour, DARKGRAY);
        DrawText("RETOUR",(int)Retour.x+12,(int)Retour.y+10,30,WHITE);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            *pointeurEtat=0;
        }
    }
    else {
        DrawRectangleLines((int)Retour.x,(int)Retour.y,(int)Retour.width,(int)Retour.height,BLACK);
        DrawText("RETOUR",(int)Retour.x+12,(int)Retour.y+10,30,WHITE);
    }
}


void afficher_options_jeu(int* pointeurEtat) {

    Rectangle Regles = {WIDTH/6, HEIGHT/3,426,426};
    Rectangle Credits = {(WIDTH/6)+852, HEIGHT/3,426,426};

    bool mouse_on_Regles = CheckCollisionPointRec(GetMousePosition(),Regles);
    bool mouse_on_Credits = CheckCollisionPointRec(GetMousePosition(),Credits);

    BeginDrawing();

    ClearBackground(WHITE);

    bouton_rectangle(Regles,"REGLES",DARKGRAY,DARKGRAY,30,WHITE);
    bouton_rectangle(Credits,"CREDITS",DARKGRAY,DARKGRAY,30,WHITE);
    bouton_Retour(pointeurEtat);

    if(mouse_on_Regles) {
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            *pointeurEtat=4;
        }
    }

    if(mouse_on_Credits) {
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            *pointeurEtat=5;
        }
    }
    EndDrawing();
}


void afficher_credits(int* pointeurEtat) {

    Rectangle Credits = {0,0, WIDTH,HEIGHT};

    BeginDrawing();

    bouton_rectangle(Credits,"",BLUE,BLUE,0,WHITE);
    bouton_Retour(pointeurEtat);

    /*char* txt1 = "Créateurs"; //idée faire une enum pour que les txt soit les valeurs de i et comme j'aug les distance pareil on mettra j

    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {


        }

    }*/


    DrawText("Early Access Version 1.0.0", Credits.x+20,Credits.y+20,30,WHITE);
    DrawText("Créateurs :",Credits.x+20,Credits.y+80,50,WHITE);
    DrawText("EL EUCH Habib",Credits.x+20,Credits.y+140,50,WHITE);
    DrawText("SCHMITT Théo",Credits.x+20,Credits.y+200,50,WHITE);
    DrawText("ROBERGE Martial",Credits.x+20,Credits.y+260,50,WHITE);
    DrawText("MASSON Charles",Credits.x+20,Credits.y+320,50,WHITE);
    DrawText("Merci d'avoir joué à notre jeu !",Credits.x+(Credits.width - MeasureText("Merci d'avoir joué à notre jeu !",100))/2,Credits.y+500,100,WHITE);

    EndDrawing();
}

void afficher_regles(int* pointeurEtat) {

    Rectangle Regles = {0,0, WIDTH,HEIGHT};

    BeginDrawing();

    bouton_rectangle(Regles,"",BLUE,BLUE,0,WHITE);

    bouton_Retour(pointeurEtat);

    DrawText("Bienvenue dans ECE CITY !",Regles.x+20,Regles.y+20,30,WHITE);
    DrawText("Vous êtes le maire de cette belle ville, mais tout est encore à faire. En effet vous devrez construire des bâtiments,", Regles.x+20,Regles.y+80,30,WHITE);
    DrawText("gérer des ressources et faire croître votre ville",Regles.x +20 , Regles.y +140,30,WHITE);
    DrawText("Chaque maison vous rapporte de l'argent mais a besoin d'électricité et d'eau pour évoluer à un stade plus avancé",Regles.x+20, Regles.x+200,30,WHITE);




    EndDrawing();
}



void afficher_modes_jeu(int* pointeurEtat,Texture2D image,Texture2D image2) {

    bool mouse_on_Capitalistes = false;
    bool mouse_on_Communistes  = false;

    Rectangle Capitalistes = {WIDTH/6, HEIGHT/3,426,426  };
    Rectangle Communistes = {(WIDTH/6)+852, HEIGHT/3,426,426  };

    mouse_on_Communistes = CheckCollisionPointRec(GetMousePosition(), Communistes);
    mouse_on_Capitalistes = CheckCollisionPointRec(GetMousePosition(), Capitalistes);


        BeginDrawing();

            ClearBackground(WHITE);

            bouton_Retour(pointeurEtat);

            bouton_rectangle(Communistes,"COMMUNISTES",RED,RED,30,WHITE);
            bouton_rectangle(Capitalistes,"CAPITALISTES",BLUE,BLUE,30,WHITE);


            if(mouse_on_Capitalistes) {
                DrawTexture(image,Capitalistes.x,Communistes.y,WHITE);
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    *pointeurEtat=100;
                }
            }

            if(mouse_on_Communistes) {
                DrawTexture(image2,Communistes.x,Communistes.y,WHITE);
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    *pointeurEtat=200;
                }
            }
            EndDrawing();
}

void afficher_menu_accueil(int* pointeurEtat) {

    double timer = GetTime();

    Rectangle Jouer = { WIDTH/3, HEIGHT/3,640,110};
    Rectangle Charger = { WIDTH/3, (HEIGHT/3)+160,640,110};
    Rectangle Option = { WIDTH/3, (HEIGHT/3)+320,640,110};
    Rectangle Quitter = { WIDTH/3, (HEIGHT/3)+480,640,110};


    bool clignotte=false;
    bool mouse_on_Jouer = CheckCollisionPointRec(GetMousePosition(),Jouer);
    bool mouse_on_Charger = CheckCollisionPointRec(GetMousePosition(),Charger);
    bool mouse_on_Option = CheckCollisionPointRec(GetMousePosition(),Option);
    bool mouse_on_Quitter = CheckCollisionPointRec(GetMousePosition(),Quitter);

    /// La variable timer est calée sur le temps qui s'est écoulé depuis la création de la fenêtre
        if((int)timer % 2 == 0) {
            clignotte=true;
        }
        else clignotte=false;


        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawRectangleRec(Jouer,DARKGRAY);
            DrawRectangleRec(Charger,DARKGRAY);
            DrawRectangleRec(Option,DARKGRAY);
            DrawRectangleRec(Quitter,DARKGRAY);


            if(mouse_on_Jouer) {

                if(clignotte==false) {
                    DrawRectangleRec(Jouer, RED);
                    DrawText("CLIQUE ! :)",(int)Jouer.x+161,(int)Jouer.y+30,60,BLACK);
                }
                else {
                    DrawRectangleRec(Jouer, RED);
                    DrawText("JOUER",(int)Jouer.x+220,(int)Jouer.y+30,60,BLACK);
                }
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                   *pointeurEtat=1;
                }
            }
            else {
                DrawRectangleLines((int)Jouer.x,(int)Jouer.y,(int)Jouer.width,(int)Jouer.height,BLACK);
                DrawText("JOUER",(int)Jouer.x+220,(int)Jouer.y+30,60,WHITE);
            }

            if(mouse_on_Charger) {

                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    *pointeurEtat=2;
                }

                if(clignotte==false) {
                    DrawRectangleRec(Charger, RED);
                    DrawText("CLIQUE ! :)",(int)Charger.x+161,(int)Charger.y+30,60,BLACK);
                }
                else {
                    DrawRectangleRec(Charger,RED);
                    DrawText("CHARGER",(int)Charger.x+176,(int)Charger.y+30,60,BLACK);
                }
            }
            else {
                DrawRectangleLines((int)Charger.x,(int)Charger.y,(int)Charger.width,(int)Charger.height,BLACK);
                DrawText("CHARGER",(int)Charger.x+176,(int)Charger.y+30,60,WHITE);
            }

            if(mouse_on_Option) {

                if(clignotte==false) {
                    DrawRectangleRec(Option, RED);
                    DrawText("CLIQUE ! :)",(int)Option.x+161,(int)Option.y+30,60,BLACK);
                }
                else {
                    DrawRectangleRec(Option, RED);
                    DrawText("OPTION",(int)Option.x+203,(int)Option.y+30,60,BLACK);
                }
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    *pointeurEtat=3;
                }
            }
            else {
                DrawRectangleLines((int)Option.x,(int)Option.y,(int)Option.width,(int)Option.height,BLACK);
                DrawText("OPTION",(int)Option.x+203,(int)Option.y+30,60,WHITE);
            }

            if(mouse_on_Quitter) {

                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) CloseWindow();

                if(clignotte==false) {
                    DrawRectangleLines((int)Jouer.x,(int)Jouer.y,(int)Jouer.width,(int)Jouer.height,BLACK);
                    DrawRectangleRec(Quitter, RED);
                    DrawText("NE CLIQUE PAS :(",(int)Quitter.x+ 55,(int)Quitter.y+30,60,BLACK);
                }
                else {
                    DrawRectangleRec(Quitter, RED);
                    DrawText("QUITTER",(int)Quitter.x+179,(int)Quitter.y+30,60,BLACK);
                }
            }
            else {
                DrawRectangleLines((int)Quitter.x,(int)Quitter.y,(int)Quitter.width,(int)Quitter.height,BLACK);
                DrawText("QUITTER",(int)Quitter.x+179,(int)Quitter.y+30,60,WHITE);
            }
        EndDrawing();
    }



