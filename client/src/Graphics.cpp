#include "Graphics.h"

Graphics::Graphics(sf::RenderWindow &window) : window(window) {
    background_texture.loadFromFile("../client/textures/bg.jpg");
}

void Graphics::drawShape(const sf::Texture& texture,
                         int x1, int y1, int w1,
                         int x2, int y2, int w2) {
    sf::ConvexShape field(4);
    field.setPoint(0, sf::Vector2f(x1 - w1, y1));
    field.setPoint(1, sf::Vector2f(x2 - w2, y2));
    field.setPoint(2, sf::Vector2f(x2 + w2, y2));
    field.setPoint(3, sf::Vector2f(x1 + w1, y1));

    sf::Texture bg;
    field.setTexture(&texture);

    window.draw(field);
}

void Graphics::drawField() {
    int field_shift = 50;
    drawShape(background_texture,
              W/2, H/2 - TABLE_H/2, TABLE_W1,
              W/2, H/2 + TABLE_H/2 + field_shift, TABLE_W2);
}
