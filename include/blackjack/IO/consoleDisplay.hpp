#pragma once

#include "blackjack/IO/gameDisplay.hpp"
#include "blackjack/components/dealer.hpp"
#include "blackjack/components/player.hpp"

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