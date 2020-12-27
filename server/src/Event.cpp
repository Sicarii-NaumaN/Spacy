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

    speed = speed.setMag(4);

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
    std::cout << "TRYING TO MOVE PLAYER #" << player.ID;
    float defaultSpeed = 30;
    int side = (player.side == 0)? 1 : -1;
    float speed = defaultSpeed * side;
    Vector current_speed = player.speed * side;

    if (state == 0)
    {
        switch (key_code) //WASD - 0123
        {
        case 0:
            player.setSpeedY(-speed);
            break;

        case 1:
            player.setSpeedX(-speed);
            break;

        case 2:
            player.setSpeedY(speed);
            break;

        case 3:
            player.setSpeedX(speed);
            break;
        }
    }
    else
    {
        switch (key_code) //WASD - 0123
        {
        case 0:

            if (current_speed.y < 0)
            {
                player.setSpeedY(0);
            }
            break;

        case 1:

            if (current_speed.x < 0)
            {
                player.setSpeedX(0);
            }
            break;

        case 2:

            if (current_speed.y > 0)
            {
                player.setSpeedY(0);
            }
            break;

        case 3:

            if (current_speed.x > 0)
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
