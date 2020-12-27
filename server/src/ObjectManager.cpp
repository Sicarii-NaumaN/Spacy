#include <algorithm>
#include <include/ObjectManager.h>
#include <ObjectManager.h>

void ObjectManager::update_all_and_kill_dead_bullets() {
    std::vector<std::shared_ptr<Object>>::iterator obj;
    std::cout << "BLABLA " << objects1.size() << std::endl;
    for (  size_t i = 2; i < objects1.size(); i++ )
    {
        std::cout << "1";
        bool deleted = false;
        objects1[i]->update();
        std::cout << "2";
        switch (objects1[i]->type)
        {
        case Object::Type::BULLET:
            std::cout << "3";
            auto bullet = std::static_pointer_cast<Bullet>(objects1[i]);
            std::cout << "4";
            if (bullet->state == 0) {
                std::cout << "5";
                deleted = true;
                std::cout << "before " << objects1.size() << std::endl;
                /*if(obj != objects.end() && objects.size() > 1) {
                    auto new_obj(obj++);
                    obj = this->objects.erase(obj);

                    obj = new_obj;
                }*/
                this->objects1.erase(objects1.begin()+i);
                //if (obj == objects.end())
                //    continue;
                //obj++;

                std::cout << "after " << objects1.size() << std::endl;
                std::cout << "6";
            }
            break;
        }
        if (!deleted) {
            std::cout << "7";
            //obj++;
        }
        std::cout << "8\n";
    }
    std::cout << "after all " << objects1.size() << std::endl;
}

int ObjectManager::pick_enable_id() const
{
    std::lock_guard<std::mutex> lg(id_cointer_m);
    return(id_counter++);
}


std::vector<std::shared_ptr<Object> > &ObjectManager::get_objects_by_map()
{
    return(objects1);
}


std::shared_ptr<Object> &ObjectManager::get_object_by_id(int id)
{
    //return(objects[id]);
    return (objects1[id]);
}

void ObjectManager::update_objects(const std::shared_ptr<Object> &changed_object,int i) {
    if (i != -1) {
        auto buf = std::static_pointer_cast<Player>(changed_object);
        objects1[changed_object->ID] = buf;
        return;
    }


        objects1.push_back(changed_object);
        return;

}

/*std::list<std::shared_ptr<Player> > ObjectManager::get_users()
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
*/