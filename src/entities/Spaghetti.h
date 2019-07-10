#pragma once

#include "../utils/Arduboy2Ext.h"
#include "../Utils/Enums.h"
#include "Base.h"

class Spaghetti : public Base {

  public:

    Spaghetti();
 

    // Properties ..

    bool isVisible();
    uint8_t getFood();
    
    void setVisible(bool visible);
    void setFood(uint8_t visfoodible);


    // Methods

    void update();
    void incFood();


  protected:

    uint8_t food = 0;
    bool visible = true;

};

