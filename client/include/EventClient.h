#ifndef SPACY_EVENT_H
#define SPACY_EVENT_H
const static int DEFAULT_BULLET_SPEED_CLIENT = 10;
#include <map>

struct VectorInterface
{
    float x, y;
    VectorInterface(float xpos, float ypos)
        : x(xpos)
        , y(ypos) {}
};

struct EventInterface
{
    enum EventType
    {
        SHOT,
        KEYPRESSED
    };
    EventType type; // move, blink
    EventInterface(EventType t)
        : type(t) {}
};

struct KeyEvent : EventInterface
{
    enum KeyState
    {
        PRESSED,
        RELEASED
    };

    int      keyCode;
    int      mouse_x, mouse_y;
    KeyState state;
    KeyEvent(int keyCode, int mx, int my, KeyState state)
        : EventInterface(EventType::KEYPRESSED)
        , keyCode(keyCode)
        , mouse_x(mx)
        , mouse_y(my)
        , state(state) {}
};

struct KeyPressedEvent : KeyEvent
{
    KeyPressedEvent(int keyCode, int mx, int my)
        : KeyEvent(keyCode, mx, my, KeyEvent::KeyState::PRESSED) {}
};

struct KeyReleasedEvent : KeyEvent
{
    KeyReleasedEvent(int keyCode, int mx, int my)
        : KeyEvent(keyCode, mx, my, KeyEvent::KeyState::RELEASED) {}
};

struct ShotInterface : EventInterface
{
    int origin_x, origin_y;
    int mouse_x, mouse_y;
    ShotInterface(int ox, int oy, int mx, int my)
        : EventInterface(EventType::SHOT)
        , mouse_x(mx)
        , mouse_y(my)
        , origin_x(ox)
        , origin_y(oy) {}
};

struct ObjectInterface
{
    enum Type
    {
        PLAYER,
        BULLET,
        MAP
    };
    VectorInterface position;
    Type            type;
    int             ID;
    ObjectInterface(Type t, int id, VectorInterface pos)
        : type(t)
        , ID(id)
        , position(pos) {}
};

struct PlayerInterface : ObjectInterface
{
    int side;
    PlayerInterface(int id, int side, VectorInterface pos)
        : ObjectInterface(Type::PLAYER, id, pos)
        , side(side) {}
};


struct BulletInterface : ObjectInterface
{
    BulletInterface(int id, VectorInterface pos)
        : ObjectInterface(Type::BULLET, id, pos) {}
};

#endif // SPACY_EVENT_H
