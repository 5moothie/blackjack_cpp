#pragma once

#include "blackjack/components/playerHand.hpp"
#include "blackjack/components/shoe.hpp"

#include <stdexcept>
#include <vector>

// #define int long long  // honorable mention ~ Ula

/*
Since the balance is an integer for simplicity, the bets must be even. F. eg. 10, 20, 50, 100, 200, 500 chips
*/
class Player {
private:
  std::vector<PlayerHand> hands{};
  size_t activeHand;
  long long balance;

  
  PlayerHand& getActiveHand();
public:
  Player(long long balance): balance(balance), activeHand(0), hands{} {
    if(balance < 0)
      throw std::invalid_argument("The balance cannot be negative.");
  }

  [[nodiscard]] const PlayerHand& getActiveHandConst() const;
  // activates next hand, when no more hands - does nothing
  void activateNextHand() noexcept;
  [[nodiscard]] bool hasActiveHand() const noexcept { return handsLeftToPlay() > 0; };
  [[nodiscard]] const std::vector<PlayerHand>& getAllHands() const noexcept { return hands; };
  // hands left to play including active hand
  [[nodiscard]] size_t handsLeftToPlay() const noexcept { return hands.size() - activeHand; }
  [[nodiscard]] long long getBalance() const noexcept  { return balance; }

  [[nodiscard]] bool canDoubleActiveHand() const;
  [[nodiscard]] bool canSplitActiveHand() const;

  void hitActiveHand(Shoe& shoe);
  void doubleActiveHand(Shoe& shoe);
  void standActiveHand();
  void splitActiveHand(Shoe& shoe);

  void settleHands(const Hand& dealersHand);
  void clearHands();
  void addHand(long long bet, Shoe& shoe);
};