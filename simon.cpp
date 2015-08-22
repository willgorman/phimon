#include "InternetButton.h"
#include "Game.h"

InternetButton b = InternetButton();
Game game = Game(b);

void setup() {
  b.begin();
}

void loop() {
  // If the game isn't running we'll check for all buttons pressed to start it
  if (!game.inProgress()) {
    if (b.allButtonsOn()) {
      game.begin();
    }
    return;
  }

  game.play();
}
