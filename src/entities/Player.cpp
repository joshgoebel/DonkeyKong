#include "Player.h"

#include "../utils/Enums.h"
#include "../map/Coordinates.h"

Player::Player() { 

  this->movements = pgm_read_byte(&Coordinates::Player[(this->position * 6) + 5]);
  this->yOffset = pgm_read_byte(&Coordinates::Player[(this->position * 6) + 2]);

}

uint8_t Player::getPosition() {

  return this->position;

}

uint8_t Player::getJumpPosition() {

  return this->jumpPosition;

}

uint8_t Player::getXPosition() {

  return pgm_read_byte(&Coordinates::Player[(this->position * 6)]);

}

int8_t Player::getYPosition() {

  int8_t y = pgm_read_byte(&Coordinates::Player[(this->position * 6) + 1]) - this->yOffset;
  return y;

}

uint8_t Player::getMovements() {

  return this->movements;

}

uint8_t Player::getYOffset() {

  return this->yOffset;

}

void Player::setPosition(uint8_t position) {

  this->position = position;

}

void Player::setJumpPosition(uint8_t jumpPosition) {

  this->jumpPosition = jumpPosition;

}

void Player::setMovements(uint8_t movements) {

  this->movements = movements;

}

void Player::setYOffset(uint8_t yOffset) {

  this->yOffset = yOffset;

}

void Player::incPlayerPosition() {

  this->position++;
  this->movements = pgm_read_byte(&Coordinates::Player[(this->position * 6) + 5]);
  this->yOffset = pgm_read_byte(&Coordinates::Player[(this->position * 6) + 2]);

}

void Player::decPlayerPosition() {

  this->position--;
  this->movements = pgm_read_byte(&Coordinates::Player[(this->position * 6) + 5]);
  this->yOffset = pgm_read_byte(&Coordinates::Player[(this->position * 6) + 2]);

}

bool Player::canMove(Movements movement) {

  return (this->movements & static_cast<uint8_t>(movement));

}

void Player::initLife() {

  this->setPosition(0);

}