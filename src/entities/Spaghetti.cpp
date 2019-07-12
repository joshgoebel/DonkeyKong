#include "Spaghetti.h"

#include "../utils/Utils.h"
#include "../utils/Enums.h"
#include "../map/Coordinates.h"

Spaghetti::Spaghetti() : Base() { }


bool Spaghetti::isVisible() {

  return this->visible;

}

uint8_t Spaghetti::getFood() {

  return this->food;

}

void Spaghetti::setVisible(bool visible) {

  this->visible = visible;

}

void Spaghetti::setFood(uint8_t food) {

  this->food = food;

}

void Spaghetti::incFood() {

  this->food = wrapInc(this->food, static_cast<uint8_t>(0), static_cast<uint8_t>(2));

}

void Spaghetti::update() {

  this->counter = wrapInc(this->counter, static_cast<uint8_t>(0), static_cast<uint8_t>(2));

}