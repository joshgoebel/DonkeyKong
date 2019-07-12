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

    int8_t x = pgm_read_byte(&Coordinates::Scenery[(i * 3)]);
    int8_t y = pgm_read_byte(&Coordinates::Scenery[(i * 3) + 1]) - yOffset;
    uint8_t image = pgm_read_byte(&Coordinates::Scenery[(i * 3) + 2]) & 0x1F;
    uint8_t mode = pgm_read_byte(&Coordinates::Scenery[(i * 3) + 2]) & 0xC0;

    if ( ((paintMode == SCENERY_PAINT_FIRST) && ((mode & SCENERY_PAINT_LAST) == 0)) || 
         ((paintMode == SCENERY_PAINT_LAST) && ((mode & SCENERY_PAINT_LAST) > 0))
       ) {

      if ((gameStats.mode == GameMode::Hard) || !((mode & SCENERY_LEVEL_2_ONLY) > 0)) {

        uint8_t const *imageName = nullptr;
        uint8_t const *mask = nullptr;
        uint8_t imageIndex = 0;
        int8_t xOffset = 0;
        int8_t yOffset = 0;

        switch (image) {
          
          case static_cast<uint8_t>(Components::Girder):
            imageName = Images::Girder;
            break;
          
          case static_cast<uint8_t>(Components::Girder_OverHead):
            imageName = Images::Girder_OverHead;
            break;
          
          case static_cast<uint8_t>(Components::Girder_Small):
            imageName = Images::Girder_Small;
            break;
          
          case static_cast<uint8_t>(Components::Plate1):
            {
              xOffset = this-> plates[0].getXOffset();
              yOffset = this-> plates[0].getYOffset();
              imageIndex = this-> plates[0].getImage();
              imageName = Images::Plate;
            }
            break;

          case static_cast<uint8_t>(Components::Plate2):
            {
              yOffset = this->plates[1].getYOffset();
              imageIndex = this->plates[1].getImage();
              imageName = Images::Plate;
            }
            break;
          
          case static_cast<uint8_t>(Components::Plate3):
            {
              xOffset = this-> plates[2].getXOffset();
              yOffset = this->plates[2].getYOffset();
              imageIndex = this->plates[2].getImage();
              imageName = Images::Plate;
            }
            break;
          
          case static_cast<uint8_t>(Components::Ladder):
            imageName = Images::Ladder;
            mask = Images::Ladder_Mask;
            break;
          
          case static_cast<uint8_t>(Components::Lever):
            imageName = Images::Lever;
            imageIndex = static_cast<uint8_t>(this->lever.getPosition());
            break;
          
          case static_cast<uint8_t>(Components::Cable1):
            imageName = Images::Cable_1;
            mask = Images::Cable_1_Mask;
            break;
          
          case static_cast<uint8_t>(Components::Cable2):
            imageName = Images::Cable_2;
            mask = Images::Cable_2_Mask;
            break;
          
          case static_cast<uint8_t>(Components::Crane):
            imageName = Images::Crane;
            imageIndex = this->crane.getImage();
            break;
          
          case static_cast<uint8_t>(Components::Hook):
            imageName = Images::Hook;
            imageIndex = this->hook.getCounter();
            break;
          
          case static_cast<uint8_t>(Components::Fire):
            imageName = Images::Fire;
            imageIndex = this->fire.getCounter();
            break;
          
          case static_cast<uint8_t>(Components::Spaghetti):
            if (this->spaghetti.isVisible()) {
              uint8_t food = this->spaghetti.getFood();
              imageName = Images::Spaghetti;
              imageIndex = (food * 3) + (food < 2 ? this->spaghetti.getCounter() : 0);
            }
            break;
          
          case static_cast<uint8_t>(Components::Fire_Foreground):
            imageName = Images::Fire_Foreground;
            mask = Images::Fire_Foreground_Mask;
            break;
          
          case static_cast<uint8_t>(Components::EasyHard):
            imageName = Images::Mode;
            mask = Images::Mode_Mask;
            imageIndex = static_cast<uint8_t>(gameStats.mode);
            break;
          
          case static_cast<uint8_t>(Components::LivesLeft1):
            if (gameStats.numberOfLivesLeft >= 1) {
              imageName = Images::LivesLeft;
            }
            break;
          
          case static_cast<uint8_t>(Components::LivesLeft2):
            if (gameStats.numberOfLivesLeft >= 2) {
              imageName = Images::LivesLeft;
            }
            break;
          
          case static_cast<uint8_t>(Components::LivesLeft3):
            if (gameStats.numberOfLivesLeft >= 3) {
              imageName = Images::LivesLeft;
            }
            break;
            
        }

        if (imageName != nullptr) {

          if (mask == nullptr) {
            Sprites::drawSelfMasked(x + xOffset, y + yOffset, imageName, imageIndex);
          }
          else {
            Sprites::drawExternalMask(x + xOffset, y + yOffset, imageName, mask, imageIndex, 0);
          }
          
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

  this->hook.setCounter(NUMBER_OF_HOOKS); //SJH

}

void PlayGameState::updatePlayerAndCrane(CranePosition position) {

    this->player.incPlayerPosition();
    this->crane.setPosition(position);

}