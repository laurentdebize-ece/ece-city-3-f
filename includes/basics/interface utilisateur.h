//
// Created by eleuc on 31/10/2022.
//

#ifndef PROJET_INTERFACE_UTILISATEUR_H
#define PROJET_INTERFACE_UTILISATEUR_H

#include <raylib.h>

#define WIDTH (1920)   //1024
#define HEIGHT (1080)  //768
#define TITLE "ECE City"
#define FPS 60.0f

typedef enum {
    Mouse_Button_Left,       // Mouse button left
    Mouse_Button_Right,       // Mouse button right
    Mouse_Button_Middle,        // Mouse button middle (la molette)
    Mouse_Button_Side_Back,        // Mouse button side back (sur la souris d'Habib)
    Mouse_Button_Side_Front,        // Mouse button side front (sur la souris d'Habib)
    Nb_Mouse_Button
} MOUSE_BUTTONS;

int get_button_hovered(Rectangle *buttons, int buttons_count, Vector2 mouse_pos);

bool should_window_be_closed();

Vector2 get_screen_size();

#endif //PROJET_INTERFACE_UTILISATEUR_H
