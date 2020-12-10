#include <GameEnvironment.h>

GameEnvironment::GameEnvironment(std::uint16_t port,
                                unsigned int max_game_duration,
                                unsigned int points_to_win
                              ):
                              net_server(port),
                              max_game_duration(max_game_duration),
                              points_to_win(points_to_win) {
  tick_duration = 1 / FRAMES_PER_SECOND;
}

bool GameEnvironment::start_game() {
  std::vector<User> players_init = netServer.accept_users(2, objectManager);
    std::vector<boost::thread> threads;
    for (auto& usr: players_init) {
        objectManager.update_objects(init_user(usr));
        boost::thread  th([&](){
            this->serve_user(usr);
        });
        threads.push_back(move(th));
    }
    initialize_objects();
    game_is_active = true;
    boost::thread th([&](){
        this->update_objects();
    });
    threads.push_back(move(th));

    // Определяем переменные времени
    auto round_start = boost::posix_time::microsec_clock::universal_time();
    boost::posix_time::time_duration current_game_duration;
    boost::posix_time::time_duration current_tick_duration;
    auto last_tick = boost::posix_time::microsec_clock::universal_time();

    // Главный таймер
    while (current_game_duration.total_seconds() < max_game_duration) {
        auto curr_time = boost::posix_time::microsec_clock::universal_time();
        current_tick_duration = curr_time - last_tick;
        if ((current_tick_duration.total_milliseconds() / 1000.0) > tick_duration) {
            last_tick = curr_time;
            need_update = true;
            netServer.notify_all_users(objectManager.get_objects_by_map());
        }
        curr_time = boost::posix_time::microsec_clock::universal_time();
        current_game_duration = curr_time - round_start;
    }

    game_is_active = false;
    for (auto& th: threads) {
        th.join();
    }
}

void GameEnvironment::initialize_objects() {
  std::vector<std::shared_ptr<Object>> players;
    for (int i = 0; i < player_count; i++) {
        players.push_back(objectManager.get_object_by_id(i));
    }
    std::shared_ptr<Map> map = std::make_shared<Map>(objectManager.pick_enable_id(),
                                                     game_duration * FRAMES_PER_SECOND, move(players));
    objectManager.update_objects(map);

    //TODO: Сделать стены
    // std::shared_ptr<Obstruction> obs1 = std::make_shared<Obstruction>(objectManager.pick_enable_id(), Point(460, 280), 30, 250);
    // objectManager.update_objects(obs1);
    //
    // std::shared_ptr<Obstruction> obs2 = std::make_shared<Obstruction>(objectManager.pick_enable_id(), Point(520, 200), 250, 30);
    // objectManager.update_objects(obs2);
    //
    // std::shared_ptr<Obstruction> obs3 = std::make_shared<Obstruction>(objectManager.pick_enable_id(), Point(800, 280), 30, 250);
    // objectManager.update_objects(obs3);
    //
    // std::shared_ptr<Obstruction> obs4 = std::make_shared<Obstruction>(objectManager.pick_enable_id(), Point(520, 560), 250, 30);
    // objectManager.update_objects(obs4);
}

void GameEnvironment::update_objects() {
  while(game_is_active) {
        // Получаем объекты
        std::unordered_map<int, std::shared_ptr<Object>>& objects = objectManager.get_objects_by_map();
        // Проверка на столкновения
        if (need_update) {
            // for (auto& object: objects) {
            //     if (object.second->type != Object::STATIC_OBJECT) {
            //         object.second->update();
            //         auto collisions = objectManager.collisionSolver.check_object_collisions(objects, object.second);
            //         for (auto& collision: collisions) {
            //             objectManager.collisionSolver.resolve_collision(object.second, collision);
            //         }
            //     }
            // }
            need_update = false;
        // Обновляем состояние объектов, проверяем на коллизии в новом состоянии
        } else {
            std::lock_guard<std::mutex> lock(events_mutex);
            if (!event_queue.empty()) {
                // Тащим событие из очереди
                std::shared_ptr<Event> event = event_queue.front();
                event_queue.pop();

                // Получаем объект, к которому относится событие
                auto object = objectManager.get_object_by_id(event->IniciatorID);
                // Вычисляем его новое состояние
                auto new_state = event->proccess(object, objectManager);
                // Проверяем на столкновение с другими объектами
                // if (!objectManager.collisionSolver.is_object_collided(objects, new_state)) {
                if (1) {
                    // Если нет столкновений, обновляем состояние
                    *object = *new_state;
                    // objectManager.update_objects(New_state);
                }
            }
            // Обрабатываем ивент из очереди
        }
    }
}

std::shared_ptr(Player) GameEnvironment::init_user(User& user) {
  int id = user.get_username();
  std::shared_ptr<Player> player = std::make_shared<Player>(id);
  return player;
}

void GameEnvironment::serve_user(User &user) {
  while(game_is_active) {
        std::shared_ptr<Event> event = net_server.get_client_action(user);
        std::lock_guard<std::mutex> lock(events_mutex);
        event_queue.push(event);
    }
}
