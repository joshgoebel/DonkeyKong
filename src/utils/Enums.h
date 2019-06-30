#pragma once

#include <Arduboy2.h>

enum class LeverPosition : uint8_t {
  Off,
  On
};

enum class Stance : uint8_t {
  Normal,
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
  Hook
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
  Swinging
};
