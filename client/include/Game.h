#pragma once

#include "PlayerModel.h"
#include <list>

enum GameState {
  WAITING_FOR_PLAYERS,
  RUNNING,
  FINISHED
};

class Game {
private:
  GameState state;
  std::list<PlayerModel> players;
  uint8_t players_to_start;
  uint8_t players_number;

public:
  Game(uint8_t n_players): state(WAITING_FOR_PLAYERS),
                           players_to_start(n_players) {}

  void addPlayer();

};
