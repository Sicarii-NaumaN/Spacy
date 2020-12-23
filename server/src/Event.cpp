#include <Event.h>
#include <iostream>

std::shared_ptr<Object> Shot::process(std::shared_ptr<Object> obj, ObjectManager &object_manager) {
    std::shared_ptr<Player> sh_player= std::static_pointer_cast<Player>(obj);
    Player player = *sh_player.get();

    if (sh_player->state_.is_shot_avaible()) {
        //sh_player->sight = player.normalize(sight);
        Vector bullet_postiton = player.position + Vector(player.model.width / 2.0, player.model.height / 2.0);
        object_manager.update_objects(std::make_shared<Bullet>(object_manager.pick_enable_id(),
                                                              bullet_postiton, player.speed, player.ID));
        player.state_.shot();
        sh_player->state_.shot();
    }
    return std::make_shared<Player>(player);
}

std::shared_ptr<Object> KeyPressed::process(std::shared_ptr<Object> obj, ObjectManager &object_manager)
{
  std::shared_ptr<Player> sh_player= std::static_pointer_cast<Player>(obj);
  Player player = *sh_player.get();

  float defaultSpeed = 5;

  std::cout << "HELLO BLAYT\n";

  player.setSpeed(defaultSpeed, 0);
  player.update();
  std::cout << "SDLFKJSDLF" << player.position.x << ' ' << player.position.y << std::endl;
  object_manager.update_objects(std::make_shared<Player>(player));

  return std::make_shared<Player>(player);
}
