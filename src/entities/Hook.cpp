#include "Hook.h"

#include "../utils/Enums.h"

Hook::Hook() { 

  this->counter = 4;//SJH

}

uint8_t Hook::getCounter() {

  return this->counter;

}

void Hook::setCounter(uint8_t counter) {

  this->counter = counter;

}

void Hook::decCounter() {

  if (this->counter > 0) this->counter--;

}