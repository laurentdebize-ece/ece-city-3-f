//
// Created by eleuc on 20/11/2022.
//

#include "../includes/game.h"

Game_t *create_game(void) {

    Game_t *game = malloc(sizeof(Game_t));
    game->money = 500000;
    game->time = (Time_t){1,0,0,0,0,3,2069};
    game->houses = NULL;
    game->water_towers = NULL;
    game->power_plants = NULL;

    /// Ouverture de la fenêtre (à supprimer)
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    //SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(WIDTH, HEIGHT, TITLE);
    SetWindowPosition(10, 50);

    //map = load_map(DEFAULT_MAP_FILE_PATH);
    load_saved_map(&game->map, &game->houses, &game->water_towers, &game->power_plants, &game->time, &game->money, &game->population, SAVE_1_PATH);

    connexity_init(game->map);
    print_map_console(game->map);

    /// Création de la caméra
    game->camera = camera_new(game->map, TILES_WIDTH);
    SetCameraMode(game->camera, CAMERA_FREE); // Set a free camera mode

    /// Création de la structure HUD
    hud_init(&game->hud, (Vector2) {WIDTH, HEIGHT});

    /// Chargement des modèles 3D et de leur texture
    game->house_model[0] = LoadModel("../assets/Models3d/Houses/buildingP1.obj");
    game->house_model[1] = LoadModel("../assets/Models3d/Houses/buildingM1.obj");
    game->house_model[2] = LoadModel("../assets/Models3d/Houses/buildingG1.obj");
    game->house_model[3] = LoadModel("../assets/Models3d/Houses/buildingT1.obj");

    game->power_plant_model = LoadModel("../assets/Models3d/power_plant/ncl2.obj");
    game->power_plant_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = LoadTexture("../assets/Models3d/power_plant/Nuclear station_color_1_.png");

    /// Création de la position de la souris
    game->mouse_pos_world = (Vector2){0,0};

    /// Création des positions de construction de routes
    game->first_road_coord = (Vector2){0,0};
    game->second_road_coord = game->first_road_coord;
    game->last_road_coord = game->first_road_coord;

    /// Création des positions des points composant le plan de la map
    game->plateau[0] = (Vector3){ -game->map->width*(TILES_WIDTH/2.0f + DECALAGE_MAP_X), 0.0f + DECALAGE_MAP_Y, -game->map->height*(TILES_WIDTH/2.0f + DECALAGE_MAP_Z)};
    game->plateau[1] = (Vector3){ game->map->width*(TILES_WIDTH/2.0f + DECALAGE_MAP_X), 0.0f + DECALAGE_MAP_Y,  -game->map->height*(TILES_WIDTH/2.0f + DECALAGE_MAP_Z)};
    game->plateau[2] = (Vector3){  game->map->width*(TILES_WIDTH/2.0f + DECALAGE_MAP_X), 0.0f + DECALAGE_MAP_Y,  game->map->height*(TILES_WIDTH/2.0f + DECALAGE_MAP_Z)};
    game->plateau[3] = (Vector3){  -game->map->width*(TILES_WIDTH/2.0f + DECALAGE_MAP_X), 0.0f + DECALAGE_MAP_Y, game->map->height*(TILES_WIDTH/2.0f + DECALAGE_MAP_Z)};

    /// Chargement de la texture de la route
    game->road_texture = LoadTexture("../assets/map/roads/road_texture.png");
    game->grass_texture = LoadTexture("../assets/map/grass.png");

    game->view_mode = 0;

    game->building_orientation = Building_Orientation_S;

    /// Création des variables de pause
    game-> pause_counter = 0;
    game->is_on_pause = false;

    return game;
}

void commands(Game_t *game) {
    if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL)){
        if (IsKeyPressed(KEY_S)) {  /// Sauvegarde de la map
            save_map(game->map, game->houses, game->water_towers, game->power_plants, &game->time, game->money, SAVE_1_PATH);
        }
        if (IsKeyPressed(KEY_T)) {   /// Accélération du temps
            change_time_speed(&game->time);
        }
        if (IsKeyPressed(KEY_P)) {  /// Pause
            game->is_on_pause = !game->is_on_pause;
            game->pause_counter = 0;
        }
        if (IsKeyPressed(KEY_V)) {  /// Changement de vue
            change_view_mode(&game->view_mode);
        }
        if (IsKeyPressed(KEY_C)) {  /// Reset de la caméra
            game->camera = camera_new(game->map, TILES_WIDTH);
        }
        if (IsKeyPressed(KEY_B))
            game->hud.button_selected = Button_Build;
        if (IsKeyPressed(KEY_D))
            game->hud.button_selected = Button_Destroy;
        if (IsKeyPressed(KEY_R))
            game->hud.button_selected = Button_Road;
        if (IsKeyPressed(KEY_H))
            game->hud.button_selected = Button_House;
        if (IsKeyPressed(KEY_W))
            game->hud.button_selected = Button_Water_Tower;
    }
    if (IsKeyPressed(KEY_DELETE) && game->hud.selected_entity) {
        if (game->hud.selected_entity_type == Tile_Type_House) {
            game->money -= HOUSE_PRICE/5;
            switch (((House_t*)game->hud.selected_entity)->level) {
                case Cabane:
                    game->population -= 10;
                    break;
                case Maison:
                    game->population -= 50;
                    break;
                case Immeuble:
                    game->population -= 100;
                    break;
                case Gratte_Ciel:
                    game->population -= 1000;
                    break;
            }
            house_destroy_one(game->map, &game->houses, game->hud.selected_entity);
        }
        else if (game->hud.selected_entity_type == Tile_Type_Builing) {
            switch (game->hud.selected_entity_variant) {
                case Building_Varient_Water_Tower:
                    game->money -= WATER_TOWER_PRICE/5;
                    water_tower_destroy_one(game->map, &game->water_towers, game->hud.selected_entity);
                    break;
                case Building_Varient_Power_Plant:
                    game->money -= POWER_PLANT_PRICE/5;
                    power_plant_destroy_one(game->map, &game->power_plants, game->hud.selected_entity);
                    break;
            }
        }
        game->hud.selected_entity = NULL;
        game->hud.selected_entity_type = -1;
        game->hud.selected_entity_variant = -1;
    }
}

void update_game(Game_t *game, Vector2 *mouse_pos, Vector2 *screen_size) {

    /// Mise à jour de la souris
    *mouse_pos = GetMousePosition();

    /// Mise a jour de la caméra
    move_camera_with_mouse(&game->camera, *mouse_pos, *screen_size);
    //camera_update(&camera);  // ma version petee

    /// Si on clique sur la minimap
    if(CheckCollisionPointRec(*mouse_pos, game->hud.mini_map) && IsMouseButtonDown(Mouse_Button_Left) && !(game->hud.button_selected == Button_Road || game->hud.button_selected == Button_House || game->hud.button_selected == Button_Water_Tower || game->hud.button_selected == Button_Power_Plant || game->hud.button_selected == Button_Destroy)){
        /// On déplace la caméra sur la position pointée sur la minimap
        move_camera_with_mini_map(&game->camera, game->map, game->hud.mini_map, *mouse_pos);
    }

    UpdateCamera(&game->camera);          // Update camera

    game->mouse_ray = GetMouseRay(*mouse_pos, game->camera);
    game->mouse_ground_collision = GetRayCollisionQuad(game->mouse_ray, game->plateau[0], game->plateau[1], game->plateau[2], game->plateau[3]);
    game->mouse_pos_world = (Vector2) {(int) (game->mouse_ground_collision.point.x / TILES_WIDTH),
                                       (int) (game->mouse_ground_collision.point.z / TILES_WIDTH)};

    if(!game->is_on_pause) {    /// Si on n'est pas en pause alors on update le temps
        update_time(&game->time);
        house_update(game->houses, game->map, &game->population, &game->money, game->time.speed);
    }
    else game->pause_counter++;
}

void event_click_game(Game_t *game, Vector2 mouse_pos) {

    /// Si on est en mode construction
    if(game->hud.button_selected == Button_Destroy || game->hud.button_selected == Button_Road || game->hud.button_selected == Button_House || game->hud.button_selected == Button_Water_Tower || game->hud.button_selected == Button_Power_Plant){

        /// Si on veut pivoter le bâtiment
        if((IsMouseButtonPressed(Mouse_Button_Side_Front) || IsKeyPressed(KEY_Q)) && game->hud.button_selected != Button_Destroy && game->hud.button_selected != Button_Road)
            game->building_orientation = (game->building_orientation + 1) % 4;

        /// Si on veut quitter le mode construction
        else if (IsMouseButtonPressed(Mouse_Button_Right)) {
            game->hud.button_selected = -1;
            game->hud.button_hovered = -1;
        }

        /// Sinon (si on va construire ou détruire un truc)
        else {
            switch (game->hud.button_selected) {
                case Button_Destroy:    /// Destroy mode on
                    if (IsMouseButtonPressed(Mouse_Button_Left) && game->map->tiles[(int)(game->mouse_pos_world.y*game->map->width + game->mouse_pos_world.x)]->type == Tile_Type_House && game->money >= HOUSE_PRICE/5) {
                        switch (((House_t*)game->map->tiles[(int)(game->mouse_pos_world.y*game->map->width + game->mouse_pos_world.x)]->building)->level) {
                            case Cabane:
                                game->population -= 10;
                                break;
                            case Maison:
                                game->population -= 50;
                                break;
                            case Immeuble:
                                game->population -= 100;
                                break;
                            case Gratte_Ciel:
                                game->population -= 1000;
                                break;
                        }
                        house_destroy_one(game->map, &game->houses, game->map->tiles[(int)(game->mouse_pos_world.y*game->map->width + game->mouse_pos_world.x)]->building);
                        game->money -= HOUSE_PRICE/5;
                    }
                    else if (IsMouseButtonPressed(Mouse_Button_Left) && game->map->tiles[(int)(game->mouse_pos_world.y*game->map->width + game->mouse_pos_world.x)]->type == Tile_Type_Builing) {
                        if (game->map->tiles[(int)(game->mouse_pos_world.y*game->map->width + game->mouse_pos_world.x)]->varient == Building_Varient_Water_Tower){
                            game->money -= WATER_TOWER_PRICE/5;
                            water_tower_destroy_one(game->map, &game->water_towers, game->map->tiles[(int)(game->mouse_pos_world.y*game->map->width + game->mouse_pos_world.x)]->building);
                        }
                        else if (game->map->tiles[(int)(game->mouse_pos_world.y*game->map->width + game->mouse_pos_world.x)]->varient == Building_Varient_Power_Plant){
                            game->money -= POWER_PLANT_PRICE/5;
                            power_plant_destroy_one(game->map, &game->power_plants, game->map->tiles[(int)(game->mouse_pos_world.y*game->map->width + game->mouse_pos_world.x)]->building);
                        }
                    }
                    else  destroy_roads(game->map, game->mouse_pos_world, &game->first_road_coord, &game->second_road_coord, &game->last_road_coord, &game->money);
                    break;
                case Button_Road:   /// Road mode on
                    build_roads(game->map, game->mouse_pos_world, &game->first_road_coord, &game->second_road_coord, &game->last_road_coord, &game->money, game->mouse_ground_collision.hit);
                    break;
                case Button_House:    /// House mode on

                    if (IsMouseButtonPressed(Mouse_Button_Left) && is_possible_to_build(game->map, game->mouse_pos_world, Tile_Type_House, game->money, game->building_orientation)) {
                        add_house(game->map, &game->houses, game->mouse_pos_world, game->building_orientation);
                        game->money -= HOUSE_PRICE;
                        if (!IsKeyDown(KEY_LEFT_SHIFT) && !IsKeyDown(KEY_RIGHT_SHIFT))    /// Shift not pressed
                            game->hud.button_selected = Button_Build;
                        else
                            game->hud.button_selected = Button_House;
                        game->hud.button_hovered = -1;
                    }
                    break;

                case Button_Water_Tower:    /// Water tower mode on
                    if (IsMouseButtonPressed(Mouse_Button_Left) && is_possible_to_build(game->map, game->mouse_pos_world, Tile_Type_Builing, game->money, game->building_orientation)) {
                        add_water_tower(game->map, &game->water_towers, game->mouse_pos_world, game->building_orientation);
                        game->money -= WATER_TOWER_PRICE;
                        if (!IsKeyDown(KEY_LEFT_SHIFT) && !IsKeyDown(KEY_RIGHT_SHIFT))    /// Shift not pressed
                            game->hud.button_selected = Button_Build;
                        else
                            game->hud.button_selected = Button_Water_Tower;
                        game->hud.button_hovered = -1;
                    }
                    break;

                case Button_Power_Plant:    /// Power plant mode on
                    if (IsMouseButtonPressed(Mouse_Button_Left) && is_possible_to_build(game->map, game->mouse_pos_world, Tile_Type_Builing, game->money, game->building_orientation)) {
                        add_power_plant(game->map, &game->power_plants, game->mouse_pos_world, game->building_orientation);
                        game->money -= POWER_PLANT_PRICE;
                        if (!IsKeyDown(KEY_LEFT_SHIFT) && !IsKeyDown(KEY_RIGHT_SHIFT))    /// Shift not pressed
                            game->hud.button_selected = Button_Build;
                        else
                            game->hud.button_selected = Button_Power_Plant;
                        game->hud.button_hovered = -1;
                    }
                    break;
            }
        }
    }
    /// Sinon si on n'est pas en mode construction et que la souris est dans le HUD
    else if (is_mouse_on_hud(mouse_pos)){
        game->mouse_pos_world = (Vector2){-1,-1};
        if (game->hud.button_selected==-1) game->hud.button_hovered = get_button_hovered(game->hud.tab_buttons, 5, mouse_pos);
        else if (game->hud.button_selected == Button_Build) game->hud.button_hovered = get_button_hovered(game->hud.tab_buttons, 5, mouse_pos);
        if (IsMouseButtonPressed(Mouse_Button_Left)) {
            switch (game->hud.button_selected) {
                case Button_Build:    /// Build mode on
                    game->hud.button_selected = game->hud.button_hovered;
                    if (game->hud.button_selected == Button_1) {    /// Return button pressed
                        game->hud.button_selected = -1;    /// Build mode off
                    } else if (game->hud.button_selected == Button_2) {    /// Road button pressed
                        game->hud.button_selected = Button_Road;    /// Road mode on
                        game->first_road_coord = (Vector2) {-1, -1};
                        game->second_road_coord = (Vector2) {-1, -1};
                        game->last_road_coord = (Vector2) {-1, -1};
                    } else if (game->hud.button_selected == Button_3) {    /// House button pressed
                        game->hud.button_selected = Button_House;    /// House mode on
                    } else if (game->hud.button_selected == Button_4) {    /// Water tower button pressed
                        game->hud.button_selected = Button_Water_Tower;    /// Water tower mode on
                    } else if (game->hud.button_selected == Button_5) {    /// Power plant button pressed
                        game->hud.button_selected = Button_Power_Plant;    /// Power plant mode on
                    } else game->hud.button_selected = Button_Build;    /// Build mode stays on
                    break;

                default:    /// No mode on, default menu mode
                    game->hud.button_selected = game->hud.button_hovered;
                    if (game->hud.button_selected == Button_2) game->first_road_coord = (Vector2){-1,-1};
                    if (game->hud.button_selected == Button_3) {   /// View button pressed
                        change_view_mode(&game->view_mode);
                        game->hud.button_selected = -1;
                    } else if (game->hud.button_selected == Button_4) {  /// Pause button pressed
                        game->is_on_pause = !game->is_on_pause;
                        game->pause_counter = 0;
                        game->hud.button_selected = -1;
                    } else if (game->hud.button_selected == Button_5) {  /// Speed button pressed
                        change_time_speed(&game->time);
                        game->hud.button_selected = -1;
                    }
                    break;
            }
        }
    }
    else {
        if (IsMouseButtonPressed(Mouse_Button_Left)) {
            printf("\nMouse clicked on the map");
            fflush(stdout);
            switch (game->map->tiles[(int) (game->mouse_pos_world.y*game->map->width + game->mouse_pos_world.x)]->type) {
                case Tile_Type_House:
                    printf("\nHouse clicked");
                    fflush(stdout);
                    game->hud.selected_entity = game->map->tiles[(int) (game->mouse_pos_world.y*game->map->width + game->mouse_pos_world.x)]->building;
                    game->hud.selected_entity_type = Tile_Type_House;
                    game->hud.selected_entity_variant = ((House_t*) game->map->tiles[(int) (game->mouse_pos_world.y*game->map->width + game->mouse_pos_world.x)]->building)->level;
                    break;
                case Tile_Type_Builing:
                    switch (game->map->tiles[(int) (game->mouse_pos_world.y*game->map->width + game->mouse_pos_world.x)]->varient) {
                        case Building_Varient_Water_Tower:
                            game->hud.selected_entity = game->map->tiles[(int) (game->mouse_pos_world.y*game->map->width + game->mouse_pos_world.x)]->building;
                            game->hud.selected_entity_type = Tile_Type_Builing;
                            game->hud.selected_entity_variant = Building_Varient_Water_Tower;
                            break;
                        case Building_Varient_Power_Plant:
                            game->hud.selected_entity = game->map->tiles[(int) (game->mouse_pos_world.y*game->map->width + game->mouse_pos_world.x)]->building;
                            game->hud.selected_entity_type = Tile_Type_Builing;
                            game->hud.selected_entity_variant = Building_Varient_Power_Plant;
                            break;
                    }
                    break;
                case Tile_Type_Road:
                case Tile_Type_Grass:
                    game->hud.selected_entity = NULL;
                    game->hud.selected_entity_type = -1;
                    game->hud.selected_entity_variant = -1;
                    break;
            }
        }
    }
}

void draw_3D_game(Game_t *game) {
    BeginMode3D(game->camera);

    map_draw(game->map, game->road_texture, game->grass_texture, TILES_WIDTH, game->view_mode);

    if (!game->view_mode) {
        house_draw(game->houses, game->house_model);
        water_tower_draw(game->water_towers, 0);
        power_plant_draw(game->power_plants, &game->power_plant_model);
    }

    if (game->hud.button_selected == Button_House && game->mouse_ground_collision.hit) {
        draw_transparent_house(game->map, game->mouse_pos_world, game->money, game->building_orientation, &game->house_model[1]);
    }
    else if (game->hud.button_selected == Button_Water_Tower && game->mouse_ground_collision.hit) {
        draw_transparent_water_tower(game->map, game->mouse_pos_world, game->money, game->building_orientation, 0);
    }
    else if (game->hud.button_selected == Button_Power_Plant && game->mouse_ground_collision.hit) {
        draw_transparent_power_plant(game->map, game->mouse_pos_world, game->money, game->building_orientation, &game->power_plant_model);
    }

    EndMode3D();
}

void draw_2D_game(Game_t *game, Vector2 screen_size, Vector2 mouse_pos) {
    int draw_x = (screen_size.x - 60)/5;

    DrawRectangle(10, 10, draw_x, 50, Fade(GREEN, 0.5f));
    DrawRectangleLines(10, 10, draw_x, 50, GREEN);
    DrawText(TextFormat("Money : $%d", game->money), 20, 20, 30, BLACK);

    DrawRectangle(20 + draw_x, 10, draw_x, 50, Fade(BLUE, 0.5f));
    DrawRectangleLines(20 + draw_x, 10, draw_x, 50, DARKBLUE);
    DrawText(TextFormat("Water : %d/%d", game->map->water_tower_count*WATER_TOWER_CAPACITY, game->map->water_tower_count*WATER_TOWER_CAPACITY), 30 + draw_x, 20, 30, BLACK);

    DrawRectangle(30 + 2*draw_x, 10, draw_x, 50, Fade(YELLOW, 0.5f));
    DrawRectangleLines(30 + 2*draw_x, 10, draw_x, 50, GOLD);
    DrawText(TextFormat("Power : %d/%d", game->map->power_plant_count*POWER_PLANT_CAPACITY, game->map->power_plant_count*POWER_PLANT_CAPACITY), 40 + draw_x*2, 20, 30, BLACK);

    DrawRectangle(40 + 3*draw_x, 10, draw_x, 50, Fade(VIOLET, 0.5f));
    DrawRectangleLines(40 + 3*draw_x, 10, draw_x, 50, DARKPURPLE);
    DrawText(TextFormat("People : %d", game->population), 50 + draw_x*3, 20, 30, BLACK);

    print_time((Vector2) {screen_size.x - draw_x - 10, 10}, (Vector2){draw_x, 50}, &game->time);

    DrawText(TextFormat("FPS : %d\nTime speed : x%d\nCounter : %d", GetFPS(), game->time.speed, game->time.counter), 10, 100, 10, BLACK);

    if(game->hud.button_selected == Button_Destroy || game->hud.button_selected == Button_Road || game->hud.button_selected == Button_House || game->hud.button_selected == Button_Water_Tower || game->hud.button_selected == Button_Power_Plant) {
        DrawRectangle((screen_size.x - MeasureText("Right click to disable", 20))/2 - 10, screen_size.y/16, MeasureText("Right click to disable", 20) + 20, 70, Fade(GRAY, 0.5f));
        DrawRectangleLines((screen_size.x - MeasureText("Right click to disable", 20))/2 - 10, screen_size.y/16, MeasureText("Right click to disable", 20) + 20, 70, Fade(DARKGRAY, 0.5f));
        DrawText("Build mode active", (GetScreenWidth()-MeasureText("Build mode active", 20))/2, screen_size.y/16 + 5, 20, Fade(BLACK, 0.5f));
        DrawText("Right click to disable", (GetScreenWidth()-MeasureText("Right click to disable", 20))/2, screen_size.y/16 + 25, 20, Fade(BLACK, 0.5f));
        DrawText("Shift to keep active", (GetScreenWidth()-MeasureText("Shift to keep active", 20))/2, screen_size.y/16 + 45, 20, Fade(BLACK, 0.5f));
    }

    else {
        if(game->hud.selected_entity) draw_selected_entity_info(game->hud.selected_entity, game->hud.selected_entity_type, game->hud.selected_entity_variant, screen_size);
        draw_hud(game->hud.hud_textures, game->hud.tab_buttons, mouse_pos, screen_size, game->hud.button_selected, game->view_mode, game->is_on_pause, game->time.speed);
        draw_minimap(game->map, game->hud.mini_map, (Vector2){game->camera.position.x, game->camera.position.z}, (Vector2){game->camera.target.x, game->camera.target.z}, game->view_mode);
        if (game->hud.button_hovered != -1) draw_button_description(mouse_pos, game->hud.button_selected, game->hud.button_hovered);
    }

    if (game->is_on_pause)
        DrawText("PAUSE", screen_size.x / 2 - MeasureText("PAUSE", 40) / 2, screen_size.y / 2 - 20, 50, Fade(WHITE, fabs(cos(game->pause_counter*PAUSE_BLINK_RATIO))));

}

void destroy_game(Game_t **game) {
    house_destroy(&(*game)->houses);
    water_tower_destroy(&(*game)->water_towers);
    power_plant_destroy(&(*game)->power_plants);
    map_destroy(&(*game)->map);
    UnloadModel((*game)->house_model[0]);
    UnloadModel((*game)->house_model[1]);
    UnloadModel((*game)->house_model[2]);
    UnloadModel((*game)->house_model[3]);
    UnloadModel((*game)->water_tower_model);
    UnloadModel((*game)->power_plant_model);
    UnloadTexture((*game)->road_texture);
    free(*game);
}