#include "game.h"
#include <iostream>
#include <memory>

Game::Game(GameEngine &gameEngineVal) : gameEngine(gameEngineVal) {
  gameEngine.networkIO.connectionsLimit = 3;
  gameEngine.networkIO.setOnNewConnectionCallback(
      std::bind(&Game::initNewPlayer, this, std::placeholders::_1));
}

void Game::initNewPlayer(int connectionId) {
  players.push_back(std::make_unique<Player>(Player(connectionId)));
  players.back()->position.x = connectionId * 20;
  players.back()->setFillColor(utils.getNextColor());
  gameEngine.registerGameObject(*players.back().get());
}

void Game::run() { gameEngine.run(); }

void Game::setup() { std::cout << "SETUP GAME COMPELETE" << std::endl; }
