#include "BaseState.h"

#include "../images/Images.h"
#include "../utils/Utils.h"
#include "../utils/Enums.h"

void BaseState::renderScore(StateMachine & machine, int16_t health) {
  	
  auto & gameStats = machine.getContext().gameStats;
  auto & arduboy = machine.getContext().arduboy;

  Sprites::drawExternalMask(102, 0, Images::Scoreboard, Images::Scoreboard_Mask, 0, 0);

  uint8_t digits[4] = {};
  extractDigits(digits, gameStats.score);

  for (uint8_t j = 4; j > 0; --j) {

    Sprites::drawSelfMasked(125 - (j*5), 3, Images::Scoreboard_Numbers, digits[j - 1]);

  }

}


bool BaseState::getPaused() {

  return this->paused;

}

void BaseState::setPaused(bool value) {
  
  this->paused = value;

}

void BaseState::handleCommonButtons(StateMachine & machine) {

	auto & arduboy = machine.getContext().arduboy;
  auto & gameStats = machine.getContext().gameStats;
  auto justPressed = arduboy.justPressedButtons();

  if (gameStats.gameOver) {

    if (justPressed & A_BUTTON) {
      machine.changeState(GameStateType::HighScoreScreen); 
    }

  }
  else {

    if (justPressed & B_BUTTON) {
      this->paused = !this->paused; 
    }

  }

}

void BaseState::renderGameOverOrPause(StateMachine & machine) {

  auto & gameStats = machine.getContext().gameStats;


  // Game Over?

  if (gameStats.gameOver) {

    Sprites::drawExternalMask(25, 20, Images::GameOver, Images::GameOver_Mask, 0, 0); 

  }

  // Pause?

  if (this->paused) {

    Sprites::drawExternalMask(39, 20, Images::Pause, Images::Pause_Mask, 0, 0); 

  }

}
