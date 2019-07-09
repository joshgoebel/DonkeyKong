#pragma once

#include "../utils/Arduboy2Ext.h"
#include "../Utils/Enums.h"
#include "Base.h"

class Spaghetti : public Base {

  public:

    Spaghetti();
 

    // Properties ..

    bool isVisible();
    void setVisible(bool visible);


    // Methods

    void update();


  protected:

    bool visible = true;

};

