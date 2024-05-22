#include "game.h"
#include <memory>

Game::Game(GameEngine &gameEngineVal) : gameEngine(gameEngineVal) {}

void Game::setup() {
  gameEngine.networkIO.connectionsLimit = 2;
  gameEngine.networkIO.setOnNewConnectionCallback(
      std::bind(&Game::initNewPlayer, this, std::placeholders::_1));
  gameEngine.setOnNewActionCallback(std::bind(
      &Game::handleAction, this, std::placeholders::_1, std::placeholders::_2));

  runner = Runner();
  gameEngine.registerGameObject(runner);
  gameEngine.observationPerConnection = &gameStatePerConnection;
}

void Game::run() { gameEngine.run(); }

void Game::initNewPlayer(int connectionId) {
  gameStatePerConnection[connectionId] = "HELLO";
  players.push_back(std::make_unique<Player>(Player(connectionId)));
  players.back()->setFillColor(utils.getNextColor());
  gameEngine.registerGameObject(*players.back().get());
}

void Game::handleAction(int connectionId, std::string action) {
  for (auto &player : players) {
    if (player->connectionId == connectionId) {
      if (action == "MOVE") {
        player->position.x += 10;
        gameStatePerConnection[connectionId] =
            "MOVE: " + std::to_string(player->position.x);
      }
    }
  }
}
