#include "TitleScreenState.h"
#include "../images/Images.h"
#include "../utils/EEPROM_Utils.h"
#include "../utils/Enums.h"
#include "../utils/Utils.h"
#include "../sounds/Sounds.h"

// For size_t
#include <stddef.h>

// For pgm_read_ptr
#include <avr/pgmspace.h>

constexpr const static uint8_t PRESS_A_DELAY = 200;
constexpr const static uint8_t UPLOAD_DELAY = 16;


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void TitleScreenState::activate(StateMachine & machine) {

  auto & gameStats = machine.getContext().gameStats;
  auto & arduboy = machine.getContext().arduboy;
  auto & sound = machine.getContext().sound;  
	
  gameStats.resetGame();
  sound.setOutputEnabled(arduboy.audio.enabled);

  auto scoreIndex = static_cast<size_t>(random(getSize(Sounds::Scores)));
  auto score = static_cast<const uint16_t *>(pgm_read_ptr(&Sounds::Scores[scoreIndex]));

  //sound.tones(score);

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void TitleScreenState::update(StateMachine & machine) {

  auto & arduboy = machine.getContext().arduboy;
  auto justPressed = arduboy.justPressedButtons();
  auto pressed = arduboy.pressedButtons();
  auto & gameStats = machine.getContext().gameStats;


	// Restart ?

	if (pressed & DOWN_BUTTON) {

		if (this->restart < UPLOAD_DELAY) {
			this->restart++;
		}
		else {
			arduboy.exitToBootloader();
		}

	}
	else {
		this->restart = 0;
	}


	// Handle other input ..

	if (justPressed & A_BUTTON || justPressed & B_BUTTON) {
    gameStats.mode = (justPressed & A_BUTTON ? GameMode::Easy : GameMode::Hard);
		machine.changeState(GameStateType::PlayGameScreen, GameStateType::None); 
	}

	if (justPressed & UP_BUTTON || justPressed & DOWN_BUTTON || justPressed & LEFT_BUTTON || justPressed & RIGHT_BUTTON) {
		machine.changeState(GameStateType::HighScoreScreen, GameStateType::None); 
	}


  // Update 'Press A' counter / delay ..

  if (this->pressACounter < PRESS_A_DELAY) this->pressACounter++;

}


// ----------------------------------------------------------------------------
//  Render the state .. 
//
void TitleScreenState::render(StateMachine & machine) {

  auto & arduboy = machine.getContext().arduboy;

  BaseState::renderCommonScenery(machine);

  Sprites::drawExternalMask(26, 9, Images::Title, Images::Title_Mask, 0, 0);

  if (this->pressACounter == PRESS_A_DELAY) {

    Sprites::drawExternalMask(35, 42, Images::PressAandB, Images::PressAandB_Mask, 0, 0);

  }

  arduboy.display(true);

}
