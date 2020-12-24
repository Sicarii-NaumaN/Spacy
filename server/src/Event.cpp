#include <Event.h>
#include <iostream>


std::shared_ptr<Object> Shot::process(std::shared_ptr<Object> obj,
                                      ObjectManager           &object_manager)
{
    std::shared_ptr<Player> sh_player = std::static_pointer_cast<Player>(obj);
    Player                  player    = *sh_player.get();

    if (sh_player->state_.is_shot_avaible())
    {
        // sh_player->sight = player.normalize(sight);
        Vector bullet_postiton =
            player.position +
            Vector(player.model.width / 2.0, player.model.height / 2.0);
        object_manager.update_objects(
            std::make_shared<Bullet>(object_manager.pick_enable_id(),
                                     bullet_postiton, player.speed, player.ID));
        player.state_.shot();
        sh_player->state_.shot();
    }
    return(std::make_shared<Player>(player));
}


std::shared_ptr<Object> KeyPressed::process(std::shared_ptr<Object> obj,
                                            ObjectManager           &object_manager)
{
    std::shared_ptr<Player> sh_player = std::static_pointer_cast<Player>(obj);

    Player                  player = *sh_player.get();

    float defaultSpeed = 10;
    if (state == 1)
        defaultSpeed = 0;

    std::cout << "KEYSTATE IS " << state << std::endl;


    //WASD - 0123
    switch (key_code)
    {
    case 0:
        player.setSpeedY(-defaultSpeed);
        player.setSpeedX(0);
        break;

    case 1:
        player.setSpeedX(-defaultSpeed);
        player.setSpeedY(0);
        break;

    case 2:
        player.setSpeedY(defaultSpeed);
        player.setSpeedX(0);
        break;

    case 3:
        player.setSpeedX(defaultSpeed);
        player.setSpeedY(0);
        break;
    }

    std::cout << "SDLFKJSDLF" << player.position.x << ' ' << player.position.y
              << std::endl;
    object_manager.update_objects(std::make_shared<Player>(player));

    return(std::make_shared<Player>(player));
} // KeyPressed::process
