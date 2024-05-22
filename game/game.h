#ifndef GAME
#define GAME

#include "../engine/game_engine.h"
#include "player.h"
#include "runner.h"
#include "utils.h"

class Game {
public:
  Game(GameEngine &gameEngineVal);
  void run();
  void setup();
  Runner runner;

  std::unordered_map<int, std::string> gameStatePerConnection;

private:
  std::vector<std::unique_ptr<Player>> players;
  GameEngine &gameEngine;
  void initNewPlayer(int connectionId);
  void handleAction(int connectionId, std::string action);
  Utils utils;
};

#endif // !GAME
