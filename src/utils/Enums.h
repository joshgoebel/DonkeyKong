#pragma once

#include <Arduboy2.h>

enum class Stance : uint8_t {
  Normal,
};

enum class Components : uint8_t {
  Girder,
  Girder_OverHead, 
  Girder_Small,
  Ladder,
  Plate
};

enum class Movements : uint8_t {
  Up = 1,
  Down = 2, 
  Left = 4,
  Right = 8,
  Jump = 16,
  Reverse = 32
};

enum class Rotation : uint8_t {
  Left,
  Right,
  None
};