#pragma once

#include "UI/screenManager.hpp"
#include "display.hpp"
#include <raylib.h>
#include "UI/util/button.hpp"
#include "UI/util/background.hpp"

class MainMenuIO : public Display {
private:
  ScreenManager& screenManager;
  Background background;
  Button playButton;
  Button exitButton;

public:
  MainMenuIO(ScreenManager& screenManager);
  ~MainMenuIO() override = default;

  void update() override;
  void draw() const override;
};