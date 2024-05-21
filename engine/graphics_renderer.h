#ifndef GRAPHICS_RENDERER_H
#define GRAPHICS_RENDERER_H

#include "game_object.h"
#include "types.h"
#include <SDL2/SDL_render.h>
#include <string>
#include <vector>

class GraphicsRenderer {
public:
  GraphicsRenderer();
  ~GraphicsRenderer();
  void setup(std::string title, Size screenSize);
  void drawFrame(std::vector<GameObject *> &gameObjects);

private:
  bool isSetup;
  SDL_Window *window;
  SDL_Renderer *renderer;
};

#endif // !GRAPHICS_RENDERER_H
