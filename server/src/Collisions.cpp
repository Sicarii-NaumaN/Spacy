#include "Collisions.h"

void CollisionManager::check(const std::unordered_map<int, std::shared_ptr<Object>> &objects,
                        std::shared_ptr<Object> object) {

    std::vector<std::shared_ptr<Object>> result;

    auto bullet = std::static_pointer_cast<Bullet>(object);

    if(bullet->state == 0)
        return; // неактивные пули не участвуют в коллизиях

    for (auto &obj: objects) {
        if (obj.second->type == Object::PLAYER) {
            auto player = std::static_pointer_cast<Player>(obj.second);
            if (collides(player, bullet) && player->ID != bullet->iniciator_ID) {
                // std::cout << "BULLET COLLIDED\n";
                bullet->state = 0;
                return; //Выходим из функции т.к одновременная коллизия с двумя объектами невозможна
            }
        }
    }


}

//void CollisionManager::resolve_collision(std::shared_ptr<Player> player, std::shared_ptr<Bullet> bullet) {
//    std::cout << "\n\n\n\n\n\n[COLLISION MANAGER] resolve func\n\n\n\n\n\n" << std::endl;
//
//}

bool CollisionManager::collides(std::shared_ptr<Player> player, std::shared_ptr<Bullet> bullet) const {
    return std::abs(player->position.x - bullet->position.x) <= 60
            && std::abs(player->position.y - bullet->position.y) <= 60;
}

void CollisionManager::gates(std::shared_ptr<Object> object, std::shared_ptr<GameStatistics> stat) {
    auto bullet = std::static_pointer_cast<Bullet>(object);

    if(bullet->state == 0)
        return; // неактивные пули не участвуют в коллизиях

    if (std::abs(640 - bullet->position.x) < 70 && std::abs(50 - bullet->position.y) < 20) {
        stat->addPoint(0);
        bullet->state = 0;
        return;
    }

    if (std::abs(640 - bullet->position.x) < 70 && std::abs(750 - bullet->position.y) < 20 ) {
        stat->addPoint(1);
        bullet->state = 0;
        return;
    }
}
