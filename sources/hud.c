//
// Created by eleuc on 07/11/2022.
//

#include "../includes/hud.h"

void draw_minimap(Map_t *map, Vector2 screen_size, int view_mode){
    int minimap_width = (int)(screen_size.y * MINI_MAP_MAX_WIDTH_RATIO);
    int minimap_height = (int)(screen_size.y * MINI_MAP_MAX_HEIGHT_RATIO);
    int minimap_x = (int)(screen_size.x - minimap_width - 20);
    int minimap_y = (int)(screen_size.y - minimap_height - 20);
    if (minimap_width > minimap_height){
        minimap_width = minimap_height;
    } else {
        minimap_height = minimap_width;
    }
    for (int y = 0; y < map->height; ++y) {
        for (int x = 0; x < map->width; ++x) {
            if (map->tiles[y*map->width + x]->type == Tile_Type_Grass){
                DrawRectangle(x * minimap_width / map->width + minimap_x, y * minimap_height / map->height + minimap_y, minimap_width / map->width, minimap_height / map->height, GREEN);
            }
            else if (map->tiles[y*map->width + x]->type == Tile_Type_Road){
                DrawRectangle(x * minimap_width / map->width + minimap_x, y * minimap_height / map->height + minimap_y, minimap_width / map->width, minimap_height / map->height, GRAY);
            }
            else if (map->tiles[y*map->width + x]->type == Tile_Type_House){
                DrawRectangle(x * minimap_width / map->width + minimap_x, y * minimap_height / map->height + minimap_y, minimap_width / map->width, minimap_height / map->height, BROWN);
            }
            else if (map->tiles[y*map->width + x]->type == Tile_Type_Builing) {
                if (map->tiles[y*map->width + x]->varient == Building_Varient_Water_Tower) {
                    DrawRectangle(x * minimap_width / map->width + minimap_x, y * minimap_height / map->height + minimap_y, minimap_width / map->width, minimap_height / map->height, BLUE);
                }
                else if (map->tiles[y*map->width + x]->varient == Building_Varient_Power_Plant) {
                    DrawRectangle(x * minimap_width / map->width + minimap_x, y * minimap_height / map->height + minimap_y, minimap_width / map->width, minimap_height / map->height, YELLOW);
                }
            }

        }
    }
}

void draw_hud(Texture2D hud_textures, Rectangle *tab_button_icon_rec, Vector2 mouse_pos, Vector2 scren_size, HUD_BUTTONS button_pressed, int view_mode, bool is_paused, int speed){
    Color speed_colors[4] = {SKYBLUE, GREEN, YELLOW, RED};
    int speed_color = speed;
    if(speed_color == 5) speed_color = 3;
    else if(speed_color == 10) speed_color = 4;
    DrawRectangle(0, scren_size.y*(1.0 - HUD_HEIGHT_RATIO), scren_size.x, scren_size.y*HUD_HEIGHT_RATIO, Fade(BLACK, 0.5f));
    DrawRectangleLines(0, scren_size.y*3.0f/4.0f, scren_size.x, scren_size.y*HUD_HEIGHT_RATIO, BLACK);

    if(button_pressed == Button_Build || button_pressed == Button_Road || button_pressed == Button_House || button_pressed == Button_Water_Tower || button_pressed == Button_Power_Plant){  /// Si on est en mode construction
        for (int i = Button_Back; i < Button_Power_Plant+1; i++) {
            DrawTextureRec(hud_textures, (Rectangle){0, i * hud_textures.height / Nb_Hud_Buttons, hud_textures.width, hud_textures.height / Nb_Hud_Buttons}, (Vector2) {tab_button_icon_rec[i - Button_Back].x, tab_button_icon_rec[i - Button_Back].y}, (CheckCollisionPointRec(mouse_pos, tab_button_icon_rec[i - Button_Back]) || i == button_pressed) ? GRAY : WHITE);
        }
    }
    else{
        /// Dessin du bouton de construction
        DrawTextureRec(hud_textures, (Rectangle){0, 0, hud_textures.width, hud_textures.height / Nb_Hud_Buttons}, (Vector2) {tab_button_icon_rec[Button_1].x, tab_button_icon_rec[Button_1].y}, (CheckCollisionPointRec(mouse_pos, tab_button_icon_rec[Button_Build]) ? GRAY : WHITE));
        /// Dessin du bouton de destruction
        DrawTextureRec(hud_textures, (Rectangle){0, hud_textures.height / Nb_Hud_Buttons, hud_textures.width, hud_textures.height / Nb_Hud_Buttons}, (Vector2) {tab_button_icon_rec[Button_2].x, tab_button_icon_rec[Button_2].y}, (CheckCollisionPointRec(mouse_pos, tab_button_icon_rec[Button_Destroy]) || button_pressed == Button_Destroy) ? GRAY : WHITE);
        /// Dessin du bouton de vue
        DrawTextureRec(hud_textures, (Rectangle){0, (Button_View_Normal + view_mode) * hud_textures.height / Nb_Hud_Buttons, hud_textures.width, hud_textures.height / Nb_Hud_Buttons}, (Vector2) {tab_button_icon_rec[Button_3].x, tab_button_icon_rec[Button_3].y}, (CheckCollisionPointRec(mouse_pos, tab_button_icon_rec[Button_View_Normal]) ? GRAY : WHITE));
        /// Dessin du bouton de pause
        DrawTextureRec(hud_textures, (Rectangle){0, (Button_Pause + is_paused) * hud_textures.height / Nb_Hud_Buttons, hud_textures.width, hud_textures.height / Nb_Hud_Buttons}, (Vector2) {tab_button_icon_rec[Button_4].x, tab_button_icon_rec[Button_4].y}, (CheckCollisionPointRec(mouse_pos, tab_button_icon_rec[Button_View_Water]) ? GRAY : WHITE));
        /// Dessin du bouton de vitesse
        DrawRectangle(tab_button_icon_rec[Button_5].x, tab_button_icon_rec[Button_5].y, tab_button_icon_rec[Button_5].width, tab_button_icon_rec[Button_5].height, speed_colors[speed_color-1]);
        DrawText(TextFormat("x%d", speed), tab_button_icon_rec[Button_5].x + tab_button_icon_rec[Button_5].width/2 - MeasureText(TextFormat("x%d", speed), 50)/2, tab_button_icon_rec[Button_5].y + tab_button_icon_rec[Button_5].height/2 - 50/2, 50, BLACK);
        if(CheckCollisionPointRec(mouse_pos, tab_button_icon_rec[Button_5])) DrawRectangle(tab_button_icon_rec[Button_5].x, tab_button_icon_rec[Button_5].y, tab_button_icon_rec[Button_5].width, tab_button_icon_rec[Button_5].height,Fade(DARKGRAY, 0.5f));
    }
}

void draw_button_description(Vector2 mouse_pos, int button_pressed, int button_hovered){
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
                DrawRectangle(mouse_pos.x + 10, mouse_pos.y - 10, MeasureText("Change view mode\nShortcut : CTRL + V", 20) + 20, 60, Fade(GRAY, 0.8f));
                DrawRectangleLines(mouse_pos.x + 10, mouse_pos.y - 10, MeasureText("Change view mode\nShortcut : CTRL + V", 20) + 20, 60, Fade(DARKGRAY, 0.8f));
                DrawText("Change view mode\nShortcut : CTRL + V", mouse_pos.x + 20, mouse_pos.y - 5, 20, Fade(BLACK, 0.8f));
                break;
            case Button_4:
                /// Draw a rectangle with description of the pause button next to mouse
                DrawRectangle(mouse_pos.x + 10, mouse_pos.y - 10, MeasureText("Pause and resume time\nShortcut : CTRL + P", 20) + 20, 60, Fade(GRAY, 0.8f));
                DrawRectangleLines(mouse_pos.x + 10, mouse_pos.y - 10, MeasureText("Pause and resume time\nShortcut : CTRL + P", 20) + 20, 60, Fade(DARKGRAY, 0.8f));
                DrawText("Pause and resume time\nShortcut : CTRL + P", mouse_pos.x + 20, mouse_pos.y - 5, 20, Fade(BLACK, 0.8f));
                break;
            case Button_5:
                /// Draw a rectangle with description of the time speed button next to mouse
                DrawRectangle(mouse_pos.x + 10, mouse_pos.y - 10, MeasureText("Change time speed\nShortcut : CTRL + T", 20) + 20, 60, Fade(GRAY, 0.8f));
                DrawRectangleLines(mouse_pos.x + 10, mouse_pos.y - 10, MeasureText("Change time speed\nShortcut : CTRL + T", 20) + 20, 60, Fade(DARKGRAY, 0.8f));
                DrawText("Change time speed\nShortcut : CTRL + T", mouse_pos.x + 20, mouse_pos.y - 5, 20, Fade(BLACK, 0.8f));
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

void change_view_mode(int *view_mode){
    *view_mode = (*view_mode + 1) % 3;
}

bool is_mouse_on_hud(Vector2 mouse_position){
    if (mouse_position.y > (float)GetScreenHeight() * (1.0f - HUD_HEIGHT_RATIO)){
        return true;
    }
    return false;
}

