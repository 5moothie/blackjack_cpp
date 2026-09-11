#pragma once

#include "blackjack/blackjackGame.hpp"
#include "display.hpp"

class BlackjackRayLibIO : public Display {
private:
  BlackjackGame& blackjackGame;

public:
  BlackjackRayLibIO();

  void update() override;
  void draw() override;
};