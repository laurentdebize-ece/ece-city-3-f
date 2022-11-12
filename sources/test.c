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
    //SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetConfigFlags(FLAG_FULLSCREEN_MODE);
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

    int screen_width = GetScreenWidth();
    int screen_height = GetScreenHeight();

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
        }


        /*---------------------------------------UPDATE---------------------------------------*/

        if (IsWindowResized()){ /// Ca pue la merde
            screen_width = GetScreenWidth();
            screen_height = GetScreenHeight();
            for (int i = 0; i < 5; ++i) {
                tab_button_icon_rec[i].y = screen_height*(1.0f - HUD_HEIGHT_RATIO) + (float)(screen_height*HUD_HEIGHT_RATIO - hud_icons.height / Nb_Hud_Buttons) / 2.0f;
            }
        }

        /// Mise à jour de la souris
        mouse_pos = GetMousePosition();

        move_camera_with_mouse(&camera, mouse_pos);
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

        if(button_pressed == Button_Road || button_pressed == Button_House){
            if (IsMouseButtonPressed(Mouse_Button_Right)) button_pressed = Button_Build;
            else {
                switch (button_pressed) {
                    case Button_Road:
                        if (IsMouseButtonPressed(Mouse_Button_Left) && mouse_pos_world.x >= 0 && mouse_pos_world.x < map->width && mouse_pos_world.y >= 0 && mouse_pos_world.y < map->height) {
                            first_road_coord = mouse_pos_world;
                            second_road_coord = mouse_pos_world;
                            last_road_coord = mouse_pos_world;
                        }
                        else if (IsMouseButtonDown(Mouse_Button_Left)) {
                            if (vec2D_sub(first_road_coord, second_road_coord).x == 0 &&
                                vec2D_sub(first_road_coord, second_road_coord).y == 0) {
                                second_road_coord = mouse_pos_world;
                            } else if (vec2D_sub(first_road_coord, second_road_coord).x) last_road_coord.x = mouse_pos_world.x;
                            else last_road_coord.y = mouse_pos_world.y;
                        } else if (IsMouseButtonReleased(Mouse_Button_Left)) {
                            if (mouse_ground_collision.hit && (vec2D_sub(first_road_coord, second_road_coord).x != 0 ||
                                                               vec2D_sub(first_road_coord, second_road_coord).y != 0)) {
                                money -= 10 * build_line_of_road(map, first_road_coord, last_road_coord);
                            }
                        } else if (IsMouseButtonReleased(Mouse_Button_Left) && first_road_coord.x == last_road_coord.x && first_road_coord.y == last_road_coord.y) {
                            if (is_possible_to_build(map, first_road_coord, Tile_Type_Road, money)) {
                                build_one_road(map, first_road_coord);
                                money -= 10;
                            }
                        }
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

        EndMode3D();

        DrawRectangle(10, 10, 350, 50, Fade(GREEN, 0.5f));
        DrawRectangleLines(10, 10, 350, 50, GREEN);
        DrawText(TextFormat("Money : $%d", money), 20, 20, 30, BLACK);

        print_time((Vector2) {WIDTH - 310, 10}, &time);

        DrawText(TextFormat("FPS : %d\nTime speed : x%d\nCounter : %d", GetFPS(), time.speed, time.counter), 10, 100, 10, BLACK);

        if(button_pressed == Button_Road || button_pressed == Button_House) {
            DrawRectangle((screen_width - MeasureText("Right click to disable", 20))/2 - 10, screen_height/16, MeasureText("Right click to disable", 20) + 20, 50, Fade(GRAY, 0.5f));
            DrawRectangleLines((screen_width - MeasureText("Right click to disable", 20))/2 - 10, screen_height/16, MeasureText("Right click to disable", 20) + 20, 50, Fade(DARKGRAY, 0.5f));
            DrawText("Build mode active", (GetScreenWidth()-MeasureText("Build mode active", 20))/2, screen_height/16 + 5, 20, Fade(BLACK, 0.5f));
            DrawText("Right click to disable", (GetScreenWidth()-MeasureText("Right click to disable", 20))/2, screen_height/16 + 25, 20, Fade(BLACK, 0.5f));
        }

        else {
            draw_hud(hud_icons, tab_button_icon_rec, mouse_pos, button_pressed, view_mode, is_on_pause, time.speed);
            if(button_pressed == -1) {  /// No mode on
                switch (button_hovered) {
                    case Button_1:
                        /// Draw a rectangle with description of the build button next to mouse
                        DrawRectangle(mouse_pos.x + 10, mouse_pos.y - 10, MeasureText("Build things like roads, houses...", 20) + 20, 30, Fade(GRAY, 0.8f));
                        DrawRectangleLines(mouse_pos.x + 10, mouse_pos.y - 10, MeasureText("Build things like roads, houses...", 20) + 20, 30, Fade(DARKGRAY, 0.8f));
                        DrawText("Build things like roads, houses...", mouse_pos.x + 20, mouse_pos.y - 5, 20, Fade(BLACK, 0.8f));
                        break;
                    case Button_2:
                        /// Draw a rectangle with description of the destroy button next to mouse
                        DrawRectangle(mouse_pos.x + 10, mouse_pos.y - 10, MeasureText("Destroy things like roads, houses...", 20) + 20, 30, Fade(GRAY, 0.8f));
                        DrawRectangleLines(mouse_pos.x + 10, mouse_pos.y - 10, MeasureText("Destroy things like roads, houses...", 20) + 20, 30, Fade(DARKGRAY, 0.8f));
                        DrawText("Destroy things like roads, houses...", mouse_pos.x + 20, mouse_pos.y - 5, 20, Fade(BLACK, 0.8f));
                        break;
                    case Button_3:
                        /// Draw a rectangle with description of the view button next to mouse
                        DrawRectangle(mouse_pos.x + 10, mouse_pos.y - 10, MeasureText("Change view mode", 20) + 20, 30, Fade(GRAY, 0.8f));
                        DrawRectangleLines(mouse_pos.x + 10, mouse_pos.y - 10, MeasureText("Change view mode", 20) + 20, 30, Fade(DARKGRAY, 0.8f));
                        DrawText("Change view mode", mouse_pos.x + 20, mouse_pos.y - 5, 20, Fade(BLACK, 0.8f));
                        break;
                    case Button_4:
                        /// Draw a rectangle with description of the pause button next to mouse
                        DrawRectangle(mouse_pos.x + 10, mouse_pos.y - 10, MeasureText("Pause and resume time", 20) + 20, 30, Fade(GRAY, 0.8f));
                        DrawRectangleLines(mouse_pos.x + 10, mouse_pos.y - 10, MeasureText("Pause and resume time", 20) + 20, 30, Fade(DARKGRAY, 0.8f));
                        DrawText("Pause and resume time", mouse_pos.x + 20, mouse_pos.y - 5, 20, Fade(BLACK, 0.8f));
                        break;
                    case Button_5:
                        /// Draw a rectangle with description of the time speed button next to mouse
                        DrawRectangle(mouse_pos.x + 10, mouse_pos.y - 10, MeasureText("Change time speed", 20) + 20, 30, Fade(GRAY, 0.8f));
                        DrawRectangleLines(mouse_pos.x + 10, mouse_pos.y - 10, MeasureText("Change time speed", 20) + 20, 30, Fade(DARKGRAY, 0.8f));
                        DrawText("Change time speed", mouse_pos.x + 20, mouse_pos.y - 5, 20, Fade(BLACK, 0.8f));
                        break;
                }
            }
            else if(button_pressed == Button_Build) {
                switch (button_hovered) {
                    case Button_1:
                        /// Draw a rectangle with description of the return button next to mouse
                        DrawRectangle(mouse_pos.x + 10, mouse_pos.y - 10, MeasureText("Return to main menu", 20) + 20, 30, Fade(GRAY, 0.8f));
                        DrawRectangleLines(mouse_pos.x + 10, mouse_pos.y - 10, MeasureText("Return to main menu", 20) + 20, 30, Fade(DARKGRAY, 0.8f));
                        DrawText("Return to main menu", mouse_pos.x + 20, mouse_pos.y - 5, 20, Fade(BLACK, 0.8f));
                        break;
                    case Button_2:
                        /// Draw a rectangle with description of the road button next to mouse
                        DrawRectangle(mouse_pos.x + 10, mouse_pos.y - 10, MeasureText("Build roads", 20) + 20, 30, Fade(GRAY, 0.8f));
                        DrawRectangleLines(mouse_pos.x + 10, mouse_pos.y - 10, MeasureText("Build roads", 20) + 20, 30, Fade(DARKGRAY, 0.8f));
                        DrawText("Build roads", mouse_pos.x + 20, mouse_pos.y - 5, 20, Fade(BLACK, 0.8f));
                        break;
                    case Button_3:
                        /// Draw a rectangle with description of the house button next to mouse
                        DrawRectangle(mouse_pos.x + 10, mouse_pos.y - 10, MeasureText("Build houses", 20) + 20, 30, Fade(GRAY, 0.8f));
                        DrawRectangleLines(mouse_pos.x + 10, mouse_pos.y - 10, MeasureText("Build houses", 20) + 20, 30, Fade(DARKGRAY, 0.8f));
                        DrawText("Build houses", mouse_pos.x + 20, mouse_pos.y - 5, 20, Fade(BLACK, 0.8f));
                        break;
                    case Button_4:
                        /// Draw a rectangle with description of the water tower button next to mouse
                        DrawRectangle(mouse_pos.x + 10, mouse_pos.y - 10, MeasureText("Build a water tower", 20) + 20, 30, Fade(GRAY, 0.8f));
                        DrawRectangleLines(mouse_pos.x + 10, mouse_pos.y - 10, MeasureText("Build a water tower", 20) + 20, 30, Fade(DARKGRAY, 0.8f));
                        DrawText("Build a water tower", mouse_pos.x + 20, mouse_pos.y - 5, 20, Fade(BLACK, 0.8f));
                        break;
                    case Button_5:
                        /// Draw a rectangle with description of the power plant button next to mouse
                        DrawRectangle(mouse_pos.x + 10, mouse_pos.y - 10, MeasureText("Build a power plant", 20) + 20, 30, Fade(GRAY, 0.8f));
                        DrawRectangleLines(mouse_pos.x + 10, mouse_pos.y - 10, MeasureText("Build a power plant", 20) + 20, 30, Fade(DARKGRAY, 0.8f));
                        DrawText("Build a power plant", mouse_pos.x + 20, mouse_pos.y - 5, 20, Fade(BLACK, 0.8f));
                        break;
                }
            }

        }

        if (is_on_pause) {
            pause_counter++;
            DrawText("PAUSE", WIDTH / 2 - MeasureText("PAUSE", 40) / 2, HEIGHT / 2 - 20, 50, Fade(WHITE, fabs(cos(pause_counter*PAUSE_BLINK_RATIO))));
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