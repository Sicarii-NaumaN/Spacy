#include <Event.h>
#include <iostream>


std::shared_ptr<Object> Shot::process(std::shared_ptr<Object> obj,
                                      ObjectManager           &object_manager)
{
    std::shared_ptr<Player> sh_player = std::static_pointer_cast<Player>(obj);
    Player                  player    = *sh_player.get();

    // if (sh_player->state_.is_shot_avaible())
    // {

    Vector speed = Vector(mouse_x - origin_x, mouse_y - origin_y);

    speed = speed.setMag(10);

    object_manager.update_objects(
        std::make_shared<Bullet>(
            object_manager.pick_enable_id(),
            player.ID,
            Vector(origin_x, origin_y),
            speed)
        );
    // player.state_.shot();
    // sh_player->state_.shot();
    // }
    return(std::make_shared<Player>(player));
}


std::shared_ptr<Object> KeyPressed::process(std::shared_ptr<Object> obj,
                                            ObjectManager           &object_manager)
{
    std::shared_ptr<Player> sh_player = std::static_pointer_cast<Player>(obj);

    Player player = *sh_player.get();

    float defaultSpeed = 30;

    std::cout << "KEYSTATE IS " << state << std::endl;

    if (state == 0)
    {
        switch (key_code) //WASD - 0123
        {
        case 0:
            player.setSpeedY(-defaultSpeed);
            break;

        case 1:
            player.setSpeedX(-defaultSpeed);
            break;

        case 2:
            player.setSpeedY(defaultSpeed);
            break;

        case 3:
            player.setSpeedX(defaultSpeed);
            break;
        }
    }
    else
    {
        switch (key_code) //WASD - 0123
        {
        case 0:

            if (player.speed.y < 0)
            {
                player.setSpeedY(0);
            }
            break;

        case 1:

            if (player.speed.x < 0)
            {
                player.setSpeedX(0);
            }
            break;

        case 2:

            if (player.speed.y > 0)
            {
                player.setSpeedY(0);
            }
            break;

        case 3:

            if (player.speed.x > 0)
            {
                player.setSpeedX(0);
            }
            break;
        }
    }
    // std::cout << "SDLFKJSDLF" << player.position.x << ' ' << player.position.y
    //           << std::endl;
    object_manager.update_objects(std::make_shared<Player>(player));

    return(std::make_shared<Player>(player));
} // KeyPressed::process
