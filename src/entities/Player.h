#pragma once

#include <Arduboy2.h>
#include "../Utils/Enums.h"
#include "../map/Coordinates.h"

class Player {

  public:

    Player();
 
    // Properties ..

    uint8_t getPosition();
    uint8_t getJumpPosition();
    uint8_t getXPosition();
    int8_t getYPosition();
    uint8_t getMovements();
    uint8_t getYOffset();

    void setPosition(uint8_t position);
    void setJumpPosition(uint8_t jumpPosition);
    void setMovements(uint8_t movements);
    void setYOffset(uint8_t yOffset);


    // Methods

    void incPlayerPosition();
    void decPlayerPosition();
    bool canMove(Movements movement);

  protected:

    uint8_t position;
    uint8_t jumpPosition;
    uint8_t movements;
    uint8_t yOffset;

};

