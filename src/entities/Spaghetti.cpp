#include "Spaghetti.h"

#include "../utils/Enums.h"
#include "../map/Coordinates.h"

#define LEVER_ON 140

Spaghetti::Spaghetti() { }

uint8_t Spaghetti::getCounter() {

  return this->counter;

}

bool Spaghetti::isVisible() {

  return this->visible;

}

void Spaghetti::setCounter(uint8_t counter) {

  this->counter = counter;

}

void Spaghetti::setVisible(bool visible) {

  this->visible = visible;

}

void Spaghetti::update() {

  this->counter++;
  if (this->counter == 3) this->counter = 0;

}