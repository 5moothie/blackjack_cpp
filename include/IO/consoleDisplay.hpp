#pragma once

#include "IO/gameDisplay.hpp"
#include "blackjack/dealer.hpp"
#include "blackjack/player.hpp"

class ConsoleDisplay : public GameDisplay {
private:
  void clearConsole() const noexcept;
public:
 ~ConsoleDisplay() = default;

  void showMainMenu() override;
  void showTable(const Dealer& dealer, const Player& player) override;
  void showBettingScreen(const Player& player) override;
  void showHandResults(const Dealer& dealer, const Player& player) override;
};