
#ifndef PLAYER_H
#define PLAYER_H

#include "../engine/game_object.h"

class Player : public GameObject {
public:
  Player(int connectionIdVal);
  virtual ~Player();
  void up();
  void down();
  void right();
  void left();
  int connectionId;
};

#endif // !PLAYER_H
