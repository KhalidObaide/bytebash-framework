#include "runner.h"
#include "../engine/game_object.h"
#include "../engine/types.h"
#include <cmath>

Runner::Runner() : GameObject({0, 0}, {30, 30}, (RGBA){255, 255, 0, 255}) {
  radius = 100; // Set the radius of the circular path
  angle = 0;    // Initialize the angle
}

void Runner::update() {
  // Calculate the new position based on circular motion
  position.x =
      350 + radius * cos(angle); // Adjust center (350, any value you like)
  position.y =
      250 + radius * sin(angle); // Adjust center (250, any value you like)

  // Update the angle for the next frame
  angle += 0.005; // Adjust angular speed as needed

  // Optional: Add conditions to keep the object within a specific range
  // For example, you might want to reset the angle to 0 after a full circle
  if (angle >= 2 * M_PI) {
    angle = 0;
  }
}

Runner::~Runner() {}
