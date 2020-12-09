#ifndef SPACY_GRAPHICS_H
#define SPACY_GRAPHICS_H

#include <SFML/Graphics.hpp>
#include <PlayerModel.h>
#include <unordered_map>

class Graphics {
public:
    void drawShape(const sf::Texture& texture, int x1, int y1, int w1, int x2, int y2, int w2);
    void drawField();
//    void drawPlayer(const std::vector<PlayerInterface> &playerData);
//    void drawProjectile(const std::vector<BulletInterface> &);

    explicit Graphics(sf::RenderWindow &window);
private:

    int W = 1280;
    int H = 800;

    int TABLE_W1 = 200;
    int TABLE_W2 = 800;
    int TABLE_H = 550;

    sf::RenderWindow &window;
    sf::Texture background_texture;
    sf::Texture player_texture;
    sf::Texture enemy_player_texture;
    sf::Texture bullet_texture;
};

#endif //SPACY_GRAPHICS_H
