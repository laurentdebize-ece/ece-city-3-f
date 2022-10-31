//
// Created by eleuc on 29/10/2022.
//

#ifndef PROJET_CAMERA_H
#define PROJET_CAMERA_H

#include "maths.h"

#define MOVING_ZONE_WIDTH_RATIO 1.0f/8.0f
#define MAX_CAMERA_SPEED 10.0f/60.0f

typedef enum {
    MOVE_FRONT = 0,
    MOVE_BACK,
    MOVE_RIGHT,
    MOVE_LEFT,
    MOVE_UP,
    MOVE_DOWN
} CameraMove;

// Camera global state context data [56 bytes]
typedef struct {
    unsigned int mode;              // Current camera mode
    float targetDistance;           // Camera distance from position to target
    float playerEyesPosition;       // Player eyes position from ground (in meters)
    Vector2 angle;                  // Camera angle in plane XZ

    // Camera movement control keys
    int moveControl[6];             // Move controls (CAMERA_FIRST_PERSON)
    int smoothZoomControl;          // Smooth zoom control key
    int altControl;                 // Alternative control key
    int panControl;                 // Pan view control key
} CameraData;

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
static CameraData CAMERA = {        // Global CAMERA state context
        .mode = 0,
        .targetDistance = 0,
        .playerEyesPosition = 1.85f,
        .angle = { 0 },
        .moveControl = { 'W', 'S', 'D', 'A', 'E', 'Q' },
        .smoothZoomControl = 341,       // raylib: KEY_LEFT_CONTROL
        .altControl = 342,              // raylib: KEY_LEFT_ALT
        .panControl = 2                 // raylib: MOUSE_BUTTON_MIDDLE
};

void move_camera_with_mouse(Camera *camera, Vector2 mouse_pos);

#endif //PROJET_CAMERA_H
