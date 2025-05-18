#pragma once
#include "Vector.h"
#include "Timer.h"

class Camera
{
private:
    int width, height;
    Vector offset, screenshakeOffset;
    Timer screenshakeTimer;

public:
    Camera();
    Camera(int width, int height);
    void updateDimensions(float width, float height);
    Vector getCenter();
    Vector getOffset();
    float getX();
    float getY();
    void centerOnPosition(Vector pos);
    void drag(Vector vec);
    void startScreenShake();
    void shakeScreen();
};