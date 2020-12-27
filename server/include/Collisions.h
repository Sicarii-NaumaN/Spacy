#ifndef SPACY_COLLISIONS_H
#define SPACY_COLLISIONS_H

#include <vector>
#include <unordered_map>
#include <Object.h>

class CollisionManager {
public:
    CollisionManager() = default;
    std::vector<std::shared_ptr<Object>>check(const std::unordered_map<int, std::shared_ptr<Object>>& objects,
                                                                std::shared_ptr<Object> object);

    bool is_object_collided(const std::unordered_map<int, std::shared_ptr<Object>>& objects,
                            std::shared_ptr<Object> object) const;

    void resolve_collision(std::shared_ptr<Object> lhs_obj, std::shared_ptr<Object> rhs_obj);
private:

    bool collides(std::shared_ptr<Object> lhs_obj, std::shared_ptr<Object> rhs_obj) const ;

    void resolve_collision(std::shared_ptr<Player> player, std::shared_ptr<Obstruction> obstruct);
    void resolve_collision(std::shared_ptr<Player> player, std::shared_ptr<Bullet> bullet);
    void resolve_collision(std::shared_ptr<Bullet> bullet, std::shared_ptr<Obstruction> obstruct);
    void resolve_collision(std::shared_ptr<Obstruction> obstruct, std::shared_ptr<Player> player);
    void resolve_collision(std::shared_ptr<Bullet> bullet, std::shared_ptr<Player> player);
    void resolve_collision(std::shared_ptr<Obstruction> obstruct, std::shared_ptr<Bullet> bullet);

};


#endif //SPACY_COLLISIONS_H
