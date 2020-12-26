#include <algorithm>
#include <include/ObjectManager.h>
#include <ObjectManager.h>

void ObjectManager::update_all_and_kill_dead_bullets() {
    std::cout << "BLABLA " << objects.size() << std::endl;
    for (auto obj = objects.begin(); obj != objects.end();)
    {
        std::cout << "1";
        bool deleted = false;
        obj->second->update();
        std::cout << "2";
        switch (obj->second->type)
        {
        case Object::Type::BULLET:
            std::cout << "3";
            auto bullet = std::static_pointer_cast<Bullet>(obj->second);
            std::cout << "4";
            if (bullet->state == 0) {
                std::cout << "5";
                //deleted = true;
                std::cout << "before " << objects.size() << std::endl;
                //obj = this->objects.erase(obj);
                std::cout << "after " << objects.size() << std::endl;
                std::cout << "6";
            }
            break;
        }
        if (!deleted) {
            std::cout << "7";
            obj++;
        }
        std::cout << "8\n";
    }
    std::cout << "after all " << objects.size() << std::endl;
}

int ObjectManager::pick_enable_id() const
{
    std::lock_guard<std::mutex> lg(id_cointer_m);
    return(id_counter++);
}


std::unordered_map<int, std::shared_ptr<Object> > &ObjectManager::get_objects_by_map()
{
    return(objects);
}


std::shared_ptr<Object> &ObjectManager::get_object_by_id(int id)
{
    return(objects[id]);
}

void ObjectManager::update_objects(std::shared_ptr<Object> changed_object)
{
    objects[changed_object->ID] = changed_object;
}

std::list<std::shared_ptr<Player> > ObjectManager::get_users()
{
    std::list<std::shared_ptr<Player> > result;

    for (int i = 0; i < objects.size(); ++i)
    {
        if (objects.at(i)->type == Object::Type::PLAYER)
        {
            result.push_back(std::static_pointer_cast<Player>(objects.at(i)));
        }
    }

    return(result);
}
