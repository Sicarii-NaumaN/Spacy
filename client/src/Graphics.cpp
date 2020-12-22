#include "Graphics.h"
#include "Utils.h"
#include <iostream>

Graphics::Graphics(sf::RenderWindow &window, const Config &config) : window(window), config(config) {
    background_texture.loadFromFile(config.textures_path + "bg.jpg");
    player_texture.loadFromFile(config.textures_path + "plane_back_0.png");
    enemy_texture.loadFromFile(config.textures_path + "plane_front_0.jpg");
    metal_light_texture.loadFromFile(config.textures_path + "metal_light.jpg");
    metal_texture.loadFromFile(config.textures_path + "metal.jpg");

    transform.translate(0, -100);

    player.setTexture(player_texture);
    player.resize(0.20, 0.20);
    player.setPosition(500, 400);
    enemy.setTexture(enemy_texture);

    // Параметры проецирования:
    // Угол наклона плоскости проецирования
    // Размеры окна
    projector = Projector(M_PI/6, config.window_width, config.window_height);

    setWindowIcon();
}

void Graphics::drawShape(const sf::Texture& texture) {
    sf::ConvexShape field(4);

    float w = config.window_width;
    float h = config.window_height;

    sf::Vector2f p1 = projector.projectPoint(0, 0);
    sf::Vector2f p2 = projector.projectPoint(0, h);
    sf::Vector2f p3 = projector.projectPoint(w, h);
    sf::Vector2f p4 = projector.projectPoint(w, 0);

    field.setPoint(0, p1);
    field.setPoint(1, p2);
    field.setPoint(2, p3);
    field.setPoint(3, p4);

    field.setTexture(&texture);
    window.draw(field, transform);
}

void Graphics::drawSideWalls() {
    float w = config.window_width;
    float h = config.window_height;

    sf::Vector2f p00 = projector.projectPoint(0, 0);
    sf::Vector2f p01 = projector.projectPoint(0, h);
    sf::Vector2f p10 = projector.projectPoint(w, h);
    sf::Vector2f p11 = projector.projectPoint(w, 0);

    float top_width = abs(p00.x - p11.x);
    float bottom_width = abs(p01.x - p10.x);
    float scale_factor = top_width / bottom_width;

    float h1 = 50;
    float h2 = h1 * scale_factor;

    sf::Vector2f t00 = sf::Vector2f(p00.x, p00.y - h2);
    sf::Vector2f t01 = sf::Vector2f(p01.x, p01.y - h1);
    sf::Vector2f t10 = sf::Vector2f(p10.x, p10.y - h1);
    sf::Vector2f t11 = sf::Vector2f(p11.x, p11.y - h2);

    sf::ConvexShape wall1(4);
    sf::ConvexShape wall3(4);

    wall1.setPoint(0, p00);
    wall1.setPoint(1, p01);
    wall1.setPoint(2, t01);
    wall1.setPoint(3, t00);

    wall3.setPoint(0, p10);
    wall3.setPoint(1, p11);
    wall3.setPoint(2, t11);
    wall3.setPoint(3, t10);

    wall1.setTexture(&metal_light_texture);
    wall3.setTexture(&metal_light_texture);

    window.draw(wall1, transform);
    window.draw(wall3, transform);
}

void Graphics::drawBackWall() {
  float w = config.window_width;
  float h = config.window_height;

  sf::Vector2f p00 = projector.projectPoint(0, 0);
  sf::Vector2f p01 = projector.projectPoint(0, h);
  sf::Vector2f p10 = projector.projectPoint(w, h);
  sf::Vector2f p11 = projector.projectPoint(w, 0);

  float top_width = abs(p00.x - p11.x);
  float bottom_width = abs(p01.x - p10.x);
  float scale_factor = top_width / bottom_width;

  float h1 = 50;
  float h2 = h1 * scale_factor;

  sf::Vector2f t00 = sf::Vector2f(p00.x, p00.y - h2);
  sf::Vector2f t11 = sf::Vector2f(p11.x, p11.y - h2);

  sf::ConvexShape wall4(4);

  wall4.setPoint(0, p11);
  wall4.setPoint(1, p00);
  wall4.setPoint(2, t00);
  wall4.setPoint(3, t11);

  wall4.setTexture(&metal_texture);

  window.draw(wall4, transform);
}

void Graphics::drawFrontWall() {
    float w = config.window_width;
    float h = config.window_height;

    sf::Vector2f p00 = projector.projectPoint(0, 0);
    sf::Vector2f p01 = projector.projectPoint(0, h);
    sf::Vector2f p10 = projector.projectPoint(w, h);
    sf::Vector2f p11 = projector.projectPoint(w, 0);

    float top_width = abs(p00.x - p11.x);
    float bottom_width = abs(p01.x - p10.x);
    float scale_factor = top_width / bottom_width;

    float h1 = 50;
    float h2 = h1 * scale_factor;

    sf::Vector2f t01 = sf::Vector2f(p01.x, p01.y - h1);
    sf::Vector2f t10 = sf::Vector2f(p10.x, p10.y - h1);

    sf::ConvexShape front_wall(4);

    front_wall.setPoint(0, p01);
    front_wall.setPoint(1, p10);
    front_wall.setPoint(2, t10);
    front_wall.setPoint(3, t01);

    front_wall.setTexture(&metal_texture);

    window.draw(front_wall, transform);
}

void Graphics::drawField() {
    sf::RectangleShape background;

    background.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));

    sf::Texture texture;
    sf::Texture wall_texture;

    texture.loadFromFile(config.textures_path + "space.png");
    wall_texture.loadFromFile(config.textures_path + "metal.jpg");

    background.setTexture(&texture);
    window.draw(background);
    drawShape(background_texture);
    drawBackWall();
    drawSideWalls();
}

void Graphics::movePlayer(float vx, float vy) {
  auto pos = player.getPosition();
  player.setPosition(pos.x + vx, pos.y + vy);
}

void Graphics::movePlayerTo(float x, float y) {
  player.setPosition(x, y);
}

void Graphics::drawPlayer() {
    auto pos = player.getPosition();
    float x = pos.x;
    float y = pos.y;
    float player_width = player.getWidth();

    sf::Vector2f projected_position = projector.projectPoint(player.getPosition());
    player.setSpritePosition(projected_position.x, projected_position.y);

    float new_width = projector.projectLength(sf::Vector2f(x, y), player_width);
    float scale_factor = new_width / player_width;

    player.resize(scale_factor);
    player.draw(window, renderStates);
}

void Graphics::setWindowIcon() {
    sf::Image icon;
    icon.loadFromFile(config.textures_path + "icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}
