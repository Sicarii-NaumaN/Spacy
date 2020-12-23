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
    Shot(int Iniciator_ID)
        : Event(Iniciator_ID) {}
    std::shared_ptr<Object> process(std::shared_ptr<Object> obj, ObjectManager &objectmanager) override;
};

class KeyPressed : public Event
{
public:
    KeyPressed(int Player_ID, int key_code)
        : Event(Player_ID)
        , key_code(key_code) {}
    int key_code;
    std::shared_ptr<Object> process(std::shared_ptr<Object> obj, ObjectManager &objectmanager) override;
};
