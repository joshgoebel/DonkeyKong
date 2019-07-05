#pragma once

#include "../utils/Enums.h"

#define SCENERY_COUNT 69
#define SCENERY_LEVEL_2_ONLY 1
#define SCENERY_PAINT_LAST 2
#define SCENERY_PAINT_FIRST 4

namespace Coordinates {

  const uint8_t PROGMEM Scenery[] = {

    0, 25, static_cast<uint8_t>(Components::Girder_OverHead), SCENERY_PAINT_FIRST,
    0, 5, static_cast<uint8_t>(Components::Spaghetti), SCENERY_PAINT_FIRST,

    11, 24, static_cast<uint8_t>(Components::Plate1), SCENERY_PAINT_FIRST,
    36, 24, static_cast<uint8_t>(Components::Plate1), SCENERY_PAINT_FIRST,
    61, 24, static_cast<uint8_t>(Components::Plate2), SCENERY_PAINT_FIRST,

    // X, Y, Item, Spare
    9, 67, static_cast<uint8_t>(Components::Girder), SCENERY_PAINT_FIRST,
    19, 66, static_cast<uint8_t>(Components::Girder), SCENERY_PAINT_FIRST,
    29, 65, static_cast<uint8_t>(Components::Girder), SCENERY_PAINT_FIRST,
    39, 64, static_cast<uint8_t>(Components::Girder), SCENERY_PAINT_FIRST,
    49, 63, static_cast<uint8_t>(Components::Girder), SCENERY_PAINT_FIRST,
    59, 62, static_cast<uint8_t>(Components::Girder), SCENERY_PAINT_FIRST,
    69, 61, static_cast<uint8_t>(Components::Girder), SCENERY_PAINT_FIRST,

    9, 47, static_cast<uint8_t>(Components::Ladder), SCENERY_PAINT_FIRST,

    21, 48, static_cast<uint8_t>(Components::Girder_OverHead), SCENERY_PAINT_FIRST,
    33, 48, static_cast<uint8_t>(Components::Girder_OverHead), SCENERY_PAINT_FIRST,
    45, 48, static_cast<uint8_t>(Components::Girder_OverHead), SCENERY_PAINT_FIRST,
    57, 48, static_cast<uint8_t>(Components::Girder_OverHead), SCENERY_PAINT_FIRST,
    69, 48, static_cast<uint8_t>(Components::Girder_OverHead), SCENERY_PAINT_FIRST,

    //Lower Half, 10, , 0,

    23, 75, static_cast<uint8_t>(Components::Girder_OverHead), SCENERY_PAINT_FIRST,
    35, 75, static_cast<uint8_t>(Components::Girder_OverHead), SCENERY_PAINT_FIRST,
    87, 80, static_cast<uint8_t>(Components::Girder_OverHead), SCENERY_PAINT_FIRST,
    91, 80, static_cast<uint8_t>(Components::Girder_OverHead), SCENERY_PAINT_FIRST,

    87, 63, static_cast<uint8_t>(Components::Girder_OverHead), SCENERY_PAINT_FIRST,
    99, 63, static_cast<uint8_t>(Components::Girder_OverHead), SCENERY_PAINT_FIRST,
    111, 63, static_cast<uint8_t>(Components::Girder_OverHead), SCENERY_PAINT_FIRST,
    123, 63, static_cast<uint8_t>(Components::Girder_OverHead), SCENERY_PAINT_FIRST,


    static_cast<uint8_t>(-5), 108, static_cast<uint8_t>(Components::Girder_OverHead), SCENERY_PAINT_FIRST,
    22, 108, static_cast<uint8_t>(Components::Girder_OverHead), SCENERY_PAINT_FIRST,
    34, 108, static_cast<uint8_t>(Components::Girder_OverHead), SCENERY_PAINT_FIRST,
    46, 108, static_cast<uint8_t>(Components::Girder_OverHead), SCENERY_PAINT_FIRST,
    50, 108, static_cast<uint8_t>(Components::Girder_OverHead), SCENERY_PAINT_FIRST,

    79, 108, static_cast<uint8_t>(Components::Girder_OverHead), SCENERY_PAINT_FIRST,

    0, 92, static_cast<uint8_t>(Components::Girder), SCENERY_PAINT_FIRST,
    10, 93, static_cast<uint8_t>(Components::Girder), SCENERY_PAINT_FIRST,
    20, 94, static_cast<uint8_t>(Components::Girder), SCENERY_PAINT_FIRST,

    30, 95, static_cast<uint8_t>(Components::Girder), SCENERY_PAINT_FIRST,
    40, 96, static_cast<uint8_t>(Components::Girder), SCENERY_PAINT_FIRST,
    50, 97, static_cast<uint8_t>(Components::Girder), SCENERY_PAINT_FIRST,
    60, 98, static_cast<uint8_t>(Components::Girder), SCENERY_PAINT_FIRST,

    70, 99, static_cast<uint8_t>(Components::Girder), SCENERY_PAINT_FIRST,
    80, 100, static_cast<uint8_t>(Components::Girder), SCENERY_PAINT_FIRST,
    90, 101, static_cast<uint8_t>(Components::Girder), SCENERY_PAINT_FIRST,
    113, 112, static_cast<uint8_t>(Components::Girder_Small), SCENERY_PAINT_FIRST,

    125, 112, static_cast<uint8_t>(Components::Girder_Small), SCENERY_PAINT_FIRST,
    10, 133, static_cast<uint8_t>(Components::Girder), SCENERY_PAINT_FIRST,
    20, 132, static_cast<uint8_t>(Components::Girder), SCENERY_PAINT_FIRST,
    30, 131, static_cast<uint8_t>(Components::Girder), SCENERY_PAINT_FIRST,
    40, 130, static_cast<uint8_t>(Components::Girder), SCENERY_PAINT_FIRST,
    50, 129, static_cast<uint8_t>(Components::Girder), SCENERY_PAINT_FIRST,
    60, 128, static_cast<uint8_t>(Components::Girder), SCENERY_PAINT_FIRST,
    70, 127, static_cast<uint8_t>(Components::Girder), SCENERY_PAINT_FIRST,

    80, 126, static_cast<uint8_t>(Components::Girder), SCENERY_PAINT_FIRST,
    90, 125, static_cast<uint8_t>(Components::Girder), SCENERY_PAINT_FIRST,
    100, 124, static_cast<uint8_t>(Components::Girder), SCENERY_PAINT_FIRST,
    9, 74, static_cast<uint8_t>(Components::Ladder), SCENERY_PAINT_FIRST,

    91, 106, static_cast<uint8_t>(Components::Ladder), SCENERY_PAINT_FIRST,

    static_cast<uint8_t>(-4), 48, static_cast<uint8_t>(Components::Girder_OverHead), SCENERY_PAINT_FIRST,
    0, 37, static_cast<uint8_t>(Components::Lever), SCENERY_PAINT_FIRST,


    0, 68, static_cast<uint8_t>(Components::Cable2), SCENERY_PAINT_FIRST | SCENERY_LEVEL_2_ONLY,
    20, 68, static_cast<uint8_t>(Components::Cable1), SCENERY_PAINT_FIRST | SCENERY_LEVEL_2_ONLY,
    40, 69, static_cast<uint8_t>(Components::Cable1), SCENERY_PAINT_FIRST | SCENERY_LEVEL_2_ONLY,
    60, 70, static_cast<uint8_t>(Components::Cable1), SCENERY_PAINT_FIRST | SCENERY_LEVEL_2_ONLY,
    80, 71, static_cast<uint8_t>(Components::Cable1), SCENERY_PAINT_FIRST | SCENERY_LEVEL_2_ONLY,
    100, 72, static_cast<uint8_t>(Components::Cable1), SCENERY_PAINT_FIRST | SCENERY_LEVEL_2_ONLY,
    120, 73, static_cast<uint8_t>(Components::Cable1), SCENERY_PAINT_FIRST | SCENERY_LEVEL_2_ONLY,


    88, 10, static_cast<uint8_t>(Components::Crane), SCENERY_PAINT_FIRST,
    85, 0, static_cast<uint8_t>(Components::Hook), SCENERY_PAINT_FIRST,
    0, 122, static_cast<uint8_t>(Components::Fire), SCENERY_PAINT_FIRST,
    0, 122, static_cast<uint8_t>(Components::Fire_Foreground), SCENERY_PAINT_LAST,

    0, 0, static_cast<uint8_t>(Components::Girder), SCENERY_PAINT_FIRST,

  };
 
 }