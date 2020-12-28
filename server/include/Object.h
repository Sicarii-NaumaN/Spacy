#pragma once

#include <cmath>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

const static double DEFAULT_BULLET_SPEED = 5;
const static int BULLET_TICKS_LIFETIME = 100;
const static int MAX_BULLET_COLLISIONS = 3;
const static int PLAYER_COLLISION_RADIUS = 10;


const static int WINDOW_H = 800;
const static int WINDOW_W = 1280;

struct Vector {
    float x, y;

    Vector() = default;

    Vector(float xpos, float ypos)
            : x(xpos), y(ypos) {}

    Vector operator+(const Vector &rhs) const {
        return
                {this->x + rhs.x, this->y + rhs.y};
    }

    Vector operator-(const Vector &rhs) const {
        return
                {this->x - rhs.x, this->y - rhs.y};
    }

    Vector operator*(float value) const {
        return
                {this->x * value, this->y * value};
    }


    Vector normalize() {
        float len = sqrt(x * x + y * y);

        return (Vector(x / len, y / len));
    }


    Vector setMag(float value) {
        Vector normalized = this->normalize();

        return (normalized * value);
    }


    float distance_between(const Vector &other) const {
        return (sqrt(pow((this->x - other.x), 2) + pow((this->y - other.y), 2)));
    }
};

class Object {
public:
    enum Type {
        PLAYER,
        BULLET,
        GAMESTATS
    };

    Object(Type t, int id, Vector pos)
            : type(t), ID(id), position(pos) {}

    virtual void update() = 0;

    Vector position;
    Type type;
    int ID;
};

class Player : public Object {
public:
    Player(int id, int side, Vector pos, Vector speed)
            : Object(Type::PLAYER, id, pos), speed(speed), side(side) {}

    void update() override {
        position = position + speed;
        constrain();
    }

    void constrain() {

        int margin_y = 50;

        if (side == 0) {
            if (position.x < 0)
                position.x = 0;
            else if (position.x > 1280)
                position.x = 1280;

            if (position.y < 600)
                position.y = 600;
            else if (position.y > 800 - margin_y)
                position.y = 800 - margin_y;
        }
        else if (side == 1) {
            if (position.x < 0)
                position.x = 0;
            else if (position.x > 1280)
                position.x = 1280;

            if (position.y < 20)
                position.y = 30; // Чтоб корабль не торчал
            else if (position.y > 200 - margin_y)
                position.y = 200 - margin_y;
        }
    }

    void setSpeed(float vx, float vy) { speed = Vector(vx, vy); }

    void setSpeedX(float vx) { speed.x = vx; }

    void setSpeedY(float vy) { speed.y = vy; }

    Vector speed;
    int side;
};

// g- в пульку добавлено поле collisionCount, инкрементируется при каждом столкновении, когда доходит до 3 убиваем пульку
class Bullet : public Object {
public:
    Bullet(int id, int iniciator_id, Vector pos, Vector speed)
            : Object(Type::BULLET, id, pos), iniciator_ID(iniciator_id), speed(speed),
              state(1) {}


    void constrain() {
        int x = position.x;
        int y = position.y;

        //Vector enemy_pos = {0,0};


        if (x > 1280 || x < 0) {
            speed.x *= -1;
            ++collisions_count;
        }

        if (y > 750 || y < 50) { // g- 50 для того чтобы пулька не выходила за заднюю стенку (front wall)
            speed.y *= -1;
            ++collisions_count;
        }
        position = position + speed;
    }


    void update() {
        if (state == 0) { return; }

        if (collisions_count == MAX_BULLET_COLLISIONS) {
            state = 0;
            return;
        }

        position = position + speed;
        constrain();
    }

    Vector speed;
    int collisions_count = 0;
    int iniciator_ID;
    bool state;
};

class GameStatistics : public Object {
public:
    int team1_score;
    int team2_score;
    int time_remaining;

    GameStatistics(int id, int game_duration)
            : Object(Type::GAMESTATS, id, Vector(0, 0))
            , team1_score(0)
            , team2_score(0)
            , time_remaining(game_duration) {}

    void addPoint(int team) {
        if (team == 0)
            team1_score++;
        else if (team == 1)
            team2_score++;
    }

    void update() {}

};
