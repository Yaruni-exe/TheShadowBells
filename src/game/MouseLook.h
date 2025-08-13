#ifndef MOUSELOOK_H
#define MOUSELOOK_H

#include <raylib.h>

class MouseLook {
public:
    void Update(Vector2 playerPos, Vector2 worldMousePos);
    int GetDirectionIndex() const;
    float GetAngleDegrees() const;

private:
    int directionIndex = 0;
    float angleDegrees = 0.0f;
};

#endif // MOUSELOOK_H