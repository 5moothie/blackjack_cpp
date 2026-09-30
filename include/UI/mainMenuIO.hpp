#pragma once

#include "UI/screenManager.hpp"
#include "display.hpp"
#include <raylib.h>
#include "UI/util/button.hpp"

class MainMenuIO : public Display {
private:
  ScreenManager& screenManager;
  Texture2D background;
  Button playButton;
  Button exitButton;

public:
  MainMenuIO(ScreenManager& screenManager);
  ~MainMenuIO() override;

  void update() override;
  void draw() const override;
};