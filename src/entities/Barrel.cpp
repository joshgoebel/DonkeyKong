#include "Barrel.h"

#include "../utils/Utils.h"
#include "../utils/Enums.h"
#include "../map/Coordinates.h"

Barrel::Barrel() { 
}

uint8_t Barrel::getPosition() {

  return this->position;

}

uint8_t Barrel::getAisle() {

  return this->aisle;

}

uint8_t Barrel::getRotation() {

  return this->rotation;

}

uint8_t Barrel::getEnabledCountdown() {

  return this->enabledCountdown;

}

bool Barrel::isEnabled() {

  return this->enabled;

}

bool Barrel::isEnabledOrPending() {

  return this->enabled || (this->enabledCountdown > 0);

}

void Barrel::setPosition(uint8_t position) {

  this->position = position;

}

void Barrel::setAisle(uint8_t aisle) {

  this->aisle = aisle;

}

void Barrel::setRotation(uint8_t rotation) {

  this->rotation = rotation;

}

void Barrel::setEnabledCountdown(uint8_t enabledCountdown) {

  this->enabledCountdown = enabledCountdown;

}

void Barrel::setEnabled(bool enabled) {

  this->enabled = enabled;
  if (!enabled) this->enabledCountdown = 0;

}


// Methods ..

int8_t Barrel::getXPosition() {

  int8_t x = pgm_read_byte(&Coordinates::Barrel[(this->position * BARREL_NUMBER_OF_ELEMENTS)]);
  return x;

}

int8_t Barrel::getYPosition(uint8_t yOffset) {

  int8_t y = pgm_read_byte(&Coordinates::Barrel[(this->position * BARREL_NUMBER_OF_ELEMENTS) + 1]) - yOffset;
  return y;

}

void Barrel::updatePosition() {

  // Retrieve sjip value from current position (if it exists) ..

  uint8_t skip = pgm_read_byte(&Coordinates::Barrel[(this->position * BARREL_NUMBER_OF_ELEMENTS)+ 2]) >> 3;
  this->position = this->position + 1 + skip;

  uint8_t x = pgm_read_byte(&Coordinates::Barrel[(this->position * BARREL_NUMBER_OF_ELEMENTS)]);
  uint8_t y = pgm_read_byte(&Coordinates::Barrel[(this->position * BARREL_NUMBER_OF_ELEMENTS) + 1]);

  if (x == 0 && y == 0) {

    this->position = 0;
    this->enabled = false;

  }

  this->rotationDirection = static_cast<Rotation>(pgm_read_byte(&Coordinates::Barrel[(this->position * BARREL_NUMBER_OF_ELEMENTS) + 2]) & 0x07);

}

void Barrel::rotate() {

  switch (this->rotationDirection) {

    case Rotation::Right:
      this->rotation = wrapInc(this->rotation, static_cast<uint8_t>(0), static_cast<uint8_t>(2));
      break;

    case Rotation::Left:
      this->rotation = wrapDec(this->rotation, static_cast<uint8_t>(0), static_cast<uint8_t>(2));
      break;

    case Rotation::None:
      break;
      
  }

}

void Barrel::launch(uint8_t startingPosition) {

  const uint8_t startingPositions[3] = { BARREL_POSITION_1_START, BARREL_POSITION_2_START, BARREL_POSITION_3_START };

  this->position = startingPositions[startingPosition];
  this->aisle = startingPosition;
  this->enabled = true;

}

void Barrel::decEnabledCountdown() {

  if (this->enabledCountdown > 0) {
    
    this->enabledCountdown--;

  }

}

Rect Barrel::getRect(uint8_t yOffset) {

  int8_t x = pgm_read_byte(&Coordinates::Barrel[(this->position * BARREL_NUMBER_OF_ELEMENTS)]);
  int8_t y = pgm_read_byte(&Coordinates::Barrel[(this->position * BARREL_NUMBER_OF_ELEMENTS) + 1]) - yOffset;

  return Rect{x + 1, y + 1, 7, 7 };

}