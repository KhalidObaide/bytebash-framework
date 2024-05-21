#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "types.h"
#include <string>

class GameObject {
public:
  GameObject();
  GameObject(Coordinate positionVal, Size sizeVal);
  GameObject(Coordinate positionVal, Size sizeVal, RGBA fillVal);
  GameObject(Coordinate positionVal, Size sizeVal, std::string texturePathVal);

  void setup(Coordinate positionVal, Size sizeVal);
  void setFillColor(RGBA fillVal);
  void setTexturePath(std::string texturePathVal);

  virtual void update();

  Coordinate position;
  Size size;
  bool isUsingTexture;
  RGBA fill;
  std::string texturePath;
  int zIndex;
};

#endif // !GAME_OBJECT_H
