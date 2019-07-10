#include "Spaghetti.h"

#include "../utils/Utils.h"
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

  this->counter = wrapInc(this->counter, static_cast<uint8_t>(0), static_cast<uint8_t>(2));
  // this->counter++;
  // if (this->counter == 3) this->counter = 0;

}