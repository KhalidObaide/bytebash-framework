#include "game_engine.h"
#include <iostream>
#include <thread>

GameEngine::GameEngine() {
  title = "Game";
  worldSize = {800, 800}; // default world size
  isNetworkLoopEnabled = true;
  isUpdateLoopEnabled = true;
  isRenderLoopEnabled = true;
  setup();
}

GameEngine::GameEngine(std::string titleVal, Size worldSizeVal,
                       bool enableNetwork, bool enableUpdate,
                       bool enableRender) {
  title = titleVal;
  worldSize = worldSizeVal;
  isNetworkLoopEnabled = enableNetwork;
  isUpdateLoopEnabled = enableUpdate;
  isRenderLoopEnabled = enableRender;
  setup();
}

void GameEngine::setup() {
  if (isRenderLoopEnabled) {
    renderer.setup(title, worldSize);
  }
}

void GameEngine::run() {
  std::optional<std::thread> networkThread;
  std::optional<std::thread> updateThread;
  std::optional<std::thread> renderThread;

  if (isNetworkLoopEnabled)
    networkThread.emplace([&]() { runNetworkLoop(); });
  if (isUpdateLoopEnabled)
    updateThread.emplace([&]() { runUpdateLoop(); });
  if (isRenderLoopEnabled)
    renderThread.emplace([&]() { runRenderLoop(); });

  std::cout << "GAME ENGINE RUNING" << std::endl;

  if (networkThread && networkThread->joinable())
    networkThread->join();
  if (updateThread && updateThread->joinable())
    updateThread->join();
  if (renderThread && renderThread->joinable())
    renderThread->join();
}

void GameEngine::runNetworkLoop() {}

void GameEngine::runUpdateLoop() {}

void GameEngine::runRenderLoop() {}
