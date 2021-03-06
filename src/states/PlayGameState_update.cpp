#include "PlayGameState.h"

#include "../utils/Arduboy2Ext.h"
#include "../images/Images.h"
#include "../sounds/Sounds.h"


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
// Serial.print("Player pos :");
// Serial.print(this->player.getPosition());
// Serial.print(" x");
// Serial.print(this->player.getXPosition(false));
// Serial.print(",y ");
// Serial.print(this->player.getYPosition());
// Serial.print(" Crane :");
// Serial.println(static_cast<uint8_t>(this->crane.getPosition())); 


    //Handle player movements ..

    if (this->playing && arduboy.everyXFrames(2)) {

      if (!this->player.isJumping() && !this->player.isLeaping() && !this->player.isFalling()) {


        // If the player is running from right to left, the controls are reversed ..

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
          

            // Have we jumped from the top level towards the crane ?

            if ((pressed & A_BUTTON) && this->player.canMove(Movements::JumpToCrane)) {
              this->player.setLeaping(true);
              this->player.incPlayerPosition();
              pressed = 0;

            }
            else {

              if (this->player.canMove(Movements::Right)) {


                // Have we just run of the edge of the top level without jumping?

                if (this->player.getPosition() == END_OF_TOP_LEVEL) {
                  this->player.setFalling(true);
                  this->player.setPosition(PLAYER_RUNOFF_START);
#ifndef IGNORE_SOUNDS 
                  sound.tones(Sounds::falling);
#endif
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
            if (this->lever.getPosition() == LeverPosition::Off) {
              this->lever.setPosition(LeverPosition::On);
              this->crane.turnOn();
#ifndef IGNORE_SOUNDS 
              sound.tones(Sounds::lever_on);
#endif
            }
          }

        }

        if ((pressed & DOWN_BUTTON) && this->player.canMove(Movements::Down)) {
          this->player.decPlayerPosition();
        }

        if ((pressed & UP_BUTTON) && this->player.canMove(Movements::Up)) {
          this->player.incPlayerPosition();
        }

        if (this->preventJumpDelay == 0 && (pressed & A_BUTTON) && this->player.canMove(Movements::Jump)) {
          this->player.startJump();
        }

      }


      // Player is jumping, falling or leaping ..
      //
      // Leaping = towards the crane but haven't made it yet.
      // Falling = we have run off the top level without jumping and are about to die!
      // Jumping = we have successfully latched onto the crane and are travelling up.
      //
      else {

        if (this->player.isJumping()) {
          this->player.updateJump();
        }

        else if (this->player.isFalling() && arduboy.everyXFrames(4)) {

          switch (this->player.getPosition()) {

            case PLAYER_RUNOFF_END - 1:
              this->killPlayer(machine);
              break;

            default:  
              this->player.incPlayerPosition();
              break;

          }

        }

        else if (this->player.isLeaping() && arduboy.everyXFrames(4)) {

          const uint8_t cranePosLeft = static_cast<uint8_t>(CranePosition::Inclined_01);
          const uint8_t cranePosRight = (gameStats.mode == GameMode::Hard ? static_cast<uint8_t>(CranePosition::Inclined_01) : static_cast<uint8_t>(CranePosition::Inclined_02));
          const uint16_t playerPos = this->player.getPosition();

          uint8_t cranePos = static_cast<uint8_t>(this->crane.getPosition());



          // Update the plates if the player has caught the crane.  The routine will 
          // fail early and return if there are hooks left ..

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
//SJH              if (false) {
              if (cranePos < cranePosLeft || cranePos > cranePosRight) {
                this->player.setPosition(PLAYER_DIE_START);
#ifndef IGNORE_SOUNDS 
                sound.tones(Sounds::falling);
#endif
              }
              else {
                this->updatePlayerAndCrane(CranePosition::Inclined_02);
                this->crane.setLiftPlayer(true);
              }
              break;

            case PLAYER_CRANE_LIFT_01 - 1:
              this->updatePlayerAndCrane(CranePosition::Upright_01);
              this->gorilla.moveToCentre();
              break;

            case PLAYER_CRANE_LIFT_02 - 1:
              this->updatePlayerAndCrane(CranePosition::Upright_02);
              this->hook.decCounter();
              break;

            case PLAYER_CRANE_LIFT_03 - 1:
              this->updatePlayerAndCrane(CranePosition::Upright_03);
              break;

            case PLAYER_CRANE_LIFT_04 - 1:
              this->updatePlayerAndCrane(CranePosition::Inclined_03);
              break;

            case PLAYER_CRANE_LIFT_05 - 1:
              this->updatePlayerAndCrane(CranePosition::Flat);
              break;

            // Is the gorilla about to drop?  Should we do the victory run?

            case PLAYER_VICTORY_RUN_DECISION - 1: 
              if (this->hook.getCounter() == 0) {
                this->player.setPosition(PLAYER_VICTORY_RUN_START);
#ifndef IGNORE_SOUNDS 
                sound.tones(Sounds::mission_success);
#endif                
              }
              else {
                this->player.incPlayerPosition();
              }
              break;

            case PLAYER_CRANE_LIFT_06 - 1:
              this->updatePlayerAndCrane(CranePosition::Declined);
              break;

            case PLAYER_CRANE_POINTS - 1:
              gameStats.score = gameStats.score + 20;
              this->player.incPlayerPosition();
              break;

            case PLAYER_CRANE_END:
            case PLAYER_VICTORY_RUN_END - 1:
              this->resetLevel();             
              break;

            case PLAYER_VICTORY_RUN_EAT_SPAGHETTI - 1:
              this->spaghetti.setVisible(false);
              this->player.incPlayerPosition();
              break;

            case PLAYER_VICTORY_RUN_POINTS - 1:
              gameStats.score = gameStats.score + 50;
              this->player.incPlayerPosition();

              // Make the game that little bit harder ..

              if (this->numberOfBarrelsInPlay < NUMBER_OF_BARRELS_MAX) {
                this->numberOfBarrelsInPlay++;
              }
              if (this->frameRate + 1 < FRAME_RATE_MAX) {
                this->frameRate = this->frameRate + 2;
                arduboy.setFrameRate(this->frameRate);
              }
              break;

            case PLAYER_DIE_END: // end of death sequence.
              this->killPlayer(machine);
              break;

            default:
              this->player.incPlayerPosition();
              break;
            
          }

        }

      }

    }

    uint8_t yOffset = this->player.getYOffset();


    // Handle crane movements.  If the crane is carrying the person, the movements are 
    // controlled in the switch statement above ..

    if (arduboy.everyXFrames(2) && !this->crane.getLiftPlayer()) {

      this->crane.update();

    }


    // Handle Barrels.
    //
    // We can only launch barrels if he gorilla is not already about to launch one and he is 
    // in a position in the center of the plates.  If this is true, then we ensure there are
    // no existing barrels that have just been launched that would result in the new barrel 
    // and it to be too close together.
    {
      uint8_t gorillaPosition = this->gorilla.isInPosition();
      bool launch = this->gorilla.readyToLaunchNewBarrel();

      uint8_t barrelsEnabled = 0;

      for (auto &barrel : this->barrels) {
        
        if (barrel.isEnabled()) {

          barrelsEnabled++;

        }

      }

      if (barrelsEnabled >= this->numberOfBarrelsInPlay) launch = false;

// Serial.print("GP: ");
// Serial.print(gorillaPosition);
// Serial.print(", launch: ");
// Serial.println(launch);

      if (launch) {

//  for (uint8_t x=0; x<this->numberOfBarrelsInPlay; x++) {
//           auto &barrel = this->barrels[x];
//           // Serial.print(barrel.getXPosition());
//           // Serial.print(",");
//           // Serial.print(barrel.getYPosition(0));
//           // Serial.print(",");
//           Serial.print(barrel.getPosition());
//           Serial.print("=");
//         }
//  Serial.println(".");


        for (auto &barrel : this->barrels) {
          
          if (barrel.isEnabled()) {

            if (barrel.getPosition() < 78 && barrel.getAisle() != gorillaPosition) { launch = false;}
            if (barrel.getPosition() > BARREL_POSITION_1_START && barrel.getPosition() < BARREL_POSITION_1_START + 12 && barrel.getAisle() == gorillaPosition && barrel.getAisle() == 0) { launch = false;}
            if (barrel.getPosition() > BARREL_POSITION_2_START && barrel.getPosition() < BARREL_POSITION_2_START + 12 && barrel.getAisle() == gorillaPosition && barrel.getAisle() == 1) { launch = false;}
            if (barrel.getPosition() > BARREL_POSITION_3_START && barrel.getPosition() < BARREL_POSITION_3_START + 12 && barrel.getAisle() == gorillaPosition && barrel.getAisle() == 2) { launch = false;}
  //           switch (gorillaPosition) {

  //             case 0:

  //               if ((barrel.getPosition() < this->barrelOffset) ||
  //                   (barrel.getPosition() >= BARREL_POSITION_2_START + BARREL_POSITION_2_COUNT - BARREL_POSITION_1_COUNT + this->barrelOffset && barrel.getPosition() <= BARREL_POSITION_2_END) ||
  //                   (barrel.getPosition() >= BARREL_POSITION_3_START + BARREL_POSITION_3_COUNT - BARREL_POSITION_1_COUNT + this->barrelOffset && barrel.getPosition() <= BARREL_POSITION_3_END)) {
  // //Serial.println("..launch failed 0");
  //                 launch = false;
  //               }
  //               break;

  //             case 1:

  //               if ((barrel.getPosition() >= BARREL_POSITION_1_START && barrel.getPosition() <= BARREL_POSITION_1_END) ||
  //                   (barrel.getPosition() >= BARREL_POSITION_2_START && barrel.getPosition() <= BARREL_POSITION_2_START + this->barrelOffset) ||
  //                   (barrel.getPosition() >= BARREL_POSITION_3_START + BARREL_POSITION_3_COUNT - BARREL_POSITION_2_COUNT && barrel.getPosition() <= BARREL_POSITION_3_START + BARREL_POSITION_3_COUNT - BARREL_POSITION_2_COUNT + this->barrelOffset)) {
  // //Serial.println("..launch failed 1");
  //                   launch = false;
  //                 }
  //                 break;

  //             case 2:

  //               if ((barrel.getPosition() >= BARREL_POSITION_1_START && barrel.getPosition() <= BARREL_POSITION_1_END) ||
  //                   (barrel.getPosition() >= BARREL_POSITION_2_START && barrel.getPosition() <= BARREL_POSITION_3_COUNT - BARREL_POSITION_2_START + this->barrelOffset) ||
  //                   (barrel.getPosition() <= BARREL_POSITION_3_START + this->barrelOffset)) {
  // //Serial.println("..launch failed 2");
  //                   launch = false;
  //                 }
  //                 break;

  //           }

          }

        }
        
      }


      // Are we able to launch a barrel?
//   Serial.print("GP:");
//   Serial.print(gorillaPosition);
//   Serial.print(") ");
//  for (uint8_t x=0; x<this->numberOfBarrelsInPlay; x++) {
//           auto &barrel = this->barrels[x];
//           if (barrel.isEnabled()) {
//           // Serial.print(barrel.getXPosition());
//           // Serial.print(",");
//           // Serial.print(barrel.getYPosition(0));
//           // Serial.print(",");
//           Serial.print(barrel.getPosition());
//           Serial.print(":");
//           Serial.print(barrel.getAisle());
//           Serial.print("=");
//           }
//         }
//   Serial.println(".");


      if (launch) {
  // Serial.print("..launch good to go! ");
  //       for (uint8_t x=0; x<5; x++) {
  //         auto &barrel = this->barrels[x];
  //         Serial.print(barrel.isEnabledOrPending());
  //       }
  // Serial.println(".");

        for (auto &barrel : this->barrels) {


          // Look for a barrel that is not enabled (or about to be launched) ..

          if (!barrel.isEnabledOrPending()) { 

            uint8_t countdown = random(5, 40);
            Barrel* ptr_Barrel = &barrel;
            barrel.setEnabledCountdown(countdown);
            this->gorilla.launch(ptr_Barrel, countdown);
            break;

          }

        }

      }


      // Update barrel positions and detect collisions with the player ..

      if (arduboy.everyXFrames(6)) {

        for (auto &barrel : this->barrels) {

          if (barrel.isEnabled()) {

            if (this->playing && this->player.isJumping()) {

              int8_t barrelX = barrel.getXPosition();
              int16_t barrelY = static_cast<uint16_t>(barrel.getYPosition(yOffset));
              uint8_t playerX = this->player.getXPosition(false);
              int16_t playerY = static_cast<int16_t>(this->player.getYPosition());

              if ((barrelX == playerX) && (playerY - barrelY <= 8) && barrel.getAisle() < 3) {

                barrel.setAisle(255);
                gameStats.score++;
#ifndef IGNORE_SOUNDS 
                sound.tones(Sounds::jump_barrel);
#endif

              }

            }

            Rect playerRect = this->player.getRect();
            Rect barrelRect = barrel.getRect(yOffset);

            if (this->playing && arduboy.collide(this->player.getRect(), barrel.getRect(yOffset)) ) {

#ifndef IGNORE_BARREL_COLLISIONS
              this->killPlayer(machine);
#ifndef IGNORE_SOUNDS              
              sound.tones(Sounds::crash_into_barrel);
#endif            
#endif
            }

            barrel.updatePosition();
            barrel.rotate();

          }

        }

      }

    }


    // Update girders and detect collisions with the player ..

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


    // Move the overhead girder if on 'hard' mode ..

    if (gameStats.mode == GameMode::Hard) {

      uint8_t activeGirderCount = getActiveGirderCount();
      uint8_t girderMaxPosition = getGirderMaxPosition();

      if ((activeGirderCount == 0 || (activeGirderCount < 2 && girderMaxPosition > 50)) && (random(0, 50) == 0)) {

        uint8_t girderIndex = getDisabledGirderIndex();

        Girder &girder = this->girders[girderIndex];
        girder.setEnabled(true);

      }

    }


    // Update lever if it has been pulled.  It will stop the crane automatically ..

    if (arduboy.everyXFrames(4)) {

      this->lever.update();

    }
    

    // Move gorilla and reduce ..

    this->gorilla.move();

    for (auto &barrel : this->barrels) {
      barrel.decEnabledCountdown();
    }


    // Update fire and spaghetti ..

    if (arduboy.everyXFrames(6)) {
      this->fire.update();
    }

    if (arduboy.everyXFrames(12)) {
      this->spaghetti.update();
    }

  }


  // End of Game?

  if (gameStats.numberOfLivesLeft == 0) {

    gameStats.gameOver = true;
    this->playing = false;

  }


  // Handle the transition to a new life ..

  switch (this->introDelay) {

    case 101 ... 255:
      this->introDelay--;
      break;

    case 100:
      this->showLivesLeft = true;
      if (gameStats.numberOfLivesLeft > 0) {
        this->player.setPosition(0);
        this->removeLowerBarrels();
        if (this->hook.getCounter() == 0) {
          this->resetGorillaAndPlates();
        }
        else {
          this->gorilla.reset();
        }
      }
      this->introDelay--;
      break;

    case 2 ... 99:
      this->introDelay--;
      break;

    case 1:
      if (gameStats.numberOfLivesLeft > 0) {
      this->player.reset();
      this->playing = true;
      }
      this->introDelay = 0;
      this->showLivesLeft = false;
      this->spaghetti.setVisible(true);
      this->spaghetti.incFood();
      break;

    default:
      break;

  }


  // Handle other buttons ..

  if (this->preventJumpDelay > 0) this->preventJumpDelay--;

  if (!this->playing && !gameStats.gameOver) {

    if ((justPressed & A_BUTTON) || (justPressed & B_BUTTON)) {

      this->playing = true;
      this->showLivesLeft = false;
      this->introDelay = 0;
      this->player.reset();
      this->lever.setPosition(LeverPosition::Off);

      if (justPressed & A_BUTTON) {
        this->preventJumpDelay = 20;
      }

    }

  }
  else {  

    BaseState::handleCommonButtons(machine);

  }

}
