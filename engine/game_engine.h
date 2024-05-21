#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "game_object.h"
#include "graphics_renderer.h"
#include "network_io.h"
#include "types.h"
#include <string>
#include <vector>

class GameEngine {
public:
  GameEngine();
  GameEngine(std::string titleVal, Size worldSizeVal, bool enableNetwork,
             bool enableRender);
  void run();
  void registerGameObject(GameObject &gameObjectVal);
  void deRegisterGameObject(GameObject &gameObjectVal);

  bool running;
  NetworkIO networkIO;

private:
  std::string title;
  Size worldSize;
  bool isNetworkIOEnabled;
  bool isRenderingEnabled;
  GraphicsRenderer graphicsRenderer;
  std::vector<GameObject *> gameObjects;

  void setup();
  void runNetworkLoop();
  void runMainLoop();
};

#endif
