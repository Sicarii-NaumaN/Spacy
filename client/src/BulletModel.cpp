#include "BulletModel.h"


void BulletModel::draw(sf::RenderTarget &renderTarget,
                       sf::RenderStates renderStates)
{
    //sprite.scale(0.1, 0.1);

    sf::Transform transform;
    transform.translate(0, -100);

    renderStates.transform = transform;

    renderTarget.draw(sprite, renderStates);
}


void BulletModel::setTexture(const sf::Texture &texture)
{
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
}


void BulletModel::setPosition(float x, float y)
{
    position.x = x;
    position.y = y;
}


void BulletModel::setSpritePosition(float x, float y)
{
    sprite.setPosition(x, y);
}


void BulletModel::resize(float width_scale, float height_scale)
{
    sprite.setScale(width_scale, height_scale);
}
