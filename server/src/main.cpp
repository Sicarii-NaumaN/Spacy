#include <GameEnvironment.h>

int main() {
  auto new_game = GameEnvironment(
    8000,   // Порт
    120,    // Максимальная длительность игры в секундах
    1       // Количество очков для победы
  );

  return new_game.start_game();
}
