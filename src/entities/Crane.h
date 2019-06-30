#pragma once

#include <Arduboy2.h>
#include "../Utils/Enums.h"
#include "../map/Coordinates.h"

class Crane {

  public:

    Crane();
 
    // Properties ..

    CranePosition getPosition();
    uint8_t getCounter();

    void setPosition(CranePosition position);
    void setCounter(uint8_t counter);


    // Methods

    void turnOn();
    void update();
    uint8_t getImage();


  protected:

    CranePosition position = CranePosition::Declined;
    uint8_t hook = 2;
    CraneState state = CraneState::Dormant;
    uint8_t counter = 0;
    Movements hookDirection = Movements::Right;

};

