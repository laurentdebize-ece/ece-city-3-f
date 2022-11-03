//
// Created by eleuc on 25/10/2022.
//

#include "../includes/test.h"

void draw_cube_on_map(Map_t *map, Vector2 building_core_position){
    Vector3 cube_position = {building_core_position.x*TILES_WIDTH + DECALAGE_MAP_X, 0.75f + DECALAGE_MAP_Y, building_core_position.y*TILES_WIDTH + DECALAGE_MAP_Z};
    DrawCube(cube_position, 1.5f, 1.5f, 1.5f, BLACK);
}

void test() {

    Map_t *map = load_map("../assets/map/map.txt");
    House_t *house = NULL;
    print_map_console(map);
    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(WIDTH, HEIGHT, TITLE);

    Model house_model = LoadModel("../assets/models/house.obj");
    Texture2D texture = LoadTexture("../assets/textures/house.mtl");
    house_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

    Vector2 tabModels[10];
    int nbModels = 0;

    Camera3D camera = camera_new();

    Vector2 mouse_pos = {0,0};

    Vector2 first_road_coord = {0,0}, second_road_coord = first_road_coord, last_road_coord = first_road_coord;

    // terrain du sol
    Vector3 g0 = (Vector3){ -MAP_WIDTH*TILES_WIDTH/2.0f + DECALAGE_MAP_X, 0.0f + DECALAGE_MAP_Y, -MAP_HEIGHT*TILES_WIDTH/2.0f + DECALAGE_MAP_Z};
    Vector3 g1 = (Vector3){ MAP_WIDTH*TILES_WIDTH/2.0f + DECALAGE_MAP_X, 0.0f + DECALAGE_MAP_Y,  -MAP_HEIGHT*TILES_WIDTH/2.0f + DECALAGE_MAP_Z};
    Vector3 g2 = (Vector3){  MAP_WIDTH*TILES_WIDTH/2.0f + DECALAGE_MAP_X, 0.0f + DECALAGE_MAP_Y,  MAP_HEIGHT*TILES_WIDTH/2.0f + DECALAGE_MAP_Z};
    Vector3 g3 = (Vector3){  -MAP_WIDTH*TILES_WIDTH/2.0f + DECALAGE_MAP_X, 0.0f + DECALAGE_MAP_Y, MAP_HEIGHT*TILES_WIDTH/2.0f + DECALAGE_MAP_Z};

    Ray mouse_ray;

    SetCameraMode(camera, CAMERA_FREE); // Set a free camera mode

    int counter = 0, secs = 0, mins = 0, hours = 0;

    SetTargetFPS(FPS);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------


    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        mouse_pos = GetMousePosition();

        move_camera_with_mouse(&camera, mouse_pos);
        //camera_update(&camera);  ma version petee

        UpdateCamera(&camera);          // Update camera

        mouse_ray = GetMouseRay(mouse_pos, camera);
        RayCollision mouse_ground_collision = GetRayCollisionQuad(mouse_ray, g0, g1, g2, g3);

        update_time(&counter, &secs, &mins, &hours);

        house_update(house);

        if(IsMouseButtonPressed(Mouse_Button_Left)){
            if(mouse_ground_collision.hit && is_possible_to_build(map, (Vector2){(int)(mouse_ground_collision.point.x/TILES_WIDTH), (int)(mouse_ground_collision.point.z/TILES_WIDTH)}, Tile_Type_House)){
                add_house(map, &house, (Vector2) {(int)(mouse_ground_collision.point.x/TILES_WIDTH), (int)(mouse_ground_collision.point.z/TILES_WIDTH)});
                nbModels++;
            }
        }


        if(IsMouseButtonPressed(Mouse_Button_Right)){
            first_road_coord = (Vector2){(int)(mouse_ground_collision.point.x/TILES_WIDTH), (int)(mouse_ground_collision.point.z/TILES_WIDTH)};
            second_road_coord = (Vector2){(int)(mouse_ground_collision.point.x/TILES_WIDTH), (int)(mouse_ground_collision.point.z/TILES_WIDTH)};
            last_road_coord = (Vector2){(int)(mouse_ground_collision.point.x/TILES_WIDTH), (int)(mouse_ground_collision.point.z/TILES_WIDTH)};
        } else if(IsMouseButtonDown(Mouse_Button_Right)) {
            if(vec2D_sub(first_road_coord, second_road_coord).x == 0 && vec2D_sub(first_road_coord, second_road_coord).y == 0){
                second_road_coord = (Vector2){(int)(mouse_ground_collision.point.x/TILES_WIDTH), (int)(mouse_ground_collision.point.z/TILES_WIDTH)};
            }
            else if(vec2D_sub(first_road_coord, second_road_coord).x) last_road_coord.x = (int)(mouse_ground_collision.point.x/TILES_WIDTH);
            else last_road_coord.y = (int)(mouse_ground_collision.point.z/TILES_WIDTH);
        }
        else if (IsMouseButtonReleased(Mouse_Button_Right)){
            if(mouse_ground_collision.hit && (vec2D_sub(first_road_coord, second_road_coord).x != 0 || vec2D_sub(first_road_coord, second_road_coord).y != 0)){
                build_line_of_road(map, first_road_coord, last_road_coord);
            }
        }

        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        map_draw(map, TILES_WIDTH);
        for (int i = 0; i < nbModels; ++i) {
            DrawModel(house_model, (Vector3){tabModels[i].x, 1, tabModels[i].y}, 1, GRAY);
        }

        EndMode3D();

        DrawRectangle( 10, 10, 320, 133, Fade(SKYBLUE, 0.5f));
        DrawRectangleLines( 10, 10, 320, 133, BLUE);

        //DrawText("Free camera default controls:", 20, 20, 10, BLACK);
        //DrawText("- Mouse Wheel to Zoom in-out", 40, 40, 10, DARKGRAY);
        //DrawText("- Mouse Wheel Pressed to Pan", 40, 60, 10, DARKGRAY);
        //DrawText("- Alt + Mouse Wheel Pressed to Rotate", 40, 80, 10, DARKGRAY);
        //DrawText("- Alt + Ctrl + Mouse Wheel Pressed for Smooth Zoom", 40, 100, 10, DARKGRAY);
        //DrawText("- Z to zoom to (0, 0, 0)", 40, 120, 10, DARKGRAY);
        print_time((Vector2){10, 10}, secs, mins, hours);
        DrawText(TextFormat("Camera coords : X = %f, Y = %f, Z = %f", camera.position.x, camera.position.y, camera.position.z), 40, 200, 20, BLACK);
        DrawText(TextFormat("Camera angle = %f pi", getRadianAngleBetween2Vec2D(new_vec2D(camera.target.x, camera.target.z), new_vec2D(camera.position.x, camera.position.z))), 40, 240, 20, BLACK);
        DrawText(TextFormat("Mouse collision coords : X = %f, Y = %f, Z = %f, hit = %d", mouse_ground_collision.point.x, mouse_ground_collision.point.y, mouse_ground_collision.point.z, mouse_ground_collision.hit), 40, 280, 20, BLACK);

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