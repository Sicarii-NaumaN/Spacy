#pragma once

#include <memory>
#include <map>
#include <vector>
#include <cmath>
#include <iostream>

const static double DEFAULT_BULLET_SPEED = 20;
const static double DEFAULT_PLAYER_SPEED = 3;
const static int SHOT_COULDOWN_TICKS = 15;
const static int BULLET_TICKS_LIVETIME = 250;

const static int WINDOW_H = 800;
const static int WINDOW_W = 1280;


struct Point {
    double x, y;
    Point() = default;
    Point(double xpos, double ypos): x(xpos), y(ypos) {}
    Point operator+ (const Point& rhs) const {
        return {this->x + rhs.x, this->y + rhs.y};
    }
    Point operator- (const Point& rhs) const {
        return {this->x - rhs.x, this->y - rhs.y};
    }
    Point operator* (double value) const {
        return {this->x * value, this->y * value};
    }
    double distance_between(const Point& other) const {
        return sqrt(pow((this->x - other.x), 2) + pow((this->y - other.y), 2));
    }

};

struct Vector {
    Point from, to;
    Vector(Point f, Point t):from(f), to(t){}
};

struct Model {
    int height, width;
    Model(int w, int h):height(h), width(w) {}
};

class Object {
public:
    enum Type {
        STATIC_OBJECT,
        PLAYER_OBJECT,
        BULLET_OBJECT,
        MAP_OBJECT
    };
    Object(Type t, int id, Point pos, Model mod):type(t), ID(id), position(pos), model(mod) {}
    virtual void update()  = 0;
    Point position;
    Model model;
    Type type;
    int ID;
};

class PlayerState {
public:
    PlayerState(): shot_cd_tick(0) {};
    void get_state() {
        next_shot_tick();
    }
    bool is_shot_avaible() const {
        return !is_shot_cd;
    }

    void shot() {
        is_shot_cd = true;
    }
private:
    void next_shot_tick() {
        if (is_shot_cd) {
            shot_cd_tick++;
            if (shot_cd_tick > SHOT_COULDOWN_TICKS) {
                is_shot_cd = false;
                shot_cd_tick = 0;
            }
        }
    }

    int shot_cd_tick;
    bool is_shot_cd;
};

class Player : public Object {
public:
    Player(int id, Point pos): Object(Type::PLAYER_OBJECT, id, pos, Model(26,26)),
                               sight(1, 0), speed(DEFAULT_PLAYER_SPEED) {};
    void update() override {
      speed = DEFAULT_PLAYER_SPEED;
    }
    PlayerState state_;
    Point sight;
    double speed;
    Point normalize(const Vector& vec) const {
        double t1 = vec.to.x - vec.from.x;
        double t2 = vec.to.y - vec.from.y;
        double l = sqrt(t1 * t1 + t2 * t2);
        return {t1 / l, t2 / l};
    }
};

class Map : public  Object {
public:
    Map(int id, int durations_tick, std::vector<std::shared_ptr<Object>> plrs):
            Object(Type::MAP_OBJECT, id, Point(0, 0), Model(0, 0)),
            game_duration_ticks(durations_tick),
            players(move(plrs)),
            map_centr({WINDOW_W/ 2}, {WINDOW_H / 2}) {

        for(const auto& player: players) {
            players_pts[player->ID] = 0;
        }
    }
    void update() override {
        ;
    }
    std::map<int, int> players_pts;
private:
    // TODO: Сделать добавление очков при попадании в соперника/его ворота

    // void add_points_to_player(const std::shared_ptr<Object>& player) {
    //     int position_rating = (map_centr.distance_between(player->position) / ring_radius);
    //     if (position_rating < layers_count) {
    //         players_pts[player->ID] += pts_table[pts_table.size() - position_rating];
    //         //           std::cout << "ID: " << player->ID << " +PTS: " << pts_table[position_rating] << std::endl;
    //     }
    // }
    int game_duration_ticks;
    std::vector<std::shared_ptr<Object>> players;

    Point map_centr;
};

class Obstruction : public  Object {
public:
    Obstruction(int id, Point pos, int w, int h): Object(Type::STATIC_OBJECT, id, pos, Model(w,h)) {};
    void update() override {}
};

class BulletState {
public:
    enum State {
        ACTIVE,
        INACTIVE
    };
    BulletState(): state_(State::ACTIVE), live_tick(0) {};
    void state_to_inactive() {
        if (state_ == State::ACTIVE) {
            state_ = State::INACTIVE;
        }
    }
    State get_state() {
        next_tick();
        return state_;
    }
private:
    void next_tick() {
        live_tick++;
        if (live_tick > BULLET_TICKS_LIVETIME) {
            state_ = State::INACTIVE;
            live_tick = 0;
        }
    };
    int live_tick;
    State state_;
};

class Bullet : public  Object {
public:
    Bullet(int id, Point pos, Point sight, int iniciator_id): Object(Type::BULLET_OBJECT, id, pos, Model(7,7)),
                                                              sight(sight), speed(DEFAULT_BULLET_SPEED), iniciator_ID(iniciator_id) {};

    void update() override {
        if (state.get_state() == BulletState::ACTIVE) {
            position = position +  sight * speed;
        }
    }
    BulletState state;
    Point sight;
    int iniciator_ID;
    double speed;
};
