#include "InternetButton.h"
#include "Game.h"

Game::Game(InternetButton btn) {
  b = btn;
  started = false;
  rnd = 0;
}

void Game::begin() {
  started = true;
  rnd = 1;
  b.rainbow(3);
  //TODO: Fanfare!
}

uint8_t Game::inProgress() {
  return started;
}

uint32_t Game::getRound() {
  return rnd;
}

/*
* Returns true if the game is still going or false if over
*
*/
uint8_t Game::play() {
  return true;
}
