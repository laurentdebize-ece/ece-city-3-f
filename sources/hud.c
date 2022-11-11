//
// Created by eleuc on 07/11/2022.
//

#include "../includes/hud.h"

void draw_hud(Texture2D hud_textures, Rectangle *tab_button_icon_rec, Vector2 mouse_pos, HUD_BUTTONS button_pressed, int view_mode, bool is_paused, int speed){
    int width = GetScreenWidth(), height = GetScreenHeight();
    Color speed_colors[4] = {SKYBLUE, GREEN, YELLOW, RED};
    int speed_color = speed;
    if(speed_color == 5) speed_color = 3;
    else if(speed_color == 10) speed_color = 4;
    DrawRectangle(0, height*(1.0 - HUD_HEIGHT_RATIO), width, height*HUD_HEIGHT_RATIO, Fade(BLACK, 0.5f));
    DrawRectangleLines(0, height*3.0f/4.0f, width, height*HUD_HEIGHT_RATIO, BLACK);

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

void change_view_mode(int *view_mode){
    *view_mode = (*view_mode + 1) % 3;
}

bool is_mouse_on_hud(Vector2 mouse_position){
    if (mouse_position.x > GetScreenWidth() * (1.0f - HUD_WIDTH_RATIO)){
        return true;
    }
    return false;
}