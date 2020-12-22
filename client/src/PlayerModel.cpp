#include "PlayerModel.h"

PlayerModel::PlayerModel(float startX, float startY, float width, float height, float sightToX, float sightToY)
        : width(width), height(height), sightToX(sightToX), sightToY(sightToY) {
    position.x = startX;
    position.y = startY;
    sprite.setPosition(position.x, position.y);
}

PlayerModel::~PlayerModel() = default;

void PlayerModel::draw(sf::RenderTarget &renderTarget, sf::RenderStates renderStates) {
    renderTarget.draw(sprite);
}

void PlayerModel::setTexture(const sf::Texture &texture) {
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x/2, texture.getSize().y/2);
}

void PlayerModel::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
}

void PlayerModel::setSpritePosition(float x, float y) {
  sprite.setPosition(x, y);
}

void PlayerModel::resize(float width_scale, float height_scale) {
    sprite.setScale(width_scale, height_scale);
}

PlayerModel::PlayerModel() = default;
