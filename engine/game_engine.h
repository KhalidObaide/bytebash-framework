#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "../types.h"
#include "graphics_renderer.h"
#include <string>

class GameEngine {
public:
  GameEngine();
  GameEngine(std::string titleVal, Size worldSizeVal, bool enableNetwork,
             bool enableUpdate, bool enableRender);
  void run();

private:
  std::string title;
  Size worldSize;
  bool isNetworkLoopEnabled;
  bool isUpdateLoopEnabled;
  bool isRenderLoopEnabled;
  GraphicsRenderer renderer;

  void setup();
  void runNetworkLoop();
  void runUpdateLoop();
  void runRenderLoop();
};

#endif
