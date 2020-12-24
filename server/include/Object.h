#pragma once

#include <cmath>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

const static double DEFAULT_BULLET_SPEED  = 20;
const static int    SHOT_COULDOWN_TICKS   = 15;
const static int    BULLET_TICKS_LIVETIME = 250;

const static int    WINDOW_H = 800;
const static int    WINDOW_W = 1280;

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


    float distance_between(const Vector &other) const
    {
        return(sqrt(pow((this->x - other.x), 2) + pow((this->y - other.y), 2)));
    }
};

struct Model
{
    float width;
    float height;

    Model(float w, float h)
        : height(h)
        , width(w) {}
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

class PlayerState
{
public:
    PlayerState()
        : shot_cd_tick(0) {}
    void get_state() { next_shot_tick(); }
    bool is_shot_avaible() const { return(!is_shot_cd); }

    void shot() { is_shot_cd = true; }

private:
    void next_shot_tick()
    {
        if (is_shot_cd)
        {
            shot_cd_tick++;

            if (shot_cd_tick > SHOT_COULDOWN_TICKS)
            {
                is_shot_cd   = false;
                shot_cd_tick = 0;
            }
        }
    }

    int  shot_cd_tick;
    bool is_shot_cd;
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

    PlayerState state_;
    Vector      speed;
    int         side;
};

class Map : public Object
{
public:
    Map(int id, int durations_tick, std::vector<std::shared_ptr<Object> > plrs)
        : Object(Type::MAP, id, Vector(0, 0))
        , game_duration_ticks(durations_tick)
        , players(move(plrs))
        , map_centr(
            { WINDOW_W / 2 },
            { WINDOW_H / 2 })
    {
        for (const auto &player : players)
        {
            players_pts[player->ID] = 0;
        }
    }
    void update() override {}

    std::map<int, int> players_pts;

private:
    // TODO: Сделать добавление очков при попадании в соперника/его ворота

    // void add_points_to_player(const std::shared_ptr<Object>& player) {
    //     int position_rating = (map_centr.distance_between(player->position) /
    //     ring_radius); if (position_rating < layers_count) {
    //         players_pts[player->ID] += pts_table[pts_table.size() -
    //         position_rating];
    //         //           std::cout << "ID: " << player->ID << " +PTS: " <<
    //         pts_table[position_rating] << std::endl;
    //     }
    // }
    int                                   game_duration_ticks;
    std::vector<std::shared_ptr<Object> > players;

    Vector                                map_centr;
};

class Bullet : public Object
{
public:
    Bullet(int id, int iniciator_id, Vector pos, Vector speed, )
        : Object(Type::BULLET, id, pos)
        , iniciator_ID(iniciator_id)
        , speed(speed)
        , lifetime(BULLET_TICKS_LIFETIME),
        , state(1){}


    void update() override
    {
        if (state == BulletState::ACTIVE)
        {
            if (state == 0)
                return;
            if (lifetime == 0) {
                state = 0;
                return;
            }
            lifetime--;
            position = position + speed;
        }
    }
    Vector speed;
    int    lifetime;
    int    iniciator_ID;
    bool state;
};
