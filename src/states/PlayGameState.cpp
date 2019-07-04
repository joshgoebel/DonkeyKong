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

  if (!BaseState::getPaused() && !this->player.isDead()) {


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

    uint8_t yOffset = this->player.getYOffset();


    // Handle crane

    if (arduboy.everyXFrames(2)) {

      this->crane.update();

    }


    // Handle Barrels
    {

      // Should we launch a new barrel?

// can we?
//0, 31 - 59   ,0 - 30
/* 
      bool launch = true;
      uint8_t gorillaPosition = this->gorilla.isInPosition();

      if (gorillaPosition != NOT_IN_A_POSITION) {
      
        for (auto &barrel : this->barrels) {

          if (barrel.isEnabled()) {

            switch (barrel.getPosition()) {

              case BARREL_POSITION_3_START ... BARREL_POSITION_3_START + BARREL_POSITION_3_COUNT - 1: // 3

                switch (gorillaPosition) {

                  case 0:
                    if (barrel.getPosition() - BARREL_POSITION_3_COUNT - BARREL_POSITION_2_COUNT < 11) launch = false;
                    break;

                  case 1:
                    if (barrel.getPosition() < 11) launch = false;
                    break;

                  case 2:
                    if (barrel.getPosition() < 11) launch = false;
                    break;
                  
                }

                break;

              case BARREL_POSITION_2_START ... BARREL_POSITION_2_START + BARREL_POSITION_2_COUNT - 1: // 2
                break;

              case BARREL_POSITION_1_START ... BARREL_POSITION_1_START + BARREL_POSITION_1_COUNT - 1: // 1
                break;

            }

          }

        }

      }
      else {
        launch = false;
      }
*/

      if (this->gorilla.isReadyToLaunch() && random(0, 40) == 0) {

        for (auto &barrel : this->barrels) {

          if (!barrel.isEnabled()) {

            Barrel* ptr_Barrel = &barrel;
            this->gorilla.launch(ptr_Barrel);
            break;

          }

        }

      }

      if (arduboy.everyXFrames(6)) {

        for (auto &barrel : this->barrels) {

          if (barrel.isEnabled()) {

Serial.print(barrel.getPosition());
Serial.print(", ");

            if (this->playing && this->player.isJumping()) {

              int8_t barrelX = barrel.getXPosition();
              int16_t barrelY = static_cast<uint16_t>(barrel.getYPosition(yOffset));
              uint8_t playerX = this->player.getXPosition();
              int16_t playerY = static_cast<int16_t>(this->player.getYPosition());

              if ((barrelX == playerX) && (playerY - barrelY <= 8)) {

                gameStats.score++;

              }

            }

            Rect playerRect = this->player.getRect();
            Rect barrelRect = barrel.getRect(yOffset);

            if (this->playing && arduboy.collide(this->player.getRect(), barrel.getRect(yOffset)) ) {

#ifndef BARRELS
              this->player.setDead(true);
              this->playing = false;
              this->deadCounter = 100;
              gameStats.numberOfLivesLeft--;
              Serial.println("hit barrel");
#endif
            }

            barrel.updatePosition();
            barrel.rotate();

          }

        }

Serial.println("");


      }

    }


    // Update girders ..

    if (gameStats.mode == GameMode::Hard) {

      if (arduboy.everyXFrames(10)) {

        for (auto &girder : this->girders) {

          if (girder.isEnabled()) {

            girder.updatePosition();

            if (this->playing && arduboy.collide(this->player.getRect(), girder.getRect(yOffset)) ) {
              this->player.setDead(true);
              this->playing = false;
              this->deadCounter = 100;
              gameStats.numberOfLivesLeft--;
              Serial.println("hit girder");
            }

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


    // Update fire and spaghetti ..

    if (arduboy.everyXFrames(12)) {
      this->fire.update();
      this->spaghetti.update();
    }

  }


  // Dead counter

  if (gameStats.numberOfLivesLeft == 0) {

    gameStats.gameOver = true;

  }

  switch (this->deadCounter) {

    case 2 ... 255:
      this->deadCounter--;
      break;

    case 1:
      this->player.setPosition(0);
      this->player.setDead(false);
      this->player.setJumpPosition(0);
      this->deadCounter--;
      break;

    default:
      break;

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


// Serial.print(this->player.getXPosition());
// Serial.print(" ");
// Serial.println(this->player.getYPosition());
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
          
          case static_cast<uint8_t>(Components::Spaghetti):
            Sprites::drawSelfMasked(x, y, Images::Spaghetti, this->spaghetti.getCounter());
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




// ----------------------------------------------------------------------------
//  Render the state .. 
//
void PlayGameState::render(StateMachine & machine) {

	auto & arduboy = machine.getContext().arduboy;
  auto & gameStats = machine.getContext().gameStats;
  
  const uint8_t yOffset = this->player.getYOffset();
  const bool flash = arduboy.getFrameCountHalf(FLASH_FRAME_COUNT);

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

  if (this->playing || flash) {

    Sprites::drawExternalMask(this->player.getXPosition(), this->player.getYPosition(), Images::Mario, Images::Mario_Mask, this->player.getImage(), this->player.getImage());

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

  if (!this->playing && !gameStats.gameOver && this->deadCounter == 0) {

    Sprites::drawExternalMask(27, 20, Images::PlayerFrame, Images::PlayerFrame_Mask, 0, 0);
    Sprites::drawSelfMasked(79, 23, Images::Player_Number, gameStats.numberOfLivesLeft - 1);

  }
  else {

    BaseState::renderGameOverOrPause(machine);

  }


  // Render score ..

  BaseState::renderScore(machine, false, 0);

  arduboy.display(true);

}