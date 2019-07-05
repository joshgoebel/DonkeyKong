#pragma once

#include <Arduboy2.h>
#include "../Utils/Enums.h"
#include "../map/Coordinates.h"

class Player {

  public:

    Player();
 
    // Properties ..

    uint8_t getPosition();
    uint8_t getJumpPosition();
    uint8_t getXPosition();
    int8_t getYPosition();
    uint8_t getMovements();
    uint8_t getYOffset();
    bool isDead();
    bool isLeaping();

    void setPosition(uint8_t position);
    void setJumpPosition(uint8_t jumpPosition);
    void setMovements(uint8_t movements);
    void setYOffset(uint8_t yOffset);
    void setDead(bool dead);
    void setLeaping(bool dead);


    // Methods

    void incPlayerPosition();
    void decPlayerPosition();
    bool canMove(Movements movement);
    void initLife();
    void updateJump();
    void startJump();
    bool isJumping();
    uint8_t getImage();
    Rect getRect();
    void reset();

  protected:

    uint8_t position;
    uint8_t jumpPosition;
    uint8_t movements;
    uint8_t yOffset;

    uint8_t prevXPosition;
    uint8_t currXPosition;
    uint8_t runCounter;
    Movements runMovement = Movements::Right;

    bool dead = false;
    bool leaping = false;

};

