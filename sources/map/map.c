//
// Created by eleuc on 31/10/2022.
//

#include "../../includes/map/map.h"

Map_t* map_create(int width, int height) {
    Map_t* map = malloc(sizeof(Map_t));
    map->width = width;
    map->height = height;
    map->house_count = 0;
    /// Création du tableau de pointeurs de Tile_t (tuiles)
    map->tiles = malloc(height * width * sizeof(Tile_t *));
    for (int i = 0; i < width*height; i++) {
        /// Création des tuiles
        map->tiles[i] = malloc(sizeof(Tile_t));
        /// Initialisation des tuiles
        *map->tiles[i] = tile_init_default();
    }
    /// Retourne la map
    return map;
}

Map_t* load_map(const char* path) {
    /// Ouverture du fichier
    FILE *file = fopen(path, "r");
    if (file == NULL) { /// Si le fichier n'existe pas
        printf("ERREUR : FICHIER INTROUVABLE"); /// Affiche un message d'erreur
    }
    int width, height;
    /// Récupère la largeur et la hauteur de la map
    fscanf(file, "%d %d", &width, &height);
    /// Création de la map
    Map_t* map = map_create(width, height);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            /// Récupère le type de la tuile
            fscanf(file, "%d", &map->tiles[y*width + x]->type);
        }
    }
    /// Ferme le fichier
    fclose(file);
    /// Retourne la map
    return map;
}

void print_map_console(Map_t* map){
    /// Affiche la map dans la console
    for (int y = 0; y < map->height; ++y) {
        for (int x = 0; x < map->width; ++x) {
            printf("%d ", map->tiles[y*map->width + x]->type);
        }
        printf("\n");
    }
}

void map_destroy(Map_t **map) {
    /// Libère chaque tuile
    for (int i = 0; i < (*map)->width*(*map)->height; i++) {
        free((*map)->tiles[i]);
        (*map)->tiles[i] = NULL;
    }
    /// Libère le tableau de pointeurs de Tile_t (tuiles)
    free((*map)->tiles);
    (*map)->tiles = NULL;
    /// Libère la map
    free(*map);
    *map = NULL;
}

