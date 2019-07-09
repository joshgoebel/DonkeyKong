#pragma once

#include "../utils/Arduboy2Ext.h"
#include "../Utils/Enums.h"

class Hook {

  public:

    Hook();
 
    // Properties ..

    uint8_t getCounter();
    void setCounter(uint8_t counter);

    // Methods ..

    void decCounter();

  protected:

    uint8_t counter = 0;

};

