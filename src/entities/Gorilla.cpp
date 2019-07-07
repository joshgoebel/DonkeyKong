#include "Gorilla.h"
#include "../utils/Enums.h"


const uint8_t PROGMEM Offsets[] = {

  0, 0, 0, 0,0, 0, 0, 0, 0, 3, 6, 9, 12, 15, 18, 20 // 16 elements

};

Gorilla::Gorilla() { 
}

uint8_t Gorilla::getXPosition() {

  return this->xPosition;

}

int8_t Gorilla::getYPosition(uint8_t yOffset) {

  return 3 - yOffset + (this->moveCentre ? pgm_read_byte(&Offsets[fallingIndex]) : 0);

}

bool Gorilla::getMoveToCentre() {

  return this->moveCentre;

}

uint8_t Gorilla::getFallingIndex() {

  return this->fallingIndex;

}

GorillaStance Gorilla::getStance() {

  switch (this->fallingIndex) {

    case 13 ... 14:
      return GorillaStance::Dead1;

    case 15:
      return GorillaStance::Dead2;

    default:

      switch (this->xPosition) {

        case GORILLA_X_POSITION_1:
        case GORILLA_X_POSITION_2:
        case GORILLA_X_POSITION_3:

          if (this->launchBarrel > 0) {

            return static_cast<GorillaStance>( static_cast<uint8_t>(GorillaStance::ThrowingBarrel1) + (3 - (this->launchBarrel / 10)) );

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

}

void Gorilla::move() {

  if (this->moveCentre) {

    switch (this->xPosition) {

      case GORILLA_X_POSITION_2:
        break;

      case GORILLA_X_POSITION_1:
        this->movement = Movements::Right;
        moveLeftOrRight();
        break;

      case GORILLA_X_POSITION_3:
        this->movement = Movements::Left;
        moveLeftOrRight();
        break;

      case GORILLA_X_POSITION_1 + 1 ... GORILLA_X_POSITION_2 - 1:
      case GORILLA_X_POSITION_2 + 1 ... GORILLA_X_POSITION_3 - 1:
        moveLeftOrRight();
        break;    

    }

  }
  else {

    if (this->pause > 0) {

      this->pause--;

      if (this->launchBarrel > 0) {

        this->launchBarrel--;

        if (this->launchBarrel == 0) {
          
          uint8_t lauchPosition = 0;
          if (this->xPosition == GORILLA_X_POSITION_2) lauchPosition = 1;
          if (this->xPosition == GORILLA_X_POSITION_3) lauchPosition = 2;
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
              this->pause = random(100, 255);
              break;

            default:            
              break;    

          }

          break;    

      }

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

  this->barrel = barrel;
  this->launchBarrel = 40;

}

bool Gorilla::isPaused() {

  return (this->pause > 0);

}

bool Gorilla::isReadyToLaunch() {

  return (this->pause > 25 && this->launchBarrel == 0);

}

uint8_t Gorilla::isInPosition() {

  switch (this->xPosition) {

    case GORILLA_X_POSITION_1:
      return 0;

    case GORILLA_X_POSITION_2:
      return 1;
      
    case GORILLA_X_POSITION_3:
      return 2;

    default: 
      return NOT_IN_A_POSITION;

  }

}

void Gorilla::moveToCentre() {

  this->moveCentre = true;

}

void Gorilla::incFallingIndex() {
  
  if (this->fallingIndex < 15) this->fallingIndex++;

}

void Gorilla::reset() {

    this->pause = 40;
    this->launchBarrel = 0;
    this->xPosition = GORILLA_X_POSITION_1;
    this->moveCentre = false;
    this->fallingIndex = 0;

}