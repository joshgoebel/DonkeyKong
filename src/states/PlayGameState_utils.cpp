#include "PlayGameState.h"

#include "../utils/Arduboy2Ext.h"
#include "../images/Images.h"
#include "../sounds/Sounds.h"

void PlayGameState::incPlateCounters() {

  if (this->hook.getCounter() == 0) {

    for (uint8_t x=0;x<3;x++) {
      this->plates[x].incCounter();
    }

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

        uint8_t const *imageSelfMasked = nullptr;
        uint8_t imageIndex = 0;

        switch (image) {
          
          case static_cast<uint8_t>(Components::Girder):
            imageSelfMasked = Images::Girder;
            break;
          
          case static_cast<uint8_t>(Components::Girder_OverHead):
            imageSelfMasked = Images::Girder_OverHead;
            break;
          
          case static_cast<uint8_t>(Components::Girder_Small):
            imageSelfMasked = Images::Girder_Small;
            break;

          
          // case static_cast<uint8_t>(Components::Plate1) ... static_cast<uint8_t>(Components::Plate3):
          //   {
          //     const uint8_t idx = image - static_cast<uint8_t>(Components::Plate1);
          //     const int8_t xOffset = this-> plates[idx].getXOffset();
          //     const uint8_t yOffset = this-> plates[idx].getYOffset();
          //     const uint8_t image = this-> plates[idx].getImage();
          //     Sprites::drawSelfMasked(x + xOffset, y + yOffset, Images::Plate, image);

          //   }
          //   break;
          
          case static_cast<uint8_t>(Components::Plate1):
            {
              const int8_t xOffset = this-> plates[0].getXOffset();
              const uint8_t yOffset = this-> plates[0].getYOffset();
              imageIndex = this-> plates[0].getImage();
              imageSelfMasked = Images::Plate;
            }
            break;

          case static_cast<uint8_t>(Components::Plate2):
            {
              const int8_t xOffset = this-> plates[1].getXOffset();
              const uint8_t yOffset = this-> plates[1].getYOffset();
              imageIndex = this-> plates[1].getImage();
              imageSelfMasked = Images::Plate;
            }
            break;
          
          case static_cast<uint8_t>(Components::Plate3):
            {
              const int8_t xOffset = this-> plates[2].getXOffset();
              const uint8_t yOffset = this-> plates[2].getYOffset();
              imageIndex = this-> plates[2].getImage();
              imageSelfMasked = Images::Plate;
            }
            break;
          
          case static_cast<uint8_t>(Components::Ladder):
            Sprites::drawExternalMask(x, y, Images::Ladder, Images::Ladder_Mask, 0, 0);
            break;
          
          case static_cast<uint8_t>(Components::Lever):
            imageSelfMasked = Images::Lever;
            imageIndex = static_cast<uint8_t>(this->lever.getPosition());
            break;
          
          case static_cast<uint8_t>(Components::Cable1):
            Sprites::drawExternalMask(x, y, Images::Cable_1, Images::Cable_1_Mask, 0, 0);
            break;
          
          case static_cast<uint8_t>(Components::Cable2):
            Sprites::drawExternalMask(x, y, Images::Cable_2, Images::Cable_2_Mask, 0, 0);
            break;
          
          case static_cast<uint8_t>(Components::Crane):
            imageSelfMasked = Images::Crane;
            imageIndex = this->crane.getImage();
            break;
          
          case static_cast<uint8_t>(Components::Hook):
            imageSelfMasked = Images::Hook;
            imageIndex = this->hook.getCounter();
            break;
          
          case static_cast<uint8_t>(Components::Fire):
            imageSelfMasked = Images::Fire;
            imageIndex = this->fire.getCounter();
            break;
          
          case static_cast<uint8_t>(Components::Spaghetti):
            if (this->spaghetti.isVisible()) {
              imageSelfMasked = Images::Spaghetti;
              imageIndex = this->spaghetti.getCounter();
            }
            break;
          
          case static_cast<uint8_t>(Components::Fire_Foreground):
            Sprites::drawExternalMask(x, y, Images::Fire_Foreground, Images::Fire_Foreground_Mask, 0, 0);
            break;
          
          case static_cast<uint8_t>(Components::EasyHard):
            Sprites::drawExternalMask(x, y, Images::Mode, Images::Mode_Mask, static_cast<uint8_t>(gameStats.mode), 0);
            break;
          
          case static_cast<uint8_t>(Components::LivesLeft1):
            if (gameStats.numberOfLivesLeft >= 1) {
              imageSelfMasked = Images::LivesLeft;
            }
            break;
          
          case static_cast<uint8_t>(Components::LivesLeft2):
            if (gameStats.numberOfLivesLeft >= 2) {
              imageSelfMasked = Images::LivesLeft;
            }
            break;
          
          case static_cast<uint8_t>(Components::LivesLeft3):
            if (gameStats.numberOfLivesLeft >= 3) {
              imageSelfMasked = Images::LivesLeft;
            }
            break;
            
        }

        if (imageSelfMasked != nullptr) {
          Sprites::drawSelfMasked(x, y, imageSelfMasked, imageIndex);
        }

      }

    }

  }

}


uint8_t PlayGameState::getActiveGirderCount() {

  return (this->girders[0].isEnabled() ? 1 : 0) + (this->girders[1].isEnabled() ? 1 : 0);

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

void PlayGameState::resetLevel(uint8_t introDelay) {

  this->introDelay = introDelay;
  this->lever.setPosition(LeverPosition::Off);
  this->showLivesLeft = false;
  this->playing = false;

}

void PlayGameState::removeLowerBarrels() {


  // Remove any barrels in the home leg of the game ..

  for (auto &barrel : this->barrels) {

    if (barrel.getPosition() > 170) {
      
      barrel.setPosition(0);
      barrel.setEnabled(false);

    }

  }

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

  this->hook.setCounter(4); //SJH

}