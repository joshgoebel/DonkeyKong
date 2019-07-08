#include "PlayGameState.h"

#include "../utils/Arduboy2Ext.h"
#include "../images/Images.h"
#include "../sounds/Sounds.h"
#include "../utils/Utils.h"


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void PlayGameState::activate(StateMachine & machine) {

  auto & gameStats = machine.getContext().gameStats;
  auto & arduboy = machine.getContext().arduboy;
  auto & sound = machine.getContext().sound;  

  this->lever.setCrane(&crane);
  this->player.reset();

  this->frameRate = FRAME_RATE_MIN;
  this->numberOfBarrelsInPlay = NUMBER_OF_BARRELS_MIN;
  this->resetLevel(125);
  this->resetGorillaAndPlates();

  for (auto &barrel : this->barrels) {
    barrel.setPosition(0);
    barrel.setEnabled(false);
  }

  for (uint8_t x = 0; x < this->numberOfBarrelsInPlay; x++) {
  
    auto &barrel = this->barrels[x];

    for (uint8_t x = 0; x < this->numberOfBarrelsInPlay; x++) {

      bool notValid = false;
      uint8_t randomPos = 0;

      while (!notValid) {

        notValid = true;
        randomPos = random(80, 190);

        for (uint8_t y = 0; y < this->numberOfBarrelsInPlay; y++) {

          auto &barrel2 = this->barrels[y];

          if (x != y && absT(randomPos - barrel2.getPosition()) < this->barrelOffset) {
            notValid = false;
            break;
          }

        }

      }

      barrel.setPosition(randomPos);
      barrel.setEnabled(true);

    }

  }

  this->playing = false;
  BaseState::setPaused(false);

  sound.setOutputEnabled(arduboy.audio.enabled);

}
  