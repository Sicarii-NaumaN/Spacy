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
        : id_counter(0) {}
    void update_objects(std::shared_ptr<Object> changed_object);
    std::shared_ptr<Object> &get_object_by_id(int id);
    std::list<std::shared_ptr<Player>> get_users();
    std::unordered_map<int, std::shared_ptr<Object> > &get_objects_by_map();
    int pick_enable_id() const;

private:
    mutable int                                       id_counter;
    mutable std::mutex                                id_cointer_m;
    std::unordered_map<int, std::shared_ptr<Object> > objects;
};

#endif // SPACY_OBJECT_MANAGER_H
