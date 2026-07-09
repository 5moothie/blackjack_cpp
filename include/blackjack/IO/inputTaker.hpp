#pragma once
#include "blackjack/IO/actions.hpp"

#include "blackjack/components/player.hpp"

class InputTaker {
public:
  virtual ~InputTaker() = default;

  virtual int getBet(const Player& player) = 0;
  virtual MainMenuActions getMenuAction() = 0;
  virtual BetweenHandActions getBetweenHandsAction(const Player& player) = 0;
  virtual HandActions getHandAction(const Player& player) = 0;
};