#include <Vector.h>

Vector::Vector()
{
    x = 0;
    y = 0;
}

Vector::Vector(float posX, float posY)
{
    x = posX;
    y = posY;
}

bool Vector::operator==(const Vector &other) const
{
    return x == other.x && y == other.y;
}

bool Vector::operator!=(const Vector &other) const
{
    return x != other.x || y != other.y;
}

Vector Vector::operator+(const Vector &other) const
{
    return Vector(x + other.x, y + other.y);
}

Vector Vector::operator-(const Vector &other) const
{
    return Vector(x - other.x, y - other.y);
}

Vector Vector::operator*(const Vector &other) const
{
    return Vector(x * other.x, y * other.y);
}

Vector Vector::operator/(const Vector &other) const
{
    float tempX = x;
    float tempY = y;
    tempX = (other.x != 0) ? tempX / other.x : 0;
    tempY = (other.y != 0) ? tempY / other.y : 0;

    return Vector(tempX, tempY);
}

void Vector::operator+=(const Vector &other)
{
    x += other.x;
    y += other.y;
}

void Vector::operator-=(const Vector &other)
{
    x -= other.x;
    y -= other.y;
}

void Vector::operator*=(const Vector &other)
{
    x *= other.x;
    y *= other.y;
}

void Vector::operator/=(const Vector &other)
{
    x = (other.x != 0) ? x / other.x : 0;
    y = (other.y != 0) ? y / other.y : 0;
}

Vector Vector::operator+(const float &other) const
{
    return Vector(x + other, y + other);
}

Vector Vector::operator-(const float &other) const
{
    return Vector(x - other, y - other);
}

Vector Vector::operator*(const float &other) const
{
    return Vector(x * other, y * other);
}

Vector Vector::operator/(const float &other) const
{
    float tempX = x;
    float tempY = y;
    tempX = (other != 0) ? tempX / other : 0;
    tempY = (other != 0) ? tempY / other : 0;

    return Vector(tempX, tempY);
}

void Vector::operator+=(const float &other)
{
    x += other;
    y += other;
}

void Vector::operator-=(const float &other)
{
    x -= other;
    y -= other;
}

void Vector::operator*=(const float &other)
{
    x *= other;
    y *= other;
}

void Vector::operator/=(const float &other)
{
    x = (other != 0) ? x / other : 0;
    y = (other != 0) ? y / other : 0;
}

float Vector::dotProduct(const Vector &other)
{
    return x * other.x + y * other.y;
}

Vector Vector::absolute()
{
    x = abs(x);
    y = abs(y);
    return *this;
}

Vector Vector::roundVec()
{
    x = round(x);
    y = round(y);
    return *this;
}

Vector Vector::floorVec()
{
    x = floor(x);
    y = floor(y);
    return *this;
}

bool Vector::isZero()
{
    if (x == 0 && y == 0)
    {
        return true;
    }
    return true;
}

float Vector::magnitude()
{
    return sqrt((pow(x, 2) + pow(y, 2)));
}

float Vector::distance(Vector other)
{
    return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
}

Vector Vector::normalize()
{
    float mag = magnitude();
    *this /= Vector(mag, mag);
    return *this;
}

double Vector::getRadians()
{
    return atan2(y, x);
}

double Vector::getAngle()
{
    return atan2(y, x) * 180 / PI;
}

void Vector::rotate(float rotation)
{
    rotation = rotation * PI / 180;
    float xPrime = (x * cos(rotation)) - (y * sin(rotation));
    float yPrime = (y * cos(rotation)) + (x * sin(rotation));
    x = xPrime;
    y = yPrime;
}

void Vector::display()
{
    cout << "Vector(" << x << ", " << y << ")" << std::endl;
}
