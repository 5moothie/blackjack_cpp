#pragma once

#include "UI/screenManager.hpp"
#include "display.hpp"

class MainMenuIO : public Display {
private:
  ScreenManager& screenManager;

public:
  MainMenuIO(ScreenManager& screenManager);
  ~MainMenuIO() override = default;

  void update() override {}
  void draw() const override {}
};