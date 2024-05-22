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
  void onNewNetworkAction(int connectionId, std::string action);
  void setOnNewActionCallback(std::function<void(int, std::string)> callback);

  std::unordered_map<int, std::string> *observationPerConnection;
  bool running;
  std::string *endingMessage;
  NetworkIO networkIO;

private:
  std::string title;
  Size worldSize;
  bool isNetworkIOEnabled;
  bool isRenderingEnabled;
  GraphicsRenderer graphicsRenderer;
  std::vector<GameObject *> gameObjects;
  std::function<void(int, std::string)> onNewAction;

  void setup();
  void runNetworkLoop();
  void runMainLoop();
};

#endif // GAME_ENGINE_H
