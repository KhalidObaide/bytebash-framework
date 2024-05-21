#ifndef GAME
#define GAME

#include "../engine/game_engine.h"
#include "player.h"
#include "utils.h"

class Game {
public:
  Game(GameEngine &gameEngineVal);
  void run();
  void setup();

private:
  std::vector<std::unique_ptr<Player>> players;
  GameEngine &gameEngine;
  void initNewPlayer(int id);
  Utils utils;
};

#endif // !GAME
