#include "utils.h"

Utils::Utils() {
  colorPickerIndex = 0;
  colorsList = {{255, 0, 0, 255},   {0, 255, 0, 255},   {0, 0, 255, 255},
                {255, 255, 0, 255}, {255, 0, 255, 255}, {0, 255, 255, 255}};
}

RGBA Utils::getNextColor() {
  colorPickerIndex++;
  return colorsList[colorPickerIndex - 1];
}
