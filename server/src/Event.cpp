//
// Created by moira-q on 14.04.20.
//

#include <Event.h>
#include <include/Event.h>

std::shared_ptr<Object> Move::proccess(std::shared_ptr<Object> obj, ObjectManager &objectmanager) {
    std::shared_ptr<Player> sh_player= std::static_pointer_cast<Player>(obj);
    Player player = *sh_player.get();
    if (player.state_.get_state() == PlayerState::STATE_FLYING) {
        return std::make_shared<Player>(player);
    }
    switch (direction) {
        case UP: {
            player.position.y -= player.speed;
            break;
        }
        case DOWN:{
            player.position.y += player.speed;
            break;
        }
        case LEFT:{
            player.position.x -= player.speed;
            break;
        }
        case RIGHT:{
            player.position.x += player.speed;
            break;
        }
        default:
            break;
    }
    player.sight = player.normalize(this->sight);
    sh_player->sight = sh_player->normalize(this->sight);
    return std::make_shared<Player>(player);
    //obj.get()->position.;
}

std::shared_ptr<Object> Shot::proccess(std::shared_ptr<Object> obj, ObjectManager &objectmanager) {
    std::shared_ptr<Player> sh_player= std::static_pointer_cast<Player>(obj);
    Player player = *sh_player.get();
    if (player.state_.get_state() == PlayerState::STATE_FLYING) {
        return std::make_shared<Player>(player);
    }
    if (sh_player->state_.is_shot_avaible()) {
        sh_player->sight = player.normalize(sight);;
        player.sight = sh_player->sight;
        Point bullet_postiton = player.position + Point(player.model.width / 2.0, player.model.height / 2.0);
        objectmanager.update_objects(std::make_shared<Bullet>(objectmanager.pick_enable_id(),
                                                              bullet_postiton, player.sight, player.ID));
        player.state_.shot();
        sh_player->state_.shot();
    }
    return std::make_shared<Player>(player);
}
