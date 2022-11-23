#include "debutMenu.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 1920
#define HEIGHT 1080
#define TITLE "ECE City"
#define NomJoueurs 20


int debutMenu() {
    InitWindow(WIDTH, HEIGHT, "ECE City");
    SetTargetFPS(60);

    int argent = 1000;
    int eau = 150;
    int elec = 0;
    int population = 0;

    while(!WindowShouldClose()) {

        BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawText(TextFormat("Argent : %d", argent), 10, 10, 20, BLACK);
            DrawText(TextFormat("Eau : %d", eau), 10, 40, 20, RED);
            DrawText(TextFormat("Electricite : %d", elec), 10, 70, 20, BLUE);
            DrawText(TextFormat("Population : %d", population), 10, 100, 20, GREEN);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}


bool IsAnyKeyPressed() {
    bool keyPress = false;
    int key = GetKeyPressed();

    if((key>=32) && (key<=126)) {
        keyPress = true;
    }
    return keyPress;
}


int nomJoueurs() {

    InitWindow(WIDTH, HEIGHT, "ECE City");
    char nomJoueur[NomJoueurs+1] = "\0";
    int letterCount = 0;


    Rectangle textBox = { 10, 10, 280, 30 };
    bool mouseOnText = false;

    int framesCounter = 0;
    SetTargetFPS(60);

    while(!WindowShouldClose()) {
        if(CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
        else mouseOnText = false;

        if(mouseOnText) {
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            int key = GetCharPressed();

            while(key > 0) {
                if((key >= 32) && (key <= 125) && (letterCount < NomJoueurs)) {
                    nomJoueur[letterCount] = (char)key;
                    nomJoueur[letterCount + 1] = '\0';
                    letterCount++;
                }
                key = GetCharPressed();
            }
            if(IsKeyPressed(KEY_BACKSPACE)) {
                letterCount--;
                if(letterCount < 0) letterCount = 0;
                nomJoueur[letterCount] = '\0';
            }
        }
        else SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        if(mouseOnText) framesCounter++;
        else framesCounter = 0;

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Place le souris dans la boite pour ecrire ton nom", 10, 50, 20, DARKGRAY);

        DrawRectangleRec(textBox, LIGHTGRAY);
        if(mouseOnText) {
            DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
        }
        else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

        DrawText(nomJoueur, (int)textBox.x + 5, (int)textBox.y + 8, 20, MAROON);

        DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, NomJoueurs), 10, 80, 20, DARKGRAY);

        if(mouseOnText) {
            if(letterCount < NomJoueurs) {
                if(((framesCounter/20)%2) == 0) DrawText("_", (int)textBox.x + 8 + MeasureText(nomJoueur, 20), (int)textBox.y + 12, 20, MAROON);
            }
            else DrawText("Text box full!", 10, 110, 20, RED);
        }
        EndDrawing();
    }
    CloseWindow();
}



int premierePage() {

    InitWindow(WIDTH,HEIGHT,"ECE CITY");
    SetTargetFPS(60);

    Rectangle Rec = { WIDTH / 4.0, HEIGHT / 3.0, 800, 100};
    Rectangle Rec2 = {WIDTH/4.0,HEIGHT/2.0,800,100};

    bool mouse_on_text =false;
    bool clignotte=false;

    while(!WindowShouldClose()) {

        mouse_on_text = CheckCollisionPointRec(GetMousePosition(),Rec);
        double timer = GetTime();

        if((int)timer % 2 == 0) {
            clignotte=true;
        }
        else clignotte=false;

        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawRectangleRec(Rec, BLACK);
            DrawRectangleRec(Rec2,GREEN);

            DrawText("JOUER",(int)Rec.x+(int)Rec.width/3,(int)Rec.y+(int)Rec.height/2,50,RED);


            if(mouse_on_text) {
                DrawRectangleRec(Rec, GRAY);
                DrawRectangleLines((int)Rec.x,(int)Rec.y,(int)Rec.width,(int)Rec.height,BLACK);
            }
            else {
                DrawRectangleLines((int)Rec.x,(int)Rec.y,(int)Rec.width,(int)Rec.height,BLACK);
            }

            if(clignotte) DrawRectangleRec(Rec2,RED);
            else DrawRectangleRec(Rec2,BLUE);

            //DrawRectangle(WIDTH/4,HEIGHT/3,800,100,RED);
            //DrawRectangle(WIDTH/4,HEIGHT/2,800,100,GREEN);
            DrawRectangle(WIDTH/4,(2*HEIGHT)/3,800,100,BLUE);
            DrawRectangle(WIDTH/4,(5*HEIGHT)/6,800,100,BLACK);





            EndDrawing();


    }
    printf("%d \n",MeasureText("Jouer",50));
    CloseWindow();

    return 0;
}


