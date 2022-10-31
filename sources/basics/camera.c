//
// Created by eleuc on 29/10/2022.
//

#include "../../includes/basics/camera.h"

void move_camera_with_mouse(Camera *camera, Vector2 mouse_pos) {

    // Update camera position with mouse coordinates

    if (mouse_pos.x < 1024*MOVING_ZONE_WIDTH_RATIO){    // Aller à gauche
        float tauxX = 1 - mouse_pos.x / (1024*MOVING_ZONE_WIDTH_RATIO);
        if(mouse_pos.y < 768*MOVING_ZONE_WIDTH_RATIO){  /// Aller en haut à gauche
            float tauxY = 1 - mouse_pos.y / (768*MOVING_ZONE_WIDTH_RATIO);
            /// A gauche
            camera->target.x += cos(-M_PI_2+getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxX*MAX_CAMERA_SPEED;
            camera->target.z += sin(-M_PI_2+getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxX*MAX_CAMERA_SPEED;
            /// En haut
            camera->target.x += cos(getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxY*MAX_CAMERA_SPEED;
            camera->target.z += sin(getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxY*MAX_CAMERA_SPEED;
        }else if(mouse_pos.y > 768*(1-MOVING_ZONE_WIDTH_RATIO)){    /// Aller en bas à gauche
            float tauxY = (mouse_pos.y - 768*(1-MOVING_ZONE_WIDTH_RATIO)) / (768*MOVING_ZONE_WIDTH_RATIO);
            /// A gauche
            camera->target.x += cos(-M_PI_2+getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxX*MAX_CAMERA_SPEED;
            camera->target.z += sin(-M_PI_2+getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxX*MAX_CAMERA_SPEED;
            /// En bas
            camera->target.x += cos(M_PI+getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxY*MAX_CAMERA_SPEED;
            camera->target.z += sin(M_PI+getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxY*MAX_CAMERA_SPEED;
        }
        else{   /// Aller à gauche
            camera->target.x += cos(-M_PI_2+getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxX*MAX_CAMERA_SPEED;
            camera->target.z += sin(-M_PI_2+getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxX*MAX_CAMERA_SPEED;
        }
    } else if (mouse_pos.x > 1024*(1-MOVING_ZONE_WIDTH_RATIO)){ /// Aller à droite
        float tauxX = (mouse_pos.x - 1024*(1-MOVING_ZONE_WIDTH_RATIO)) / (1024*MOVING_ZONE_WIDTH_RATIO);
        if(mouse_pos.y < 768*MOVING_ZONE_WIDTH_RATIO){  /// Aller en haut à droite
            float tauxY = 1 - mouse_pos.y / (768*MOVING_ZONE_WIDTH_RATIO);
            /// A droite
            camera->target.x += cos(M_PI_2+getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxX*MAX_CAMERA_SPEED;
            camera->target.z += sin(M_PI_2+getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxX*MAX_CAMERA_SPEED;
            /// En haut
            camera->target.x += cos(getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxY*MAX_CAMERA_SPEED;
            camera->target.z += sin(getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxY*MAX_CAMERA_SPEED;
        }else if(mouse_pos.y > 768*(1-MOVING_ZONE_WIDTH_RATIO)){    /// Aller en bas à droite
            float tauxY = (mouse_pos.y - 768*(1-MOVING_ZONE_WIDTH_RATIO)) / (768*MOVING_ZONE_WIDTH_RATIO);
            /// A droite
            camera->target.x += cos(M_PI_2+getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxX*MAX_CAMERA_SPEED;
            camera->target.z += sin(M_PI_2+getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxX*MAX_CAMERA_SPEED;
            /// En bas
            camera->target.x += cos(M_PI+getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxY*MAX_CAMERA_SPEED;
            camera->target.z += sin(M_PI+getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxY*MAX_CAMERA_SPEED;
        }
        else{   /// Aller à droite
            camera->target.x += cos(M_PI_2+getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxX*MAX_CAMERA_SPEED;
            camera->target.z += sin(M_PI_2+getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxX*MAX_CAMERA_SPEED;
        }
    }
    else{   /// Aller en haut ou en bas
        if(mouse_pos.y < 768*MOVING_ZONE_WIDTH_RATIO){  /// Aller en haut
            float tauxY = 1- mouse_pos.y / (768*MOVING_ZONE_WIDTH_RATIO);
            camera->target.x += cos(getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxY*MAX_CAMERA_SPEED;
            camera->target.z += sin(getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxY*MAX_CAMERA_SPEED;
        }else if(mouse_pos.y > 768*(1-MOVING_ZONE_WIDTH_RATIO)){    /// Aller en bas
            float tauxY = (mouse_pos.y - 768*(1-MOVING_ZONE_WIDTH_RATIO)) / (768*MOVING_ZONE_WIDTH_RATIO);
            camera->target.x += cos(M_PI+getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxY*MAX_CAMERA_SPEED;
            camera->target.z += sin(M_PI+getRadianAngleBetween2Vec2D(new_vec2D(camera->position.x, camera->position.z), new_vec2D(camera->target.x, camera->target.z)))*tauxY*MAX_CAMERA_SPEED;
        }
    }

    camera->position.x =
            -sinf(CAMERA.angle.x) * CAMERA.targetDistance * cosf(CAMERA.angle.y) + camera->target.x;
    camera->position.y = -sinf(CAMERA.angle.y) * CAMERA.targetDistance + camera->target.y;
    camera->position.z =
            -cosf(CAMERA.angle.x) * CAMERA.targetDistance * cosf(CAMERA.angle.y) + camera->target.z;
}
