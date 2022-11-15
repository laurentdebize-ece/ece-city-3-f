//
// Created by eleuc on 15/06/2022.
//

#include "../../includes/basics/vectors.h"

Vector2 new_vec2D(float x, float y){
    return (Vector2) {x, y};
}

Vector2 vec2D_add(Vector2 a, Vector2 b){
    return (Vector2) {a.x + b.x, a.y + b.y};
}

Vector2 vec2D_sub(Vector2 a, Vector2 b){
    return (Vector2) {a.x - b.x, a.y - b.y};
}

Vector2 new_vec2D_with_length_and_angle(float length, double angle){
    return (Vector2) {length * cos(angle), length * sin(angle)};
}

bool is_vec2D_same(Vector2 a, Vector2 b){
    if (a.x == b.x && a.y == b.y){
        return true;
    }
    return false;
}