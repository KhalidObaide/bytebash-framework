#ifndef UTILS_H
#define UTILS_H

#include "../engine/types.h"
#include <vector>

class Utils {
public:
  Utils();
  RGBA getNextColor();

private:
  std::vector<RGBA> colorsList;
  int colorPickerIndex;
};

#endif // !UTILS_H
