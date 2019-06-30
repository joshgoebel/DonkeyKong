#include "src/Game.h"

#include "src/utils/Arduboy2Ext.h"

#ifdef DEBUG_NO_USB
ARDUBOY_NO_USB 
#endif

Game game;

void setup() {
	game.setup();
}

void loop() {
	game.loop();
}
