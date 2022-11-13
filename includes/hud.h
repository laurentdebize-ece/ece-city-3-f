//
// Created by eleuc on 07/11/2022.
//

#ifndef PROJET_HUD_H
#define PROJET_HUD_H

#define HUD_WIDTH_RATIO (1.0f/1.0f)
#define HUD_HEIGHT_RATIO (1.0f/4.0f)
#define MINI_MAP_MAX_WIDTH_RATIO (1.0f/4.0f)
#define MINI_MAP_MAX_HEIGHT_RATIO (1.0f/4.0f) - 40
#define PAUSE_BLINK_RATIO (1.0f/20.0f)
#define MAX_HUD_BUTTONS 5

#include <raylib.h>
#include "map/map_draw.h"

typedef enum {
    Button_Build,
    Button_Destroy,
    Button_View_Normal,
    Button_View_Water,
    Button_View_Electricity,
    Button_Pause,
    Button_Play,
    Button_Back,
    Button_Road,
    Button_House,
    Button_Water_Tower,
    Button_Power_Plant,
    Nb_Hud_Buttons
}HUD_BUTTONS;

typedef enum {
    Button_1,
    Button_2,
    Button_3,
    Button_4,
    Button_5,
    Button_6,
    Nb_Hud_Button_Positions
}HUD_BUTTON_POSITIONS;

void draw_minimap(Map_t *map, Vector2 screen_size, int view_mode);

void draw_hud(Texture2D hud_textures, Rectangle *tab_buttons_rec, Vector2 mouse_position, Vector2 screen_size, HUD_BUTTONS button_pressed, int view_mode, bool is_paused, int speed);

void draw_button_description(Vector2 mouse_pos, int button_pressed, int button_hovered);

void change_view_mode(int *view_mode);

bool is_mouse_on_hud(Vector2 mouse_position);

#endif //PROJET_HUD_H
