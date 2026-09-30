#pragma once

#include "blackjack/blackjackGame.hpp"
#include "UI/display.hpp"
#include "UI/screenManager.hpp"
#include <raylib.h>

class BlackjackRayLibIO : public Display {
private:
  BlackjackGame blackjackGame{};
  ScreenManager& screenManager;

public:
  BlackjackRayLibIO(ScreenManager& screenManager): screenManager(screenManager) {}

  void update() override {}
  void draw() const override;
};