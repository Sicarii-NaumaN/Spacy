#pragma once

#include <math.h>
#include <SFML/Graphics.hpp>

class Projector
{
    float        angle;
    sf::Vector3f point;
    float        width;
    float        height;
    float        B;
    float        C;

public:
    Projector() {}
    Projector(float angle, float width, float height)
        : angle(angle)
    {
        point =
        { width / 2, height, height / 3 };
        B = sin(angle);
        C = cos(angle);
    }


    // Изменение размера окна
    void resize(float new_width, float new_height)
    {
        width  = new_width;
        height = new_height;
    }

    sf::Vector2f projectPoint(float x, float y) { return(projectPoint({ x, y })); }

    sf::Vector2f getOriginPoint(sf::Vector2f projected) {
        auto origin = sf::Vector2f(0, 0);
        projected.y += 100;
        origin.y = (C * point.y * point.z + (projected.y - point.y) * (B * point.y + C * point.z)) / (C * point.z - B * point.y + B * projected.y);
        origin.x = point.x + (projected.x - point.x) * (B * point.y - B * origin.y + C * point.z) / (C * point.z);

        return origin;
    }

    // Проецирование точки
    sf::Vector2f projectPoint(sf::Vector2f origin)
    {
        auto projected = sf::Vector2f(0, 0);
        float t = C * point.z / (B * point.y - B * origin.y + C * point.z);

        // Преобразованные координаты
        projected.x = point.x + (origin.x - point.x) * t;
        projected.y = point.y + (origin.y - point.y) * t;

        return projected;
    }


    // Проекция длины горизонтального отрезка
    float projectLength(sf::Vector2f p1, sf::Vector2f p2)
    {
        auto _p1 = projectPoint(p1);
        auto _p2 = projectPoint(p2);

        return(abs(_p2.x - _p1.x));
    }


    float projectLength(sf::Vector2f center, float width)
    {
        return(projectLength(
                   { center.x - width / 2, center.y },
                   { center.x + width / 2, center.y }));
    }
};
