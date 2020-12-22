#pragma once

#include <math.h>

class Point {
private:
public:
  float x, y, z;
  Point(): x(0), y(0), z(0) {}
  Point(float x, float y, float z): x(x), y(y), z(z) {}
  Point(float x, float y) : Point(x, y, 0) {};
};

class Projector {
  float angle;
  Point point;
  float width;
  float height;
public:
  Projector() {};
  Projector(float angle, float width, float height) : angle(angle) {
    point = Point(width/2, height, height/3);
  }

  void resize(float new_width, float new_height) {
    width = new_width;
    height = new_height;
  }

  Point projectPoint(Point from) {
    float x = from.x;
    float y = from.y;
    float x0 = point.x;
    float y0 = point.y;
    float z0 = point.z;
    float B = sin(angle);
    float C = cos(angle);
    Point origin = Point(width/2.0, height, height/3.0);

    float t = C * z0 / (B * y0 - B * y + C * z0);

    float new_x = x0 + (x - x0) * t;
    float new_y = y0 + (y - y0) * t;
    return Point(new_x, new_y);
  }

  float projectLength(Point p1, Point p2) {
    Point _p1 = projectPoint(p1);
    Point _p2 = projectPoint(p2);
    return abs(_p2.x - _p1.x);
  }

  float projectLength(Point center, float width) {
    return projectLength(Point(center.x - width/2, center.y), Point(center.x + width/2, center.y));
  }
};
