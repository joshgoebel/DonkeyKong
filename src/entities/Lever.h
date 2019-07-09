#pragma once

#include "../utils/Arduboy2Ext.h"
#include "../Utils/Enums.h"
#include "../map/Coordinates.h"
#include "Crane.h"

class Lever {

  public:

    Lever();
 
    // Properties ..

    LeverPosition getPosition();
    uint8_t getCounter();

    void setPosition(LeverPosition position);
    void setCounter(uint8_t counter);
    void setCrane(Crane *crane);


    // Methods

    void update();


  protected:

    LeverPosition position = LeverPosition::Off;
    Crane *crane;
    uint8_t counter = 0;

};

