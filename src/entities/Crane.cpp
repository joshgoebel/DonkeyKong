#include "Crane.h"

#include "../utils/Enums.h"
#include "../map/Coordinates.h"

Crane::Crane() { }

CranePosition Crane::getPosition() {

  return this->position;

}

uint8_t Crane::getCounter() {

  return this->counter;

}

void Crane::setPosition(CranePosition position) {

  this->position = position;

}

void Crane::setCounter(uint8_t counter) {

  this->counter = counter;

}

uint8_t Crane::getImage() {

  switch (this->position) {

    case CranePosition::Upright:
    case CranePosition::Flat:
    case CranePosition::Declined: 
      return static_cast<uint8_t>(this->position);

    default:
      return static_cast<uint8_t>(CranePosition::Inclined) + this->hook;

  }

}


void Crane::turnOn() {

  this->state = CraneState::TurningOn;
  this->counter = 20;

}

void Crane::update() {

  switch (this->state) {

    case CraneState::Dormant:
      break;

    case CraneState::TurningOn:

      if (this->counter > 0) {

        this->counter--;

      }
      else {

        switch (this->position) {

          case CranePosition::Declined:
            this->position = CranePosition::Flat;
            this->counter = 20;
            break;

          case CranePosition::Flat:
            this->position = CranePosition::Inclined;
            this->counter = 20;
            break;

          case CranePosition::Inclined:
Serial.println("Inclined");
            this->hook = 2;
            this->counter = 10;
            this->state = CraneState::Swinging;
            break;

        }

      }

      break;

    case CraneState::Swinging:

      if (this->counter > 0) {

        this->counter--;

      }
      else {

        switch (this->hookDirection) {

          case Movements::Left: 

            switch (this->hook) {
              
              case 0:
                this->hook = 1;
                this->hookDirection = Movements::Right;
                break;

              case 1 ... 4:
                this->hook--;
                break;

            }

            break;

          case Movements::Right: 

            switch (this->hook) {
              
              case 0 ... 3:
                this->hook++;
                break;

              case 4:
                this->hook = 3;
                this->hookDirection = Movements::Left;
                break;

            }

            break;

        }

        this->counter = 10;

      }

      break;

    default: break;

  }

}