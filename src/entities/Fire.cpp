#include "Fire.h"

#include "../utils/Enums.h"
#include "../map/Coordinates.h"

#define LEVER_ON 140

Fire::Fire() : Base() { }

void Fire::update() {

  this->counter++;
  if (this->counter == 4) this->counter = 0;

}