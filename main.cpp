#include "game/game.h"

int main() {
  GameEngine gameEngine = GameEngine("My Game", {800, 800}, true, true);
  Game game = Game(gameEngine);
  game.setup();
  gameEngine.run();
  return 0;
}
