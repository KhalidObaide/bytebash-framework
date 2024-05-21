#include "graphics_renderer.h"
#include "game_object.h"
#include "types.h"
#include <SDL2/SDL.h>
#include <string>
#include <vector>

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

void GraphicsRenderer::drawFrame(std::vector<GameObject *> &gameObjects) {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);
  for (auto &gameObject : gameObjects) {
    if (gameObject->isUsingTexture) {

    } else {
      SDL_SetRenderDrawColor(renderer, gameObject->fill.r, gameObject->fill.g,
                             gameObject->fill.b, gameObject->fill.a);

      SDL_Rect repr = {gameObject->position.x, gameObject->position.y,
                       gameObject->size.width, gameObject->size.height};
      SDL_RenderFillRect(renderer, &repr);
    }
  }
  SDL_RenderPresent(renderer);
}
