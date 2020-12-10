#ifndef PLAYERMODEL_H_INCLUDED
#define PLAYERMODEL_H_INCLUDED

#include <SFML/Graphics.hpp>

#include <iostream>
#include <NetClient.h>

struct EventInterface {
    enum EventType {
        move,
        shot
    };
    EventType type; //move
    sf::Vector2f sight;
    EventInterface(EventType t, sf::Vector2f s): type(t), sight(s) {}
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

class PlayerModel {
public:
    enum EventType {
        move,
        shot
    };
    PlayerModel();

    PlayerModel(float startX, float startY, float width, float height, float sightToX, float sightToY);

    virtual ~PlayerModel();

    virtual void draw(sf::RenderTarget &renderTarget, sf::RenderStates renderStates);

    void setTexture(const sf::Texture &texture);
    void setPosition(float x, float y);

    int getID() { return id; }

private:
    NetClient network;
    int id;
    sf::Sprite sprite;
    sf::Vector2f position;
    float width;
    float height;
    float sightToX;
    float sightToY;
};


#endif