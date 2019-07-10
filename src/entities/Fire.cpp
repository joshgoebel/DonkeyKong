#include "Fire.h"

#include "../utils/Utils.h"
#include "../utils/Enums.h"
#include "../map/Coordinates.h"

#define LEVER_ON 140

Fire::Fire() : Base() { }

void Fire::update() {

  this->counter = wrapInc(this->counter, static_cast<uint8_t>(0), static_cast<uint8_t>(3));

}