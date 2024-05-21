#ifndef GRAPHICS_RENDERER_H
#define GRAPHICS_RENDERER_H

#include "../types.h"
#include <SDL2/SDL_render.h>
#include <string>

class GraphicsRenderer {
public:
  GraphicsRenderer();
  ~GraphicsRenderer();
  void setup(std::string title, Size screenSize);

private:
  bool isSetup;
  SDL_Window *window;
  SDL_Renderer *renderer;
};

#endif // !GRAPHICS_RENDERER_H
