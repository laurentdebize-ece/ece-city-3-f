//
// Created by eleuc on 31/10/2022.
//

#include "../../includes/map/map.h"

Map_t* map_create(int width, int height) {
    Map_t* map = malloc(sizeof(Map_t));
    map->width = width;
    map->height = height;
    map->tiles = malloc(height * width * sizeof(Tile_t *));
    for (int i = 0; i < width*height; i++) {
        map->tiles[i] = malloc(sizeof(Tile_t));
        *map->tiles[i] = tile_init_default();
    }
    return map;
}

Map_t* load_map(const char* path) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("ERREUR : FICHIER INTROUVABLE");
    }
    int width, height;
    fscanf(file, "%d %d", &width, &height);
    Map_t* map = map_create(width, height);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            fscanf(file, "%d", &map->tiles[y*width + x]->type);
        }
    }

    return map;
}

void print_map_console(Map_t* map){
    for (int y = 0; y < map->height; ++y) {
        for (int x = 0; x < map->width; ++x) {
            printf("%d ", map->tiles[y*map->width + x]->type);
        }
        printf("\n");
    }
}

void map_destroy(Map_t **map) {
    for (int i = 0; i < (*map)->width*(*map)->height; i++) {
        free((*map)->tiles[i]);
        (*map)->tiles[i] = NULL;
    }
    free((*map)->tiles);
    (*map)->tiles = NULL;
    free(*map);
    *map = NULL;
}
