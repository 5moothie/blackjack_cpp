#pragma once

#include "blackjack/IO/inputTaker.hpp"
#include "blackjack/IO/actions.hpp"

class ConsoleInputTaker : public InputTaker {
public:
  ~ConsoleInputTaker() = default;

  int getBet(const Player& player) override;
  MainMenuActions getMenuAction() override;
  BetweenHandActions getBetweenHandsAction(const Player& player) override;
  HandActions getHandAction(const Player& player) override;
};