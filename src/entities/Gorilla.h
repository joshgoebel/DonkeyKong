#pragma once

#include <Arduboy2.h>

class Gorilla {

  public:

    Gorilla();


    // Properties ..

    uint8_t getPosition();

    void setPosition(uint8_t position);

  protected:

    uint8_t position;

};

