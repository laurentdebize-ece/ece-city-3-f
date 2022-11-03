//
// Created by eleuc on 03/07/2022.
//

#ifndef JOE_MATHS_H
#define JOE_MATHS_H

#include <math.h>
#include "vectors.h"

double getVec2DLength(Vector2 vec2D);

double getDistanceBetween2Points(Vector2 a, Vector2 b);

double radiansToDegrees(double angle);

double getRadianVec2DAngle(Vector2 vec2D);

double getDegreesVec2DAngle(Vector2 vec2D);

double getRadianAngleBetween2Vec2D(Vector2 a, Vector2 b);

double getDegreesAngleBetween2Vec2D(Vector2 a, Vector2 b);

#endif //JOE_MATHS_H
