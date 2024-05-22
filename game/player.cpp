#include "player.h"
#include "../engine/game_object.h"
#include "../engine/types.h"

Player::Player(int connectionIdVal)
    : GameObject({0, 0}, {80, 80}, (RGBA){0, 0, 0, 0}) {
  connectionId = connectionIdVal;
}
void Player::up() { position.y -= size.height; }
void Player::down() { position.y += size.height; }
void Player::right() { position.x += size.width; }
void Player::left() { position.x -= size.width; }

Player::~Player() {}
