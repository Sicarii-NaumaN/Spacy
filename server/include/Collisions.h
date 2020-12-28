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

    void gates(std::shared_ptr<Object> object, std::shared_ptr<GameStatistics> stat);

private:
    const static int COLLISION_RADIUS = 80;
    bool collides(std::shared_ptr<Player> player, std::shared_ptr<Bullet> bullet) const ;


};


#endif //SPACY_COLLISIONS_H
