#include <GameEnvironment.h>


int main()
{

    auto new_game =
        GameEnvironment(8001, // Порт
                        20,  // Максимальная длительность игры в секундах
                        1
                        );

    new_game.start_game();
    return(0);
}
