
#ifndef SFML_VECTOR_H
#define SFML_VECTOR_H

#include <cmath>

class Vector2D {
private:
    float x;
    float y;

public:
    explicit Vector2D(const float &x = 0, const float &y = 0) : x(x), y(y) {}
    Vector2D(const Vector2D &src) : x(src.x), y(src.y) {}
    virtual ~Vector2D() {}

    float X() const { return x; }

    float Y() const { return y; }

    float X(const float &_x) { this->x = _x; }

    float Y(const float &_y) { this->y = _y; }

    float operator*(const Vector2D &v) const { return x * v.x + y * v.y; }

    Vector2D operator-() const { return Vector2D(-x, -y); }

    inline Vector2D operator-(const Vector2D &v) const { return Vector2D(x - v.x, y - v.y); }

    float norm() const { return sqrt(x * x + y * y); }

    static float angle(const Vector2D &v1, const Vector2D &v2) {
        return acos((v1 * v2) / (v1.norm() * v2.norm()));
    }
};

#endif //SFML_VECTOR_H
