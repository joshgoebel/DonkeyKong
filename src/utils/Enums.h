#pragma once


enum class Rotation : uint8_t {
  Left,
  Right
};

enum class Stance : uint8_t {
  Normal,
};


enum class Components : uint8_t {
  Girder,
  Girder_OverHead, 
  Girder_Small,
  Ladder
};



enum class Movements : uint8_t {
  Up = 1,
  Down = 2, 
  Left = 4,
  Right = 8,
  Jump = 16,
  Reverse = 32
};