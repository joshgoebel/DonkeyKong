#include "Barrel.h"

#include "../utils/Enums.h"
#include "../map/Coordinates.h"

Barrel::Barrel() { 
}

uint8_t Barrel::getPosition() {

  return this->position;

}

uint8_t Barrel::getRotation() {

  return this->rotation;

}

bool Barrel::isEnabled() {

  return this->enabled;

}

void Barrel::setPosition(uint8_t position) {

  this->position = position;

}

void Barrel::setRotation(uint8_t rotation) {

  this->rotation = rotation;

}

void Barrel::setEnabled(bool enabled) {

  this->enabled = enabled;

}


// Methods ..

int8_t Barrel::getXPosition() {

  int8_t x = pgm_read_byte(&Coordinates::Barrel[(this->position * BARREL_NUMER_OF_ELEMENTS)]);
  return x;

}

int8_t Barrel::getYPosition(uint8_t yOffset) {

  int8_t y = pgm_read_byte(&Coordinates::Barrel[(this->position * BARREL_NUMER_OF_ELEMENTS) + 1]) - yOffset;
  return y;

}

void Barrel::updatePosition() {

  // Retrieve sjip value from current position (if it exists) ..

  uint8_t skip = pgm_read_byte(&Coordinates::Barrel[(this->position * BARREL_NUMER_OF_ELEMENTS)+ 3]);
  this->position = this->position + 1 + skip;

  uint8_t x = pgm_read_byte(&Coordinates::Barrel[(this->position * BARREL_NUMER_OF_ELEMENTS)]);
  uint8_t y = pgm_read_byte(&Coordinates::Barrel[(this->position * BARREL_NUMER_OF_ELEMENTS) + 1]);

  if (x == 0 && y == 0) {

    this->position = 0;
    this->enabled = false;

  }

  this->rotationDirection = static_cast<Rotation>(pgm_read_byte(&Coordinates::Barrel[(this->position * BARREL_NUMER_OF_ELEMENTS) + 2]));

}

void Barrel::rotate() {

  switch (this->rotationDirection) {

    case Rotation::Right:
      this->rotation++;
      if (this->rotation == 3) this->rotation = 0;
      break;

    case Rotation::Left:
      if (this->rotation == 0) this->rotation = 3;
      this->rotation--;
      break;

    case Rotation::None:
      break;
      
  }

}

void Barrel::launch(uint8_t startingPosition) {

  const uint8_t startingPositions[3] = { BARREL_POSITION_1_START, BARREL_POSITION_2_START, BARREL_POSITION_3_START };

  this->position = startingPositions[startingPosition];
  this->enabled = true;

}