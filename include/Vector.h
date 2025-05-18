#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <math.h>
#define PI 3.14159265358979323846

using namespace std;

class Vector
{
public:
    float x, y;
    Vector();
    Vector(float posX, float posY);
    bool operator==(const Vector &other) const;
    bool operator!=(const Vector &other) const;
    Vector operator+(const Vector &other) const;
    Vector operator-(const Vector &other) const;
    Vector operator*(const Vector &other) const;
    Vector operator/(const Vector &other) const;
    void operator+=(const Vector &other);
    void operator-=(const Vector &other);
    void operator*=(const Vector &other);
    void operator/=(const Vector &other);
    Vector operator+(const float &other) const;
    Vector operator-(const float &other) const;
    Vector operator*(const float &other) const;
    Vector operator/(const float &other) const;
    void operator+=(const float &other);
    void operator-=(const float &other);
    void operator*=(const float &other);
    void operator/=(const float &other);
    float dotProduct(const Vector &other);
    Vector absolute();
    Vector roundVec();
    Vector floorVec();
    bool isZero();
    float magnitude();
    float distance(Vector other);
    Vector normalize();
    double getRadians();
    double getAngle();
    void rotate(float rotation);
    void display();
};