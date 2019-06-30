#pragma once

#include <Arduboy2.h>
#include "../Utils/Enums.h"
#include "../map/Coordinates.h"

class Barrel {

  public:

    Barrel();

 
    // Properties ..
    uint8_t getPosition();
    uint8_t getRotation();
    uint8_t getNumber();
    bool isEnabled();

    void setPosition(uint8_t position);
    void setRotation(uint8_t rotation);
    void setEnabled(bool enabled);
    void setNumber(uint8_t number);

    // Methods ..

    int8_t getXPosition();
    int8_t getYPosition(uint8_t yOffset);
    void updatePosition();
    void rotate();
    void launch(uint8_t startingPosition);

  protected:

    uint8_t number;
    uint8_t position;
    uint8_t rotation;
    bool enabled;
    Rotation rotationDirection;

};

