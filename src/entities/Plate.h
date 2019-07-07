#pragma once

#include "../utils/Arduboy2Ext.h"
#include "../Utils/Enums.h"

class Plate {

  public:

    Plate();
 
    // Properties ..

    uint8_t getPlateNumber();
    uint8_t getCounter();
    int8_t getXOffset();
    uint8_t getYOffset();
    uint8_t getImage();

    void setPlateNumber(uint8_t plateNumber);
    void setCounter(uint8_t counter);

    // Methods ..

    void incCounter();

  protected:

    uint8_t plateNumber = 0;
    uint8_t counter = 0;

};

