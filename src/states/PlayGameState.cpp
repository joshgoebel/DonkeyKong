#include "PlayGameState.h"

#include "../utils/Arduboy2Ext.h"
#include "../images/Images.h"
#include "../sounds/Sounds.h"


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void PlayGameState::activate(StateMachine & machine) {

  auto & gameStats = machine.getContext().gameStats;
  auto & arduboy = machine.getContext().arduboy;
  auto & sound = machine.getContext().sound;  

  for (auto &barrel : this->barrels) {

    if (random(0, 2) == 0) {

      barrel.setPosition(random(4, 180));
      barrel.setEnabled(true);

    }

  }

  BaseState::setPaused(false);

  sound.setOutputEnabled(arduboy.audio.enabled);

}
  

// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void PlayGameState::update(StateMachine & machine) { 

	auto & arduboy = machine.getContext().arduboy;
  auto & gameStats = machine.getContext().gameStats;
  auto & sound = machine.getContext().sound;  
	auto pressed = arduboy.pressedButtons();

  if (!BaseState::getPaused()) {


    //Handle player movements ..
    {
      
      if (this->player.canMove(Movements::Reverse)) {

        if ((pressed & LEFT_BUTTON) && this->player.canMove(Movements::Left)) {
          this->player.incPlayerPosition();
        }

        if ((pressed & RIGHT_BUTTON) && this->player.canMove(Movements::Right)) {
          this->player.decPlayerPosition();
        }


      }
      else {

        if ((pressed & LEFT_BUTTON) && this->player.canMove(Movements::Left)) {
          this->player.decPlayerPosition();
        }

        if ((pressed & LEFT_BUTTON) && this->player.canMove(Movements::Lever)) {
          this->lever.setPosition(LeverPosition::On);
          this->crane.turnOn();
        }

        if ((pressed & RIGHT_BUTTON) && this->player.canMove(Movements::Right)) {
          this->player.incPlayerPosition();
        }

      }

      if ((pressed & DOWN_BUTTON) && this->player.canMove(Movements::Down)) {
        this->player.decPlayerPosition();
      }

      if ((pressed & UP_BUTTON) && this->player.canMove(Movements::Up)) {
        this->player.incPlayerPosition();
      }

    }


    // Handle crane
    this->crane.update();


    // Handle Barrels
    {

      // Should we launch a new barrel?

      if (this->gorilla.isReadyToLaunch() && random(0, 40) == 0) {

        for (auto &barrel : this->barrels) {

          if (!barrel.isEnabled()) {

            Barrel* ptr_Barrel = &barrel;
            this->gorilla.launch(ptr_Barrel);
            break;

          }

        }

      }

    }


    // Update girders ..

    if (arduboy.everyXFrames(4)) {

      for (auto &girder : this->girders) {

        if (girder.isEnabled()) {

          girder.updatePosition();

        }

      }

    }

    uint8_t activeGirderCount = getActiveGirderCount();
    uint8_t girderMaxPosition = getGirderMaxPosition();

    if ((activeGirderCount == 0 || (activeGirderCount == 1 < 2 && girderMaxPosition > 50)) && random(0, 50) == 0) {

      uint8_t girderIndex = getDisabledGirderIndex();

      Girder &girder = this->girders[girderIndex];
      girder.setEnabled(true);

    }


    //Update lever

    this->lever.update();
    
    // Draw gorilla

    this->gorilla.move();

  }
  else {  
    BaseState::handleCommonButtons(machine);
  }

}



// ----------------------------------------------------------------------------
//  Render the state .. 
//
void PlayGameState::render(StateMachine & machine) {

	auto & arduboy = machine.getContext().arduboy;
  auto & gameStats = machine.getContext().gameStats;
  
  uint8_t yOffset = this->player.getYOffset();

  BaseState::renderCommonScenery(machine);

  // Draw Scenery ..
  {
    for (uint8_t i = 0; i < SCENERY_COUNT; i++) {

      int8_t x = pgm_read_byte(&Coordinates::Scenery[(i * 4)]);
      int8_t y = pgm_read_byte(&Coordinates::Scenery[(i * 4) + 1]) - yOffset;
      uint8_t image = pgm_read_byte(&Coordinates::Scenery[(i * 4) + 2]);
      uint8_t mode = pgm_read_byte(&Coordinates::Scenery[(i * 4) + 3]);

      if (mode <= static_cast<uint8_t>(gameStats.mode)) {

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
            Sprites::drawSelfMasked(x, y, Images::Plate_1, 0);
            break;
          
          case static_cast<uint8_t>(Components::Plate2):
            Sprites::drawSelfMasked(x, y, Images::Plate_2, 0);
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
            Sprites::drawSelfMasked(x, y, Images::Hook, 0);
            break;
            
        }

      }

    }

  }

  // Draw Barrels
  {

    for (auto &barrel : this->barrels) {

      if (barrel.isEnabled()) {

        Sprites::drawExternalMask(barrel.getXPosition(), barrel.getYPosition(yOffset), Images::BarrelImg, Images::Barrel_Mask, barrel.getRotation(), 0);

        if (arduboy.everyXFrames(4)) {

          barrel.updatePosition();
          barrel.rotate();

        }

      }

    }

  }

  // Draw player

  {
    Sprites::drawSelfMasked(this->player.getXPosition(), this->player.getYPosition(), Images::Mario, 0);

  }


  Sprites::drawSelfMasked(this->gorilla.getXPosition(), this->gorilla.getYPosition(yOffset), Images::Gorilla, static_cast<uint8_t>(this->gorilla.getStance()) );


  // Draw girders ..

  for (auto &girder : this->girders) {

    if (girder.isEnabled()) {

      Sprites::drawExternalMask(girder.getXPosition(), girder.getYPosition(yOffset), Images::Girder_Moving, Images::Girder_Moving_Mask, girder.getImage(), girder.getImage());

    }

  }


  if (!this->playing && !gameStats.gameOver) {

    Sprites::drawExternalMask(27, 20, Images::PlayerFrame, Images::PlayerFrame_Mask, 0, 0);
    Sprites::drawSelfMasked(79, 23, Images::Player_Number, gameStats.numberOfLivesLeft - 1);

  }
  else {

    BaseState::renderGameOverOrPause(machine);

  }

  arduboy.display(true);

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