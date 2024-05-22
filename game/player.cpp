#include "player.h"
#include "../engine/game_object.h"
#include "../engine/types.h"

Player::Player(int connectionIdVal)
    : GameObject({0, 0}, {10, 10}, (RGBA){0, 0, 0, 0}) {
  connectionId = connectionIdVal;
}
void Player::update() {}
void Player::move() { position.x += 10; }
Player::~Player() {}
