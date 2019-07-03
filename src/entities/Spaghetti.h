#pragma once

#include <Arduboy2.h>
#include "../Utils/Enums.h"

class Spaghetti {

  public:

    Spaghetti();
 

    // Properties ..

    uint8_t getCounter();

    void setCounter(uint8_t counter);


    // Methods

    void update();


  protected:

    uint8_t counter = 0;

};

