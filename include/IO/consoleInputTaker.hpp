#pragma once

#include "IO/inputTaker.hpp"
#include "IO/actions.hpp"

class ConsoleInputTaker : public InputTaker {
public:
  ~ConsoleInputTaker() = default;

  int getBet(const Player& player) override;
  MainMenuActions getMenuAction() override;
  BetweenHandActions getBetweenHandsAction(const Player& player) override;
  HandActions getHandAction(const Player& player) override;
};