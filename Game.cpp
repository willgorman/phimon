#include "InternetButton.h"
#include "Game.h"

Game::Game(InternetButton btn) {
  b = btn;
  started = false;
  rnd = 0;
  playerTurn = false;
}

void Game::begin() {
  started = true;
  rnd = 1;
  memset(cpuMoves, 0, sizeof(cpuMoves));
  playerTurn = false;
  b.rainbow(3);
  b.playSong("E5,8,G5,8,E6,8,C6,8,D6,8,G6,8");
  b.allLedsOff();
  delay(1000);
  randomSeed(millis());
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
  if (playerTurn) {
    uint8_t outcome = checkPlayerMove();
    switch (outcome) {
      case 0:
        return true;
      case 1:
        lightButton(*nextMove, 1000);
        nextMove = nextMove + sizeof(uint8_t);
        if (*nextMove == 0) {
          playerTurn = false;
          rnd++;
          b.rainbow(1);
          b.playSong("E5,8,G6,8");
          //TODO Fanfare!
          b.allLedsOff();
          delay(1000);
        }
        return true;
      case 2:
        started = false;
        showGameOver(2000);
        //TODO: sad trombone
        return false;
    }
  } else {
    nextMove = getCPUMoves();
    playerTurn = true;
  }
  return true;
}

uint8_t* Game::getCPUMoves() {
  memset(cpuMoves, 0, sizeof(cpuMoves));
  for (size_t i = 0; i < rnd; i++) {
    cpuMoves[i] = random(1,5);
    lightButton(cpuMoves[i], 1000); // TODO: decrease per round?
    delay(1000);
  }
  return cpuMoves;
}

uint8_t Game::checkPlayerMove() {
  if (b.allButtonsOff()) {
    return NO_MOVE;
  } else {
    //TODO: this allows cheating with multiple buttons
    return b.buttonOn(*nextMove) ? GOOD_MOVE : BAD_MOVE;
  }
}

void Game::showGameOver(uint8_t duration) {
  // uint8_t elapsed = 0;
  // while (elapsed < duration) {
  //     b.allLedsOn(100, 0, 0);
  //     delay(1000);
  //     b.allLedsOff();
  //     delay(1000);
  //     elapsed += 500;
  // }
  b.allLedsOn(100, 0, 0);
  b.playSong("D5,8,D5,8,C5,8,B5,8"); 
  delay(750);
  b.allLedsOff();
}

void Game::lightButton(uint8_t button, uint8_t duration) {
  uint8_t first;
  switch (button) {
    case 1:
      b.ledOn(1, 255, 0, 0);
      b.ledOn(11, 255, 0, 0);
      b.playNote("E5",4);
      break;
    case 2:
      first = buttonLights[button - 1] - 1;
      for (size_t i = first; i < (first + 3); i++) {
        b.ledOn(i, 0, 255, 0);
      }
      b.playNote("G6",4);
      break;
    case 3:
      first = buttonLights[button - 1] - 1;
      for (size_t i = first; i < (first + 3); i++) {
        b.ledOn(i, 0, 0, 255);
      }
      b.playNote("G5",4);
      break;
    case 4:
      first = buttonLights[button - 1] - 1;
      for (size_t i = first; i < (first + 3); i++) {
        b.ledOn(i, 255, 255, 34);
      }
      b.playNote("C5",4);
      break;
  }
  delay(duration);
  b.allLedsOff();
}
