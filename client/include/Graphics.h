#ifndef SPACY_GRAPHICS_H
#define SPACY_GRAPHICS_H

#include <SFML/Graphics.hpp>
#include "PlayerModel.h"
#include "Utils.h"
#include <unordered_map>
#include "structConfig.h"

class Graphics {
public:
    void drawShape(const sf::Texture& texture);
    void drawBackWall();
    void drawFrontWall();
    void drawSideWalls();
    void drawField();
    void drawPlayer();
    void movePlayer(float vx, float vy);
    void movePlayerTo(float x, float y);
//    void drawProjectile(const std::vector<BulletInterface> &);
    void setWindowIcon();

    explicit Graphics(sf::RenderWindow &window, const Config &config);
private:
    struct Config config;

    PlayerModel player;
    PlayerModel enemy;

    sf::RenderWindow &window;
    sf::RenderStates renderStates;

    sf::Texture background_texture;
    sf::Texture player_texture;
    sf::Texture enemy_texture;
    sf::Texture bullet_texture;
    sf::Texture metal_texture;
    sf::Texture metal_light_texture;

    sf::Transform transform;

    Projector projector;
};

#endif //SPACY_GRAPHICS_H
