#include "game/game.h"

int main() {
  GameEngine gameEngine = GameEngine("My Game", {400, 400}, true, true);
  Game game = Game(gameEngine);
  game.setup();
  gameEngine.run();
  return 0;
}
