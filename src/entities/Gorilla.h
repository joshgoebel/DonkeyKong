#pragma once

#include <Arduboy2.h>
#include "../Utils/Enums.h"
#include "Barrel.h"

#define GORILLA_X_POSITION_1 13
#define GORILLA_X_POSITION_2 38
#define GORILLA_X_POSITION_3 63

class Gorilla {

  public:

    Gorilla();


    // Properties ..

    uint8_t getXPosition();
    int8_t getYPosition(uint8_t yOffset);
    GorillaStance getStance();


    // Methods ..

    void move();
    void launch(Barrel *barrel);
    bool isPaused();
    bool isReadyToLaunch();

  private:

    void moveLeftOrRight();
    void changeDirections();

  protected:

    uint8_t pause = 40;
    uint8_t launchBarrel = 0;
    uint8_t xPosition = GORILLA_X_POSITION_1;
    Movements movement;
    Barrel *barrel;

};

