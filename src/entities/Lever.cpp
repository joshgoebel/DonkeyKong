#include "Lever.h"

#include "../utils/Enums.h"
#include "../map/Coordinates.h"

#define LEVER_ON 140

Lever::Lever() { }

LeverPosition Lever::getPosition() {

  return this->position;

}

uint8_t Lever::getCounter() {

  return this->counter;

}

void Lever::setPosition(LeverPosition position) {

  this->position = position;

  if (position == LeverPosition::On) {
    this->counter = LEVER_ON;
  }

}

void Lever::setCounter(uint8_t counter) {

  this->counter = counter;

}

void Lever::setCrane(Crane *crane) {

  this->crane = crane;

}

void Lever::update() {

  switch (this->counter) {

    case 0:
      break;

    case 1:
      this->counter = 0;
      this->position = LeverPosition::Off;
      this->crane->turnOff();
      break;

    default:
      this->counter--;
      break;

  }

}