#include <Event.h>

std::shared_ptr<Object> Move::process(std::shared_ptr<Object> obj, ObjectManager &objectmanager) {
    std::shared_ptr<Player> sh_player= std::static_pointer_cast<Player>(obj);
    Player player = *sh_player.get();

    switch (direction) {
        // TODO: Пересчет координат в трапецию
        // case UP: {
        //     player.position.y -= player.speed;
        //     break;
        // }
        // case DOWN:{
        //     player.position.y += player.speed;
        //     break;
        // }
        case LEFT:{
            player.setSpeed(-5, 0);
            // player.position.x += player.speed.x;
            break;
        }
        case RIGHT:{
            player.setSpeed(5, 0);
            //player.position.x += player.speed.y;
            break;
        }
        default:
            break;
    }
    //player.sight = player.normalize(this->sight);
    //sh_player->sight = sh_player->normalize(this->sight);
    return std::make_shared<Player>(player);
}

std::shared_ptr<Object> Shot::process(std::shared_ptr<Object> obj, ObjectManager &object_manager) {
    std::shared_ptr<Player> sh_player= std::static_pointer_cast<Player>(obj);
    Player player = *sh_player.get();

    if (sh_player->state_.is_shot_avaible()) {
        //sh_player->sight = player.normalize(sight);
        player.sight = sh_player->sight;
        Vector bullet_postiton = player.position + Vector(player.model.width / 2.0, player.model.height / 2.0);
        object_manager.update_objects(std::make_shared<Bullet>(object_manager.pick_enable_id(),
                                                              bullet_postiton, player.sight, player.ID));
        player.state_.shot();
        sh_player->state_.shot();
    }
    return std::make_shared<Player>(player);
}

std::shared_ptr<Object> KeyPressed::process(std::shared_ptr<Object> obj, ObjectManager &object_manager)
{
  std::shared_ptr<Player> sh_player= std::static_pointer_cast<Player>(obj);
  Player player = *sh_player.get();

  return std::make_shared<Player>(player);
}
