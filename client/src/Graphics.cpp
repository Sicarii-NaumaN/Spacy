#include "Graphics.h"

Graphics::Graphics(sf::RenderWindow &window, const Config &config) : window(window), config(config) {
    background_texture.loadFromFile(config.textures_path + "bg.jpg");
    player_texture.loadFromFile(config.textures_path + "plane_back_0.png");
    enemy_texture.loadFromFile(config.textures_path + "plane_front_0.jpg");

    player.setTexture(player_texture);
    player.resize(0.20, 0.20);
    player.setPosition(500, 400);
    enemy.setTexture(enemy_texture);


    setWindowIcon();
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
    int x1 = config.window_width / 2;
    int y1 = (config.window_height - config.table_height)  / 2 ;
    int width_top = config.table_width_top;

    int x2 = config.window_width/2;
    int y2 = (config.window_height + config.table_height)/2 + config.table_shift;
    int width_bot = config.table_width_bot;

    sf::RectangleShape background;

    background.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));

    sf::Texture texture;
    texture.loadFromFile(config.textures_path + "space.png");

    background.setTexture(&texture);
    window.draw(background);
    drawShape(background_texture,
              x1, y1, width_top,
              x2, y2, width_bot);
}

void Graphics::drawPlayer(int x, int y) {
    player.setPosition(x, y);
    player.draw(window, renderStates);
}

void Graphics::setWindowIcon() {
    sf::Image icon;
    icon.loadFromFile(config.textures_path + "icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}
