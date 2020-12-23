#ifndef SPACY_BULLETMODEL_H
#define SPACY_BULLETMODEL_H

#include <SFML/Graphics.hpp>

class BulletModel{
public:
    BulletModel() = default;
    virtual ~BulletModel() = default;

    virtual void draw(sf::RenderTarget &renderTarget, sf::RenderStates renderStates);

    void resize(float scale) { resize(scale, scale); }
    void resize(float width_scale, float height_scale);
    void setTexture(const sf::Texture &texture);
    void setPosition(float x, float y);
    void setSpritePosition(float x, float y);

    sf::Vector2f getPosition() {return position; }
    sf::Vector2f getSpritePosition() { return sprite.getPosition(); }
    float getWidth() { return sprite.getTexture()->getSize().x * sprite.getScale().x;}

private:
    sf::Sprite sprite;
    sf::Vector2f position;

    float sightToX;
    float sightToY;

    int player_id;
};


#endif //SPACY_BULLETMODEL_H
