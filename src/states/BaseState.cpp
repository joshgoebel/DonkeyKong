#include "BaseState.h"

#include "../images/Images.h"
#include "../utils/Utils.h"
#include "../utils/Enums.h"

void BaseState::renderScore(StateMachine & machine, bool renderHealth, int16_t health) {
  	
  auto & gameStats = machine.getContext().gameStats;
  auto & arduboy = machine.getContext().arduboy;

  Sprites::drawExternalMask(52, 1, Images::Scoreboard, Images::Scoreboard_Mask, 0, 0);

  if (!renderHealth) {

    uint8_t digits[4] = {};
    extractDigits(digits, gameStats.score);

    for (uint8_t j = 4; j > 0; --j) {

      Sprites::drawSelfMasked(75 - (j*5), 4, Images::Scoreboard_Numbers, digits[j - 1]);

    }

  }
  else {

    for (uint8_t i = 0; i < health; i = i + 2) {
      
      arduboy.drawFastVLine(94 + i, 3, 8);

    }

  }

}


void BaseState::renderCommonScenery(StateMachine & machine) {

  auto & gameStats = machine.getContext().gameStats;
	auto & arduboy = machine.getContext().arduboy;

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
      machine.changeState(GameStateType::HighScoreScreen, GameStateType::None); 
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
