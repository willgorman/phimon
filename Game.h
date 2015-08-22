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
    started;
  uint32_t
    rnd;

// Methods

};
