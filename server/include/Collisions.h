#ifndef SPACY_COLLISIONS_H
#define SPACY_COLLISIONS_H

#include <vector>
#include <unordered_map>
#include <Object.h>
#include <cmath>

class CollisionManager {
public:
    CollisionManager() = default;
    void check(const std::unordered_map<int, std::shared_ptr<Object>>& objects,
                                                                std::shared_ptr<Object> object);

    bool is_object_collided(const std::unordered_map<int, std::shared_ptr<Object>>& objects,
                            std::shared_ptr<Object> object) const;

    void resolve_collision(std::shared_ptr<Player> player, std::shared_ptr<Bullet> bullet);
private:
    static int COLLISION_RADIUS = 60;
    bool collides(std::shared_ptr<Player> player, std::shared_ptr<Bullet> bullet) const ;


};


#endif //SPACY_COLLISIONS_H
