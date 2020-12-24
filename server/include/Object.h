#pragma once

#include <cmath>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

const static double DEFAULT_BULLET_SPEED  = 20;
const static int    BULLET_TICKS_LIFETIME = 100;

const static int WINDOW_H = 800;
const static int WINDOW_W = 1280;

struct Vector
{
    float x, y;
    Vector() = default;
    Vector(float xpos, float ypos)
        : x(xpos)
        , y(ypos) {}
    Vector operator+(const Vector &rhs) const
    {
        return
            { this->x + rhs.x, this->y + rhs.y };
    }
    Vector operator-(const Vector &rhs) const
    {
        return
            { this->x - rhs.x, this->y - rhs.y };
    }
    Vector operator*(float value) const
    {
        return
            { this->x * value, this->y * value };
    }


    Vector normalize()
    {
        float len = sqrt(x * x + y * y);

        return(Vector(x / len, y / len));
    }


    Vector setMag(float value)
    {
        Vector normalized = this->normalize();

        return(normalized * value);
    }


    float distance_between(const Vector &other) const
    {
        return(sqrt(pow((this->x - other.x), 2) + pow((this->y - other.y), 2)));
    }
};

class Object
{
public:
    enum Type
    {
        PLAYER,
        BULLET,
        MAP
    };
    Object(Type t, int id, Vector pos)
        : type(t)
        , ID(id)
        , position(pos) {}
    virtual void update() = 0;

    Vector position;
    Type   type;
    int    ID;
};

class Player : public Object
{
public:
    Player(int id, int side, Vector pos, Vector speed)
        : Object(Type::PLAYER, id, pos)
        , speed(speed)
        , side(side) {}
    void update() override { position = position + speed; }

    void setSpeed(float vx, float vy) { speed = Vector(vx, vy); }
    void setSpeedX(float vx) { speed.x = vx; }
    void setSpeedY(float vy) { speed.y = vy; }

    Vector      speed;
    int         side;
};


class Bullet : public Object
{
public:
    Bullet(int id, int iniciator_id, Vector pos, Vector speed)
        : Object(Type::BULLET, id, pos)
        , iniciator_ID(iniciator_id)
        , speed(speed)
        , lifetime(BULLET_TICKS_LIFETIME)
        , state(1) {}


    void constrain()
    {
        int x = position.x;
        int y = position.y;

        if (x > 1280 || x < 0)
        {
            speed.x *= -1;
        }

        if (y > 770 || y < 0)
        {
            speed.y *= -1;
        }
        position = position + speed;
    }


    void update() override
    {
        if (state == 0) { return; }

        if (lifetime == 0)
        {
            state = 0;
            return;
        }
        lifetime--;

        position = position + speed;
        constrain();
    }


    Vector speed;
    int    lifetime;
    int    iniciator_ID;
    bool   state;
};
