//
// Created by eleuc on 25/10/2022.
//

#include "../includes/test.h"

void test() {

    //SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(WIDTH, HEIGHT, TITLE);

    Camera3D camera = camera_new();

    Vector3 cubePosition = { 0.0f + DECALAGE_MAP_X, 1.5f + DECALAGE_MAP_Y, 0.0f + DECALAGE_MAP_Z};
    Vector2 mouse_pos = {0,0};

    SetCameraMode(camera, CAMERA_FREE); // Set a free camera mode

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------


    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        mouse_pos = GetMousePosition();

        //move_camera_with_mouse(&camera, mouse_pos);
        //camera_update(&camera);  ma version petee

        UpdateCamera(&camera);          // Update camera

        if (IsKeyDown('Z')) camera.target = (Vector3){ 0.0f + DECALAGE_MAP_X, 0.0f + DECALAGE_MAP_Y, 0.0f + DECALAGE_MAP_Z};
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        IsKeyDown('Q') ? cubePosition.y += 1 : 0;
        IsKeyDown('S') ? cubePosition.y -= 1 : 0;
        IsKeyDown('W') ? DrawCube(cubePosition, 10.0f, 10.0f, 10.0f, RED) : DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, BLUE);

        DrawCube(cubePosition, 3.0f, 3.0f, 3.0f, YELLOW);
        DrawCubeWires(cubePosition, 3.0f, 3.0f, 3.0f, BLACK);


        DrawPlane((Vector3){0.0f + DECALAGE_MAP_X, 0.0f + DECALAGE_MAP_Y, 0.0f + DECALAGE_MAP_Z}, (Vector2){100, 100}, GREEN);
        DrawGrid2(10, 1.0f, (Vector3){DECALAGE_MAP_X, DECALAGE_MAP_Y + 0.01, DECALAGE_MAP_Z});

        EndMode3D();

        DrawRectangle( 10, 10, 320, 133, Fade(SKYBLUE, 0.5f));
        DrawRectangleLines( 10, 10, 320, 133, BLUE);

        DrawText("Free camera default controls:", 20, 20, 10, BLACK);
        DrawText("- Mouse Wheel to Zoom in-out", 40, 40, 10, DARKGRAY);
        DrawText("- Mouse Wheel Pressed to Pan", 40, 60, 10, DARKGRAY);
        DrawText("- Alt + Mouse Wheel Pressed to Rotate", 40, 80, 10, DARKGRAY);
        DrawText("- Alt + Ctrl + Mouse Wheel Pressed for Smooth Zoom", 40, 100, 10, DARKGRAY);
        DrawText("- Z to zoom to (0, 0, 0)", 40, 120, 10, DARKGRAY);
        DrawText(TextFormat("Camera coords : X = %f, Y = %f, Z = %f", camera.position.x, camera.position.y, camera.position.z), 40, 200, 20, BLACK);
        DrawText(TextFormat("Camera angle = %f pi", getRadianAngleBetween2Vec2D(new_vec2D(camera.target.x, camera.target.z), new_vec2D(camera.position.x, camera.position.z))), 40, 240, 20, BLACK);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

}

void test_chargement_map(){
    Map_t *map = load_map("../assets/map/map.txt");
    print_map_console(map);
    map_destroy(&map);
}