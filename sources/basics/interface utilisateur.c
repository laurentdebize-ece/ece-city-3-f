//
// Created by eleuc on 31/10/2022.
//

#include "../../includes/basics/interface utilisateur.h"

int get_button_hovered(Rectangle *buttons, int buttons_count, Vector2 mouse_pos){
    for (int i = 0; i < buttons_count; ++i) {
        if (CheckCollisionPointRec(mouse_pos, buttons[i])){
            return i;
        }
    }
    return -1;
}

bool should_window_be_closed(){
    if (IsKeyDown(KEY_ESCAPE) && (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))){
        return true;
    }
    return false;
}