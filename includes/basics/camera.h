//
// Created by eleuc on 29/10/2022.
//

#ifndef PROJET_CAMERA_H
#define PROJET_CAMERA_H

#include "interface utilisateur.h"
#include "maths.h"
#include "../map/map_draw.h"

#define CAMERA_MOUSE_SCROLL_SENSITIVITY 1.5f
#define CAMERA_FREE_MOUSE_SENSITIVITY 0.01f
#define CAMERA_FREE_DISTANCE_MIN_CLAMP 0.3f
#define CAMERA_FREE_DISTANCE_MAX_CLAMP 120.0f
#define CAMERA_FREE_MIN_CLAMP 85.0f
#define CAMERA_FREE_MAX_CLAMP -85.0f
#define CAMERA_FREE_SMOOTH_ZOOM_SENSITIVITY 0.05f
#define CAMERA_FREE_PANNING_DIVIDER 5.1f

#define MOVING_ZONE_WIDTH_RATIO 1.0f/24.0f
#define MAX_CAMERA_SPEED 40.0f/FPS

typedef enum {
    MOVE_FRONT = 0,
    MOVE_BACK,
    MOVE_RIGHT,
    MOVE_LEFT,
    MOVE_UP,
    MOVE_DOWN
} CameraMove;

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

static CameraData CAMERA = {        // Global CAMERA state context
        .mode = 0,
        .targetDistance = 0,
        .playerEyesPosition = 1.85f,
        .angle = { 0 },
        .moveControl = { 'W', 'S', 'D', 'A', 'E', 'Q' },
        .smoothZoomControl = 341,       // raylib: KEY_LEFT_CONTROL
        .altControl = 342,              // raylib: KEY_LEFT_ALT
        .panControl = Mouse_Button_Right
};

Camera camera_new(Map_t *map);

void camera_update(Camera *camera);

void move_camera_with_mouse(Camera *camera, Vector2 mouse_pos);

#endif //PROJET_CAMERA_H
