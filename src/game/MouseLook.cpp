#include "MouseLook.h"
#include "raymath.h"

void MouseLook::Update(Vector2 playerPos, Vector2 worldMousePos) {
    Vector2 dir = Vector2Subtract(worldMousePos, playerPos);
    angleDegrees = atan2f(-dir.y, dir.x) * RAD2DEG;
    if (angleDegrees < 0) angleDegrees += 360.0f;

    float angle = angleDegrees;

    if      (angle < 22.5f || angle >= 337.5f) directionIndex = 0; // Rechts
    else if (angle < 67.5f)  directionIndex = 1;                   // Oben-Rechts
    else if (angle < 112.5f) directionIndex = 2;                   // Oben
    else if (angle < 157.5f) directionIndex = 3;                   // Oben-Links
    else if (angle < 202.5f) directionIndex = 4;                   // Links
    else if (angle < 247.5f) directionIndex = 5;                   // Unten-Links
    else if (angle < 292.5f) directionIndex = 6;                   // Unten
    else                     directionIndex = 7;                   // Unten-Rechts
}

int MouseLook::GetDirectionIndex() const {
    return directionIndex;
}

float MouseLook::GetAngleDegrees() const {
    return angleDegrees;
}