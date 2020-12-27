#ifndef SPACY_OBJECT_MANAGER_H
#define SPACY_OBJECT_MANAGER_H

#include <map>
#include <mutex>
#include <Object.h>
#include <thread>
#include <unordered_map>
#include <vector>
#include <list>

class ObjectManager
{
public:
    ObjectManager()
        : id_counter(0) {
        /*for (size_t i = 0; i< 4; i++) {
            objects1.push_back(0);
        }*/
       objects1.reserve(6);
    }
    void update_objects(const std::shared_ptr<Object> &changed_object, int i = -1);
    int pick_enable_id() const;
    void update_all_and_kill_dead_bullets();
    std::shared_ptr<Object> &get_object_by_id(int id);
    std::list<std::shared_ptr<Player>> get_users();
    std::vector<std::shared_ptr<Object> > &get_objects_by_map();


private:
    mutable int                                       id_counter;
    mutable std::mutex                                id_cointer_m;
    //std::unordered_map<int, std::shared_ptr<Object> > objects;
    std::vector<std::shared_ptr<Object>> objects1;
};

#endif // SPACY_OBJECT_MANAGER_H
