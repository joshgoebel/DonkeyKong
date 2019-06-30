#pragma once

#include <Arduboy2.h>
#include "../Utils/Enums.h"
#include "../map/Coordinates.h"

class Player {

  public:

    Player();
 
    // Properties ..

    uint8_t getPosition();

    void setPosition(uint8_t position);

  protected:

    uint8_t position;

};

