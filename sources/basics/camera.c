//
// Created by eleuc on 29/10/2022.
//

#include "../../includes/basics/camera.h"

Camera camera_new(Map_t *map, float tile_size) {
    Camera camera = { 0 };
    camera.position = (Vector3){ (100.0f + map->width*DECALAGE_MAP_X)*tile_size, (30.0f + DECALAGE_MAP_Y)*tile_size, (100.0f + map->height*DECALAGE_MAP_Z)*tile_size}; // Camera position
    camera.target = (Vector3){ 0.0f + map->width*DECALAGE_MAP_X, 0.0f + DECALAGE_MAP_Y, 0.0f + map->height*DECALAGE_MAP_Z};      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                   // Camera mode type
    return camera;
}

void move_camera_with_mini_map(Camera *camera, Map_t *map, Rectangle mini_map, Vector2 mouse_pos){
    Vector2 mouse_pos_on_mini_map = {mouse_pos.x - mini_map.x, mouse_pos.y - mini_map.y};
    camera->target.x = (mouse_pos_on_mini_map.x) * map->width * TILES_WIDTH / mini_map.width;
    camera->target.y = 0;
    camera->target.z = (mouse_pos_on_mini_map.y) * map->height * TILES_WIDTH / mini_map.height;

}

void camera_update(Camera *camera){

    // Mouse movement detection
    Vector2 mousePositionDelta = GetMouseDelta();
    float mouseWheelMove = GetMouseWheelMove();

    bool keyPan = IsMouseButtonDown(CAMERA.panControl);
    bool keyAlt = IsKeyDown(CAMERA.altControl);
    bool szoomKey = IsKeyDown(CAMERA.smoothZoomControl);
    bool direction[6] = { IsKeyDown(CAMERA.moveControl[MOVE_FRONT]),
                          IsKeyDown(CAMERA.moveControl[MOVE_BACK]),
                          IsKeyDown(CAMERA.moveControl[MOVE_RIGHT]),
                          IsKeyDown(CAMERA.moveControl[MOVE_LEFT]),
                          IsKeyDown(CAMERA.moveControl[MOVE_UP]),
                          IsKeyDown(CAMERA.moveControl[MOVE_DOWN]) };

// Camera zoom
    if ((CAMERA.targetDistance < CAMERA_FREE_DISTANCE_MAX_CLAMP) && (mouseWheelMove < 0))
    {
        CAMERA.targetDistance -= (mouseWheelMove*CAMERA_MOUSE_SCROLL_SENSITIVITY);
        if (CAMERA.targetDistance > CAMERA_FREE_DISTANCE_MAX_CLAMP) CAMERA.targetDistance = CAMERA_FREE_DISTANCE_MAX_CLAMP;
    }
    if ((CAMERA.targetDistance < CAMERA_FREE_DISTANCE_MAX_CLAMP) && (mouseWheelMove > 0))
    {
        CAMERA.targetDistance -= (mouseWheelMove*CAMERA_MOUSE_SCROLL_SENSITIVITY);
        if (CAMERA.targetDistance > CAMERA_FREE_DISTANCE_MAX_CLAMP) CAMERA.targetDistance = CAMERA_FREE_DISTANCE_MAX_CLAMP;
    }


        // Camera looking down
    else if ((camera->position.y > camera->target.y) && (CAMERA.targetDistance == CAMERA_FREE_DISTANCE_MAX_CLAMP) && (mouseWheelMove < 0))
    {
        camera->target.x += mouseWheelMove*(camera->target.x - camera->position.x)*CAMERA_MOUSE_SCROLL_SENSITIVITY/CAMERA.targetDistance;
        camera->target.y += mouseWheelMove*(camera->target.y - camera->position.y)*CAMERA_MOUSE_SCROLL_SENSITIVITY/CAMERA.targetDistance;
        camera->target.z += mouseWheelMove*(camera->target.z - camera->position.z)*CAMERA_MOUSE_SCROLL_SENSITIVITY/CAMERA.targetDistance;
    }
    else if ((camera->position.y > camera->target.y) && (camera->target.y >= 0))
    {
        camera->target.x += mouseWheelMove*(camera->target.x - camera->position.x)*CAMERA_MOUSE_SCROLL_SENSITIVITY/CAMERA.targetDistance;
        camera->target.y += mouseWheelMove*(camera->target.y - camera->position.y)*CAMERA_MOUSE_SCROLL_SENSITIVITY/CAMERA.targetDistance;
        camera->target.z += mouseWheelMove*(camera->target.z - camera->position.z)*CAMERA_MOUSE_SCROLL_SENSITIVITY/CAMERA.targetDistance;

        // if (camera->target.y < 0) camera->target.y = -0.001;
    }
    else if ((camera->position.y > camera->target.y) && (camera->target.y < 0) && (mouseWheelMove > 0))
    {
        CAMERA.targetDistance -= (mouseWheelMove*CAMERA_MOUSE_SCROLL_SENSITIVITY);
        if (CAMERA.targetDistance < CAMERA_FREE_DISTANCE_MIN_CLAMP) CAMERA.targetDistance = CAMERA_FREE_DISTANCE_MIN_CLAMP;
    }
        // Camera looking up
    else if ((camera->position.y < camera->target.y) && (CAMERA.targetDistance == CAMERA_FREE_DISTANCE_MAX_CLAMP) && (mouseWheelMove < 0))
    {
        camera->target.x += mouseWheelMove*(camera->target.x - camera->position.x)*CAMERA_MOUSE_SCROLL_SENSITIVITY/CAMERA.targetDistance;
        camera->target.y += mouseWheelMove*(camera->target.y - camera->position.y)*CAMERA_MOUSE_SCROLL_SENSITIVITY/CAMERA.targetDistance;
        camera->target.z += mouseWheelMove*(camera->target.z - camera->position.z)*CAMERA_MOUSE_SCROLL_SENSITIVITY/CAMERA.targetDistance;
    }
    else if ((camera->position.y < camera->target.y) && (camera->target.y <= 0))
    {
        camera->target.x += mouseWheelMove*(camera->target.x - camera->position.x)*CAMERA_MOUSE_SCROLL_SENSITIVITY/CAMERA.targetDistance;
        camera->target.y += mouseWheelMove*(camera->target.y - camera->position.y)*CAMERA_MOUSE_SCROLL_SENSITIVITY/CAMERA.targetDistance;
        camera->target.z += mouseWheelMove*(camera->target.z - camera->position.z)*CAMERA_MOUSE_SCROLL_SENSITIVITY/CAMERA.targetDistance;

        // if (camera->target.y > 0) camera->target.y = 0.001;
    }
    else if ((camera->position.y < camera->target.y) && (camera->target.y > 0) && (mouseWheelMove > 0))
    {
        CAMERA.targetDistance -= (mouseWheelMove*CAMERA_MOUSE_SCROLL_SENSITIVITY);
        if (CAMERA.targetDistance < CAMERA_FREE_DISTANCE_MIN_CLAMP) CAMERA.targetDistance = CAMERA_FREE_DISTANCE_MIN_CLAMP;
    }

    // Input keys checks
    if (keyPan)
    {
        if (keyAlt)     // Alternative key behaviour
        {
            if (szoomKey)
            {
                // Camera smooth zoom
                CAMERA.targetDistance += (mousePositionDelta.y*CAMERA_FREE_SMOOTH_ZOOM_SENSITIVITY);
            }
            else
            {
                // Camera rotation
                CAMERA.angle.x += mousePositionDelta.x*-CAMERA_FREE_MOUSE_SENSITIVITY;
                CAMERA.angle.y += mousePositionDelta.y*-CAMERA_FREE_MOUSE_SENSITIVITY;

                // Angle clamp
                if (CAMERA.angle.y > CAMERA_FREE_MIN_CLAMP*DEG2RAD) CAMERA.angle.y = CAMERA_FREE_MIN_CLAMP*DEG2RAD;
                else if (CAMERA.angle.y < CAMERA_FREE_MAX_CLAMP*DEG2RAD) CAMERA.angle.y = CAMERA_FREE_MAX_CLAMP*DEG2RAD;
            }
        }
        else
        {
            // Camera panning
            camera->target.x += ((mousePositionDelta.x*CAMERA_FREE_MOUSE_SENSITIVITY)*cosf(CAMERA.angle.x) + (mousePositionDelta.y*-CAMERA_FREE_MOUSE_SENSITIVITY)*sinf(CAMERA.angle.x)*sinf(CAMERA.angle.y))*(CAMERA.targetDistance/CAMERA_FREE_PANNING_DIVIDER);
            camera->target.y += ((mousePositionDelta.y*CAMERA_FREE_MOUSE_SENSITIVITY)*cosf(CAMERA.angle.y))*(CAMERA.targetDistance/CAMERA_FREE_PANNING_DIVIDER);
            camera->target.z += ((mousePositionDelta.x*-CAMERA_FREE_MOUSE_SENSITIVITY)*sinf(CAMERA.angle.x) + (mousePositionDelta.y*-CAMERA_FREE_MOUSE_SENSITIVITY)*cosf(CAMERA.angle.x)*sinf(CAMERA.angle.y))*(CAMERA.targetDistance/CAMERA_FREE_PANNING_DIVIDER);
        }
    }

    // Update camera position with changes
    camera->position.x = -sinf(CAMERA.angle.x)*CAMERA.targetDistance*cosf(CAMERA.angle.y) + camera->target.x;
    camera->position.y = -sinf(CAMERA.angle.y)*CAMERA.targetDistance + camera->target.y;
    camera->position.z = -cosf(CAMERA.angle.x)*CAMERA.targetDistance*cosf(CAMERA.angle.y) + camera->target.z;

}

void move_camera_with_mouse(Camera *camera, Vector2 mouse_pos, Vector2 screen_size){

    /// Update camera position with mouse coordinates

    if (mouse_pos.x < screen_size.x*MOVING_ZONE_WIDTH_RATIO){    /// Aller ?? gauche
        float tauxX = 1 - mouse_pos.x / (screen_size.x*MOVING_ZONE_WIDTH_RATIO);
        if(mouse_pos.y < screen_size.y*MOVING_ZONE_WIDTH_RATIO){  /// Aller en haut ?? gauche
            float tauxY = 1 - mouse_pos.y / (HEIGHT*MOVING_ZONE_WIDTH_RATIO);
            /// A gauche
            camera->target.x += cos(-M_PI_2+getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxX*MAX_CAMERA_SPEED;
            camera->target.z += sin(-M_PI_2+getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxX*MAX_CAMERA_SPEED;
            /// En haut
            camera->target.x += cos(getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxY*MAX_CAMERA_SPEED;
            camera->target.z += sin(getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxY*MAX_CAMERA_SPEED;
        }else if(mouse_pos.y > screen_size.y*(1-MOVING_ZONE_WIDTH_RATIO)){    /// Aller en bas ?? gauche
            float tauxY = (mouse_pos.y - screen_size.y*(1-MOVING_ZONE_WIDTH_RATIO)) / (screen_size.y*MOVING_ZONE_WIDTH_RATIO);
            /// A gauche
            camera->target.x += cos(-M_PI_2+getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxX*MAX_CAMERA_SPEED;
            camera->target.z += sin(-M_PI_2+getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxX*MAX_CAMERA_SPEED;
            /// En bas
            camera->target.x += cos(M_PI+getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxY*MAX_CAMERA_SPEED;
            camera->target.z += sin(M_PI+getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxY*MAX_CAMERA_SPEED;
        }
        else{   /// Aller ?? gauche
            camera->target.x += cos(-M_PI_2+getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxX*MAX_CAMERA_SPEED;
            camera->target.z += sin(-M_PI_2+getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxX*MAX_CAMERA_SPEED;
        }
    } else if (mouse_pos.x > screen_size.x*(1-MOVING_ZONE_WIDTH_RATIO)){ /// Aller ?? droite
        float tauxX = (mouse_pos.x - screen_size.x*(1-MOVING_ZONE_WIDTH_RATIO)) / (screen_size.x*MOVING_ZONE_WIDTH_RATIO);
        if(mouse_pos.y < screen_size.y*MOVING_ZONE_WIDTH_RATIO){  /// Aller en haut ?? droite
            float tauxY = 1 - mouse_pos.y / (screen_size.y*MOVING_ZONE_WIDTH_RATIO);
            /// A droite
            camera->target.x += cos(M_PI_2+getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxX*MAX_CAMERA_SPEED;
            camera->target.z += sin(M_PI_2+getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxX*MAX_CAMERA_SPEED;
            /// En haut
            camera->target.x += cos(getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxY*MAX_CAMERA_SPEED;
            camera->target.z += sin(getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxY*MAX_CAMERA_SPEED;
        }else if(mouse_pos.y > screen_size.y*(1-MOVING_ZONE_WIDTH_RATIO)){    /// Aller en bas ?? droite
            float tauxY = (mouse_pos.y - screen_size.y*(1-MOVING_ZONE_WIDTH_RATIO)) / (screen_size.y*MOVING_ZONE_WIDTH_RATIO);
            /// A droite
            camera->target.x += cos(M_PI_2+getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxX*MAX_CAMERA_SPEED;
            camera->target.z += sin(M_PI_2+getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxX*MAX_CAMERA_SPEED;
            /// En bas
            camera->target.x += cos(M_PI+getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxY*MAX_CAMERA_SPEED;
            camera->target.z += sin(M_PI+getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxY*MAX_CAMERA_SPEED;
        }
        else{   /// Aller ?? droite
            camera->target.x += cos(M_PI_2+getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxX*MAX_CAMERA_SPEED;
            camera->target.z += sin(M_PI_2+getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxX*MAX_CAMERA_SPEED;
        }
    }
    else{   /// Aller en haut ou en bas
        if(mouse_pos.y < screen_size.y*MOVING_ZONE_WIDTH_RATIO){  /// Aller en haut
            float tauxY = 1- mouse_pos.y / (screen_size.y*MOVING_ZONE_WIDTH_RATIO);
            camera->target.x += cos(getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxY*MAX_CAMERA_SPEED;
            camera->target.z += sin(getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxY*MAX_CAMERA_SPEED;
        }else if(mouse_pos.y > screen_size.y*(1-MOVING_ZONE_WIDTH_RATIO)){    /// Aller en bas
            float tauxY = (mouse_pos.y - screen_size.y*(1-MOVING_ZONE_WIDTH_RATIO)) / (screen_size.y*MOVING_ZONE_WIDTH_RATIO);
            camera->target.x += cos(M_PI+getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxY*MAX_CAMERA_SPEED;
            camera->target.z += sin(M_PI+getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxY*MAX_CAMERA_SPEED;
        }
    }

    /// On met ?? jour la position de la cam??ra
    camera->position.x =
            -sinf(CAMERA.angle.x) * CAMERA.targetDistance * cosf(CAMERA.angle.y) + camera->target.x;
    camera->position.y = -sinf(CAMERA.angle.y) * CAMERA.targetDistance + camera->target.y;
    camera->position.z =
            -cosf(CAMERA.angle.x) * CAMERA.targetDistance * cosf(CAMERA.angle.y) + camera->target.z;
}
