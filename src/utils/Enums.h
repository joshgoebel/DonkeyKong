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