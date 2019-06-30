#include "Gorilla.h"
#include "../utils/Enums.h"


Gorilla::Gorilla() { 
}


uint8_t Gorilla::getXPosition() {

  return this->xPosition;

}

int8_t Gorilla::getYPosition(uint8_t yOffset) {

  return 5 - yOffset;

}

GorillaStance Gorilla::getStance() {

  switch (this->xPosition) {

    case GORILLA_X_POSITION_1:
    case GORILLA_X_POSITION_2:
    case GORILLA_X_POSITION_3:

      if (this->launchBarrel > 0) {

        return static_cast<GorillaStance>( static_cast<uint8_t>(GorillaStance::ThrowingBarrel1) + (3 - (this->launchBarrel / 5)) );

      }
      else {
        return GorillaStance::Normal;
      }

    case GORILLA_X_POSITION_1 + 1 ... GORILLA_X_POSITION_2 - 1:
    case GORILLA_X_POSITION_2 + 1 ... GORILLA_X_POSITION_3 - 1:

      switch (this->movement) {

        case Movements::Left:
          return GorillaStance::Left;

        case Movements::Right:
          return GorillaStance::Right;

      }

      return GorillaStance::Normal;

  }

}


void Gorilla::move() {

  if (this->pause > 0) {

    this->pause--;

    if (this->launchBarrel > 0) {

      this->launchBarrel--;
Serial.print("Gorilla.cpp move() : launchBarrel pause : ");
Serial.print(this->pause);
Serial.print(", counter : ");
Serial.println(this->launchBarrel);

      if (this->launchBarrel == 0) {
        
        uint8_t lauchPosition = 0;
        if (this->xPosition == GORILLA_X_POSITION_2) lauchPosition = 1;
        if (this->xPosition == GORILLA_X_POSITION_3) lauchPosition = 2;
Serial.print("Gorilla.cpp move() : launch a barrel, pos: ");
Serial.println(lauchPosition);
        this->barrel->launch(lauchPosition);

      }

    }

  }
  else {

    switch (this->xPosition) {

      case GORILLA_X_POSITION_1:
      case GORILLA_X_POSITION_2:
      case GORILLA_X_POSITION_3:
        changeDirections();

      case GORILLA_X_POSITION_1 + 1 ... GORILLA_X_POSITION_2 - 1:
      case GORILLA_X_POSITION_2 + 1 ... GORILLA_X_POSITION_3 - 1:
        moveLeftOrRight();

        switch (this->xPosition) {

          case GORILLA_X_POSITION_1:
          case GORILLA_X_POSITION_2:
          case GORILLA_X_POSITION_3:
            this->pause = random(50, 150);
            break;

          default:            
            break;    

        }

        break;    

    }

  }
  
}

void Gorilla::moveLeftOrRight() {

  switch (this->movement) {

    case Movements::Left:
      this->xPosition--;
      break;

    case Movements::Right:
      this->xPosition++;
      break;

    default: break;

  }

}

void Gorilla::changeDirections() {

  switch (this->xPosition) {

    case GORILLA_X_POSITION_1:
      this->movement = Movements::Right;
      break;

    case GORILLA_X_POSITION_2:
      this->movement = (random(0, 2) == 0 ? Movements::Left : Movements::Right);
      break;
      
    case GORILLA_X_POSITION_3:
      this->movement = Movements::Left;
      break;

  }
  
}

void Gorilla::launch(Barrel *barrel) {

Serial.print("Gorilla.cpp launch() : lbarrel number : ");
Serial.println(barrel->getNumber());

  this->barrel = barrel;
  this->launchBarrel = 20;

}

bool Gorilla::isPaused() {

  return (this->pause > 0);

}


bool Gorilla::isReadyToLaunch() {

  return (this->pause > 25 && this->launchBarrel == 0);

}