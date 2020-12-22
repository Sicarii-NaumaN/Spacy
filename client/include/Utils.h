#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>

class Projector {
  float angle;
  sf::Vector3f point;
  float width;
  float height;
public:
  Projector() {};
  Projector(float angle, float width, float height) : angle(angle) {
    point = sf::Vector3f(width/2, height, height/3);
  }

  // Изменение размера окна
  void resize(float new_width, float new_height) {
    width = new_width;
    height = new_height;
  }

  sf::Vector2f projectPoint(float x, float y) {
    return projectPoint(sf::Vector2f(x, y));
  }

  // Проецирование точки
  sf::Vector2f projectPoint(sf::Vector2f from) {
    // Координаты, которые нужно преобразовать
    float x = from.x;
    float y = from.y;

    // Точка, из которой выходят линии для проецирования
    float x0 = point.x;
    float y0 = point.y;
    float z0 = point.z;

    // Коэффициенты плоскости, на которую будем проецировать
    float B = sin(angle);
    float C = cos(angle);

    float t = C * z0 / (B * y0 - B * y + C * z0);

    // Преобразованные координаты
    float new_x = x0 + (x - x0) * t;
    float new_y = y0 + (y - y0) * t;

    return sf::Vector2f(new_x, new_y);
  }

  // Проекция длины горизонтального отрезка
  float projectLength(sf::Vector2f p1, sf::Vector2f p2) {
    sf::Vector2f _p1 = projectPoint(p1);
    sf::Vector2f _p2 = projectPoint(p2);
    return abs(_p2.x - _p1.x);
  }

  float projectLength(sf::Vector2f center, float width) {
    return projectLength(sf::Vector2f(center.x - width/2, center.y), sf::Vector2f(center.x + width/2, center.y));
  }
};
