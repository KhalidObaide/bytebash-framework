#include "graphics_renderer.h"
#include "../types.h"
#include <SDL2/SDL.h>
#include <string>

GraphicsRenderer::GraphicsRenderer() { isSetup = false; }

void GraphicsRenderer::setup(std::string title, Size screenSize) {
  SDL_Init(SDL_INIT_VIDEO);
  window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, screenSize.width,
                            screenSize.height, 0);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  isSetup = true;
}

GraphicsRenderer::~GraphicsRenderer() {
  if (isSetup) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    isSetup = false;
  }
}
