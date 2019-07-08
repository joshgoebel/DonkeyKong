#pragma once

#include "../utils/Arduboy2Ext.h"
#include "../Utils/Enums.h"

class Spaghetti {

  public:

    Spaghetti();
 

    // Properties ..

    uint8_t getCounter();
    bool isVisible();

    void setCounter(uint8_t counter);
    void setVisible(bool visible);


    // Methods

    void update();


  protected:

    uint8_t counter = 0;
    bool visible = true;

};

