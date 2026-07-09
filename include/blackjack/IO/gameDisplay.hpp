#pragma once

#include "blackjack/components/dealer.hpp"
#include "blackjack/components/player.hpp"


class GameDisplay {
public:
  virtual ~GameDisplay() = default;

  virtual void showMainMenu() = 0;
  virtual void showTable(const Dealer& dealer, const Player& player) = 0;
  virtual void showBettingScreen(const Player& player) = 0;
  virtual void showHandResults(const Dealer& dealer, const Player& player) = 0;
};