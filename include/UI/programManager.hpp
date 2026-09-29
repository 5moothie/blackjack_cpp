#pragma once


#include "blackjack/UI/blackjackRayLibIO.hpp"
#include "UI/display.hpp"
#include "UI/screenManager.hpp"
#include "mainMenuIO.hpp"
#include <memory>


class ProgramManager : public Display {
private:
  std::unique_ptr<ScreenManager> screenManager;
  std::unique_ptr<BlackjackRayLibIO> blackjackIO;
  std::unique_ptr<MainMenuIO> mainMenuIO;

  

public:
  void update() override;
  void draw() const override;
  ProgramManager();
  ~ProgramManager() override = default;

  void start();
};