cmake_minimum_required(VERSION 3.17)
project(Projet C)

set(CMAKE_C_STANDARD 99)

add_executable(Projet main.c  sources/menu_accueil.c sources/menu_UI.c sources/test.c includes/test.h sources/map/tiles.c includes/map/tiles.h sources/foncftions_affichage.c includes/foncftions_affichage.h sources/basics/camera.c includes/basics/camera.h sources/basics/maths.c includes/basics/maths.h sources/basics/vectors.c includes/basics/vectors.h "sources/basics/interface utilisateur.c" "includes/basics/interface utilisateur.h" sources/map/map.c includes/map/map.h sources/map/map_draw.c includes/map/map_draw.h sources/buildings/build.c includes/buildings/build.h sources/buildings/house.c includes/buildings/house.h sources/basics/time.c includes/basics/time.h sources/hud.c includes/hud.h sources/buildings/algoConnexite.c includes/buildings/algoConnexite.h sources/map/save_map.c includes/map/save_map.h sources/buildings/water_tower.c includes/buildings/water_tower.h sources/basics/queue_file.c includes/basics/queue_file.h sources/buildings/power_plant.c includes/buildings/power_plant.h sources/game.c includes/game.h sources/buildings/water_elec_distribution.c includes/buildings/water_elec_distribution.h)

add_subdirectory("raylib")
include_directories("raylib")

target_link_libraries(Projet raylib)
