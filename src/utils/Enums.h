#pragma once

#include <Arduboy2.h>

#define _BARRELS


#define NOT_IN_A_POSITION 255


// - High Scores ---------------------

#define NAME_LENGTH 3
#define NAME_LENGTH_PLUS_TERM (NAME_LENGTH + 1)

#define HS_NAME_LEFT 36
#define HS_SCORE_LEFT 69
#define HS_CHAR_TOP 24
#define HS_CHAR_V_SPACING 9
#define HS_PRESS_A_DELAY 100
#define NO_WINNER 255


#define FLASH_FRAME_COUNT 40

enum class LeverPosition : uint8_t {
  Off,
  On
};

enum class Stance : uint8_t {
  Normal,                     // 0
  Normal_RHS,                 // 1
  Running_01,                 // 2
  Running_01_RHS,             // 3
  Running_02,                 // 4
  Running_02_RHS,             // 5
  Running_03,                 // 6
  Running_03_RHS,             // 7
  Running_04,                 // 8
  Running_04_RHS,             // 9
  Jump,                       // 8
  Jump_RHS,                   // 9
  Ladder_01,                  // 12
  Ladder_02,                  // 13
};

enum class GorillaStance : uint8_t {
  Normal,
  Left,
  Right,
  ThrowingBarrel1,
  ThrowingBarrel2,
  ThrowingBarrel3,
  ThrowingBarrel4,
};

enum class Components : uint8_t {
  Girder,
  Girder_OverHead, 
  Girder_Small,
  Ladder,
  Plate1,
  Plate2,
  Lever,
  Cable1,
  Cable2,
  Crane,
  Hook,
  Fire,
  Fire_Foreground,
  Spaghetti
};

enum class Movements : uint8_t {
  Up = 1,
  Down = 2, 
  Left = 4,
  Right = 8,
  Jump = 16,
  Lever = 32,
  Reverse = 64
};

enum class Rotation : uint8_t {
  Left,
  Right,
  None
};

enum class CranePosition : uint8_t {
  Upright = 0,
  Inclined = 1,
  Inclined_01 = 0,
  Inclined_02 = 1,
  Inclined_03 = 2,
  Inclined_04 = 3,
  Inclined_05 = 4,
  Flat = 6,
  Declined = 7,
};

enum class CraneState : uint8_t {
  Dormant,
  TurningOn,
  TurningOff,
  Swinging
};

enum class GameStateType : uint8_t {
  None,
	SplashScreen,
	TitleScreen,
  GameIntroScreen,
  PlayGameScreen,
  HighScoreScreen
};

enum class GameMode : uint8_t {
  Easy,
  Hard
};

struct GameStats {

  public: 
    
    GameStats() { };

    uint16_t score = 0;
    uint8_t numberOfLivesLeft = 3;

    GameMode mode = GameMode::Easy;

    bool gameOver = false;

    void resetGame() {

      this->numberOfLivesLeft = 3;
      this->score = 0; 
      this->gameOver = false;

    }

};