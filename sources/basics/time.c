//
// Created by eleuc on 01/11/2022.
//

#include "../../includes/basics/time.h"

void update_time(Time_t *time) {
    time->counter+=time->speed;
    if (time->counter >= FPS) {
        time->seconds++;
        if (time->seconds % SECS_FOR_MONTH == 0) {
            time->months++;
            if (time->months >= 12) {
                time->months = 0;
                time->years++;
            }
        }
        time->counter = time->counter %(int)FPS;
        if (time->seconds >= 60) {
            time->seconds = 0;
            time->minutes++;
            if (time->minutes >= 60) {
                time->minutes = 0;
                time->hours++;
            }
        }
    }
}

void print_real_time(Vector2 position, Time_t *time) {

    char time_string[16]={'T','i','m','e',' ',':',' ',' ',' ',' ',' ',' ',' ',' ',' ','\0'};

    if (time->hours < 10) {
        time_string[7] = '0';
        time_string[8] = time->hours + '0';
    } else {
        time_string[7] = (time->hours / 10) + '0';
        time_string[8] = (time->hours % 10) + '0';
    }
    time_string[9] = ':';
    if (time->minutes < 10) {
        time_string[10] = '0';
        time_string[11] = time->minutes + '0';
    } else {
        time_string[10] = (time->minutes / 10) + '0';
        time_string[11] = (time->minutes % 10) + '0';
    }
    time_string[12] = ':';
    if (time->seconds < 10) {
        time_string[13] = '0';
        time_string[14] = time->seconds + '0';
    } else {
        time_string[13] = (time->seconds / 10) + '0';
        time_string[14] = (time->seconds % 10) + '0';
    }
    DrawRectangle( position.x, position.y, 300, 50, Fade(RED, 0.5f));
    DrawRectangleLines( position.x, position.y, 300, 50, RED);
    DrawText(time_string, position.x + 10, position.y + 10, 30, BLACK);
}

void print_in_game_time(Vector2 position, Time_t *time) {
    char time_sting[16]={'D', 'a', 't', 'e', ' ', ':', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'};

    switch (time->months) {
        case 0:
            time_sting[7] = 'J';
            time_sting[8] = 'a';
            time_sting[9] = 'n';
            break;
        case 1:
            time_sting[7] = 'F';
            time_sting[8] = 'e';
            time_sting[9] = 'b';
            break;
        case 2:
            time_sting[7] = 'M';
            time_sting[8] = 'a';
            time_sting[9] = 'r';
            break;
        case 3:
            time_sting[7] = 'A';
            time_sting[8] = 'p';
            time_sting[9] = 'r';
            break;
        case 4:
            time_sting[7] = 'M';
            time_sting[8] = 'a';
            time_sting[9] = 'y';
            break;
        case 5:
            time_sting[7] = 'J';
            time_sting[8] = 'u';
            time_sting[9] = 'n';
            break;
        case 6:
            time_sting[7] = 'J';
            time_sting[8] = 'u';
            time_sting[9] = 'l';
            break;
        case 7:
            time_sting[7] = 'A';
            time_sting[8] = 'u';
            time_sting[9] = 'g';
            break;
        case 8:
            time_sting[7] = 'S';
            time_sting[8] = 'e';
            time_sting[9] = 'p';
            break;
        case 9:
            time_sting[7] = 'O';
            time_sting[8] = 'c';
            time_sting[9] = 't';
            break;
        case 10:
            time_sting[7] = 'N';
            time_sting[8] = 'o';
            time_sting[9] = 'v';
            break;
        case 11:
            time_sting[7] = 'D';
            time_sting[8] = 'e';
            time_sting[9] = 'c';
            break;
    }
    if(time->years < 10){
        time_sting[11] = '0' + time->years;
    }
    else if (time->years < 100){
        time_sting[11] = '0' + time->years / 10;
        time_sting[12] = '0' + time->years % 10;
    }
    else if (time->years < 1000){
        time_sting[11] = '0' + time->years / 100;
        time_sting[12] = '0' + (time->years % 100) / 10;
        time_sting[13] = '0' + time->years % 10;
    }
    else{
        time_sting[11] = '0' + time->years / 1000;
        time_sting[12] = '0' + (time->years % 1000) / 100;
        time_sting[13] = '0' + (time->years % 100) / 10;
        time_sting[14] = '0' + time->years % 10;
    }
    DrawRectangle( position.x, position.y, 300, 50, Fade(ORANGE, 0.5f));
    DrawRectangleLines( position.x, position.y, 300, 50, ORANGE);
    DrawText(time_sting, position.x + 10, position.y + 10, 30, BLACK);
}

void print_time(Vector2 position, Time_t *time) {
    print_real_time(position, time);
    print_in_game_time((Vector2){position.x, position.y + 60}, time);
}

void change_time_speed(Time_t *time) {
    switch (time->speed) {
        case 1:
            time->speed = 2;
            break;
        case 2:
            time->speed = 4;
            break;
        case 5:
            time->speed = 10;
            break;
        case 10:
            time->speed = 1;
            break;
    }
}