#include "banana.h"
#include "../engine/game_object.h"
#include "../engine/types.h"

Banana::Banana() : GameObject({0, 0}, {80, 80}, (RGBA){255, 255, 0, 255}) {}
