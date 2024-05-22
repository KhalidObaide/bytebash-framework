
#ifndef RUNNER_H
#define RUNNER_H

#include "../engine/game_object.h"

class Runner : public GameObject {
public:
  Runner();
  virtual ~Runner();
  void update() override;

private:
  int radius;
  float angle;
};

#endif // !PLAYER_H
