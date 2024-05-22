#include "game.h"
#include "../engine/types.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

Game::Game(GameEngine &gameEngineVal) : gameEngine(gameEngineVal) {
  srand(time(nullptr));

  // gameEngine API
  gameEngine.networkIO.connectionsLimit = 2;
  gameEngine.networkIO.setOnNewConnectionCallback(
      std::bind(&Game::initNewPlayer, this, std::placeholders::_1));
  gameEngine.setOnNewActionCallback(std::bind(
      &Game::handleAction, this, std::placeholders::_1, std::placeholders::_2));
  gameEngine.observationPerConnection = &gameStatePerConnection;
  gameEngine.endingMessage = &endingMessage;
  banana.position.x = (rand() % 10) * 80;
  banana.position.y = (rand() % 10) * 80;
  gameEngine.registerGameObject(banana);
}

void Game::initNewPlayer(int connectionId) {
  players.push_back(std::make_unique<Player>(Player(connectionId)));
  players.back()->setFillColor(utils.getNextColor());
  players.back()->position.x = (rand() % 10) * 80;
  players.back()->position.y = (rand() % 10) * 80;
  gameEngine.registerGameObject(*players.back().get());
  gameStatePerConnection[connectionId] =
      generateObserveration(players.back()->position);
}

void Game::handleAction(int connectionId, std::string action) {
  for (auto &player : players) {
    if (player->connectionId == connectionId) {
      if (action == "UP") {
        player->up();
      } else if (action == "DOWN") {
        player->down();
      } else if (action == "RIGHT") {
        player->right();
      } else if (action == "LEFT") {
        player->left();
      }
      gameStatePerConnection[connectionId] =
          generateObserveration(player->position);
    }
  }

  // after each action
  runStatusCheck();
}

std::string Game::generateObserveration(Coordinate playerPosition) {
  std::string result;
  result += std::to_string(playerPosition.x) + ",";
  result += std::to_string(playerPosition.y) + " ";
  result += std::to_string(banana.position.x) + ",";
  result += std::to_string(banana.position.y);
  return result;
}

void Game::runStatusCheck() {
  for (auto &player : players) {
    if (player->position.x == banana.position.x &&
        player->position.y == banana.position.y) {
      endingMessage = "WINNER: " + std::to_string(player->connectionId);
      gameEngine.running = false;
      std::cout << endingMessage << std::endl;
      break;
    }
  }
}

void Game::run() { gameEngine.run(); }
