//
// Created by eleuc on 25/10/2022.
//

#include "../includes/test.h"

void test() {

    Game_t *game = create_game();   /// Création et initialisation du jeu

    Vector2 mouse_pos = {0,0};  /// Création de la position de la souris

    SetTargetFPS(FPS);  /// Définition du nombre de FPS

    Vector2 screen_size = {GetScreenWidth(), GetScreenHeight()};    /// Récupération de la taille de l'écran

    while (!should_window_be_closed()) {    /// Est-ce qu'on ferme la fenêtre ?

        /*--------------------------------------------COMMANDES CLAVIER-----------------------------------------------*/

        /// Commandes clavier

        commands(game);

        /*--------------------------------------------------UPDATE----------------------------------------------------*/

        if (IsWindowResized()){    /// Ca pue la merde
            screen_size = get_screen_size();
            resize_hud(&game->hud, screen_size);
        }

        update_game(game, &mouse_pos, &screen_size);    /// Update du jeu

        /*--------------------------------------------CLICK EVENT REACTION--------------------------------------------*/

        event_click_game(game, mouse_pos);

        /*--------------------------------------------------DRAWING---------------------------------------------------*/

        BeginDrawing();    /// Début du dessin

        ClearBackground(SKYBLUE);   /// On efface l'écran avec la couleur du ciel

        draw_3D_game(game);    /// Dessin du jeu en 3D

        draw_2D_game(game, screen_size, mouse_pos);    /// Dessin du jeu en 2D

        EndDrawing();    /// Fin du dessin

        /*------------------------------------------------FIN DE BOUCLE-----------------------------------------------*/
    }

    CloseWindow();

    destroy_game(&game);

}

void loop_jeu(Game_t* game) {

    Vector2 mouse_pos = {0,0};  /// Création de la position de la souris

    Vector2 screen_size = {GetScreenWidth(), GetScreenHeight()};    /// Récupération de la taille de l'écran

        /*--------------------------------------------COMMANDES CLAVIER-----------------------------------------------*/

        /// Commandes clavier

        commands(game);

        /*--------------------------------------------------UPDATE----------------------------------------------------*/

        if (IsWindowResized()){    /// Ca pue la merde
            screen_size = get_screen_size();
            resize_hud(&game->hud, screen_size);
        }

        update_game(game, &mouse_pos, &screen_size);    /// Update du jeu

        /*--------------------------------------------CLICK EVENT REACTION--------------------------------------------*/

        event_click_game(game, mouse_pos);

        /*--------------------------------------------------DRAWING---------------------------------------------------*/

        BeginDrawing();
        ClearBackground(SKYBLUE);   /// On efface l'écran avec la couleur du ciel

        draw_3D_game(game);    /// Dessin du jeu en 3D

        draw_2D_game(game, screen_size, mouse_pos);    /// Dessin du jeu en 2D
        EndDrawing();

}