//
// Created by eleuc on 01/11/2022.
//

#ifndef PROJET_TIME_H
#define PROJET_TIME_H

#include <raylib.h>
#include "interface utilisateur.h"

#define SECS_FOR_MONTH 15

typedef struct {
    int speed;
    int counter;
    int seconds;
    int minutes;
    int hours;
    int months;
    int years;
} Time_t;

void update_time(Time_t *time);

void print_real_time(Vector2 position, Vector2 size, Time_t *time);

void print_in_game_time(Vector2 position, Vector2 size, Time_t *time);

void print_time(Vector2 position, Vector2 size, Time_t *time);

void change_time_speed(Time_t *time);

#endif //PROJET_TIME_H
