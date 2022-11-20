//
// Created by eleuc on 03/07/2022.
//

#include "../../includes/basics/maths.h"

double getVec2DLength(Vector2 vec2D){
    return sqrt(vec2D.x * vec2D.x + vec2D.y * vec2D.y);
}

double getDistanceBetween2Points(Vector2 a, Vector2 b){
    Vector2 c = vec2D_sub(a, b);
    return sqrt(c.x * c.x + c.y * c.y);
}

double radiansToDegrees(double angle){
    return angle*180/M_PI;
}

double getRadianVec2DAngle(Vector2 vec2D){
    if (vec2D.x > 0) return atan(vec2D.y/vec2D.x);
    if (vec2D.x < 0) return atan(vec2D.y/vec2D.x) + M_PI;
    if (!vec2D.x && vec2D.y > 0) return M_PI_2;
    return -M_PI_2;
}

double getDegreesVec2DAngle(Vector2 vec2D){
    if (vec2D.x > 0) return atan(vec2D.y/vec2D.x)*180/M_PI;
    if (vec2D.x < 0) return (atan(vec2D.y/vec2D.x) + M_PI)*180/M_PI;
    if (!vec2D.x && vec2D.y > 0) return M_PI_2*180/M_PI;
    return -M_PI_2*180/M_PI;
}

double getRadianAngleBetween2Vec2D(Vector2 a, Vector2 b){
    Vector2 vec2D = (Vector2) {b.x - a.x, b.y - a.y};
    if (vec2D.x > 0) return atan(vec2D.y/vec2D.x);
    if (vec2D.x < 0) return atan(vec2D.y/vec2D.x) + M_PI;
    if (!vec2D.x && vec2D.y > 0) return M_PI_2;
    return -M_PI_2;
}

double getDegreesAngleBetween2Vec2D(Vector2 a, Vector2 b){
    return atan((a.y - b.y)/(a.x - b.x))*180/M_PI;
}