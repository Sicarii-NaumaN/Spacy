#include "Graphics.h"
#include "Utils.h"
#include <iostream>

Graphics::Graphics(sf::RenderWindow &window, const Config &config) : window(window), config(config) {
    background_texture.loadFromFile(config.textures_path + "bg.jpg");
    player_texture.loadFromFile(config.textures_path + "plane_back_0.png");
    enemy_texture.loadFromFile(config.textures_path + "plane_front_0.jpg");

    player.setTexture(player_texture);
    player.resize(0.20, 0.20);
    player.setPosition(500, 400);
    enemy.setTexture(enemy_texture);

    projector = Projector(M_PI/6, config.window_width, config.window_height);

    setWindowIcon();
}

void Graphics::drawShape(const sf::Texture& texture,
                         int x1, int y1, int w1,
                         int x2, int y2, int w2) {
    sf::ConvexShape field(4);

    Point p1 = projector.projectPoint(Point(0, 0));
    Point p2 = projector.projectPoint(Point(0, config.window_height));
    Point p3 = projector.projectPoint(Point(config.window_width, config.window_height));
    Point p4 = projector.projectPoint(Point(config.window_width, 0));

    field.setPoint(0, sf::Vector2f(p1.x, p1.y));
    field.setPoint(1, sf::Vector2f(p2.x, p2.y));
    field.setPoint(2, sf::Vector2f(p3.x, p3.y));
    field.setPoint(3, sf::Vector2f(p4.x, p4.y));

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
    float player_width = player.getWidth() * 0.3;

    Point projected_position = projector.projectPoint(Point(x, y));
    player.setSpritePosition(projected_position.x, projected_position.y);

    float new_width = projector.projectLength(Point(x, y), player_width);
    float scale_factor = new_width / player_width * 0.3;

    player.resize(scale_factor, scale_factor);
    player.draw(window, renderStates);
}

void Graphics::setWindowIcon() {
    sf::Image icon;
    icon.loadFromFile(config.textures_path + "icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}
