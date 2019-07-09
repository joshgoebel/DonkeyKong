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

        Sprites::drawExternalMask(barrel.getXPosition(), barrel.getYPosition(yOffset), Images::BarrelImg, Images::Barrel_Mask, barrel.getRotation(), 0);

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

    if (mask == nullptr) {
      Sprites::drawSelfMasked(this->player.getXPosition(true), this->player.getYPosition(), imageName, image);
    }
    else {
      Sprites::drawExternalMask(this->player.getXPosition(true), this->player.getYPosition(), imageName, mask, image, image);
    }

  }


  // Draw gorilla ..

  Sprites::drawSelfMasked(this->gorilla.getXPosition(), this->gorilla.getYPosition(yOffset), Images::Gorilla, static_cast<uint8_t>(this->gorilla.getStance()) );


  // Draw girders ..

  if (gameStats.mode == GameMode::Hard) {

    for (auto &girder : this->girders) {

      if (girder.isEnabled()) {

        Sprites::drawExternalMask(girder.getXPosition(), girder.getYPosition(yOffset), Images::Girder_Moving, Images::Girder_Moving_Mask, girder.getImage(), girder.getImage());

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