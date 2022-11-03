//
// Created by eleuc on 01/11/2022.
//

#ifndef PROJET_TIME_H
#define PROJET_TIME_H

#include <raylib.h>

void update_time(int *counter, int *seconds, int *minutes, int *hours);

void print_time(Vector2 position, int seconds, int minutes, int hours);

#endif //PROJET_TIME_H
