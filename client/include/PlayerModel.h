#ifndef PLAYERMODEL_H_INCLUDED
#define PLAYERMODEL_H_INCLUDED

#include <iostream>
#include <SFML/Graphics.hpp>

class PlayerModel
{
public:
    PlayerModel();

    PlayerModel(float startX, float startY, float width, float height, float sightToX, float sightToY);

    virtual ~PlayerModel() = default;

    virtual void draw(sf::RenderTarget &renderTarget, sf::RenderStates renderStates);

    void resize(float scale) { resize(scale, scale); }
    void resize(float width_scale, float height_scale);
    void setTexture(const sf::Texture &texture);
    void setPosition(float x, float y);
    void setSpritePosition(float x, float y);

    int getID() { return(id); }

    sf::Vector2f getPosition() { return(position); }
    sf::Vector2f getSpritePosition() { return(sprite.getPosition()); }


    float getWidth()
    {
        return(sprite.getTexture()->getSize().x * sprite.getScale().x);
    }

private:
    int          id;
    sf::Sprite   sprite;
    sf::Vector2f position;
    float        width;
    float        height;
    float        sightToX;
    float        sightToY;
};

#endif
