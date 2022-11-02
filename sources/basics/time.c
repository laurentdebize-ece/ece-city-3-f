//
// Created by eleuc on 01/11/2022.
//

#include "../../includes/basics/time.h"

void update_time(int *counter, int *seconds, int *minutes, int *hours) {
    *counter += 1;
    if (*counter == 60) {
        *counter = 0;
        *seconds += 1;
    }
    if (*seconds == 60) {
        *seconds = 0;
        *minutes += 1;
    }
    if (*minutes == 60) {
        *minutes = 0;
        *hours += 1;
    }
}

void print_time(Vector2 position, int seconds, int minutes, int hours) {
    char time[16]={'T','i','m','e',' ',':',' ',' ',' ',' ',' ',' ',' ',' ',' ','\0'};
    if (hours < 10) {
        time[7] = '0';
        time[8] = hours + '0';
    } else {
        time[7] = hours / 10 + '0';
        time[8] = hours % 10 + '0';
    }
    time[9] = ':';
    if (minutes < 10) {
        time[10] = '0';
        time[11] = minutes + '0';
    } else {
        time[10] = minutes / 10 + '0';
        time[11] = minutes % 10 + '0';
    }
    time[12] = ':';
    if (seconds < 10) {
        time[13] = '0';
        time[14] = seconds + '0';
    } else {
        time[13] = seconds / 10 + '0';
        time[14] = seconds % 10 + '0';
    }
    DrawText(time, position.x, position.y, 20, BLACK);
}