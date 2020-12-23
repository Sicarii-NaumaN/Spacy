#ifndef SPACY_GRAPHICS_H
#define SPACY_GRAPHICS_H

#include "BulletModel.h"
#include "PlayerModel.h"
#include "structConfig.h"
#include "Utils.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <unordered_map>

class Graphics
{
public:
    void drawShape(const sf::Texture &texture);

    void drawBackWall();
    void drawFrontWall();
    void drawSideWalls();
    void drawField();

    void drawPlayer();
    void drawEnemy();

    void movePlayerTo(float x, float y);
    void moveEnemyTo(float x, float y);

    void drawBullet(float x, float y);

    void setWindowIcon();

    explicit Graphics(sf::RenderWindow &window, const Config &config);
    virtual ~Graphics() = default;

private:
    struct Config    config;

    PlayerModel      player;
    PlayerModel      enemy;

    sf::RenderWindow &window;
    sf::RenderStates renderStates;

    sf::Texture      background_texture;
    sf::Texture      player_texture[11];
    sf::Texture      enemy_texture[11];
    sf::Texture      bullet_texture;
    sf::Texture      metal_texture;
    sf::Texture      metal_light_texture;

    sf::Transform    transform;

    Projector        projector;
};

#endif // SPACY_GRAPHICS_H
