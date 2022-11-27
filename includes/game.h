//
// Created by eleuc on 20/11/2022.
//

#ifndef PROJET_GAME_H
#define PROJET_GAME_H

#include "basics/camera.h"
#include "buildings/build.h"
#include "basics/time.h"
#include "buildings/house.h"
#include "buildings/water_tower.h"
#include "buildings/power_plant.h"
#include "hud.h"
#include "map/save_map.h"
#include "buildings/algoConnexite.h"

typedef struct Game_t {
    Camera camera;
    Time_t time;
    Model house_model[4];
    Model water_tower_model;
    Model power_plant_model;
    Vector2 mouse_pos_world, first_road_coord, second_road_coord, last_road_coord;
    Vector3 plateau[4];
    Texture2D road_texture;
    Texture2D grass_texture;
    Ray mouse_ray;
    RayCollision mouse_ground_collision;
    Queue_t *houses;
    Queue_t *water_towers;
    Queue_t *power_plants;
    Hud_t hud;
    Map_t *map;
    int view_mode;
    int money;
    int building_orientation;
    int population;
    int pause_counter;
    bool is_on_pause;
    bool capitaliste;
} Game_t;

Game_t *create_game(Vector2 screen_size,bool capitaliste,bool loadmap);

void commands(Game_t *game);

void update_game(Game_t *game, Vector2 *mouse_pos, Vector2 *screen_size);

void event_click_game(Game_t *game, Vector2 mouse_pos);

void draw_3D_game(Game_t *game);

void draw_2D_game(Game_t *game, Vector2 screen_size, Vector2 mouse_pos);

void destroy_game(Game_t **game);

#endif //PROJET_GAME_H
