#include "Camera.h"

Camera::Camera()
{
}

Camera::Camera(int width, int height)
{
    updateDimensions(width, height);
}

void Camera::updateDimensions(float width, float height)
{
    this->width = width;
    this->height = height;
}

Vector Camera::getCenter()
{
    return offset + Vector(width / 2, height / 2);
}

Vector Camera::getOffset()
{
    return offset + screenshakeOffset;
}

float Camera::getX()
{
    return offset.x;
}

float Camera::getY()
{
    return offset.y;
}

void Camera::centerOnPosition(Vector pos)
{
    offset = Vector(pos.x - width / 2.0, pos.y - height / 2.0);
}

void Camera::drag(Vector vec)
{
    offset -= vec;
}

void Camera::startScreenShake()
{
    screenshakeTimer.start();
}

void Camera::shakeScreen()
{
    if (screenshakeTimer.isStarted())
    {
        if (screenshakeTimer.getTicks() / 1000 < 0.2)
        {
            screenshakeOffset = Vector(-4 + rand() % 9, -4 + rand() % 9);
        }
        else
        {
            screenshakeOffset = Vector(0, 0);
            screenshakeTimer.reset();
        }
    }
}
