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


    // Проецирование точки
    sf::Vector2f projectPoint(sf::Vector2f from)
    {
        float t = C * point.z / (B * point.y - B * from.y + C * point.z);

        // Преобразованные координаты
        float new_x = point.x + (from.x - point.x) * t;
        float new_y = point.y + (from.y - point.y) * t;

        return
            { new_x, new_y };
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
