#include "Spaghetti.h"

#include "../utils/Enums.h"
#include "../map/Coordinates.h"

#define LEVER_ON 140

Spaghetti::Spaghetti() : Base() { }


bool Spaghetti::isVisible() {

  return this->visible;

}

void Spaghetti::setVisible(bool visible) {

  this->visible = visible;

}

void Spaghetti::update() {

  this->counter++;
  if (this->counter == 3) this->counter = 0;

}