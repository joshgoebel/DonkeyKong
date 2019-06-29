#include <Arduboy2.h>
Arduboy2 arduboy;

#include "src/images/Images.h"
#include "src/map/Coordinates.h"
#include "src/utils/Enums.h"

int8_t barrel_Rot = 0;
uint8_t barrel_Pos = 0;

uint8_t playerPosition = 0;

void setup() {

  arduboy.boot();
  arduboy.flashlight();
  arduboy.systemButtons();
  arduboy.setFrameRate(60);
  arduboy.initRandomSeed();
	arduboy.clear();

}

void loop() {

	if (!arduboy.nextFrame()) return;
	arduboy.clear();


  //Handle movements ..
  {
    uint8_t movements = pgm_read_byte(&Coordinates::Player[(playerPosition * 6) + 5]);

    if (movements & static_cast<uint8_t>(Movements::Reverse)) {

      if (arduboy.pressed(LEFT_BUTTON) && (movements & static_cast<uint8_t>(Movements::Left))) {
        playerPosition++;
      }

      if (arduboy.pressed(RIGHT_BUTTON) && (movements & static_cast<uint8_t>(Movements::Right))) {
        playerPosition--;
      }


    }
    else {

if (arduboy.pressed(RIGHT_BUTTON)) {
  Serial.print("Right ");
  Serial.print(movements);
  Serial.print(" ");
  Serial.println(movements & static_cast<uint8_t>(Movements::Left));
}
      if (arduboy.pressed(LEFT_BUTTON) && (movements & static_cast<uint8_t>(Movements::Left))) {
        playerPosition--;
      }

      if (arduboy.pressed(RIGHT_BUTTON) && (movements & static_cast<uint8_t>(Movements::Right))) {
        playerPosition++;
      }

    }

    if (arduboy.pressed(DOWN_BUTTON) && (movements & static_cast<uint8_t>(Movements::Down))) {
      playerPosition--;
    }

    if (arduboy.pressed(UP_BUTTON) && (movements & static_cast<uint8_t>(Movements::Up))) {
      playerPosition++;
    }

  }

  uint8_t yOffset = pgm_read_byte(&Coordinates::Player[(playerPosition * 6) + 2]);


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
        
        case static_cast<uint8_t>(Components::Ladder):
          Sprites::drawExternalMask(x, y, Images::Ladder, Images::Ladder_Mask, 0, 0);
          break;
          
      }

    }

  }


  // Draw Barrel
  {
    uint8_t x = pgm_read_byte(&Coordinates::Barrel[(barrel_Pos * 3)]);
    int8_t y = pgm_read_byte(&Coordinates::Barrel[(barrel_Pos * 3) + 1]) - yOffset;
    Rotation rot = static_cast<Rotation>(pgm_read_byte(&Coordinates::Barrel[(barrel_Pos * 3) + 2]));

    Sprites::drawExternalMask(x, y, Images::Barrel, Images::Barrel_Mask, barrel_Rot, 0);

    if (arduboy.everyXFrames(4)) {

      switch (rot) {
        case Rotation::Right:
          barrel_Rot++;
          if (barrel_Rot == 4) barrel_Rot = 0;
          break;

        case Rotation::Left:
          barrel_Rot--;
          if (barrel_Rot == -1) barrel_Rot = 3;
          break;

      }

      barrel_Pos++;
      if (barrel_Pos == 128) barrel_Pos = 0;

    }
  }

  // Draw player

  {
    uint8_t x = pgm_read_byte(&Coordinates::Player[(playerPosition * 6)]);
    int8_t y = pgm_read_byte(&Coordinates::Player[(playerPosition * 6) + 1]) - yOffset;
// Serial.print(x);
// Serial.print(" ");
// Serial.print(y);
// Serial.print(" ");
// Serial.println(y + 64);
    Sprites::drawSelfMasked(x, y, Images::Mario, 0);

    arduboy.display();

  }
}