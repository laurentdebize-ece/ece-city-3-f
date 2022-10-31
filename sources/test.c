//
// Created by eleuc on 25/10/2022.
//

#include "../includes/test.h"

void test() {

    Map_t *map = load_map("../assets/map/map.txt");
    print_map_console(map);
    //SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(WIDTH, HEIGHT, TITLE);

    Model house = LoadModel("../assets/models/house.obj");
    Vector2 tabModels[10];
    int nbModels = 0;

    Camera3D camera = camera_new();

    Vector3 cubePosition = { 0.0f + DECALAGE_MAP_X, 1.5f + DECALAGE_MAP_Y, 0.0f + DECALAGE_MAP_Z};
    Vector2 mouse_pos = {0,0};

    // terrain du sol
    Vector3 g0 = (Vector3){ -MAP_WIDTH*TILES_WIDTH/2.0f + DECALAGE_MAP_X, 0.0f + DECALAGE_MAP_Y, -MAP_HEIGHT*TILES_WIDTH/2.0f + DECALAGE_MAP_Z};
    Vector3 g1 = (Vector3){ MAP_WIDTH*TILES_WIDTH/2.0f + DECALAGE_MAP_X, 0.0f + DECALAGE_MAP_Y,  -MAP_HEIGHT*TILES_WIDTH/2.0f + DECALAGE_MAP_Z};
    Vector3 g2 = (Vector3){  MAP_WIDTH*TILES_WIDTH/2.0f + DECALAGE_MAP_X, 0.0f + DECALAGE_MAP_Y,  MAP_HEIGHT*TILES_WIDTH/2.0f + DECALAGE_MAP_Z};
    Vector3 g3 = (Vector3){  -MAP_WIDTH*TILES_WIDTH/2.0f + DECALAGE_MAP_X, 0.0f + DECALAGE_MAP_Y, MAP_HEIGHT*TILES_WIDTH/2.0f + DECALAGE_MAP_Z};

    Ray mouse_ray;

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

        mouse_ray = GetMouseRay(mouse_pos, camera);

        RayCollision mouse_ground_collision = GetRayCollisionQuad(mouse_ray, g0, g1, g2, g3);

        if(IsMouseButtonPressed(Mouse_Button_Left)){
            if(mouse_ground_collision.hit && is_there_place_to_build(map, (Vector2) {mouse_ground_collision.point.x/TILES_WIDTH, mouse_ground_collision.point.z/TILES_WIDTH}, TILE_HOUSE)){
                test_build_house(map, (Vector2) {mouse_ground_collision.point.x/TILES_WIDTH, mouse_ground_collision.point.z/TILES_WIDTH});
                tabModels[nbModels] = (Vector2){(int)mouse_ground_collision.point.x, (int)mouse_ground_collision.point.z};
                nbModels++;
            }
        }

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

        map_draw(map, TILES_WIDTH);
        for (int i = 0; i < nbModels; ++i) {
            DrawModel(house, (Vector3){tabModels[i].x, 1, tabModels[i].y}, 1, GRAY);
        }

        //DrawPlane((Vector3){0.0f + DECALAGE_MAP_X, 0.0f + DECALAGE_MAP_Y, 0.0f + DECALAGE_MAP_Z}, (Vector2){100, 100}, GREEN);

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
        DrawText(TextFormat("Mouse collision coords : X = %f, Y = %f, Z = %f", mouse_ground_collision.point.x, mouse_ground_collision.point.y, mouse_ground_collision.point.z), 40, 280, 20, BLACK);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    map_destroy(&map);
}

void test_chargement_map(){
    Map_t *map = load_map("../assets/map/map.txt");
    print_map_console(map);
    map_destroy(&map);
}