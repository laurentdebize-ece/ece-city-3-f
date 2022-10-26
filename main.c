//
// Created by eleuc on 25/10/2022.
//

#include <stdio.h>
#include <raylib.h>

int main (void){
 //open a window using raylib
    InitWindow(800, 450, "Hello World");
    SetTargetFPS(60);
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello World", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }
    printf("Hello World");
    return 0;
}


