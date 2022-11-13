//
// Created by eleuc on 26/10/2022.
//

#ifndef PROJET_TILES_H
#define PROJET_TILES_H

#define TILE_SIZE 20

typedef enum {
    Tile_Type_Grass,
    Tile_Type_Road,
    Tile_Type_House,
    Tile_Type_Builing,
    Tile_Type_Count
}TileType;

typedef enum {
    ROAD_ALONE,
    ROAD_N,
    ROAD_S,
    ROAD_NS,
    ROAD_E,
    ROAD_NE,
    ROAD_SE,
    ROAD_NSE,
    ROAD_W,
    ROAD_NW,
    ROAD_SW,
    ROAD_NSW,
    ROAD_EW,
    ROAD_NEW,
    ROAD_SEW,
    ROAD_NSEW,
    ROAD_COUNT
}RoadType;

typedef enum{
    Ruins,
    Terrain_nu,
    Cabane,
    Maison,
    Immeuble,
    Gratte_Ciel,
    Nb_Variantes_Maisons
}HouseVariant;

typedef enum {
    Building_Varient_Water_Tower,
    Building_Varient_Power_Plant,
    Nb_Variantes_Batiments
}BuildingVariant;

typedef enum {
    Building_Orientation_N,
    Building_Orientation_S,
    Building_Orientation_E,
    Building_Orientation_W
}BuildingOrientation;

typedef struct {
    TileType type;
    int varient;
    union {
        void *building;
    };
    union {
        BuildingOrientation orientation;
    };
}Tile_t;

Tile_t tile_init_default(void);

#endif //PROJET_TILES_H
