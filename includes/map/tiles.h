//
// Created by eleuc on 26/10/2022.
//

#ifndef PROJET_TILES_H
#define PROJET_TILES_H

#define TILE_SIZE 20

enum TileType {
    TILE_GRASS,
    TILE_ROAD,
    TILE_HOUSE,
    TILE_BUILDING,
    TILE_COUNT
}TileType;

enum RoadType {
    ROAD_N,
    ROAD_S,
    ROAD_E,
    ROAD_W,
    ROAD_NE,
    ROAD_NW,
    ROAD_SE,
    ROAD_SW,
    ROAD_NS,
    ROAD_EW,
    ROAD_NSE,
    ROAD_NSW,
    ROAD_SEW,
    ROAD_NSEW,
    ROAD_COUNT
}RoadType;

typedef struct {
    int tile_type;
    union {
        int road_type;
        int building_type;
    };
};

#endif //PROJET_TILES_H
