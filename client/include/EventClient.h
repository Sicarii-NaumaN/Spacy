#ifndef SPACY_EVENT_H
#define SPACY_EVENT_H
const static int DEFAULT_BULLET_SPEED_CLIENT = 10;
#include <map>

struct PointInterface {
    double x, y;
    PointInterface(double xpos, double ypos): x(xpos), y(ypos) {}
};

struct VectorInterface {
    PointInterface from, to;
    VectorInterface(PointInterface f, PointInterface t):from(f), to(t){}
};

struct ModelInterface {
    int height, width;
    ModelInterface(int h, int w):height(h), width(w) {}
};

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct MousePosition {
    int x;
    int y;
};


struct EventInterface {
    enum EventType {
        move,
        blink,
        shot
    };
    EventType type; //move, blink
    VectorInterface sight;
    EventInterface(EventType t, VectorInterface s): type(t), sight(s) {}
};

struct MoveInterface: EventInterface{
    Direction direction;
    MoveInterface(EventType t, VectorInterface s, Direction dir):EventInterface(t, s), direction(dir) {}
};

struct ShotInterface: EventInterface{
    ShotInterface(EventType t, VectorInterface s):EventInterface(t, s) {}
};


struct ObjectInterface {
    enum Type {
        STATIC_OBJECT,
        PLAYER_OBJECT,
        BULLET_OBJECT,
        MAP_OBJECT
    };
    PointInterface position;
    ModelInterface model;
    Type type;
    int ID;
    ObjectInterface(Type t, int id, PointInterface pos, ModelInterface mod):type(t), ID(id), position(pos), model(mod) {}

};

struct PlayerInterface:ObjectInterface {
    VectorInterface sight;
    int speed;
    enum State {
        STATE_STANDING,
        STATE_FLYING
    };
    State state_;
    PlayerInterface(Type t, int id, PointInterface pos, ModelInterface mod,  VectorInterface sight): ObjectInterface(t, id, pos, mod),
                                                                                                     sight(sight), speed(50) {}

};


struct MapInterface:ObjectInterface {
    int layers_count;
    double ring_radius;
    std::map<int, int> players_pts;
    MapInterface(int id, int layers_count, double ring_radius, std::map<int, int> players_pts):
            ObjectInterface(Type::MAP_OBJECT, id, PointInterface(0, 0), ModelInterface(0, 0)),
            layers_count(layers_count), ring_radius(ring_radius), players_pts(std::move(players_pts)){}
};

struct ObstructionInterface:ObjectInterface {
    ObstructionInterface(Type t, int id, PointInterface pos, ModelInterface mod): ObjectInterface(t, id, pos, mod) {}
};


struct BulletStateInterface {
    enum State {
        ACTIVE,
        INACTIVE
    };
    BulletStateInterface(): state_(State::ACTIVE), live_tick(0) {};
    int live_tick;
    State state_;
};

struct BulletInterface:ObjectInterface {

    BulletInterface(int id, PointInterface pos, int iniciator_id): ObjectInterface(Type::BULLET_OBJECT, id, pos, ModelInterface(15,15)),
                                                                   speed(DEFAULT_BULLET_SPEED_CLIENT), iniciator_ID(iniciator_id) {};
    BulletStateInterface state;
    int iniciator_ID;
    int speed;
};

#endif //SPACY_EVENT_H
