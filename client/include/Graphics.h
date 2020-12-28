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
    void drawMenu();
    void drawScore(std::string score1, std::string score2);
    void drawGates(int gates1_pos, int gates2_posx);

    void drawPlayer();
    void drawEnemy();

    void movePlayerTo(float x, float y);
    void moveEnemyTo(float x, float y);
    void setFlipped() {flipped = true;}

    void drawBullet(float x, float y, int state);

    void setWindowIcon();

    explicit Graphics(sf::RenderWindow &window, const Config &config, bool flipped = false);
    virtual ~Graphics() = default;

    sf::Vector2i invertPositionIfFlipped(sf::Vector2i pos);

    sf::Vector2f getPlayerPosition();
    sf::Vector2f getOriginPoint(sf::Vector2f origin) { return projector.getOriginPoint(origin); }
    sf::Vector2i getProjectedMousePosition(sf::Vector2i mouse);

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
    bool flipped;
};

#endif // SPACY_GRAPHICS_H
