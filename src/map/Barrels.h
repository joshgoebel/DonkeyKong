#pragma once

#include "../utils/Enums.h"

#define BARREL_POSITION_3_START       0
#define BARREL_POSITION_3_COUNT       30
#define BARREL_POSITION_3_END         BARREL_POSITION_3_START + BARREL_POSITION_3_COUNT - 1 /* 29 */
#define BARREL_POSITION_2_START       BARREL_POSITION_3_START + BARREL_POSITION_3_COUNT     /* 30 */
#define BARREL_POSITION_2_COUNT       29
#define BARREL_POSITION_2_END         BARREL_POSITION_2_START + BARREL_POSITION_2_COUNT - 1 /* 58 */
#define BARREL_POSITION_1_START       BARREL_POSITION_2_START + BARREL_POSITION_2_COUNT     /* 59 */
#define BARREL_POSITION_1_COUNT       19
#define BARREL_POSITION_1_END         BARREL_POSITION_1_START + BARREL_POSITION_1_COUNT - 1 /* 78 */
#define BARREL_NUMER_OF_ELEMENTS      4


namespace Coordinates {

  const uint8_t PROGMEM Barrel[880] = {


    //From Position 3 ..

    69, 18, static_cast<uint8_t>(Rotation::None), 0,	
    69, 20, static_cast<uint8_t>(Rotation::None), 0,	
    69, 22, static_cast<uint8_t>(Rotation::None), 0,	

    69, 24, static_cast<uint8_t>(Rotation::None), 0,	
    69, 26, static_cast<uint8_t>(Rotation::None), 0,	
    69, 28, static_cast<uint8_t>(Rotation::None), 0,	
    69, 30, static_cast<uint8_t>(Rotation::None), 0,	

    69, 32, static_cast<uint8_t>(Rotation::None), 0,	
    69, 34, static_cast<uint8_t>(Rotation::None), 0,	
    69, 36, static_cast<uint8_t>(Rotation::None), 0,	
    69, 38, static_cast<uint8_t>(Rotation::None), 0,	

    69, 40, static_cast<uint8_t>(Rotation::None), 0,	
    69, 42, static_cast<uint8_t>(Rotation::None), 0,	
    69, 44, static_cast<uint8_t>(Rotation::None), 0,	
    69, 46, static_cast<uint8_t>(Rotation::None), 0,	

    69, 48, static_cast<uint8_t>(Rotation::None), 0,	
    69, 50, static_cast<uint8_t>(Rotation::None), 0,	
    69, 52, static_cast<uint8_t>(Rotation::None), 0,	
    67, 52, static_cast<uint8_t>(Rotation::Left), 0,	

    65, 52, static_cast<uint8_t>(Rotation::Left), 0,	
    63, 52, static_cast<uint8_t>(Rotation::Left), 0,	
    61, 53, static_cast<uint8_t>(Rotation::Left), 0,	
    57, 53, static_cast<uint8_t>(Rotation::Left), 0,	

    55, 53, static_cast<uint8_t>(Rotation::Left), 0,	
    53, 53, static_cast<uint8_t>(Rotation::Left), 0,	
    51, 54, static_cast<uint8_t>(Rotation::Left), 0,	
    49, 54, static_cast<uint8_t>(Rotation::Left), 0,	

    47, 54, static_cast<uint8_t>(Rotation::Left), 0,	
    45, 54, static_cast<uint8_t>(Rotation::Left), 0,	
    43, 54, static_cast<uint8_t>(Rotation::Left), 21,	


    // From Position 2 ..

    44, 19, static_cast<uint8_t>(Rotation::None), 0,	
    44, 21, static_cast<uint8_t>(Rotation::None), 0,	

    44, 23, static_cast<uint8_t>(Rotation::None), 0,	
    44, 25, static_cast<uint8_t>(Rotation::None), 0,	
    44, 27, static_cast<uint8_t>(Rotation::None), 0,	
    44, 29, static_cast<uint8_t>(Rotation::None), 0,	

    44, 31, static_cast<uint8_t>(Rotation::None), 0,	
    44, 33, static_cast<uint8_t>(Rotation::None), 0,	
    44, 35, static_cast<uint8_t>(Rotation::None), 0,	
    44, 37, static_cast<uint8_t>(Rotation::None), 0,	

    44, 39, static_cast<uint8_t>(Rotation::None), 0,	
    44, 41, static_cast<uint8_t>(Rotation::None), 0,	
    44, 43, static_cast<uint8_t>(Rotation::None), 0,	
    44, 45, static_cast<uint8_t>(Rotation::None), 0,	

    44, 47, static_cast<uint8_t>(Rotation::None), 0,	
    44, 49, static_cast<uint8_t>(Rotation::None), 0,	
    44, 51, static_cast<uint8_t>(Rotation::None), 0,	
    44, 53, static_cast<uint8_t>(Rotation::Left), 0,	

    44, 55, static_cast<uint8_t>(Rotation::Left), 0,	
    41, 55, static_cast<uint8_t>(Rotation::Left), 0,	// From Position 3
    39, 55, static_cast<uint8_t>(Rotation::Left), 0,	
    37, 55, static_cast<uint8_t>(Rotation::Left), 0,	

    35, 55, static_cast<uint8_t>(Rotation::Left), 0,	
    31, 56, static_cast<uint8_t>(Rotation::Left), 0,	
    29, 56, static_cast<uint8_t>(Rotation::Left), 0,	
    27, 56, static_cast<uint8_t>(Rotation::Left), 0,	

    25, 56, static_cast<uint8_t>(Rotation::Left), 0,	
    23, 56, static_cast<uint8_t>(Rotation::Left), 0,	
    21, 57, static_cast<uint8_t>(Rotation::Left), 21,	
//    19, 57, static_cast<uint8_t>(Rotation::Left), 0,	 //in position 1


    // From Position 1 ..

    19, 19, static_cast<uint8_t>(Rotation::None), 0,	
    19, 21, static_cast<uint8_t>(Rotation::None), 0,
        	
    19, 23, static_cast<uint8_t>(Rotation::None), 0,	
    19, 25, static_cast<uint8_t>(Rotation::None), 0,	
    19, 27, static_cast<uint8_t>(Rotation::None), 0,	
    19, 29, static_cast<uint8_t>(Rotation::None), 0,

    19, 31, static_cast<uint8_t>(Rotation::None), 0,	
    19, 33, static_cast<uint8_t>(Rotation::None), 0,	
    19, 35, static_cast<uint8_t>(Rotation::None), 0,	
    19, 37, static_cast<uint8_t>(Rotation::None), 0,

    19, 39, static_cast<uint8_t>(Rotation::None), 0,	
    19, 41, static_cast<uint8_t>(Rotation::None), 0,	
    19, 43, static_cast<uint8_t>(Rotation::None), 0,	
    19, 45, static_cast<uint8_t>(Rotation::None), 0,	

    19, 47, static_cast<uint8_t>(Rotation::None), 0,	
    19, 49, static_cast<uint8_t>(Rotation::None), 0,	
    19, 51, static_cast<uint8_t>(Rotation::None), 0,	
    19, 53, static_cast<uint8_t>(Rotation::None), 0,

    19, 55, static_cast<uint8_t>(Rotation::None), 0,	

    // Common to all ..

    19, 57, static_cast<uint8_t>(Rotation::Left), 0,	// From Position 2
    17, 57, static_cast<uint8_t>(Rotation::Left), 0,	
    15, 57, static_cast<uint8_t>(Rotation::Left), 0,	
    13, 57, static_cast<uint8_t>(Rotation::Left), 0,	
    11, 58, static_cast<uint8_t>(Rotation::Left), 0,	
    9, 58, static_cast<uint8_t>(Rotation::Left), 0,	
    7, 58, static_cast<uint8_t>(Rotation::Left), 0,	
    5, 58, static_cast<uint8_t>(Rotation::Left), 0,	
    3, 58, static_cast<uint8_t>(Rotation::Left), 0,	
    1, 59, static_cast<uint8_t>(Rotation::Left), 0,	
    static_cast<uint8_t>(-1), 61, static_cast<uint8_t>(Rotation::Left), 0,	
    static_cast<uint8_t>(-1), 63, static_cast<uint8_t>(Rotation::Left), 0,	
    static_cast<uint8_t>(-1), 65, static_cast<uint8_t>(Rotation::Left), 0,	

    static_cast<uint8_t>(-1), 67, static_cast<uint8_t>(Rotation::Left), 0,	
    static_cast<uint8_t>(-1), 69, static_cast<uint8_t>(Rotation::Left), 0,	
    static_cast<uint8_t>(-1), 71, static_cast<uint8_t>(Rotation::Left), 0,	
      
    static_cast<uint8_t>(-1), 73, static_cast<uint8_t>(Rotation::Left), 0,	
    static_cast<uint8_t>(-1), 75, static_cast<uint8_t>(Rotation::Left), 0,	
    static_cast<uint8_t>(-1), 77, static_cast<uint8_t>(Rotation::Left), 0,	
    static_cast<uint8_t>(-1), 79, static_cast<uint8_t>(Rotation::Left), 0,	
      
    static_cast<uint8_t>(-1), 81, static_cast<uint8_t>(Rotation::Left), 0,	
    static_cast<uint8_t>(-1), 83, static_cast<uint8_t>(Rotation::Left), 0,	
    1, 83, static_cast<uint8_t>(Rotation::Right), 0,	
    3, 83, static_cast<uint8_t>(Rotation::Right), 0,	
    5, 83, static_cast<uint8_t>(Rotation::Right), 0,	

    7, 83, static_cast<uint8_t>(Rotation::Right), 0,	
    9, 84, static_cast<uint8_t>(Rotation::Right), 0,	
    11, 84, static_cast<uint8_t>(Rotation::Right), 0,	
    13, 84, static_cast<uint8_t>(Rotation::Right), 0,	//16
      
    15, 84, static_cast<uint8_t>(Rotation::Right), 0,	
    17, 84, static_cast<uint8_t>(Rotation::Right), 0,	
    19, 85, static_cast<uint8_t>(Rotation::Right), 0,	
    21, 85, static_cast<uint8_t>(Rotation::Right), 0,	
      
    23, 85, static_cast<uint8_t>(Rotation::Right), 0,	
    25, 85, static_cast<uint8_t>(Rotation::Right), 0,	
    27, 85, static_cast<uint8_t>(Rotation::Right), 0,	
    29, 86, static_cast<uint8_t>(Rotation::Right), 0,	//24
      
    31, 86, static_cast<uint8_t>(Rotation::Right), 0,	
    33, 86, static_cast<uint8_t>(Rotation::Right), 0,	
    35, 86, static_cast<uint8_t>(Rotation::Right), 0,	
    37, 86, static_cast<uint8_t>(Rotation::Right), 0,	
      
    39, 87, static_cast<uint8_t>(Rotation::Right), 0,	
    41, 87, static_cast<uint8_t>(Rotation::Right), 0,	
    43, 87, static_cast<uint8_t>(Rotation::Right), 0,	
    45, 87, static_cast<uint8_t>(Rotation::Right), 0,	//32
      
    47, 87, static_cast<uint8_t>(Rotation::Right), 0,	
    49, 88, static_cast<uint8_t>(Rotation::Right), 0,	
    51, 88, static_cast<uint8_t>(Rotation::Right), 0,	
    53, 88, static_cast<uint8_t>(Rotation::Right), 0,	
      
    55, 88, static_cast<uint8_t>(Rotation::Right), 0,	
    57, 88, static_cast<uint8_t>(Rotation::Right), 0,	
    59, 89, static_cast<uint8_t>(Rotation::Right), 0,	
    61, 89, static_cast<uint8_t>(Rotation::Right), 0,	//40
      
    63, 89, static_cast<uint8_t>(Rotation::Right), 0,	
    65, 89, static_cast<uint8_t>(Rotation::Right), 0,	
    67, 89, static_cast<uint8_t>(Rotation::Right), 0,	
    69, 90, static_cast<uint8_t>(Rotation::Right), 0,	
      
    71, 90, static_cast<uint8_t>(Rotation::Right), 0,	
    73, 90, static_cast<uint8_t>(Rotation::Right), 0,	
    75, 90, static_cast<uint8_t>(Rotation::Right), 0,	
    77, 90, static_cast<uint8_t>(Rotation::Right), 0,	//48
      
    79, 91, static_cast<uint8_t>(Rotation::Right), 0,	
    81, 91, static_cast<uint8_t>(Rotation::Right), 0,	
    83, 91, static_cast<uint8_t>(Rotation::Right), 0,	
    85, 91, static_cast<uint8_t>(Rotation::Right), 0,	
      
    87, 91, static_cast<uint8_t>(Rotation::Right), 0,	
    89, 92, static_cast<uint8_t>(Rotation::Right), 0,	
    91, 92, static_cast<uint8_t>(Rotation::Right), 0,	
    93, 92, static_cast<uint8_t>(Rotation::Right), 0,	//56
      
    95, 92, static_cast<uint8_t>(Rotation::Right), 0,	
    97, 92, static_cast<uint8_t>(Rotation::Right), 0,	
    99, 93, static_cast<uint8_t>(Rotation::Right), 0,	
    100, 94, static_cast<uint8_t>(Rotation::Right), 0,	
      
    101, 95, static_cast<uint8_t>(Rotation::Right), 0,	
    101, 97, static_cast<uint8_t>(Rotation::Right), 0,	
    101, 99, static_cast<uint8_t>(Rotation::Right), 0,	
    101, 101, static_cast<uint8_t>(Rotation::Right), 0,	//64
      
    101, 103, static_cast<uint8_t>(Rotation::Right), 0,	
    101, 105, static_cast<uint8_t>(Rotation::Right), 0,	
    101, 107, static_cast<uint8_t>(Rotation::Right), 0,	
    101, 109, static_cast<uint8_t>(Rotation::Right), 0,	
      
    101, 111, static_cast<uint8_t>(Rotation::Right), 0,	
    101, 113, static_cast<uint8_t>(Rotation::Right), 0,	
    101, 115, static_cast<uint8_t>(Rotation::Right), 0,	
    99, 115, static_cast<uint8_t>(Rotation::Left), 0,	//72
      
    97, 115, static_cast<uint8_t>(Rotation::Left), 0,	
    95, 115, static_cast<uint8_t>(Rotation::Left), 0,	
    93, 116, static_cast<uint8_t>(Rotation::Left), 0,	
    91, 116, static_cast<uint8_t>(Rotation::Left), 0,	
      
    89, 116, static_cast<uint8_t>(Rotation::Left), 0,	
    87, 116, static_cast<uint8_t>(Rotation::Left), 0,	
    85, 116, static_cast<uint8_t>(Rotation::Left), 0,	
    83, 117, static_cast<uint8_t>(Rotation::Left), 0,	//80
      
    81, 117, static_cast<uint8_t>(Rotation::Left), 0,	
    79, 117, static_cast<uint8_t>(Rotation::Left), 0,	
    77, 117, static_cast<uint8_t>(Rotation::Left), 0,	
    75, 117, static_cast<uint8_t>(Rotation::Left), 0,	
      
    73, 118, static_cast<uint8_t>(Rotation::Left), 0,	
    71, 118, static_cast<uint8_t>(Rotation::Left), 0,	
    69, 118, static_cast<uint8_t>(Rotation::Left), 0,	
    67, 118, static_cast<uint8_t>(Rotation::Left), 0,	//88
      
    65, 118, static_cast<uint8_t>(Rotation::Left), 0,	
    63, 119, static_cast<uint8_t>(Rotation::Left), 0,	
    61, 119, static_cast<uint8_t>(Rotation::Left), 0,	
    59, 119, static_cast<uint8_t>(Rotation::Left), 0,	
      
    57, 119, static_cast<uint8_t>(Rotation::Left), 0,	
    55, 119, static_cast<uint8_t>(Rotation::Left), 0,	
    53, 120, static_cast<uint8_t>(Rotation::Left), 0,	
    51, 120, static_cast<uint8_t>(Rotation::Left), 0,	//96
      
    49, 120, static_cast<uint8_t>(Rotation::Left), 0,	
    47, 120, static_cast<uint8_t>(Rotation::Left), 0,	
    45, 120, static_cast<uint8_t>(Rotation::Left), 0,	
    43, 121, static_cast<uint8_t>(Rotation::Left), 0,	
      
    41, 121, static_cast<uint8_t>(Rotation::Left), 0,	
    39, 121, static_cast<uint8_t>(Rotation::Left), 0,	
    37, 121, static_cast<uint8_t>(Rotation::Left), 0,	
    35, 121, static_cast<uint8_t>(Rotation::Left), 0,	//104
      
    33, 122, static_cast<uint8_t>(Rotation::Left), 0,	
    31, 122, static_cast<uint8_t>(Rotation::Left), 0,	
    29, 122, static_cast<uint8_t>(Rotation::Left), 0,	
    27, 122, static_cast<uint8_t>(Rotation::Left), 0,	
      
    25, 122, static_cast<uint8_t>(Rotation::Left), 0,	
    23, 123, static_cast<uint8_t>(Rotation::Left), 0,	
    21, 123, static_cast<uint8_t>(Rotation::Left), 0,	
    19, 123, static_cast<uint8_t>(Rotation::Left), 0,	//112
      
    17, 123, static_cast<uint8_t>(Rotation::Left), 0,	
    15, 123, static_cast<uint8_t>(Rotation::Left), 0,	
    13, 124, static_cast<uint8_t>(Rotation::Left), 0,	
    11, 124, static_cast<uint8_t>(Rotation::Left), 0,	
      
    9, 124, static_cast<uint8_t>(Rotation::Left), 0,	
    7, 124, static_cast<uint8_t>(Rotation::Left), 0,	
    5, 124, static_cast<uint8_t>(Rotation::Left), 0,	
    3, 125, static_cast<uint8_t>(Rotation::Left), 0,	//120
      
    1, 126, static_cast<uint8_t>(Rotation::Left), 0,	//last corner
    1, 128, static_cast<uint8_t>(Rotation::Left), 0,	
    1, 130, static_cast<uint8_t>(Rotation::Left), 0,	
    1, 132, static_cast<uint8_t>(Rotation::Left), 0,	
      
    1, 134, static_cast<uint8_t>(Rotation::Left), 0,	
    1, 136, static_cast<uint8_t>(Rotation::Left), 0,	
    1, 138, static_cast<uint8_t>(Rotation::Left), 0,	
    1, 140, static_cast<uint8_t>(Rotation::Left), 0,	//128

    0, 0, static_cast<uint8_t>(Rotation::None), 0,	//End

  };
 
 }