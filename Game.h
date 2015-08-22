#include "InternetButton.h"

class Game {
public:
  Game(InternetButton b);
  void
    begin(void);
  uint8_t
    inProgress(void),
    play(void);
  uint32_t
    getRound(void);

private:

// Members
  InternetButton
    b;
  uint8_t
    started,
    playerTurn,
    *nextMove;
  uint8_t  cpuMoves[50];
  uint32_t
    rnd;

  const uint8_t NO_MOVE = 0;
  const uint8_t GOOD_MOVE = 1;
  const uint8_t BAD_MOVE = 2;

  //TODO: button1 should be 1 AND 11 since there's no 12 o'clock
  uint8_t buttonLights[4] = {1, 3, 6, 9};


// Methods
  uint8_t
    *getCPUMoves(void),
    checkPlayerMove(void);
  void
    showGameOver(uint8_t duration),
    lightButton(uint8_t button, uint8_t duration);

};
