#ifndef SPACY_GRAPHICS_H
#define SPACY_GRAPHICS_H

#include <SFML/Graphics.hpp>
#include "PlayerModel.h"
#include "Utils.h"
#include <unordered_map>
#include "structConfig.h"

class Graphics {
public:
    void drawShape(const sf::Texture& texture, int x1, int y1, int w1, int x2, int y2, int w2);
    void drawField();
    void drawPlayer(int x, int y);
//    void drawProjectile(const std::vector<BulletInterface> &);
    void setWindowIcon();

    explicit Graphics(sf::RenderWindow &window, const Config &config);
private:
    struct Config config;

//    int W = 1280;
//    int H = 800;
//
//    int TABLE_W1 = 200;
//    int TABLE_W2 = 800;
//    int TABLE_H = 550;

    PlayerModel player;
    PlayerModel enemy;

    sf::RenderWindow &window;
    sf::RenderStates renderStates;

    sf::Texture background_texture;
    sf::Texture player_texture;
    sf::Texture enemy_texture;
    sf::Texture bullet_texture;

    Projector projector;
};

#endif //SPACY_GRAPHICS_H
