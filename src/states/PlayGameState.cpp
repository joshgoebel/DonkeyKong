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
  this->player.reset();

  for (uint8_t x = 0; x < 3; x++) {

    plates[x].setPlateNumber(x);

  }

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
Serial.print("Player pos :");
Serial.print(this->player.getPosition());
Serial.print(" x");
Serial.print(this->player.getXPosition(false));
Serial.print(",y ");
Serial.print(this->player.getYPosition());
Serial.print(" Crane :");
Serial.print(static_cast<uint8_t>(this->crane.getPosition())); 
Serial.print(" s :");
Serial.print(PLAYER_CRANE_END); 
Serial.print(" e :");
Serial.println(PLAYER_DIE_START); 

    //Handle player movements ..

    if (this->playing && arduboy.everyXFrames(2)) {

      if (!this->player.isJumping() && !this->player.isLeaping() && !this->player.isFalling()) {

        if (this->player.canMove(Movements::Reverse)) {

          if ((pressed & LEFT_BUTTON) && this->player.canMove(Movements::Left)) {
            this->player.incPlayerPosition();
          }

          if ((pressed & RIGHT_BUTTON) && this->player.canMove(Movements::Right)) {
            this->player.decPlayerPosition();
          }


        }
        else {

          if (pressed & RIGHT_BUTTON) {
          
            if ((pressed & A_BUTTON) && this->player.canMove(Movements::JumpToCrane)) {
              this->player.setLeaping(true);
              this->player.incPlayerPosition();
              pressed = 0;

            }
            else {

              if (this->player.canMove(Movements::Right)) {

                if (this->player.getPosition() == END_OF_TOP_LEVEL) {
                  this->player.setFalling(true);
                  this->player.setPosition(PLAYER_RUNOFF_START);
                }
                else {
                  this->player.incPlayerPosition();
                }
              
              }

            }

          }


          if ((pressed & LEFT_BUTTON) && this->player.canMove(Movements::Left)) {
            this->player.decPlayerPosition();
          }

          if ((pressed & LEFT_BUTTON) && this->player.canMove(Movements::Lever)) {
            this->lever.setPosition(LeverPosition::On);
            this->crane.turnOn();
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
      // Player is jumping, falling or leaping ..
      else {

        if (this->player.isJumping()) {
          this->player.updateJump();
        }

        if (this->player.isFalling() && arduboy.everyXFrames(4)) {

          switch (this->player.getPosition()) {

            case PLAYER_RUNOFF_END - 1:
              this->killPlayer(machine);
              break;

            default:  
              this->player.incPlayerPosition();
              break;

          }

        }

        if (this->player.isLeaping() && arduboy.everyXFrames(4)) {

          const uint8_t cranePosLeft = static_cast<uint8_t>(CranePosition::Inclined_01);
          const uint8_t cranePosRight = static_cast<uint8_t>(CranePosition::Inclined_02);
          const uint16_t playerPos = this->player.getPosition();

          uint8_t cranePos = static_cast<uint8_t>(this->crane.getPosition());

          // Start plate action after a period of time ..
          if (playerPos >= PLAYER_CRANE_LIFT_01 && playerPos < PLAYER_CRANE_END) {
            this->incPlateCounters();
          }

          switch (playerPos) {

            case LEAP_DECISION_POINT - 1: 
              if (cranePos > cranePosLeft && cranePos <= cranePosRight) {
                this->crane.setLiftPlayer(true);
                this->player.incPlayerPosition();
              }
              this->player.incPlayerPosition();
              break;

            case LEAP_DECISION_POINT:
              if (false) {//cranePos == cranePosLeft || cranePos > cranePosRight) {
//SJH              if (cranePos == cranePosLeft || cranePos > cranePosRight) {
                this->player.setPosition(PLAYER_DIE_START);
              }
              else {
                this->crane.setPosition(CranePosition::Inclined_02);
                this->crane.setLiftPlayer(true);
                this->player.incPlayerPosition();
              }
              break;

            case PLAYER_CRANE_LIFT_01 - 1:
              this->player.incPlayerPosition();
              this->crane.setPosition(CranePosition::Upright_01);
              this->gorilla.moveToCentre();
              break;

            case PLAYER_CRANE_LIFT_02 - 1:
              this->player.incPlayerPosition();
              this->crane.setPosition(CranePosition::Upright_02);
              this->hook.decCounter();
              break;

            case PLAYER_CRANE_LIFT_03 - 1:
              this->player.incPlayerPosition();
              this->crane.setPosition(CranePosition::Upright_03);
              break;

            case PLAYER_CRANE_LIFT_04 - 1:
              this->player.incPlayerPosition();
              this->crane.setPosition(CranePosition::Inclined_03);
              break;

            case PLAYER_CRANE_LIFT_05 - 1:
              this->player.incPlayerPosition();
              this->crane.setPosition(CranePosition::Flat);
              break;

            case PLAYER_VICTORY_RUN_DECISION - 1:
              if (this->hook.getCounter() == 0) {
                this->player.setPosition(PLAYER_VICTORY_RUN_START);
              }
              else {
                this->player.incPlayerPosition();
              }
              break;

            case PLAYER_CRANE_LIFT_06 - 1:
              this->player.incPlayerPosition();
              this->crane.setPosition(CranePosition::Declined);
              break;

            case PLAYER_CRANE_END:
              break;

            case PLAYER_VICTORY_RUN_END - 1:
            Serial.println("PLAYER_VICTORY_RUN_END");
              break;

            case PLAYER_DIE_END: // end of death sequence.
              this->killPlayer(machine);
              break;

            default:
              //if (arduboy.everyXFrames(4)) {
                this->player.incPlayerPosition();
              //}
              break;
            
          }

        }

      }

    }

    uint8_t yOffset = this->player.getYOffset();


    // Handle crane

    if (arduboy.everyXFrames(2) && !this->crane.getLiftPlayer()) {

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

            if (this->playing && this->player.isJumping()) {

              int8_t barrelX = barrel.getXPosition();
              int16_t barrelY = static_cast<uint16_t>(barrel.getYPosition(yOffset));
              uint8_t playerX = this->player.getXPosition(false);
              int16_t playerY = static_cast<int16_t>(this->player.getYPosition());

              if ((barrelX == playerX) && (playerY - barrelY <= 8)) {

                gameStats.score++;

              }

            }

            Rect playerRect = this->player.getRect();
            Rect barrelRect = barrel.getRect(yOffset);

            if (this->playing && arduboy.collide(this->player.getRect(), barrel.getRect(yOffset)) ) {

#ifndef BARRELS
              this->killPlayer(machine);
#endif
            }

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

            if (this->playing && arduboy.collide(this->player.getRect(), girder.getRect(yOffset)) ) {
              this->killPlayer(machine);
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

    if (arduboy.everyXFrames(6)) {
      this->fire.update();
    }

    if (arduboy.everyXFrames(12)) {
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
      this->player.reset();
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

}


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
  this->deadCounter = 100;
  gameStats.numberOfLivesLeft--;

}


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

    uint8_t image = this->player.getImage();

    switch (image) {

      case static_cast<uint8_t>(Stance::Normal) ... static_cast<uint8_t>(Stance::OnCrane_RHS):
        Sprites::drawExternalMask(this->player.getXPosition(true), this->player.getYPosition(), Images::Mario, Images::Mario_Mask, image, image);
        break;

      case static_cast<uint8_t>(Stance::Dead_01) ... static_cast<uint8_t>(Stance::Dead_03):
        image = image - static_cast<uint8_t>(Stance::Dead_01);
        Sprites::drawSelfMasked(this->player.getXPosition(true), this->player.getYPosition(), Images::Mario_Dying, image);
        break;

      case static_cast<uint8_t>(Stance::OnCrane_EmptyHand) ... static_cast<uint8_t>(Stance::OnCrane_HoldingHook):
        image = image - static_cast<uint8_t>(Stance::OnCrane_EmptyHand);
        Sprites::drawSelfMasked(this->player.getXPosition(true), this->player.getYPosition(), Images::Mario_Leaping, image);
        break;

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