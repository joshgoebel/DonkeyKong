#include "Hook.h"

#include "../utils/Utils.h"
#include "../utils/Enums.h"

Hook::Hook() : Base() { 

  this->counter = 4;

}

void Hook::decCounter() {

  if (this->counter > 0) this->counter--;

}