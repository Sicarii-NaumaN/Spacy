#include <GameEnvironment.h>
#include <ObjectManager.h>

GameEnvironment::GameEnvironment(std::uint16_t port,
                                 unsigned int  max_game_duration,
                                 unsigned int  points_to_win)
    : net_server(port)
    , max_game_duration(max_game_duration)
    , points_to_win(points_to_win)
{
    tick_duration = 1.0 / FRAMES_PER_SECOND;
}


bool GameEnvironment::start_game()
{
    std::cout << "[GAME ENV] "
              << "Starting game..." << std::endl;
    // Ждем пользователей
    std::cout << "[GAME ENV] "
              << "Waiting for players..." << std::endl;
    std::vector<User> players_init =
        net_server.accept_users(player_count, object_manager);
    std::cout << "[GAME ENV] "
              << "Players connected" << std::endl;
    // Создаем слушателя событий для каждого пользователя
    std::vector<boost::thread> threads;

    for (auto &usr : players_init)
    {
        object_manager.update_objects(init_user(usr));
        boost::thread th([&]() {
            this->serve_user(usr);
        });
        threads.push_back(move(th));
    }

//    initialize_objects();
    game_is_active = true;
    std::cout << "[GAME ENV] " << "Updating objects" << std::endl;
    boost::thread th([&]() {
        this->update_objects();
    });
    // boost::thread th(boost::bind(&(this->update_objects), this, boost::ref(object_manager)));
    std::cout << "[GAME ENV] " << "Objects updated" << std::endl;
    threads.push_back(move(th));

    std::cout << "[GAME ENV] " << "Starting main game cycle" << std::endl;
    // Определяем переменные времени
    auto                             round_start = boost::posix_time::microsec_clock::universal_time();
    boost::posix_time::time_duration current_game_duration;
    boost::posix_time::time_duration current_tick_duration;
    auto                             last_tick = boost::posix_time::microsec_clock::universal_time();

    // Главный таймер
    while (current_game_duration.total_seconds() < max_game_duration)
    {
        auto curr_time = boost::posix_time::microsec_clock::universal_time();
        current_tick_duration = curr_time - last_tick;

        if ((current_tick_duration.total_milliseconds() / 1000.0) > tick_duration)
        {
            last_tick   = curr_time;
            std::cout << "BEFORE KILL " << object_manager.get_objects_by_map().size() << std::endl;
            object_manager.update_all_and_kill_dead_bullets();
            std::cout << "AFTER KILL " << object_manager.get_objects_by_map().size() << std::endl;
            net_server.notify_all_users(object_manager.get_objects_by_map());
            std::cout << "AFTER NOTIFICATION " << object_manager.get_objects_by_map().size() << std::endl;
            need_update = true;
        }
        curr_time             = boost::posix_time::microsec_clock::universal_time();
        current_game_duration = curr_time - round_start;
    }
    std::cout << "[GAME ENV] " << "Game over" << std::endl;
    game_is_active = false;

    for (auto &th : threads)
        th.join();

    std::cout << "[GAME ENV] " << "Exiting..." << std::endl;
    return(0);
} // GameEnvironment::start_game


void GameEnvironment::initialize_objects()
{
    std::vector<std::shared_ptr<Object> > players;

    for (int i = 0; i < player_count; i++)
    {
        players.push_back(object_manager.get_object_by_id(i));
    }
}


void GameEnvironment::update_objects()
{
    while (game_is_active)
    {
        // Получаем объекты
        // std::unordered_map<int, std::shared_ptr<Object> > &objects =
        //     object_manager.get_objects_by_map();

        // Проверка на столкновения
        if (need_update)
        {
            need_update = false;

        }
        else
        {
            std::lock_guard<std::mutex> lock(events_mutex);

            if (!event_queue.empty())
            {
                std::shared_ptr<Event> event = event_queue.front();
                event_queue.pop();
                auto object    = object_manager.get_object_by_id(event->IniciatorID);
                auto new_state = event->process(object, object_manager);
                *object = *new_state;
            }
        }
    }
} // GameEnvironment::update_objects


std::shared_ptr<Player> GameEnvironment::init_user(User &user)
{
    int id = user.get_username();
    int side = id;
    int pos_x = 0, pos_y = 0;
    int speed_x = 0, speed_y = 0;

    if (side == 0)
    {
        pos_x = 640;
        pos_y = 700;
    }
    else if (side == 1)
    {
        pos_x = 640;
        pos_y = 100;
    }
    std::shared_ptr<Player> player =
        std::make_shared<Player>(id, side, Vector(pos_x, pos_y), Vector(speed_x, speed_y));

    return(player);
}


void GameEnvironment::serve_user(User &user)
{
    std::cout << "[GAME ENV -- SERVICE] "
              << "Serve user start" << std::endl;

    while (game_is_active)
    {
        std::shared_ptr<Event> event = net_server.get_client_action(user);

        std::cout << "server: EVENT RECEIVED!" << std::endl;

        std::lock_guard<std::mutex> lock(events_mutex);
        event_queue.push(event);
    }
}
