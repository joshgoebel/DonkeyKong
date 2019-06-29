#pragma once

#include "../utils/Enums.h"
#define SCENERY_COUNT  49

namespace Coordinates {

  const int8_t PROGMEM Scenery[] = {
    0, 0, static_cast<uint8_t>(Components::Girder), 0,

//  X, Y,  Item, Spare
    9, 57, static_cast<uint8_t>(Components::Girder), 0,
    19, 56, static_cast<uint8_t>(Components::Girder), 0,
    29, 55, static_cast<uint8_t>(Components::Girder), 0,
    39, 54, static_cast<uint8_t>(Components::Girder), 0,
    49, 53, static_cast<uint8_t>(Components::Girder), 0,
    59, 52, static_cast<uint8_t>(Components::Girder), 0,
    69, 51, static_cast<uint8_t>(Components::Girder), 0,

    9, 37, static_cast<uint8_t>(Components::Ladder), 0,

    23, 40, static_cast<uint8_t>(Components::Girder_OverHead), 0,
    35, 40, static_cast<uint8_t>(Components::Girder_OverHead), 0,
    47, 40, static_cast<uint8_t>(Components::Girder_OverHead), 0,
    59, 40, static_cast<uint8_t>(Components::Girder_OverHead), 0,
    71, 40, static_cast<uint8_t>(Components::Girder_OverHead), 0,

    //Lower Half

    23, 65, static_cast<uint8_t>(Components::Girder_OverHead), 0,
    35, 65, static_cast<uint8_t>(Components::Girder_OverHead), 0,
    87, 70, static_cast<uint8_t>(Components::Girder_OverHead), 0,
    91, 70, static_cast<uint8_t>(Components::Girder_OverHead), 0,
    -5, 98, static_cast<uint8_t>(Components::Girder_OverHead), 0,

    22, 98, static_cast<uint8_t>(Components::Girder_OverHead), 0,
    34, 98, static_cast<uint8_t>(Components::Girder_OverHead), 0,
    46, 98, static_cast<uint8_t>(Components::Girder_OverHead), 0,
    50, 98, static_cast<uint8_t>(Components::Girder_OverHead), 0,

    79, 98, static_cast<uint8_t>(Components::Girder_OverHead), 0,
    0, 82, static_cast<uint8_t>(Components::Girder), 0,
    10, 83, static_cast<uint8_t>(Components::Girder), 0,
    20, 84, static_cast<uint8_t>(Components::Girder), 0,

    30, 85, static_cast<uint8_t>(Components::Girder), 0,
    40, 86, static_cast<uint8_t>(Components::Girder), 0,
    50, 87, static_cast<uint8_t>(Components::Girder), 0,
    60, 88, static_cast<uint8_t>(Components::Girder), 0,

    70, 89, static_cast<uint8_t>(Components::Girder), 0,
    80, 90, static_cast<uint8_t>(Components::Girder), 0,
    90, 91, static_cast<uint8_t>(Components::Girder), 0,
    113, 102, static_cast<uint8_t>(Components::Girder_Small), 0,

    125, 102, static_cast<uint8_t>(Components::Girder_Small), 0,
    10, 123, static_cast<uint8_t>(Components::Girder), 0,
    20, 122, static_cast<uint8_t>(Components::Girder), 0,
    30, 121, static_cast<uint8_t>(Components::Girder), 0,

    40, 120, static_cast<uint8_t>(Components::Girder), 0,
    50, 119, static_cast<uint8_t>(Components::Girder), 0,
    60, 118, static_cast<uint8_t>(Components::Girder), 0,
    70, 117, static_cast<uint8_t>(Components::Girder), 0,

    80, 116, static_cast<uint8_t>(Components::Girder), 0,
    90, 115, static_cast<uint8_t>(Components::Girder), 0,
    100, 114, static_cast<uint8_t>(Components::Girder), 0,
    9, 64, static_cast<uint8_t>(Components::Ladder), 0,

    91, 96, static_cast<uint8_t>(Components::Ladder), 0

  };
 
 }