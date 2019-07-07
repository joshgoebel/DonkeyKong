#pragma once

#include "../utils/Arduboy2Ext.h"
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
    bool getMoveToCentre();
    GorillaStance getStance();
    uint8_t getFallingIndex();


    void setFallingIndex(uint8_t fallingIndex);


    // Methods ..

    void move();
    void launch(Barrel *barrel);
    bool isPaused();
    bool isReadyToLaunch();
    uint8_t isInPosition();
    void moveToCentre();
    void reset();
    void incFallingIndex();


  private:

    void moveLeftOrRight();
    void changeDirections();

  protected:

    uint8_t pause = 40;
    uint8_t launchBarrel = 0;
    uint8_t xPosition = GORILLA_X_POSITION_1;
    uint8_t fallingIndex = 0;
    Movements movement;
    Barrel *barrel;
    bool moveCentre = false;

};

