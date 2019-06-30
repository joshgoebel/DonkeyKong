#pragma once

#include "../utils/Enums.h"

#define SCENERY_COUNT 65
#define SCENERY_LEVEL_2_ONLY 56

namespace Coordinates {

  const uint8_t PROGMEM Scenery[] = {

    11, 24, static_cast<uint8_t>(Components::Plate1), 0,
    36, 24, static_cast<uint8_t>(Components::Plate1), 0,
    61, 24, static_cast<uint8_t>(Components::Plate2), 0,

    // X, Y, Item, Spare
    9, 67, static_cast<uint8_t>(Components::Girder), 0,
    19, 66, static_cast<uint8_t>(Components::Girder), 0,
    29, 65, static_cast<uint8_t>(Components::Girder), 0,
    39, 64, static_cast<uint8_t>(Components::Girder), 0,
    49, 63, static_cast<uint8_t>(Components::Girder), 0,
    59, 62, static_cast<uint8_t>(Components::Girder), 0,
    69, 61, static_cast<uint8_t>(Components::Girder), 0,

    9, 47, static_cast<uint8_t>(Components::Ladder), 0,

    21, 48, static_cast<uint8_t>(Components::Girder_OverHead), 0,
    33, 48, static_cast<uint8_t>(Components::Girder_OverHead), 0,
    45, 48, static_cast<uint8_t>(Components::Girder_OverHead), 0,
    57, 48, static_cast<uint8_t>(Components::Girder_OverHead), 0,
    69, 48, static_cast<uint8_t>(Components::Girder_OverHead), 0,

    //Lower Half, 10, , 0,

    23, 75, static_cast<uint8_t>(Components::Girder_OverHead), 0,
    35, 75, static_cast<uint8_t>(Components::Girder_OverHead), 0,
    87, 80, static_cast<uint8_t>(Components::Girder_OverHead), 0,
    91, 80, static_cast<uint8_t>(Components::Girder_OverHead), 0,

    87, 63, static_cast<uint8_t>(Components::Girder_OverHead), 0,
    99, 63, static_cast<uint8_t>(Components::Girder_OverHead), 0,
    111, 63, static_cast<uint8_t>(Components::Girder_OverHead), 0,
    123, 63, static_cast<uint8_t>(Components::Girder_OverHead), 0,


    static_cast<uint8_t>(-5), 108, static_cast<uint8_t>(Components::Girder_OverHead), 0,
    22, 108, static_cast<uint8_t>(Components::Girder_OverHead), 0,
    34, 108, static_cast<uint8_t>(Components::Girder_OverHead), 0,
    46, 108, static_cast<uint8_t>(Components::Girder_OverHead), 0,
    50, 108, static_cast<uint8_t>(Components::Girder_OverHead), 0,

    79, 108, static_cast<uint8_t>(Components::Girder_OverHead), 0,

    0, 92, static_cast<uint8_t>(Components::Girder), 0,
    10, 93, static_cast<uint8_t>(Components::Girder), 0,
    20, 94, static_cast<uint8_t>(Components::Girder), 0,

    30, 95, static_cast<uint8_t>(Components::Girder), 0,
    40, 96, static_cast<uint8_t>(Components::Girder), 0,
    50, 97, static_cast<uint8_t>(Components::Girder), 0,
    60, 98, static_cast<uint8_t>(Components::Girder), 0,

    70, 99, static_cast<uint8_t>(Components::Girder), 0,
    80, 100, static_cast<uint8_t>(Components::Girder), 0,
    90, 101, static_cast<uint8_t>(Components::Girder), 0,
    113, 112, static_cast<uint8_t>(Components::Girder_Small), 0,

    125, 112, static_cast<uint8_t>(Components::Girder_Small), 0,
    10, 133, static_cast<uint8_t>(Components::Girder), 0,
    20, 132, static_cast<uint8_t>(Components::Girder), 0,
    30, 131, static_cast<uint8_t>(Components::Girder), 0,
    40, 130, static_cast<uint8_t>(Components::Girder), 0,
    50, 129, static_cast<uint8_t>(Components::Girder), 0,
    60, 128, static_cast<uint8_t>(Components::Girder), 0,
    70, 127, static_cast<uint8_t>(Components::Girder), 0,

    80, 126, static_cast<uint8_t>(Components::Girder), 0,
    90, 125, static_cast<uint8_t>(Components::Girder), 0,
    100, 124, static_cast<uint8_t>(Components::Girder), 0,
    9, 74, static_cast<uint8_t>(Components::Ladder), 0,

    91, 106, static_cast<uint8_t>(Components::Ladder), 0,

    0, 38, static_cast<uint8_t>(Components::Lever), 0,


    0, 68, static_cast<uint8_t>(Components::Cable2), SCENERY_LEVEL_2_ONLY,
    20, 68, static_cast<uint8_t>(Components::Cable1), SCENERY_LEVEL_2_ONLY,
    40, 69, static_cast<uint8_t>(Components::Cable1), SCENERY_LEVEL_2_ONLY,
    60, 70, static_cast<uint8_t>(Components::Cable1), SCENERY_LEVEL_2_ONLY,
    80, 71, static_cast<uint8_t>(Components::Cable1), SCENERY_LEVEL_2_ONLY,
    100, 72, static_cast<uint8_t>(Components::Cable1), SCENERY_LEVEL_2_ONLY,
    120, 73, static_cast<uint8_t>(Components::Cable1), SCENERY_LEVEL_2_ONLY,


    88, 0, static_cast<uint8_t>(Components::Crane), 0,
    85, 0, static_cast<uint8_t>(Components::Hook), 0,

    0, 0, static_cast<uint8_t>(Components::Girder), 0,


  };
 
 }