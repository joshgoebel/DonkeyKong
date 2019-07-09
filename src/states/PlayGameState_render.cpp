#include "PlayGameState.h"

#include "../utils/Arduboy2Ext.h"
#include "../images/Images.h"
#include "../sounds/Sounds.h"


// ----------------------------------------------------------------------------
//  Render the state .. 
//
void PlayGameState::render(StateMachine & machine) {

	auto & arduboy = machine.getContext().arduboy;
  auto & gameStats = machine.getContext().gameStats;
  
  const uint8_t yOffset = this->player.getYOffset();
  const bool flash = arduboy.getFrameCountHalf(FLASH_FRAME_COUNT);


  // Draw Scenery ..
  
  this->drawScenery(machine, SCENERY_PAINT_FIRST);


  // Draw Barrels
  {

    for (auto &barrel : this->barrels) {

      if (barrel.isEnabled()) {

        int8_t x = barrel.getXPosition();
        int8_t y = barrel.getYPosition(yOffset);
        uint8_t r = barrel.getRotation();
        Sprites::drawExternalMask(x, y, Images::BarrelImg, Images::Barrel_Mask, r, 0);

      }

    }

  }


  // Draw player

  if (this->playing || flash) {

    uint8_t const *imageName = nullptr;
    uint8_t const *mask = nullptr;
    uint8_t image = this->player.getImage();

    switch (image) {

      case static_cast<uint8_t>(Stance::Normal) ... static_cast<uint8_t>(Stance::OnCrane_RHS):
        imageName = Images::Mario;
        mask = Images::Mario_Mask;
        break;

      case static_cast<uint8_t>(Stance::Dead_01) ... static_cast<uint8_t>(Stance::Dead_03):
        imageName = Images::Mario_Dying;
        image = image - static_cast<uint8_t>(Stance::Dead_01);
        break;

      case static_cast<uint8_t>(Stance::OnCrane_EmptyHand) ... static_cast<uint8_t>(Stance::OnCrane_HoldingHook):
        imageName = Images::Mario_Leaping;
        image = image - static_cast<uint8_t>(Stance::OnCrane_EmptyHand);
        break;

    }

    {

      int8_t x = this->player.getXPosition(true);
      int8_t y = this->player.getYPosition();

      if (mask == nullptr) {
        Sprites::drawSelfMasked(x, y, imageName, image);
      }
      else {
        Sprites::drawExternalMask(x, y, imageName, mask, image, image);
      }

    }

  }


  // Draw gorilla ..
  {
    uint8_t x = this->gorilla.getXPosition();
    int8_t y = this->gorilla.getYPosition(yOffset);
    uint8_t stance = static_cast<uint8_t>(this->gorilla.getStance());
    Sprites::drawSelfMasked(x, y, Images::Gorilla, stance );
  }


  // Draw girders ..

  if (gameStats.mode == GameMode::Hard) {

    for (auto &girder : this->girders) {

      if (girder.isEnabled()) {
  
        int8_t x = girder.getXPosition();
        int8_t y = girder.getYPosition(yOffset);
        uint8_t index = girder.getImage();
        Sprites::drawExternalMask(x, y, Images::Girder_Moving, Images::Girder_Moving_Mask, index, index);
  
      }

    }

  }

  this->drawScenery(machine, SCENERY_PAINT_LAST);

  if (!gameStats.gameOver && this->showLivesLeft) {

    Sprites::drawExternalMask(27, 20, Images::PlayerFrame, Images::PlayerFrame_Mask, 0, 0);
    Sprites::drawSelfMasked(79, 23, Images::Player_Number, gameStats.numberOfLivesLeft - 1);

  }
  else {

    BaseState::renderGameOverOrPause(machine);

  }


  // Render score ..

  BaseState::renderScore(machine, 0);

  arduboy.display(true);

}