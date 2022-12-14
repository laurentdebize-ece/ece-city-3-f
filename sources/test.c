//
// Created by eleuc on 25/10/2022.
//

#include "../includes/test.h"

//
// Created by eleuc on 25/10/2022.
//

#include "../includes/test.h"
/*
int entrer_nombre(){
    int i;
    printf("Ouvrir une nouvelle map vierge (1) ou charger une partie (2) ?\n");
    fflush(stdout);
    scanf("%d", &i);
}

void test() {

    /// Création de la map
    Map_t *map = NULL;
    Queue_t *houses = NULL, *water_towers = NULL, *power_plants = NULL;
    Time_t time = {1,0,0,0,0,3,2069};
    int money = 500000;

    //map = load_map(DEFAULT_MAP_FILE_PATH);
    load_saved_map(&map, &houses, &water_towers, &power_plants, &time, &money, SAVE_1_PATH);
    connexite(map);
    /// Affichage de la map en console
    print_map_console(map);

    /// Ouverture de la fenêtre
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    //SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(WIDTH, HEIGHT, TITLE);
    SetWindowPosition(10, 50);

    /// Chargement des modèles 3D et de leur texture
    Model house_model[4];
    house_model[0] = LoadModel("../assets/Models3d/Houses/buildingP1.obj");
    house_model[1] = LoadModel("../assets/Models3d/Houses/buildingM1.obj");
    house_model[2] = LoadModel("../assets/Models3d/Houses/buildingG1.obj");
    house_model[3] = LoadModel("../assets/Models3d/Houses/buildingT1.obj");

    /// Création de la position de la souris
    Vector2 mouse_pos = {0,0}, mouse_pos_world = {0,0};

    /// Création des positions de construction de routes
    Vector2 first_road_coord = {0,0}, second_road_coord = first_road_coord, last_road_coord = first_road_coord;

    /// Création des positions des points composant le plan de la map
    Vector3 g0 = (Vector3){ -map->width*(TILES_WIDTH/2.0f + DECALAGE_MAP_X), 0.0f + DECALAGE_MAP_Y, -map->height*(TILES_WIDTH/2.0f + DECALAGE_MAP_Z)};
    Vector3 g1 = (Vector3){ map->width*(TILES_WIDTH/2.0f + DECALAGE_MAP_X), 0.0f + DECALAGE_MAP_Y,  -map->height*(TILES_WIDTH/2.0f + DECALAGE_MAP_Z)};
    Vector3 g2 = (Vector3){  map->width*(TILES_WIDTH/2.0f + DECALAGE_MAP_X), 0.0f + DECALAGE_MAP_Y,  map->height*(TILES_WIDTH/2.0f + DECALAGE_MAP_Z)};
    Vector3 g3 = (Vector3){  -map->width*(TILES_WIDTH/2.0f + DECALAGE_MAP_X), 0.0f + DECALAGE_MAP_Y, map->height*(TILES_WIDTH/2.0f + DECALAGE_MAP_Z)};

    /// Création de la position de la souris dans l'espace 3D
    Ray mouse_ray;

    /// Création de la structure HUD
    HUD_t hud;
    hud_init(&hud, (Vector2){WIDTH, HEIGHT});

    /// Création de la caméra
    Camera3D camera = camera_new(map, TILES_WIDTH);
    SetCameraMode(camera, CAMERA_FREE); // Set a free camera mode
    //SetCameraAltControl(KEY_LEFT_SHIFT); // Pour Martial qui n'a pas Alt sur son clavier

    Texture2D road_texture = LoadTexture("../assets/map/roads/road_texture.png");

    int view_mode = 0;

    SetTargetFPS(FPS);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    //int button_pressed = -1, button_pressed_last = -1, button_hovered = -1, button_hovered_last = -1;

    bool is_on_pause = false;
    int pause_counter = 0;

    int building_orientation = Building_Orientation_S;

    Vector2 screen_size = {GetScreenWidth(), GetScreenHeight()};

    // Main game loop
    while (!should_window_be_closed())        /// Est-ce qu'on ferme la fenêtre ?
    {

        /*---------------------------------------COMMANDES CLAVIER---------------------------------------*/
/*
        /// Commandes clavier
        if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL)) {
            if (IsKeyPressed(KEY_S)) {  /// Sauvegarde de la map
                save_map(map, houses, water_towers, power_plants, &time, money, SAVE_1_PATH);
            }
            if (IsKeyPressed(KEY_T)){   /// Accélération du temps
                change_time_speed(&time);
            }
            if (IsKeyPressed(KEY_P)) {  /// Pause
                is_on_pause = !is_on_pause;
                pause_counter = 0;
            }
            if (IsKeyPressed(KEY_V)) {  /// Changement de vue
                change_view_mode(&view_mode);
            }
            if (IsKeyPressed(KEY_C)) {  /// Reset de la caméra
                camera = camera_new(map, TILES_WIDTH);
            }
            if (IsKeyPressed(KEY_B))
                hud.button_selected = Button_Build;
            if (IsKeyPressed(KEY_D))
                hud.button_selected = Button_Destroy;
            if (IsKeyPressed(KEY_R))
                hud.button_selected = Button_Road;
            if (IsKeyPressed(KEY_H))
                hud.button_selected = Button_House;

        }
*/

        /*---------------------------------------UPDATE---------------------------------------*/
/*
        if (IsWindowResized()){ /// Ca pue la merde
            screen_size = get_screen_size();
            resize_hud(&hud, screen_size);
        }

        /// Mise à jour de la souris
        mouse_pos = GetMousePosition();

        /// Mise a jour de la caméra
        move_camera_with_mouse(&camera, mouse_pos, screen_size);
        //camera_update(&camera);  // ma version petee
        /// Si on clique sur la minimap
        if(CheckCollisionPointRec(mouse_pos, hud.mini_map) && IsMouseButtonDown(Mouse_Button_Left)){
            move_camera_with_mini_map(&camera, map, hud.mini_map, mouse_pos);
        }

        UpdateCamera(&camera);          // Update camera

        mouse_ray = GetMouseRay(mouse_pos, camera);
        RayCollision mouse_ground_collision = GetRayCollisionQuad(mouse_ray, g0, g1, g2, g3);
        mouse_pos_world = (Vector2) {(int) (mouse_ground_collision.point.x / TILES_WIDTH),
                                     (int) (mouse_ground_collision.point.z / TILES_WIDTH)};

        if(!pause_counter) {    /// Si on n'est pas en pause alors on update le temps
            update_time(&time);
            house_update(houses, map, &money, time.speed);
        }
*/
        /*---------------------------------------CLICK EVENT REACTION---------------------------------------*/
/*
        if ((IsMouseButtonPressed(Mouse_Button_Side_Front) || IsKeyPressed(KEY_Q)) && (hud.button_selected == Button_House || hud.button_selected == Button_Water_Tower || hud.button_selected == Button_Power_Plant)) /// Si on clique sur rotation sens positif
            building_orientation = (building_orientation + 1) % 4;

        if(hud.button_selected == Button_Destroy || hud.button_selected == Button_Road || hud.button_selected == Button_House || hud.button_selected == Button_Water_Tower || hud.button_selected == Button_Power_Plant){    /// Si on a cliqué sur un bouton de construction
            if (IsMouseButtonPressed(Mouse_Button_Right)) {
                hud.button_selected = -1;
                hud.button_hovered = -1;
            }
            else {
                switch (hud.button_selected) {
                    case Button_Destroy:
                        if (IsMouseButtonPressed(Mouse_Button_Left) && map->tiles[(int)(mouse_pos_world.y*map->width + mouse_pos_world.x)]->type == Tile_Type_House && money >= HOUSE_PRICE/5) {
                            house_destroy_one(map, &houses, map->tiles[(int)(mouse_pos_world.y*map->width + mouse_pos_world.x)]->building);
                            money -= HOUSE_PRICE/5;
                        }
                        else if (IsMouseButtonPressed(Mouse_Button_Left) && map->tiles[(int)(mouse_pos_world.y*map->width + mouse_pos_world.x)]->type == Tile_Type_Builing) {
                            if (map->tiles[(int)(mouse_pos_world.y*map->width + mouse_pos_world.x)]->varient == Building_Varient_Water_Tower){
                                money -= WATER_TOWER_PRICE/5;
                                water_tower_destroy_one(map, &water_towers, map->tiles[(int)(mouse_pos_world.y*map->width + mouse_pos_world.x)]->building);
                            }
                            else if (map->tiles[(int)(mouse_pos_world.y*map->width + mouse_pos_world.x)]->varient == Building_Varient_Power_Plant){
                                money -= POWER_PLANT_PRICE/5;
                                power_plant_destroy_one(map, &power_plants, map->tiles[(int)(mouse_pos_world.y*map->width + mouse_pos_world.x)]->building);
                            }
                        }
                        else  destroy_roads(map, mouse_pos_world, &first_road_coord, &second_road_coord, &last_road_coord, &money);
                        break;
                    case Button_Road:
                        build_roads(map, mouse_pos_world, &first_road_coord, &second_road_coord, &last_road_coord, &money, mouse_ground_collision.hit);
                        break;
                    case Button_House:    /// House mode on

                        if (IsMouseButtonPressed(Mouse_Button_Left) && is_possible_to_build(map, mouse_pos_world, Tile_Type_House, money, building_orientation)) {
                            add_house(map, &houses, mouse_pos_world, building_orientation);
                            money -= HOUSE_PRICE;
                            if (!IsKeyDown(KEY_LEFT_SHIFT) && !IsKeyDown(KEY_RIGHT_SHIFT))    /// Shift not pressed
                                hud.button_selected = Button_Build;
                            else
                                hud.button_selected = Button_House;
                            hud.button_hovered = -1;
                        }
                        break;

                    case Button_Water_Tower:    /// Water tower mode on
                        if (IsMouseButtonPressed(Mouse_Button_Left) && is_possible_to_build(map, mouse_pos_world, Tile_Type_Builing, money, building_orientation)) {
                            add_water_tower(map, &water_towers, mouse_pos_world, building_orientation);
                            money -= WATER_TOWER_PRICE;
                            if (!IsKeyDown(KEY_LEFT_SHIFT) && !IsKeyDown(KEY_RIGHT_SHIFT))    /// Shift not pressed
                                hud.button_selected = Button_Build;
                            else
                                hud.button_selected = Button_Water_Tower;
                            hud.button_hovered = -1;
                        }
                        break;

                    case Button_Power_Plant:    /// Power plant mode on
                        if (IsMouseButtonPressed(Mouse_Button_Left) && is_possible_to_build(map, mouse_pos_world, Tile_Type_Builing, money, building_orientation)) {
                            add_power_plant(map, &power_plants, mouse_pos_world, building_orientation);
                            money -= POWER_PLANT_PRICE;
                            if (!IsKeyDown(KEY_LEFT_SHIFT) && !IsKeyDown(KEY_RIGHT_SHIFT))    /// Shift not pressed
                                hud.button_selected = Button_Build;
                            else
                                hud.button_selected = Button_Power_Plant;
                            hud.button_hovered = -1;
                        }
                        break;
                }
            }
        }
        else if (is_mouse_on_hud(mouse_pos)){
            mouse_pos_world = (Vector2){-1,-1};
            if (hud.button_selected==-1) hud.button_hovered = get_button_hovered(hud.tab_buttons, 5, mouse_pos);
            else if (hud.button_selected == Button_Build) hud.button_hovered = get_button_hovered(hud.tab_buttons, 5, mouse_pos);
            if (IsMouseButtonPressed(Mouse_Button_Left)) {
                switch (hud.button_selected) {
                    case Button_Build:    /// Build mode on
                        hud.button_selected = hud.button_hovered;
                        if (hud.button_selected == Button_1) {    /// Return button pressed
                            hud.button_selected = -1;    /// Build mode off
                        } else if (hud.button_selected == Button_2) {    /// Road button pressed
                            hud.button_selected = Button_Road;    /// Road mode on
                            first_road_coord = (Vector2) {-1, -1};
                            second_road_coord = (Vector2) {-1, -1};
                            last_road_coord = (Vector2) {-1, -1};
                        } else if (hud.button_selected == Button_3) {    /// House button pressed
                            hud.button_selected = Button_House;    /// House mode on
                        } else if (hud.button_selected == Button_4) {    /// Water tower button pressed
                            hud.button_selected = Button_Water_Tower;    /// Water tower mode on
                        } else if (hud.button_selected == Button_5) {    /// Power plant button pressed
                            hud.button_selected = Button_Power_Plant;    /// Power plant mode on
                        } else hud.button_selected = Button_Build;    /// Build mode stays on
                        break;

                    default:    /// No mode on, default menu mode
                        hud.button_selected = hud.button_hovered;
                        if (hud.button_selected == Button_2) first_road_coord = (Vector2){-1,-1};
                        if (hud.button_selected == Button_3) {   /// View button pressed
                            change_view_mode(&view_mode);
                            hud.button_selected = -1;
                        } else if (hud.button_selected == Button_4) {  /// Pause button pressed
                            is_on_pause = !is_on_pause;
                            pause_counter = 0;
                            hud.button_selected = -1;
                        } else if (hud.button_selected == Button_5) {  /// Speed button pressed
                            change_time_speed(&time);
                            hud.button_selected = -1;
                        }
                        break;
                }
            }
        }
*/
        /*---------------------------------------DRAWING---------------------------------------*/
/*
        BeginDrawing();

        ClearBackground(SKYBLUE); // Clear background to sky blue

        BeginMode3D(camera);

        map_draw(map, road_texture, TILES_WIDTH, view_mode);

        if (!view_mode) {
            house_draw(houses, house_model);
            water_tower_draw(water_towers, 0);
            power_plant_draw(power_plants, 0);
        }

        if (hud.button_selected == Button_House && mouse_ground_collision.hit) {
            draw_transparent_house(map, mouse_pos_world, money, building_orientation, &house_model[1]);
        }
        else if (hud.button_selected == Button_Water_Tower && mouse_ground_collision.hit) {
            draw_transparent_water_tower(map, mouse_pos_world, money, building_orientation, 0);
        }
        else if (hud.button_selected == Button_Power_Plant && mouse_ground_collision.hit) {
            draw_transparent_power_plant(map, mouse_pos_world, money, building_orientation, 0);
        }

        EndMode3D();

        DrawRectangle(10, 10, 350, 50, Fade(GREEN, 0.5f));
        DrawRectangleLines(10, 10, 350, 50, GREEN);
        DrawText(TextFormat("Money : $%d", money), 20, 20, 30, BLACK);

        DrawRectangle(370, 10, 350, 50, Fade(BLUE, 0.5f));
        DrawRectangleLines(370, 10, 350, 50, DARKBLUE);
        DrawText(TextFormat("Water : %d/%d", map->water_tower_count*WATER_TOWER_CAPACITY, map->water_tower_count*WATER_TOWER_CAPACITY), 380, 20, 30, BLACK);

        DrawRectangle(730, 10, 350, 50, Fade(YELLOW, 0.5f));
        DrawRectangleLines(730, 10, 350, 50, ORANGE);
        DrawText(TextFormat("Power : %d/%d", map->power_plant_count*POWER_PLANT_CAPACITY, map->power_plant_count*POWER_PLANT_CAPACITY), 740, 20, 30, BLACK);

        print_time((Vector2) {screen_size.x - 310, 10}, &time);

        // Draw camera position
        DrawText(TextFormat("FPS : %d\nTime speed : x%d\nCounter : %d", GetFPS(), time.speed, time.counter), 10, 100, 10, BLACK);

        if(hud.button_selected == Button_Destroy || hud.button_selected == Button_Road || hud.button_selected == Button_House || hud.button_selected == Button_Water_Tower || hud.button_selected == Button_Power_Plant) {
            DrawRectangle((screen_size.x - MeasureText("Right click to disable", 20))/2 - 10, screen_size.y/16, MeasureText("Right click to disable", 20) + 20, 70, Fade(GRAY, 0.5f));
            DrawRectangleLines((screen_size.x - MeasureText("Right click to disable", 20))/2 - 10, screen_size.y/16, MeasureText("Right click to disable", 20) + 20, 70, Fade(DARKGRAY, 0.5f));
            DrawText("Build mode active", (GetScreenWidth()-MeasureText("Build mode active", 20))/2, screen_size.y/16 + 5, 20, Fade(BLACK, 0.5f));
            DrawText("Right click to disable", (GetScreenWidth()-MeasureText("Right click to disable", 20))/2, screen_size.y/16 + 25, 20, Fade(BLACK, 0.5f));
            DrawText("Shift to keep active", (GetScreenWidth()-MeasureText("Shift to keep active", 20))/2, screen_size.y/16 + 45, 20, Fade(BLACK, 0.5f));
        }

        else {
            draw_hud(hud.hud_textures, hud.tab_buttons, mouse_pos, screen_size, hud.button_selected, view_mode, is_on_pause, time.speed);
            draw_minimap(map, hud.mini_map, (Vector2){camera.position.x, camera.position.z}, (Vector2){camera.target.x, camera.target.z}, view_mode);
            if (hud.button_hovered != -1) draw_button_description(mouse_pos, hud.button_selected, hud.button_hovered);
        }

        if (is_on_pause) {
            pause_counter++;
            DrawText("PAUSE", screen_size.x / 2 - MeasureText("PAUSE", 40) / 2, screen_size.y / 2 - 20, 50, Fade(WHITE, fabs(cos(pause_counter*PAUSE_BLINK_RATIO))));
        }

        EndDrawing();
*/
        /*---------------------------------------FIN DE BOUCLE---------------------------------------*/
    //}
/*
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    map_destroy(&map);
    house_destroy(&houses);
    water_tower_destroy(&water_towers);
    power_plant_destroy(&power_plants);
}
*/