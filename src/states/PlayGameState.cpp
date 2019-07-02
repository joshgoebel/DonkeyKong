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


  //           Crane* ptr_Barrel = &this->crane;

  // this->lever.setCrane(ptr_Barrel);

  this->lever.setCrane(&crane);

  for (auto &barrel : this->barrels) {

    if (random(0, 2) == 0) {

      barrel.setPosition(random(4, 180));
      barrel.setEnabled(true);

    }

  }

  this->playing = false;
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
  auto justPressed = arduboy.justPressedButtons();

  if (!BaseState::getPaused()) {


    //Handle player movements ..

    if (this->playing && arduboy.everyXFrames(2)) {
      
      if (!this->player.isJumping()) {

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

        if ((pressed & A_BUTTON) && this->player.canMove(Movements::Jump)) {
          this->player.startJump();
        }

      }
      else {

        this->player.updateJump();

      }

    }


    // Handle crane

    if (arduboy.everyXFrames(2)) {

      this->crane.update();

    }


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

      if (arduboy.everyXFrames(8)) {

        for (auto &barrel : this->barrels) {

          if (barrel.isEnabled()) {

            barrel.updatePosition();
            barrel.rotate();

          }

        }

      }

    }


    // Update girders ..

    if (gameStats.mode == GameMode::Hard) {

      if (arduboy.everyXFrames(10)) {

        for (auto &girder : this->girders) {

          if (girder.isEnabled()) {

            girder.updatePosition();

          }

        }

      }

    }

    uint8_t activeGirderCount = getActiveGirderCount();
    uint8_t girderMaxPosition = getGirderMaxPosition();

    if ((activeGirderCount == 0 || (activeGirderCount < 2 && girderMaxPosition > 50)) && (random(0, 50) == 0)) {

      uint8_t girderIndex = getDisabledGirderIndex();

      Girder &girder = this->girders[girderIndex];
      girder.setEnabled(true);

    }


    //Update lever

    if (arduboy.everyXFrames(4)) {

      this->lever.update();

    }
    

    // Move gorilla

    this->gorilla.move();


    // Update fire
    if (arduboy.everyXFrames(12)) {
      this->fire.update();
    }

  }

  // Handle other buttons ..

  if (!this->playing && !gameStats.gameOver) {

    if ((justPressed & A_BUTTON) || (justPressed & B_BUTTON)) {

      //sound.tones(Sounds::PackageNotDelivered);
      this->playing = true;
      this->player.initLife();

    }

  }
  else {  
    BaseState::handleCommonButtons(machine);
  }


Serial.print(this->player.getXPosition());
Serial.print(" ");
Serial.println(this->player.getYPosition());
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

  {
    Sprites::drawSelfMasked(this->player.getXPosition(), this->player.getYPosition(), Images::Mario, 0);

  }


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

  if (!this->playing && !gameStats.gameOver) {

    Sprites::drawExternalMask(27, 20, Images::PlayerFrame, Images::PlayerFrame_Mask, 0, 0);
    Sprites::drawSelfMasked(79, 23, Images::Player_Number, gameStats.numberOfLivesLeft - 1);

  }
  else {

    BaseState::renderGameOverOrPause(machine);

  }

  arduboy.display(true);

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
          
          case static_cast<uint8_t>(Components::Fire):
            Sprites::drawSelfMasked(x, y, Images::Fire, this->fire.getCounter());
            break;
          
          case static_cast<uint8_t>(Components::Fire_Foreground):
            Sprites::drawExternalMask(x, y, Images::Fire_Foreground, Images::Fire_Foreground_Mask, 0, 0);
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