#include "PlayerModel.h"

PlayerModel::PlayerModel(float startX, float startY, float width, float height,
                         float sightToX, float sightToY)
    : width(width)
    , height(height)
    , sightToX(sightToX)
    , sightToY(sightToY)
{
    position.x = startX;
    position.y = startY;
    sprite.setPosition(position.x, position.y);
}


void PlayerModel::draw(sf::RenderTarget &renderTarget,
                       sf::RenderStates renderStates)
{
    sprite.scale(0.2, 0.2);

    sf::Transform transform;
    transform.translate(0, -100);

    renderStates.transform = transform;

    renderTarget.draw(sprite, renderStates);
}


void PlayerModel::setTexture(const sf::Texture &texture)
{
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
}


void PlayerModel::setPosition(float x, float y)
{
    position.x = x;
    position.y = y;

    float wall_offset = 20;

    if (position.x > 1280 - wall_offset)
    {
        position.x = 1280 - wall_offset;
    }
    else if (position.x < 0 + wall_offset)
    {
        position.x = 0 + wall_offset;
    }

    if (position.y > 725)
    {
        position.y = 725;
    }
    else if (position.y < 550)
    {
        position.y = 550;
    }
}


void PlayerModel::setSpritePosition(float x, float y)
{
    sprite.setPosition(x, y);
}


void PlayerModel::resize(float width_scale, float height_scale)
{
    sprite.setScale(width_scale, height_scale);
}

PlayerModel::PlayerModel() = default;
