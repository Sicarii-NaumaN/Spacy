#pragma once

#include <vector>

#include <boost/thread/thread.hpp>

#include <queue>
#include <boost/date_time.hpp>
#include <PacketManagerServer.h>
#include <ObjectManager.h>
#include <NetServer.h>
#include <Event.h>

const static unsigned int FRAMES_PER_SECOND = 20;
const static unsigned int MAX_PLAYERS = 30;

class GameEnvironment {
  public:
    GameEnvironment(std::uint16_t port,                 // Порт
          unsigned int  max_game_duration,    // Максимальная длительность игры
          unsigned int  points_to_win         // Количество очков для победы
        );

    bool start_game();

  private:
    ObjectManager object_manager;
    std::queue<std::shared_ptr<Event>> event_queue;

    NetServer net_server;

    double tick_duration;
    double max_game_duration;
    double points_to_win;

    void initialize_objects();
    void update_objects();

    std::shared_ptr<Player> init_user(User& user);
    void serve_user(User& user);

    std::mutex events_mutex;

    bool need_update;
    bool game_is_active;
    int player_count = 2;
};
