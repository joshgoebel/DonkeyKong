#include "Fire.h"

#include "../utils/Enums.h"
#include "../map/Coordinates.h"

#define LEVER_ON 140

Fire::Fire() { }

uint8_t Fire::getCounter() {

  return this->counter;

}

void Fire::setCounter(uint8_t counter) {

  this->counter = counter;

}

void Fire::update() {

  this->counter++;
  if (this->counter == 4) this->counter = 0;

}