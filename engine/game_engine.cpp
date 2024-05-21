#include "game_engine.h"
#include <SDL2/SDL.h>
#include <thread>

GameEngine::GameEngine() {
  title = "Game";
  worldSize = {800, 800}; // default world size
  isNetworkIOEnabled = true;
  isRenderingEnabled = true;
  setup();
}

GameEngine::GameEngine(std::string titleVal, Size worldSizeVal,
                       bool enableNetwork, bool enableRender) {
  title = titleVal;
  worldSize = worldSizeVal;
  isNetworkIOEnabled = enableNetwork;
  isRenderingEnabled = enableRender;
  setup();
}

void GameEngine::setup() {
  running = false;
  if (isRenderingEnabled) {
    graphicsRenderer.setup(title, worldSize);
  }
  if (isNetworkIOEnabled) {
    networkIO.setup();
  }
}

void GameEngine::run() {
  std::optional<std::thread> networkThread;

  if (isNetworkIOEnabled)
    networkThread.emplace([&]() { runNetworkLoop(); });

  runMainLoop();

  if (networkThread && networkThread->joinable())
    networkThread->join();
}

void GameEngine::runMainLoop() {
  running = true;
  while (running) {
    for (auto &gameObject : gameObjects) {
      gameObject->update();
    }

    // render
    if (!isRenderingEnabled)
      continue;
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
        break;
      }
    }
    graphicsRenderer.drawFrame(gameObjects);
  }
}

void GameEngine::registerGameObject(GameObject &gameObjectVal) {
  // Find the correct position to insert the new game object based on its zIndex
  auto it =
      std::upper_bound(gameObjects.begin(), gameObjects.end(), &gameObjectVal,
                       [](const GameObject *a, const GameObject *b) {
                         return a->zIndex < b->zIndex;
                       });

  // Insert the game object at the found position
  gameObjects.insert(it, &gameObjectVal);
}

void GameEngine::deRegisterGameObject(GameObject &gameObjectVal) {
  // Find the game object in the vector
  auto it = std::find(gameObjects.begin(), gameObjects.end(), &gameObjectVal);

  // Remove it if found
  if (it != gameObjects.end()) {
    gameObjects.erase(it);
  }
}

void GameEngine::runNetworkLoop() { networkIO.run(running); }
