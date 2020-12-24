#include "Graphics.h"

Graphics::Graphics(sf::RenderWindow &window, const Config &config, bool flipped)
    : window(window)
    , config(config)
    , flipped(flipped)
{
    background_texture.loadFromFile(config.textures_path + "bg.jpg");

    player_texture[0].loadFromFile(config.textures_path + "left-5.png");
    player_texture[1].loadFromFile(config.textures_path + "left-4.png");
    player_texture[2].loadFromFile(config.textures_path + "left-3.png");
    player_texture[3].loadFromFile(config.textures_path + "left-2.png");
    player_texture[4].loadFromFile(config.textures_path + "left-1.png");
    player_texture[5].loadFromFile(config.textures_path + "center.png");
    player_texture[6].loadFromFile(config.textures_path + "right-1.png");
    player_texture[7].loadFromFile(config.textures_path + "right-2.png");
    player_texture[8].loadFromFile(config.textures_path + "right-3.png");
    player_texture[9].loadFromFile(config.textures_path + "right-4.png");
    player_texture[10].loadFromFile(config.textures_path + "right-5.png");

    enemy_texture[0].loadFromFile(config.textures_path + "back-left-5.png");
    enemy_texture[1].loadFromFile(config.textures_path + "back-left-4.png");
    enemy_texture[2].loadFromFile(config.textures_path + "back-left-3.png");
    enemy_texture[3].loadFromFile(config.textures_path + "back-left-2.png");
    enemy_texture[4].loadFromFile(config.textures_path + "back-left-1.png");
    enemy_texture[5].loadFromFile(config.textures_path + "back-center.png");
    enemy_texture[6].loadFromFile(config.textures_path + "back-right-1.png");
    enemy_texture[7].loadFromFile(config.textures_path + "back-right-2.png");
    enemy_texture[8].loadFromFile(config.textures_path + "back-right-3.png");
    enemy_texture[9].loadFromFile(config.textures_path + "back-right-4.png");
    enemy_texture[10].loadFromFile(config.textures_path + "back-right-5.png");

    //    enemy_texture.loadFromFile(config.textures_path + "front.png");

    metal_light_texture.loadFromFile(config.textures_path + "metal_light.jpg");
    metal_texture.loadFromFile(config.textures_path + "metal.jpg");

    bullet_texture.loadFromFile(config.textures_path + "bullet.png");

    transform.translate(0, -100);

    player.setTexture(player_texture[5]);

    enemy.setTexture(enemy_texture[5]);

    // Параметры проецирования:
    // Угол наклона плоскости проецирования
    // Размеры окна
    projector = Projector(M_PI / 5, config.field_width, config.field_height);

    setWindowIcon();
}


sf::Vector2f Graphics::getPlayerPosition() {
    return player.getPosition();
}

void Graphics::drawGates() {
    sf::CircleShape gates;
    gates.setRadius(30.0);
    gates.setPosition(1290, 400);
    window.draw(gates);
}

void Graphics::drawShape(const sf::Texture &texture)
{
    sf::ConvexShape field(4);

    float           w = config.window_width;
    float           h = config.window_height;

    auto            p1 = projector.projectPoint(0, 0);
    auto            p2 = projector.projectPoint(0, h);
    auto            p3 = projector.projectPoint(w, h);
    auto            p4 = projector.projectPoint(w, 0);

    field.setPoint(0, p1);
    field.setPoint(1, p2);
    field.setPoint(2, p3);
    field.setPoint(3, p4);

    field.setTexture(&texture);
    window.draw(field, transform);
}


void Graphics::drawSideWalls()
{
    float           w = config.window_width;
    float           h = config.window_height;

    auto            p00 = projector.projectPoint(0, 0);
    auto            p01 = projector.projectPoint(0, h);
    auto            p10 = projector.projectPoint(w, h);
    auto            p11 = projector.projectPoint(w, 0);

    float           top_width    = abs(p00.x - p11.x);
    float           bottom_width = abs(p01.x - p10.x);
    float           scale_factor = top_width / bottom_width;

    float           h1 = 50;
    float           h2 = h1 * scale_factor;

    auto            t00 = sf::Vector2f(p00.x, p00.y - h2);
    auto            t01 = sf::Vector2f(p01.x, p01.y - h1);
    auto            t10 = sf::Vector2f(p10.x, p10.y - h1);
    auto            t11 = sf::Vector2f(p11.x, p11.y - h2);

    sf::ConvexShape left_wall(4);
    sf::ConvexShape right_wall(4);

    left_wall.setPoint(0, p00);
    left_wall.setPoint(1, p01);
    left_wall.setPoint(2, t01);
    left_wall.setPoint(3, t00);

    right_wall.setPoint(0, p10);
    right_wall.setPoint(1, p11);
    right_wall.setPoint(2, t11);
    right_wall.setPoint(3, t10);

    left_wall.setTexture(&metal_light_texture);
    right_wall.setTexture(&metal_light_texture);

    window.draw(left_wall, transform);
    window.draw(right_wall, transform);
}


void Graphics::drawBackWall()
{
    float           w = config.window_width;
    float           h = config.window_height;

    auto            p00 = projector.projectPoint(0, 0);
    auto            p01 = projector.projectPoint(0, h);
    auto            p10 = projector.projectPoint(w, h);
    auto            p11 = projector.projectPoint(w, 0);

    float           top_width    = abs(p00.x - p11.x);
    float           bottom_width = abs(p01.x - p10.x);
    float           scale_factor = top_width / bottom_width;

    float           h1 = 50;
    float           h2 = h1 * scale_factor;

    auto            t00 = sf::Vector2f(p00.x, p00.y - h2);
    auto            t11 = sf::Vector2f(p11.x, p11.y - h2);

    sf::ConvexShape back_wall(4);

    back_wall.setPoint(0, p11);
    back_wall.setPoint(1, p00);
    back_wall.setPoint(2, t00);
    back_wall.setPoint(3, t11);

    back_wall.setTexture(&metal_texture);

    window.draw(back_wall, transform);
}


void Graphics::drawFrontWall()
{
    float           w = config.window_width;
    float           h = config.window_height;

    auto            p00 = projector.projectPoint(0, 0);
    auto            p01 = projector.projectPoint(0, h);
    auto            p10 = projector.projectPoint(w, h);
    auto            p11 = projector.projectPoint(w, 0);

    float           top_width    = abs(p00.x - p11.x);
    float           bottom_width = abs(p01.x - p10.x);
    float           scale_factor = top_width / bottom_width;

    float           h1 = 50;
    float           h2 = h1 * scale_factor;

    auto            t01 = sf::Vector2f(p01.x, p01.y - h1);
    auto            t10 = sf::Vector2f(p10.x, p10.y - h1);

    sf::ConvexShape front_wall(4);

    front_wall.setPoint(0, p01);
    front_wall.setPoint(1, p10);
    front_wall.setPoint(2, t10);
    front_wall.setPoint(3, t01);

    front_wall.setTexture(&metal_texture);

    window.draw(front_wall, transform);
}


void Graphics::drawField()
{
    sf::RectangleShape background;

    background.setSize(
    {
        (float)window.getSize().x, (float)window.getSize().y
    });

    sf::Texture texture;
    sf::Texture wall_texture;

    texture.loadFromFile(config.textures_path + "space.png");
    wall_texture.loadFromFile(config.textures_path + "metal.jpg");

    background.setTexture(&texture);
    window.draw(background);

    drawShape(background_texture); // Стол
    drawBackWall();                // Задняя стенка
    drawSideWalls();               // Боковые стены
}


void Graphics::movePlayerTo(float x, float y)
{
    player.setPosition(x, y);
}


void Graphics::drawPlayer()
{
    auto  pos          = player.getPosition();
    float x            = pos.x;
    float y            = pos.y;
    float player_width = player.getWidth();

    auto  projected_position = projector.projectPoint(player.getPosition());

    player.setSpritePosition(projected_position.x, projected_position.y);

    float new_width    = projector.projectLength(sf::Vector2f(x, y), player_width);
    float scale_factor = new_width / player_width;

    player.resize(scale_factor);
    player.setTexture(player_texture[(int)(player.getPosition().x / 117)]);
    player.draw(window, renderStates);
}


void Graphics::setWindowIcon()
{
    sf::Image icon;

    icon.loadFromFile(config.textures_path + "icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}


void Graphics::drawBullet(float x, float y)
{
    BulletModel bullet;

    bullet.setTexture(bullet_texture);

    float bullet_width = bullet.getWidth();

    auto  projected_position = projector.projectPoint(sf::Vector2f(x, y));

    bullet.setSpritePosition(projected_position.x, projected_position.y);

    float new_width    = projector.projectLength(sf::Vector2f(x, y), bullet_width);
    float scale_factor = new_width / bullet_width;
    bullet.resize(scale_factor);

    bullet.draw(window, renderStates);
}


void Graphics::drawEnemy()
{
    auto  pos         = enemy.getPosition();
    float x           = pos.x;
    float y           = pos.y;
    float enemy_width = enemy.getWidth();

    auto  projected_position = projector.projectPoint(enemy.getPosition());

    enemy.setSpritePosition(projected_position.x, projected_position.y);

    float new_width    = projector.projectLength(sf::Vector2f(x, y), enemy_width);
    float scale_factor = new_width / enemy_width;

    enemy.resize(scale_factor);
    enemy.setTexture(enemy_texture[(int)(enemy.getPosition().x / 117)]);
    enemy.draw(window, renderStates);
}


void Graphics::moveEnemyTo(float x, float y)
{
    float w = config.window_width;
    float h = config.window_height;

    enemy.setPosition(w - x, h - y);
}
