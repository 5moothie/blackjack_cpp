#pragma once


#include "blackjack/blackjackGame.hpp"
#include "display.hpp"
#include "screens.hpp"


class ProgramManager : Display {
private:
  ProgramScreen programScreen;
  BlackjackGame blackjackGame;


  void update() override {};
  void draw() override {};

public:
  ~ProgramManager() override = default;

  void start();
  void setProgramScreen(ProgramScreen newProgramScreen);
};