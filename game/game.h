#ifndef GAME
#define GAME

#include "../engine/game_engine.h"
#include "../engine/types.h"
#include "banana.h"
#include "player.h"
#include "utils.h"

class Game {
public:
  Game(GameEngine &gameEngineVal);
  Banana banana;

  void run();
  std::unordered_map<int, std::string> gameStatePerConnection;
  std::string endingMessage;

private:
  void initNewPlayer(int connectionId);
  void handleAction(int connectionId, std::string action);
  void runStatusCheck();

  std::vector<std::unique_ptr<Player>> players;
  GameEngine &gameEngine;
  Utils utils;
  std::string generateObserveration(Coordinate playerPosition);
};

#endif // !GAME
