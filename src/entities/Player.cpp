#include "Player.h"

#include "../utils/Enums.h"
#include "../map/Coordinates.h"

Player::Player() { }

uint8_t Player::getPosition() {

  return this->position;

}

void Player::setPosition(uint8_t position) {

  this->position = position;

}