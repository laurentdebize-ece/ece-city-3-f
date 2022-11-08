//
// Created by eleuc on 25/10/2022.
//

#include "../includes/test.h"

void test() {

    Map_t *map = load_map(DEFAULT_MAP_FILE_PATH);
    House_t *house = NULL;
    print_map_console(map);
    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(WIDTH, HEIGHT, TITLE);

    Model house_model = LoadModel("../assets/map/models/house.obj");
    Texture2D texture = LoadTexture("../assets/map/models/house.mtl");
    house_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

    Vector2 tabModels[10];
    int nbModels = 0;

    Camera3D camera = camera_new(map);

    Vector2 mouse_pos = {0,0};

    Vector2 first_road_coord = {0,0}, second_road_coord = first_road_coord, last_road_coord = first_road_coord;

    // terrain du sol
    Vector3 g0 = (Vector3){ -map->width*(TILES_WIDTH/2.0f + DECALAGE_MAP_X), 0.0f + DECALAGE_MAP_Y, -map->height*(TILES_WIDTH/2.0f + DECALAGE_MAP_Z)};
    Vector3 g1 = (Vector3){ map->width*(TILES_WIDTH/2.0f + DECALAGE_MAP_X), 0.0f + DECALAGE_MAP_Y,  -map->height*(TILES_WIDTH/2.0f + DECALAGE_MAP_Z)};
    Vector3 g2 = (Vector3){  map->width*(TILES_WIDTH/2.0f + DECALAGE_MAP_X), 0.0f + DECALAGE_MAP_Y,  map->height*(TILES_WIDTH/2.0f + DECALAGE_MAP_Z)};
    Vector3 g3 = (Vector3){  -map->width*(TILES_WIDTH/2.0f + DECALAGE_MAP_X), 0.0f + DECALAGE_MAP_Y, map->height*(TILES_WIDTH/2.0f + DECALAGE_MAP_Z)};

    Ray mouse_ray;

    SetCameraMode(camera, CAMERA_FREE); // Set a free camera mode

    Texture2D hud_icons = LoadTexture("../assets/bitmaps/hud/hud_icons.png");

    Rectangle build_icon_rec = {WIDTH/20.0f,  HEIGHT*3.0f/4.0f + (float)(HEIGHT/4.0f - hud_icons.height/2)/2.0f, hud_icons.width, hud_icons.height/Nb_Hud_Buttons};

    Time_t time = {0,0,0,0,3,2069};
    int money = 500000;

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

        update_time(&time);

        house_update(house, map, &money);

        if(IsMouseButtonPressed(Mouse_Button_Left)){
            if(mouse_ground_collision.hit && is_possible_to_build(map, (Vector2){(int)(mouse_ground_collision.point.x/TILES_WIDTH), (int)(mouse_ground_collision.point.z/TILES_WIDTH)}, Tile_Type_House, money)){
                add_house(map, &house, (Vector2) {(int)(mouse_ground_collision.point.x/TILES_WIDTH), (int)(mouse_ground_collision.point.z/TILES_WIDTH)});
                nbModels++;
                money -= 1000;
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
            if (mouse_ground_collision.hit && (vec2D_sub(first_road_coord, second_road_coord).x != 0 || vec2D_sub(first_road_coord, second_road_coord).y != 0)){
                money -= 10*build_line_of_road(map, first_road_coord, last_road_coord);
            }
            else if(first_road_coord.x == last_road_coord.x && first_road_coord.y == last_road_coord.y){
                if(is_possible_to_build(map, first_road_coord, Tile_Type_Road, money)){
                    build_one_road(map, first_road_coord);
                    money -= 10;
                }
            }
        }



        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(Fade(SKYBLUE, 0.5f)); // Clear background to sky blue

        BeginMode3D(camera);

        map_draw(map, TILES_WIDTH);
        for (int i = 0; i < nbModels; ++i) {
            DrawModel(house_model, (Vector3){0,0,0}, 1, GRAY);
        }
        house_draw(house);

        EndMode3D();

        DrawRectangle(0, HEIGHT*3.0f/4.0f, WIDTH, HEIGHT/4.0f, Fade(BLACK, 0.5f));
        DrawRectangleLines(0, HEIGHT*3.0f/4.0f, WIDTH, HEIGHT/4.0f, BLACK);

        DrawRectangle( 10, 10, 350, 50, Fade(GREEN, 0.5f));
        DrawRectangleLines( 10, 10, 350, 50, GREEN);
        DrawText(TextFormat("Money : $%d", money), 20, 20, 30, BLACK);

        print_time((Vector2){WIDTH - 310, 10}, &time);

        DrawText(TextFormat("Camera coords : X = %f, Y = %f, Z = %f", camera.position.x, camera.position.y, camera.position.z), 40, 200, 20, BLACK);
        DrawText(TextFormat("Camera angle = %f pi", getRadianAngleBetween2Vec2D(new_vec2D(camera.target.x, camera.target.z), new_vec2D(camera.position.x, camera.position.z))), 40, 240, 20, BLACK);
        DrawText(TextFormat("Mouse collision coords : X = %f, Y = %f, Z = %f, hit = %d", mouse_ground_collision.point.x, mouse_ground_collision.point.y, mouse_ground_collision.point.z, mouse_ground_collision.hit), 40, 280, 20, BLACK);
        DrawText(TextFormat("FPS : %d", GetFPS()), 10, 100, 20, BLACK);

        DrawTextureRec(hud_icons, (Rectangle){0, 0, hud_icons.width, hud_icons.height/Nb_Hud_Buttons}, (Vector2) {build_icon_rec.x, build_icon_rec.y}, WHITE);


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    map_destroy(&map);
    house_destroy(&house);
}