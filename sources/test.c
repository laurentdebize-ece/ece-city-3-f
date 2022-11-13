//
// Created by eleuc on 25/10/2022.
//

#include "../includes/test.h"

void test() {

    /// Création de la map
    Map_t *map = load_map(DEFAULT_MAP_FILE_PATH);
    House_t *house = NULL;

    /// Affichage de la map en console
    print_map_console(map);

    /// Ouverture de la fenêtre
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    //SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(WIDTH, HEIGHT, TITLE);

    /// Chargement des modèles 3D et de leur texture
    //Model cabane_model = LoadModel("../assets/map/models/cabane.obj");
    //Texture2D texture = LoadTexture("../assets/map/models/cabane.png");
    //cabane_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

    /// Création de la caméra
    Camera3D camera = camera_new(map);

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

    SetCameraMode(camera, CAMERA_FREE); // Set a free camera mode

    Texture2D hud_icons = LoadTexture("../assets/bitmaps/hud/hud_icons.png");
    Texture2D road_texture = LoadTexture("../assets/map/roads/road_texture.png");

    Rectangle tab_button_icon_rec[Nb_Hud_Buttons] = {
            (Rectangle){WIDTH/20.0f,  HEIGHT*(1.0f - HUD_HEIGHT_RATIO) + (float)(HEIGHT*HUD_HEIGHT_RATIO - hud_icons.height / Nb_Hud_Buttons) / 2.0f, hud_icons.width, hud_icons.height / Nb_Hud_Buttons},
            (Rectangle){WIDTH*2/20.f, HEIGHT*(1.0f - HUD_HEIGHT_RATIO) + (float)(HEIGHT*HUD_HEIGHT_RATIO - hud_icons.height / Nb_Hud_Buttons) / 2.0f, hud_icons.width, hud_icons.height / Nb_Hud_Buttons},
            (Rectangle){WIDTH*3/20.f, HEIGHT*(1.0f - HUD_HEIGHT_RATIO) + (float)(HEIGHT*HUD_HEIGHT_RATIO - hud_icons.height / Nb_Hud_Buttons) / 2.0f, hud_icons.width, hud_icons.height / Nb_Hud_Buttons},
            (Rectangle){WIDTH*4/20.f, HEIGHT*(1.0f - HUD_HEIGHT_RATIO) + (float)(HEIGHT*HUD_HEIGHT_RATIO - hud_icons.height / Nb_Hud_Buttons) / 2.0f, hud_icons.width, hud_icons.height / Nb_Hud_Buttons},
            (Rectangle){WIDTH*5/20.f, HEIGHT*(1.0f - HUD_HEIGHT_RATIO) + (float)(HEIGHT*HUD_HEIGHT_RATIO - hud_icons.height / Nb_Hud_Buttons) / 2.0f, hud_icons.width, hud_icons.height / Nb_Hud_Buttons},
    };

    int view_mode = 0;

    Time_t time = {1,0,0,0,0,3,2069};
    int money = 500000;

    SetTargetFPS(FPS);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    int button_pressed = -1, button_pressed_last = -1, button_hovered = -1, button_hovered_last = -1;

    bool is_on_pause = false;
    int pause_counter = 0;

    Vector2 screen_size = {GetScreenWidth(), GetScreenHeight()};

    // Main game loop
    while (!should_window_be_closed())        /// Est-ce qu'on ferme la fenêtre ?
    {

        /*---------------------------------------COMMANDES CLAVIER---------------------------------------*/
        /// Commandes clavier
        if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL)) {

            if (IsKeyPressed(KEY_S)) {  /// Sauvegarde de la map
                //save_map(map, DEFAULT_MAP_FILE_PATH);
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
                camera = camera_new(map);
            }
        }


        /*---------------------------------------UPDATE---------------------------------------*/

        if (IsWindowResized()){ /// Ca pue la merde
            screen_size = get_screen_size();
            for (int i = 0; i < 5; ++i) {
                tab_button_icon_rec[i].y = screen_size.x*(1.0f - HUD_HEIGHT_RATIO) + (float)(screen_size.y*HUD_HEIGHT_RATIO - hud_icons.height / Nb_Hud_Buttons) / 2.0f;
            }
        }

        /// Mise à jour de la souris
        mouse_pos = GetMousePosition();

        move_camera_with_mouse(&camera, mouse_pos, screen_size);
        //camera_update(&camera);  // ma version petee

        UpdateCamera(&camera);          // Update camera

        mouse_ray = GetMouseRay(mouse_pos, camera);
        RayCollision mouse_ground_collision = GetRayCollisionQuad(mouse_ray, g0, g1, g2, g3);
        mouse_pos_world = (Vector2) {(int) (mouse_ground_collision.point.x / TILES_WIDTH),
                                     (int) (mouse_ground_collision.point.z / TILES_WIDTH)};

        if(!pause_counter) {    /// Si on n'est pas en pause alors on update le temps
            update_time(&time);
            house_update(house, map, &money, time.speed);
        }

        /*---------------------------------------CLICK EVENT REACTION---------------------------------------*/

        if(button_pressed == Button_Road || button_pressed == Button_House || button_pressed == Button_Water_Tower || button_pressed == Button_Power_Plant){    /// Si on a cliqué sur un bouton de construction
            if (IsMouseButtonPressed(Mouse_Button_Right)) {
                button_pressed = Button_Build;
                button_hovered = -1;
            }
            else {
                switch (button_pressed) {
                    case Button_Road:
                        build_roads(map, mouse_pos_world, &first_road_coord, &second_road_coord, &last_road_coord, &money, mouse_ground_collision.hit);
                        break;
                    case Button_House:    /// House mode on

                        if (IsMouseButtonPressed(Mouse_Button_Left) && is_possible_to_build(map, mouse_pos_world, Tile_Type_House, money)) {
                            add_house(map, &house, mouse_pos_world);
                            money -= HOUSE_PRICE;
                            if (!IsKeyDown(KEY_LEFT_SHIFT) && !IsKeyDown(KEY_RIGHT_SHIFT))    /// Shift not pressed
                                button_pressed = Button_Build;

                        }
                        break;
                }
            }
        }
        else if (is_mouse_on_hud(mouse_pos)){
            if (button_pressed==-1) button_hovered = get_button_hovered(tab_button_icon_rec, 5, mouse_pos);
            else if (button_pressed == Button_Build) button_hovered = get_button_hovered(tab_button_icon_rec, 5, mouse_pos);
            if (IsMouseButtonPressed(Mouse_Button_Left)) {
                switch (button_pressed) {
                    case Button_Build:    /// Build mode on
                        button_pressed = button_hovered;
                        if (button_pressed == Button_1) {    /// Return button pressed
                            button_pressed = -1;    /// Build mode off
                        } else if (button_pressed == Button_2) {    /// Road button pressed
                            button_pressed = Button_Road;    /// Road mode on
                            first_road_coord = (Vector2) {-1, -1};
                            second_road_coord = (Vector2) {-1, -1};
                            last_road_coord = (Vector2) {-1, -1};
                        } else if (button_pressed == Button_3) {    /// House button pressed
                            button_pressed = Button_House;    /// House mode on
                        } else button_pressed = Button_Build;    /// Build mode stays on
                        break;
                    case Button_Destroy:    /// Destroy mode on
                        button_pressed = button_hovered;
                        if (button_pressed == Button_2) {    /// Destroy button pressed
                            button_pressed = -1;    /// Destroy mode off
                        } else if (button_pressed == Button_1) {  /// Build button pressed
                            button_pressed = Button_Build;    /// Destroy mode off
                        } else if (button_pressed == Button_3) {  /// House button pressed
                            view_mode = (view_mode + 1) % 3;    /// House mode on
                            button_pressed = Button_Destroy;    /// Destroy mode stays on
                        } else button_pressed = Button_Destroy;    /// Destroy mode stays on
                        break;

                    default:    /// No mode on, default menu mode
                        button_pressed = button_hovered;
                        if (button_pressed == Button_3) {   /// View button pressed
                            change_view_mode(&view_mode);
                            button_pressed = -1;
                        } else if (button_pressed == Button_4) {  /// Pause button pressed
                            is_on_pause = !is_on_pause;
                            pause_counter = 0;
                            button_pressed = -1;
                        } else if (button_pressed == Button_5) {  /// Speed button pressed
                            change_time_speed(&time);
                            button_pressed = -1;
                        }
                        break;
                }
            }
        }

        /*---------------------------------------DRAWING---------------------------------------*/

        BeginDrawing();

        ClearBackground(SKYBLUE); // Clear background to sky blue

        BeginMode3D(camera);

        map_draw(map, road_texture, TILES_WIDTH, view_mode);

        if (!view_mode) house_draw(house);

        if (button_pressed == Button_House && mouse_ground_collision.hit) {
            draw_transparent_house(map, mouse_pos_world, money);
        }

        EndMode3D();

        DrawRectangle(10, 10, 350, 50, Fade(GREEN, 0.5f));
        DrawRectangleLines(10, 10, 350, 50, GREEN);
        DrawText(TextFormat("Money : $%d", money), 20, 20, 30, BLACK);

        print_time((Vector2) {screen_size.x - 310, 10}, &time);

        DrawText(TextFormat("FPS : %d\nTime speed : x%d\nCounter : %d", GetFPS(), time.speed, time.counter), 10, 100, 10, BLACK);

        if(button_pressed == Button_Road || button_pressed == Button_House) {
            DrawRectangle((screen_size.x - MeasureText("Right click to disable", 20))/2 - 10, screen_size.y/16, MeasureText("Right click to disable", 20) + 20, 50, Fade(GRAY, 0.5f));
            DrawRectangleLines((screen_size.x - MeasureText("Right click to disable", 20))/2 - 10, screen_size.y/16, MeasureText("Right click to disable", 20) + 20, 50, Fade(DARKGRAY, 0.5f));
            DrawText("Build mode active", (GetScreenWidth()-MeasureText("Build mode active", 20))/2, screen_size.y/16 + 5, 20, Fade(BLACK, 0.5f));
            DrawText("Right click to disable", (GetScreenWidth()-MeasureText("Right click to disable", 20))/2, screen_size.y/16 + 25, 20, Fade(BLACK, 0.5f));
        }

        else {
            draw_hud(hud_icons, tab_button_icon_rec, mouse_pos, screen_size, button_pressed, view_mode, is_on_pause, time.speed);
            draw_minimap(map, screen_size, view_mode);
            if (button_hovered != -1) draw_button_description(mouse_pos, button_pressed, button_hovered);
        }

        if (is_on_pause) {
            pause_counter++;
            DrawText("PAUSE", screen_size.x / 2 - MeasureText("PAUSE", 40) / 2, screen_size.y / 2 - 20, 50, Fade(WHITE, fabs(cos(pause_counter*PAUSE_BLINK_RATIO))));
        }

        EndDrawing();

        /*---------------------------------------FIN DE BOUCLE---------------------------------------*/
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    map_destroy(&map);
    house_destroy(&house);
}