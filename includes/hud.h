//
// Created by eleuc on 07/11/2022.
//

#ifndef PROJET_HUD_H
#define PROJET_HUD_H

#include <raylib.h>

typedef enum {
    Button_Build,
    Button_Destroy,
    Nb_Hud_Buttons
}HUD_BUTTONS;

void draw_hud(Texture2D *hud_textures, Vector2 mouse_position);

#endif //PROJET_HUD_H
