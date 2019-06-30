#include <Arduboy2.h>
Arduboy2 arduboy;

#include "src/utils/Enums.h"
#include "src/images/Images.h"
#include "src/map/Coordinates.h"
#include "src/entities/Entities.h"


Gorilla gorilla;
Barrel barrels[6];
Girder girders[2];
Lever lever;
Player player;

void setup() {

  arduboy.boot();
  arduboy.flashlight();
  arduboy.systemButtons();
  arduboy.setFrameRate(60);
  arduboy.initRandomSeed();
	arduboy.clear();

  for (auto &barrel : barrels) {

    if (random(0, 2) == 0) {

      barrel.setPosition(random(4, 180));
      barrel.setEnabled(true);

    }

  }

}

void loop() {

	if (!arduboy.nextFrame()) return;
	arduboy.clear();


  //Handle movements ..
  {
    
    if (player.canMove(Movements::Reverse)) {

      if (arduboy.pressed(LEFT_BUTTON) && player.canMove(Movements::Left)) {
        player.incPlayerPosition();
      }

      if (arduboy.pressed(RIGHT_BUTTON) && player.canMove(Movements::Right)) {
        player.decPlayerPosition();
      }


    }
    else {

      if (arduboy.pressed(LEFT_BUTTON) && player.canMove(Movements::Left)) {
        player.decPlayerPosition();
      }

      if (arduboy.pressed(LEFT_BUTTON) && player.canMove(Movements::Lever)) {
        lever.setPosition(LeverPosition::On);
      }

      if (arduboy.pressed(RIGHT_BUTTON) && player.canMove(Movements::Right)) {
        player.incPlayerPosition();
      }

    }

    if (arduboy.pressed(DOWN_BUTTON) && player.canMove(Movements::Down)) {
      player.decPlayerPosition();
    }

    if (arduboy.pressed(UP_BUTTON) && player.canMove(Movements::Up)) {
      player.incPlayerPosition();
    }

  }


  uint8_t yOffset = player.getYOffset();


  // Handle Barrels
  {

    // Should we launch a new barrel?

    if (gorilla.isReadyToLaunch() && random(0, 40) == 0) {

      for (auto &barrel : barrels) {

        if (!barrel.isEnabled()) {

          Barrel* ptr_Barrel = &barrel;
          gorilla.launch(ptr_Barrel);
          break;

        }

      }

    }

  }


  // Update girders ..

  if (arduboy.everyXFrames(4)) {

    for (auto &girder : girders) {

      if (girder.isEnabled()) {

        girder.updatePosition();

      }

    }

  }

  uint8_t activeGirderCount = getActiveGirderCount();
  uint8_t girderMaxPosition = getGirderMaxPosition();

  if ((activeGirderCount == 0 || (activeGirderCount == 1 < 2 && girderMaxPosition > 50)) && random(0, 50) == 0) {

    uint8_t girderIndex = getDisabledGirderIndex();

    Girder &girder = girders[girderIndex];
    girder.setEnabled(true);

  }


  //Update lever

  lever.update();


  //----------------------------------------------------------------------

  // Draw Scenery ..
  {
    for (uint8_t i = 0; i < SCENERY_COUNT; i++) {

      int8_t x = pgm_read_byte(&Coordinates::Scenery[(i * 4)]);
      int8_t y = pgm_read_byte(&Coordinates::Scenery[(i * 4) + 1]) - yOffset;
      uint8_t image = pgm_read_byte(&Coordinates::Scenery[(i * 4) + 2]);

      switch (image) {
        
        case static_cast<uint8_t>(Components::Girder):
          Sprites::drawSelfMasked(x, y, Images::Girder, 0);
          break;
        
        case static_cast<uint8_t>(Components::Girder_OverHead):
          Sprites::drawSelfMasked(x, y, Images::Girder_OverHead, 0);
          break;
        
        case static_cast<uint8_t>(Components::Girder_Small):
          Sprites::drawSelfMasked(x, y, Images::Girder_Small, 0);
          break;
        
        case static_cast<uint8_t>(Components::Plate1):
          Sprites::drawSelfMasked(x, y, Images::Plate_1, 0);
          break;
        
        case static_cast<uint8_t>(Components::Plate2):
          Sprites::drawSelfMasked(x, y, Images::Plate_2, 0);
          break;
        
        case static_cast<uint8_t>(Components::Ladder):
          Sprites::drawExternalMask(x, y, Images::Ladder, Images::Ladder_Mask, 0, 0);
          break;
        
        case static_cast<uint8_t>(Components::Lever):
          Sprites::drawSelfMasked(x, y, Images::Lever, static_cast<uint8_t>(lever.getPosition()));
          break;
        
        case static_cast<uint8_t>(Components::Cable1):
          Sprites::drawExternalMask(x, y, Images::Cable_1, Images::Cable_1_Mask, 0, 0);
          break;
        
        case static_cast<uint8_t>(Components::Cable2):
          Sprites::drawExternalMask(x, y, Images::Cable_2, Images::Cable_2_Mask, 0, 0);
          break;
        
        case static_cast<uint8_t>(Components::Crane):
          Sprites::drawSelfMasked(x, y, Images::Crane, 0);
          break;
        
        case static_cast<uint8_t>(Components::Hook):
          Sprites::drawSelfMasked(x, y, Images::Hook, 0);
          break;
          
      }

    }

  }

  // Draw Barrels
  {

    for (auto &barrel : barrels) {

      if (barrel.isEnabled()) {

        Sprites::drawExternalMask(barrel.getXPosition(), barrel.getYPosition(yOffset), Images::BarrelImg, Images::Barrel_Mask, barrel.getRotation(), 0);

        if (arduboy.everyXFrames(4)) {

          barrel.updatePosition();
          barrel.rotate();

        }

      }

    }

  }

  // Draw player

  {
    Sprites::drawSelfMasked(player.getXPosition(), player.getYPosition(), Images::Mario, 0);

  }


  // Draw gorilla

  gorilla.move();
  Sprites::drawSelfMasked(gorilla.getXPosition(), gorilla.getYPosition(yOffset), Images::Gorilla, static_cast<uint8_t>(gorilla.getStance()) );


  // Draw girders ..

  for (auto &girder : girders) {

    if (girder.isEnabled()) {

      Sprites::drawExternalMask(girder.getXPosition(), girder.getYPosition(yOffset), Images::Girder_Moving, Images::Girder_Moving_Mask, girder.getImage(), girder.getImage());

    }

  }


  arduboy.display();

}

uint8_t getActiveGirderCount() {

  uint8_t girderCount = 0;

  for (auto &girder : girders) {

      if (girder.isEnabled()) {

        girderCount++;

      }
  
  }

  return girderCount;

}

uint8_t getGirderMaxPosition() {

  uint8_t girderPosition = 0;

  for (auto &girder : girders) {

      if (girder.isEnabled() && girder.getPosition() > girderPosition) {

        girderPosition = girder.getPosition();

      }
  
  }

  return girderPosition;
  
}

#define GIRDER_COUNT 2
#define NONE_FOUND 255

uint8_t getDisabledGirderIndex() {

  for (uint8_t x = 0; x < GIRDER_COUNT; x++) {

      Girder girder = girders[x];

      if (!girder.isEnabled()) {

        return x;

      }
  
  }

  return NONE_FOUND;
  
}