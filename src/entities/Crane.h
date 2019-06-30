#pragma once

#include <Arduboy2.h>
#include "../Utils/Enums.h"
#include "../map/Coordinates.h"

class Crane {

  public:

    Crane();
 
    // Properties ..

    LeverPosition getPosition();
    uint8_t getCounter();

    void setPosition(LeverPosition position);
    void setCounter(uint8_t counter);


    // Methods

    void update();


  protected:

    LeverPosition position = LeverPosition::Off;
    uint8_t counter = 0;

};

