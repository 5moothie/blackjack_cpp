#pragma once


#include "blackjack/blackjackGame.hpp"
#include "screens.hpp"


class GameManager {
private:
  ProgramScreen programScreen;
  BlackjackGame blackjackGame;


  void update();
  void draw();

public:
  void start();
};