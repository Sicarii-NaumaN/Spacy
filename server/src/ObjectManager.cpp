#include <algorithm>
#include <include/ObjectManager.h>
#include <ObjectManager.h>

void ObjectManager::update_all_and_kill_dead_bullets() {
    // std::cout << "BLABLA " << objects.size() << std::endl;
    for (auto obj = objects.begin(); obj != objects.end();)
    {
        obj->second->update();
            obj++;
    }

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
