#pragma once

#include <Object.h>
#include <ObjectManager.h>

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};
class Event
{
public:
    Event(int Player_ID)
        : IniciatorID(Player_ID) {}
    virtual std::shared_ptr<Object> process(std::shared_ptr<Object> obj, ObjectManager &objectmanager) = 0;

    int IniciatorID;
};

class Move : public Event
{
public:
    Move(int Player_ID, Direction dir)
        : Event(Player_ID)
        , direction(dir) {}
    std::shared_ptr<Object> process(std::shared_ptr<Object> obj, ObjectManager &objectmanager) override;

    Direction direction;
};

class Shot : public Event
{
public:
    Shot(int Iniciator_ID, int mx, int my, int ox, int oy)
        : Event(Iniciator_ID), origin_x(ox), origin_y(oy), mouse_x(mx), mouse_y(my){}

    int origin_x;
    int origin_y;
    int mouse_x;
    int mouse_y;
    std::shared_ptr<Object> process(std::shared_ptr<Object> obj, ObjectManager &objectmanager) override;
};

class KeyPressed : public Event
{
public:
    KeyPressed(int Player_ID, int key_code, int mx, int my, int state)
        : Event(Player_ID)
        , key_code(key_code)
        , mouse_x(mx)
        , mouse_y(my)
        , state(state) {}

    int key_code;
    int mouse_x;
    int mouse_y;
    int state;
    std::shared_ptr<Object> process(std::shared_ptr<Object> obj, ObjectManager &objectmanager) override;
};
