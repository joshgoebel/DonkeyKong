#include "PlayGameState.h"

#include "../utils/Arduboy2Ext.h"
#include "../images/Images.h"
#include "../sounds/Sounds.h"

void PlayGameState::incPlateCounters() {

  if (this->hook.getCounter() == 0) {

    this->plates[0].incCounter();
    this->plates[1].incCounter();
    this->plates[2].incCounter();
    this->gorilla.incFallingIndex();

  }

}

uint8_t PlayGameState::drawScenery(StateMachine & machine, uint8_t paintMode) {

  auto & gameStats = machine.getContext().gameStats;

  uint8_t yOffset = this->player.getYOffset();

  for (uint8_t i = 0; i < SCENERY_COUNT; i++) {

    int8_t x = pgm_read_byte(&Coordinates::Scenery[(i * 4)]);
    int8_t y = pgm_read_byte(&Coordinates::Scenery[(i * 4) + 1]) - yOffset;
    uint8_t image = pgm_read_byte(&Coordinates::Scenery[(i * 4) + 2]);
    uint8_t mode = pgm_read_byte(&Coordinates::Scenery[(i * 4) + 3]);

    if (paintMode & mode) {

      if ((gameStats.mode == GameMode::Hard) || !(mode & static_cast<uint8_t>(GameMode::Hard))) {

        switch (image) {
          
          case static_cast<uint8_t>(Components::Girder):
            Sprites::drawSelfMasked(x, y, Images::Girder, 0);
            break;
          
          case static_cast<uint8_t>(Components::Girder_OverHead):
            Sprites::drawSelfMasked(x, y, Images::Girder_OverHead, 0);
            break;
          
          case static_cast<uint8_t>(Components::Girder_Small):
            Sprites::drawSelfMasked(x, y, Images::Girder_Small, 0);
            break;
          
          case static_cast<uint8_t>(Components::Plate1):
            {
              const int8_t xOffset = this-> plates[0].getXOffset();
              const uint8_t yOffset = this-> plates[0].getYOffset();
              const uint8_t image = this-> plates[0].getImage();
              Sprites::drawSelfMasked(x + xOffset, y + yOffset, Images::Plate, image);

            }
            break;
          
          case static_cast<uint8_t>(Components::Plate2):
            {
              const int8_t xOffset = this-> plates[1].getXOffset();
              const uint8_t yOffset = this-> plates[1].getYOffset();
              const uint8_t image = this-> plates[1].getImage();
              Sprites::drawSelfMasked(x - xOffset, y + yOffset, Images::Plate, image);

            }
            break;
          
          case static_cast<uint8_t>(Components::Plate3):
            {
              const int8_t xOffset = this-> plates[2].getXOffset();
              const uint8_t yOffset = this-> plates[2].getYOffset();
              const uint8_t image = this-> plates[2].getImage();
              Sprites::drawSelfMasked(x + xOffset, y + yOffset, Images::Plate, image);
            }
            break;
          
          case static_cast<uint8_t>(Components::Ladder):
            Sprites::drawExternalMask(x, y, Images::Ladder, Images::Ladder_Mask, 0, 0);
            break;
          
          case static_cast<uint8_t>(Components::Lever):
            Sprites::drawSelfMasked(x, y, Images::Lever, static_cast<uint8_t>(this->lever.getPosition()));
            break;
          
          case static_cast<uint8_t>(Components::Cable1):
            Sprites::drawExternalMask(x, y, Images::Cable_1, Images::Cable_1_Mask, 0, 0);
            break;
          
          case static_cast<uint8_t>(Components::Cable2):
            Sprites::drawExternalMask(x, y, Images::Cable_2, Images::Cable_2_Mask, 0, 0);
            break;
          
          case static_cast<uint8_t>(Components::Crane):
            Sprites::drawSelfMasked(x, y, Images::Crane, this->crane.getImage());
            break;
          
          case static_cast<uint8_t>(Components::Hook):
            Sprites::drawSelfMasked(x, y, Images::Hook, this->hook.getCounter());
            break;
          
          case static_cast<uint8_t>(Components::Fire):
            Sprites::drawSelfMasked(x, y, Images::Fire, this->fire.getCounter());
            break;
          
          case static_cast<uint8_t>(Components::Spaghetti):
            Sprites::drawSelfMasked(x, y, Images::Spaghetti, this->spaghetti.getCounter());
            break;
          
          case static_cast<uint8_t>(Components::Fire_Foreground):
            Sprites::drawExternalMask(x, y, Images::Fire_Foreground, Images::Fire_Foreground_Mask, 0, 0);
            break;
          
          case static_cast<uint8_t>(Components::EasyHard):
            Sprites::drawExternalMask(x, y, Images::Mode, Images::Mode_Mask, static_cast<uint8_t>(gameStats.mode), 0);
            break;
            
        }

      }

    }

  }

}


uint8_t PlayGameState::getActiveGirderCount() {

  uint8_t girderCount = 0;

  for (auto &girder : this->girders) {

      if (girder.isEnabled()) {

        girderCount++;

      }
  
  }

  return girderCount;

}

uint8_t PlayGameState::getGirderMaxPosition() {

  uint8_t girderPosition = 0;

  for (auto &girder : this->girders) {

      if (girder.isEnabled() && girder.getPosition() > girderPosition) {

        girderPosition = girder.getPosition();

      }
  
  }

  return girderPosition;
  
}


#define GIRDER_COUNT 2
#define NONE_FOUND 255

uint8_t PlayGameState::getDisabledGirderIndex() {

  for (uint8_t x = 0; x < GIRDER_COUNT; x++) {

      Girder girder = this->girders[x];

      if (!girder.isEnabled()) {

        return x;

      }
  
  }

  return NONE_FOUND;
  
}

void PlayGameState::killPlayer(StateMachine & machine) {

  auto & gameStats = machine.getContext().gameStats;

  this->player.setDead(true);
  this->playing = false;
  this->introDelay = 200;
  this->showLivesLeft = false;
  this->lever.setPosition(LeverPosition::Off);
  gameStats.numberOfLivesLeft--;

}

void PlayGameState::resetLevel() {

  this->introDelay = 200;
  this->lever.setPosition(LeverPosition::Off);
  this->showLivesLeft = false;
  this->playing = false;


}

void PlayGameState::resetGorillaAndPlates() {

  // Reset plates ..

  for (uint8_t x = 0; x < 3; x++) {

    plates[x].setPlateNumber(x);
    plates[x].setCounter(0);

  }

  // Reset gorilla ..

  this->gorilla.reset();


  // Reset hook ..

  this->hook.setCounter(4);

}