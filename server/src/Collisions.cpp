#include "Collisions.h"

std::vector<std::shared_ptr<Object>>
CollisionManager::check(const std::unordered_map<int, std::shared_ptr<Object>> &objects,
                        std::shared_ptr<Object> object) {
    std::vector<std::shared_ptr<Object>> result;
    for (auto& obj: objects) {
        if (collides(obj.second, object)) {
            if (obj.second->ID != object->ID) {
                result.push_back(obj.second);
            }
        }
    }
    return result;
}

bool CollisionManager::collides(std::shared_ptr<Object> lhs_obj, std::shared_ptr<Object> rhs_obj) const {
    return false;
}
