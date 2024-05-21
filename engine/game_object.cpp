#include "game_object.h"
#include "types.h"

GameObject::GameObject() {
  setup({0, 0}, {0, 0});
  setFillColor({0, 0, 0, 0});
}

GameObject::GameObject(Coordinate positionVal, Size sizeVal) {
  setup(positionVal, sizeVal);
  setFillColor({255, 0, 0, 175});
}

GameObject::GameObject(Coordinate positionVal, Size sizeVal, RGBA fillVal) {
  setup(positionVal, sizeVal);
  setFillColor(fillVal);
}

GameObject::GameObject(Coordinate positionVal, Size sizeVal,
                       std::string texturePathVal) {
  setup(positionVal, sizeVal);
  setTexturePath(texturePathVal);
}

void GameObject::setup(Coordinate positionVal, Size sizeVal) {
  position = positionVal;
  size = sizeVal;
  zIndex = 0;
}

void GameObject::setFillColor(RGBA fillVal) {
  isUsingTexture = false;
  texturePath = "";
  fill = fillVal;
}
void GameObject::setTexturePath(std::string texturePathVal) {
  isUsingTexture = true;
  fill = {0, 0, 0, 0};
  texturePath = texturePathVal;
}

void GameObject::update() {}
